#include "pathtracer.h"
#include "material.h"

#include <iostream>
#include <fstream>

PathTracer::PathTracer()
	: m_outputWidth(0)
	, m_outputHeight(0)
	, m_samplesPerPixel(1)
	, m_maxBounces(1)
	, m_gammaCorrect(false)
	, m_world(nullptr)
	, m_camera(nullptr)
{
}

Colour PathTracer::traceRay(const Ray& ray) const
{
//	Hit hh = {};
//	m_world->performRayCollision(ray, &hh);
//	return 0.5 * (Vec3(1.0) + hh.getNormal());

	Colour outputLight(0.0, 0.0, 0.0);
	Colour currentRayColour(1.0, 1.0, 1.0);

	Ray myRay = ray;

	for (int i = 0; i < m_maxBounces; i++)
	{
		Hit hit = {};
		bool didHit = m_world->performRayCollision(myRay, &hit);

		if (didHit)
		{
			const Ref<Material>& material = hit.material;

			if (material->scatter(myRay, &myRay, hit))
			{
				Colour emittedLight = material->emit(hit.position);
				outputLight += emittedLight * currentRayColour;
				currentRayColour *= material->colour(hit.position);

				double probabilityOfDiscard = glm::max(currentRayColour.r, glm::max(currentRayColour.g, currentRayColour.b));
				if (getRandom01Double() >= probabilityOfDiscard) {
					break;
				} else {
					currentRayColour *= 1.0 / probabilityOfDiscard;
				}
			}
		}
		else
		{
			outputLight += getEnvironmentLight(myRay) * currentRayColour;
			break;
		}
	}

	return outputLight;
}

Colour PathTracer::getEnvironmentLight(const Ray& ray)
{
	double t = 0.5 * (ray.direction.y + 1.0);
	return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.65, 0.65, 0.85);
}

void PathTracer::renderToFileAsPPM(const char* path)
{
	std::cout << "begun rendering..." << std::endl;

	std::ofstream outFile(path);
	outFile << "P3\n" << m_outputWidth << " " << m_outputHeight << "\n255\n";

	for (int i = m_outputHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < m_outputWidth; j++)
		{
			Colour pixel(0.0, 0.0, 0.0);

			for (int k = 0; k < m_samplesPerPixel; k++)
			{
				double u = ((double)j + getRandom01Double()) / (m_outputWidth - 1);
				double v = ((double)i + getRandom01Double()) / (m_outputHeight - 1);

				Ray ray = m_camera->getRay(u, v);

				pixel += traceRay(ray);
			}

			double factor = 1.0 / (double)m_samplesPerPixel;

			if (m_gammaCorrect) {
				pixel.r = glm::sqrt(pixel.r * factor);
				pixel.g = glm::sqrt(pixel.g * factor);
				pixel.b = glm::sqrt(pixel.b * factor);
			} else {
				pixel.r = pixel.r * factor;
				pixel.g = pixel.g * factor;
				pixel.b = pixel.b * factor;
			}

			outFile
				<< (int)(glm::clamp(pixel.r, 0.0, 0.999) * 256.0) << " "
				<< (int)(glm::clamp(pixel.g, 0.0, 0.999) * 256.0) << " "
				<< (int)(glm::clamp(pixel.b, 0.0, 0.999) * 256.0) << "\n";
		}

		std::cout << (100.0 - 100.0*(double)i/(double)m_outputHeight) << "%" << std::endl;
	}

	outFile.close();

	std::cout << "finished rendering!" << std::endl;
}

void PathTracer::setWorld(const World& world)
{
	m_world = &world;
}

void PathTracer::setCamera(const Camera& camera)
{
	m_camera = &camera;
}

void PathTracer::setSamplesPerPixel(int samplesPerPixel)
{
	m_samplesPerPixel = samplesPerPixel;
}

void PathTracer::setMaxBounces(int maxBounces)
{
	m_maxBounces = maxBounces;
}

void PathTracer::setOutputDimensions(int width, int height)
{
	m_outputWidth = width;
	m_outputHeight = height;
}

void PathTracer::doGammaCorrect(bool bb)
{
	m_gammaCorrect = bb;
}
