#pragma once

#include <vector>

#include "ray.h"
#include "object.h"

class World
{
public:
	World();
	~World();

	bool performRayCollision(const Ray& ray, Hit* hit) const;

	template <typename T, typename... Args>
	Ref<T> add(Args&&... args);

private:
	std::vector<Ref<Object>> m_objects;
};

template <typename T, typename... Args>
Ref<T> World::add(Args&&... args)
{
	Ref<T> object = std::make_shared<T>(std::forward<Args>(args)...);
	m_objects.push_back(object);
	return object;
}
