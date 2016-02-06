#pragma once

#include <memory>

namespace namaste {

	typedef std::shared_ptr<class VolumeRegion> VolumeRegionRef;

	class VolumeRegion
	{
	public:
		VolumeRegion();
		~VolumeRegion();
	private:
	};

} // namespace namaste

