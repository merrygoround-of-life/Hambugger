
#if defined(_WIN64)
#	if defined(_DEBUG)
#		include "HbgDebug_x64_Debug_h.h"
#	else
#		include "HbgDebug_x64_Release_h.h"
#	endif
#elif defined(_WIN32)
#	if defined(_DEBUG)
#		include "HbgDebug_Win32_Debug_h.h"
#	else
#		include "HbgDebug_Win32_Release_h.h"
#	endif
#endif
