#pragma once

#include "Luci/Core/Timestep.h"

#include <iostream>

namespace Luci {

	class CameraController : public ScriptableEntity {
	public:
		void OnUpdate(Timestep timestep) {
			auto& transform = GetComponent<TransformComponent>().Transform;
			static float speed = 5.0f;

			if (Input::IsKeyPressed(KeyCode::A)) {
				transform[3][0] -= speed * timestep;
			} else if (Input::IsKeyPressed(KeyCode::D)) {
				transform[3][0] += speed * timestep;
			}

			if (Input::IsKeyPressed(KeyCode::W)) {
				transform[3][1] += speed * timestep;
			} else if (Input::IsKeyPressed(KeyCode::S)) {
				transform[3][1] -= speed * timestep;
			}
		}
	};

}
