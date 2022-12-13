#include <iostream>
#include <vector>

#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer.h"
#include "imgui_impl_sdl.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL init falure\n";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    SDL_Window* window = SDL_CreateWindow("Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Couldn't create window\n";
        return -1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Couldn't create renderer\n";
        return -1;
    }

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    size_t textureWidth = 500;
    size_t textureHeight = 500;
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING | SDL_TEXTUREACCESS_TARGET,
        textureWidth,
        textureHeight);
    std::vector<Uint32> bufferForUpdate(textureWidth * textureHeight);

    for (int i = 0; i < bufferForUpdate.size(); i++)
    {
        bufferForUpdate[i] = 0x00000000;
    }

    SDL_UpdateTexture(texture, nullptr, bufferForUpdate.data(), textureWidth * sizeof(bufferForUpdate[0]));

    bool programWorks = true;
    int fps = 60;
    Uint64 trueFrameTime = 1000.f / fps;
    while (programWorks)
    {
        Uint64 frameTime = SDL_GetTicks();
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                ImGui_ImplSDL2_ProcessEvent(&e);
                if (e.type == SDL_QUIT)
                    programWorks = false;
            }
        }

        // UpdateImage
        {
            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("Window");

                if (ImGui::Button("Yellow"))
                {
                    for (int i = 0; i < bufferForUpdate.size(); i++)
                    {
                        bufferForUpdate[i] = 0xffff0000;
                    }
                    SDL_UpdateTexture(texture, nullptr, bufferForUpdate.data(), textureWidth * sizeof(bufferForUpdate[0]));
                }

                if (ImGui::Button("Green"))
                {
                    for (int i = 0; i < bufferForUpdate.size(); i++)
                    {
                        bufferForUpdate[i] = 0x44944A00;
                    }
                    SDL_UpdateTexture(texture, nullptr, bufferForUpdate.data(), textureWidth * sizeof(bufferForUpdate[0]));
                }

                if (ImGui::Button("White"))
                {
                    for (int i = 0; i < bufferForUpdate.size(); i++)
                    {
                        bufferForUpdate[i] = 0xffffffff;
                    }
                    SDL_UpdateTexture(texture, nullptr, bufferForUpdate.data(), textureWidth * sizeof(bufferForUpdate[0]));
                }

                ImGui::End();
            }

            ImGui::Render();

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, nullptr, nullptr);

            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderer);
        }
        
        frameTime = SDL_GetTicks() - frameTime;
        if (frameTime < trueFrameTime)
        {
            SDL_Delay(trueFrameTime - frameTime);
        }
            
    }

    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}