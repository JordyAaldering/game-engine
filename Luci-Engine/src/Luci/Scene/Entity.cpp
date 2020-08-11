#include "lucipch.h"

#include "Luci/Scene/Entity.h"

namespace Luci {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene) {
	}

	template<typename T, typename... Args>
	T& Entity::AddComponent(Args&&... args) {
		LUCI_CORE_ASSERT(!HasComponent<T>(), "Entity already has component.");
		return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& Entity::GetComponent() {
		LUCI_CORE_ASSERT(HasComponent<T>(), "Entity does not have component.");
		return m_Scene->m_Registry.get<T>(m_EntityHandle);
	}

	template<typename T>
	bool Entity::HasComponent() {
		return m_Scene->m_Registry.has<T>(m_EntityHandle);
	}

	template<typename T>
	T& Entity::RemoveComponent() {
		LUCI_CORE_ASSERT(HasComponent<T>(), "Entity does not have component.");
		m_Scene->m_Registry.remove<T>(m_EntityHandle);
	}
}
