#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glm/ext.hpp"

// 光線クラス
class Ray
{
  public:
	Ray() {}
	Ray(const glm::vec3 &origin, const glm::vec3 &dir)
		: m_origin(origin), m_dir(dir)
	{
	}

	~Ray() {}

	const glm::vec3 pointAtParam(float t)
	{
		return m_origin + (t * m_dir);
	}

	glm::vec3 m_origin; // 光線の原点
	glm::vec3 m_dir;	// 光線の方向
};

// 色計算（レイトレース処理）
glm::vec3 calcColor(const Ray& ray)
{
	auto normalizedDir = glm::normalize(ray.m_dir);
	float t = glm::clamp(0.5f * (normalizedDir.y + 1.0f), 0.0f, 1.0f);

	// 倍率に応じて水色と白を線形補間
	return glm::mix(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.7f, 1.0f), t);
}

int main(int, char **)
{
	std::cout << "start ratrace\n";

	constexpr int nx = 200;
	constexpr int ny = 100;
	constexpr int bpp = 3;

	glm::vec3 lowerLeftCorner(-2.0, -1.0, -1.0);	// 左下
	glm::vec3 horizontal(4.0, 0.0, 0.0);			// 水平幅
	glm::vec3 vertical(0.0, 2.0, 0.0);				// 垂直幅
	glm::vec3 origin(0.0, 0.0, 0.0);				// 中心

	char *data = new char[nx * ny * bpp];
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			// 左下からレイを飛ばして走査していく
			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
			auto color = calcColor(ray);

			const int offset = ((ny - 1 - j) * nx * bpp) + (i * bpp);
			data[offset + 0] = int(255.99f * color.x);
			data[offset + 1] = int(255.99f * color.y);
			data[offset + 2] = int(255.99f * color.z);
		}
	}

	stbi_write_tga("output.tga", nx, ny, bpp, data);

	std::cout << "end ratrace\n";
}
