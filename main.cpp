#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "lexic.h"
#include "syntax.h"
#include "generator.h"
extern vector<int> intConsts;
extern vector<float> floatConsts;
extern vector<string> ids;
extern vector<lexeme> lexemes;
int main(int argc, char **argv)
{
	//vector<lexeme> lexemes;
	//string str = "SANYA@8name+ 234 6+-*/*-\nnamme2+-#\nfuck 99 7^98 fuck+fock_feck3fick";
	string str = "23[[name[[47super]]56][]]pi3";
	str+=1;//(char)0xAB;//its 1/2
	str+="14[]";
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
    cout<<endl<<"Int constants: ";
	for (size_t i=0;i<intConsts.size();i++)
	{
		cout<<intConsts[i]<<' ';
	}
	cout<<endl<<"Float constants: ";
	for (size_t i=0;i<floatConsts.size();i++)
	{
		cout<<floatConsts[i]<<' ';
	}
	cout<<endl<<"identificators: ";
	for (size_t i=0;i<ids.size();i++)
	{
		cout<<ids[i]<<' ';
	}
	cout<<endl;
	
	node* tree = program();
	printTree(tree);
	cout<<endl;
	string code = generateCode(tree);
	cout<<code;
	return 0;
}
