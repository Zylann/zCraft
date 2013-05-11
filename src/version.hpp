#ifndef VERSION_H
#define VERSION_H

namespace autoversion{
	
	//Date Version Types
	static const char DATE[] = "11";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.05";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 399;
	static const long REVISION = 2126;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 546;
	#define RC_FILEVERSION 0,1,399,2126
	#define RC_FILEVERSION_STRING "0, 1, 399, 2126\0"
	static const char FULLVERSION_STRING[] = "0.1.399.2126";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 399;
	

}
#endif //VERSION_H
