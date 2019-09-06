#pragma once

#include <mfapi.h>
#include <mfidl.h>

class CTranscoder
{
public:
	CTranscoder();
	~CTranscoder();
	HRESULT OpenFile(const WCHAR* pInputPath);

private:
	HRESULT Shutdown();
	IMFMediaSession* m_pSession;

};