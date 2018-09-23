#pragma once

#include "Ray.h"

// カメラクラス
class Camera
{
  public:
	static const glm::vec3 s_bottomLeft; // 左下
	static const glm::vec3 s_horizontal; // 水平幅
	static const glm::vec3 s_vertical;   // 垂直幅
	static const glm::vec3 s_origin;	 // 中心

  public:
	Camera();
	Camera(
		const glm::vec3 &pos,
		const glm::vec3 &locoat,
		const glm::vec3 &vup,
		float fov,
		float aspect);

	~Camera();

	// パラメータ設定
	void setParam(
		const glm::vec3 &pos,
		const glm::vec3 &locoat,
		const glm::vec3 &vup,
		float fov,
		float aspect);

	// 光線獲得
	Ray getRay(float u, float v);

	glm::vec3 m_bottomLeft; // 左下
	glm::vec3 m_horizontal; // 水平幅
	glm::vec3 m_vertical;   // 垂直幅
	glm::vec3 m_origin;		// 中心
};
