#include <vcl.h>
/*
Входные параметры:
1. SQL строка-запрос.
2. Поле, по которому делать выборку
3. Звено TreeView, предок
4. Звено потомок
5. Индекс звеньев (группа вложенности)
6. Компонент ABS для запроса
*/
void BuildNode(String S, String FBN, TTreeNode* Node, TTreeView* Tr, int ind, TABSQuery* AQ)
{
	if (Node)
	{

		AQ->SQL->Text = S;
		AQ->Active = true;
		while (!AQ->Eof)
		{
			Tr->Items->AddChild(Node, AQ->FieldByName(FBN)->AsString)->SelectedIndex = ind;
			AQ->Next();   //заполняются ноды
		}
	}
	if (ind == 1 && Node == NULL)
	{
		AQ->Close();
		AQ->SQL->Text = S;
		AQ->Active = true;
		while (!AQ->Eof)
		{
			Tr->Items->Add(NULL, AQ->FieldByName(FBN)->AsString)->SelectedIndex = ind;
			AQ->Next();   //заполняются ноды
		}
		AQ->Close();
	}
}