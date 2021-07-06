#pragma once

#include "Luci/Core/Timestep.h"

#include <iostream>

namespace Luci {

	class CameraController : public ScriptableEntity {
	public:
		virtual void OnUpdate(Timestep timestep) {
			auto& translation = GetComponent<TransformComponent>().Translation;
			static float speed = 5.0f;

			if (Input::IsKeyPressed(KeyCode::A)) {
				translation.x -= speed * timestep;
			} else if (Input::IsKeyPressed(KeyCode::D)) {
				translation.x += speed * timestep;
			}

			if (Input::IsKeyPressed(KeyCode::W)) {
				translation.y += speed * timestep;
			} else if (Input::IsKeyPressed(KeyCode::S)) {
				translation.y -= speed * timestep;
			}
		}
	};

}
