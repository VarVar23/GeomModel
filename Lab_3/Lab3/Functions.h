#pragma once
#include "SDL_rect.h"
#include <cmath>

namespace Functions
{
// R-функциональное пересечение
	inline float RAnd(float f1, float f2)
	{
		return f1 + f2 - std::sqrt(powf(f1, 2) + powf(f2, 2));
	}

	// R-функциональное объежигегте
	inline float ROr(float f1, float f2)
	{
		return f1 + f2 + std::sqrt(powf(f1, 2) + powf(f2, 2));
	}

	inline float Circle(SDL_FPoint position, float radius, SDL_FPoint args)
	{
		return powf(radius, 2) - powf(args.x - position.x, 2) - powf(args.y - position.y, 2);
	}
	inline float Circle(SDL_Point position, float radius, SDL_Point args)
	{
		return powf(radius, 2) - powf(args.x - position.x, 2) - powf(args.y - position.y, 2);
	}

	inline float Rectangle(SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint args)
	{
		float up = -p2.y + args.y;
		float down = -args.y + p1.y;
		float left = args.x - p1.x;
		float right = p2.x - args.x;

		return RAnd(up, RAnd(down, RAnd(left, right)));
	}
	inline float Rectangle(SDL_Point p1, SDL_Point p2, SDL_Point args)
	{
		return Rectangle(SDL_FPoint{ (float)p1.x, (float)p1.y },
			SDL_FPoint{ (float)p2.x, (float)p2.y },
			SDL_FPoint{ (float)args.x, (float)args.y });
	}
}

// тип М-Образа
enum MImageType
{
	Cx, Cy, Cz, Cd
};
// тип для обозначения того, какой зоне принадлежит точка
enum FunctionZone
{
	Negative, Positive
};
// геометрическая информация о точке в пространстве
struct MImagePixelData
{
	double nx, ny, nz, nd;
	FunctionZone zone;
};

