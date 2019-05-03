#pragma once
#ifndef _SINGLETON_H__
#define _SINGLETON_H__

//����ģʽ��˫���������̣߳�
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

////����ģʽ����̬�ֲ������������Լ�������Դ
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

////����ģʽ��һ��ʼ���ʼ�������迼�Ƕ��߳�����
////���ǣ� ��������������ĵ����࣬���ֱ����ɵ�������A, ��������B. ���Ƿֱ����ڲ�ͬ�ı��뵥Ԫ��cpp�У��� 
////��A�ĳ�ʼ��������B �� ��A�Ĺ��캯����Ҫ����B::GetInstance() ������ʱB::m_instance ���ܻ�δ��ʼ������Ȼ���ý�����ǷǷ��� ���� 
////����˵ֻ��B��A֮ǰ��ɳ�ʼ�����������ȷ���У������ֿ���뵥Ԫ�ĳ�ʼ��˳����������޷���֤��
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

////����ģʽ��boostʵ��
////����������Ϊ��̬�ֲ�������Ȼ������һ�������࣬������һ���ø�������ྲ̬��Ա�������ڸø�����Ĺ��캯���У���ʼ����������
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
