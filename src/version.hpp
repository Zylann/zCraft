#ifndef VERSION_H
#define VERSION_H

namespace autoversion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.03";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 309;
	static const long REVISION = 1644;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 413;
	#define RC_FILEVERSION 0,1,309,1644
	#define RC_FILEVERSION_STRING "0, 1, 309, 1644\0"
	static const char FULLVERSION_STRING[] = "0.1.309.1644";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 309;
	

}
#endif //VERSION_H
