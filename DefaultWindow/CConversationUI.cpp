#include "stdafx.h"
#include "CConversationUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"

#include "CConversationBtn.h"

#include "MainGame.h"
#include "CNpc.h"
#include "CQuest.h"

#include "CSound.h"

#include "CSixEffect.h"

CConversationUI::CConversationUI()
    : m_pInteractionObj(nullptr)
	, m_iCount(0)
	, m_pRenderTex(nullptr)
{
	m_pNpcTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"NPC_FACE", L"../API/UI/rain_talk.png");
	m_pPlayerTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"PLAYER_FACE", L"../API/UI/player_talk.png");

	m_pRenderTex = m_pPlayerTex;


	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	SetBf(bf);

	m_vecText.reserve(10);
}

CConversationUI::~CConversationUI()
{
	Release();
}

void CConversationUI::Initialize(NPC_TYPE _e)
{
	m_tInfo = { WINCX / 2.f  , WINCY / 2.f   , 520.f ,200.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::CONVERSATION;
	
	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"TALKUI", L"../API/UI/NPC_TALK.png");


	CPlayerUI* pUIBtn = new CConversationBtn;
	pUIBtn->SetParentUI(this);
	pUIBtn->Initialize();
	m_childUI_List.push_back(pUIBtn);


	m_eActionType = _e;
	switch (m_eActionType)
	{
	case NPC_TYPE::TALK:
	{
		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"rain_voice");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
		pNewSound1->SetVolume(90.f); // �Ҹ� ���� ũ��

		m_iMaxCount = 9;
		m_vecText.push_back(make_pair(L" ��..? ��� �����..", 0));
		m_vecText.push_back(make_pair(L" �������� ���� �����ް� �־��.",1));
		m_vecText.push_back(make_pair(L" '��' �̶�� ���簡 �ſ� ���� �ӿ� ���� ���� ���� ���̿���.", 1));
		m_vecText.push_back(make_pair(L" �׸� óġ�Ϸ��� ���� ���� ����?!", 0));
		m_vecText.push_back(make_pair(L" '��' �� ������� �� �� �ſ��� ���� ���� �� �־��.", 1));

		m_vecText.push_back(make_pair(L" ������ ���� �׿��� �ٰ����� ����� ������..\n\n ���� ������ �ӹ��� �ϼ��ϸ� �׿��� �����帱�Կ�.", 1));
		m_vecText.push_back(make_pair(L" � �ͺ��� �ϸ� �ɱ��?", 0));
		m_vecText.push_back(make_pair(L" �켱 ������ ������ ���� ������ ������ ������.", 1));
		m_vecText.push_back(make_pair(L" �� ��, 'I' Ű�� ���� \n\n �Һ�â���� ������ 1�� �� ���Կ� ��ġ�ϼ���.", 1));
	}
	break;
	case NPC_TYPE::BOSS_SIGN:
	{
		m_iMaxCount = 2;
		m_vecText.push_back(make_pair(L"�� �ʸӿ� ���� ������ �� ����..",0));
		m_vecText.push_back(make_pair(L"�׸� óġ�Ϸ� ����.",0));
	}
		break;
	case NPC_TYPE::NPC_TYPE_END:
		break;
	default:
		break;
	}
}


int CConversationUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bActivate)
	{
		if (m_iMaxCount == m_iCount)
		{
			StartAction();
			m_bActivate = false;
			return OBJ_NOEVENT;
		}

		if (m_vecText[m_iCount].second == 0)
		{
			m_pRenderTex = m_pPlayerTex;
		}
		else
			m_pRenderTex = m_pNpcTex;



		__super::Update_Rect();

		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Update();


		return OBJ_NOEVENT;
	}

	
}

void CConversationUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();


		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Late_Update();
	}

}

void CConversationUI::Render(HDC hDC)
{
	if (m_bActivate)
	{
		AlphaBlend(hDC
			, m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
			, m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
			, m_tInfo.fCX							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
			, m_tInfo.fCY
			, m_pUITex->GetDC()
			, 0								// ������ �̹����� ������ġ
			, 0
			, m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
			, m_pUITex->Height()
			, this->GetBf());



		RECT rt = {
		  m_tRect.left + 200.f							// ��ȭâ ������ 1000 x 210�� 
		, m_tRect.top + 50.f
		, m_tRect.right - 50.f
		, m_tRect.bottom - 30.f
		};


		if (m_iMaxCount > m_iCount)
			DrawTextW(hDC
				, m_vecText[m_iCount].first.c_str()				// ������ ������
				, -1
				, &rt
				, DT_LEFT | DT_WORDBREAK);




		AlphaBlend(hDC
			, m_tRect.left + 35.f					// ( ������ġ )						// �̹����� ����� x
			, m_tRect.top + 30.f		            // ( ������ġ )						// �̹����� ����� y
			, 100									// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
			, 100
			, m_pRenderTex->GetDC()
			, 0										// ������ �̹����� ������ġ
			, 0
			, m_pRenderTex->Width() 				// �߶� ũ��ϱ� �׻� 800 �̿�����
			, m_pRenderTex->Height()
			, this->GetBf());





		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Render(hDC);
	}

}

