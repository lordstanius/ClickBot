//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "VirtualCursor1.h"
#include "VirtualCursor2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeCanvas"
#pragma resource "*.dfm"

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))


TfrmMain *frmMain;

HHOOK keyboardHook;
//char shortcut = 0;

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0 || frmMain->txtShortcut->Text == "")
		return CallNextHookEx(keyboardHook, code, wParam, lParam);


	if (wParam == WM_KEYDOWN)
	{
		KBDLLHOOKSTRUCT* kbdll = (KBDLLHOOKSTRUCT*)lParam;
		if (kbdll->vkCode == frmMain->txtShortcut->Text[1])
			frmMain->OperationButtonClick();
	}

	return CallNextHookEx(keyboardHook, code, wParam, lParam);
}

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner): TForm(Owner)
{
	btnCursor1Color->Color = clBlue;
	btnCursor2Color->Color = (TColor)RGB(250, 150, 0);

	cursor1pos = TPoint(Left + 100, Top + 2);
	cursor2pos = TPoint(Left + 160, Top + 2);
	plThread = NULL;
	LoadSettings();
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, (HINSTANCE)NULL, 0); //GetCurrentThreadId()
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
	frmCursor1->Show();
	frmCursor2->Show();
	frmCursor1->Width = upDown1->Position;
	frmCursor2->Width = upDown2->Position;

	OnShow();

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OperationPanelMouseEnter(TPanel *Sender)
{
	Sender->Color = clBtnFace;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OperationPanelMouseLeave(TPanel *Sender)
{
	Sender->Color = clWindow;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OperationPanelMouseDown(TPanel *Sender)
{
	Sender->BevelInner = bvNone;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OperationPanelMouseUp(TPanel *Sender)
{
	Sender->BevelInner = bvSpace;
}

void __fastcall TfrmMain::btnOperationMouseLeave(TObject *Sender)
{
	if (btnOperation->Tag == 1)
		btnOperation->Color = clLime;
	else
		btnOperation->Color = clRed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnOperationMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseDown(btnOperation);

	if (btnOperation->Tag == 1)
		btnOperation->Color = clPaleGreen;
	else
		btnOperation->Color = clPaleRed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnOperationMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseUp(btnOperation);
	OperationButtonClick();
}
//---------------------------------------------------------------------------
void TfrmMain::OperationButtonClick()
{
	if (btnOperation->Tag == 0)
	{
		btnOperation->Caption = "IN";
		btnOperation->Color = clLime;
		btnOperation->Tag = 1;

		plThread = new PixelLookup(true);
		plThread->FreeOnTerminate = true;
		plThread->Resume();
	}
	else
	{
		if (plThread != NULL)
		{
			if (!plThread->Finished)
			{
				plThread->Terminate();
				//plThread->WaitFor();
			}
			plThread = NULL;
		}

		frmMain->btnOperation->Caption = "OUT";
		frmMain->btnOperation->Color = clRed;
		frmMain->btnOperation->Tag = 0;
	}
}

void __fastcall TfrmMain::PanelMouseEnter(TPanel *Sender)
{
	Sender->BevelInner = bvRaised;
	Sender->BevelKind = bkNone;
	Sender->BevelOuter = bvSpace;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::PanelMouseLeave(TPanel *Sender)
{
	Sender->BevelInner = bvNone;
	Sender->BevelKind = bkNone;
	Sender->BevelOuter = bvSpace;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::PanelMouseDown(TPanel *Sender)
{
	Sender->BevelInner = bvNone;
	Sender->BevelKind = bkSoft;
	Sender->BevelOuter = bvSpace;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCursor1ColorMouseEnter(TObject *Sender)
{
	PanelMouseEnter(btnCursor1Color);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor1ColorMouseLeave(TObject *Sender)
{
	PanelMouseLeave(btnCursor1Color);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor1ColorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	PanelMouseDown(btnCursor1Color);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor1ColorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	dlgColor->Execute();
	btnCursor1Color->Color = dlgColor->Color;
	frmCursor1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor2ColorMouseEnter(TObject *Sender)
{
	PanelMouseEnter(btnCursor2Color);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor2ColorMouseLeave(TObject *Sender)
{
	PanelMouseLeave(btnCursor2Color);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor2ColorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	PanelMouseDown(btnCursor2Color);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCursor2ColorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	dlgColor->Execute();
	btnCursor2Color->Color = dlgColor->Color;
	frmCursor2->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSearchColorMouseEnter(TObject *Sender)
{
	PanelMouseEnter(btnSearchColor);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSearchColorMouseLeave(TObject *Sender)
{
	PanelMouseLeave(btnSearchColor);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSearchColorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	PanelMouseDown(btnSearchColor);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSearchColorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	dlgColor->Execute();
	btnSearchColor->Color = dlgColor->Color;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd1MouseEnter(TObject *Sender)
{
	OperationPanelMouseEnter(btnAdd1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd1MouseLeave(TObject *Sender)
{
	OperationPanelMouseLeave(btnAdd1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseDown(btnAdd1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseUp(btnAdd1);
	AddItem(listView1, StrToInt(btnCursor1Color->Color));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd2MouseEnter(TObject *Sender)
{
	OperationPanelMouseEnter(btnAdd2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd2MouseLeave(TObject *Sender)
{
	OperationPanelMouseLeave(btnAdd2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseDown(btnAdd2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAdd2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseUp(btnAdd2);
	AddItem(listView2, StrToInt(btnCursor2Color->Color));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove1MouseEnter(TObject *Sender)
{
	OperationPanelMouseEnter(btnRemove1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove1MouseLeave(TObject *Sender)
{
	OperationPanelMouseLeave(btnRemove1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseDown(btnRemove1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseUp(btnRemove1);
	RemoveItem(listView1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove2MouseEnter(TObject *Sender)
{
	OperationPanelMouseEnter(btnRemove2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove2MouseLeave(TObject *Sender)
{
	OperationPanelMouseLeave(btnRemove2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseDown(btnRemove2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemove2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	OperationPanelMouseUp(btnRemove2);
	RemoveItem(listView2);
}

void __fastcall TfrmMain::AddItem(TListView* list, TColor color)
{
	list->Items->Add();
	String xValue = txtXcoord->Text;
	String yValue = txtYcoord->Text;
	String width = txtWidth->Text;
	String height = txtHeight->Text;


	if (xValue == "") xValue = 0;
	if (yValue == "") yValue = 0;
	if (width == "") width = 0;
	if (height == "") height = width;

	int count = list->Items->Count-1;

	list->Items->Item[count]->Checked = true;
	list->Items->Item[count]->SubItems->Add(xValue);
	list->Items->Item[count]->SubItems->Add(yValue);
	list->Items->Item[count]->SubItems->Add(width);
	list->Items->Item[count]->SubItems->Add(height);

	DrawIndicatorRectangle(list->Items->Item[count], color);
	if (list == listView1)
		ValidateListForItem(listView2, list->Items->Item[count]);
	else
		ValidateListForItem(listView1, list->Items->Item[count]);
}

void __fastcall TfrmMain::RemoveItem(TListView* list)
{
	if (list->Items->Count == 0)
		return;

	if (list->SelCount > 0)
	{
		while (list->SelCount != 0)
			list->Selected->Delete();
    }
	else
	{
		int count = list->Items->Count;
		list->Items->Delete(count-1);
	}
}

void __fastcall TfrmMain::listView1ItemChecked(TObject *Sender, TListItem *Item)
{
	ValidateListForItem(listView2, Item);

	if (!Item->Checked)
		return;

	DrawIndicatorRectangle(Item, StrToInt(btnCursor1Color->Color));

	for (int i = 0; i < listView1->Items->Count; ++i)
	{
		TListItem* currentItem = listView1->Items->Item[i];

		if (currentItem != Item)
			currentItem->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::listView2ItemChecked(TObject *Sender, TListItem *Item)
{
	ValidateListForItem(listView1, Item);

	if (!Item->Checked)
		return;

	DrawIndicatorRectangle(Item, StrToInt(btnCursor2Color->Color));

	for (int i = 0; i < listView2->Items->Count; ++i)
	{
		TListItem* currentItem = listView2->Items->Item[i];

		if (currentItem != Item)
			currentItem->Checked = false;
	}
}
//---------------------------------------------------------------------------

void TfrmMain::DrawIndicatorRectangle(TListItem *Item, TColor color)
{
	if (Item->SubItems->Count < 4)
		return;

	DrawRectangle(
		StrToInt(Item->SubItems->Strings[0]),
		StrToInt(Item->SubItems->Strings[1]),
		StrToInt(Item->SubItems->Strings[2]),
		StrToInt(Item->SubItems->Strings[3]),
		color
	);
}


void TfrmMain::ValidateListForItem(TListView* list, TListItem* item)
{
	int count = list->Items->Count;
	if (count == 0)
		return;

	if (item->SubItems->Count == 0)
		return;

	int x1 = StrToInt(item->SubItems->Strings[0]);
	int y1 = StrToInt(item->SubItems->Strings[1]);


	for (int j = 0; j < count; ++j)
	{
		TListItem* currentItem = list->Items->Item[j];

		int x2 = StrToInt(currentItem->SubItems->Strings[0]);
		int y2 = StrToInt(currentItem->SubItems->Strings[1]);

		if (item->Checked && x1 == x2 && y1 == y2)
			currentItem->Checked = false;
	}
}

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	WriteSettings();
}
//---------------------------------------------------------------------------

void TfrmMain::WriteSettings()
{
	String path = GetCurrentDir();

	path.sprintf(TEXT("%s\\ClickBotSettings.ini"), path);
	DeleteFile(path);

	TCHAR sectionStrBuffer[1024];
	TCHAR nameBuffer[64];

	ZeroMemory(sectionStrBuffer, 1024*sizeof(TCHAR));
	ZeroMemory(nameBuffer, 64*sizeof(TCHAR));

	int count1 = listView1->Items->Count;
	int count2 = listView2->Items->Count;

	wsprintf(sectionStrBuffer,
		TEXT("List1EntryCount= %d\nList2EntryCount = %d\nSearchColor = %d\nShortcut = %s\nLeft = %d\nTop = %d\nHeight = %d\nFreezed = %d\nOCR = %d\nDX = %d\nDY = %d\nTarget1 = %s\nTarget2 = %s"),
		count1, count2, btnSearchColor->Color, txtShortcut->Text.t_str(), this->Left, this->Top, this->Height, chkFreeze->Checked, chkOcrMode->Checked,
		cursorDistance.x, cursorDistance.y, cbTargetNum1->Text, cbTargetNum2->Text);
	WritePrivateProfileSection(TEXT("General"), sectionStrBuffer, path.t_str());
	ZeroMemory(sectionStrBuffer, 1024 * sizeof(TCHAR));

	wsprintf(sectionStrBuffer, TEXT("Color = %d\nX = %d\nY = %d\nWidth = %d"), btnCursor1Color->Color, frmCursor1->Left, frmCursor1->Top, frmCursor1->Width);
	WritePrivateProfileSection(TEXT("VirtualCursor1"), sectionStrBuffer, path.t_str());
	ZeroMemory(sectionStrBuffer, 1024 * sizeof(TCHAR));

	wsprintf(sectionStrBuffer, TEXT("Color = %d\nX = %d\nY = %d\nWidth = %d"), btnCursor2Color->Color, frmCursor2->Left, frmCursor2->Top, frmCursor2->Width);
	WritePrivateProfileSection(TEXT("VirtualCursor2"), sectionStrBuffer, path.t_str());
	ZeroMemory(sectionStrBuffer, 1024 * sizeof(TCHAR));

	for (int i = 0; i < count1; ++i)
	{
		TListItem* item = listView1->Items->Item[i];
		ZeroMemory(nameBuffer, sizeof(TCHAR)*64);
		wsprintf(nameBuffer, TEXT("List1Entry.%d"), i);
		wsprintf(sectionStrBuffer, TEXT("X = %s\nY = %s\nWidth = %s\nHeight = %s\nChecked = %d\nCaption = %s"),
			item->SubItems->Strings[0], item->SubItems->Strings[1], item->SubItems->Strings[2], item->SubItems->Strings[3],
			item->Checked, item->Caption.t_str());
		WritePrivateProfileSection(nameBuffer, sectionStrBuffer, path.t_str());
	}

	for (int i = 0; i < count2; ++i)
	{
		TListItem* item = listView2->Items->Item[i];
		ZeroMemory(nameBuffer, sizeof(TCHAR)*64);
		wsprintf(nameBuffer, TEXT("List2Entry.%d"), i);
		wsprintf(sectionStrBuffer, TEXT("X = %s\nY = %s\nWidth = %s\nHeight = %s\nChecked = %d\nCaption = %s"),
			item->SubItems->Strings[0], item->SubItems->Strings[1], item->SubItems->Strings[2], item->SubItems->Strings[3],
			item->Checked, item->Caption.t_str());
		WritePrivateProfileSection(nameBuffer, sectionStrBuffer, path.t_str());
	}

	cbTargetNum1->Items->SaveToFile("targets1.txt");
	cbTargetNum2->Items->SaveToFile("targets2.txt");
}

void TfrmMain::LoadSettings()
{
	String path = GetCurrentDir();

	path.sprintf(TEXT("%s\\ClickBotSettings.ini"), path);

	TCHAR keyValue[1024];
	TCHAR nameBuffer[64];
	ZeroMemory(keyValue, 1024*sizeof(TCHAR));

	int count1 = GetPrivateProfileInt(TEXT("General"), TEXT("List1EntryCount"), 0, path.t_str());
	int count2 = GetPrivateProfileInt(TEXT("General"), TEXT("List2EntryCount"), 0, path.t_str());
	Left = GetPrivateProfileInt(TEXT("General"), TEXT("Left"), 300, path.t_str());
	Top = GetPrivateProfileInt(TEXT("General"), TEXT("Top"), 300, path.t_str());
	Height = GetPrivateProfileInt(TEXT("General"), TEXT("Height"), 330, path.t_str());
	btnSearchColor->Color = GetPrivateProfileInt(TEXT("General"), TEXT("SearchColor"), clLime, path.t_str());
	GetPrivateProfileString(TEXT("General"), TEXT("Shortcut"), TEXT(""), keyValue, 1024, path.t_str());
	txtShortcut->Text = String(keyValue);

	chkFreeze->Checked = (bool)GetPrivateProfileInt(TEXT("General"), TEXT("Freezed"), 0, path.t_str());
	chkOcrMode->Checked = (bool)GetPrivateProfileInt(TEXT("General"), TEXT("OCR"), 1, path.t_str());

	GetPrivateProfileString(TEXT("General"), TEXT("Target1"), TEXT(""), keyValue, 1024, path.t_str());
	cbTargetNum1->Text = keyValue;

	GetPrivateProfileString(TEXT("General"), TEXT("Target2"), TEXT(""), keyValue, 1024, path.t_str());
	cbTargetNum2->Text = keyValue;

	cursorDistance.x = GetPrivateProfileInt(TEXT("General"), TEXT("DX"), 0, path.t_str());
	cursorDistance.y = GetPrivateProfileInt(TEXT("General"), TEXT("DY"), 0, path.t_str());

	btnCursor1Color->Color = GetPrivateProfileInt(TEXT("VirtualCursor1"), TEXT("Color"), clBlue, path.t_str());
	cursor1pos.x = GetPrivateProfileInt(TEXT("VirtualCursor1"), TEXT("X"), cursor1pos.x, path.t_str());
	cursor1pos.y = GetPrivateProfileInt(TEXT("VirtualCursor1"), TEXT("Y"), cursor1pos.y, path.t_str());
	upDown1->Position = GetPrivateProfileInt(TEXT("VirtualCursor1"), TEXT("Width"), 56, path.t_str());

	btnCursor2Color->Color = GetPrivateProfileInt(TEXT("VirtualCursor2"), TEXT("Color"), RGB(250, 150, 0), path.t_str());
	cursor2pos.x = GetPrivateProfileInt(TEXT("VirtualCursor2"), TEXT("X"), cursor2pos.x, path.t_str());
	cursor2pos.y = GetPrivateProfileInt(TEXT("VirtualCursor2"), TEXT("Y"), cursor2pos.y, path.t_str());
	upDown2->Position = GetPrivateProfileInt(TEXT("VirtualCursor2"), TEXT("Width"), 56, path.t_str());

	for (int i = 0; i < count1; ++i)
	{
		listView1->Items->Add();

		ZeroMemory(nameBuffer, 64*sizeof(TCHAR));
		wsprintf(nameBuffer, TEXT("List1Entry.%d"), i);

		int x = GetPrivateProfileInt(nameBuffer, TEXT("X"), 0, path.t_str());
		listView1->Items->Item[i]->SubItems->Add(IntToStr(x));

		int y = GetPrivateProfileInt(nameBuffer, TEXT("Y"), 0, path.t_str());
		listView1->Items->Item[i]->SubItems->Add(IntToStr(y));

		int width = GetPrivateProfileInt(nameBuffer, TEXT("Width"), 0, path.t_str());
		listView1->Items->Item[i]->SubItems->Add(IntToStr(width));

		int height = GetPrivateProfileInt(nameBuffer, TEXT("Height"), 0, path.t_str());
		listView1->Items->Item[i]->SubItems->Add(IntToStr(height));

		bool checked = GetPrivateProfileInt(nameBuffer, TEXT("Checked"), 0, path.t_str());
		listView1->Items->Item[i]->Checked = checked;

		ZeroMemory(keyValue, 1024*sizeof(TCHAR));
		GetPrivateProfileString(nameBuffer, TEXT("Caption"), TEXT(""), keyValue, 1024, path.t_str());
		listView1->Items->Item[i]->Caption = String(keyValue);
	}

	for (int i = 0; i < count2; ++i)
	{
		listView2->Items->Add();

		ZeroMemory(nameBuffer, 64*sizeof(TCHAR));
		wsprintf(nameBuffer, TEXT("List2Entry.%d"), i);

		int x = GetPrivateProfileInt(nameBuffer, TEXT("X"), 0, path.t_str());
		listView2->Items->Item[i]->SubItems->Add(IntToStr(x));

		int y = GetPrivateProfileInt(nameBuffer, TEXT("Y"), 0, path.t_str());
		listView2->Items->Item[i]->SubItems->Add(IntToStr(y));

		int width = GetPrivateProfileInt(nameBuffer, TEXT("Width"), 0, path.t_str());
		listView2->Items->Item[i]->SubItems->Add(IntToStr(width));

		int height = GetPrivateProfileInt(nameBuffer, TEXT("Height"), 0, path.t_str());
		listView2->Items->Item[i]->SubItems->Add(IntToStr(height));

		bool checked = GetPrivateProfileInt(nameBuffer, TEXT("Checked"), 0, path.t_str());
		listView2->Items->Item[i]->Checked = checked;

		ZeroMemory(keyValue, 1024*sizeof(TCHAR));
		GetPrivateProfileString(nameBuffer, TEXT("Caption"), TEXT(""), keyValue, 1024, path.t_str());
		listView2->Items->Item[i]->Caption = String(keyValue);
	}

	if (FileExists("targets1.txt"))
		cbTargetNum1->Items->LoadFromFile("targets1.txt");
	if (FileExists("targets2.txt"))
		cbTargetNum2->Items->LoadFromFile("targets2.txt");

	int count = listView1->Items->Count;
	for (int i = 0; i < count; ++i)
		ValidateListForItem(listView2, listView1->Items->Item[i]);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::upDown1Click(TObject *Sender, TUDBtnType Button)
{
	frmCursor1->Width = upDown1->Position;
	frmCursor1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::upDown2Click(TObject *Sender, TUDBtnType Button)
{
	frmCursor2->Width = upDown2->Position;
	frmCursor1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
/*
	if (plThread != NULL)
	{
		if (!plThread->Finished)
		{
			plThread->Terminate();
			plThread->WaitFor();
		}
		plThread->Free();
	}
 */
	if (keyboardHook)
		UnhookWindowsHookEx(keyboardHook);
}
//---------------------------------------------------------------------------

void TfrmMain::MoveVirtualCursor(TObject* sender)
{
	if (dynamic_cast<TfrmCursor1*>(sender))
	{
		frmCursor2->Left = frmCursor1->Left + cursorDistance.x;
		frmCursor2->Top = frmCursor1->Top + cursorDistance.y;
		frmMain->clickPoint2 = TPoint(frmCursor2->Left-1, frmCursor2->Top + 10);
	}
	else
	{
		frmCursor1->Left = frmCursor2->Left - cursorDistance.x;
		frmCursor1->Top = frmCursor2->Top - cursorDistance.y;
		frmMain->clickPoint1 = TPoint(frmCursor1->Left + frmCursor1->Width, frmCursor1->Top + 10);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkFreezeClick(TObject *Sender)
{
	if (frmCursor1 == NULL || frmCursor2 == NULL)
		return;

	if (chkFreeze->Checked)
	{
		cursorDistance.x = frmCursor2->Left - frmCursor1->Left;
		cursorDistance.y = frmCursor2->Top - frmCursor1->Top;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::OnShow()
{
/*
	char *outText;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init("d:\\Lib\\tesseract\\", "eng")) {
		ShowMessage("Could not initialize tesseract.\n");
		//fprintf(stderr, "Could not initialize tesseract.\n");
		//exit(1);
	}

	// Open input image with leptonica library
	Pix *image = pixRead("d:\\Projects\\OCR_test\\test.bmp");
	api->SetImage(image);
	// Get OCR result
	outText = api->GetUTF8Text();
	ShowMessage(String().sprintf(L"OCR output:\n%s", outText));

	// Destroy used object and release memory
	api->End();
	delete [] outText;
	pixDestroy(&image); */
}
void __fastcall TfrmMain::btnWhereClick(TObject *Sender)
{
	int x = txtXcoord->Text.Length() > 0 ? StrToInt(txtXcoord->Text) : 0;
	int y = txtYcoord->Text.Length() > 0 ? StrToInt(txtYcoord->Text) : 0;
	int width = txtWidth->Text.Length() > 0 ? StrToInt(txtWidth->Text) : 0;
	int height = txtHeight->Text.Length() > 0 ? StrToInt(txtHeight->Text) : 0;
	if (width > 0 && height == 0)
	{
		txtHeight->Text = width;
		height = width;
	}
	DrawRectangle(x, y, width, height, RGB(255,0,0));
}
//---------------------------------------------------------------------------

void TfrmMain::DrawRectangle(int x, int y, int width, int height, TColor color)
{
	CRect r(x, y, width, height);
	HDC hdc = GetDC(NULL);
	PixelLookup::DrawRectangle(hdc, r, color);
	DeleteDC(hdc);
}

void __fastcall TfrmMain::listView1Click(TObject *Sender)
{
	OnItemClick(listView1->ItemFocused);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::listView2Click(TObject *Sender)
{
	OnItemClick(listView2->ItemFocused);
}
//---------------------------------------------------------------------------

void TfrmMain::OnItemClick(TListItem* item)
{
	if (item == NULL)
		return;

	txtXcoord->Text = item->SubItems->Strings[0];
	txtYcoord->Text = item->SubItems->Strings[1];
	txtWidth->Text  = item->SubItems->Strings[2];
	txtHeight->Text = item->SubItems->Strings[3];
}


void TfrmMain::OnComboAddItem(TComboBox* cbTarget)
{
	bool isUnique = true;
	for (int i = 0; i < cbTarget->Items->Count; ++i)
		if (cbTarget->Items->Strings[i] == cbTarget->Text)
		{
			isUnique = false;
			break;
		}

	if (isUnique)
		cbTarget->Items->Add(cbTarget->Text);
	if (cbTarget->Focused())
		btnOperation->SetFocus();
}


void TfrmMain::OnComboClear(TComboBox* cbTarget)
{
	if (cbTarget->Text == "")
		cbTarget->Items->Clear();
	else
		for (int i = 0; i < cbTarget->Items->Count; ++i)
		{
			if (cbTarget->Items->Strings[i] == cbTarget->Text)
			{
				cbTarget->Items->Delete(i);
				break;
			}
        }
}


void __fastcall TfrmMain::cbTargetNum1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN)
		OnComboAddItem(cbTargetNum1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cbTargetNum2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN)
		OnComboAddItem(cbTargetNum2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAddCombo1Click(TObject *Sender)
{
	OnComboAddItem(cbTargetNum1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAddCombo2Click(TObject *Sender)
{
	OnComboAddItem(cbTargetNum2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnClearCombo1Click(TObject *Sender)
{
	OnComboClear(cbTargetNum1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnClearCombo2Click(TObject *Sender)
{
	OnComboClear(cbTargetNum2);
}
//---------------------------------------------------------------------------

