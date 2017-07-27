#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include "common.h"
#pragma comment (lib,"gdiplus.lib")

using namespace Gdiplus;
int GetEncoderClsid(WCHAR *format, CLSID *pClsid)
{
	
    unsigned int num = 0,  size = 0;
    GetImageEncodersSize(&num, &size);
    if(size == 0) return -1;
    ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
    if(pImageCodecInfo == NULL) return -1;
    GetImageEncoders(num, size, pImageCodecInfo);
  
    for (unsigned int j = 0; j < num; ++j) {
        if(wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }   
    }
    free(pImageCodecInfo);
    return -1;
}


int SaveScreenshot(std::string filename, ULONG uQuality) 
{
	IStream *imageStream = NULL;
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    HWND hMyWnd = GetDesktopWindow();
    RECT r;
    int w, h;
    HDC dc, hdcCapture;
    int nBPP, nCapture, iRes;
    char* lpCapture;
    CLSID imageCLSID;
    Bitmap *pScreenShot;
	HBITMAP imageData;
    // get the area of my application's window     
    GetWindowRect(hMyWnd, &r);
    dc = GetWindowDC(hMyWnd);   
    w = r.right - r.left;
    h = r.bottom - r.top;
    nBPP = GetDeviceCaps(dc, BITSPIXEL);
    hdcCapture = CreateCompatibleDC(dc);

    BITMAPINFO bmiCapture = { sizeof(BITMAPINFOHEADER), w, -h, 1, nBPP, BI_RGB, 0, 0, 0, 0, 0, };

    // create a container and take the screenshot
	lpCapture = new char[w*h];
    HBITMAP hbmCapture = CreateDIBSection(dc, &bmiCapture, DIB_PAL_COLORS, (LPVOID *)&lpCapture, NULL, 0);
	// failed to take it
    if (!hbmCapture) {
        DeleteDC(hdcCapture);
        DeleteDC(dc);
        GdiplusShutdown(gdiplusToken);
        return 0;
    }
	
    nCapture = SaveDC(hdcCapture);
    SelectObject(hdcCapture, hbmCapture);
    BitBlt(hdcCapture, 0, 0, w, h, dc, 0, 0, SRCCOPY);
	
    RestoreDC(hdcCapture, nCapture);
    DeleteDC(hdcCapture);
    DeleteDC(dc);
	
    pScreenShot = new Bitmap(hbmCapture, (HPALETTE)NULL);
    EncoderParameters encoderParams;
    encoderParams.Count = 1;
    encoderParams.Parameter[0].NumberOfValues = 1;
    encoderParams.Parameter[0].Guid  = EncoderQuality;
    encoderParams.Parameter[0].Type  = EncoderParameterValueTypeLong;
    encoderParams.Parameter[0].Value = &uQuality;
    GetEncoderClsid(L"image/jpeg", &imageCLSID);

    wchar_t *lpszFilename = new wchar_t[filename.length() + 1];
    mbstowcs( lpszFilename, filename.c_str(), filename.length() + 1);

	//TO DO STUFF
	int iWidth =	pScreenShot->GetWidth();
	int iHeight = pScreenShot->GetHeight();
	int stride = 4 * ((iWidth + 3) / 4);
    size_t safeSize = stride * iHeight * 4 + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + 256 * sizeof(RGBQUAD);
    HGLOBAL mem = GlobalAlloc(GHND, safeSize);
	BYTE* buffer = new BYTE[safeSize]; 
	
	IStream* pStream;
	
	HRESULT hres = CreateStreamOnHGlobal ( mem , TRUE , &pStream );
	iRes = (pScreenShot->Save(lpszFilename, &imageCLSID, &encoderParams) == Ok);
	BitmapData data;
	Rect rect(0,0,iWidth,iHeight);
	pScreenShot->LockBits(&rect,ImageLockModeRead,PixelFormat32bppARGB,&data);
	BYTE* pPixels = (BYTE*)data.Scan0;
	// Use the data here
	
	pScreenShot->UnlockBits(&data);
    delete pScreenShot;
    DeleteObject(hbmCapture);
	
    GdiplusShutdown(gdiplusToken);
    return iRes;
}
