#include "stdafx.h"
#include "LineMgr.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CMonster.h"

#include "CKeyMgr.h"


#include <ctime>


CLineMgr*	CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	srand(time(NULL));
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float & fX, float& fY ,float *pY, float *pX )  // fX, fY�� Player ��ǥ 
{
	if (m_LineList.empty())
		return false;

	CLine*		pTargetLine = nullptr;
	CLine*		pDownTargetLine = nullptr;
	
	float fMinY = 999.f;


	list<CLine*>::iterator iter = m_LineList.begin();

	for (iter; iter != m_LineList.end(); ++iter)   // PushBack ������ ���� �켱���� ���� �޶��� �� ������ �����߰��Ѿְ� �츮�ʹݼ���
	{	
		if (fX >= (*iter)->Get_Info().tLPoint.fX &&
			fX <= (*iter)->Get_Info().tRPoint.fX)      // � ������ ��,�� x��ǥ ���̿� �ִٴ� ���̰�
		{
		
			float x1 = (*iter)->Get_Info().tLPoint.fX;
			float y1 = (*iter)->Get_Info().tLPoint.fY;
			float x2 = (*iter)->Get_Info().tRPoint.fX;
			float y2 = (*iter)->Get_Info().tRPoint.fY;

			
			*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			float fDiagonal = abs(*pY - fY);			// �����ǹ������� y��ǥ�� �� y��ǥ�� ���̰�
			
			// ������ 

			if (*pY >= fY)								// �׻� �� Y ��ǥ�� ������ Y ��ǥ���� ���� �־����
			{							
				if (!pTargetLine || fDiagonal < fMinY)
				{
					pDownTargetLine = pTargetLine; // ����... 

					fMinY = fDiagonal;
					pTargetLine = (*iter);
				}
	
			}
		}

	}

	


	if (!pTargetLine)
	{
		return false;
	}


	


	CPlayer* pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
	if (pPlayer->m_bDownJump && pDownTargetLine)
		pTargetLine = pDownTargetLine;


	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;
	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;
	
	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

bool CLineMgr::Collision_LineMonster(CMonster* _p , float& fX, float& fY, float* pY, float* pX)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	float fMinY = 0.f;

	for (auto& iter : m_LineList)   // PushBack ������ ���� �켱���� ���� �޶��� �� ������ �����߰��Ѿְ� �츮�ʹݼ���
	{
		if (fX >= iter->Get_Info().tLPoint.fX &&
			fX <= iter->Get_Info().tRPoint.fX)      // � ������ ��,�� x��ǥ ���̿� �ִٴ� ���̰�
		{
			float x1 = iter->Get_Info().tLPoint.fX;
			float y1 = iter->Get_Info().tLPoint.fY;
			float x2 = iter->Get_Info().tRPoint.fX;
			float y2 = iter->Get_Info().tRPoint.fY;


			*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			float fDiagonal = abs(*pY - fY); // �����ǹ������� y��ǥ�� �� y��ǥ�� ���̰�

			if (*pY >= fY)					 // �׻� �� Y ��ǥ�� ������ Y ��ǥ���� ���� �־����
			{
				if (!pTargetLine || fDiagonal < fMinY)  // �׶� �Ÿ��� ���� ���� ������ �� Target Line
				{
					fMinY = fDiagonal;
					pTargetLine = iter;
				}
			}
		}

	}

	if (!pTargetLine)
	{
		return false;
	}



	
	//if (_p)
	//{
	//	_p->SetPreLine(pTargetLine);
	//
	//	pTargetLine = _p->GetPreLine();
	//}


	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;
	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;


	   // 22  ~  511 
	if (*pX == 0.f || _p->GetArrival() &&  _p->m_fMoveDelay <= 0.f )
	{
		*pX = rand() % int(x2);

		float fDistance = (x2 - x1);

		if (*pX < fDistance)
			*pX += x1;
		else if (*pX + fDistance < x2)
			*pX += fDistance;




		_p->m_fMoveDelay = 1.f;
	}
		

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;



	return true;
}

bool CLineMgr::Collision_Wall(CObj* pObj)
{
	for (auto& iter : m_LineList)
	{
		if (iter->Get_LineType() == LINETYPE::WALL)
		{
			//if ((pObj->Get_Info().fCX / 2.f) >= pObj->Get_Info().fX - iter->Get_Info().tLPoint.fX )
			//{
			//	pObj->Set_PosX(abs(iter->Get_Info().tLPoint.fX - pObj->Get_Info().fX)); // ��:�� _ ��:Player
			//}
			//else if ((pObj->Get_Info().fCX / 2.f) >= iter->Get_Info().tRPoint.fX - pObj->Get_Info().fX)
			//{
			//	pObj->Set_PosX( -abs(iter->Get_Info().tRPoint.fX - pObj->Get_Info().fX)); // ��:Player _ ��:��
			//}

		}
	}



	return false;
}

bool CLineMgr::Collisiong_DownRopeLine(CObj* pObj, float* fY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_LineType() == LINETYPE::ROPE)
		{
			INFO playerInfo = pObj->Get_Info();
			LINE LineInfo = iter->Get_Info();


			if (LineInfo.tLPoint.fY >= playerInfo.fY - (playerInfo.fCY / 2.f)
				&& LineInfo.tRPoint.fY <= playerInfo.fY + (playerInfo.fCY / 2.f)
				&& LineInfo.tLPoint.fX - 5 > playerInfo.fX - (playerInfo.fCX / 2.f)
				&& LineInfo.tRPoint.fX + 5 < playerInfo.fX + (playerInfo.fCX / 2.f))
			{
				pObj->Set_Pos(LineInfo.tRPoint.fX, playerInfo.fY);
				pTargetLine = iter;
			}
		}
	}


	if (!pTargetLine)
		return false;

	*fY = pTargetLine->Get_Info().tLPoint.fY;

	return true;
}


