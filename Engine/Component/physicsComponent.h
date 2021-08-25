#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"

namespace jc
{
	class physicsComponent : public Component
	{
	public:
		void Update() override;
		virtual void ApplyForce(const Vector2& force) { acceleration += force; }

			// Inherited via Component
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
	public:
			Vector2 velocity;
			Vector2 acceleration;
			float damping = 1;
	};
}