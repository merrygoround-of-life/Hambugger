// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// Windows ��� ����:
#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <objbase.h>
#include <string>


#ifdef _DEBUG
#	define _REPORT_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#	define new _REPORT_DEBUG_NEW
#endif // _DEBUG
