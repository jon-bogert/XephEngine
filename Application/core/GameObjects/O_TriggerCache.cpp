#include "O_TriggerCache.h"

namespace O
{
	TriggerCache::TriggerCache()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void TriggerCache::LoadComponents()
	{
		AddComponent(new C::TriggerCache(this));
	}
}
