#pragma once

#include "glm/vec3.hpp"

// 単位球によるランダムな位置を生成
glm::vec3 randomInUnitSphere();

// 反射ベクトル獲得(屈折を考慮)
bool getRefrect(const glm::vec3& in, const glm::vec3& normal, float niOverNt, glm::vec3& refracted);