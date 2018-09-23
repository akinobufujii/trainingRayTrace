#include "Other.h"

#include <random>
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
