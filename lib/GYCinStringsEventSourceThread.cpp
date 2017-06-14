#include"GYUtility.h"
#include"GYCinStringsEventSourceThread.h"
#include<iostream>
using std::chrono::milliseconds;
using std::string;
using namespace GYStudyEvents;


//Map member const iterator
typedef std::map<string, GYEventListener*>::const_iterator	GYCIter;
////Map member non-const iterator
typedef std::map<string, GYEventListener*>::iterator		GYIter;


//-----------------------------------------------------------------------
//CTOR <-> `m_threadObject` is ctord explicitly
GYCinStringsEventSourceThread::GYCinStringsEventSourceThread()
:m_threadObject(&GYCinStringsEventSourceThread::mf_threadProc, this) { }


//DTOR
GYCinStringsEventSourceThread::~GYCinStringsEventSourceThread()
{
	//iterate over map elements to deRegister
	GYCIter end = m_listeners.end();
	for (GYIter it = m_listeners.begin(); it != end; it++)
	{
		//it->first		KEY = string
		it->second->unhookEvent(&m_eventsSource);
		it->second = NULL;
	}
}


bool GYCinStringsEventSourceThread::setListenerRegistration
										(GYEventListener& inClient)
{//not using `std::to_string`
	string addr(//copy ctor
		GYUtility::getPointerAddressAsString<GYEventListener>(&inClient)
	);
	bool toRet = false;
	if (m_lock_map.try_lock_for(milliseconds(GY_THREAD_LOCK_WAIT_MS_MAX)))
	{
		//`m_lock_map.lock()`         ->
		//for more than one lock objz -> std::lock(lock1, lock2, ...);
		GYCIter iter = m_listeners.find(addr);//can also `auto iter = ...`
		if (iter == m_listeners.end())
		{//not in map
			inClient.hookEvent(&m_eventsSource);//hook to NON const obj
			m_listeners[addr] = &inClient;
			toRet = true;
			//m_listeners.insert({ addr, inClient });//ctored pair object
		}
		m_lock_map.unlock();
	}
	return toRet;
}


bool GYCinStringsEventSourceThread::setListenerDeregistration(
											GYEventListener& inDeReg)
{
	string addr(
		GYUtility::getPointerAddressAsString<GYEventListener>(&inDeReg)
	);
	bool toRet = false;
	if (m_lock_map.try_lock_for(milliseconds(GY_THREAD_LOCK_WAIT_MS_MAX)))
	{
		GYCIter iter = m_listeners.find(addr);
		if (iter != m_listeners.end())
		{//in map
			inDeReg.unhookEvent(&m_eventsSource);
			m_listeners.erase(addr);
			toRet = true;
		}
		m_lock_map.unlock();
	}
	return toRet;
}


void GYCinStringsEventSourceThread::waitJoin()
{
	m_threadObject.join();
}


void GYCinStringsEventSourceThread::mf_threadProc()
{
	string textViaCin;
	while (true)
	{//multiline code
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		//REM   char pszIn[100] = { u8"" };
		//REM   std::cin >> pszIn;
		std::cout << \
			"Input text and hit `Enter` when done " << \
			"(Enter " << m_quit << " to quit)" << std::endl;
		std::getline(std::cin, textViaCin).clear();
		mf_raiseEvent(textViaCin);
		//AFTER `mf_raiseEvent` returns - can MUTATE the string
		//via range-based for loop
		for (auto& c : textViaCin) c = toupper(c);
		if (m_quit.compare(textViaCin) == 0) break;
	}
}


void GYCinStringsEventSourceThread::mf_raiseEvent(
									const string& inMsg)
{
	//until <-> from now + delta
	auto unTil =
		std::chrono::high_resolution_clock::now() +
		milliseconds(GY_THREAD_LOCK_WAIT_MS_MAX);
	if (m_lock_map.try_lock_until(unTil))
	{//TESTED OK : with no registered listeners
		__raise m_eventsSource.setEvent(GYCINEventSignal(inMsg));
		m_lock_map.unlock();//from now on - map can be changed
	}
}
