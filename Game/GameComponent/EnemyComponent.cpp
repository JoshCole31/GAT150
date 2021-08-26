#include "EnemyComponent.h"
#include "Engine.h"

using namespace jc;

void EnemyComponent::Update()
{
	Actor* player = owner->scene->FindActor("Player");
	if (player)
	{
		Vector2 direction = player->transform.position - owner->transform.position;
		Vector2 force = direction.Normalized() * speed;

		physicsComponent* PhysicsComponent = owner->GetComponent<physicsComponent>();
		assert(PhysicsComponent);

		PhysicsComponent->ApplyForce(force);
	}
}
bool EnemyComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}
