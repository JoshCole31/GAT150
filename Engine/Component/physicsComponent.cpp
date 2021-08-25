#include "physicsComponent.h"
#include "Engine.h"
namespace jc {

	void physicsComponent::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		velocity *= damping;

		acceleration = Vector2::zero;
	}
	bool physicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool physicsComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, damping);

		return true;
	}
}
