#pragma once

#include "Camera.h"

const glm::vec3 Camera::s_bottomLeft(-2.0, -1.0, -1.0);
const glm::vec3 Camera::s_horizontal(4.0, 0.0, 0.0);
const glm::vec3 Camera::s_vertical(0.0, 2.0, 0.0);
const glm::vec3 Camera::s_origin(0.0, 0.0, 0.0);

Camera::Camera()
{
}
Camera::~Camera()
{
}

// 光線獲得
Ray Camera::getRay(float u, float v)
{
	return Ray(s_origin, s_bottomLeft + (u * s_horizontal) + (v * s_vertical));
}
