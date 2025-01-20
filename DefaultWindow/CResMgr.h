#pragma once
#include "Define.h"


class CRes;
class CTexture;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CRes*> m_mapTex;
	map<wstring, CRes*> m_mapSound;



public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);  // ���ϴ� png ������ �ҷ����� ��
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);    // ����� �ؽ��� �� �ؽ��� ����� ��
	CTexture* FindTexture(const wstring& _strKey);



	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
};

