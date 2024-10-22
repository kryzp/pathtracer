#include "world.h"

World::World()
{
}

World::~World()
{
}

bool World::performRayCollision(const Ray& ray, Hit* hit) const
{
	bool didHit = false;
	Hit closestHit = {};
	double closest = std::numeric_limits<double>::infinity();

	for (const auto& obj : m_objects) {
		if (obj->hit(ray, 0.001, closest, &closestHit)) {
			didHit = true;
			closest = closestHit.t;
			(*hit) = closestHit;
		}
	}

	return didHit;
}
