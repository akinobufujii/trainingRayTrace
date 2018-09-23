#include "LambertMaterial.h"

#include "Hitable.h"
#include "Ray.h"
#include "Other.h"

LambertMaterial::LambertMaterial()
{
}

LambertMaterial::LambertMaterial(const glm::vec3 &albedo)
	: m_albedo(albedo)
{
}

LambertMaterial::~LambertMaterial()
{
}

// 散乱結果を返す
bool LambertMaterial::scatter(
	const Ray &in,
	const HitRecord &hitRecord,
	glm::vec3 &attenuation,
	Ray &scattered) const
{
	// 衝突したところから更にランダムな位置に光線を飛ばして
	// 各種結果を返す
	glm::vec3 target = hitRecord.point + hitRecord.normal + randomInUnitSphere();
	scattered = Ray(hitRecord.point, target - hitRecord.point);
	attenuation = m_albedo;

	return true;
}
