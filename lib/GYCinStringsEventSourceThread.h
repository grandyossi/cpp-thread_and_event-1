#ifndef GY_EVENT_SOURCE_THREAD
#define GY_EVENT_SOURCE_THREAD  
#include"GYEventSignalT.h"
#include"GYEventSource.h"
#include"GYEventListener.h"
#include<map>
#include<mutex>
#include<thread>
using std::string;


BEGIN_GY_NAMESPACE_STUDY_EVENTS
//max millisecs to wait for obtaining a lock
#define GY_THREAD_LOCK_WAIT_MS_MAX 100
/**
	Specialized in strings input via `std::cin` until `quit` is inputted.
	final (C# sealed) class */
class GYCinStringsEventSourceThread final
{
public:
	GYCinStringsEventSourceThread();
	~GYCinStringsEventSourceThread();
	//
	bool setListenerRegistration(GYEventListener&);//non-const methods
	bool setListenerDeregistration(GYEventListener&);//---------------
	//thread.join
	void waitJoin();

private:
	std::map<string, GYEventListener*> 	m_listeners = { };
	//timed <-> `try_lock_for` / `try_lock_until`
	std::timed_mutex 			m_listeners_mutex = { };
	std::unique_lock<std::timed_mutex> 	m_lock_map = {
												m_listeners_mutex,
												std::defer_lock
											};
	//TO_DO *0*   READ   : thread ctor is marked `explicit` -
	//thus init is not possible here,
	//but in ctor.
	std::thread			m_threadObject;
	//
	GYEventSource			m_eventsSource = { };
	bool				m_isDisposed = false;
	//
	void				mf_threadProc();//both cant be const ----
	void				mf_raiseEvent(const string&); //----
	//QUIT indication constant
	const string			m_quit = { u8"!Q!" };
};
END_GY_NAMESPACE_STUDY_EVENTS
#endif //!GY_EVENT_SOURCE_THREAD
