#include <Windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <iostream>
#pragma comment (lib,"winhttp.lib")

#include "common.h"

std::string WINHTTP_POST(LPCWSTR host,LPCWSTR path)
{
	std::string error = "ERROR";
	return error;
}

std::string WINHTTP_GET(LPCWSTR host,LPCWSTR path)
{
	std::string buffer;
	std::string error = "ERROR";
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL bResults = FALSE;
	HINTERNET hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;
	
	hSession = WinHttpOpen(L"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_5_8) AppleWebKit/534.31 (KHTML, like Gecko) Chrome/13.0.748.0 Safari/534.31",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession)
		hConnect = WinHttpConnect(hSession, (LPCWSTR)host,
			INTERNET_DEFAULT_HTTPS_PORT, 0);
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", path,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS, 0,
			WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	if (bResults)
	{
		do
		{
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				return error;
			pszOutBuffer = (char*)malloc(dwSize + 1);
			if (!pszOutBuffer)
			{
				return error;
				dwSize = 0;
			}
			else
			{
				ZeroMemory(pszOutBuffer, dwSize + 1);
				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
					return error;
				else
					buffer += pszOutBuffer;
				free(pszOutBuffer);
			}
		} while (dwSize > 0);
	}
	if (!bResults)
		return error;
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
	return buffer;
}