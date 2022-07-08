#include "FileSystem.h"
#include <fstream>
#include <string>

namespace xe
{
	std::string FilePath(std::string name)
	{
		std::string filePath = "dat/";
		filePath.append(name);
		filePath.append(".dat");
		return filePath;
	}

	SaveData LoadCore(std::string filePath, std::string name)
	{
		SaveData data(name);
		std::ifstream file(filePath);

		if (!file.is_open())
		{
			std::cout << "[WARN] File at " << filePath << " not found. Creating new SaveData with name: " << name << std::endl;
			return data;
		}

		std::string line, type, key, info0, info1, info2, info3, info4;
		while (std::getline(file, line))
		{
			int stage{};
			for (char c : line)
			{
				if (c == '_' || c == '=' || c == '/')
					stage++;

				else if (stage == 0)
					type.push_back(c);
				else if (stage == 1)
					key.push_back(c);
				else if (stage == 2)
					info0.push_back(c);
				else if (stage == 3)
					info1.push_back(c);
				else if (stage == 4)
					info2.push_back(c);
				else if (stage == 5)
					info3.push_back(c);
				else if (stage == 6)
					info4.push_back(c);
			}
			std::cout << type << " " << key << " " << info0 << std::endl;;

			if (type == "STR")
			{
				data.AddString(key, info0);
			}
			else if (type == "INT")
			{
				data.AddInt(key, atoi(info0.c_str()));
			}
			else if (type == "FLT")
			{
				data.AddFloat(key, atof(info0.c_str()));
			}
			else if (type == "FLT")
			{
				data.AddFloat(key, atof(info0.c_str()));
			}
			else if (type == "CHR")
			{
				if (info0.size() != 0)
					data.AddFloat(key, info0[0]);
			}
			else if (type == "BOOL")
			{
				data.AddBool(key, (info0 == "true" || info0 == "TRUE"
					|| info0 == "True" || info0 == "T" || info0 == "t" || info0 == "1"));
			}
			else if (type == "VEC2")
			{
				data.AddVector2(key, Vector2((float)atof(info0.c_str()), atof(info1.c_str())));
			}
			else if (type == "TRAN")
			{
				data.AddTransform(key,
					{
						Vector2((float)atof(info0.c_str()), atof(info1.c_str())),
						Rotator(atof(info2.c_str())),
						Vector2((float)atof(info3.c_str()), atof(info4.c_str()))
					});
			}
			else if (type == "COL")
			{
				data.AddColor(key, Color(atoi(info0.c_str()), atoi(info1.c_str()), atoi(info2.c_str()), atoi(info3.c_str())));
			}
			else if (type == "RECT")
			{
				data.AddRectangle(key, Rectangle(atof(info0.c_str()), atof(info1.c_str()), atof(info2.c_str()), atof(info3.c_str())));
			}
			type.clear(); key.clear(); info0.clear(); info1.clear(); info2.clear(); info3.clear(); info4.clear();
		}
		file.close();
	}
}

xe::SaveData xe::FileSystem::Load(std::string name)
{
	std::string filePath = FilePath(name);
	return LoadCore(filePath, name);
}

xe::SaveData xe::FileSystem::LoadProjSettings()
{
	return LoadCore("ProjSettings.dat", "ProjSettings");
}

xe::SaveData xe::FileSystem::LoadEncrypted(std::string name)
{
	std::cout << "[ERROR] Encryped saving/loading not yet supported." << std::endl;
	return SaveData("null");
}

bool xe::FileSystem::Save(SaveData saveData)
{
	std::string filePath = FilePath(saveData.GetName());

	//Check if file will be created
	std::ifstream ifile(filePath);
	bool wasCreated = (!ifile.is_open());
	ifile.close();

	//Save
	std::ofstream file(filePath);
	std::vector<std::pair<std::string, std::string>> data = saveData.Compile();
	for (std::pair<std::string, std::string> pair : data)
	{
		file << pair.first << "=" << pair.second << std::endl;
	}
	file.close();

	return wasCreated;
}

bool xe::FileSystem::SaveEncrypted(SaveData saveData)
{
	std::cout << "[ERROR] Encryped saving/loading not yet supported." << std::endl;
	return false;
}
