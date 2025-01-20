#pragma once

#include "Define.h"

class CTexture;
class CObj;
class CPotal;

class CScene  abstract
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual	void		Initialize()PURE;
	virtual void		Update()PURE;
	virtual void		Late_Update() PURE;
	virtual void		Render(HDC hDC) PURE;

	virtual void		Enter() PURE;
	virtual void		Exit()PURE;


public:

public:
	SCENE_TYPE	GetSceneType() { return m_SceneType; }

	//list<CObj*>& Get_TypeObj(OBJID _e) { return m_ObjList[_e]; }


public:
	CTexture* GetMapTex() { return m_pMapTex; }


public:
	CObj*				 GetCurSceneNpc() { return m_pNpc;}
	CObj*				 GetCurSceneStoreNpc() { return m_pStoreNpc; }
	vector<CPotal*>&	 GetCurScenePotalvec() { return m_vecPotal; }


protected:
	CTexture*		m_pMapTex;  // æ¿ ∏  ¿ÃπÃ¡ˆ


	float			m_iMapMinX;
	float			m_iMapMinY;


	SCENE_TYPE		m_SceneType;


	//list<CObj*>		m_ObjList[OBJID::OBJ_END];


	CObj*					m_pNpc;
	CObj*					m_pStoreNpc;
	vector<CPotal*>			m_vecPotal;



	CTexture*				m_pBossIntroTex;

};

