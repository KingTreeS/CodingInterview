#pragma once
#ifndef _SINGLETON_H__
#define _SINGLETON_H__

//懒汉模式：双检锁（多线程）
#include <mutex>

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pMutex.lock();
			if (m_pInstance == nullptr)
			{
				m_pInstance = new Singleton();
			}
			m_pMutex.unlock();
		}
		return m_pInstance;
	}

	static void Destory()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	Singleton() {};
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	virtual ~Singleton() {};

private:
	static Singleton* m_pInstance;
	static std::mutex m_pMutex;

};

Singleton* Singleton::m_pInstance = nullptr;
std::mutex Singleton::m_pMutex;

////懒汉模式：静态局部变量，避免自己回收资源
//#include <mutex>
//
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		m_pMutex.lock();
//		static Singleton singleton;
//		m_pMutex.unlock();
//
//		return &singleton;
//	}
//
//private:
//	Singleton() {};
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//	virtual ~Singleton() {};
//
//private:
//	static std::mutex m_pMutex;
//
//};
//
//std::mutex Singleton::m_pMutex;

////饿汉模式：一开始便初始化，无需考虑多线程问题
////考虑： 如果有两个这样的单例类，将分别生成单例对象A, 单例对象B. 它们分别定义在不同的编译单元（cpp中）， 
////而A的初始化依赖于B 【 即A的构造函数中要调用B::GetInstance() ，而此时B::m_instance 可能还未初始化，显然调用结果就是非法的 】， 
////所以说只有B在A之前完成初始化程序才能正确运行，而这种跨编译单元的初始化顺序编译器是无法保证的
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		return &m_pSingleton;
//	}
//
//private:
//	Singleton() {};
//	~Singleton() {};
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//private:
//	static Singleton m_pSingleton;
//};
//
//Singleton Singleton::m_pSingleton;

////饿汉模式：boost实现
////单例对象作为静态局部变量，然后增加一个辅助类，并声明一个该辅助类的类静态成员变量，在该辅助类的构造函数中，初始化单例对象
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		static Singleton m_pSingleton;
//		return &m_pSingleton;
//	}
//
//protected:
//	struct Boost
//	{
//		Boost()
//		{
//			Singleton::GetInstance();
//		}
//	};
//	static Boost boost;
//
//private:
//	Singleton() {};
//	~Singleton() {};
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//};
//
//Singleton::Boost Singleton::boost;
#endif // !_SINGLETON_H__