void CConversationUI::Release()
{
	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();
}

void CConversationUI::MouseLBtnDown()
{
}

void CConversationUI::MouseLBtnUp()
{
}

void CConversationUI::MouseClick()
{
}

void CConversationUI::MouseOn()
{
}

void CConversationUI::MouseOut()
{
}

void CConversationUI::StartAction()		// ��ȭ�� ������ ȣ��Ǵ� �Լ��� 
{
	switch (m_eActionType)
	{
	case NPC_TYPE::TALK:
	{
		// ���° ��ȭ������ ���� �б�ó�� �ؾ��ϰ�
		static UINT iQuest = (UINT)QUEST_TYPE::PORTIONBUY_DRAG;

		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"quest");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
		pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��
		m_iCount = 0;

		CQuest* pQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();		
		if (pQuest->IsSuccess())
		{
			pQuest->SetCurQuest((QUEST_TYPE)++iQuest);
		}
		else
		{
			// ����Ʈ �������޴µ� �ٽ� ��ȭ�ǰ��
		}
		pQuest->SetState(QUEST_STATE::PROCEED);

		if (QUEST_TYPE::KILL_WILL == (QUEST_TYPE)iQuest)
			ChangeScene(BOSS_LOBBY);
		else if (QUEST_TYPE::MINIGAME == (QUEST_TYPE)iQuest)
			ChangeScene(MINIGAME);
		else if (QUEST_TYPE::TICKSIX == (QUEST_TYPE)iQuest)
		{
			CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Appear");
			pNewSound->Play(false);
			pNewSound->SetPosition(1.f); // ��з� , �Ҹ���ġ
			pNewSound->SetVolume(75.f); // �Ҹ� ���� ũ��

			CSixEffect* pSixEffect = new CSixEffect;
			pSixEffect->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_EFFECT, pSixEffect);		// ���ð� ������ �˾Ƽ� ������
		}
		else if (QUEST_TYPE::PETBUY_ACTIVE == (QUEST_TYPE)iQuest)
		{
			m_pPlayer->SetMeso(10000);
		}

		else if (QUEST_TYPE::WEARINGPARTS == (QUEST_TYPE)iQuest)
			m_pPlayer->SetMeso(50000);

		else if (QUEST_TYPE::EMD == (QUEST_TYPE)iQuest)
		{
			list<CObj*>& npcList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_NPC);
			for (auto& iter : npcList)
				iter->Set_Dead();

			list<CObj*>& backList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BACKGROUD);
			for (auto& iter : backList)
				iter->Set_Dead();

			CCamera::CreateSingleTonInst()->SetEnd(true);
		}
			

	}
		break;
	case NPC_TYPE::STORE:
		break;
	case NPC_TYPE::BOSS_SIGN:
		ChangeScene(BOSS_PAGE1);
		break;
	case NPC_TYPE::NPC_TYPE_END:
		break;
	default:
		break;
	}
}

