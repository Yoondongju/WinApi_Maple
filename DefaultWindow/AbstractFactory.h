#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();		
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, int _iType, CObj* _pPlayer)							//헤네시스 1 몬스터 생성용
	{
		CObj* pObj = new T(_iType);
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Target(_pPlayer);

		return pObj;
	}



public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};

