#include <vcl.h>
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