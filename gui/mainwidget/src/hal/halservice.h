#ifndef HALSERVICE_H
#define HALSERVICE_H

// Hardware Abstraction Layer service.
template<class T>
class HALService
{
public:
	static T *impl() { return sImpl; }             // Get implementation.
	static void setImpl(T *impl) { sImpl = impl; } // Set implementation.
private:
	static T *sImpl;
};

template<class T>
T *HALService<T>::sImpl = NULL;

#endif
