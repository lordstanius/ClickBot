//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VirtualCursor2.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmCursor2 *frmCursor2 = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmCursor2::TfrmCursor2(TComponent* Owner) : TForm(Owner)
{
	isDragging = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCursor2::FormPaint(TObject *Sender)
{
	TPoint points[] = { TPoint(0, 10), TPoint(10, 0), TPoint(10, 5), TPoint(Width-1, 5), TPoint(Width-1, 15), TPoint(10, 15), TPoint(10, 20) };

	Canvas->Pen->Color = frmMain->btnCursor2Color->Color;
	Canvas->Brush->Color = frmMain->btnCursor2Color->Color;
	Canvas->Polygon(points, sizeof(points)/sizeof(TPoint)-1);

	frmMain->clickPoint2 = TPoint(Left-1, Top + 10);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCursor2::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	frmMain->clickPoint2 = TPoint(Left-1, Top + 10);

	if (isDragging)
	{
		Left = Mouse->CursorPos.x - delta.x;
		Top = Mouse->CursorPos.y - delta.y;

		if (frmMain->chkFreeze->Checked)
			frmMain->MoveVirtualCursor(frmCursor2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCursor2::FormShow(TObject *Sender)
{
	Left = frmMain->cursor2pos.x;
	Top = frmMain->cursor2pos.y;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCursor2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caNone;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCursor2::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	isDragging = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCursor2::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	delta = TPoint(X,Y);
	isDragging = true;
}
//---------------------------------------------------------------------------

/*
void __fastcall TfrmCursor2::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (frmMain->txtShortcut->Text.IsEmpty())
		return;

	if (toupper(Key) == frmMain->txtShortcut->Text[1])
	{
		//frmMain->btnOperationMouseUp((TObject*)&frmMain, mbLeft, TShiftState(), 0, 0);
        frmMain->OperationButtonClick();
	}
}         */
//---------------------------------------------------------------------------

