#pragma once

#include <vector>

#include "primitive.h"
#include "light.h"
#include "volume.h"

namespace namaste {

	typedef std::shared_ptr<class Scene> SceneRef;

	class Scene
	{
	public:
		Scene();
		~Scene();

		//bool intersect(const Ray &ray, Intersection *isect);
	private:
		PrimitiveRef mAggregate;
		std::vector<LightRef> mLights;
		VolumeRegionRef	mVolumeRegion;
	};

} // namespace namaste