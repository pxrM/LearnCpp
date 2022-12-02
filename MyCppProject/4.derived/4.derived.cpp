/*
	派生、继承、多继承、菱形继承问题、虚继承
*/

#include <iostream>
#include <stdio.h>

class Works {
public:
	void work()
	{
		/*..........*/
	}

private:
	void MyWork() {

	}
protected:
	void ChildWork() {

	}
};

/*
	public继承：	子类继承后：
		public		public
		private		private
		protected	protected
*/
class ComponentWorks : public Works {
public:
	void Func() {
		ChildWork();
	}
};

/*
	private继承：	 子类继承后：
		public		 private
		private		 private
		protected	 private
*/
class SpliceWorks : private Works {
public:
	void Only() {
		work();
	}
};

/*
	protected继承：	 子类继承后：
		public		 protected
		private		 private
		protected	 protected
*/
class Test :protected Works {
public:
	void Func2() {
		work();
	}
};


/////////////////////////////////////////////////////////
//多继承，好处有：可以将代码进行分块、便于维护
class Object {

};

class Actor :public Object {
public:
	void Start() {

	}
	void End() {

	}
};

class Physics {
public:
	void Simulate() {

	}
};

class Attach {
public:
	void AttachTarget() {

	}
};

class Character :public Actor, public Physics, public Attach {
public:

};

bool IsSimulate(Physics* p)
{
	if (p)
	{
		p->Simulate();
	}
	return true;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//菱形继承问题
class ObjectTwo {
public:
	void Destroy() {

	}
};

class ActorTwo :public ObjectTwo {
public:
	void Start() {

	}
	void End() {

	}
};

class ActorThree :public ObjectTwo {
public:

};

class PhysicsTwo {
public:
	void Simulate() {

	}
};

class CharacteTwo :public ActorTwo, public ActorThree, public PhysicsTwo {
public:

};
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//虚继承，可以解决菱形继承问题，将不明确的类合并为一个
class A1 {
public:
	A1() {
		printf("Hello -A1 \n");
	}

	void Hello()
	{
		printf("Hello()   \n");
	}
};

class B2 :virtual public A1 {
public:
	B2() :A1() {

	}
};

class C3 :virtual public A1 {
public:
	C3() :A1() {

	}
};

class D4 :public B2, public C3 {
public:
	D4() :B2(), C3() {

	}
	~D4()
	{

	}
};
/////////////////////////////////////////////////////////


void main()
{
	ComponentWorks component;
	component.work();
	component.Func();

	SpliceWorks splice;
	splice.Only();

	Test test;
	test.Func2();

	/////////////////////////////////////////////////////////

	Character character;
	character.Start();
	character.Simulate();
	character.End();
	Actor* actorPtr = &character;
	Physics* physicsPtr = &character;
	Attach* attachPtr = &character;
	IsSimulate(&character);

	CharacteTwo chTwo;
	//chTwo.Destroy(); //ERR：找不到明确的目标，因为继承的ActorTwo、ActorThree都继承自ObjectTwo，所以它们都有这个函数

	/////////////////////////////////////////////////////////

	D4 d;
	d.Hello();
}