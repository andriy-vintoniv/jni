#ifndef UNICODE
#define UNICODE
#endif

#include "HelloWorld.h"
#include "jni.h"
#include "stdio.h"
#include <windows.h>
#include <stdio.h>
#include "MyEventProvider.h"

#pragma comment(lib, "advapi32.lib")

#define PROVIDER_NAME L"MyEventProvider"

// Hardcoded insert string for the event messages.
CONST LPWSTR pBadCommand = L"The command that was not valid";
CONST LPWSTR pFilename = L"c:\\folder\\file.ext";
CONST LPWSTR pNumberOfRetries = L"3";
CONST LPWSTR pSuccessfulRetries = L"0";
CONST LPWSTR pQuarts = L"8";
CONST LPWSTR pGallons = L"2";


JNIEXPORT void JNICALL Java_HelloWorld_reportEvent(JNIEnv *env, jobject obj, jstring message)
{
	HANDLE hEventLog = NULL;
    LPWSTR pInsertStrings[2] = {NULL, NULL};
    DWORD dwEventDataSize = 0;

	const char *nativemessage = env->GetStringUTFChars(message, 0);
	
	const int size = strlen(nativemessage);
	wchar_t *wtext = new wchar_t[size];
	mbstowcs(wtext, nativemessage, strlen(nativemessage)+1);//Plus null


	LPWSTR ptr = wtext;

    // The source name (provider) must exist as a subkey of Application.
    hEventLog = RegisterEventSource(NULL, PROVIDER_NAME);
    if (NULL == hEventLog)
    {
        wprintf(L"RegisterEventSource failed with 0x%x.\n", GetLastError());
        goto cleanup;
    }

	env->ReleaseStringUTFChars(message, nativemessage);
    
    // This event uses insert strings.
    pInsertStrings[0] = ptr;
    pInsertStrings[1] = pGallons;
    if (!ReportEvent(hEventLog, EVENTLOG_INFORMATION_TYPE, UI_CATEGORY, MSG_COMPUTE_CONVERSION, NULL, 1, 0, (LPCWSTR*)pInsertStrings, NULL))
    {
        wprintf(L"ReportEvent failed with 0x%x for event 0x%x.\n", GetLastError(), MSG_COMPUTE_CONVERSION);
        goto cleanup;
    }

	if (!ReportEvent(hEventLog, EVENTLOG_WARNING_TYPE, UI_CATEGORY, MSG_COMPUTE_CONVERSION, NULL, 1, 0, (LPCWSTR*)pInsertStrings, NULL))
    {
        wprintf(L"ReportEvent failed with 0x%x for event 0x%x.\n", GetLastError(), MSG_COMPUTE_CONVERSION);
        goto cleanup;
    }

	
	if (!ReportEvent(hEventLog, EVENTLOG_ERROR_TYPE, UI_CATEGORY, MSG_COMPUTE_CONVERSION, NULL, 1, 0, (LPCWSTR*)pInsertStrings, NULL))
    {
        wprintf(L"ReportEvent failed with 0x%x for event 0x%x.\n", GetLastError(), MSG_COMPUTE_CONVERSION);
        goto cleanup;
    }
    wprintf(L"All events successfully reported.\n");

cleanup:

    if (hEventLog)
	{
        DeregisterEventSource(hEventLog);
	}

}