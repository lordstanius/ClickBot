//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PixelLookup.h"
#include "VirtualCursor1.h"
#include "VirtualCursor2.h"
#include "Main.h"
#include "Logger.h"
#include "tessapi.h"
#pragma package(smart_init)

#pragma comment(lib, "tessapi.lib")

//#define _DEBUG

int scale = 1;
String out;
Logger log;
//---------------------------------------------------------------------------

__fastcall PixelLookup::PixelLookup(bool CreateSuspended) : TThread(CreateSuspended)
{
	_bmp1 = NULL;
	_bmp2 = NULL;
	_bmp = NULL;
	_cursor1Color = frmMain->btnCursor1Color->Color;
	_cursor2Color = frmMain->btnCursor2Color->Color;
	_hitColor = frmMain->btnSearchColor->Color;
}
//---------------------------------------------------------------------------
void __fastcall PixelLookup::Execute()
{
	log.Open(L"clickbot.log");
	//log.WriteTimestamp();
	log.Write(L"------------ Thread started ----------------------");

	Synchronize(&GetOcrSetting);
	log.Write(L"Get Setting");
	int initResult = 0;
	if (_ocr)
	{
		if (TessAPI_Initialize(".\\", "eng") != 0)
		{
			log.Write(L"Failed to initialize TesseractOCR");
			return;
		}
	}

	Synchronize(&Init);

	out.sprintf(L"Running in OCR mode: %s", _ocr ? L"true" : L"false");
	log.Write(out.w_str());

	bool done = false;
	while (!Terminated && !done)
	{
		done = IsClicked();
#ifdef _DEBUG
		Sleep(1000);
#else
		Sleep(1);
#endif
	}

	if (done)
		Synchronize(&ShutDown);

	if (_bmp != NULL)
		delete[] _bmp;

	if (_bmp1 != NULL)
		delete[] _bmp1;

	if (_bmp2 != NULL)
		delete[] _bmp2;

	if (_ocr)
		TessAPI_End();

	log.Write(L"Thread out.");
}
//---------------------------------------------------------------------------

void __fastcall PixelLookup::Init()
{
#ifdef _DEBUG
	log.Write(L"Initializing first window.");
#endif
	Initialize(frmMain->listView1, &_bmp1, _rect1, _t1);

#ifdef _DEBUG
	log.Write(L"Initializing second window.");
#endif
	Initialize(frmMain->listView2, &_bmp2, _rect2, _t2);

	int size1 = _rect1.width * scale * _rect1.height * scale * 4;
	int size2 = _rect2.width * scale * _rect2.height * scale * 4;

#ifdef _DEBUG
	log.Write(L"Getting size.");
#endif
	_bmp = new unsigned char[size2 > size1 ? size2 : size1];

	_isTarget1Set = frmMain->cbTargetNum1->Text.Length() > 0;
	if (_isTarget1Set)
		_t1 = frmMain->cbTargetNum1->Text[1];

	_isTarget2Set = frmMain->cbTargetNum2->Text.Length() > 0;
	if (_isTarget2Set)
		_t2 = frmMain->cbTargetNum2->Text[1];
}

void PixelLookup::Initialize(TListView *list, unsigned char **pBuffer, CRect &r, char &value)
{
	int itemCount = list->Items->Count;

	if (itemCount == 0)
		return;

	TListItem *item;

	r.width = -1;
	r.height = -1;

	for (int i = 0; i < itemCount; ++i)
	{
		item = list->Items->Item[i];

		if (item->Checked)
		{
			r.x = StrToInt(item->SubItems->Strings[0]);
			r.y = StrToInt(item->SubItems->Strings[1]);
			r.width = StrToInt(item->SubItems->Strings[2]);
			r.height = StrToInt(item->SubItems->Strings[3]);

			if (r.width <= 0 && r.height <= 0)
				continue;

			HRGN hrgn = CreateRectRgn(r.x, r.y, r.x + r.width + 1, r.y + r.height + 1);
			HDC hdc = GetDCEx(NULL, hrgn, DCX_INTERSECTRGN);

			int buffSize = r.width * r.height * 4 * scale * scale;
			*pBuffer = new unsigned char[buffSize];

			if (LoadBuffer(pBuffer, r, hdc) != buffSize)
				log.Write(L"Initialize(): Error in bitmap buffer allocation.");

			ReleaseDC(NULL, hdc);

			if (_ocr)
			{
				FlipBmpBuffer(*pBuffer, r.width * scale, r.height * scale);
				TessAPI_SetImage(*pBuffer, r.width * scale, r.height * scale, 4, r.width * scale * 4);

				char *text = TessAPI_GetUTF8Text();
				value = *text;
				log.Write(out.sprintf(L"Recognized start: %c", value).w_str());

#ifdef _DEBUG
				FlipBmpBuffer(*pBuffer, r.width * scale, r.height * scale);
				SaveImage(out.sprintf(L"%c.bmp", value >= 48 && value < 58 ? value : '#').w_str(), r.width * scale, r.height * scale, *pBuffer, buffSize);
				log.Write(L"Clearing tesseract...");
#endif

				TessAPI_Clear();
#ifdef _DEBUG
				log.Write(L"Done.");
#endif
			}
			break;
		}
	}
}

