#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "FrameWork/Scene.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() * kiko::HalfPi;
	}

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * dt;
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());


	// sets the enemy to fire at a certain rate
	if (m_fireRate)
	{
		m_fireRate -= dt;
		if (m_fireRate <= 0.0f)
		{
			// create weapon
			kiko::Transform transform{ m_transform.position, m_transform.rotation, 1 };
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
			m_scene->Add(std::move(weapon));

			m_fireRate = m_fireTime;
		}
	}
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "Player")
	{
		m_game->AddPoints(100);
		m_destoryed = true;

	}
}
