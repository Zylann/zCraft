#ifndef VERSION_H
#define VERSION_H

namespace autoversion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.05";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 419;
	static const long REVISION = 2250;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 575;
	#define RC_FILEVERSION 0,1,419,2250
	#define RC_FILEVERSION_STRING "0, 1, 419, 2250\0"
	static const char FULLVERSION_STRING[] = "0.1.419.2250";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 419;
	

}
#endif //VERSION_H
