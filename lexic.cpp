#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "lexic.h"
using namespace std;

vector<int> intConsts;
vector<float> floatConsts;
vector<string> ids;
vector<lexeme> strToLexemes(string str)
{
	vector<lexeme> ans;
	bool readingName = false;
	bool readingNumber = false;
	bool readingFloatNumber = false;
	bool readingCommentary = false;
	string readingStr;
	int lineNum = 1, columnNum=0;
	//int bufNum;
	int flag;
	for (size_t i=0;i<str.size();i++, columnNum++)
	{
		//cout<<(short)str[i]<<" ";
		//cout<<readingStr<<endl;
		lexeme tmpLexeme;
		if (readingCommentary)
		{
			if (str[i]=='\n') {lineNum++; columnNum=0; /*continue;*/}
			if (str[i]=='}') {readingCommentary=false; /*continue;*/}
			continue;
		}
		if (str[i]=='{') {readingCommentary=true; continue;}
		if (str[i]=='}') {cout<<"Error: illegal closing brace at line "<<lineNum<<", column "<<columnNum<<" \n"; continue;}
		if (str[i]=='\n') {lineNum++; columnNum=0;}
		if ((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
		{
			if (readingNumber)
			{
				/*bufNum = atoi(readingStr.c_str());
				flag=0;
				size_t i;
				for (i=0;i<intConsts.size();i++)
				{
					if (bufNum==intConsts[i]) flag=1;
				}
				if (!flag) intConsts.push_back(bufNum);
				*/
				intConsts.push_back(atoi(readingStr.c_str()));
				tmpLexeme.type = INT_CONST;
				tmpLexeme.value = intConsts.size()-1;
				ans.push_back(tmpLexeme);
				readingNumber = false;
			}
			else if (readingFloatNumber)
			{
				floatConsts.push_back(atof(readingStr.c_str()));
				tmpLexeme.type = FLOAT_CONST;
				tmpLexeme.value = floatConsts.size()-1;
				ans.push_back(tmpLexeme);
				readingFloatNumber = false;
			}
			if (readingName)
			{
				readingStr+=str[i];
			}
			else
			{
				readingStr.clear();
				readingName = true;
				readingNumber = false;
				readingStr+=str[i];
			}
		}
		else if (str[i]>='0'&&str[i]<='9')
		{
			if (readingName)
			{
				flag=0;
				size_t i;
				for (i=0;i<ids.size();i++)
				{
					if (readingStr==ids[i]) flag=1;
				}
				if (!flag) ids.push_back(readingStr);
				tmpLexeme.type = NAME;
				tmpLexeme.value = i;
				ans.push_back(tmpLexeme);
				readingName = false;
			}
			if (readingNumber||readingFloatNumber)
			{
				readingStr+=str[i];
			}
			else
			{
				readingStr.clear();
				readingName = false;
				readingNumber = true;
				readingStr+=str[i];
			}
		}
		else if(str[i]==1)//0xAB//float
		{
			if (readingName)
			{
				flag=0;
				size_t i;
				for (i=0;i<ids.size();i++)
				{
					if (readingStr==ids[i]) flag=1;
				}
				if (!flag) ids.push_back(readingStr);
				tmpLexeme.type = NAME;
				tmpLexeme.value = i;
				ans.push_back(tmpLexeme);
				readingName = false;
			}
			else if (readingNumber)
			{
				readingFloatNumber = true;
				readingNumber=false;
				readingStr+='.';
			}
			else if (readingFloatNumber)
			{
			}
		}
		else
		{
			if (readingName)
			{
				flag=0;
				size_t i;
				for (i=0;i<ids.size();i++)
				{
					if (readingStr==ids[i]) flag=1;
				}
				if (!flag) ids.push_back(readingStr);
				tmpLexeme.type = NAME;
				tmpLexeme.value = i;
				ans.push_back(tmpLexeme);
				readingName = false;
			}
			else if (readingNumber)
			{
				/*bufNum = atoi(readingStr.c_str());
				flag=0;
				size_t i;
				for (i=0;i<intConsts.size();i++)
				{
					if (bufNum==intConsts[i]) flag=1;
				}
				if (!flag) intConsts.push_back(bufNum);*/
				intConsts.push_back(atoi(readingStr.c_str()));
				tmpLexeme.type = INT_CONST;
				tmpLexeme.value = intConsts.size()-1;
				ans.push_back(tmpLexeme);
				readingNumber = false;
			}
			else if (readingFloatNumber)
			{
				floatConsts.push_back(atof(readingStr.c_str()));
				tmpLexeme.type = FLOAT_CONST;
				tmpLexeme.value = floatConsts.size()-1;
				ans.push_back(tmpLexeme);
				readingFloatNumber = false;
			}
			switch(str[i])
			{
				case '+': tmpLexeme.type = PLUS;ans.push_back(tmpLexeme);break;
				case '-': tmpLexeme.type = MINUS;ans.push_back(tmpLexeme);break;
				case '*': tmpLexeme.type = MULT;ans.push_back(tmpLexeme);break;
				case '/': tmpLexeme.type = DIV;ans.push_back(tmpLexeme);break;
				case ':': tmpLexeme.type = ASSIGNMENT;ans.push_back(tmpLexeme);break;
				case '~': tmpLexeme.type = OPPNUMBER;ans.push_back(tmpLexeme);break;
				case '=': tmpLexeme.type = EQUAL;ans.push_back(tmpLexeme);break;
				case '&': tmpLexeme.type = AND;ans.push_back(tmpLexeme);break;
				case '|': tmpLexeme.type = OR;ans.push_back(tmpLexeme);break;
				case '$': tmpLexeme.type = DUP;ans.push_back(tmpLexeme);break;
				case '%': tmpLexeme.type = DROP;ans.push_back(tmpLexeme);break;
				case '\\': tmpLexeme.type = SWAP;ans.push_back(tmpLexeme);break;
				case ';': tmpLexeme.type = PUT;ans.push_back(tmpLexeme);break;
				case '@': tmpLexeme.type = ROT;ans.push_back(tmpLexeme);break;
				case '?': tmpLexeme.type = IF;ans.push_back(tmpLexeme);break;
				case '#': tmpLexeme.type = WHILE;ans.push_back(tmpLexeme);break;
				case '[': tmpLexeme.type = FUNC_OPEN;ans.push_back(tmpLexeme);break;
				case ']': tmpLexeme.type = FUNC_CLOSE;ans.push_back(tmpLexeme);break;
				case ' ':break;
				case '\n':break;
				default:
				{
				tmpLexeme.type = ERROR;
				ans.push_back(tmpLexeme);
				cout<<"Error: undefined symbol "<<str[i]<<" at line "<<lineNum<<", column "<<columnNum<<" \n";
				} break;
			}
		}
	/*if (readingName)
	{
		if ((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
		{
			readingStr+=str[i];
		}
		else if
	}*/
	
	}
	lexeme tmpLexeme;
	if (readingName)
	{
		flag=0;
		size_t i;
		for (i=0;i<ids.size();i++)
		{
			if (readingStr==ids[i]) flag=1;
		}
		if (!flag) ids.push_back(readingStr);
		tmpLexeme.type = NAME;
		tmpLexeme.value = i;
		ans.push_back(tmpLexeme);
		readingName = false;
	}
	else if (readingNumber)
	{
		/*bufNum = atoi(readingStr.c_str());
		flag=0;
		size_t i;
		for (i=0;i<intConsts.size();i++)
		{
			if (bufNum==intConsts[i]) flag=1;
		}
		if (!flag) intConsts.push_back(bufNum);*/
		intConsts.push_back(atoi(readingStr.c_str()));
		tmpLexeme.type = INT_CONST;
		tmpLexeme.value = intConsts.size()-1;
		ans.push_back(tmpLexeme);
		readingNumber = false;
	}
	cout<<"Total symbols: "<<str.size()<<"\nTotal lines: "<<lineNum<<" \n\n";
	return ans;
}
/*
int main(int argc, char **argv)
{
	vector<lexeme> lexemes;*/
	//string str = "SANYA@8name+ 234 6+-*/*-\nnamme2+-#\nfuck 99 7^98 fuck+fock_feck3fick";
	/*lexemes = strToLexemes(str);
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
	for (size_t i=0;i<intConsts.size();i++)
	{
		cout<<intConsts[i]<<' ';
	}
	cout<<endl<<"identificators: ";
	for (size_t i=0;i<ids.size();i++)
	{
		cout<<ids[i]<<' ';
	}
	cout<<endl;
	return 0;
}
*/
