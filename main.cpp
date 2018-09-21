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
	float t = 0.5f * (normalizedDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

int main(int, char **)
{
	std::cout << "start ratrace\n";

	constexpr int nx = 200;
	constexpr int ny = 100;
	constexpr int bpp = 3;

	glm::vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
	glm::vec3 horizontal(4.0, 0.0, 0.0);
	glm::vec3 vertical(0.0, 2.0, 0.0);
	glm::vec3 origin(0.0, 0.0, 0.0);

	char *data = new char[nx * ny * bpp];
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
			auto color = calcColor(ray);

			int ir = int(255.99f * color.x);
			int ig = int(255.99f * color.y);
			int ib = int(255.99f * color.z);

			const int offset = ((ny - 1 - j) * nx * bpp) + (i * bpp);
			data[offset + 0] = ir;
			data[offset + 1] = ig;
			data[offset + 2] = ib;
		}
	}

	stbi_write_tga("output.tga", nx, ny, bpp, data);

	std::cout << "end ratrace\n";
}
