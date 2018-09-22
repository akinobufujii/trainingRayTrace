#pragma once

#include "glm/vec3.hpp"

// 光線クラス
class Ray
{
  public:
	Ray();
	Ray(const glm::vec3 &origin, const glm::vec3 &dir);

	~Ray();

	// 指定倍率分、光線を伸ばした位置を返す
	const glm::vec3 pointAtParam(float t) const;

	glm::vec3 m_origin; // 光線の原点
	glm::vec3 m_dir;	// 光線の方向
};
