#include "stdafx.h"
#include "HbgMemPtr.h"


CHbgMemPtr::CHbgMemPtr(SIZE_T size)
:	m_data(NULL)
{
	if (size)
		m_data = new BYTE[size];
}

CHbgMemPtr::~CHbgMemPtr()
{
	if (m_data) {
		delete[] m_data;
		m_data = NULL;
	}
}
