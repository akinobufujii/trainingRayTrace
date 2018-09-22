#pragma once

#include "Ray.h"

// 光線クラス
Ray::Ray()
{
}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &dir)
	: m_origin(origin), m_dir(dir)
{
}

Ray::~Ray()
{
}

// 指定倍率分、光線を伸ばした位置を返す
const glm::vec3 Ray::pointAtParam(float t) const
{
	return m_origin + (t * m_dir);
}
