/*
	������

*/


#pragma once


template<class ContainerType, typename ElementType>
class IndexedContainerIterator
{
public:
	typedef IndexedContainerIterator<ContainerType, ElementType> MIteraotr;

	//����
	IndexedContainerIterator(ContainerType &InContainer, int InIndex = 0)
		:Container(InContainer)
		, Index(InIndex)
	{
	}
	//�������  ��������Ҫ��const��
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
	int Index;	//������ƫ��

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
		Data = (ElementType **)malloc(sizeof(int) * Allocation); //�����±��ڴ�
		memset(Data, 0, sizeof(ElementType));
		//�����±��ָ���ڴ�
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
			//������ڴ�ռ��Ѿ������ˣ���Ҫ����
			int lastAllocation = Allocation;	//��¼�ϴε�
			Allocation *= 2;
			Data = (ElementType **)realloc(Data, sizeof(int) * Allocation);  //��ԭ�еĻ����Ͻ�����չ
			for (int i = lastAllocation; i < Allocation; i++)
			{
				Data[i] = (ElementType *)malloc(sizeof(ElementType));
				memset(Data[i], 0, sizeof(ElementType));
			}
		}

		//����
		memcpy(Data[Size], &InType, sizeof(ElementType));
		Size++;
	}


	void RemoveAt(int Index)
	{
		for (int i = Index + 1; i <= Size; i++)
		{
			memcpy(Data[i - 1], Data[i], sizeof(ElementType));	//��Data[Index]�ƶ������
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
	ElementType **Data; //Ԫ��  ��ά����
	int Size; //ʵ��Ԫ�ش�С
	int Allocation;	//Ԥ�����С
};

