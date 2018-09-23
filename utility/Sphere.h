#pragma once

#include <memory>
#include "hitable.h"

class Material;

// 球
class Sphere : public Hitable
{
  public:
	Sphere();
	Sphere(const glm::vec3 &center, float radius, const std::shared_ptr<Material> &pMaterial);

	~Sphere();

	// 衝突しているかどうか
	bool isHit(const Ray &ray, float min, float max, HitRecord *pResult) const override;

  private:
	glm::vec3 m_center;					   // 中心座標
	float m_radius;						   // 半径
	std::shared_ptr<Material> m_pMaterial; // マテリアル
};
