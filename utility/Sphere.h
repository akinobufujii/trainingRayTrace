#pragma once

#include "hitable.h"

// 球
class Sphere : public Hitable
{
public:
	Sphere();
	Sphere(const glm::vec3& center, float radius);

	~Sphere();

	// 衝突しているかどうか
	bool isHit(const Ray& ray, float min, float max, HitRecord* pResult) const override;

private:
	glm::vec3 m_center;	// 中心座標
	float m_radius;		// 半径
};
