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
#include <objbase.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>


#include "HbgCoreDll.h"
#include "HbgBase/HbgDefs.h"


#ifdef _DEBUG
#	define _REPORT_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#	define new _REPORT_DEBUG_NEW
#endif // _DEBUG
