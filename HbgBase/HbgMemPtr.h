#ifndef _HbgMemPtr_h_
#define _HbgMemPtr_h_


class CHbgMemPtr
{
public:
	CHbgMemPtr(SIZE_T size);
	~CHbgMemPtr();

public:
	operator LPBYTE() const { return m_data; }

private:
	LPBYTE m_data;
};


#endif // _HbgMemPtr_h_
