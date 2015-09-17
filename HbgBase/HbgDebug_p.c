
#if defined(_WIN64)
#	if defined(_DEBUG)
#		include "HbgDebug_x64_Debug_p.c"
#	else
#		include "HbgDebug_x64_Release_p.c"
#	endif
#elif defined(_WIN32)
#	if defined(_DEBUG)
#		include "HbgDebug_Win32_Debug_p.c"
#	else
#		include "HbgDebug_Win32_Release_p.c"
#	endif
#endif
