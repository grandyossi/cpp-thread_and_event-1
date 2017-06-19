#include"GYEventSignalT.h"
#include"GYEventSignalT.hpp"
using namespace GYStudyEvents;


GYBasicEventSignal::GYEventSignalT(const __int64& inSignal,
				   const std::string& inInf)
:signal(inSignal),
about(inInf) { }
