#pragma once

#include "object.h"
#include "types.h"
#include "ray.h"

class Sphere : public Object
{
public:
	Sphere(const Ref<Material>& mat, const Vec3& pos, double rad);

	bool hit(const Ray& r, double tMin, double tMax, Hit* hit) const override;

	Vec3 position;
	double radius;
};
