#include "HitableList.h"

#include "Ray.h"

HitableList::HitableList()
{
}

HitableList::HitableList(const std::vector<std::shared_ptr<Hitable>>& list)
	: m_hitableList(list)
{
}

HitableList::~HitableList()
{
}

// 衝突しているかどうか
bool HitableList::isHit(const Ray& ray, float min, float max, HitRecord* pResult) const
{
	HitRecord hitRecord;
	bool isAnyHit = false;
	float soFar = max;

	// すべての衝突判定を行う
	for(const auto& pHitable : m_hitableList)
	{
		if(pHitable && pHitable->isHit(ray, min, soFar, &hitRecord))
		{
			// 衝突したらmaxを小さくする
			isAnyHit = true;
			soFar = hitRecord.t;
			if(pResult)
			{
				*pResult = hitRecord;
			}
		}
	}

	return isAnyHit;
}
