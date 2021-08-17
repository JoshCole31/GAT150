#pragma once
#include "Object/Actor.h"

class HealthPack : public jc::Actor
{
public:
	HealthPack( jc::Vector2 v, std::shared_ptr<jc::Texture> texture, float speed) : jc::Actor{ v, texture }, speed{ speed }{}

	void Update(float dt)override;
	void OnCollision(Actor* actor)override;
private:
	float speed = { 200 };

};
