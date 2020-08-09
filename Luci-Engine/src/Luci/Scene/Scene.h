#pragma once

#include "Luci/Core/Timestep.h"

#include <entt.hpp>

namespace Luci {

	class Scene {
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		void OnUpdate(Timestep timestep);

		entt::registry& Get() { return m_Registry; }

	private:
		entt::registry m_Registry;
	};

}
