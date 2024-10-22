#pragma once

#include "types.h"

class Texture
{
public:
	virtual ~Texture() = default;

	virtual Colour sample(const Vec3& position) const = 0;
};

class SolidTexture : public Texture
{
public:
	SolidTexture(const Colour& colour);

	Colour sample(const Vec3& position) const override;

	Colour colour;
};

class CheckerTexture : public Texture
{
public:
	CheckerTexture(const Colour& a, const Colour& b, double size);

	Colour sample(const Vec3& position) const override;

	Colour colourA;
	Colour colourB;
	double checkerSize;
};
