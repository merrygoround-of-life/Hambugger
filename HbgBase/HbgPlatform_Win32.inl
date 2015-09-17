

inline DWORD_PTR& HbgGetContextIP(CONTEXT& context)
{
	return context.Eip;
}


inline DWORD_PTR& HbgGetContextSP(CONTEXT& context)
{
	return context.Esp;
}

