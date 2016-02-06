#pragma once

#include <memory>

namespace namaste {

	typedef std::shared_ptr<class Primitive> PrimitiveRef;

	class Primitive
	{
	public:
		Primitive();
		~Primitive();
	private:
		// Shape mShape
		// Material mMaterial
	};

} // namespace namaste