bool PixelLookup::IsClicked()
{
	if (IsMatchFound(_rect1, frmMain->clickPoint1, _bmp1, _cursor1Color, _t1, _isTarget1Set))
	{
		Click(frmMain->clickPoint1);
		return true;
	}

	if (IsMatchFound(_rect2, frmMain->clickPoint2, _bmp2, frmMain->btnCursor2Color->Color, _t2, _isTarget2Set))
	{
		Click(frmMain->clickPoint2);
		if (IsMatchFound(_rect1, frmMain->clickPoint1, _bmp1, _cursor1Color, _t1, _isTarget1Set))
			Click(frmMain->clickPoint1);

		return true;
	}

	return false;
}

bool PixelLookup::IsMatchFound(CRect r, TPoint clickPoint, const unsigned char *bmpBytes, TColor color, char value, bool isTargetSet)
{
	if (r.width == -1 && r.height == -1)
		return false;

#ifdef _DEBUG
	log.Write(L"Enter DoClick():");
#endif
	if (r.width == 0 || r.height == 0)
		return IsPixelMatched(r);

#ifdef _DEBUG
	log.Write(L"Enter Loading buffer...");
#endif
	HDC hdc = GetDC(NULL);
	int buffSize = r.width * scale * r.height * scale * 4;
	if (buffSize != LoadBuffer(&_bmp, r, hdc))
		log.Write(L"DoClick(): error in bitmap buffer allocation.");
	ReleaseDC(NULL, hdc);

#ifdef _DEBUG
	log.Write(L"Buffer loaded...");
	SaveImage(L"_bmp.bmp", r.width * scale, r.height * scale, _bmp, buffSize);
#endif

	if (!_ocr && memcmp(_bmp, bmpBytes, buffSize))
	{
		//log.WriteBinary(_bmp, buffSize);
		log.Write(L"Change in window detected.");
		log.Write(L"-----------------------------------------");
		//log.WriteBinary(bmpBytes, buffSize);
		return true;
	}

	if (_ocr)
		return IsOCRMatched(r, value, isTargetSet);

	return false;
}

bool PixelLookup::IsPixelMatched(CRect r)
{
	RECT rect;
	HWND hwnd = WindowFromPoint(Point(r.x, r.y));
	GetWindowRect(hwnd, &rect);
	HDC hdc = GetWindowDC(hwnd);

	r.x -= rect.left;
	r.y -= rect.top;

#ifdef _DEBUG
	out.sprintf(L"[%d, %d] rw = %d; rh = %d", r.x, r.y, r.width, r.height);
	log.Write(out.w_str());
#endif

	TColor pixelColor = (TColor)GetPixel(hdc, r.x, r.y);
	ReleaseDC(hwnd, hdc);
#ifdef _DEBUG
	out.sprintf(L"Pixel color: %d. Target color: %d", pixelColor, _hitColor);
	log.Write(out.w_str());
#endif

	return pixelColor == _hitColor;
}

bool PixelLookup::IsOCRMatched(CRect r, char value, bool isTargetSet)
{
	FlipBmpBuffer(_bmp, r.width * scale, r.height * scale);
	TessAPI_SetImage(_bmp, r.width * scale, r.height * scale, 4, r.width * scale * 4);

	char *text = TessAPI_GetUTF8Text();
	char t = text[0];

#ifdef _DEBUG
	log.Write(L"Reckognition done.");
	log.Write(out.sprintf(L"Detected value of %c", t).w_str());
#endif

	TessAPI_Clear();

	if (t != '\0' && ((isTargetSet && t == value) || (!isTargetSet && t != value)))
	{
		log.Write(out.sprintf(L"Value of %c changed to %c", value, t).w_str());
		log.Write(L"---------------------------------------------");
		return true;
	}

	return false;
}

void PixelLookup::Click(TPoint clickPoint)
{
	int x = clickPoint.x;
	int y = clickPoint.y;

	GetCursorPos(&_oldCursorPoint); // save cursor pos before click
	HWND hwnd = WindowFromPoint(clickPoint);
	SendMessage(hwnd, WA_ACTIVE, 0, 0); // activate target window first

	ReleaseCapture(); // release capture from current window
	SetCursorPos(x, y);

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // simulate click
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

#ifdef _DEBUG
	log.Write(L"Clicked!");
#endif
}

