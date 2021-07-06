#pragma once

#include "Luci/Scene/Scene.h"

namespace Luci {

	class SceneSerializer {
	public:
		SceneSerializer(const Ref<Scene>& scene);

		// serialize to human-readable yaml
		void Serialize(const std::string& filepath);
		// serialize to binary
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);

	private:
		Ref<Scene> m_Scene;
	};

}
