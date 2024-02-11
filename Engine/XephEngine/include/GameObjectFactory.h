#ifndef __XE_XEPHENGINE_GAMEOBJECTFACTORY_H__
#define __XE_XEPHENGINE_GAMEOBJECTFACTORY_H__

namespace xe
{
	class GameObject;

	using CustomMake = std::function<bool(const std::string&, const yaml_val&, GameObject&)>;

	namespace GameObjectFactory
	{
		void SetCustomMake(CustomMake customMake);
		void Make(const std::string& filePath, GameObject& gameObject);
	}
}

#endif //!__XE_XEPHENGINE_GAMEOBJECTFACTORY_H__