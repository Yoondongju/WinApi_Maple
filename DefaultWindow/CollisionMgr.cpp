#include "stdafx.h"
#include "CollisionMgr.h"


#include "CMonster.h"
#include "Player.h"

#include "CPlayerSkill.h"
#include "CDamageEffect.h"
#include "ObjMgr.h"

#include "CTimeMgr.h"

#include "CWill_Page1.h"
#include "CWIll_Page3.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CKariainSkill.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}



void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{

				

			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	if (OBJ_PLAYER_SKILL == pDst->GetObjType() && OBJ_MONSTER == pSrc->GetObjType())
	{
		CPlayerSkill* pSkill = static_cast<CPlayerSkill*>(pDst);
		CMonster* pMon = static_cast<CMonster*>(pSrc);
	
		
		if (false == pSkill->GetSkillActivate())
			return false;

		RECT rtSkillRange = pSkill->GetSkillRange();
		if (rtSkillRange.right == WINCX)		// 무조건 충돌
		{
			pMon->SetHit(true);
			pMon->SetCollisionObj(pDst);

			float fBossHp = pMon->GetHp();

			if (fBossHp <= 0.f)
			{
				pMon->SetDeadAniPlay(true);
			}
			else
			{
				pMon->SetCurColliSkillType(pSkill->GetSkillType());
				pMon->SetHp(fBossHp - pSkill->GetSkillAttackInfo());
			}

			return true;
		}

		float fskillCX = (rtSkillRange.right - rtSkillRange.left) / 2.f;	 // Skill 사이즈
		float fskillCY = (rtSkillRange.bottom - rtSkillRange.top) / 2.f;	 // Skill 사이즈

		float fskillX = rtSkillRange.left + fskillCX;						 // 스킬 중점 
		float fskillY = rtSkillRange.top + fskillCY;						 // 스킬 중점 


		float	fWidth = abs(fskillX - pSrc->Get_Info().fX);
		float	fHeight = abs(fskillY - pSrc->Get_Info().fY);

		float	fRadiusX = (fskillCX + pSrc->Get_Info().fCX) * 0.5f;
		float	fRadiusY = (fskillCY + pSrc->Get_Info().fCY) * 0.5f;


		if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
		{			
			pMon->SetCurColliSkillType(pSkill->GetSkillType());
			pMon->SetHit(true);
			pMon->SetCollisionObj(pDst);
			pMon->SetDeadAniPlay(true);

			return true;
		}
		else
		{
			pMon->SetHit(false);
		}

		return false;
	}

	if((OBJ_PLAYER_SKILL == pDst->GetObjType() && OBJ_BOSS == pSrc->GetObjType()))
	{
		CPlayerSkill* pSkill = static_cast<CPlayerSkill*>(pDst);
		CMonster* pMon = static_cast<CMonster*>(pSrc);

		
		if (false == pSkill->GetSkillActivate())
			return false;

		RECT rtSkillRange = pSkill->GetSkillRange();
		if (rtSkillRange.right == WINCX)		// 무조건 충돌
		{
			pMon->SetHit(true);
			pMon->SetCollisionObj(pDst);

			float fBossHp = pMon->GetHp();

			if (pSkill->IsFirstAttack())
			{
				pSkill->SetFirstAttack(false);		// 스킬 다시 누른 시점에서 풀어주는듯

				pMon->SetCurColliSkillType(pSkill->GetSkillType());

				pMon->SetHp(fBossHp - pSkill->GetSkillAttackInfo());
			}

			if (fBossHp <= 0.f)
			{
				pMon->SetDeadAniPlay(true);
			}
			return true;
		}



		float fskillCX = (rtSkillRange.right - rtSkillRange.left) / 2.f;	 // Skill 사이즈
		float fskillCY = (rtSkillRange.bottom - rtSkillRange.top) / 2.f;	 // Skill 사이즈

		float fskillX = rtSkillRange.left + fskillCX;						 // 스킬 중점 
		float fskillY = rtSkillRange.top + fskillCY;						 // 스킬 중점 


		float	fWidth = abs(fskillX - pSrc->Get_Info().fX);
		float	fHeight = abs(fskillY - pSrc->Get_Info().fY);

		float	fRadiusX = (fskillCX + pSrc->Get_Info().fCX) * 0.5f;
		float	fRadiusY = (fskillCY + pSrc->Get_Info().fCY) * 0.5f;
		

		if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
		{
			pMon->SetHit(true);
			pMon->SetCollisionObj(pDst);

			float fBossHp = pMon->GetHp();

			// 충돌 중이면 루프가 계속 돌고 
			// 스킬과 충돌한 시점 한번만 데미지를 깎아야함
			if (pSkill->IsFirstAttack())
			{
				pSkill->SetFirstAttack(false);

				pMon->SetCurColliSkillType(pSkill->GetSkillType());
				pMon->SetHp(fBossHp - pSkill->GetSkillAttackInfo());
			}

			if (fBossHp <= 0.f)
			{
				pMon->SetDeadAniPlay(true);
			}
			return true;
		}
		else
		{
			pMon->SetHit(false);
		}

		return false;
	}


	if (OBJ_PLAYER == pDst->GetObjType() && OBJ_BOSS == pSrc->GetObjType())
	{
		INFO playerInfo = pDst->Get_Info();
		CPlayer* pPlayer = (CPlayer*)pDst;

		CWill_Page1* pMon = dynamic_cast<CWill_Page1*>(pSrc);

		if (pMon)
		{
			switch (pMon->GetCurPage())
			{
			case WILL_PAGE::PAGE1:
				return WillPage1_Colli(playerInfo, pPlayer, pMon);
				break;
			case WILL_PAGE::PAGE2:
				return WillPage2_Colli(playerInfo, pPlayer, pMon);
				break;
			case WILL_PAGE::PAGE3:
				return WillPage3_Colli(playerInfo, pPlayer, pMon);
				break;
			default:
				break;
			}
		}
		
	}


	
	if (OBJ_PLAYER == pDst->GetObjType() && OBJ_BOSS_SKILL == pSrc->GetObjType())
	{
		INFO playerInfo = pDst->Get_Info();
		CPlayer* pPlayer = (CPlayer*)pDst;

		float	fWidth = abs(playerInfo.fX - pSrc->Get_Info().fX);
		float	fHeight = abs(playerInfo.fY - pSrc->Get_Info().fY);

		float	fRadiusX = (playerInfo.fCX + pSrc->Get_Info().fCX) * 0.5f;
		float	fRadiusY = (playerInfo.fCY + pSrc->Get_Info().fCY) * 0.5f;

		CKariainSkill* pKariainSkill = dynamic_cast<CKariainSkill*>(pSrc);

		if (!pKariainSkill)		// 윌의 스킬일 경우
		{
			if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
			{
				pPlayer->SetCollsion(true);
				float fHitDelay = pPlayer->GetHitDelay();

				if (fHitDelay == 1.5f)
				{
					pPlayer->SetFirstCollsion(true);
					pPlayer->SetHp(pPlayer->GetHp() - (pPlayer->GetMaxHP() * 0.3));

					if (pPlayer->GetHp() <= 0.f)
					{
						pPlayer->SetFakeDead(true);
					}
				}
				return true;
			}
			else
			{
				pPlayer->SetCollsion(false);
			}
		}
		else
		{
			if (pKariainSkill->GetActive())
			{				
					pPlayer->SetCollsion(true);
					float fHitDelay = pPlayer->GetHitDelay();

					if (fHitDelay == 1.5f)
					{
						pPlayer->SetFirstCollsion(true);
						pPlayer->SetHp(pPlayer->GetHp() - (pPlayer->GetMaxHP() * 0.3));

						if (pPlayer->GetHp() <= 0.f)
						{
							pPlayer->SetFakeDead(true);
						}
					}
					return true;	
			}
			else
				pPlayer->SetCollsion(false);
		}

		return false;
	}

}




	

	


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	
	return false;
}

