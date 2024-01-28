#ifndef __XE_XEPHENGINE_GAMEOBJECTHANDLE_H__
#define __XE_XEPHENGINE_GAMEOBJECTHANDLE_H__

namespace xe
{
	class GameObjectHandle
	{
	public:
		GameObjectHandle() = default;

	private:
		friend class World;

		int m_index = -1;
		int m_generation = -1;
	};
}

#endif //!__XE_XEPHENGINE_GAMEOBJECTHANDLE_H__
