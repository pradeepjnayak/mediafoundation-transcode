#include <mfapi.h>
#include <mfreadwrite.h>
#include <mfidl.h>

class MTranscoder
{
    public:
        static HRESULT CreateInstance(MTranscoder **ppMTrancoder);
        
        HRESULT Transcode(LPCWSTR wszSourceFile, LPCWSTR wszTargetFile);

        HRESULT SetStartPosition(LONGLONG llStarTime);

        HRESULT SetDuration(ULONGLONG ullDuration);

        HRESULT SetTargetAudioFormat();

        HRESULT SetTargetVideoFormat();

        HRESULT SetVideoFrameSize();

        DWORD GetStreamCount();

    
    private:

        MTranscoder();
        ~MTranscoder();

    private:
        LPCWSTR m_wszSourceFile;
        LPCWSTR m_wszTargetFile;
        
        IMFSourceReader *m_pSourceReader;


        // Trim info
        struct TrimInfo
        {
            LONGLONG llStartTime;
            LONGLONG llStopTime;
        } m_TrimTime;

}