#pragma once

#include <memory>

namespace namaste {

	typedef std::shared_ptr<class Light> LightRef;

	class Light
	{
	public:
		Light();
		~Light();
	private:
	};

} // namespace namaste