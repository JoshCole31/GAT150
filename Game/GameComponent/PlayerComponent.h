#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

class PlayerComponent :public jc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); }
	virtual ~PlayerComponent();

	void Create() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(const jc::Event& event);
	virtual void OnCollisionExit(const jc::Event& event);

	// Inherited via Component
	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;


public:
	float speed{ 0 };
	float jump{ 0 };


private:
	std::list<jc::Actor*> contacts;
};