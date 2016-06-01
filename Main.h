//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TeCanvas.hpp"
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include "PixelLookup.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *txtShortcut;
	TPanel *btnOperation;
	TPanel *btnSearchColor;
	TPanel *btnCursor1Color;
	TPanel *btnCursor2Color;
	TColorDialog *dlgColor;
	TListView *listView1;
	TListView *listView2;
	TPanel *btnAdd1;
	TPanel *btnRemove1;
	TPanel *btnRemove2;
	TPanel *btnAdd2;
	TUpDown *upDown1;
	TUpDown *upDown2;
	TCheckBox *chkFreeze;
	TGroupBox *GroupBox1;
	TLabel *Label5;
	TEdit *txtXcoord;
	TLabel *Label6;
	TEdit *txtYcoord;
	TLabel *Label7;
	TEdit *txtWidth;
	TLabel *Label8;
	TEdit *txtHeight;
	TButton *btnWhere;
	TCheckBox *chkOcrMode;
	TComboBox *cbTargetNum1;
	TComboBox *cbTargetNum2;
	TGroupBox *GroupBox2;
	TButton *btnAddCombo1;
	TButton *btnAddCombo2;
	TButton *btnClearCombo1;
	TButton *btnClearCombo2;
	void __fastcall btnOperationMouseLeave(TObject *Sender);
	void __fastcall btnOperationMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnOperationMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCursor1ColorMouseEnter(TObject *Sender);
	void __fastcall btnCursor1ColorMouseLeave(TObject *Sender);
	void __fastcall btnCursor1ColorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnCursor1ColorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnCursor2ColorMouseEnter(TObject *Sender);
	void __fastcall btnCursor2ColorMouseLeave(TObject *Sender);
	void __fastcall btnCursor2ColorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnCursor2ColorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnSearchColorMouseEnter(TObject *Sender);
	void __fastcall btnSearchColorMouseLeave(TObject *Sender);
	void __fastcall btnSearchColorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnSearchColorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnAdd1MouseEnter(TObject *Sender);
	void __fastcall btnAdd1MouseLeave(TObject *Sender);
	void __fastcall btnAdd1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnAdd1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnAdd2MouseEnter(TObject *Sender);
	void __fastcall btnAdd2MouseLeave(TObject *Sender);
	void __fastcall btnAdd2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnAdd2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnRemove1MouseEnter(TObject *Sender);
	void __fastcall btnRemove1MouseLeave(TObject *Sender);
	void __fastcall btnRemove1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnRemove1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnRemove2MouseEnter(TObject *Sender);
	void __fastcall btnRemove2MouseLeave(TObject *Sender);
	void __fastcall btnRemove2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnRemove2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall listView1ItemChecked(TObject *Sender, TListItem *Item);
	void __fastcall listView2ItemChecked(TObject *Sender, TListItem *Item);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall upDown1Click(TObject *Sender, TUDBtnType Button);
	void __fastcall upDown2Click(TObject *Sender, TUDBtnType Button);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall chkFreezeClick(TObject *Sender);
	void __fastcall btnWhereClick(TObject *Sender);
	void __fastcall listView1Click(TObject *Sender);
	void __fastcall listView2Click(TObject *Sender);
	void __fastcall cbTargetNum1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbTargetNum2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnAddCombo1Click(TObject *Sender);
	void __fastcall btnAddCombo2Click(TObject *Sender);
	void __fastcall btnClearCombo1Click(TObject *Sender);
	void __fastcall btnClearCombo2Click(TObject *Sender);




private:	// User declarations
	void __fastcall PanelMouseEnter(TPanel *Sender);
	void __fastcall PanelMouseLeave(TPanel *Sender);
	void __fastcall PanelMouseDown(TPanel *Sender);
	void __fastcall OperationPanelMouseEnter(TPanel *Sender);
	void __fastcall OperationPanelMouseLeave(TPanel *Sender);
	void __fastcall OperationPanelMouseDown(TPanel *Sender);
	void __fastcall OperationPanelMouseUp(TPanel *Sender);
	void __fastcall AddItem(TListView* list, TColor color);
	void __fastcall RemoveItem(TListView* list);

	void ValidateListForItem(TListView* list, TListItem* item);
	void DrawIndicatorRectangle(TListItem *item, TColor color);
	void DrawRectangle(int x, int y, int width, int height, TColor color);
	void OnItemClick(TListItem* item);
	void OnComboAddItem(TComboBox* cbTarget);
	void OnComboClear(TComboBox* cbTarget);
	void WriteSettings();
	void LoadSettings();
	void OnShow();

	PixelLookup* plThread;

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
	void MoveVirtualCursor(TObject* sender);
	void OperationButtonClick();
	TPoint clickPoint1;
	TPoint clickPoint2;
	TPoint cursor1pos;
	TPoint cursor2pos;
	TPoint cursorDistance;
	char shortcut;
};

const TColor clPaleRed   = RGB(255,190,190);
const TColor clPaleGreen = RGB(163,255,176);
const TColor clHighlightRed = RGB(255,207,206);
const TColor clHighlightGreen = RGB(205,252,206);
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
#endif
