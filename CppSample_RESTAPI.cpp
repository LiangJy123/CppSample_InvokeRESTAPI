// This sample is for Invoking Rest API.
//
#pragma once
#include "pch.h"
#include <iostream>
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib,"Winhttp.lib")

int ReadFile(char *buffer, long & lSize);

int main()
{

	BOOL  bResults = FALSE;
	
	HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

	LPSTR pszOutBuffer = NULL;
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;

	char *buffer = NULL;
	long  lSize = 0;

	LPCWSTR host = L"<Input your host>"; // input your host here ,for example:  "southeastasia.api.cognitive.microsoft.com"

	hSession = WinHttpOpen(L"Cognitive Service API Test",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Connect an HTTPS server.  INTERNET_DEFAULT_HTTPS_PORT  means using 443 port. You can change to  INTERNET_DEFAULT_HTTP_PORT ,which can build an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, host,
			INTERNET_DEFAULT_HTTPS_PORT, 0);
	else
	{
		int err = GetLastError();
	}

	// Create an HTTPS Request.    WINHTTP_FLAG_SECURE means using SSL.  You can change to  0x0 ,when you connect to an HTTP server.
	if (hConnect)
		hRequest = WinHttpOpenRequest(
			hConnect,
			L"POST",
			L"<Input your content here>", //  In REST API , what content you write means what feature you choose , such as "/customvision/v3.0/Prediction/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/classify/iterations/Iteration1/image"
			NULL,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);
	else
	{
		DWORD err = GetLastError();
	}


	
	// Set Options , client without certificates. You can set other Options ,such as proxy, timeout and so on.
	BOOL bRet = WinHttpSetOption(hRequest, WINHTTP_OPTION_CLIENT_CERT_CONTEXT, WINHTTP_NO_CLIENT_CERT_CONTEXT, 0);

	if (hRequest)
		bResults = WinHttpAddRequestHeaders(hRequest, 
			L"Prediction-Key: <Input your key here>",   //other informations in the form when using http "post".  "Prediction-Key" is a field for MS Cognitive service REST API ,if you use other API,you should input their specific fields. 
			(ULONG)-1L,
			WINHTTP_ADDREQ_FLAG_ADD);

	if (hRequest)
		bResults = WinHttpAddRequestHeaders(hRequest,
			L"Content-Type: application/octet-stream",  //other informations in the form when using http "post",same explanation as the last step.For example: "Content-Type: application/octet-stream".
			(ULONG)-1L,
			WINHTTP_ADDREQ_FLAG_ADD);


	ReadFile(buffer, lSize);

	//Send the Request
	bResults = WinHttpSendRequest(hRequest,
		WINHTTP_NO_ADDITIONAL_HEADERS,
		0, buffer,
		lSize, lSize, 0);

	// Receive the Response
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);


	if (bResults)
	{
		do
		{
			// Verify.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				std::cout << "Error %u in WinHttpQueryDataAvailable.\n" << GetLastError();

			// new a space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				std::cout << pszOutBuffer; "Out of memory\n";
				dwSize = 0;
			}
			else
			{
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded));

				else
				{
					if (dwSize != 0)
					{
						std::cout << pszOutBuffer;
					}

				}

				// delete the memory .
				delete[] pszOutBuffer;
			}

		} while (dwSize > 0);
	
	}

		 //if get Errors,print them.
		if (!bResults)printf("Error %d has occurred.\n", GetLastError());
	
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}

		// Close handles.
		if (hRequest) WinHttpCloseHandle(hRequest);
		if (hConnect) WinHttpCloseHandle(hConnect);
		if (hSession) WinHttpCloseHandle(hSession);
		std::cout << "\n";
		system("pause");
}


int ReadFile(char *buffer, long & lSize)
{
	//Read Picture
	FILE *pFile = NULL;

	
	size_t result = 0;;


	pFile = fopen("SamplePicture.jpg", "rb");

	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);


	buffer = (char *)malloc(sizeof(char) * lSize);

	result = fread(buffer, 1, lSize, pFile);

	fclose(pFile);

	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
