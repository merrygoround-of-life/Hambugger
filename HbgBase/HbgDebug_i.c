
#if defined(_WIN64)
#	if defined(_DEBUG)
#		include "HbgDebug_x64_Debug_i.c"
#	else
#		include "HbgDebug_x64_Release_i.c"
#	endif
#elif defined(_WIN32)
#	if defined(_DEBUG)
#		include "HbgDebug_Win32_Debug_i.c"
#	else
#		include "HbgDebug_Win32_Release_i.c"
#	endif
#endif
