//---------------------------------------------------------------------------

#ifndef VirtualCursor1H
#define VirtualCursor1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmCursor1 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	//void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	TPoint delta;
	bool isDragging;
public:		// User declarations
	__fastcall TfrmCursor1(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TfrmCursor1 *frmCursor1;
//---------------------------------------------------------------------------

#endif
