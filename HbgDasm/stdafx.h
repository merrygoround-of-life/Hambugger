// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <math.h>
#include <string>
#include "HbgBase/HbgPlatform.h"
#include "HbgDasmDll.h"
#include "HbgDasm.h"


#ifdef _DEBUG
#	define _REPORT_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#	define new _REPORT_DEBUG_NEW
#endif // _DEBUG
