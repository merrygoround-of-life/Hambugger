#pragma once

class CHbgBreakPoint
{
public:
	CHbgBreakPoint();
	CHbgBreakPoint(DWORD_PTR address, BYTE bOp);
	~CHbgBreakPoint(void);
	
public:
	bool operator() (const CHbgBreakPoint& val1, const CHbgBreakPoint& val2) const { return (val1.m_address < val2.m_address) ? TRUE : FALSE; }

public:
	DWORD_PTR m_address;
	BYTE m_bOp;
};
