//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VirtualCursor1.h"

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmCursor1 *frmCursor1 = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmCursor1::TfrmCursor1(TComponent* Owner): TForm(Owner)
{
	isDragging = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCursor1::FormPaint(TObject *Sender)
{
	TPoint points[] = { TPoint(0, 5), TPoint(Width-11, 5), TPoint(Width-11, 0), TPoint(Width-1, 10), TPoint(Width-11, 20), TPoint(Width-11, 15), TPoint(0, 15) };

	Canvas->Pen->Color = frmMain->btnCursor1Color->Color;
	Canvas->Brush->Color = frmMain->btnCursor1Color->Color;
	Canvas->Polygon(points, sizeof(points)/sizeof(TPoint)-1);

	frmMain->clickPoint1 = TPoint(Left + Width, Top + 10);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCursor1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	frmMain->clickPoint1 = TPoint(Left + Width, Top + 10);

	if (isDragging)
	{
		Left = Mouse->CursorPos.x - delta.x;
		Top = Mouse->CursorPos.y - delta.y;

		if (frmMain->chkFreeze->Checked)
		{
			frmMain->MoveVirtualCursor(frmCursor1);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCursor1::FormShow(TObject *Sender)
{
	Left = frmMain->cursor1pos.x;
	Top = frmMain->cursor1pos.y;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCursor1::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caNone;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCursor1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	isDragging = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCursor1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    delta = TPoint(X,Y);
	isDragging = true;
}
//---------------------------------------------------------------------------

/*
void __fastcall TfrmCursor1::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (frmMain->txtShortcut->Text.IsEmpty())
		return;

	if (toupper(Key) == frmMain->txtShortcut->Text[1])
	{
		//frmMain->btnOperationMouseUp((TObject*)&frmMain, mbLeft, TShiftState(), 0, 0);
		frmMain->OperationButtonClick();
	}
}                */
//---------------------------------------------------------------------------

