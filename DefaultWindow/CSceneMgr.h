#pragma once

#include "Define.h"

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

public:
	void		init();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);

	
public:
	void		SceneChange(SCENE_TYPE _e);

public:
	CScene* GetCurScene() { return m_pCurScene; }
	CScene* GetPreScene() { return m_pPreScene; }

private:
	vector<CScene*> m_vecGameScene;

	CScene*			m_pCurScene;
	CScene*			m_pPreScene;

};

