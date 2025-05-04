#include <Windows.h>
#include <gdiplus.h>
#pragma comment (lib, "gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0; // number of image encoders
    UINT size = 0; // size of the image encoder array in bytes

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1; // failure

    Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1; // failure

    Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j; // success
        }
    }

    free(pImageCodecInfo);
    return -1; // failure
}

int SaveJpeg(HBITMAP hBmp, LPCWSTR lpszFilename)
{
    ULONG* pBitmap = NULL;
    CLSID imageCLSID;
    Gdiplus::EncoderParameters encoderParams;
    int iRes = 0;

    typedef Gdiplus::Status(WINAPI* pGdipCreateBitmapFromHBITMAP)(HBITMAP, HPALETTE, ULONG**);
    pGdipCreateBitmapFromHBITMAP lGdipCreateBitmapFromHBITMAP;

    typedef Gdiplus::Status(WINAPI* pGdipSaveImageToFile)(ULONG*, const WCHAR*, const CLSID*, const Gdiplus::EncoderParameters*);
    pGdipSaveImageToFile lGdipSaveImageToFile;

    // load Gdiplus library
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // load GdipCreateBitmapFromHBITMAP
    HMODULE hModuleThread = LoadLibrary(L"gdiplus.dll");
    lGdipCreateBitmapFromHBITMAP = (pGdipCreateBitmapFromHBITMAP)GetProcAddress(hModuleThread, "GdipCreateBitmapFromHBITMAP");
    if (lGdipCreateBitmapFromHBITMAP == NULL)
    {
        // error
        Gdiplus::GdiplusShutdown(gdiplusToken);
        return 0;
    }

    // load GdipSaveImageToFile
    lGdipSaveImageToFile = (pGdipSaveImageToFile)GetProcAddress(hModuleThread, "GdipSaveImageToFile");
    if (lGdipSaveImageToFile == NULL)
    {
        // error
        Gdiplus::GdiplusShutdown(gdiplusToken);
        return 0;
    }

    lGdipCreateBitmapFromHBITMAP(hBmp, NULL, &pBitmap);

    //iRes = GetEncoderClsid(L"image/jpeg", &imageCLSID);
    iRes = GetEncoderClsid(L"image/png", &imageCLSID);
    if (iRes == -1)
    {
        // error
        Gdiplus::GdiplusShutdown(gdiplusToken);
        return 0;
    }

    encoderParams.Count = 1;

    lGdipSaveImageToFile(pBitmap, lpszFilename, &imageCLSID, &encoderParams);

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 1;
}

int main()
{
    // Get the screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a device context compatible with the screen
    HDC hScreenDC = GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hScreenDC);

    // Create a bitmap compatible with the screen
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);

    // Select the bitmap into the memorycontext
    SelectObject(hMemDC, hBitmap);

    // Copy the screen contents into the bitmap
    BitBlt(hMemDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY);

    // Release the device contexts
    ReleaseDC(NULL, hScreenDC);
    DeleteDC(hMemDC);

    // Save the bitmap as a JPEG file
    SaveJpeg(hBitmap, L"screen_capture.png");

    // Clean up the bitmap
    DeleteObject(hBitmap);

    return 0;
}