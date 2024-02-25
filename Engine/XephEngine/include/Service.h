#ifndef __XE_XEPHENGINE_SERVICE_H__
#define __XE_XEPHENGINE_SERVICE_H__

#include "TypeIDs.h"

namespace xe
{
	class World;
	class Service
	{
	public:
		Service() = default;
		virtual ~Service() = default;

		Service(const Service&) = delete;
		Service(const Service&&) = delete;
		Service& operator=(const Service&) = delete;
		Service& operator=(const Service&&) = delete;

		virtual uint32_t GetTypeID() const = 0;

		virtual void Initialize() {}
		virtual void Terminate() {}
		virtual void Update(const float deltaTime) {}
		virtual void Draw() {}
		virtual void DebugUI() {}
		virtual void EditorUI() {}

		World& GetWorld() { return *m_world; }
		const World& GetWorld() const { return *m_world; }

		virtual void Serialize(YAML::Node& components) {};
		virtual void Deserialize(const yaml_val& data) {};

	private:
		friend class World;
		World* m_world = nullptr;
	};
}

#endif //!__XE_XEPHENGINE_SERVICE_H__