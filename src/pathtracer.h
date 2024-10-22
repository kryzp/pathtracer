#pragma once

#include "types.h"
#include "ray.h"
#include "world.h"
#include "camera.h"

// path
class PathTracer
{
public:
	PathTracer();
	~PathTracer() = default;

	void renderToFileAsPPM(const char* path);

	void setWorld(const World& world);
	void setCamera(const Camera& camera);
	void setSamplesPerPixel(int samplesPerPixel);
	void setMaxBounces(int maxBounces);
	void setOutputDimensions(int width, int height);
	void doGammaCorrect(bool bb);

private:
	Colour traceRay(const Ray& ray) const;
	static Colour getEnvironmentLight(const Ray& ray) ;

	int m_outputWidth;
	int m_outputHeight;
	int m_samplesPerPixel;
	int m_maxBounces;
	bool m_gammaCorrect;

	const World* m_world;
	const Camera* m_camera;
};
