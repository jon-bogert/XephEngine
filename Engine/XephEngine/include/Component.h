#ifndef __XE_XEPHENGINE_COMPONENT_H__
#define __XE_XEPHENGINE_COMPONENT_H__

#include "TypeIDs.h"

namespace xe
{
	class GameObject;
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component&) = delete;
		Component(const Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(const Component&&) = delete;

		virtual void Initialize() {}
		virtual void Terminate(){}
		virtual void Update(const float deltaTime) {}
		virtual void DebugUI() {}
		virtual void EditorUI() {}
		virtual uint32_t GetTypeID() const = 0;

		GameObject& GetGameObject() { return *m_gameObject; }
		const GameObject& GetGameObject() const { return *m_gameObject; }

		//Serialization
		virtual void Serialize(YAML::Node& components) {};
		virtual void Deserialize(const yaml_val& data) {};

	private:
		friend class GameObject;
		GameObject* m_gameObject = nullptr;
	};
}

#endif //!__XE_XEPHENGINE_COMPONENT_H__