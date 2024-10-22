#pragma once

#include "ray.h"
#include "types.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	void makeView(const Vec3& lookFrom, const Vec3& lookAt, double fov, double aspect, double aperture, double focusDistance);

	Ray getRay(double u, double v) const;

private:
	Vec3 m_position;
	Vec3 m_lowerLeftCorner;
	Vec3 m_horizontal;
	Vec3 m_vertical;

	Vec3 m_basisU, m_basisV, m_basisW;

	double m_lensRadius;
};
