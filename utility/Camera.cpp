#include "Camera.h"

#include <cmath>
#include "glm/glm.hpp"

const glm::vec3 Camera::s_bottomLeft(-2.0, -1.0, -1.0);
const glm::vec3 Camera::s_horizontal(4.0, 0.0, 0.0);
const glm::vec3 Camera::s_vertical(0.0, 2.0, 0.0);
const glm::vec3 Camera::s_origin(0.0, 0.0, 0.0);

Camera::Camera()
{
}

Camera::Camera(
	const glm::vec3 &pos,
	const glm::vec3 &lookat,
	const glm::vec3 &vup,
	float fov,
	float aspect)
{
	setParam(pos, lookat, vup, fov, aspect);
}

Camera::~Camera()
{
}

// パラメータ設定
void Camera::setParam(
	const glm::vec3 &pos,
	const glm::vec3 &lookat,
	const glm::vec3 &vup,
	float fov,
	float aspect)
{
	const float halfHeight = tan((fov * 3.14f / 180.0f) * 0.5f);
	const float halfWidth = aspect * halfHeight;

	const glm::vec3 w = glm::normalize(pos - lookat);
	const glm::vec3 u = glm::normalize(glm::cross(vup, w));
	const glm::vec3 v = glm::cross(w, u);

	m_origin = pos;
	m_bottomLeft = m_origin - halfWidth * u - halfHeight * v - w;
	m_horizontal = 2.0f * halfWidth * u;
	m_vertical = 2.0f * halfHeight * v;
}

// 光線獲得
Ray Camera::getRay(float u, float v)
{
	return Ray(m_origin, m_bottomLeft + (u * m_horizontal) + (v * m_vertical) - m_origin);
}
