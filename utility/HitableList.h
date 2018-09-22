#pragma once

#include <vector>
#include <memory>

#include "Hitable.h"

// 衝突リスト
class HitableList : public Hitable
{
public:
	HitableList();
	HitableList(const std::vector<std::shared_ptr<Hitable>>& list);

	~HitableList();

	// 衝突しているかどうか
	bool isHit(const Ray& ray, float min, float max, HitRecord* pResult) const override;

	std::vector<std::shared_ptr<Hitable>>	m_hitableList;	// 衝突物リスト
};
