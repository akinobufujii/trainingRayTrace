#pragma once

#include "glm/vec3.hpp"

class Ray;

// 衝突レコード
struct HitRecord
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
};

// 衝突しうることを表すインターフェイス
class Hitable
{
public:
	// 衝突しているかどうか
	virtual bool isHit(const Ray& ray, float min, float max, HitRecord* pResult) const = 0;
};
