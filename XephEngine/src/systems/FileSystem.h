#pragma once

#include "../Libraries.h"
#include "../../lib/XephEngine/Engine.h"

namespace xe
{
	namespace FileSystem
	{
		SaveData Load(std::string name);
		SaveData LoadEncrypted(std::string name);

		bool Save(SaveData saveData);
		bool SaveEncrypted(SaveData saveData);
	}
}

