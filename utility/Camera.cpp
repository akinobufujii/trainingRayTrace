#include "Camera.h"

#include <cmath>
#include <random>
#include "glm/glm.hpp"

const glm::vec3 Camera::s_bottomLeft(-2.0, -1.0, -1.0);
const glm::vec3 Camera::s_horizontal(4.0, 0.0, 0.0);
const glm::vec3 Camera::s_vertical(0.0, 2.0, 0.0);
const glm::vec3 Camera::s_origin(0.0, 0.0, 0.0);

Camera::Camera()
	: m_lensRadius(0.0f)
{
}

Camera::Camera(
	const glm::vec3 &pos,
	const glm::vec3 &lookat,
	const glm::vec3 &vup,
	float fov,
	float aspect,
	float aperture,
	float focusDist)
	: m_lensRadius(0.0f)
{
	setParam(pos, lookat, vup, fov, aspect, aperture, focusDist);
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
	float aspect,
	float aperture,
	float focusDist)
{
	m_lensRadius = aperture * 0.5f;
	const float halfHeight = tan((fov * 3.14f / 180.0f) * 0.5f);
	const float halfWidth = aspect * halfHeight;

	m_w = glm::normalize(pos - lookat);
	m_u = glm::normalize(glm::cross(vup, m_w));
	m_v = glm::cross(m_w, m_u);

	m_origin = pos;
	m_bottomLeft = m_origin - halfWidth * focusDist * m_u - halfHeight * focusDist * m_v - focusDist * m_w;
	m_horizontal = 2.0f * halfWidth * focusDist * m_u;
	m_vertical = 2.0f * halfHeight * focusDist * m_v;
}

// 光線獲得
Ray Camera::getRay(float u, float v)
{
	const auto rd = rundomInUnitDisk() * m_lensRadius;
	const auto offset = rd.x * m_u + rd.y * m_v;
	return Ray(m_origin + offset, m_bottomLeft + (u * m_horizontal) + (v * m_vertical) - m_origin - offset);
}

glm::vec3 Camera::rundomInUnitDisk()
{
	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std::uniform_real_distribution<float> randomOffset(0.0f, 1.0f);

	glm::vec3 point;
	do
	{
		point = 2.0f * glm::vec3(randomOffset(randomEngine), randomOffset(randomEngine), 0.0f) - glm::vec3(1.0f, 1.0f, 0.0f);
	} while (glm::dot(point, point) >= 1.0);
	return point;
}
