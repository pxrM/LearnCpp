/*
	�������̳С���̳С����μ̳����⡢��̳�
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
	public�̳У�	����̳к�
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
	private�̳У�	 ����̳к�
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
	protected�̳У�	 ����̳к�
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
//��̳У��ô��У����Խ�������зֿ顢����ά��
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
//���μ̳�����
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
//��̳У����Խ�����μ̳����⣬������ȷ����ϲ�Ϊһ��
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
	//chTwo.Destroy(); //ERR���Ҳ�����ȷ��Ŀ�꣬��Ϊ�̳е�ActorTwo��ActorThree���̳���ObjectTwo���������Ƕ����������

	/////////////////////////////////////////////////////////

	D4 d;
	d.Hello();
}