void CConversationUI::SetReText()
{
	m_vecText.clear();


	CQuest* pQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();
	       
	switch (pQuest->GetCurQuest())   // ���� ����Ʈ�� ��ȭ�� ������ �ٷ� �ο��� �̹�
	{
	case QUEST_TYPE::PORTIONBUY_DRAG:
	{
		m_iMaxCount = 2;
		m_vecText.push_back(make_pair(L" ���ϼ̾��,\n\n �̹��� ���� 1�� �޼Ҹ� �帱�Կ�.", 1));
		m_vecText.push_back(make_pair(L" �̰ɷ� ���� �ϳ� �����Ͻð�,\n\n ���� Ŭ���ϼż� ��ȯ�� ������.", 1));
	}
		break;

	case QUEST_TYPE::PETBUY_ACTIVE:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" ���ϼ̾��,\n\n ���� ���͸� ����ϰ� ������ ��������\n �ڵ����� �Ծ��ִ� ������ �ϰԵ� �ſ���.", 1));
		m_vecText.push_back(make_pair(L" ��! �˰ڽ��ϴ�.. ������ �� �ϸ� �������?", 0));
		m_vecText.push_back(make_pair(L" ' P ' Ű�� ������ ����â�� Ȯ���غ��ð� �ɷ�ġ�� ����غ�����.", 1));
	}	
		break;
	case QUEST_TYPE::TICKSTAT:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" ����� ������̹Ƿ� �ֿ� �ɷ�ġ�� 'STR (��)'�� �÷��� �ؿ�.", 1));
		m_vecText.push_back(make_pair(L" ������ ������ ���� 'STR (��)'�� �ø��� �־��.", 1));
		m_vecText.push_back(make_pair(L" �������δ� ' O ' Ű�� ���� ��罺ų�� Ȱ��ȭ�ϼ���.", 1));
	}
		break;
	case QUEST_TYPE::TICKSKILL:
	{
		m_iMaxCount = 8;
		m_vecText.push_back(make_pair(L" ��ų�� �� 6������. �� ��ų�� Q,W,R,A,S Ű�� ��ȣ�ۿ��ؿ�.", 1));
		m_vecText.push_back(make_pair(L" ��ų���� ������ �����̸� �����ϸ�, ��ų�ɷ��� �޶��.", 1));
		m_vecText.push_back(make_pair(L" �׸���, ��ų�� ��ø�ؼ� ����Ҽ� �����.", 1));
		m_vecText.push_back(make_pair(L" ���������� �̵� ��ų�� 'D (����)' Ű��\n �� �� �������� �����ø� �ߵ��ſ�.", 1));
		m_vecText.push_back(make_pair(L" ( Ű�� �������� ��ų�� Ȯ���ؾ߰ڴ�.. )", 0));
		m_vecText.push_back(make_pair(L" ' Y ' Ű�� ���� ������ȿ���� �ٸ��� �ټ��� �־��.\n\n ���Ͻô� ȿ���� �����غ�����.", 1));
		m_vecText.push_back(make_pair(L" ���� �����ʿ� �ִ� ��Ż�� Ÿ�� ����ͷ� ������.", 1));
		m_vecText.push_back(make_pair(L" �װ����� 9������ �޼����� ���ƿ�����.", 1));
	}
		break;
	case QUEST_TYPE::HUNTING1:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" �� ���� ������ �� ���̳׿�!", 1));
		m_vecText.push_back(make_pair(L" �� ���꿡�� ������ �Ҹ��� ����µ�.. \n\n ���� Ȯ���� �ֽ� �� ����?", 1));
		m_vecText.push_back(make_pair(L" ��..!", 0));
	}
		break;

	case QUEST_TYPE::MINIGAME:			// �̴ϰ��� ������ ��ȭ �ɾ����� ������ �ؽ�Ʈ�ϱ�
	{
		m_iMaxCount = 6;
		m_vecText.push_back(make_pair(L" �װ����� ���� ���� �ִ�����? \n\n ��ź�� ������ �Ҹ� ���Ҵµ�..", 1));
		m_vecText.push_back(make_pair(L" ... ��ź�� �°� �Դ°ɿ�..", 0));
		m_vecText.push_back(make_pair(L" �� �׾����� �ƾ��. \n\n ��� ������ 6����ų�� �帱�Կ�.", 1));
		m_vecText.push_back(make_pair(L" �� ���� ���� �ڰ��� �ȰͰ��׿�.", 1));
		m_vecText.push_back(make_pair(L" ( ..�˼����±�п� ���� ��ģ�� )", 0));
		m_vecText.push_back(make_pair(L" ' X ' Ű�� ������ ����Ҽ��־�� \n\n �ѹ� ����غ�����.", 1));
	}
	break;

	case QUEST_TYPE::TICKSIX:
	{
		m_iMaxCount = 5;
		m_vecText.push_back(make_pair(L" �� ���� ����Ϸ� �����ž߰���?", 1));
		m_vecText.push_back(make_pair(L" �̹��� ���� ��Ż�� Ÿ�� ����ͷ� ��������!", 1));
		m_vecText.push_back(make_pair(L" �װ��� �� ���� ���͵��� �����ؿ�!", 1));
		m_vecText.push_back(make_pair(L" (... ��ƴ�� ����..)", 0));
		m_vecText.push_back(make_pair(L" (... ������ ���� �Һ��� �� ����..)", 0));
	}
	break;

	case QUEST_TYPE::HUNTING2:
	{
		m_iMaxCount = 7;
		m_vecText.push_back(make_pair(L" �����ϼ̱���!", 1));
		m_vecText.push_back(make_pair(L" 'ī������' �� ��� �� ������� ũ���� �� ������..", 1));
		m_vecText.push_back(make_pair(L" ���ڱ� ���ͼ� ����.. \n\n ����Ʈ ���Ͱ� ���´ٴ� ����..�����ݾƿ�", 0));
		m_vecText.push_back(make_pair(L" ��Ƴ��������� ����, \n\n �� ���� �Ƿ��̸� '��' ���� �¼� �� ���� �� ���ƿ�.", 1));
		m_vecText.push_back(make_pair(L" ������ ��� �������� �ʰ� �Ǹ����� �� �� ����.", 1));
		m_vecText.push_back(make_pair(L" ���� 5�� �޼Ҹ� �帱�Կ�, �������� ��� �����ϼ���.", 1));
		m_vecText.push_back(make_pair(L" �� �� ' U ' Ű�� ���� ���â������, \n\n �������� �巡���Ͽ� ������ ������. \n\n �κ��丮���� ������ ��ġ�� ������ ���� �ִ�ϴ�.", 1));
	}
		break;
	case QUEST_TYPE::WEARINGPARTS:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" ���ϼ̾��! ���� '��' ���� �����帱�Կ� \n\n �غ�Ǽ���?", 1));
		m_vecText.push_back(make_pair(L" ��", 0));
		m_vecText.push_back(make_pair(L" ������ ���ƿ�����!", 1));
	}
		break;

	case QUEST_TYPE::KILL_WILL:
	{
		m_iMaxCount = 1;
		m_vecText.push_back(make_pair(L" �ÿ�ȸ �� ^^", 0));
	}
		break;

	default:
		break;
	}

}
