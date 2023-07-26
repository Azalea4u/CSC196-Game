#pragma once
#include "FrameWork/Actor.h"
#include "Input/InputSystem.h"

class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, const kiko::Transform& transform, std::shared_ptr < kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;
	void OnCollision(kiko::Actor* other) override;

private:
	float m_speed = 0;

};