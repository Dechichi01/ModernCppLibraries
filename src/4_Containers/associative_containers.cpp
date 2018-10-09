/*
	. Set and Map are ordered by default (using operator<)
		. Implement binary search algoritms (lower_bound, upper_bound, range)
	. unordered_set and unordered_map are essentially hash sets (faster lookup)
	. All are no repeat structures
*/
#include "../Precompiled.h"

#include <set>
#include <map>
#include <string>

namespace std
{
	template<typename T1, typename T2>
	T1 begin(const pair<T1, T2>& range)
	{
		return range.first;
	}

	template<typename T1, typename T2>
	T2 end(const pair<T1, T2>& range)
	{
		return range.second;
	}
	
}
int main()
{
	auto set = std::set<int, std::less<int>>{ 5,4,3,6,7,1,-2 };//sorted by default

	for (auto s : set) 
	{
		LOG(s);
	}

	auto resultPair = set.emplace(-7);
	LOG(*resultPair.first);
	LOG(resultPair.second);

	auto range = set.equal_range(6);
	auto lower_bound = set.lower_bound(6);
	//pair containing the start of the lower bound and end of start bound

	ASSERT(range.first == lower_bound);

	LOG("MAP ------------");

	//----- MAP: Balanced binary tree. Container of pairs

	auto map = std::map<std::string, int>
	{
		{ "1", 1},
		{ "2", 2},
		{ "4", 4},
		{ "1", 1},
		{ "1", 1},
	};

	ASSERT(map.size() == 3);

	auto newValue = map["lollysson"];//Creates the value if not exists
	ASSERT(newValue == 0);

	auto nonExistentValue = map.find("noooo");
	ASSERT(nonExistentValue == map.end());

	for (auto pair : map)
	{
		LOG(pair.first);
		LOG(pair.second);
	}

	auto result = map.emplace("newValue", 98);
	ASSERT(result.first->second == 98);
	ASSERT(result.second);

	map.erase("lollysson");

	//Extension to enumrate on ranges (must add begin and end function)
	LOG("\n\n\nEQUAL RANGE");
	for (auto& pair : map.equal_range("4"))
	{
		LOG(pair.first);
	}


	/*
		Multimap: elements are ordered, elements with the same key keeps insertion order
	*/

	
}