void PixelLookup::DrawRectangle(HDC hdc, CRect r, TColor color)
{
	LOGPEN pen = {PS_SOLID, {1, 0}, color};
	HPEN hpen = CreatePenIndirect(&pen);
	HPEN oldpen = (HPEN)SelectObject(hdc, hpen);
	HBRUSH hbrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	if (r.width == 0)
		++r.width;

	if (r.height == 0)
		++r.height;

	Rectangle(hdc, r.x - 1, r.y - 1, r.x + r.width + 1, r.y + r.height + 1);
	SelectObject(hdc, hbrush);
	SelectObject(hdc, oldpen);
	DeleteObject(hpen);
}

void __fastcall PixelLookup::GetOcrSetting()
{
	_ocr = frmMain->chkOcrMode->Checked;
}

int PixelLookup::LoadBuffer(unsigned char **pBuffer, CRect r, HDC hdc)
{
	HDC cdc = CreateCompatibleDC(hdc);
	if (cdc == NULL)
		log.Write(L"Failed to create device context.");

	HBITMAP hbmp = CreateCompatibleBitmap(hdc, r.width * scale, r.height * scale);
	SelectObject(cdc, hbmp);

	if (scale > 1)
		StretchBlt(cdc, 0, 0, r.width * scale, r.height * scale, hdc, r.x, r.y, r.width, r.height, SRCCOPY);
	else
		BitBlt(cdc, 0, 0, r.width, r.height, hdc, r.x, r.y, SRCCOPY);

	BITMAP bmp;
	GetObject(hbmp, sizeof(BITMAP), &bmp);

	BITMAPINFO bi = {0};
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = bmp.bmWidth;
	bi.bmiHeader.biHeight = bmp.bmHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;

	int dwBmpSize = bmp.bmWidth * bmp.bmHeight * 4;

	// Gets the "bits" from the bitmap and copies them into a buffer
	// which is pointed to by lpbitmap.
	GetDIBits(cdc, hbmp, 0, (UINT)bmp.bmHeight, *pBuffer, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
	//SaveImage(L"init.bmp", bmp.bmWidth, bmp.bmHeight, *pBuffer, dwBmpSize); //!!! _DEBUG LINE

	DeleteObject(hbmp);
	//DeleteObject(hsrc);
	DeleteDC(cdc);
	return dwBmpSize;
}

bool PixelLookup::SaveImage(wchar_t *fileName, int width, int height, unsigned char *pBuffer, DWORD dwBmpSize)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));
	bmfh.bfType = 0x4d42; // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwBmpSize;
	bmfh.bfOffBits = 0x36;

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biBitCount = 32;
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 0x0ec4;
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	HANDLE file = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == file)
		return false;

	//Now we write the file header and info header:

	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	//and finally the image data:
	if (WriteFile(file, pBuffer, dwBmpSize, &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	//Now we can close our function with
	CloseHandle(file);
	return true;
}

void PixelLookup::FlipBmpBuffer(unsigned char *buffer, int width, int height)
{
	unsigned int *p = (unsigned int *)buffer;
	//unsigned int* tmp = new unsigned int[width*height];

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height / 2; ++y)
		{
			unsigned int n = x + y * width;
			unsigned int f = x + (height - y - 1) * width;
			unsigned int t = p[n];
			p[n] = p[f];
			p[f] = t;
		}
	}
}

void __fastcall PixelLookup::ShutDown()
{
	frmMain->WindowState = wsNormal;
	frmMain->btnOperation->Caption = "OUT";
	frmMain->btnOperation->Color = clRed;
	frmMain->btnOperation->Tag = 0;
	frmMain->BringToFront();

	SetCursorPos(_oldCursorPoint.x, _oldCursorPoint.y); // restore cursor pos

	// disable
	//frmMain->btnOperation->Font->Color = clGray;
	//frmMain->btnOperation->Color = clSilver;
	//frmMain->btnOperation->Enabled = false;
}

// returns true if all pixels are the same color. this indicates that
// the screen is being refreshed. One pixel is 32 bit
bool PixelLookup::CheckRefreshed(int totalPixels)
{
	if (totalPixels < 2)
		return false;

	int color = *((int *)_bmp);
	for (int i = 1; i < totalPixels; ++i)
	{
		int p = *((int *)_bmp + i);
		if (p != color)
			return false;
	}

	log.Write(L"Refresh detected.");
	return true;
}
