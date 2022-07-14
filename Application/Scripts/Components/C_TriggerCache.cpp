#include "C_TriggerCache.h"
namespace C
{
	TriggerCache::TriggerCache(GameObject* gameObject)
		:Component(gameObject){}

	void TriggerCache::Remove(Collider* collider)
	{
		int i = 0;
		while (i < triggers.size())
		{
			if (triggers[i] == collider)
			{
				triggers.erase(triggers.begin() + i);
				return;
			}
			else i++;
		}
		Debug::LogWarn("Trigger not found and could not be removed from TriggerCache");
	}
}
