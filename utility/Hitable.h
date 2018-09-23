#pragma once

#include "glm/vec3.hpp"

class Ray;

// 衝突レコード
struct HitRecord
{
	float distance;		// 衝突した距離
	glm::vec3 point;	// 衝突した場所
	glm::vec3 normal;	// 衝突した方向
};

// 衝突しうることを表すインターフェイス
class Hitable
{
public:
	// 衝突しているかどうか
	virtual bool isHit(const Ray& ray, float min, float max, HitRecord* pResult) const = 0;
};
