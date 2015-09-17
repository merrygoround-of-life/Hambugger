
#if defined(_WIN64)
#	if defined(_DEBUG)
#		include "dlldata_x64_Debug.c"
#	else
#		include "dlldata_x64_Release.c"
#	endif
#elif defined(_WIN32)
#	if defined(_DEBUG)
#		include "dlldata_Win32_Debug.c"
#	else
#		include "dlldata_Win32_Release.c"
#	endif
#endif
