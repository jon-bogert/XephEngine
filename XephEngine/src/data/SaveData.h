#pragma once
#include "../Libraries.h"
#include "Structs.h"

namespace xe
{
	class SaveData
	{
	protected:
		std::string name;

		//first => key, second => data
		std::vector<std::pair<std::string, std::string>>* dataStr = nullptr;
		std::vector<std::pair<std::string, int>>* dataInt = nullptr;
		std::vector<std::pair<std::string, float>>* dataFlt = nullptr;
		std::vector<std::pair<std::string, char>>* dataChr = nullptr;
		std::vector<std::pair<std::string, bool>>* dataBool = nullptr;
		std::vector<std::pair<std::string, Vector2>>* dataVec2 = nullptr;
		std::vector<std::pair<std::string, Transform>>* dataTrans = nullptr;
		std::vector<std::pair<std::string, Color>>* dataCol = nullptr;
		std::vector<std::pair<std::string, Rectangle>>* dataRect = nullptr;

		template <class T>
		T Search(std::string key, std::vector<std::pair<std::string, T>>* data) const;
		template <class T>
		int SearchIndex(std::string key, std::vector<std::pair<std::string, T>>* data) const;
	public:
		SaveData(std::string name);
		~SaveData();

		std::string GetName() const;
		void ChangeName(const std::string _name);

		std::string GetString(const std::string key) const;
		int GetInt(const std::string key) const;
		float GetFloat(const std::string key) const;
		char GetChar(const std::string key) const;
		char GetBool(const std::string key) const;
		Vector2 GetVector2(const std::string key) const;
		Transform GetTransform(const std::string key) const;
		Color GetColor(const std::string key) const;
		Colour GetColour(const std::string key) const;
		Rectangle GetRectangle(const std::string key) const;

		void AddString(const std::string key, const std::string data);
		void AddInt(const std::string key, const int data);
		void AddFloat(const std::string key, const float data);
		void AddChar(const std::string key, const char data);
		void AddBool(const std::string key, const bool data);
		void AddVector2(const std::string key, const Vector2 data);
		void AddTransform(const std::string key, const Transform data);
		void AddColor(const std::string key, const Color data);
		void AddColour(const std::string key, const Colour data);
		void AddRectangle(const std::string key, const Rectangle data);

		bool RemoveString(const std::string key);
		bool RemoveInt(const std::string key);
		bool RemoveFloat(const std::string key);
		bool RemoveChar(const std::string key);
		bool RemoveBool(const std::string key);
		bool RemoveVector2(const std::string key);
		bool RemoveTransform(const std::string key);
		bool RemoveColor(const std::string key);
		bool RemoveColour(const std::string key);
		bool RemoveRectangle(const std::string key);

		std::vector<std::pair<std::string, std::string>> Compile() const;
	};

	template<class T>
	inline T SaveData::Search(std::string key, std::vector<std::pair<std::string, T>>* data) const
	{
		for (std::pair<std::string, T> pair : *data)
		{
			if (pair.first == key) return pair.second;
		}

		std::cout << "[ERROR] Could not find data with with key: " << key << std::endl;
		return T();
	}
	template<class T>
	inline int SaveData::SearchIndex(std::string key, std::vector<std::pair<std::string, T>>* data) const
	{
		int index = 0;
		for (std::pair<std::string, T> pair : *data)
		{
			if (pair.first == key) return index;
			index++;
		}

		std::cout << "[ERROR] Could not find data with with key: " << key << std::endl;
		return -1;
	}
}

