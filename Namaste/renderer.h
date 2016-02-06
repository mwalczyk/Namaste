#pragma once

#include "scene.h"

namespace namaste {
	
	typedef std::shared_ptr<class Renderer> RendererRef;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		virtual void render(const SceneRef scene) = 0; 
	private:
	};

} // namespace namaste


