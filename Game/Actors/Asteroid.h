#pragma once
#include "Object/Actor.h"

class Asteroid : public jc::Actor
{
public:
	Asteroid(const jc::Transform& transform, std::shared_ptr<jc::Texture> texture, float speed) : jc::Actor{ transform, texture }, speed{ speed }{}

	void Update(float dt)override;
	void OnCollision(Actor* actor)override;
private:
	float speed = { 200 };

};