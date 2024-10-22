#include "sphere.h"

#include <glm/glm.hpp>

Sphere::Sphere(
	const Ref<Material>& mat,
	const Vec3& pos,
	double rad
)
	: Object(mat)
	, position(pos)
	, radius(rad)
{
}

bool Sphere::hit(
	const Ray& r,
	double tMin,
	double tMax,
	Hit* hit
) const
{
	Vec3 oc = r.origin - this->position;

	double a = glm::dot(r.direction, r.direction);
	double h = glm::dot(r.direction, oc);
	double c = glm::dot(oc, oc) - (this->radius * this->radius);
	double D = (h * h) - (a * c);

	if (D < 0) {
		return false;
	}

	double sqrtD = std::sqrt(D);

	double time = (-h - sqrtD) / a;
	if (time < tMin || tMax < time) {
		time = (-h + sqrtD) / a;
		if (time < tMin || tMax < time) {
			return false;
		}
	}

	hit->t = time;
	hit->position = r.at(hit->t);
	hit->material = material;

	Vec3 n = (hit->position - this->position) / this->radius;
	hit->setNormal(n, r);

	return true;
}
