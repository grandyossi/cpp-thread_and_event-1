#ifndef GY_UTILITY
#define GY_UTILITY  
#include<sstream>
#include<string>


namespace GYUtility
{
	template<typename T>
	static std::string getPointerAddressAsString(const T* inPtr)
	{
		std::stringstream	theStream;
		theStream << static_cast<const void*>(inPtr);
		return theStream.str();
	}
}
#endif //!GY_UTILITY
