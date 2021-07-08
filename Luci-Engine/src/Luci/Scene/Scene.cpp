#include "lucipch.h"

#include "Luci/Scene/Scene.h"
#include "Luci/Scene/Entity.h"
#include "Luci/Scene/Components.h"
#include "Luci/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Luci {

	Scene::Scene() {}

	Scene::~Scene() {}

	Entity Scene::CreateEntity(const std::string& tag) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity) {
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateEditor(Timestep timestep, EditorCamera& camera) {
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);
		for (auto entity : group) {
			auto [sprite, transform] = group.get<SpriteRendererComponent, TransformComponent>(entity);
			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestep timestep) {
		{ LUCI_PROFILE_SCOPE("Scene::OnUpdate Update Scripts");
			m_Registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc) {
				if (!nsc.Instance) {
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity(entity, this);
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(timestep);
			});
		}

		{ LUCI_PROFILE_SCOPE("Scene::OnUpdate Render 2D");
			Camera* mainCamera = nullptr;
			glm::mat4 cameraTransform;

			auto cameraGroup = m_Registry.group<CameraComponent, TransformComponent>();
			for (auto entity : cameraGroup) {
				auto [camera, transform] = cameraGroup.get<CameraComponent, TransformComponent>(entity);
				if (camera.Primary) {
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}

			if (mainCamera) {
				Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

				auto group = m_Registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);
				for (auto entity : group) {
					auto [sprite, transform] = group.get<SpriteRendererComponent, TransformComponent>(entity);
					Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
				}

				Renderer2D::EndScene();
			}
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto cameraView = m_Registry.view<CameraComponent>();
		for (auto entity : cameraView) {
			auto& cameraComponent = cameraView.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio) {
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

	Entity Scene::GetPrimaryCameraEntity() {
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary) {
				return Entity{ entity, this };
			}
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component) {
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component) {}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) {
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportWidth);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component) {}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {}

}
