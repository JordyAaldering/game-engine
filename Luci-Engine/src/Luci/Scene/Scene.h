#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Core/Timestep.h"

#include <entt.hpp>

namespace Luci {

	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "Entity");

		void OnUpdate(Timestep timestep);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}
