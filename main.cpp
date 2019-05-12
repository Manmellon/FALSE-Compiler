#include <iostream>
#include "lexic.h"
#include "syntax.h"
#include "generator.h"
int main(int argc, char **argv)
{
	vector<lexeme> lexemes;
	string str = "SANYA@8name+ 234 6+-*/*-\nnamme2+-#\nfuck 99 7^98 fuck+fock_feck3fick";
	lexemes = strToLexemes(str);
	for (size_t i=0;i<str.size();i++)
	{
		cout<<str[i];
	}
	cout<<"\n"<<endl;
	for (size_t i=0;i<lexemes.size();i++)
	{
		cout<<lexemes[i].type<<' ';
	}
    cout<<endl<<"Constants: ";
	for (size_t i=0;i<nums.size();i++)
	{
		cout<<nums[i]<<' ';
	}
	cout<<endl<<"identificators: ";
	for (size_t i=0;i<ids.size();i++)
	{
		cout<<ids[i]<<' ';
	}
	cout<<endl;
	
	node* tree = program();
	printTree(tree);
	
	
	return 0;
}
