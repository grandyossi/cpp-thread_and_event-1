#ifndef GY_EVENT_LISTENER
#define GY_EVENT_LISTENER  
#include"GYEventSignalT.h"
#include"GYEventSource.h"
#include<Windows.h>//Win32 API dependancy + Kernel32.lib


BEGIN_GY_NAMESPACE_STUDY_EVENTS
/**
	struct, since all public.
	TO_DO *0* : `Listener` and `Source` as interfaces + move code to cpp
*/  
struct GYEventListener
{//__declspec("event_receiver", "native")//depr : [event_receiver(native)]
	

	//The signal will be displayed as a line in the dbg window (aka `Output`)
	void onEvent(const GYCINEventSignal& inEventData)
	{
		OutputDebugStringA(inEventData.signal.c_str());
		OutputDebugStringA("\n");
		//TO_DO *3* : in case of event...
	}


	void hookEvent(GYEventSource* inSrc) {
		__hook(&GYEventSource::setEvent, inSrc, &GYEventListener::onEvent);
	}


	void unhookEvent(GYEventSource* inSrc) {
		__unhook(&GYEventSource::setEvent, inSrc, &GYEventListener::onEvent);
	}
};
END_GY_NAMESPACE_STUDY_EVENTS
#endif //!GY_EVENT_LISTENER
