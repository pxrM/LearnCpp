#pragma once

/// <summary>
/// 引用计数类
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
