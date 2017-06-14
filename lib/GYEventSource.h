#ifndef GY_EVENT_SOURCE
#define GY_EVENT_SOURCE  
#include"GYEventSignalT.h"
#include"GYEventSignalT.hpp"
using std::string;


BEGIN_GY_NAMESPACE_STUDY_EVENTS
/**
	Represents an event where a string was inputted via `std::cin`.
	Inheritance as a workaround base's optional string param ` = { u8"" }`.
	NOTICE : inherits a specialized template */
struct GYCINEventSignal : GYEventSignalT<string>
{//ctor invokes base ctor
	GYCINEventSignal(const string& inData)
	:GYEventSignalT<string>(inData, string(u8"std::cin")) { }
	//NOTICE :	the 2nd arg is explicitly constructed.
	//			u8"std::cin" as arg -> implicit
};
/**
	All public
	@see https://msdn.microsoft.com/en-us/library/ee2k0a7d.aspx
	@see https://msdn.microsoft.com/en-us/library/3fw55ssh.aspx
	`Note` at page end : A templated class or struct cannot contain events
	TO_DO *2*   READ   : deprecated ATL attrib
	@see https://msdn.microsoft.com/en-us/library/mt723604.aspx -> __declspec
*/
struct GYEventSource
{//__declspec("event_source","native")//deprecated : [event_source(native)]
	//NO need of function definition
	__event void setEvent(const GYCINEventSignal&);
};
END_GY_NAMESPACE_STUDY_EVENTS
#endif //!GY_EVENT_SOURCE
