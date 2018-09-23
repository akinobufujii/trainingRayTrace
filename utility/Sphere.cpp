#include "Sphere.h"

#include "Ray.h"
#include "glm/glm.hpp"

Sphere::Sphere()
	: m_radius(0.0f)
{
}

Sphere::Sphere(const glm::vec3 &center, float radius, const std::shared_ptr<Material> &pMaterial)
	: m_center(center), m_radius(radius), m_pMaterial(pMaterial)
{
}

Sphere::~Sphere()
{
}

// 衝突しているかどうか
bool Sphere::isHit(const Ray &ray, float min, float max, HitRecord *pResult) const
{
	glm::vec3 centerToRay = ray.m_origin - m_center;

	// 半径の2乗と(光線 - 球の中心)の2乗は等しい
	// (光線 - 球の中心)の2乗 = (光線 - 球の中心)・(光線 - 球の中心)と表すことができる
	// そのため、「(光線 - 球の中心)・(光線 - 球の中心) = 半径の2乗」と表せる
	float a = glm::dot(ray.m_dir, ray.m_dir);
	float b = glm::dot(centerToRay, ray.m_dir);
	float c = glm::dot(centerToRay, centerToRay) - m_radius * m_radius;

	// 光線と球があたっているかの解の公式に当てはめる
	// →「x = (-b +- sqrt(b * b - a * c)) / a」
	// 平方根内の計算が実数(0より上)ならあたっている可能性がある
	float discreminat = b * b - a * c;
	if (discreminat > 0.0f)
	{
		// 判定して、結果を書き込むラムダ式
		auto judgeAndWriteResult = [&](float distance) {
			if (min < distance && distance < max)
			{
				if (pResult)
				{
					pResult->distance = distance;
					pResult->point = ray.pointAtParam(distance);
					pResult->normal = (pResult->point - m_center) / m_radius;
					pResult->pMaterial = m_pMaterial;
				}
				return true;
			}
			return false;
		};

		// 球の中心から光線が出ている方向にあたっているか判定
		if (judgeAndWriteResult((-b - sqrt(discreminat)) / a))
		{
			return true;
		}

		// 反対側判定
		if (judgeAndWriteResult((-b + sqrt(discreminat)) / a))
		{
			return true;
		}
	}

	return false;
}