#include "PlayerComponent.h"
#include "Engine.h"

using namespace jc;

PlayerComponent::~PlayerComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}
void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subcribe("collision_enter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1),owner);
	owner->scene->engine->Get<EventSystem>()->Subcribe("collision_exit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1),owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "hurt.wav");
}
void PlayerComponent::Update()
{
	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
		force.x -= speed;
	}
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
		force.x += speed;
	}
	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)
	{
		force.y -= 300;
	}
	physicsComponent* PhysicsComponent=owner->GetComponent<physicsComponent>();
	assert(PhysicsComponent);
	PhysicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);

	if (PhysicsComponent->velocity.x >0) spriteAnimationComponent->StartSequence("walk_right");
	else if(PhysicsComponent->velocity.x < 0)spriteAnimationComponent->StartSequence("walk_left");
	else spriteAnimationComponent->StartSequence("idle");
}

void PlayerComponent::OnCollisionEnter(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);
	if (istring_compare(actor->tag, "ground"))
	{
		contacts.push_back(actor);
	}
	if (istring_compare(actor->tag, "enemy"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
	}
}

void PlayerComponent::OnCollisionExit(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);
	if (istring_compare(actor->tag,"ground"))
	{
		contacts.remove(actor);
	}
}
bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}

