#pragma once

#include "object.h"

class Plane : public Object
{
public:
	Plane(const Ref<Material>& mat, const Vec3& pos, const Vec3& norm);

	bool hit(const Ray& r, double tMin, double tMax, Hit* hit) const override;

	Vec3 position;
	Vec3 normal;
};
