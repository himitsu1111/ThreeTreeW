//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "ABSMain.hpp"
#include <DB.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeView1;
	TTreeView *TreeView2;
	TTreeView *TreeView3;
	TABSDatabase *ABSDatabase1;
	TABSTable *TB;
	TABSTable *Ceh;
	TABSQuery *ABSQuery1;
	TABSTable *Mod;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TButton *Button1;
	TButton *Button2;
	TMenuItem *N2;
	TPopupMenu *PopupMenu2;
	TMenuItem *NPodkat;
	TMenuItem *NOpen;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TPanel *Panel1;
	TEdit *EditTB;
	TStaticText *StaticText1TB;
	TStaticText *StaticText3Type;
	TStaticText *StaticText2Model;
	TStaticText *StaticText4Ceh;
	TStaticText *StaticText5INV;
	TEdit *EditModel;
	TEdit *EditType;
	TEdit *EditCeh;
	TEdit *EditInv;
	TGroupBox *GroupBox1;
	TButton *Button3;
	TMenuItem *N8;
	TABSQuery *ABSQuery2;
	TPanel *Panel2;
	TButton *Button4;
	TMenuItem *N9;
	TComboBox *ComboBox1;
	TPanel *Panel3;
	TComboBox *ComboBox2;
	TStaticText *StaticText1;
	TPanel *Panel4;
	TGroupBox *GroupBox2;
	TButton *Button5;
	TButton *Button6;
	TMenuItem *NDelete;
	TMainMenu *MainMenu1;
	TMenuItem *N1231;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N10;
	TMenuItem *N11;
	TEdit *Edit1;
	TButton *Button7;
	TMemo *Memo1;
	TOpenDialog *OpenDialog1;
	TTreeView *TreeView4;
	TTreeView *TreeView5;
	TStaticText *struktStanka;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall TreeView1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall TreeView1KeyPress(TObject *Sender, char &Key);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall TreeView2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall NPodkatClick(TObject *Sender);
	void __fastcall NOpenClick(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall NDeleteClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
