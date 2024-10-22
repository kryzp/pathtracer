#include "plane.h"


Plane::Plane(const Ref<Material>& mat, const Vec3& pos, const Vec3& norm)
	: Object(mat)
	, position(pos)
	, normal(norm)
{
}

bool Plane::hit(const Ray& r, double tMin, double tMax, Hit* hit) const
{
	Vec3 oc = r.origin - this->position;

	double time = -glm::dot(oc, normal) / glm::dot(r.direction, normal);

	if (glm::dot(r.direction, normal) >= 0.0) {
		return false;
	}

	if (time < tMin || time > tMax) {
		return false;
	}

	hit->t = time;
	hit->position = r.at(hit->t);
	hit->setNormal(normal, r);
	hit->material = material;

	return true;
}
