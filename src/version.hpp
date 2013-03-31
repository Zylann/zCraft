#ifndef VERSION_H
#define VERSION_H

namespace autoversion{
	
	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.04";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 393;
	static const long REVISION = 2087;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 534;
	#define RC_FILEVERSION 0,1,393,2087
	#define RC_FILEVERSION_STRING "0, 1, 393, 2087\0"
	static const char FULLVERSION_STRING[] = "0.1.393.2087";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 393;
	

}
#endif //VERSION_H
