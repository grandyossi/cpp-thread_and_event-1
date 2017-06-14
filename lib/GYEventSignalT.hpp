//some OVERHEAD when the intention is to seperate template implementation.
//however, the result is the same -
//SO,
//in NON study env -
//better leave such thingz in the original header.
#ifndef GY_BASIC_EVENT_SIGNAL
#define GY_BASIC_EVENT_SIGNAL  
#include"GYEventSignalT.h"


BEGIN_GY_NAMESPACE_STUDY_EVENTS
//ctor is defined in `.hpp`
template<class T>
GYEventSignalT<T>::GYEventSignalT(
							const T& inSig,
							const std::string& inInf)
	:signal(inSig),
	about(inInf) { }


//template specialization via `__int64`
typedef GYEventSignalT<__int64> GYBasicEventSignal;
END_GY_NAMESPACE_STUDY_EVENTS
#endif