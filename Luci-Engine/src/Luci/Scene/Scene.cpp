#include "lucipch.h"

#include "Luci/Scene/Scene.h"
#include "Luci/Scene/Entity.h"
#include "Luci/Scene/Components.h"
#include "Luci/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Luci {

	Scene::Scene() {
	}

	Scene::~Scene() {
	}

	Entity Scene::CreateEntity(const std::string& tag) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::OnUpdate(Timestep timestep) {
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		auto cameraGroup = m_Registry.group<CameraComponent, TransformComponent>();
		for (auto entity : cameraGroup) {
			auto& [camera, transform] = cameraGroup.get<CameraComponent, TransformComponent>(entity);

			if (camera.Primary) {
				mainCamera = &camera.Camera;
				cameraTransform = &transform.Transform;
				break;
			}
		}

		if (mainCamera) {
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<SpriteRendererComponent, TransformComponent>();
			for (auto entity : group) {
				auto& [sprite, transform] = group.get<SpriteRendererComponent, TransformComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

}
