#pragma once

#include "glm/vec3.hpp"
#include "Material.h"

// 拡散反射マテリアル
class LambertMaterial : public Material
{
  public:
	LambertMaterial();
	LambertMaterial(const glm::vec3 &albedo);

	~LambertMaterial();

	// 散乱結果を返す
	bool scatter(
		const Ray &in,
		const HitRecord &hitRecord,
		glm::vec3 &attenuation,
		Ray &scattered) const override;

	glm::vec3 m_albedo; // アルベドカラー
};
