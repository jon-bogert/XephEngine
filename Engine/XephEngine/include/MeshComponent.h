#ifndef __XE_XEPHENGINE_MESHCOMPONENT_H__
#define __XE_XEPHENGINE_MESHCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class MeshComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::Mesh);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const yaml_val& data) override;

		const Graphics::Model& GetModel() const { return m_model; }

	private:
		Graphics::Model m_model;
	};
}
#endif //!__XE_XEPHENGINE_MESHCOMPONENT_H__
