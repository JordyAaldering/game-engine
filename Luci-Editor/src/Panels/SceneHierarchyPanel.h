#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Scene/Scene.h"
#include "Luci/Scene/Entity.h"

namespace Luci {

	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}
