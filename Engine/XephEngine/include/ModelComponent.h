#ifndef __XE_XEPHENGINE_MODELCOMPONENT_H__
#define __XE_XEPHENGINE_MODELCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class ModelComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::Model);

		void Initialize() override;
		void Terminate() override;

		void Serialize(YAML::Node& data) override;
		void Deserialize(const yaml_val& data) override;

		bool CastShadow() const { return m_castShadow; }

		Graphics::ModelID GetModelID() const { return m_modelID; }
		const Graphics::Model& GetModel() const
		{
			return *Graphics::ModelManager::GetModel(m_modelID);
		}

	private:
		std::string m_fileName;
		Graphics::ModelID m_modelID;

		bool m_castShadow = true;
		using Animations = std::vector<std::string>;
		Animations m_animations;
	};
}

#endif //!__XE_XEPHENGINE_MODELCOMPONENT_H__
