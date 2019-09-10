#include "Transcode.h"


HRESULT CreateMediaSource(
	const WCHAR* pInputPath,
	IMFMediaSource** ppMediaSource);

CTranscoder::CTranscoder() : 
	m_pSession(NULL),
	m_pSource(NULL),
	m_pPresentation(NULL),
	m_pStreamDesc(NULL),
	m_pTopology(NULL)
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
	if (m_pTopology)
	{
		m_pTopology->Release();
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

	if (SUCCEEDED(hr))
	{
		m_pSource->CreatePresentationDescriptor(&m_pPresentation);
	}


	DWORD cStreams = 0;
	BOOL fSelected = false;

	hr = m_pPresentation->GetStreamDescriptorCount(&cStreams);

	if (FAILED(hr)) {
		return hr;
	}

	for (DWORD iStream = 0; iStream < cStreams; iStream++)
	{
		hr = m_pPresentation->GetStreamDescriptorByIndex(iStream, &fSelected, &m_pStreamDesc);

	}


	
	return hr;
}

HRESULT CTranscoder::CreateTranscodeTopo()
{
	//Create topology
	HRESULT hr = S_OK;
	hr = MFCreateTopology(&m_pTopology);

	if (FAILED(hr)) {
		goto done;
	}


	hr = CTranscoder::AddSourceNode(m_pTopology, m_pSource, m_pPresentation, m_pStreamDesc, &ppNode);


done:
	{
		SafeRelease(&m_pTopology);
	}
	return hr;
}


HRESULT CTranscoder::AddSourceNode(IMFTopology * m_pTopology,  //Topology 
	                               IMFMediaSource * m_pSource, //Media source.
	                               IMFPresentationDescriptor * pPD,  //Presentation descriptor.
	                               IMFStreamDescriptor * pSD, //Stream descriptor.
	                               IMFTopologyNode ** ppNode)  //Receives the node pointer
{
	IMFTopologyNode *pNode = NULL;

	HRESULT hr = S_OK;
	hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &pNode);

	if (FAILED(hr)) {
		goto done;
	}


	//set attributes
	pNode->SetUnknown(MF_TOPONODE_SOURCE, m_pSource);


	pNode->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, pPD);

	pNode->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, pSD);

	//check weather to add mark in here?


	hr = m_pTopology->AddNode(pNode);

	return hr;
done:
	{
		SafeRelease(&pNode);
	}
	

}

HRESULT CTranscoder::AddDestNode(IMFTopology * m_pTopology, IMFStreamSink * pStreamSink, IMFTopologyNode ** ppNode)
{

	HRESULT hr = S_OK;

	IMFTopologyNode* pNode = NULL;

	hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &pNode);

	if (SUCCEEDED(hr))
	{
		hr = m_pTopology->AddNode(pNode);
	}

}

HRESULT CTranscoder::ConfigureVideoAttributes()
{
	IMFAttributes* pVideoAttributes = NULL;

	HRESULT hr = S_OK;

	hr = MFCreateAttributes(&pVideoAttributes, 3);

	if (SUCCEEDED(hr))
	{
		hr = pVideoAttributes->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_WMV3);
		hr = MFSetAttributeRatio(pVideoAttributes, MF_MT_FRAME_RATE, 30, 1);
	}


	if (pVideoAttributes)
	{
		SafeRelease(&pVideoAttributes);
	}

	

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


