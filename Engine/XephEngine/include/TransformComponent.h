#ifndef __XE_XEPHENGINE_TRANSFORMCOMPONENT_H__
#define __XE_XEPHENGINE_TRANSFORMCOMPONENT_H__
#include "Component.h"
namespace xe
{
	class TransformComponent final : public Component, public Graphics::Transform
	{
	public:
		SET_TYPE_ID(ComponentID::Transform)
		void DebugUI() override;

		void Deserialize(const yaml_val& data);
	};
}

#endif //!__XE_XEPHENGINE_TRANSFORMCOMPONENT_H__