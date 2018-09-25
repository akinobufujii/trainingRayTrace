#include "Other.h"

#include <random>
#include <cmath>
#include "glm/glm.hpp"

// 単位球によるランダムな位置を生成
glm::vec3 randomInUnitSphere()
{
	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_real_distribution<float> randomOffset(0.0f, 1.0f);
	glm::vec3 point;
	do
	{
		// -1 ～ +1まで範囲での単位球内の位置を抽選する
		// 範囲外のものは再抽選
		point = 2.0f * glm::vec3(randomOffset(randomEngine), randomOffset(randomEngine), randomOffset(randomEngine)) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (glm::dot(point, point) >= 1.0f);

	return point;
}

// 反射ベクトル獲得(屈折を考慮)
bool getRefrect(const glm::vec3& in, const glm::vec3& normal, float niOverNt, glm::vec3& refracted)
{
	const glm::vec3 normalizedIn = glm::normalize(in);
	float dot = glm::dot(normalizedIn, normal);
	float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dot * dot);

	if(discriminant > 0.0f)
	{
		refracted = niOverNt * (normalizedIn - normal * dot) - normal * sqrt(discriminant);
		return true;
	}

	return false;
}

// Christophe Schlick が考えた関数
// ガラスマテリアルを表現するのに使用
float schlick(float cosine, float refIdx)
{
	float r0 = (1.0f - refIdx) / (1.0f + refIdx);
	r0 *= r0;

	return r0 + (1.0f + r0) * pow(1.0f - cosine, 5.0f);
}
