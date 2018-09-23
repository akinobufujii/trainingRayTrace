#include "DielectricMaterial.h"

#include <algorithm>
#include <random>
#include "glm/glm.hpp"
#include "Hitable.h"
#include "Ray.h"
#include "Other.h"

DielectricMaterial::DielectricMaterial()
{
}

DielectricMaterial::DielectricMaterial(float refIdx)
	: m_refIdx(refIdx)
{
}

DielectricMaterial::~DielectricMaterial()
{
}

// 散乱結果を返す
bool DielectricMaterial::scatter(
	const Ray &in,
	const HitRecord &hitRecord,
	glm::vec3 &attenuation,
	Ray &scattered) const
{
	// 色は減衰しない
	attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 outwardNormal;
	float niOverNt = 0;
	float cosine = 0;

	if(glm::dot(in.m_dir, hitRecord.normal) > 0)
	{
		// 1~90度以内
		outwardNormal = -hitRecord.normal;
		niOverNt = m_refIdx;
		cosine = m_refIdx * glm::dot(in.m_dir, hitRecord.normal) / glm::length(in.m_dir);
	}
	else
	{
		// それ以外
		outwardNormal = hitRecord.normal;
		niOverNt = 1.0f / m_refIdx;
		cosine = -glm::dot(in.m_dir, hitRecord.normal) / glm::length(in.m_dir);
	}

	glm::vec3 refracted;	// 屈折ベクトル
	float reflectProb = (getRefrect(in.m_dir, outwardNormal, niOverNt, refracted)) ? schlick(cosine, m_refIdx) : 1.0f;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_real_distribution<float> randomOffset(0.0f, 1.0f);

	if(randomOffset(randomEngine) < reflectProb)
	{
		scattered = Ray(hitRecord.point, refracted);
	}
	else
	{
		scattered = Ray(hitRecord.point, glm::reflect(glm::normalize(in.m_dir), hitRecord.normal));
	}

	return true;
}
