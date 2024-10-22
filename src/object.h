#pragma once

#include "ray.h"
#include "types.h"
#include "material.h"

class Object
{
public:
	Object(const Ref<Material>& mat)
		: material(mat)
	{
	}

	virtual ~Object() = default;

	virtual bool hit(const Ray& r, double tMin, double tMax, Hit* hit) const = 0;

	Ref<Material> material;
};
