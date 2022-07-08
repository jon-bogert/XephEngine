#include "SaveData.h"


xe::SaveData::SaveData(std::string name)
	: name(name)
{
}

std::string xe::SaveData::GetName() const
{
	return name;
}

void xe::SaveData::ChangeName(const std::string _name)
{
	name = _name;
}

std::string xe::SaveData::GetString(const std::string key) const
{
	return Search(key, dataStr);
}

int xe::SaveData::GetInt(const std::string key) const
{
	return Search(key, dataInt);;
}

float xe::SaveData::GetFloat(const std::string key) const
{
	return Search(key, dataFlt);;
}

char xe::SaveData::GetChar(const std::string key) const
{
	return Search(key, dataChr);
}

char xe::SaveData::GetBool(const std::string key) const
{
	return Search(key, dataBool);
}

xe::Vector2 xe::SaveData::GetVector2(const std::string key) const
{
	return Search(key, dataVec2);
}

xe::Transform xe::SaveData::GetTransform(const std::string key) const
{
	return Search(key, dataTrans);
}

xe::Color xe::SaveData::GetColor(const std::string key) const
{
	return Search(key, dataCol);
}

xe::Colour xe::SaveData::GetColour(const std::string key) const
{
	return GetColor(key);
}

xe::Rectangle xe::SaveData::GetRectangle(const std::string key) const
{
	return Search(key, dataRect);
}

void xe::SaveData::AddString(const std::string key, const std::string data)
{
	dataStr.push_back({ key, data });
}

void xe::SaveData::AddInt(const std::string key, const int data)
{
	dataInt.push_back({ key, data });
}

void xe::SaveData::AddFloat(const std::string key, const float data)
{
	dataFlt.push_back({ key, data });
}

void xe::SaveData::AddChar(const std::string key, const char data)
{
	dataChr.push_back({ key, data });
}

void xe::SaveData::AddBool(const std::string key, const bool data)
{
	dataBool.push_back({ key, data });
}

void xe::SaveData::AddVector2(const std::string key, const Vector2 data)
{
	dataVec2.push_back({ key, data });
}

void xe::SaveData::AddTransform(const std::string key, const Transform data)
{
	dataTrans.push_back({ key, data });
}

void xe::SaveData::AddColor(const std::string key, const Color data)
{
	dataCol.push_back({ key, data });
}

void xe::SaveData::AddColour(const std::string key, const Colour data)
{ 
	AddColor(key, data);
}

void xe::SaveData::AddRectangle(const std::string key, const Rectangle data)
{
	dataRect.push_back({ key, data });
}

bool xe::SaveData::RemoveString(const std::string key)
{
	int index = SearchIndex(key, dataStr);
	if (index >= 0)
	{
		dataStr.erase(dataStr.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveInt(const std::string key)
{
	int index = SearchIndex(key, dataInt);
	if (index >= 0)
	{
		dataInt.erase(dataInt.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveFloat(const std::string key)
{
	int index = SearchIndex(key, dataFlt);
	if (index >= 0)
	{
		dataFlt.erase(dataFlt.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveChar(const std::string key)
{
	int index = SearchIndex(key, dataChr);
	if (index >= 0)
	{
		dataChr.erase(dataChr.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveBool(const std::string key)
{
	int index = SearchIndex(key, dataBool);
	if (index >= 0)
	{
		dataBool.erase(dataBool.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveVector2(const std::string key)
{
	int index = SearchIndex(key, dataVec2);
	if (index >= 0)
	{
		dataVec2.erase(dataVec2.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveTransform(const std::string key)
{
	int index = SearchIndex(key, dataTrans);
	if (index >= 0)
	{
		dataTrans.erase(dataTrans.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveColor(const std::string key)
{
	int index = SearchIndex(key, dataCol);
	if (index >= 0)
	{
		dataCol.erase(dataCol.begin() + index);
		return true;
	}
	return false;
}

bool xe::SaveData::RemoveColour(const std::string key)
{
	return RemoveColor(key);
}

bool xe::SaveData::RemoveRectangle(const std::string key)
{
	int index = SearchIndex(key, dataRect);
	if (index >= 0)
	{
		dataRect.erase(dataRect.begin() + index);
		return true;
	}
	return false;
}

std::vector<std::pair<std::string, std::string>> xe::SaveData::Compile() const
{
	std::vector<std::pair<std::string, std::string>> data;

	for (std::pair<std::string, std::string> pair : dataStr)
	{
		std::string key = "STR_";
		key.append(pair.first);
		data.push_back({ key, pair.second });
	}
	for (std::pair<std::string, int> pair : dataInt)
	{
		std::string key = "INT_";
		key.append(pair.first);
		data.push_back({ key, std::to_string(pair.second)});
	}
	for (std::pair<std::string, float> pair : dataFlt)
	{
		std::string key = "FLT_";
		key.append(pair.first);
		data.push_back({ key, std::to_string(pair.second) });
	}
	for (std::pair<std::string, char> pair : dataChr)
	{
		std::string key = "CHR_";
		key.append(pair.first);
		data.push_back({ key, std::to_string(pair.second) });
	}
	for (std::pair<std::string, bool> pair : dataBool)
	{
		std::string key = "BOOL_";
		key.append(pair.first);
		if (pair.second)
			data.push_back({ key, "true" });
		else
			data.push_back({ key, "false" });
	}
	for (std::pair<std::string, Vector2> pair : dataVec2)
	{
		std::string key = "VEC2_";
		key.append(pair.first);
		std::string comp = std::to_string(pair.second.x);
		comp.push_back('/');
		comp.append(std::to_string(pair.second.y));
		data.push_back({ key, comp });
	}
	for (std::pair<std::string, Transform> pair : dataTrans)
	{
		std::string key = "TRAN_";
		key.append(pair.first);
		std::string comp = std::to_string(pair.second.position.x);
		comp.push_back('/');
		comp.append(std::to_string(pair.second.position.y));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.rotation.GetRotation()));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.scale.x));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.scale.y));
		data.push_back({ key, comp });
	}
	for (std::pair<std::string, Color> pair : dataCol)
	{
		std::string key = "COL_";
		key.append(pair.first);
		std::string comp = std::to_string(pair.second.r);
		comp.push_back('/');
		comp.append(std::to_string(pair.second.g));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.b));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.a));
		data.push_back({ key, comp });
	}
	for (std::pair<std::string, Rectangle> pair : dataRect)
	{
		std::string key = "RECT_";
		key.append(pair.first);
		std::string comp = std::to_string(pair.second.x);
		comp.push_back('/');
		comp.append(std::to_string(pair.second.y));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.width));
		comp.push_back('/');
		comp.append(std::to_string(pair.second.height));
		data.push_back({ key, comp });
	}

	return data;
}
