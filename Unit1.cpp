//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
#include "impfromtext.h"
#include "Node.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ABSMain"
#pragma resource "*.dfm"
TForm1 *Form1;
int K, Z, H, B;
bool TypeOrPlace = false; //метка для определения вида первого дерева.
						  //если false - по расположению
						  //если true - по моделям
int NomerGrupp=0; //номер группы, по которому выполняются SQL запросы для определенной группы
TTreeNode * Metka; //нод, по которому определяются операции над нодами.
					//нужен чтобы запоминать Index группы нодов, и не менять его переключением мышкой
					//в каждой операции над нодами необходимо присваивать метке свой индекс
struct TMyStr  
{               //структура для занесения информации в ноды
	int Chislo;
	String Komment;
};
//class TNodeOperations: public TForm1
//{
//	public:
//	TNodeOperations() : TForm1(0){};//!!!!!!!!!!
//	//TTreeView *TreeView1;
//	int DeleteNode();
//	int InsertNode();
//	void ChangeNode(TTreeNode * Nod, int Index)
//	{
//		ABSQuery1->SQL->Clear();
//		ABSQuery1->SQL->Text = "INSERT INTO TB (Name) values ('" + TreeView1->Selected->Text + "')";
//		ABSQuery1->ExecSQL();
//		ABSQuery1->Close();
//		Nod->Selected = true;
//		Index++;
//
//	};
//
//	private:
//
//} ;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)//ДОБАВИТЬ ПОДКАТАЛОГ++++
{
	Metka = TreeView1->Selected;
	Panel1->Visible = true;
	EditCeh->Enabled = true;
	EditCeh->SetFocus();
	StaticText4Ceh->Color = clLime;
	NomerGrupp = TreeView1->Selected->SelectedIndex + 1;
	switch (NomerGrupp)
	{
		case 2:	{
					Panel2->Caption = Metka->Text;
					EditCeh->Enabled = true;
					EditCeh->SetFocus();
					StaticText4Ceh->Color = clLime;

					EditTB->Enabled = false;
					EditInv->Enabled = false;
					EditModel->Enabled = false;
					EditType->Enabled = false;

					EditTB->Clear();
					EditInv->Clear();
					EditModel->Clear();
					EditType->Clear();

					StaticText1TB->Color = clBtnFace;
					StaticText3Type->Color = clBtnFace;
					StaticText5INV->Color = clBtnFace;
					StaticText2Model->Color = clBtnFace;
					break;
				}

		case 3:	{
					Panel2->Caption = Metka->Text;
					EditModel->Enabled = true;
					EditType->Enabled = true;
					
					EditModel->SetFocus();
					EditCeh->Enabled = false;
					EditTB->Enabled = false;
					EditInv->Enabled = false;

					EditCeh->Clear();
					EditTB->Clear();
					EditInv->Clear();
					EditModel->Clear();
					EditType->Clear();


					StaticText2Model->Color = clLime;
					StaticText3Type->Color = clLime;
					StaticText1TB->Color = clBtnFace;
					StaticText5INV->Color = clBtnFace;
					StaticText4Ceh->Color = clBtnFace;
					break;
				}
		 case 4:{
                    Panel2->Caption = Metka->Text;
					EditModel->Enabled = false;
					EditType->Enabled = false;
					EditCeh->Enabled = false;
					EditInv->Enabled = true;
					EditTB->Enabled = false;
					EditInv->SetFocus();

					EditModel->Clear();
					EditType->Clear();
					EditCeh->Clear();
					EditTB->Clear();

					StaticText3Type->Color = clBtnFace;
					StaticText2Model->Color = clBtnFace;
					StaticText1TB->Color = clBtnFace;
					StaticText5INV->Color = clLime;
					StaticText4Ceh->Color = clBtnFace;
					break;
				}

		 default:
				;

	}
	Button3->Caption = "Добавить(под)";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   
	TreeView1->SendToBack();
	Height = 638;
	Width = 625;
	//BorderStyle = bsSingle;
	struktStanka->Caption = "";
	Panel3->SendToBack();
	AnsiString DataPath = GetCurrentDir();
	ABSDatabase1->DatabaseFileName = DataPath + "\\TehDerevo.ABS";
	TreeView1->Items->Clear();

	//первая группа нодов
	BuildNode("select Name from TB",
			  "Name",
			  NULL,
			  TreeView1,
			  1,
			  ABSQuery1);

	//вторая группа нодов
	TTreeNode* siblingNode = TreeView1->Items->GetFirstNode();
	while (siblingNode)
	{
		BuildNode("select Nomer from Ceh where id_TB=(select id from TB where Name='" + siblingNode->Text + "')",
				  "Nomer",
				  siblingNode,
				  TreeView1,
				  2,
				  ABSQuery1);
		siblingNode = siblingNode->getNextSibling();
	}
	TTreeNode* childNode;
	//третья группа нодов
	for (siblingNode = TreeView1->Items->GetFirstNode(); siblingNode; siblingNode = siblingNode->getNextSibling())
	{
		childNode = siblingNode->getFirstChild();
		while (childNode)
		{
			BuildNode("select NM from Mod where id in(select id_Model from Model_Ceh where id_Ceh=(select id from Ceh where Nomer='"
					  + childNode->Text + "'))",
					  "NM",
					  childNode,
					  TreeView1,
					  3,
					  ABSQuery1);
			childNode = childNode->getNextSibling();
		}
	}
	//четвертая группа нодов
	TTreeNode* child2Node;
	for (siblingNode = TreeView1->Items->GetFirstNode(); siblingNode; siblingNode = siblingNode->getNextSibling())
	for (childNode = siblingNode->getFirstChild(); childNode; childNode = childNode->getNextSibling())
	{
		child2Node = childNode->getFirstChild();
		while (child2Node)
		{
			BuildNode("select I_N from INV where id_Mod=(select id from Mod where NM='" +
						child2Node->Text + "') and id_Ceh=(select id from Ceh where Nomer='"
						+ childNode->Text +"')",
					  "I_N",
					  child2Node,
					  TreeView1,
					  4,
					  ABSQuery1);
			child2Node = childNode->getNextSibling();
		}
	}
	/*
	ABSQuery1->SQL->Text = "select Name from TB";
	ABSQuery1->Active = true;
	while (!ABSQuery1->Eof)
	{
		TreeView1->Items->Add(NULL, ABSQuery1->FieldByName("Name")->AsString)->SelectedIndex = 1;
		ABSQuery1->Next();   //заполняются ноды группы БЮРО
	}
	ABSQuery1->Close();
	TTreeNode* siblingNode = TreeView1->Items->GetFirstNode(); //создается первый НОД
	while (siblingNode)
	{
		ABSQuery1->SQL->Text = "select Nomer from Ceh where id_TB=(select id from TB where Name='" + siblingNode->Text + "')";
		ABSQuery1->Active = true;
		while (!ABSQuery1->Eof)
			{
				TreeView1->Items->AddChild(siblingNode, ABSQuery1->FieldByName("Nomer")->AsString)->SelectedIndex = 2;
				ABSQuery1->Next();  //заполняются ноды группы ЦЕХА
			}
		siblingNode = siblingNode->getNextSibling();
		ABSQuery1->Close();
	}
	siblingNode = TreeView1->Items->GetFirstNode(); // - ноды группы цехов
	TTreeNode* childNode; // - ноды группы ИНВЕНТАРНЫХ НОМЕРОВ

	while (siblingNode)
	{
		if (siblingNode->getFirstChild()) //если есть потомок у первой группы нодов
		{
			childNode = siblingNode->getFirstChild();
			while (childNode) //перебор второй группы нодов
			{
				ABSQuery1->SQL->Text = "select NM from Mod where id in(select id_Model from Model_Ceh where id_Ceh=(select id from Ceh where Nomer='" + childNode->Text + "'))";
				ABSQuery1->Active = true;
				while (!ABSQuery1->Eof)
				{
					TreeView1->Items->AddChild(childNode, ABSQuery1->FieldByName("NM")->AsString)->SelectedIndex = 3;
					ABSQuery1->Next();    //заполняются ноды группы ИНВЕНТАРНЫХ
				}
				childNode = childNode->getNextSibling();
			}
		}
		siblingNode = siblingNode->getNextSibling();
	}
	TTreeNode* child2Node; //- ноды группы МОДЕЛЕЙ
	siblingNode = TreeView1->Items->GetFirstNode();
	while (siblingNode)
	{
		if (siblingNode->getFirstChild())
		{
			childNode = siblingNode->getFirstChild();
			while (childNode)
			{
				if (childNode->getFirstChild())
				{
					child2Node = childNode->getFirstChild();
					while (child2Node)
					{
						ABSQuery1->SQL->Text ="select I_N from INV where id_Mod=(select id from Mod where NM='" +
						child2Node->Text + "') and id_Ceh=(select id from Ceh where Nomer='" + childNode->Text +"')";
						ABSQuery1->Active = true;
						while (!ABSQuery1->Eof)
						{
							TreeView1->Items->AddChild(child2Node, ABSQuery1->FieldByName("I_N")->AsString)->SelectedIndex = 4;
							ABSQuery1->Next();
						}
						child2Node = child2Node->getNextSibling();
					}
				}
				childNode = childNode->getNextSibling();
			}
		}
		siblingNode = siblingNode->getNextSibling();
	}
	*/


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)//ПО МОДЕЛЯМ!!!
{
	AnsiString DataPath = GetCurrentDir();
	ABSDatabase1->DatabaseFileName = DataPath + "\\TehDerevo.ABS";
	TreeView1->Items->Clear();
	ABSQuery1->SQL->Text = "select distinct Vidt from Types";
	ABSQuery1->Active = true;
	while (!ABSQuery1->Eof)
	{
		TreeView1->Items->Add(NULL, ABSQuery1->FieldByName("Vidt")->AsString)->SelectedIndex = 1;
		ABSQuery1->Next();   //заполняются ноды группы ТИП
	}
	ABSQuery1->Close();
	TTreeNode* siblingNode = TreeView1->Items->GetFirstNode(); //создается первый НОД
	while (siblingNode)
	{                                          // 
		ABSQuery1->SQL->Text = "select NM from Mod where id_Type IN(select id from Types where Vidt='"
		+ siblingNode->Text + "')";
		ABSQuery1->Active = true;
		while (!ABSQuery1->Eof)
			{
				TreeView1->Items->AddChild(siblingNode, ABSQuery1->FieldByName("NM")->AsString)->SelectedIndex = 2;
				ABSQuery1->Next();  //заполняются ноды группы ЦЕХА
			}
		siblingNode = siblingNode->getNextSibling();
		ABSQuery1->Close();
	}
	siblingNode = TreeView1->Items->GetFirstNode(); // - ноды группы цехов
	TTreeNode* childNode; // - ноды группы ИНВЕНТАРНЫХ НОМЕРОВ

	while (siblingNode)
	{
		if (siblingNode->getFirstChild()) //если есть потомок у первой группы нодов
		{
			childNode = siblingNode->getFirstChild();
			while (childNode) //перебор второй группы нодов
			{
				ABSQuery1->SQL->Text = "select Nomer from Ceh where id IN(select id_Ceh from Model_Ceh where id_Model=(select id from Mod where NM='"
				+ childNode->Text + "'))";
				ABSQuery1->Active = true;
				while (!ABSQuery1->Eof)
				{
					TreeView1->Items->AddChild(childNode, ABSQuery1->FieldByName("Nomer")->AsString)->SelectedIndex = 3;
					ABSQuery1->Next();    //заполняются ноды группы ИНВЕНТАРНЫХ
				}
				childNode = childNode->getNextSibling();
			}
		}
		siblingNode = siblingNode->getNextSibling();
	}
	ABSQuery1->Close();
	TTreeNode* child2Node; //- ноды группы МОДЕЛЕЙ
	siblingNode = TreeView1->Items->GetFirstNode();
	while (siblingNode)
	{
		if (siblingNode->getFirstChild())
		{
			childNode = siblingNode->getFirstChild();
			while (childNode)
			{
				if (childNode->getFirstChild())
				{
					child2Node = childNode->getFirstChild();
					while (child2Node)
					{
						ABSQuery1->SQL->Text = "select I_N from INV where id_Ceh=(select id from Ceh where Nomer='" +
						child2Node->Text + "') and id_Mod=(select id from Mod where NM='" + childNode->Text +"')";
						ABSQuery1->Active = true;
						while (!ABSQuery1->Eof)
						{
							TreeView1->Items->AddChild(child2Node, ABSQuery1->FieldByName("I_N")->AsString)->SelectedIndex = 4;
							ABSQuery1->Next();
						}
						child2Node = child2Node->getNextSibling();
					}
				}
				childNode = childNode->getNextSibling();
			}
		}
		siblingNode = siblingNode->getNextSibling();
	}
    TypeOrPlace = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form1->OnCreate(Sender);
	TypeOrPlace = false;	
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N2Click(TObject *Sender)  //ОТКРЫТЬ++++++++++++++++++
{

//	TreeView2->SendToBack();
	AnsiString DataPath = GetCurrentDir();
	ABSDatabase1->DatabaseFileName = DataPath + "\\TehDerevo.ABS";
	//ID инвентарного, полученный из тривью1
	if (TreeView1->GetNodeAt(K,Z)->SelectedIndex==4)                                         //нужен для связи с первым три вью и инвентарным
	{
	   
		TreeView2->Items->Clear();
		/*
		ABSQuery1->SQL->Text = "select Naim from Strukt";
		ABSQuery1->Active = true;
		while (!ABSQuery1->Eof)
		{
			TreeView2->Items->Add(NULL, ABSQuery1->FieldByName("Naim")->AsString)->SelectedIndex = 1;
			ABSQuery1->Next();   //заполняются ноды группы МЕХАНИКА И ТД
		}
		ABSQuery1->Close();
		TTreeNode* siblingNode = TreeView2->Items->GetFirstNode();
		while (siblingNode)
		{    // второе дерево связывается с нодом ИНВЕНТАРНЫЙ в первом дереве. в зависимости от инвентарного, должны появляться ПГД-РГ
			ABSQuery1->SQL->Text = "select Naim from Strukt_2 where id IN(select id_S2 from Strukturs where id_Inv=(select id from INV where I_N='"
			+ TreeView1->GetNodeAt(K,Z)->Text + "') and id_S1=(select id from Strukt where Naim='" + siblingNode->Text + "'))";
			ABSQuery1->Active = true;
			while (!ABSQuery1->Eof)
				{
					TreeView2->Items->AddChild(siblingNode, ABSQuery1->FieldByName("Naim")->AsString)->SelectedIndex = 2;
					ABSQuery1->Next();  //
				}
			siblingNode = siblingNode->getNextSibling();
			ABSQuery1->Close();
		}
		*/

		//первая группа нодов ТВ2
		BuildNode("select Naim from Strukt",
				  "Naim",
				  NULL,
				  TreeView2,
				  1,
				  ABSQuery1);
		//вторая группа нодов ТВ2
		TTreeNode* siblingNode = TreeView2->Items->GetFirstNode();
		while (siblingNode)
		{
			BuildNode("select Naim from Strukt_2 where id IN(select id_S2 from Strukturs where id_Inv=(select id from INV where I_N='"
					  + TreeView1->GetNodeAt(K,Z)->Text + "') and id_S1=(select id from Strukt where Naim='"
					  + siblingNode->Text + "'))",
					  "Naim",
					  siblingNode,
					  TreeView2,
					  2,
					  ABSQuery1);
			siblingNode = siblingNode->getNextSibling();
		}

		//третья группа нодов ТВ2
		//остановился тут 4.09.2015++++++++++++++++
		TTreeNode* childNode;
		for (siblingNode = TreeView2->Items->GetFirstNode(); siblingNode; siblingNode = siblingNode->getNextSibling())
		{
			childNode = siblingNode->getFirstChild();
			while (childNode)
			{
				BuildNode("select Naim from Strukt_3 where id in(select id_S3 from Strukturs_23 where id_strukturs in(select id from Strukturs where id_S1=(select id from Strukt where Naim='"
						  + siblingNode->Text + "') and id_Inv in(select id from INV where I_N ='" + TreeView1->GetNodeAt(K,Z)->Text + "')) and id_S2=(select id from Strukt_2 where Naim='" + childNode->Text + "'))",
						  "Naim",
						  childNode,
						  TreeView2,
						  3,
						  ABSQuery1);
				childNode = childNode->getNextSibling();
			}
		}

		//новая часть с 10.08.2015+++++++++
		/*
		TTreeNode* siblingNode = TreeView2->Items->GetFirstNode(); // - ноды группы СИСТЕМА
		TTreeNode* childNode; // - ноды группы ПОДСИСТЕМА

		while (siblingNode)
		{
			if (siblingNode->getFirstChild()) //если есть потомок у первой группы нодов
			{
				childNode = siblingNode->getFirstChild();
				while (childNode) //перебор второй группы нодов
				{
					ABSQuery1->SQL->Text = "select Naim from Strukt_3 where id IN(select id_S3 from Strukturs_23 where id_strukturs=(select id from Strukturs where id_Inv=(select id from INV where I_N='"
					+ TreeView1->GetNodeAt(K,Z)->Text + "') and id_S2=(select id from Strukt_2 where Naim='" + childNode->Text + "') and id_S1=(select id from Strukt where Naim='" + siblingNode->Text + "')))";
					ABSQuery1->Active = true;
					while (!ABSQuery1->Eof)
					{
						TreeView2->Items->AddChild(childNode, ABSQuery1->FieldByName("Naim")->AsString)->SelectedIndex = 3;
						ABSQuery1->Next();    //заполняются ноды группы ИНВЕНТАРНЫХ
					}
					childNode = childNode->getNextSibling();
				}
			}
			siblingNode = siblingNode->getNextSibling();
		}
		ABSQuery1->Close();
		*/
		//конец новой части++++++++++++++++
	}
	else
	{
		ShowMessage("Не выбран инвентарный!");
	}
	Metka = TreeView1->Selected;

	TTreeNode * level_4;
	TTreeNode * level_3;
	TTreeNode * level_2;
	TTreeNode * level_1;

	level_3 = Metka->Parent;
	level_2 = level_3->Parent;
	level_1 = level_2->Parent;
	struktStanka->Caption = "Структура станка: " + level_3->Text /*модель станка */+ ", "
	+ Metka->Text + /*инвентарный */", " + level_2->Text;

	Panel3->Visible = true;
	TreeView2->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TreeView1MouseDown(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y)
	  //событие для отображения определенных строк контекстного меню
{
 K= X;  //координаты мыши
 Z= Y;
 if ((X!=0) && (Y!=0))      
 TreeView1->Enabled = true;
 
N5->Visible = true;
N1->Visible = false;
// TreeView1->GetNodeAt(K,Z);
 //скрывается кнопка ОТКРЫТЬ из всплывающего меню1. чтобы не было возможности
 //вызова второго дерева без выбора инвентарного. 4 - индекс группы нодов с инвентарными.
 if (TreeView1->Items->GetFirstNode() && TreeView1->GetNodeAt(K,Z))
 {                //условие для исключения ошибки получения индекса несуществующего нода
	 //
	 if (TypeOrPlace)
		N8->Visible = false;

	 if (!TypeOrPlace)
	 {
		N8->Visible = true;
        N7->Visible = true;
	 }
	 if (TypeOrPlace)
		 N7->Visible = false;

	 if (TypeOrPlace && TreeView1->GetNodeAt(K,Z)->SelectedIndex==1)
		 N7->Visible = true;


	 if (TreeView1->GetNodeAt(K,Z)->SelectedIndex!=4)
	 {
		N2->Visible = false;
		N9->Visible = false;
	 }
	 if (TreeView1->GetNodeAt(K,Z)->SelectedIndex==4)
	 {
		N2->Visible = true;
		N9->Visible = true;
	 }
	 //тоже самое с кнопкой ДОБАВИТЬ.
	 if ((TreeView1->GetNodeAt(K,Z)->SelectedIndex!=1) && TypeOrPlace)
	 {
		N5->Visible = false;
	 }
	 if ((TreeView1->GetNodeAt(K,Z)->SelectedIndex==1) || !TypeOrPlace)
	 {
		N5->Visible = true;
	 }
	 //тоже самое с кнопкой УДАЛИТЬ
	 if (!TypeOrPlace && TreeView1->GetNodeAt(K,Z)->SelectedIndex!=4)
		N1->Visible = true;
	 if (TypeOrPlace && TreeView1->GetNodeAt(K,Z)->SelectedIndex==4)
		N1->Visible = false;
	  //тоже самое с кнопкой ДОБАВИТЬ ВЕТВЬ
	 if (TreeView1->GetNodeAt(K,Z)->SelectedIndex==1)
		N8->Visible = true;
	 if (TypeOrPlace || TreeView1->GetNodeAt(K,Z)->SelectedIndex!=1)
		N8->Visible = false;
 }
   //	Label1->Caption = TreeView1->GetNodeAt(X,Y)->Text + " " + IntToStr(TreeView1->GetNodeAt(X,Y)->SelectedIndex);  //определяется узел в дереве
}
//---------------------------------------------------------------------------



void __fastcall TForm1::TreeView1KeyPress(TObject *Sender, char& Key)
{
	if (Key==VK_RETURN)
	{
        Button1->Caption = "123123";
    }
//			switch (TreeView1->Selected->SelectedIndex)//выбор SQL запроса в зависимости от номера ГРУППЫ нодов
//			{
//				case 1: {  //группа 1 (бюро)
//							TMyStr * Info = (TMyStr*)TreeView1->Selected->Data;//из нода выносится структурная инфа
//							if (TreeView1->Selected->StateIndex==5) 
//							{	
//								ABSQuery1->SQL->Clear();
//								ABSQuery1->SQL->Text = "update TB set Name='" + TreeView1->Selected->Text + "' where id=(select id from TB where Name='" + Info->Komment + "')";
//								ABSQuery1->ExecSQL();
//								ABSQuery1->Close();
//								break; 							
//							}
//							ABSQuery1->SQL->Clear();
//							ABSQuery1->SQL->Text = "INSERT INTO TB (Name) values ('" + TreeView1->Selected->Text + "')";
//							ABSQuery1->ExecSQL();
//							ABSQuery1->Close();
//							break;
//						}
//				default:{
//							
//							break;
//						}
//						;		
//			}
//
//		TreeView1->ReadOnly = true;
//	}
	
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N5Click(TObject *Sender)//ДОБАВИТЬ
{
//    TTreeNode *Node;
//	Node = TreeView1->Items->Add(TreeView1->GetNodeAt(K,Z), "ТБ №");//добавляет близнеца в выбранном узле
//	Node->SelectedIndex = 1;                                       //только в группе Тех Бюро.
//	Node->Selected = true;
//	TreeView1->ReadOnly = false;
//	Node->EditText();
	Panel1->Visible = true;
	EditTB->Enabled = true;
	EditTB->SetFocus();
	StaticText1TB->Color = clLime;
	NomerGrupp = 1;
	Metka = NULL;

	EditCeh->Enabled = false;
	EditInv->Enabled = false;
	EditModel->Enabled = false;
	EditType->Enabled = false;
	EditCeh->Clear();
	EditInv->Clear();
	EditModel->Clear();
	EditType->Clear();

	StaticText2Model->Color = clBtnFace;
	StaticText3Type->Color = clBtnFace;
	StaticText4Ceh->Color = clBtnFace;
	StaticText5INV->Color = clBtnFace;

	Button3->Caption = "Добавить";
	Panel2->Caption = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)//ИЗМЕНИТЬ
{
	TMyStr * Info = new TMyStr;
 	Metka = TreeView1->GetNodeAt(K,Z);//
//	TNodeOperations * ChangerK = new TNodeOperations;
	Info->Komment = Metka->Text;
	Metka->Data = Info;//записываем в нод информацию из структуры
					  //информация содержит текст нода
	Metka->Selected = true;
	TreeView1->ReadOnly = false; //открывает возможность редактирования узла. текст сразу выделяется для редактирования
	Metka->StateIndex = 5;
	NomerGrupp = TreeView1->Selected->SelectedIndex;
	Panel1->Visible = true;
	switch (NomerGrupp)
		{
			case 1: {
						if (TypeOrPlace)
						{
							EditType->Enabled = true;
							EditType->SetFocus();
							StaticText3Type->Color = clLime;
							EditCeh->Enabled = false;
							EditInv->Enabled = false;
							EditModel->Enabled = false;
							EditTB->Enabled = false;
							StaticText2Model->Color = clBtnFace;
							StaticText1TB->Color = clBtnFace;
							StaticText4Ceh->Color = clBtnFace;
							StaticText5INV->Color = clBtnFace;
							break;
						}
					  //	Panel2->Caption = Metka->Text;
						EditTB->Enabled = true;
						EditTB->SetFocus();
						StaticText1TB->Color = clLime;
						EditCeh->Enabled = false;
						EditInv->Enabled = false;
						EditModel->Enabled = false;
						EditType->Enabled = false;
						StaticText2Model->Color = clBtnFace;
						StaticText3Type->Color = clBtnFace;
						StaticText4Ceh->Color = clBtnFace;
						StaticText5INV->Color = clBtnFace;
						break;
					}
			case 2: {
                    	if (TypeOrPlace)
						{
							EditType->Enabled = false;
							
							StaticText2Model->Color = clLime;
							EditCeh->Enabled = false;
							EditInv->Enabled = false;
							EditModel->Enabled = true;
							EditTB->Enabled = false;
							EditModel->SetFocus();
							StaticText3Type->Color = clBtnFace;
							StaticText1TB->Color = clBtnFace;
							StaticText4Ceh->Color = clBtnFace;
							StaticText5INV->Color = clBtnFace;
							break;
						}
						EditTB->Enabled = false;
						EditCeh->Enabled = true;
						EditCeh->SetFocus();
						EditInv->Enabled = false;
						EditModel->Enabled = false;
						EditType->Enabled = false;

						StaticText1TB->Color = clBtnFace;
						StaticText2Model->Color = clBtnFace;
						StaticText3Type->Color = clBtnFace;
						StaticText4Ceh->Color = clLime;
						StaticText5INV->Color = clBtnFace;
						break;
					}
			case 3: {
                    	if (TypeOrPlace)
						{
							EditType->Enabled = false;
							
							EditTB->Enabled = false;
							EditCeh->Enabled = true;
							EditCeh->SetFocus();
							EditInv->Enabled = false;
							EditModel->Enabled = false;
							EditType->Enabled = false;
							StaticText1TB->Color = clBtnFace;
							StaticText2Model->Color = clBtnFace;
							StaticText3Type->Color = clBtnFace;
							StaticText4Ceh->Color = clLime;
							StaticText5INV->Color = clBtnFace;
							break;
						}
						EditTB->Enabled = false;
						EditCeh->Enabled = false;
						EditInv->Enabled = false;
						EditModel->Enabled = true;
						EditType->Enabled = false;
						EditModel->SetFocus();

						StaticText1TB->Color = clBtnFace;
						StaticText2Model->Color = clLime;
						StaticText3Type->Color = clBtnFace;
						StaticText4Ceh->Color = clBtnFace;
						StaticText5INV->Color = clBtnFace;
						break;
					}
			case 4: {
						EditTB->Enabled = false;
						EditCeh->Enabled = false;
						EditInv->Enabled = true;
						EditModel->Enabled = false;
						EditType->Enabled = false;
						EditInv->SetFocus();

						StaticText1TB->Color = clBtnFace;
						StaticText2Model->Color = clBtnFace;
						StaticText3Type->Color = clBtnFace;
						StaticText4Ceh->Color = clBtnFace;
						StaticText5INV->Color = clLime;
						break;
					}
			default:
			;
		}
	Button3->Caption = "Изменить";
  //  delete Info;
//	ChangerK->ChangeNode(Node, TreeView1->GetNodeAt(K,Z)->SelectedIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)//УДАЛИТЬ
{
Metka = TreeView1->GetNodeAt(K,Z);
NomerGrupp = TreeView1->Selected->SelectedIndex;
AnsiString Node = TreeView1->GetNodeAt(K,Z)->Text;
switch (NomerGrupp)
	{
		case 1: {
					if (TypeOrPlace)
					{
						if (MessageDlg("Действительно удалить " + Metka->Text + "?", mtWarning, mbOKCancel,0)==mrOk)
						{
                        	ABSQuery1->SQL->Clear();
							ABSQuery1->SQL->Text = "delete from Types where Vidt='" + Metka->Text + "'";
							ABSQuery1->ExecSQL();
							ABSQuery1->Close();
                            TreeView1->Selected->Delete();
						}
						break;
					}
					if (MessageDlg("Действительно удалить " + Metka->Text + "?", mtWarning, mbOKCancel,0)==mrOk)
					{   //удаление из ПО РАСПОЛОЖЕНИЮ удаляет ТОЛЬКО по группе нодов -  ТЕХ БЮРО!!!
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from INV where id_TB IN(select id from TB where Name='" + Metka->Text + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Mod where id IN(select id_Model from Model_Ceh where id_Ceh IN(select id from Ceh where id_TB IN(select id from TB where Name='"
						+ Metka->Text + "')))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Model_Ceh where id_Ceh IN(select id from Ceh where id_TB=(select id from TB where Name='"
						+ Metka->Text + "'))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Ceh where id_TB IN(select id from TB where Name='" + Metka->Text + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from TB where Name='" + Metka->Text + "'";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						TreeView1->Selected->Delete();
						break;
					}

				}      //удаление по ЦЕХАМ
		case 2: {   if (MessageDlg("Действительно удалить " + Metka->Text + "?", mtWarning, mbOKCancel,0)==mrOk)
					{
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from INV where id_Ceh IN(select id from Ceh where Nomer='" + Metka->Text + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Mod where id IN(select id_Model from Model_Ceh where id_Ceh=(select id from Ceh where Nomer='"
						+ Metka->Text + "'))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Model_Ceh where id_Ceh IN(select id from Ceh where Nomer=('"
						+ Metka->Text + "'))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Ceh where Nomer='" + Metka->Text + "'";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						TreeView1->Selected->Delete();
					}
					break;
				}       //удаление по МОДЕЛЯМ
		case 3: {   if (MessageDlg("Действительно удалить " + Metka->Text + "?", mtWarning, mbOKCancel,0)==mrOk)
					{
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from INV where id_Mod IN(select id from Mod where NM='" + Metka->Text + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Model_Ceh where id_Model IN(select id from Mod where NM=('"
						+ Metka->Text + "'))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Mod where NM='" + Metka->Text + "'";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						TreeView1->Selected->Delete();
					}
					break;
				}
        case 4: {   if (MessageDlg("Действительно удалить " + Metka->Text + "?", mtWarning, mbOKCancel,0)==mrOk)
					{
                    	ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from INV where I_N='" + Metka->Text + "'";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

                        TreeView1->Selected->Delete();
                    }
                    break;
				}

		default:
		;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)//добавление в таблицы++++++++++++++++++
{
	switch (NomerGrupp)//выбор SQL запроса в зависимости от номера ГРУППЫ нодов
	{
		case 1: {  //группа 1 (бюро)  добавляет и изменяет ТОЛЬКО группу бюро
					if (Metka)//проверка на существование нодов. если нодов нет, то работает только ДОБАВИТЬ
					if (Metka->StateIndex==5)//проверка на ИЗМЕНИТЬ
					{
						TMyStr * Info = (TMyStr*)Metka->Data;//из нода выносится структурная инфа
						if (TypeOrPlace)
						{	//
							ABSQuery1->SQL->Clear();
							ABSQuery1->SQL->Text = "update Types set Vidt='" + EditType->Text
							+ "' where id=(select id from Types where Vidt='" + Info->Komment + "')";
							ABSQuery1->ExecSQL();
							ABSQuery1->Close();
							Metka->Text = EditType->Text;
							Button3->Caption = "Добавить";
							EditType->Clear();
							EditType->Enabled = false;
							StaticText3Type->Color = clBtnFace;
							Panel1->Visible = false;
                            break;
						}
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "update TB set Name='" + EditTB->Text
						+ "' where id=(select id from TB where Name='" + Info->Komment + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
						Metka->Text = EditTB->Text;
                        Button3->Caption = "Добавить";
						EditTB->Clear();
						EditTB->Enabled = false;
						StaticText1TB->Color = clBtnFace;
						Panel1->Visible = false;
						break;
					}
					ABSQuery1->SQL->Clear();
					ABSQuery1->SQL->Text = "INSERT INTO TB (Name) values ('"
					+ EditTB->Text + "')";
					ABSQuery1->ExecSQL();
					ABSQuery1->Close();
					TreeView1->Items->Add(NULL, EditTB->Text)->SelectedIndex = 1;

					EditTB->Clear();
					EditTB->Enabled = false;
					StaticText1TB->Color = clBtnFace;
					Panel1->Visible = false;
					NomerGrupp = 0;
					break;
				}
		case 2: {    //добавляет ТОЛЬКО цеха
					if (Metka)
					if (Metka->StateIndex==5)
					{   TMyStr * Info = (TMyStr*)Metka->Data;//из нода выносится структурная инфа            //меняет цеха
						if (TypeOrPlace)
						{         //меняет МОДЕЛИ, а не цеха
							//
							ABSQuery1->SQL->Clear();
							ABSQuery1->SQL->Text = "update Mod set NM='" + EditModel->Text
						+ "' where id=(select id from Mod where NM='" + Info->Komment + "')";
							ABSQuery1->ExecSQL();
							ABSQuery1->Close();
							Metka->Text = EditModel->Text;
							Button3->Caption = "Добавить";
							EditModel->Clear();
							EditModel->Enabled = false;
							StaticText2Model->Color = clBtnFace;
							Panel1->Visible = false;
							break;
						}
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "update Ceh set Nomer='" + EditCeh->Text
						+ "' where id=(select id from Ceh where Nomer='" + Info->Komment + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
						Metka->Text = EditCeh->Text;
						Button3->Caption = "Добавить";
						EditCeh->Clear();
						EditCeh->Enabled = false;
						StaticText4Ceh->Color = clBtnFace;
						Panel1->Visible = false;
						break;
					}
					ABSQuery1->SQL->Clear();
					ABSQuery1->SQL->Text = "INSERT INTO Ceh (Nomer, id_TB) values ('" + EditCeh->Text
					+ "', (select id from TB where Name='" + Metka->Text + "'))";
					ABSQuery1->ExecSQL();
					ABSQuery1->Close();
					TreeView1->Items->AddChild(Metka, EditCeh->Text)->SelectedIndex = 2;

					EditCeh->Clear();
					EditCeh->Enabled = false;
					StaticText4Ceh->Color = clBtnFace;
					Panel1->Visible = false;
					NomerGrupp = 0;
					break;
				}
		case 3: {    //МОДЕЛИ
					if (Metka)
					if (Metka->StateIndex==5)
					{
						TMyStr * Info = (TMyStr*)Metka->Data;//из нода выносится структурная инфа
                        if (TypeOrPlace)                    //ОСТАНОВИЛСЯ ТУТ
						{         //меняет ЦЕХА, а не модели
							//
							ABSQuery1->SQL->Clear();
							ABSQuery1->SQL->Text = "update Ceh set Nomer='" + EditCeh->Text
						+ "' where id=(select id from Ceh where Nomer='" + Info->Komment + "')";
							ABSQuery1->ExecSQL();
							ABSQuery1->Close();
							Metka->Text = EditCeh->Text;
							Button3->Caption = "Добавить";
							EditCeh->Clear();
							EditCeh->Enabled = false;
							StaticText4Ceh->Color = clBtnFace;
							Panel1->Visible = false;
							break;
						}
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "update Mod set NM='" + EditModel->Text
						+ "' where id=(select id from Mod where NM='" + Info->Komment + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
						Metka->Text = EditModel->Text;
						Button3->Caption = "Добавить";
						EditModel->Clear();
						EditModel->Enabled = false;
						StaticText2Model->Color = clBtnFace;
						Panel1->Visible = false;
						break;
					}
					   //------------------------------------------------
					ABSQuery2->SQL->Clear();
					ABSQuery2->SQL->Text = "select id from Types where Vidt='" + EditType->Text + "'";
					ABSQuery2->Active = true;
					if (ABSQuery2->FieldByName("id")->AsString=="")
					{
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "INSERT INTO Types (Vidt) values ('" + EditType->Text + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
					}   //-----------------проверка есть ли уже запись в таблице Типов с таким же именем
//					if (ABSQuery2->FieldCount)
//					{
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "INSERT INTO Mod (NM, id_Type) values ('" + EditModel->Text
					+ "', (select id from Types where Vidt='" + EditType->Text + "'))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
				
						ABSQuery2->Close();

						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "INSERT INTO Model_Ceh (id_Ceh, id_Model) values ((select id from Ceh where Nomer='"
						+ Metka->Text + "'), (select id from Mod where NM='" + EditModel->Text + "'))";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();

						TreeView1->Items->AddChild(Metka, EditModel->Text)->SelectedIndex = 3;
				  //	}
					EditCeh->Clear();
					EditCeh->Enabled = false;
					StaticText4Ceh->Color = clBtnFace;
					Panel1->Visible = false;
					NomerGrupp = 0;
					break;
				}
		case 4: {   //ИНВЕНТАРНЫЕ
                    if (Metka)
					if (Metka->StateIndex==5)
					{
						TMyStr * Info = (TMyStr*)Metka->Data;//из нода выносится структурная инфа
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "update INV set I_N='" + EditInv->Text
						+ "' where id=(select id from Ceh where Nomer='" + Info->Komment + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
						Metka->Text = EditInv->Text;
						Button3->Caption = "Добавить";
						EditInv->Clear();
						EditInv->Enabled = false;
						StaticText5INV->Color = clBtnFace;
						Panel1->Visible = false;
						break;
					}
					 //мега запрос на добавление в таблицу инвентарных
					ABSQuery1->SQL->Clear();
					ABSQuery1->SQL->Text = "INSERT INTO INV (I_N, id_Mod, id_Ceh, id_TB, id_Type) values ('" + EditInv->Text
					+ "', (select id from Mod where NM ='" + Metka->Text
					+"'),(select distinct id_Ceh from Model_Ceh where id_Model=(select id from Mod where NM='"+ Metka->Text
					+"')),(select id_TB from Ceh where id=(select id_Ceh from Model_Ceh where id_Model=(select id from Mod where NM='"+ Metka->Text
					+"'))), (select id_Type from Mod where NM='" + Metka->Text + "'))";
					ABSQuery1->ExecSQL();
					ABSQuery1->Close();

					TreeView1->Items->AddChild(Metka, EditInv->Text)->SelectedIndex = 4;
					EditInv->Clear();
					EditInv->Enabled = false;
					StaticText5INV->Color = clBtnFace;
					Panel1->Visible = false;
					NomerGrupp = 0;
					break;
				}
		default:{   //копирование структуры ТриВью2
					//если некая структура у инвентарного УЖЕ существует,
					//то она удаляется и на её место копируется другая
					ABSQuery2->SQL->Clear();
					ABSQuery2->SQL->Text = "select distinct id_Inv from Strukturs where id_Inv=(select id from INV where I_N='" + ComboBox1->Text + "')";
					ABSQuery2->Active = true;
					if (ABSQuery2->FieldByName("id_Inv")->AsString!="")
					{
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "delete from Strukturs where id_Inv=(select id from INV where I_N='" + ComboBox1->Text + "')";
						ABSQuery1->ExecSQL();
						ABSQuery1->Close();
					}
					ABSQuery2->Close();

					ABSQuery2->SQL->Clear();
					ABSQuery2->SQL->Text = "select id_S2, id_S1 from Strukturs where id_Inv=(select id from INV where I_N='" + Metka->Text + "')";
					ABSQuery2->Active = true;
					while (!ABSQuery2->Eof)
					{
						ABSQuery1->SQL->Clear();
						ABSQuery1->SQL->Text = "insert into Strukturs (id_Inv, id_S2, id_S1) values ((select id from INV where I_N='" +
						ComboBox1->Text + "'), '" + ABSQuery2->FieldByName("id_S2")->AsString + "', '"
						+ ABSQuery2->FieldByName("id_S1")->AsString + "')";
						ABSQuery1->ExecSQL();
						ABSQuery2->Next();
					}
					ABSQuery2->Close();

                    Button4->Click();
					break;
				}
				;
	}
	Panel2->Caption = "";
	Metka = NULL;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button4Click(TObject *Sender) //ОТМЕНА
{
	Panel2->Caption = "";
	Metka = NULL;

	EditCeh->Clear();
	EditTB->Clear();
	EditInv->Clear();
	EditModel->Clear();
	EditType->Clear();


	StaticText2Model->Color = clBtnFace;
	StaticText3Type->Color = clBtnFace;
	StaticText1TB->Color = clBtnFace;
	StaticText5INV->Color = clBtnFace;
	StaticText4Ceh->Color = clBtnFace;
	Panel1->Visible = false;

	StaticText2Model->Visible = true;
	StaticText3Type->Visible = true;
	StaticText4Ceh->Visible = true;
	StaticText5INV->Visible = true;
	EditCeh->Visible = true;
	EditModel->Visible = true;
	EditInv->Visible = true;
	EditTB->Visible = true;
	EditType->Visible = true;
    StaticText1TB->Caption = "Тех. бюро";
	ComboBox1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TreeView2MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
	//
	H = X;
	B = Y;

	if (TreeView2->Selected->SelectedIndex==1)
	{
		NPodkat->Visible = true;
		NOpen->Visible = false;
		NDelete->Visible = false;
	}
	if (TreeView2->Selected->SelectedIndex==2)
	{
		NPodkat->Visible = true;
		NOpen->Visible = false;
		NDelete->Visible = true;
	}
    if (TreeView2->Selected->SelectedIndex==3)
	{
		NPodkat->Visible = false;
		NOpen->Visible = true;
		NDelete->Visible = true;
	}

		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)//КОПИРОВАТЬ СТРУКТУРУ
{
	ComboBox1->Items->Clear();

	Metka = TreeView1->GetNodeAt(K,Z);
	Panel1->Visible = true;
	StaticText1TB->Caption = "Куда:";

	StaticText2Model->Visible = false;
	StaticText3Type->Visible = false;
	StaticText4Ceh->Visible = false;
	StaticText5INV->Visible = false;
	EditCeh->Visible = false;
	EditModel->Visible = false;
	EditInv->Visible = false;
	EditTB->Visible = false;
	EditType->Visible = false;

	Button3->Caption = "Копировать";
	Panel2->Caption = "Откуда: " + Metka->Text;

	ComboBox1->Visible = true;
	ABSQuery2->SQL->Clear();
	ABSQuery2->SQL->Text = "select I_N from INV";
	ABSQuery2->Active = true;
	while (!ABSQuery2->Eof)
	{
		ComboBox1->Items->Add(ABSQuery2->FieldByName("I_N")->AsString);
		ABSQuery2->Next();
	}
	ABSQuery2->Close();

//	Metka = TreeView1->GetNodeAt(K,Z);
//	ABSQuery2->SQL->Clear();
//	ABSQuery2->SQL->Text = "select id_S2, id_S1 from Strukturs where id_Inv=(select id from INV where I_N='" + Metka->Text + "')";
//	ABSQuery2->Active = true;
//	while (!ABSQuery2->Eof)
//	{
//		ABSQuery1->SQL->Clear();
//		ABSQuery1->SQL->Text = "insert into Strukturs (id_Inv, id_S2, id_S1) values ((select id from INV where I_N='" +
//		Metka->Text + "')+1, '" + ABSQuery2->FieldByName("id_S2")->AsString + "', '"
//		+ ABSQuery2->FieldByName("id_S1")->AsString + "')";
//		ABSQuery1->ExecSQL();
//		ABSQuery2->Next();
//	}
		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NPodkatClick(TObject *Sender)//добавление ПОДКАТЕГОРИИ в ТриВью-2
{
								  //только включает панель выбора подкатегории
	NomerGrupp = TreeView2->Selected->SelectedIndex;
	switch (NomerGrupp)
	{
		case 1:{
				Panel3->Visible = true;
				Panel4->Caption = TreeView2->Selected->Text;
				ABSQuery2->SQL->Clear();
				ABSQuery2->SQL->Text = "select Naim from Strukt_2";
				ABSQuery2->Active = true;
					while (!ABSQuery2->Eof)
					{
						ComboBox2->Items->Add(ABSQuery2->FieldByName("Naim")->AsString);
						ABSQuery2->Next();
					}
					ABSQuery2->Close();

			   }
			break;
		case 2:{
                Panel3->Visible = true;
				Panel4->Caption = TreeView2->Selected->Text;
				ABSQuery2->SQL->Clear();
				ABSQuery2->SQL->Text = "select Naim from Strukt_3";
				ABSQuery2->Active = true;
					while (!ABSQuery2->Eof)
					{
						ComboBox2->Items->Add(ABSQuery2->FieldByName("Naim")->AsString);
						ABSQuery2->Next();
					}
					ABSQuery2->Close();
			   }

			break;


	default:
		;
	}

	TreeView2->SendToBack();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::NOpenClick(TObject *Sender)//открыть ПГДобразные данные
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)//ОТМЕНА/СБРОС ВСЕГО в ТВ-2
{
	Panel3->Visible = false;
	ComboBox2->Clear();
		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	//добавление в таблицы от ТриВью2+++++++++++++++++++++++++++++++++++++++

	 
	NomerGrupp = TreeView2->Selected->SelectedIndex;

	switch (NomerGrupp)
	{
		case 1:{
				ABSQuery1->SQL->Clear();
				ABSQuery1->SQL->Text = "INSERT INTO Strukturs (id_Inv, id_S2, id_S1) values ((select id from INV where I_N='"
				+ Metka->Text + "'), (select id from Strukt_2 where Naim='"
				+ ComboBox2->Text + "'), (select id from Strukt where Naim='" + TreeView2->Selected->Text + "'))";
				ABSQuery1->ExecSQL();
				ABSQuery1->Close();
				TreeView2->Items->AddChild(TreeView2->Selected, ComboBox2->Text)->SelectedIndex = 2;
				Panel3->Visible = false;
				ComboBox2->Clear();

			   }
			break;
		case 2:{
				String prev_node = TreeView2->Selected->Parent->Text;
				//ноды 1й группы, для SQL запроса. !!!
                ABSQuery1->SQL->Clear();
				ABSQuery1->SQL->Text =
"INSERT INTO Strukturs_23 (id_strukturs, id_S2, id_S3) values ((select id from Strukturs where id_Inv=(select id from INV where I_N='"
				+ Metka->Text + "') and id_S2=(select id from Strukt_2 where Naim='"
				+ TreeView2->Selected->Text + "') and id_S1=(select id from Strukt where Naim='" + prev_node + "')), (select id from Strukt_2 where Naim='"
				+ TreeView2->Selected->Text + "'), (select id from Strukt_3 where Naim='" + ComboBox2->Text + "'))";
				ABSQuery1->ExecSQL();
				ABSQuery1->Close();
				TreeView2->Items->AddChild(TreeView2->Selected, ComboBox2->Text)->SelectedIndex = 3;
				Panel3->Visible = false;
				ComboBox2->Clear();

			   }
			break;

	}
    Panel3->Visible = true;
	TreeView2->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDeleteClick(TObject *Sender)//УДАЛЕНИЕ из ТВ-2
{
	//
	if (TreeView2->Selected->SelectedIndex==2 && MessageDlg("Действительно удалить " + TreeView2->Selected->Text + "?", mtWarning, mbOKCancel,0)==mrOk)
	{
		ABSQuery1->SQL->Clear();
		ABSQuery1->SQL->Text = "delete from Strukturs_23 where id_strukturs=(select id from Strukturs where id_S2=(select id from Strukt_2 where Naim='"
		+ TreeView2->Selected->Text + "') and id_Inv=(select id from INV where I_N='"
		+ Metka->Text + "') and id_S1=(select id from Strukt where Naim='"
		+ TreeView2->Selected->Parent->Text + "'))";
		ABSQuery1->ExecSQL();
		ABSQuery1->Close();

		ABSQuery1->SQL->Clear();
		ABSQuery1->SQL->Text = "delete from Strukturs where id_S2=(select id from Strukt_2 where Naim='"
		+ TreeView2->Selected->Text + "') and id_Inv=(select id from INV where I_N='" + Metka->Text + "')";
		ABSQuery1->ExecSQL();
		ABSQuery1->Close();

		TreeView2->Selected->Delete();
	}

	if (MessageDlg("Действительно удалить " + TreeView2->Selected->Text + "?", mtWarning, mbOKCancel,0)==mrOk && TreeView2->Selected->SelectedIndex==3)
	{
		ABSQuery1->SQL->Clear();
		ABSQuery1->SQL->Text = "delete from Strukturs_23 where id_strukturs=(select id from Strukturs where id_S2=(select id from Strukt_2 where Naim='"
		+ TreeView2->Selected->Parent->Text + "') and id_Inv=(select id from INV where I_N='"
		+ Metka->Text + "') and id_S1=(select id from Strukt where Naim='"
		+ TreeView2->Selected->Parent->Parent->Text + "')) and id_S3=(select id from Strukt_3 where Naim='"
		+ TreeView2->Selected->Text + "')";
		ABSQuery1->ExecSQL();       //секретный ингридиент - двойной Parent!
		ABSQuery1->Close();

		TreeView2->Selected->Delete();
	}


		
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender) // ВЫХОД
{
	Form1->Close();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)//аналог ПО РАСПОЛОЖЕНИЮ
{
	Button2->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N10Click(TObject *Sender)//аналог ПО МОДЕЛЯМ
{
	Button1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	AnsiString Name;     //строковая переменная
	if (OpenDialog1->Execute())
	{
		Name = OpenDialog1->FileName;
		ImpFromTxt* Z = new ImpFromTxt;

	   //	Edit1->Text = Z->Import(Name.c_str());
		Memo1->Text = Z->Import(Name.c_str(),1);
		Button7->Caption = Z->Import(Name.c_str(),1,"Точка: ");


		delete Z;
		Memo1->Text;
	}
}
//---------------------------------------------------------------------------

