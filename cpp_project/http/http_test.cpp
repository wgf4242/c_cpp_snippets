#include <Windows.h>
#include <WinHttp.h>
#include <stdio.h>
#include <iostream> //getchar
#include <fstream>

#pragma comment(lib, "winhttp.lib")

using namespace std;

string GBKToUTF8(const char *strGBK);

std::wstring get_utf16(const std::string &str, int codepage) {
    if (str.empty()) return std::wstring();
    int sz = MultiByteToWideChar(codepage, 0, &str[0], (int) str.size(), 0, 0);
    std::wstring res(sz, 0);
    MultiByteToWideChar(codepage, 0, &str[0], (int) str.size(), &res[0], sz);
    return res;
}

string HttpsWebRequestPost(string domain, string url, string dat) {
    //Extra
    LPSTR data = const_cast<char *>(dat.c_str());;
    DWORD data_len = strlen(data);

    LPCWSTR additionalHeaders = L"Content-Type: application/x-www-form-urlencoded\r\n";
    DWORD headersLength = -1;


    wstring sdomain = get_utf16(domain, CP_UTF8);
    wstring surl = get_utf16(url, CP_UTF8);
    string response;

    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL bResults = FALSE;
    HINTERNET hSession = NULL,
            hConnect = NULL,
            hRequest = NULL;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example/1.0",
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME,
                           WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, sdomain.c_str(),
                                  INTERNET_DEFAULT_HTTP_PORT, 0);

    // Create an HTTP request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"POST", surl.c_str(),
                                      NULL, WINHTTP_NO_REFERER,
                                      WINHTTP_DEFAULT_ACCEPT_TYPES,
                                      0);

    // Send a request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
                                      additionalHeaders,
                                      headersLength,
                                      (LPVOID) data,
                                      data_len,
                                      data_len,
                                      0);;


    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Keep checking for data until there is nothing left.
    if (bResults) {
        do {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n",
                       GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer) {
                printf("Out of memory\n");
                dwSize = 0;
            } else {
                // Read the data.
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID) pszOutBuffer,
                                     dwSize, &dwDownloaded))
                    printf("Error %u in WinHttpReadData.\n", GetLastError());
                else
                    //printf("%s", pszOutBuffer);
                    response = response + string(pszOutBuffer);
                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
    }

    // Report any errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return response;

}

int main() {
    // http://pv.sohu.com/cityjson
    string domain = "pv.sohu.com";
    string url = "/cityjson";
    string d;
    const string &basicString = HttpsWebRequestPost(domain, url, d);
    std::cout << basicString << std::endl; // 1.乱码请使用GBK终端，
    // std::cout << GBKToUTF8(basicString.c_str()) << std::endl; // 2.或字符转UTF8 3. Clion设置为GBK
}

string GBKToUTF8(const char *strGBK) {
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    string strTemp = str;
    if (wstr) delete[] wstr;
    if (str) delete[] str;
    return strTemp;
}
