#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}


CObj * CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	if(m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;

	float	fDistance(0.f);  // ���� ��ü���� �Ÿ� 

	for (auto& iter : m_ObjList[eID])  // ����Ÿ���� ��ü�� �������� ã�´�
	{
		if(iter->Get_Dead())
			break;

		float	fWidth	  = pObj->Get_Info().fX - iter->Get_Info().fX;
		float	fHeight	  = pObj->Get_Info().fY - iter->Get_Info().fY; 
		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);  // ��ü���� �Ÿ��ε� �ּ� �Ÿ��� ģ���� ã������ 
		// Diagonal�� �� �����Ӹ��� ����

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}


void CObjMgr::Update()
{
	int		iResult (OBJ_NOEVENT);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (OBJID::OBJ_NPC == i || OBJID::OBJ_BACKGROUD == i)
		{
			if (SCENE_TYPE::LOBBY != CSceneMgr::CreateSingleTonInst()->GetCurScene()->GetSceneType())
			{
				continue;
			}
		}
		for ( auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}


}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (OBJID::OBJ_NPC == i || OBJID::OBJ_BACKGROUD == i)
		{
			if (SCENE_TYPE::LOBBY != CSceneMgr::CreateSingleTonInst()->GetCurScene()->GetSceneType())
			{
				continue;
			}
		}
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}


	CCollisionMgr::CreateSingleTonInst()->Collision_RectEx(m_ObjList[OBJID::OBJ_PLAYER_SKILL], m_ObjList[OBJID::OBJ_MONSTER]);
	CCollisionMgr::CreateSingleTonInst()->Collision_RectEx(m_ObjList[OBJID::OBJ_PLAYER_SKILL], m_ObjList[OBJID::OBJ_BOSS]);

	CCollisionMgr::CreateSingleTonInst()->Collision_RectEx(m_ObjList[OBJID::OBJ_PLAYER], m_ObjList[OBJID::OBJ_MONSTER]);
	CCollisionMgr::CreateSingleTonInst()->Collision_RectEx(m_ObjList[OBJID::OBJ_PLAYER], m_ObjList[OBJID::OBJ_BOSS]);
	CCollisionMgr::CreateSingleTonInst()->Collision_RectEx(m_ObjList[OBJID::OBJ_PLAYER], m_ObjList[OBJID::OBJ_BOSS_SKILL]);
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (OBJID::OBJ_NPC == i || OBJID::OBJ_BACKGROUD == i)
		{
			if (LOBBY != CSceneMgr::CreateSingleTonInst()->GetCurScene()->GetSceneType())
			{
				continue;
			}
		}
		for (auto& iter : m_ObjList[i])
		{
			if (!iter->m_bNoRender)
				iter->Render(hDC);
		}
			
	}

}


void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
