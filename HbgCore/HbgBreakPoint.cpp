#include "StdAfx.h"
#include "HbgBreakPoint.h"


CHbgBreakPoint::CHbgBreakPoint()
:	m_address(0), m_bOp(0)
{
}

CHbgBreakPoint::CHbgBreakPoint(DWORD_PTR address, BYTE bOp)
:	m_address(address), m_bOp(bOp)
{
}

CHbgBreakPoint::~CHbgBreakPoint(void)
{
}
