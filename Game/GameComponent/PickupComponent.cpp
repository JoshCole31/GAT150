#include "PickupComponent.h"
#include "Engine.h"

using namespace jc;

PickupComponent::~PickupComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}
void PickupComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subcribe("collision_enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subcribe("collision_exit", std::bind(&PickupComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "coin.wav");
}
void PickupComponent::OnCollisionEnter(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);
	
	if (istring_compare(actor->tag, "Player"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
		owner->destroy = true;
	}
}

void PickupComponent::OnCollisionExit(const Event& event)
{
	
}
void PickupComponent::Update()
{
	
}
bool PickupComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}
