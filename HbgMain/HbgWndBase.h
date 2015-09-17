#ifndef _HbgWndBase_H_
#define _HbgWndBase_H_


class CHbgMainView;
class CHbgMainDoc;


interface IHbgWndBase
{
	virtual void LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* pHbgDoc) = 0;
	virtual void Reset() = 0;
	virtual void Enable(BOOL bEnable) = 0;

	virtual void Prompt(HBG_PROMPT_TYPE type, LPCVOID pData) = 0;
	virtual void Update(HBG_UPDATE_TYPE type, LPCVOID pData) = 0;
};


#endif // _HbgWndBase_H_
