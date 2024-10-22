#include <iostream>

#include "world.h"
#include "camera.h"
#include "pathtracer.h"

#include "material.h"
#include "sphere.h"
#include "plane.h"

int main()
{
	const double HEIGHT = 360.0;
	const double ASPECT = 16.0 / 9.0;
	const double WIDTH = HEIGHT * ASPECT;

	Ref<CheckerTexture> planeTexture = createRef<CheckerTexture>(Colour(0.15, 0.15, 0.15), Colour(0.85, 0.85, 0.85), 1.0);
	Ref<SolidTexture> planeEmission = createRef<SolidTexture>(Colour(0.0, 0.0, 0.0));
	Ref<SolidTexture> planeSpecular = createRef<SolidTexture>(Colour(0.0, 0.0, 0.0));

	Ref<SolidTexture> sphereTexture1 = createRef<SolidTexture>(Colour(1.0, 0.0, 0.0));
	Ref<SolidTexture> sphereTexture2 = createRef<SolidTexture>(Colour(0.0, 0.0, 1.0));
	Ref<SolidTexture> sphereTexture3 = createRef<SolidTexture>(Colour(0.0, 1.0, 0.0));
	Ref<SolidTexture> sphereEmission1 = createRef<SolidTexture>(Colour(0.0, 0.0, 0.0));
	Ref<SolidTexture> sphereEmission2 = createRef<SolidTexture>(Colour(15.0, 20.0, 35.0));
	Ref<SolidTexture> sphereSpecular = createRef<SolidTexture>(Colour(1.0, 1.0, 1.0));

	Ref<LambertianMaterial> planeMaterial = createRef<LambertianMaterial>(planeTexture, planeEmission, planeSpecular, 0.0, 0.0);

	Ref<LambertianMaterial> sphereMaterial1 = createRef<LambertianMaterial>(sphereTexture1, sphereEmission1, sphereSpecular, 0.0, 0.0);
	Ref<LambertianMaterial> sphereMaterial2 = createRef<LambertianMaterial>(sphereTexture2, sphereEmission1, sphereSpecular, 1.0, 0.5);
	Ref<LambertianMaterial> sphereMaterial3 = createRef<LambertianMaterial>(sphereTexture3, sphereEmission1, sphereSpecular, 1.0, 1.0);
	Ref<LambertianMaterial> sphereMaterial4 = createRef<LambertianMaterial>(sphereTexture3, sphereEmission2, sphereSpecular, 1.0, 1.0);

	World world;
	world.add<Plane>(planeMaterial, Vec3(0.0, -1.0, 0.0), Vec3(0.0, 1.0, 0.0));
	world.add<Sphere>(sphereMaterial1, Vec3(0.0, 0.0, 0.0), 1.0);
	world.add<Sphere>(sphereMaterial2, Vec3(2.0, 0.0, 0.0), 1.0);
	world.add<Sphere>(sphereMaterial3, Vec3(-2.0, 0.0, 0.0), 1.0);
	world.add<Sphere>(sphereMaterial4, Vec3(0.0, 0.0, 2.0), 0.25);

	Camera camera;
	Vec3 cameraPosition = { -3.0, 1.5, 5.0 };
	Vec3 cameraFocus = { 0.0, 0.0, 0.0 };
	camera.makeView(
		cameraPosition,
		cameraFocus,
		45.0,
		ASPECT,
		0.05,
		glm::length(cameraFocus - cameraPosition)
	);

	PathTracer renderer;
	renderer.setWorld(world);
	renderer.setCamera(camera);
	renderer.setSamplesPerPixel(2048);
	renderer.setMaxBounces(32);
	renderer.setOutputDimensions(WIDTH, HEIGHT);
	renderer.doGammaCorrect(false);

	renderer.renderToFileAsPPM("../output.ppm");

	system("open -a Preview ../output.ppm");

	return 0;
}
