#include "EnemyComponent.h"
#include "Engine.h"

using namespace jc;

void EnemyComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subcribe("player_hurt", std::bind(&EnemyComponent::OnCollisionPush, this, std::placeholders::_1), owner);
}
EnemyComponent::~EnemyComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("player_hurt", owner);
}
void EnemyComponent::OnCollisionPush(const jc::Event& event)
{
	physicsComponent* PhysicsComponent = owner->GetComponent<physicsComponent>();
	assert(PhysicsComponent);

	Vector2 newposition = owner->transform.position;
	newposition.x -= 100;
	newposition.y -= 100;
	PhysicsComponent->ApplyForce(newposition);
}
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
