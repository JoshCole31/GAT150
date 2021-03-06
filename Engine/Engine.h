#pragma once

//systems

//core
#include "Core/Utilites.h"
#include"Core/FileSystem.h"
#include "Core/Timer.h"


//math
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/Random.h"

//Object
#include "Object/Actor.h"
#include "Object/Scene.h"

#include<vector>
#include<memory>
#include<algorithm>

//Resource

//Framework
#include "Framework/EventSystem.h"

//graphics
#include"Graphics/Renderer.h"
#include"Graphics/Texture.h"
#include"Graphics/ParticleSystem.h"

#include "Graphics/Font.h"

#include "Resource/ResourceSystem.h"
#include "Input/InputSystem.h"

#include "Audio/AudioSystem.h"

namespace jc
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();
		
		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;

	};
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if(dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		return nullptr;
	}
}