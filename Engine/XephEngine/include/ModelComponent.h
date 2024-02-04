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

		void Deserialize(const yaml_val& data) override;

		Graphics::ModelID GetModelID() const { return m_modelID; }
		const Graphics::Model& GetModel() const
		{
			return *Graphics::ModelManager::GetModel(m_modelID);
		}

	private:
		std::string m_fileName;
		Graphics::ModelID m_modelID;
	};
}

#endif //!__XE_XEPHENGINE_MODELCOMPONENT_H__
