#include <iostream>
#include <float.h>
#include <memory>
#include <random>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glm/glm.hpp"

#include "utility/Ray.h"
#include "utility/Sphere.h"
#include "utility/HitableList.h"
#include "utility/Camera.h"

// 単位球によるランダムな位置を生成
glm::vec3 randomInUnitSphere(
	std::mt19937 &randomEngine,
	std::uniform_real_distribution<float> &randomOffset)
{
	glm::vec3 point;
	do
	{
		// -1 ～ +1まで範囲での単位球内の位置を抽選する
		// 範囲外のものは再抽選
		point = 2.0f * glm::vec3(randomOffset(randomEngine), randomOffset(randomEngine), randomOffset(randomEngine)) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (glm::dot(point, point) >= 1.0f);

	return point;
}

// 色計算（レイトレース処理）
glm::vec3 calcColor(
	std::mt19937 &randomEngine,
	std::uniform_real_distribution<float> &randomOffset,
	const Ray &ray,
	const std::shared_ptr<Hitable> &pWorld)
{
	HitRecord hitRecord;

	// シャドウアクネ問題を解決するために
	// 極めて0に近い値を最小値として渡す
	if (pWorld && pWorld->isHit(ray, FLT_EPSILON * 2.0f, FLT_MAX, &hitRecord))
	{
		// 衝突したところから更にランダムな位置に光線を飛ばして
		// 50%の色で返却する
		glm::vec3 target = hitRecord.point + hitRecord.normal + randomInUnitSphere(randomEngine, randomOffset);
		return 0.5f * calcColor(randomEngine, randomOffset, Ray(hitRecord.point, target - hitRecord.point), pWorld);
	}

	auto normalizedDir = glm::normalize(ray.m_dir);
	float t = 0.5f * (normalizedDir.y + 1.0f);

	// 倍率に応じて白色と水色を線形補間
	return glm::mix(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.7f, 1.0f), t);
}

int main(int, char **)
{
	std::cout << "start ray trace" << std::endl;

	constexpr int width = 200;		   // 幅
	constexpr int height = 100;		   // 高さ
	constexpr int bpp = 3;			   // 画像データの色要素数
	constexpr int samplingCount = 100; // アンチエイジングのサンプル数

	// レイトレース用のデータ作成
	auto pWorld = std::make_shared<HitableList>(
		std::vector<std::shared_ptr<Hitable>>(
			{
				std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f),
				std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f),
			}));

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_real_distribution<float> randomOffset(0.0f, 1.0f);

	char *data = new char[width * height * bpp];
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			glm::vec3 color(0.0f, 0.0f, 0.0f);
			for (int i = 0; i < samplingCount; ++i)
			{
				// ジッタリングを行う
				const float u = float(x + randomOffset(randomEngine)) / float(width);
				const float v = float(y + randomOffset(randomEngine)) / float(height);

				// 左下からレイを飛ばして走査していく
				const Ray ray = Camera::getRay(u, v);
				color += calcColor(randomEngine, randomOffset, ray, pWorld);
			}

			// ガンマ補正
			color = glm::sqrt(color / float(samplingCount)) * 255.99f;

			// 画像データ出力用にバッファに書いていく
			const int offset = ((height - 1 - y) * width * bpp) + (x * bpp);
			data[offset + 0] = char(color.x);
			data[offset + 1] = char(color.y);
			data[offset + 2] = char(color.z);
		}
	}

	stbi_write_tga("output.tga", width, height, bpp, data);

	std::cout << "end ray trace" << std::endl;
}
