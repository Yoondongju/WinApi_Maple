#pragma once

#include "Obj.h"

class CWill_Page1;
class CPlayer;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)


public:
	static void	Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static void	Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);




private:
	static bool	WillPage1_Colli(INFO playerInfo, CPlayer* pPlayer , CWill_Page1* pMon);
	static bool	WillPage2_Colli(INFO playerInfo, CPlayer* pPlayer, CWill_Page1* pMon);
	static bool	WillPage3_Colli(INFO playerInfo, CPlayer* pPlayer, CWill_Page1* pMon);

};

