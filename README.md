# CppSample_InvokeRESTAPI
![](https://img.shields.io/badge/C%2B%2B-VS2017-blue.svg)



## What Is This?
#### This example shows how to access HTTPS type REST services in C++ programming.

## How to do?
 
1. Input the host you want to access.
   ```C++
   LPCWSTR host = L"<Input your host>"; // input your host here ,for example:  "southeastasia.api.cognitive.microsoft.com"
   ```
2. Iput the content.
   ```C++
   hRequest = WinHttpOpenRequest(
			hConnect,
			L"POST",
			L"<Input your content here>", //  In REST API , what content you write means what feature you choose , such as "/customvision/v3.0/Prediction/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/classify/iterations/Iteration1/image"
			NULL,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);
   ```
3. Input the form data that you want send to, such as.
   ```C++
   	if (hRequest)
		bResults = WinHttpAddRequestHeaders(hRequest,
			L"Content-Type: application/octet-stream",  //other informations in the form when using http "post".For example: "Content-Type: application/octet-stream".
			(ULONG)-1L,
			WINHTTP_ADDREQ_FLAG_ADD);
   ```
### You can run the progamm now.

## Tips

1. Selet HTTP or HTTPS .
   - HTTP:
   ```c++
   hConnect = WinHttpConnect(hSession, host,INTERNET_DEFAULT_HTTP_PORT, 0);
   ```
   - HTTPS:
   ```c++
    hConnect = WinHttpConnect(hSession, host,INTERNET_DEFAULT_HTTPS_PORT, 0);
   ```
2. Selet using SSL or not.
   - Enable(When using HTTPS):
   ```C++
	hRequest = WinHttpOpenRequest(
			hConnect,
			L"POST",
			L"<Input your content here>", //  In REST API , what content you write means what feature you choose , such as "/customvision/v3.0/Prediction/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/classify/iterations/Iteration1/image"
			NULL,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);
   ```
   - Disable(When using HTTP):
   ```C++
	hRequest = WinHttpOpenRequest(
			hConnect,
			L"POST",
			L"<Input your content here>", //  In REST API , what content you write means what feature you choose , such as "/customvision/v3.0/Prediction/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/classify/iterations/Iteration1/image"
			NULL,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			0);
   ```



## Result:
![](ReadmePicture.png)