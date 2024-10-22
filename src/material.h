#pragma once

#include "types.h"
#include "texture.h"

class Ray;
class Hit;

class Material
{
public:
	virtual ~Material() = default;

	virtual bool scatter(Ray in, Ray* out, const Hit& hit) const = 0;

	virtual Colour colour(const Vec3& position) const = 0;
	virtual Colour emit(const Vec3& position) const = 0;
};

class LambertianMaterial : public Material
{
public:
	LambertianMaterial(const Ref<Texture>& albedo, const Ref<Texture>& emission, const Ref<Texture>& specular, double specularProbability, double smoothness);

	bool scatter(Ray in, Ray* out, const Hit& hit) const override;

	Colour colour(const Vec3& position) const override;
	Colour emit(const Vec3& position) const override;

	Ref<Texture> albedo;
	Ref<Texture> emission;
	Ref<Texture> specular;

	double specularProbability;
	double smoothness;
};
