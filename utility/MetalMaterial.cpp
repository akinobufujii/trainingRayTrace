#include "MetalMaterial.h"

#include <algorithm>
#include "glm/glm.hpp"
#include "Hitable.h"
#include "Ray.h"
#include "Other.h"

MetalMaterial::MetalMaterial()
{
}

MetalMaterial::MetalMaterial(const glm::vec3 &albedo, float fuzziness)
	: m_albedo(albedo), m_fuzziness(std::max(fuzziness, 1.0f))
{
}

MetalMaterial::~MetalMaterial()
{
}

// 散乱結果を返す
bool MetalMaterial::scatter(
	const Ray &in,
	const HitRecord &hitRecord,
	glm::vec3 &attenuation,
	Ray &scattered) const
{
	// 光線と衝突した方向の反射ベクトルを取得
	auto reflectVec = glm::reflect(glm::normalize(in.m_dir), hitRecord.normal);

	// 反射による光線生成を少しブレさせる
	scattered = Ray(hitRecord.point, reflectVec + m_fuzziness * randomInUnitSphere());
	attenuation = m_albedo;

	// 1~90度以内なら散乱したと判断する
	return glm::dot(scattered.m_dir, reflectVec) > 0;
}