bool CCollisionMgr::WillPage1_Colli(INFO playerInfo, CPlayer* pPlayer, CWill_Page1* pMon)
{
	if (pMon->GetAttacking())
	{
		float	fWidth(0);
		float	fHeight(0);

		float	fRadiusX(0);
		float	fRadiusY(0);

		switch (pMon->GetAttackType())
		{
		case WILL_ATTACK_TYPE::ATTACK1:
		{
			fWidth = abs(playerInfo.fX - pMon->GetAttackRangePos().x);
			fHeight = abs(playerInfo.fY - pMon->GetAttackRangePos().y);

			fRadiusX = (playerInfo.fCX + pMon->GetAttackRangeSize().x) * 0.5f;
			fRadiusY = (playerInfo.fCY + pMon->GetAttackRangeSize().y) * 0.5f;


			if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
			{
				pPlayer->SetCollsion(true);
				float fHitDelay = pPlayer->GetHitDelay();

				if (fHitDelay == 1.5f)
				{
					pPlayer->SetFirstCollsion(true);
					pPlayer->SetHp(pPlayer->GetHp() - pMon->GetAttackInfo());

					if (pPlayer->GetHp() <= 0.f)
					{
						pPlayer->SetFakeDead(true);
					}
				}

				return true;
			}
			else
			{
				pPlayer->SetCollsion(false);
			}

		}
		break;
		default:
			break;
		}


		
	}

	return false;
}

