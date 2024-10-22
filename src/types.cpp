#include "types.h"

Vec3 getRandomDirection()
{
	return glm::sphericalRand(1.0);
}

Vec2 getRandomPointInUnitCircle()
{
	return glm::circularRand(1.0);
}

double getRandom01Double()
{
	static std::uniform_real_distribution<double> d(0.0, 1.0);
	static std::mt19937 gen;
	return d(gen);
}
