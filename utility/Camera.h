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
	~Camera();

	// 光線獲得
	static Ray getRay(float u, float v);
};
