#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Scene/Entity.h"

namespace Luci {

	class ScriptableEntity {
	public:
		template<typename T>
		T& GetComponent() { return m_Entity.GetComponent<T>(); }

	private:
		Entity m_Entity;

		friend class Scene;
	};

}
