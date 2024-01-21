#ifndef __XE_XEPHENGINE_GAMEOBJECTFACTORY_H__
#define __XE_XEPHENGINE_GAMEOBJECTFACTORY_H__

namespace xe
{
	class GameObject;
	namespace GameObjectFactory
	{
		void Make(const std::string& filePath, GameObject& gameObject);
	}
}

#endif //!__XE_XEPHENGINE_GAMEOBJECTFACTORY_H__