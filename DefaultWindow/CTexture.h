#pragma once
#include "CRes.h"

class CTexture : public CRes
{
public:
	CTexture();
	~CTexture();


public:
	HDC GetDC() { return m_DC; }

	UINT Width() { return m_BitInfo.bmWidth; }
	UINT Height() { return m_BitInfo.bmHeight; }
	
public:
	void Load(const wstring& _pPath);
	void Create(UINT _iWidth, UINT _iHeight);

public:
	void SetBf(BLENDFUNCTION _bf) { m_bf = _bf; }
	BLENDFUNCTION GetBf() { return m_bf; }




private:

	HDC			m_DC;
	HBITMAP		m_Bitmap;
	BITMAP		m_BitInfo;
	BLENDFUNCTION	 m_bf;


};

