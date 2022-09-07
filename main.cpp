#include <iostream>
#include <sstream>

class HashTableLast
{
public:
	struct Entry
	{
		std::string Data;
		std::string Status = "never used";
	};
	static const int TableSize = 26;
	HashTableLast() = default;
	void print()
	{
		for (size_t i = 0; i < TableSize; i++)
		{
			if(entries[i].Status == "occupied")
			{
			std::cout << i + 1 << " Data - " << entries[i].Data << " , Status - " << entries[i].Status << std::endl;
			}
		}
	}
	void Add(const std::string& curValue)
	{
		int tempIndex = -1;
		bool exists = find(curValue,tempIndex);
		if (!exists)
		{
			int insertIndex = getbestindex(curValue);
			if (insertIndex != -1)
			{
				entries[insertIndex].Data = curValue;
				entries[insertIndex].Status = "occupied";
			}
		}
	}
	void Delete(const std::string& curValue)
	{
		int index;
		bool exists = find(curValue,index);
		if (exists)
			entries[index].Status = "tombstone";

	}
private:
	bool find(const std::string& curValue,int& outindex)
	{
		int i = 0;
		int index = GetIndex(curValue);

			while (true)
			{
				if (entries[index].Data == curValue)
				{
					outindex = index;
					return true;
				}
				if (entries[index].Status == "never used")
				{
					return false;
				}
				index = (index + 1) % TableSize;
				i++;
				if (i == TableSize)
					return false;
			}
	}
	int getbestindex(const std::string& curValue)
	{
		int i = 0;
		int index = GetIndex(curValue);
		while (true)
		{
			if (entries[index].Status == "never used" || entries[index].Status == "tombstone")
			{
				return index;
			}
			index = (index + 1) % TableSize;
			i++;
			if (i == TableSize)
				return -1;
		}
	}
	int GetIndex(const std::string& curValue)
	{
		int index = curValue.back() - 'a';
		return index;
	}
	Entry entries[TableSize];
};
int main()
{
	HashTableLast hashTable;

	std::string input;
	getline(std::cin, input);
	std::stringstream ss(input);
	while (ss.good())
	{
		std::string token;
		ss >> token;
		std::string valueName = token.substr(1);
		if (token[0] == 'A')
		{
			hashTable.Add(valueName);
			std::cout << "Add - " << valueName << std::endl;
		}
		else if (token[0] == 'D')
		{
			hashTable.Delete(valueName);
			std::cout << "Delete - " << valueName << std::endl;
		}
		else {
			std::cout << "Invalid syntex - " << token << std::endl;
		}
		
	}

	hashTable.print();
	getline(std::cin, input);
	return 0;
}