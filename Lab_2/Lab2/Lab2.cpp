#include <iostream>
#include "AppWindow.h"
#include "Examples.h"
#include "Functions.h"
#include "imgui.h"
#include "Texture.h"


class Window: public AppWindow
{
public:
	Window(SDL_Point windowSize):
		AppWindow(windowSize),
		texture(GetRenderer(), windowSize)
	{
	}
	
	void Render() override
	{
		texture.Render();
	}
	
	void RenderGui() override
	{
		ImGui::Begin("MyWindow");
		if (ImGui::Button("Example 1"))
			Example1(texture);
		if (ImGui::Button("Example 2"))
			Example2(texture);
		if (ImGui::Button("Example 3"))
			Example3(texture);
		if (ImGui::Button("Example 4"))
			Example4(texture);
		ImGui::End();
	}
	
	void ProcessEvent(const SDL_Event& e) override
	{
		 if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					SDL_Point startPoint;
					startPoint.x = e.button.x;
					startPoint.y = e.button.y;
					GradientDescent(startPoint, 2);
				}
	}
	}

	void GradientDescent(SDL_Point startPoint, int step, SDL_Color pathColor = { 0, 255, 0, 255 })
	{
		// Спускаемся пока не выйдем за пределы пространства текстуры
		while (startPoint.x >= 0 && startPoint.x < texture.GetSize().x &&
			startPoint.y >= 0 && startPoint.y < texture.GetSize().y)
		{
			// Проверяем, не попали ли мы в точку, которая уже была рассчитана
			SDL_Color newColor = texture.GetColor({ startPoint.x, startPoint.y });
			if (newColor.r == pathColor.r &&
				newColor.g == pathColor.g &&
				newColor.b == pathColor.b &&
				newColor.a == pathColor.a)
			{
				break;
			}

			// Окрашивание пути
			texture.SetPixel({ startPoint.x, startPoint.y }, pathColor);

			// Рассчет ЛГХ в текущей точке
			MImagePixelData data = calculator.GetPixelData({ startPoint.x, startPoint.y });
			// Движение по направлению убывания с шагом
			startPoint.x -= step * data.nx;
			startPoint.y += step * data.ny;
		}
		texture.UpdateTexture();
	}
	
	Texture texture;
};


int main(int argc, char** argv)
{
	Window window({800, 600});
	
	window.Show();
	
	return 0;
}