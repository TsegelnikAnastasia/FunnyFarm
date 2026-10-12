#include "SoundTest.h"
#ifdef _WIN32

extern "C" {
    __declspec(dllimport) int __stdcall PlaySoundA(
        const char* pszSound, void* hmod, unsigned long fdwSound);
}

const unsigned long SND_ASYNC = 0x0001;
const unsigned long SND_LOOP = 0x0008;
const unsigned long SND_FILENAME = 0x00020000L;
#endif

namespace SoundTest {

    int PlayFile(const string& path) {
#ifdef _WIN32
        return PlaySoundA(path.c_str(), NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP);
#else
        return 0;
#endif
    }
}