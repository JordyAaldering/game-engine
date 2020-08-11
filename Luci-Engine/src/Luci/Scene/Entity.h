#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Scene/Scene.h"

#include <entt.hpp>

namespace Luci {

	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args);

		template<typename T>
		T& GetComponent();

		template<typename T>
		bool HasComponent();

		template<typename T>
		T& RemoveComponent();

		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};

}
