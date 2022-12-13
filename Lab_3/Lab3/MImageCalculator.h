#pragma once
#include "SDL.h"
#include <vector>
#include "Functions.h"
#include <iostream>
#include <functional>


class MImageCalculator
{
public:
	MImageCalculator(const std::function<float(SDL_Point pixel)>& computeFunction);
	std::vector<std::vector<MImagePixelData>> GetSpaceData(SDL_Point spaceSize);
	MImagePixelData GetPixelData(SDL_Point point);

private:
	std::function<float(SDL_Point)> _computeFunction;
	
};