bool CLineMgr::Collisiong_UpRopeLine(CObj* pObj , float* fY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_LineType() == LINETYPE::ROPE)
		{
			INFO playerInfo = pObj->Get_Info();
			LINE LineInfo = iter->Get_Info();


			if (LineInfo.tLPoint.fY > playerInfo.fY - (playerInfo.fCY / 2.f)
				&& LineInfo.tRPoint.fY <= playerInfo.fY 
				&& LineInfo.tLPoint.fX - 5 > playerInfo.fX - (playerInfo.fCX / 2.f)
				&& LineInfo.tRPoint.fX + 5 < playerInfo.fX + (playerInfo.fCX / 2.f))
			{
				pObj->Set_Pos(LineInfo.tRPoint.fX, playerInfo.fY);
				pTargetLine = iter;
			}
		}
	}


	if (!pTargetLine)
		return false;

	*fY = pTargetLine->Get_Info().tRPoint.fY;

	return true;
}


void CLineMgr::Initialize(SCENE_TYPE _e)
{
	list<CLine*>::iterator iterTarget = m_LineList.begin();

	float fTargetY = (*iterTarget)->Get_Info().tRPoint.fY;

	for (list<CLine*>::iterator iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		float fIter = (*iter)->Get_Info().tRPoint.fY;

		if (fTargetY < fIter)
		{
			fTargetY = (*iter)->Get_Info().tRPoint.fY;
			iterTarget = iter;
		}
		
	}
	
	(*iterTarget)->Set_LineType(LINETYPE::FLOOR);
}

int CLineMgr::Update()
{

	return 0;
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}


//void CLineMgr::Save_Line()
//{
//}


void CLineMgr::Load_Lobby_Line()
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Lobby_Line.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("������� ���� ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("��������� Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_Hunting1_Line()    // ����� ���� ���� �ȴ�
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Hunting_Line.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("������� ����� ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("������� ����� Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_Hunting2_Line()
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Hunting2_Line.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("������� ��������� ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("������� ��������� Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_BossLobby_Line()
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Boss_Lobby.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("���� �κ� ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("���� �κ� Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_BossPage1_Line()
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Boss_Page1.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("���� 1 Page ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}
	
	Safe_Delete(*m_LineList.begin());			   // �� �� ���� ����
	m_LineList.erase(m_LineList.begin());		   // �� �� ���� ����


	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("���� 1 Page Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_BossPage2_Line()
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Boss_Page2.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("���� 2 Page ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("���� 2 Page Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_BossPage3_Line()
{
	HANDLE hFile = CreateFile(L"../API/Map/Line/Boss_Page3.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("���� 3 Page ���� Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("���� 3 Page Line Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_HENESIS2_Line()    
{
	HANDLE hFile = CreateFile(L"../Data/test/Henesis2.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_HENESIS3_Line()
{
	HANDLE hFile = CreateFile(L"../Data/test/Henesis3.dat",		// ���� ���(�̸��� ����)
		GENERIC_READ,			// ���� ���� ���(GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ������� �����ϰ��� �� �� ����� ���� ���� ����(NULL�� ��� �������� ����)
		NULL,					// ���� ���(NULL�� ��� �⺻ ���� ����)
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ������ ����, ������ �����), (OPEN_EXISTING : ������ ���� ���� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�ƹ��� Ư�� �Ӽ��� ���� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ��� ���ϱ� ������ NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// ���� ó�� ����
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}


bool CLineMgr::Collision_Line_WALL(float& fX, float& fY, float* pX, float* pY)
{
	CLine* pTargetLine = nullptr;
	float YDistance = 0.f;

	if (m_LineList.empty())
		return false;

	for (auto& iter : m_LineList)
	{
		float x1 = iter->Get_Info().tLPoint.fX;
		float y1 = iter->Get_Info().tLPoint.fY;
		float x2 = iter->Get_Info().tRPoint.fX;
		float y2 = iter->Get_Info().tRPoint.fY;

		if (fX + PLAYER_CX >= x1 &&
			fX - PLAYER_CX <= x2
			&& iter->Get_LineType() == LINETYPE::WALL)
		{



			//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;  // �ĺ� 4�� 
			*pY = y1;  // �ĺ� 4�� 
			float fDiagonal = abs(*pY - fY - PLAYER_CX * 0.5f);  //�÷��̾� CX ������ ,25
			if (fY <= y1 && fY >= y2)
			{
				if (*pY > fY - PLAYER_CX * 0.5f)
				{
					if (!pTargetLine || YDistance > fDiagonal)
					{
						YDistance = fDiagonal;
						pTargetLine = iter;
					}
				}
			}

		}
	}

	if (!pTargetLine)
		return false;




	float x1_Target = pTargetLine->Get_Info().tLPoint.fX;
	float y2_Target = pTargetLine->Get_Info().tRPoint.fY;
	//float /*y1 = pTargetLine->Get_Info().tLPoint.fY;
	//float */x2 = pTargetLine->Get_Info().tRPoint.fX;


	*pX = x1_Target;

	return true;

}