

inline DWORD_PTR& HbgGetContextIP(CONTEXT& context)
{
	return context.Rip;
}


inline DWORD_PTR& HbgGetContextSP(CONTEXT& context)
{
	return context.Rsp;
}

