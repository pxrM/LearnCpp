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
		// ���ҵ������ƶ��� LRU �б�Ŀ�ͷ���Ա�ʾ��������������ʹ���
		__lru_list.splice(__lru_list.begin(), __lru_list, it);
		return it->second;
	}


	void put(key_type key, value_type value)
	{
		auto res = __hash_map.find(key);
		if (res == __hash_map.end())
		{
			// ����
			if (__capacity == __hash_map.size())
			{
				// ȡ�� LRU �б��ĩβ����ӹ�ϣ��� LRU �б���ɾ�����
				auto back = __lru_list.back();
				__hash_map.erase(back.first);
				__lru_list.pop_back();
			}
			// ���µļ�ֵ�Բ��뵽 LRU �б�Ŀ�ͷ����������������浽��ϣ���С�
			__lru_list.push_front(std::make_pair(key, value));
			__hash_map[key] = __lru_list.begin();
		}
		else
		{
			// ֱ�Ӹ��¶�Ӧ���ֵ���������ƶ��� LRU �б�Ŀ�ͷ���Ա�ʾ��������ʹ���
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
	/// ��ʾ std::unordered_map �е�
	///		�������� key_type��
	///		ֵ������ std::list<std::pair<key_type, value_type>>::iterator ��ʾ std::list ��Ԫ�صĵ�����������ָ���б��е�Ԫ�ء�
	/// std::list<std::pair<key_type, value_type>>����ʾһ���б�����ÿ��Ԫ����һ�� std::pair ���󣬰�����ֵ�ԡ�
	/// 
	/// std::pair �� C++ ��׼���е�ģ���࣬���ڱ�ʾһ��ֵ��������Ҫ���ض��ֵ������ֵ��Ϊһ����Ԫ����������
	/// std::pair �ṩ������������Ա���� first �� second���ֱ����ڴ洢����ֵ��������ֵ�����ǲ�ͬ�����͡�
	/// ���磬���Խ�һ��������һ���ַ��������һ��
	/// </summary>
	std::unordered_map<key_type, typename std::list<std::pair<key_type, value_type>>::iterator> __hash_map;

	std::list<std::pair<key_type, value_type>> __lru_list;

	size_t __capacity = CAPACITY;



};

