#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Core/Timestep.h"
#include "Luci/Scene/Entity.h"

namespace Luci {

	class ScriptableEntity {
	public:
		virtual ~ScriptableEntity() = default;

		template<typename T>
		T& GetComponent() { return m_Entity.GetComponent<T>(); }

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep timestep) {}

	private:
		Entity m_Entity;

		friend class Scene;
	};

}
