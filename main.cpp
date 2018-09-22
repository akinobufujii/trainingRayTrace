#include <iostream>
#include <float.h>
#include <memory>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glm/glm.hpp"

#include "utility/Ray.h"
#include "utility/Sphere.h"
#include "utility/HitableList.h"

// 色計算（レイトレース処理）
glm::vec3 calcColor(const Ray &ray, const std::shared_ptr<Hitable> &pWorld)
{
	HitRecord hitRecord;
	if (pWorld->isHit(ray, 0.0f, FLT_MAX, &hitRecord))
	{
		// 法線の色を出力する
		return 0.5f * (hitRecord.normal + 1.0f);
	}

	auto normalizedDir = glm::normalize(ray.m_dir);
	float t = 0.5f * (normalizedDir.y + 1.0f);

	// 倍率に応じて白色と水色を線形補間
	return glm::mix(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.7f, 1.0f), t);
}

int main(int, char **)
{
	std::cout << "start ray trace" << std::endl;

	constexpr int nx = 200;
	constexpr int ny = 100;
	constexpr int bpp = 3;

	const glm::vec3 lowerLeftCorner(-2.0, -1.0, -1.0); // 左下
	const glm::vec3 horizontal(4.0, 0.0, 0.0);		   // 水平幅
	const glm::vec3 vertical(0.0, 2.0, 0.0);		   // 垂直幅
	const glm::vec3 origin(0.0, 0.0, 0.0);			   // 中心

	// レイトレース用のデータ作成
	auto pWorld = std::make_shared<HitableList>(
		std::vector<std::shared_ptr<Hitable>>(
			{
				std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f),
				std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f),
			}));

	char *data = new char[nx * ny * bpp];
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			// 左下からレイを飛ばして走査していく
			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
			auto color = calcColor(ray, pWorld);

			// 画像データ出力用にバッファに書いていく
			const int offset = ((ny - 1 - j) * nx * bpp) + (i * bpp);
			data[offset + 0] = char(255.99f * color.x);
			data[offset + 1] = char(255.99f * color.y);
			data[offset + 2] = char(255.99f * color.z);
		}
	}

	stbi_write_tga("output.tga", nx, ny, bpp, data);

	std::cout << "end ray trace" << std::endl;
}
