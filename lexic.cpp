#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "lexic.h"
using namespace std;

extern vector<int> nums;
extern vector<string> ids;
vector<lexeme> strToLexemes(string str)
{
	vector<lexeme> ans;
	bool readingName = false;
	bool readingNumber = false;
	bool readingCommentary = false;
	string readingStr;
	int lineNum = 1, columnNum=0;
	int bufNum, flag;
	for (size_t i=0;i<str.size();i++, columnNum++)
	{
		lexeme tmpLexeme;
	    if (!readingCommentary)
        {
            if (str[i]=='{') {readingCommentary=true; continue;}
            if (str[i]=='}') {cout<<"Error: illegal closing brace at line "<<lineNum<<", column "<<columnNum<<" \n"; continue;}
            if (str[i]=='\n') {lineNum++; columnNum=0;}
            if ((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
            {
                if (readingNumber)
                {
                    bufNum = atoi(readingStr.c_str());
                    flag=0;
                    size_t i;
                    for (i=0;i<nums.size();i++)
                    {
                        if (bufNum==nums[i]) flag=1;
                    }
                    if (!flag) nums.push_back(bufNum);
                    tmpLexeme.type = CONSTANT;
                    tmpLexeme.value = i;
                    ans.push_back(tmpLexeme);
                    readingNumber = false;
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
                if (readingNumber)
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
                    bufNum = atoi(readingStr.c_str());
                    flag=0;
                    size_t i;
                    for (i=0;i<nums.size();i++)
                    {
                        if (bufNum==nums[i]) flag=1;
                    }
                    if (!flag) nums.push_back(bufNum);
                    tmpLexeme.type = CONSTANT;
                    tmpLexeme.value = i;
                    ans.push_back(tmpLexeme);
                    readingNumber = false;
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
        }
        else
        {
            if (str[i]=='\n') {lineNum++; columnNum=0; continue;}
            if (str[i]=='}') {readingCommentary=false; continue;}
        }
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
		bufNum = atoi(readingStr.c_str());
		flag=0;
		size_t i;
		for (i=0;i<nums.size();i++)
		{
			if (bufNum==nums[i]) flag=1;
		}
		if (!flag) nums.push_back(bufNum);
		tmpLexeme.type = CONSTANT;
        tmpLexeme.value = i;
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
	return 0;
}
*/
