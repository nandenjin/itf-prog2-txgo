
/*

	This is a copy of GenericTimer provided at
	http://kanamori.cs.tsukuba.ac.jp/lecture/2017/prog2/

*/

#include <stdio.h>
#include "GenericTimer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef _WIN32
typedef union {
    struct {
        unsigned int LowPart;
        long HighPart;
    } u;
    _int64 QuadPart;
} StopLargeInteger;

static LARGE_INTEGER s_LastTimeStamp;
static StopLargeInteger s_ClockFreq;
#else
static struct timeval s_LastTimeStamp;
#endif

void StartTimer(void)
{
#ifdef _WIN32
	QueryPerformanceFrequency((LARGE_INTEGER*)&s_ClockFreq);
	QueryPerformanceCounter((LARGE_INTEGER*)&s_LastTimeStamp);
#else
	gettimeofday(&s_LastTimeStamp, NULL);
#endif
}

double GetTime(void)
{
#ifdef _WIN32
	LARGE_INTEGER newStamp;
	QueryPerformanceCounter(&newStamp);
	return 1000.0 * ((newStamp.QuadPart - s_LastTimeStamp.QuadPart)
		/(double)s_ClockFreq.QuadPart);
#else
	struct timeval newStamp;
	gettimeofday(&newStamp, NULL);

	return 1000.0 * (newStamp.tv_sec - s_LastTimeStamp.tv_sec)
		+ (newStamp.tv_usec - s_LastTimeStamp.tv_usec) / 1000.0;
#endif
}

double GetRapTime(double prevTime)
{
	return GetTime() - prevTime;
}


