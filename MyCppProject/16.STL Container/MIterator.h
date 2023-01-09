/*
	迭代器

*/


#pragma once


template<class ContainerType, typename ElementType>
class IndexedContainerIterator
{
public:
	typedef IndexedContainerIterator<ContainerType, ElementType> MIteraotr;

	//构造
	IndexedContainerIterator(ContainerType &InContainer, int InIndex = 0)
		:Container(InContainer)
		, Index(InIndex)
	{
	}
	//深拷贝构造  （参数需要加const）
	IndexedContainerIterator(const MIteraotr &InIterator)
		:Container(InIterator.Container)
		, Index(InIterator.Index)
	{
	}

	//for(; It != AA.End(); ;){}
	bool operator != (const MIteraotr &InIterator)
	{
		return Container[Index] != InIterator.Container[InIterator.Index];
	}

	MIteraotr &operator++(int)
	{
		++Index;
		return *this;
	}

	MIteraotr &operator--(int)
	{
		--Index;
		return *this;
	}

	MIteraotr &operator=(const MIteraotr &InIterator)
	{
		Container = InIterator.Container;
		Index = InIterator.Index;
		return *this;
	}

	ElementType &operator*()
	{
		return *Container[Index];
	}



protected:
	ContainerType &Container;
	int Index;	//容器的偏移

};




template<typename ElementType>
class TArray
{
public:
	typedef IndexedContainerIterator<TArray<ElementType>, ElementType> MIteraotr;


	TArray()
		:Data(nullptr)
		,Size(0)
		,Allocation(10)
	{
		Data = (ElementType **)malloc(sizeof(int) * Allocation); //分配下标内存
		memset(Data, 0, sizeof(ElementType));
		//分配下标的指针内存
		for (int i = 0; i < Allocation; i++)
		{
			Data[i] = (ElementType *)malloc(sizeof(ElementType));
			memset(Data[i], 0, sizeof(ElementType));
		}
	}


	MIteraotr Begin()
	{
		return MIteraotr(*this, 0);
	}


	MIteraotr End()
	{
		return MIteraotr(*this, Size);
	}


	int Num()
	{
		return Size;
	}


	void Add(ElementType &&InType)
	{
		Add(InType);
	}
	

	void Add(ElementType &InType)
	{
		if (Size >= Allocation)
		{
			//分配的内存空间已经不够了，需要扩容
			int lastAllocation = Allocation;	//记录上次的
			Allocation *= 2;
			Data = (ElementType **)realloc(Data, sizeof(int) * Allocation);  //在原有的基础上进行扩展
			for (int i = lastAllocation; i < Allocation; i++)
			{
				Data[i] = (ElementType *)malloc(sizeof(ElementType));
				memset(Data[i], 0, sizeof(ElementType));
			}
		}

		//拷贝
		memcpy(Data[Size], &InType, sizeof(ElementType));
		Size++;
	}


	void RemoveAt(int Index)
	{
		for (int i = Index + 1; i <= Size; i++)
		{
			memcpy(Data[i - 1], Data[i], sizeof(ElementType));	//将Data[Index]移动到最后
		}

		memset(Data[Size], 0, sizeof(ElementType));
		Size--;
	}


	ElementType *operator[](int Index)
	{
		return Data[Index];
	}


	~TArray()
	{
		for (int i = 0; i < Allocation; i++)
		{
			free(Data[i]);
		}

		free(Data);
	}

protected:
	ElementType **Data; //元素  二维数组
	int Size; //实际元素大小
	int Allocation;	//预分配大小
};

