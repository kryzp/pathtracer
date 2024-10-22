#include "texture.h"

SolidTexture::SolidTexture(const Colour& colour)
	: colour(colour)
{
}

Colour SolidTexture::sample(const Vec3& position) const
{
	return colour;
}

/***************************************/

CheckerTexture::CheckerTexture(const Colour& a, const Colour& b, double size)
	: colourA(a)
	, colourB(b)
	, checkerSize(size)
{
}

Colour CheckerTexture::sample(const Vec3& position) const
{
	double xx = glm::mod(position.x, checkerSize * 2.0);
	double zz = glm::mod(position.z, checkerSize * 2.0);

	if (((int)(xx < checkerSize) + (int)(zz < checkerSize)) % 2 == 0) {
		return colourA;
	} else {
		return colourB;
	}
}
