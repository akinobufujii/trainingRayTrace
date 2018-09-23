#pragma once

#include "glm/vec3.hpp"
#include "Material.h"

// 金属反射マテリアル
class MetalMaterial : public Material
{
  public:
	MetalMaterial();
	MetalMaterial(const glm::vec3& albedo, float fuzziness);

	~MetalMaterial();

	// 散乱結果を返す
	bool scatter(
		const Ray &in,
		const HitRecord &hitRecord,
		glm::vec3 &attenuation,
		Ray &scattered) const override;

	glm::vec3 m_albedo; // アルベドカラー
	float m_fuzziness;	// 曖昧さ(反射方向を少しバラつかせるのに使用)
};
