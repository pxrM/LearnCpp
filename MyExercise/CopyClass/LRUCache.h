#pragma once

#include <unordered_map>
#include <list>
#include <utility>


template<class key_type, class value_type, size_t CAPACITY = 10>
class LRUCache
{
public:
	LRUCache() {}


public:
	value_type get(key_type key)
	{
		auto res = __hash_map.find(key);
		if (res == __hash_map.end())
			return -1;

		auto it = res->second;
		// 将找到的项移动到 LRU 列表的开头，以表示该项是最近被访问过的
		__lru_list.splice(__lru_list.begin(), __lru_list, it);
		return it->second;
	}


	void put(key_type key, value_type value)
	{
		auto res = __hash_map.find(key);
		if (res == __hash_map.end())
		{
			// 新增
			if (__capacity == __hash_map.size())
			{
				// 取出 LRU 列表的末尾项，并从哈希表和 LRU 列表中删除该项。
				auto back = __lru_list.back();
				__hash_map.erase(back.first);
				__lru_list.pop_back();
			}
			// 将新的键值对插入到 LRU 列表的开头，并将其迭代器保存到哈希表中。
			__lru_list.push_front(std::make_pair(key, value));
			__hash_map[key] = __lru_list.begin();
		}
		else
		{
			// 直接更新对应项的值。将该项移动到 LRU 列表的开头，以表示最近被访问过。
			auto it = res->second;
			it->second = value;
			__lru_list.splice(__lru_list.begin(), __lru_list, it);
		}
	}


	void clear()
	{
		__hash_map.clear();
		__lru_list.clear();
	}

	inline size_t size() { return __hash_map.size(); }

	inline bool empty() { return this->size() == 0; }


private:
	/// <summary>
	/// 表示 std::unordered_map 中的
	///		键类型是 key_type，
	///		值类型是 std::list<std::pair<key_type, value_type>>::iterator 表示 std::list 中元素的迭代器，用于指向列表中的元素。
	/// std::list<std::pair<key_type, value_type>>：表示一个列表，其中每个元素是一个 std::pair 对象，包含键值对。
	/// 
	/// std::pair 是 C++ 标准库中的模板类，用于表示一对值。用于需要返回多个值或将两个值作为一个单元处理的情况。
	/// std::pair 提供了两个公共成员变量 first 和 second，分别用于存储两个值。这两个值可以是不同的类型。
	/// 例如，可以将一个整数和一个字符串组合在一起。
	/// </summary>
	std::unordered_map<key_type, typename std::list<std::pair<key_type, value_type>>::iterator> __hash_map;

	std::list<std::pair<key_type, value_type>> __lru_list;

	size_t __capacity = CAPACITY;



};

