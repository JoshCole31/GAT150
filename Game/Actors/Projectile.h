#pragma once
#include "Object/Actor.h"

class Projectile : public jc::Actor
{
public:
	Projectile(const jc::Transform& transform, std::shared_ptr<jc::Texture> texture, float speed) : jc::Actor{ transform, texture }, speed{ speed }{}

	void Update(float dt)override;
private:
	float lifetime{ 1.5f};
	float speed = { 600 };
};