#include "material.h"
#include "ray.h"

LambertianMaterial::LambertianMaterial(const Ref<Texture>& albedo, const Ref<Texture>& emission, const Ref<Texture>& specular, double specularProbability, double smoothness)
	: albedo(albedo)
	, emission(emission)
	, specular(specular)
	, specularProbability(specularProbability)
	, smoothness(smoothness)
{
}

bool LambertianMaterial::scatter(Ray in, Ray* out, const Hit& hit) const
{
	out->origin = hit.position;

	bool isSpecularReflect = getRandom01Double() <= specularProbability;

	Vec3 diffuseDir = hit.getNormal() + getRandomDirection();
	if (glm::dot(diffuseDir, diffuseDir) <= 0.001) {
		diffuseDir = hit.getNormal();
	}

	Vec3 specularDir = glm::reflect(in.direction, hit.getNormal());

	out->direction = diffuseDir + smoothness * isSpecularReflect * (specularDir - diffuseDir);
	out->direction = glm::normalize(out->direction);

	return true;
}

Colour LambertianMaterial::colour(const Vec3& position) const
{
	return albedo->sample(position);
}

Colour LambertianMaterial::emit(const Vec3& position) const
{
	return emission->sample(position);
}
