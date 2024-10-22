#pragma once

#include "types.h"
#include "material.h"

struct Ray
{
	Vec3 origin;
	Vec3 direction;

	constexpr Vec3 at(double t) const {
		return origin + direction*t;
	}
};

struct Hit
{
	double t;
	Vec3 position;
	Ref<Material> material;

	const Vec3 getNormal() const {
		return m_normal;
	}

	void setNormal(const Vec3& normal, const Ray& ray) {
		bool frontFace = glm::dot(ray.direction, normal) < 0.0;
		m_normal = frontFace ? normal : -normal;
	}

private:
	Vec3 m_normal;
};
