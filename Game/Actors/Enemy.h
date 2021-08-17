#pragma once
#include "Object/Actor.h"

class Enemy : public jc::Actor
{
public:
	Enemy(const jc::Transform& transform, std::shared_ptr<jc::Texture> texture, float speed) : jc::Actor{ transform, texture }, speed{ speed }{}

	void Update(float dt)override;
	void OnCollision(Actor* actor)override;
private:
	float speed = { 200 };
	float fireTimer{ 0 };
	float fireRate{ 0.8f };
};