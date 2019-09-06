#include "Transcode.h"



CTranscoder::CTranscoder() : 
	m_pSession(NULL)
{


}


CTranscoder::~CTranscoder()
{
	//do media shut down and safe release of interfaces

}


HRESULT CTranscoder::Shutdown()
{

}


HRESULT CTranscoder::OpenFile(const WCHAR* pInputPath)
{
	if (!pInputPath)
	{
		return E_INVALIDARG;
	}


	

}