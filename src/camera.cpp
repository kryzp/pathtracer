#include "camera.h"

void Camera::makeView(
	const Vec3& eyePosition, const Vec3& lookAt,
	double fov, double aspect, double aperture, double focusDistance
)
{
	double theta = glm::radians(fov);
	double h = glm::tan(theta * 0.5);
	double viewportHeight = 2.0 * h;
	double viewportWidth = aspect * viewportHeight;

	m_basisW = glm::normalize(eyePosition - lookAt);
	m_basisU = glm::normalize(glm::cross(Vec3(0.0, 1.0, 0.0), m_basisW));
	m_basisV = glm::normalize(glm::cross(m_basisW, m_basisU));

	m_position = eyePosition;

	m_horizontal = focusDistance * viewportWidth * m_basisU;
	m_vertical = focusDistance * viewportHeight * m_basisV;

	m_lensRadius = aperture / 2.0;

	m_lowerLeftCorner = m_position
		- (m_horizontal / 2.0)
		- (m_vertical / 2.0)
		- (focusDistance * m_basisW);
}

Ray Camera::getRay(double u, double v) const
{
	Vec2 rd = m_lensRadius * getRandomPointInUnitCircle();
	Vec3 offset = (m_basisU * rd.x) + (m_basisV * rd.y);

	Ray r = {};
	r.origin = m_position + offset;
	r.direction = glm::normalize(
		m_lowerLeftCorner - r.origin
		+ (u * m_horizontal)
		+ (v * m_vertical)
	);

	return r;
}
