//---------------------------------------------------------------------------

#ifndef PixelLookupH
#define PixelLookupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
struct CRect
{
	int x;
	int y;
	int width;
	int height;
    CRect() { }
	CRect(int X, int Y, int W, int H): x(X), y(Y), width(W), height(H) { }
};


class PixelLookup : public TThread
{
private:
	void __fastcall ShutDown();
	void __fastcall Init();
	void __fastcall GetOcrSetting();
	//void LoadBuffer(TColor* buffer, TPoint p, int size, HDC hdc);
	bool DoWork();
	int LoadBuffer(unsigned char** ppBuffer, CRect rect, HDC hdc);
	//void FillBuffer(TListView* list, TColor** cb);
	void Initialize(TListView* list, unsigned char** pBuffer, CRect& rect, char& value);
	bool Click(TPoint clickPoint, int pixelCount);
	//bool DoClick(TListView* coordList, TPoint clickPoint, TColor* buffer, TColor color);
	bool DoClick(CRect r, TPoint clickPoint, const unsigned char* bmpBytes, TColor color, char value, bool targetSet);
	bool CheckRefreshed(int pixelCount);

	unsigned char*  _bmp; // temporary buffer for storing current region
	unsigned char*  _bmp1;
	unsigned char*  _bmp2;

	char _t1, _t2; // target values
	bool _isTarget1Set;
	bool _isTarget2Set;
	CRect _rect1;
	CRect _rect2;

	bool _ocr;

	POINT _oldCursorPoint;
	TColor _cursor1Color;
	TColor _cursor2Color;
	TColor _hitColor;
protected:
	void __fastcall Execute();
public:
	__fastcall PixelLookup(bool CreateSuspended);
	static void DrawRectangle(HDC hdc, CRect r, TColor color);
	static bool SaveImage(wchar_t* fileName, int width, int height, unsigned char* pBuffer, DWORD dwBmpSize);
    static void FlipBmpBuffer(unsigned char* buffer, int width, int height);
};
//---------------------------------------------------------------------------
#endif
