#include "FrameWork/Actor.h"

namespace kiko {
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			if (m_lifespan <= 0.0f)
				m_destoryed = true;
		}
	}

	void Actor::Draw(kiko::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
