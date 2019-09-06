#pragma once

#include <iostream>

#include <mfapi.h>
#include <mfidl.h>


template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*pT)->Release();
		*ppT = NULL;
	}
}



class CTranscoder
{
public:
	CTranscoder();
	~CTranscoder();
	HRESULT OpenFile(const WCHAR* pInputPath);

private:
	HRESULT Shutdown();
	IMFMediaSession* m_pSession;
	IMFMediaSource* m_pSource;

};