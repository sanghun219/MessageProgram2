#pragma once
#include "../framework.h"

template<class T>
class Singleton {
protected:
	Singleton() {
	}
	virtual ~Singleton() {
	}
public:
	static T* GetInstance() {
		if (m_pInst == nullptr)
			m_pInst = new T;
		return m_pInst;
	}

	static void DestroyInstance() {
		if (m_pInst) {
			delete m_pInst;
			m_pInst = nullptr;
		}
	}
private:
	static T* m_pInst;
};

template<class T> T* Singleton<T>::m_pInst = nullptr;