bool CCollisionMgr::WillPage2_Colli(INFO playerInfo, CPlayer* pPlayer, CWill_Page1* pMon)
{
	if (pMon->GetAttacking())
	{
		float	fWidth(0);
		float	fHeight(0);

		float	fRadiusX(0);
		float	fRadiusY(0);

		switch (pMon->GetAttackType())
		{
		case WILL_ATTACK_TYPE::ATTACK1:
		{
			fWidth = abs(playerInfo.fX - pMon->GetAttackRangePos().x);
			fHeight = abs(playerInfo.fY - pMon->GetAttackRangePos().y);

			fRadiusX = (playerInfo.fCX + pMon->GetAttackRangeSize().x) * 0.5f;
			fRadiusY = (playerInfo.fCY + pMon->GetAttackRangeSize().y) * 0.5f;


			if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
			{
				pPlayer->SetCollsion(true);
				float fHitDelay = pPlayer->GetHitDelay();

				if (fHitDelay == 1.5f)		// 처음 충돌한 시점 
				{
					pPlayer->SetFirstCollsion(true);
					pPlayer->SetHp(pPlayer->GetHp() - pMon->GetAttackInfo());
					
					if (pPlayer->GetHp() <= 0.f)
					{
						pPlayer->SetFakeDead(true);
					}

				}
				else                       // 현재 충돌중인 시점 
				{
					Vec2 vPos = pPlayer->GetPos();
					if (MONSTER_DIR::LEFT == pMon->GetDir())
					{
						vPos.x -= 3.f;
						pPlayer->Set_Pos(vPos.x, vPos.y);
					}
					else
					{
						vPos.x += 3.f;
						pPlayer->Set_Pos(vPos.x, vPos.y);
					}

				}

				return true;
			}
			else                            // 현재 충돌중이지 않지만 이전에 한번이라도 충돌한 경우
			{
				pPlayer->SetCollsion(false);
				return false;
			}

		}
		break;
		case WILL_ATTACK_TYPE::ATTACK2:
		{
			fWidth = abs(playerInfo.fX - pMon->GetAttack2RangePos().x);
			fHeight = abs(playerInfo.fY - pMon->GetAttack2RangePos().y);

			fRadiusX = (playerInfo.fCX + pMon->GetAttack2RangeSize().x) * 0.5f;
			fRadiusY = (playerInfo.fCY + pMon->GetAttack2RangeSize().y) * 0.5f;


			if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
			{
				pPlayer->SetCollsion(true);
				float fHitDelay = pPlayer->GetHitDelay();

				if (fHitDelay == 1.5f)
				{
					pPlayer->SetFirstCollsion(true);
					pPlayer->SetHp(pPlayer->GetHp() - pMon->GetAttackInfo());

					if (pPlayer->GetHp() <= 0.f)
					{
						pPlayer->SetFakeDead(true);
					}
				}

				return true;
			}
			else
			{
				pPlayer->SetCollsion(false);
			}
		}
		break;
		default:
			break;
		}

	}

	return false;
}

bool CCollisionMgr::WillPage3_Colli(INFO playerInfo, CPlayer* pPlayer, CWill_Page1* pMon)
{
	if (pMon->GetAttacking())
	{
		float	fWidth(0);
		float	fHeight(0);

		float	fRadiusX(0);
		float	fRadiusY(0);


		switch (pMon->GetAttackType())
		{
		case WILL_ATTACK_TYPE::ATTACK1:
		{
			fWidth = abs(playerInfo.fX - pMon->GetAttackRangePos().x);
			fHeight = abs(playerInfo.fY - pMon->GetAttackRangePos().y);

			fRadiusX = (playerInfo.fCX + pMon->GetAttackRangeSize().x) * 0.5f;
			fRadiusY = (playerInfo.fCY + pMon->GetAttackRangeSize().y) * 0.5f;


			if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
			{
				pPlayer->SetCollsion(true);
				float fHitDelay = pPlayer->GetHitDelay();

				if (fHitDelay == 1.5f)
				{
					pPlayer->SetFirstCollsion(true);
					pPlayer->SetHp(pPlayer->GetHp() - pMon->GetAttackInfo());

					if (pPlayer->GetHp() <= 0.f)
					{
						pPlayer->SetFakeDead(true);
					}
				}

				return true;
			}
			else
			{
				pPlayer->SetCollsion(false);
			}

		}
		break;
		case WILL_ATTACK_TYPE::SKILL2:
		{
			int iFrm = pMon->GetAnimator()->GetCurAnimation()->GetFrame();

			if (pMon->GetAnimator()->GetCurAnimation()->GetAllFrame().size() - 5 == iFrm) // 마지막 애니메이션보다 하나 이전 프레임일때
			{
				INFO playerInfo = pPlayer->Get_Info();
				if (536.f > playerInfo.fY)
				{
					pPlayer->SetHp(0);
					pPlayer->SetFakeDead(true);
				}
			}
			
		}
		break;
		case WILL_ATTACK_TYPE::SKILL3:
		{
			int iFrm = pMon->GetAnimator()->GetCurAnimation()->GetFrame();

			if (pMon->GetAnimator()->GetCurAnimation()->GetAllFrame().size() - 5 == iFrm)
			{
				INFO playerInfo = pPlayer->Get_Info();
				if (536.f <= playerInfo.fY)
				{
					pPlayer->SetHp(0);
					pPlayer->SetFakeDead(true);
				}
			}	
		}
		break;

		default:
			break;
		}

	}

	return false;
}
