#pragma once

/// <summary>
/// ���ü�����
/// </summary>
class MRefCounter
{
public:
	MRefCounter()
		:SharedCount(0)
		,WeakCount(0)
	{

	}

public:
	int SharedCount;
	int WeakCount;
};
