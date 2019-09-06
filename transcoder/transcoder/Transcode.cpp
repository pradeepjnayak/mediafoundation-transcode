#include "Transcode.h"


HRESULT CreateMediaSource(
	const WCHAR* pInputPath,
	IMFMediaSource** ppMediaSource);

CTranscoder::CTranscoder() : 
	m_pSession(NULL),
	m_pSource(NULL)
{


}


CTranscoder::~CTranscoder()
{
	//do media shut down and safe release of interfaces

	if (m_pSession)
	{
		m_pSession->Release();
	}

	if (m_pSource) {
		m_pSource->Release();
	}
}


HRESULT CTranscoder::Shutdown()
{
	return S_OK;
}


HRESULT CTranscoder::OpenFile(const WCHAR *pInputPath)
{
	
	if (!pInputPath)
	{
		return E_INVALIDARG;
	}
	HRESULT hr = S_OK;
	hr = CreateMediaSource(pInputPath, &m_pSource);
	//m_pSource->CreatePresentationDescriptor();

	return hr;
}


HRESULT CreateMediaSource(
	const WCHAR* pInputPath,
	IMFMediaSource** ppMediaSource
	)
{
	HRESULT hr = S_OK;
	IMFSourceResolver* pSourceResolver = NULL;

	MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;

	//to get pointers to other interfaces
	IUnknown* pUnkSource = NULL;

	hr = MFCreateSourceResolver(&pSourceResolver);

	if (SUCCEEDED(hr))
	{
		hr = pSourceResolver->CreateObjectFromURL(
			pInputPath,     //source path
			MF_RESOLUTION_MEDIASOURCE,   //create a media source.
			NULL,
			&ObjectType, //Defines the object types that are created by the source resolver
			&pUnkSource
		);
	}
	if SUCCEEDED(hr)
	{
		hr = pUnkSource->QueryInterface(IID_PPV_ARGS(ppMediaSource));
	}

	//SafeRelease(pUnkSource);
	pUnkSource->Release();
	pSourceResolver->Release();
	//SafeRelease(pSourceResolver);

	return hr;
}

