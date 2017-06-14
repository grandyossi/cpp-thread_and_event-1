//#include"../event_lib/GYEventSignalT.hpp" //GYBasicEventSignal
#include"../event_lib/GYCinStringsEventSourceThread.h"
#include<iostream>
using namespace GYStudyEvents;


int main()
{
	GYEventListener					client;
									//TEST OK : with no registered listeners
	GYCinStringsEventSourceThread	inputStringsLoop;
	inputStringsLoop.setListenerRegistration(client);
	inputStringsLoop.waitJoin();//until !q! is inputted...
	return EXIT_SUCCESS;
}
