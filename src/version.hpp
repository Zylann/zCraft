#ifndef VERSION_H
#define VERSION_H

namespace autoversion{
	
	//Date Version Types
	static const char DATE[] = "27";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.02";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 141;
	static const long REVISION = 759;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 180;
	#define RC_FILEVERSION 0,1,141,759
	#define RC_FILEVERSION_STRING "0, 1, 141, 759\0"
	static const char FULLVERSION_STRING[] = "0.1.141.759";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 141;
	

}
#endif //VERSION_H
