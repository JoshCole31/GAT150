#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

class EnemyComponent :public jc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<EnemyComponent>(*this); }
	virtual ~EnemyComponent();

	void Create() override;

	virtual void OnCollisionPush(const jc::Event& event);

	// Inherited via Component
	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;
	virtual void Update() override;


public:
	float speed{ 0 };

};