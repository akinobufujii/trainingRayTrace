#include "DielectricMaterial.h"

#include <algorithm>
#include "glm/glm.hpp"
#include "Hitable.h"
#include "Ray.h"
#include "Other.h"

DielectricMaterial::DielectricMaterial()
{
}

DielectricMaterial::DielectricMaterial(float refIndex)
	: m_refIndex(refIndex)
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
	glm::vec3 outwardNormal;
	float niOverNt = 0;

	// 色は減衰しない
	attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

	if(glm::dot(in.m_dir, hitRecord.normal) > 0)
	{
		// 1~90度以内
		outwardNormal = -hitRecord.normal;
		niOverNt = m_refIndex;
	}
	else
	{
		// それ以外
		outwardNormal = hitRecord.normal;
		niOverNt = 1.0f / m_refIndex;
	}

	glm::vec3 refracted;	// 屈折ベクトル
	if(getRefrect(in.m_dir, outwardNormal, niOverNt, refracted))
	{
		// 屈折した光線を返す
		scattered = Ray(hitRecord.point, refracted);
	}
	else
	{
		// 単なる反射光線を返す
		scattered = Ray(hitRecord.point, glm::reflect(glm::normalize(in.m_dir), hitRecord.normal));
		return false;
	}

	return true;
}
