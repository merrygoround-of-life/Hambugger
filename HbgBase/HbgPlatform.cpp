#include "stdafx.h"
#include "HbgPlatform.h"


#if defined(_WIN64)
SIZE_T HbgNullIdx = 0xffffffffffffffff;
#elif defined(_WIN32)
SIZE_T HbgNullIdx = 0xffffffff;
#endif


LPCWSTR HbgFmtAddrStr_8byte = L"0x%016I64X";
LPCWSTR HbgFmtAddrStr_4byte = L"0x%08I32X";
LPCWSTR HbgFmtAddrStr_2byte = L"0x%04X";
LPCWSTR HbgFmtAddrStr_1byte = L"0x%02X";
LPCWSTR HbgFmtAddrStr_4bit = L"0x%1X";

LPCWSTR HbgFmtValStr_8byte = L"%016I64X";
LPCWSTR HbgFmtValStr_4byte = L"%08I32X";
LPCWSTR HbgFmtValStr_2byte = L"%04X";
LPCWSTR HbgFmtValStr_1byte = L"%02X";
LPCWSTR HbgFmtValStr_4bit = L"%1X";

LPCWSTR HbgFmtValStr_fpu = L"%+1.17Le";
LPCWSTR HbgFmtValStr_mmx = L"%08I32X %08I32X";
LPCWSTR HbgFmtValStr_xmm = L"%08I32X %08I32X %08I32X %08I32X";


BOOL HbgPrintHex8byte(std::wstring& text, const DWORD64& value)
{
	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_8byte, value) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgScanHex8byte(const std::wstring& text, DWORD64& value)
{
	DWORD64 tmpVal = 0;
	if (swscanf_s(text.c_str(), HbgFmtValStr_8byte, &tmpVal) > 0) {
		value = tmpVal;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgPrintHex4byte(std::wstring& text, const DWORD& value)
{
	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_4byte, value) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgScanHex4byte(const std::wstring& text, DWORD& value)
{
	DWORD tmpVal = 0;
	if (swscanf_s(text.c_str(), HbgFmtValStr_4byte, &tmpVal) > 0) {
		value = tmpVal;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgPrintHex2byte(std::wstring& text, const WORD& value)
{
	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_2byte, value) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgScanHex2byte(const std::wstring& text, WORD& value)
{
	WORD tmpVal = 0;
	if (swscanf_s(text.c_str(), HbgFmtValStr_2byte, &tmpVal) > 0) {
		value = tmpVal;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgPrintHex1byte(std::wstring& text, const unsigned char& value)
{
	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_1byte, value) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgScanHex1byte(const std::wstring& text, unsigned char& value)
{
	unsigned char tmpVal = 0;
	if (swscanf_s(text.c_str(), HbgFmtValStr_1byte, &tmpVal) > 0) {
		value = tmpVal;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgPrintHex4bit(std::wstring& text, const unsigned char& value)
{
	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_4bit, value) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

BOOL HbgScanHex4bit(const std::wstring& text, unsigned char& value)
{
	unsigned char tmpVal = 0;
	if (swscanf_s(text.c_str(), HbgFmtValStr_4bit, &tmpVal) > 0) {
		value = tmpVal;
		return TRUE;
	}

	return FALSE;
}
