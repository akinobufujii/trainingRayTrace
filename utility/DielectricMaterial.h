#pragma once

#include "glm/vec3.hpp"
#include "Material.h"

// 誘電体マテリアル
class DielectricMaterial : public Material
{
  public:
	DielectricMaterial();
	DielectricMaterial(float refIdx);

	~DielectricMaterial();

	// 散乱結果を返す
	bool scatter(
		const Ray &in,
		const HitRecord &hitRecord,
		glm::vec3 &attenuation,
		Ray &scattered) const override;

	float m_refIdx;
};
