#pragma once

#include <iostream>

#include <mfapi.h>
#include <mfidl.h>


template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}



class CTranscoder
{
public:
	CTranscoder();
	~CTranscoder();
	HRESULT OpenFile(const WCHAR* pInputPath);
	HRESULT CreateTranscodeTopo();

	HRESULT AddSourceNode(IMFTopology *pTopology, IMFMediaSource *m_pSource, IMFPresentationDescriptor *pPD, IMFStreamDescriptor *pSD, IMFTopologyNode **ppNode);

	HRESULT AddDestNode(IMFTopology *pTopology, IMFStreamSink *pStreamSink, IMFTopologyNode **ppNode);

	HRESULT ConfigureVideoAttributes();

private:
	HRESULT Shutdown();
	IMFMediaSession* m_pSession;
	IMFMediaSource* m_pSource;
	IMFTopologyNode* ppNode;

	IMFPresentationDescriptor *m_pPresentation;
	IMFStreamDescriptor *m_pStreamDesc;

	IMFTopology *m_pTopology;
};