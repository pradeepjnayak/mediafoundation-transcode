#include <iostream>

#include "Transcode.h"


int wmain(int argc, wchar_t* argv[])
{

	//Implement argument check
	if (argc < 2)
	{
		std::cout << "arguments not passed";
		return 1;
	}

	const WCHAR* sInputFile = argv[1];



	//(void)HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	HRESULT hr = S_OK;

	//Initialize COM to support worker queue 
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	
	if (SUCCEEDED(hr))
	{
		//initializes the Media Foundation platform.
		hr = MFStartup(MF_VERSION);
	}

	if (SUCCEEDED(hr))
	{
		CTranscoder transcoder;
		hr = transcoder.OpenFile(sInputFile);

		hr = transcoder.CreateTranscodeTopo();

	}

	MFShutdown();
	CoUninitialize();
}

