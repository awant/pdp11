#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}
	static T *IPtr();
	static T &I();
	static void destroyInstance();

protected:
	static T * self;
};



template <class T>
T *Singleton<T>::self = nullptr;

template <class T>
T* Singleton<T>::IPtr() {
	if (!self) {
		self = new T();
	}
	return self;
}

template <class T>
T& Singleton<T>::I() {
	return *IPtr();
}

template <class T>
void Singleton<T>::destroyInstance() {
	delete self;
	self = nullptr;
}

#endif // _SINGLETON_H_