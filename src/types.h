#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> createRef(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

using Colour = glm::vec<3, double, glm::defaultp>;
using Vec3 = glm::vec<3, double, glm::defaultp>;
using Vec2 = glm::vec<2, double, glm::defaultp>;

Vec3 getRandomDirection();
Vec2 getRandomPointInUnitCircle();
double getRandom01Double();
