#ifndef GY_BASIC_EVENT_SIGNAL_T
#define GY_BASIC_EVENT_SIGNAL_T  
#define BEGIN_GY_NAMESPACE_STUDY_EVENTS namespace GYStudyEvents {
#define END_GY_NAMESPACE_STUDY_EVENTS }
#include<string>


BEGIN_GY_NAMESPACE_STUDY_EVENTS
/**
	Templated class to have any desired event signal
*/
template<class T>
struct GYEventSignalT
{//struct <-> all public anyway...
	/**
		CTOR.
		@param T : The actual signal
		@param string : Optional info / comment about this signal (UTF-8) */
	GYEventSignalT(const T&, const std::string& = { u8"" });
	/**
		Disabled CTOR.
		Must be instantiated with arguments! */
	GYEventSignalT() = delete;
	/** 
		Default DTOR */
	~GYEventSignalT() = default;
	//------------------------------------------------------- C D TORz
	const T				signal;
	const std::string	about;
};
END_GY_NAMESPACE_STUDY_EVENTS
#endif // !GY_BASIC_EVENT_SIGNAL_T
