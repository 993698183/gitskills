#pragma once
/*
  * �۲���ģʽ
  * �龰�������Σ�ABCD��λͬѧ��A�Ǻ�ѧ����ȥ�ϿΣ�B������˯����C�����ɴ���Ϸ��D��ѧУ����Ů�ѹ��
  * ����Լ�������Ҫ�����ˣ�A��QQȺ���һ�����������̸ϵ�����ȥ��
  * ���ù۲���ģʽʵ������龰��Ӧ�á�
*/
#include <iostream>
#include <string>
#include <list>

class Observer;

class Subject
{
public:
	virtual ~Subject() {};
	virtual void registerObsvr(Observer * obsvr) = 0;
	virtual void removeObsvr(Observer * obsvr) = 0;
	virtual void notifyObsvrs(const std::string &msg) = 0;
protected:
private:
};

class Observer
{
public:
	virtual ~Observer() {};
	virtual void Update(const std::string &msg) = 0;
	virtual std::string getName() = 0;
protected:
	Observer() {};
private:
};

class QQGroup : public Subject
{
public:
	QQGroup() { _observers = new std::list<Observer *>(); }
	void registerObsvr(Observer *obsvr);
	void removeObsvr(Observer * obsvr);
	void notifyObsvrs(const std::string &msg);
protected:
private:
	std::list<Observer *> *_observers;
};

void QQGroup::registerObsvr(Observer *obsvr)
{
	_observers->push_back(obsvr);
}

void QQGroup::removeObsvr(Observer * obsvr)
{
	if (_observers->size() > 0)
	{
		_observers->remove(obsvr);
	}
}

void QQGroup::notifyObsvrs(const std::string &msg)
{
	std::cout << "Ⱥ��Ϣ" << msg << std::endl;
	std::list<Observer *>::iterator iter = _observers->begin();
	for (; iter != _observers->end(); ++iter)
	{
		(*iter)->Update(msg);
	}
}

class RooMate : public Observer
{
public:
	RooMate(std::string name, std::string now, std::string action)
	{
		_name = name;
		_action = action;
		_now = now;
	}
	void Update(const std::string &msg);
	std::string getName();
protected:
private:
	std::string _name;
	std::string _action;
	std::string _now;
};

void RooMate::Update(const std::string &msg)
{
	std::cout << "This is" << _name << std::endl;
	if (msg == "������")
	{
		std::cout << "Action��" << _action << std::endl << std::endl;
	} 
	else
	{
		std::cout << "Go on��" << _now << std::endl << std::endl;
	}
}

std::string RooMate::getName()
{
	return _name;
}

void testObserverPattern()
{
	RooMate *B = new RooMate("B",
		"sleeping",
		"get dressed and run to classroom");

	RooMate *C = new RooMate("C",
		"playing games",
		"pay the fee and run to classroom");

	RooMate *D = new RooMate("D",
		"shopping with girl friend",
		"go back to school and be worried about girl friends angry");

	QQGroup *qqgroup = new QQGroup();
	qqgroup->registerObsvr(B);
	qqgroup->registerObsvr(C);
	qqgroup->registerObsvr(D);
	qqgroup->notifyObsvrs("Ŀǰû����");
	qqgroup->notifyObsvrs("������");

	system("Pause");
}