#include "lucipch.h"

#include "Luci/Scene/Entity.h"

namespace Luci {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene) {
	}

}
