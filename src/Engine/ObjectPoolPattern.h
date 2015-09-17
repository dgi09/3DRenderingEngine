#pragma once 
#include "Common.h"
#include <string>
#include <unordered_map>

template <class Val>
class EXPORT Object_Ref
{
public:
	unsigned int ref;
	Val res;
};

template <class Key,class Val>
class EXPORT ObjectPoolPattern
{
	std::unordered_map<Key,Object_Ref<Val>> map;
	std::vector<Object_Ref<Val>> memory;
public:

	void AddObject(Key id,Val obj);
	bool ObjectExist(Key id);
	Val GetResource(Key id);

	void DeleteAllObjects();
	void DeleteObject(Key id);

	void RefObject(Key id);
	void DerefObject(Key id);

protected:
	virtual void DeleteVal(Val value) = 0;
};

template <class Key,class Val>
void ObjectPoolPattern<Key,Val>::DerefObject(Key id)
{
	if(ObjectExist(id))
	{
		map[id].ref--;
		if(map[id].ref == 0)
			DeleteObject(id);
	}
}

template <class Key,class Val>
void ObjectPoolPattern<Key,Val>::RefObject(Key id)
{
	if(ObjectExist(id))
	{
		map[id].ref++;
	}
}

template <class Key,class Val>
void ObjectPoolPattern<Key,Val>::DeleteObject(Key id)
{
	if(ObjectExist(id))
	{
		Val & res = map[id].res;
		for(std::vector<Object_Ref<Val>>::iterator it = memory.begin();it != memory.end();++it)
		{
			if((*it).res == res)
			{
				DeleteVal((*it).res);
				it = memory.erase(it);
				break;
			}
		}

		map.erase(id);
	}
}

template <class Key,class Val>
void ObjectPoolPattern<Key,Val>::DeleteAllObjects()
{
	for(std::vector<Object_Ref<Val>>::iterator it = memory.begin();it != memory.end();++it)
	{	
			DeleteVal((*it).res);		
	}

	memory.clear();
	map.clear();
}

template <class Key,class Val>
Val ObjectPoolPattern<Key,Val>::GetResource(Key id)
{
	return map[id].res;
}

template <class Key,class Val>
bool ObjectPoolPattern<Key,Val>::ObjectExist(Key id)
{
	if(map.count(id) > 0)
	{
			return true;
	}

	else return false;
}

template <class Key,class Val>
void ObjectPoolPattern<Key,Val>::AddObject(Key id,Val obj)
{
	if(ObjectExist(id) == false)
	{
		Object_Ref<Val> or;
		or.ref = 0;
		or.res = obj;
		map[id] = or;
		memory.push_back(or);
	}
}
