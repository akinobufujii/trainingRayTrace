#pragma once

class Ray;
class HitRecord;

// マテリアルインターフェイス
class Material
{
  public:
	// 散乱結果を返す
	virtual bool scatter(
		const Ray &in,
		const HitRecord &hitRecord,
		glm::vec3 &attenuation,
		Ray &scatterd) const = 0;
};
