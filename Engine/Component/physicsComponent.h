#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"

namespace jc
{
	class physicsComponent : public Component
	{
	public:
		void Update() override;
		void ApplyForce(const Vector2& force) { acceleration += force; }

	public:
			Vector2 velocity;
			Vector2 acceleration;
	};
}