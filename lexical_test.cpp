#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
enum lexeme{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ASSIGNMENT,OPPNUMBER,EQUAL,
			AND,OR,DUP,DROP,SWAP,PUT,ROT,IF,WHILE,FUNC_OPEN,FUNC_CLOSE,ERROR};
vector<int> nums;
vector<string> ids;
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
                    for (size_t i=0;i<nums.size();i++)
                    {
                        if (bufNum==nums[i]) flag=1;
                    }
                    if (!flag) nums.push_back(bufNum);
                    ans.push_back(CONSTANT);
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
                    for (size_t i=0;i<ids.size();i++)
                    {
                        if (readingStr==ids[i]) flag=1;
                    }
                    if (!flag) ids.push_back(readingStr);
                    ans.push_back(NAME);
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
                    for (size_t i=0;i<ids.size();i++)
                    {
                        if (readingStr==ids[i]) flag=1;
                    }
                    if (!flag) ids.push_back(readingStr);
                    ans.push_back(NAME);
                    readingName = false;
                }
                else if (readingNumber)
                {
                    bufNum = atoi(readingStr.c_str());
                    flag=0;
                    for (size_t i=0;i<nums.size();i++)
                    {
                        if (bufNum==nums[i]) flag=1;
                    }
                    if (!flag) nums.push_back(bufNum);
                    ans.push_back(CONSTANT);
                    readingNumber = false;
                }
                switch(str[i])
                {
                    case '+': ans.push_back(PLUS);break;
                    case '-': ans.push_back(MINUS);break;
                    case '*': ans.push_back(MULT);break;
                    case '/': ans.push_back(DIV);break;
                    case ':': ans.push_back(ASSIGNMENT);break;
                    case '~': ans.push_back(OPPNUMBER);break;
                    case '=': ans.push_back(EQUAL);break;
                    case '&': ans.push_back(AND);break;
                    case '|': ans.push_back(OR);break;
                    case '$': ans.push_back(DUP);break;
                    case '%': ans.push_back(DROP);break;
                    case '\\': ans.push_back(SWAP);break;
                    case ';': ans.push_back(PUT);break;
                    case '@': ans.push_back(ROT);break;
                    case '?': ans.push_back(IF);break;
                    case '#': ans.push_back(WHILE);break;
                    case '[': ans.push_back(FUNC_OPEN);break;
                    case ']': ans.push_back(FUNC_CLOSE);break;
                    case ' ':break;
                    case '\n':break;
                    default:
                    {
                        ans.push_back(ERROR);
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
	if (readingName)
	{
		flag=0;
		for (size_t i=0;i<ids.size();i++)
		{
			if (readingStr==ids[i]) flag=1;
		}
		if (!flag) ids.push_back(readingStr);
		ans.push_back(NAME);
		readingName = false;
	}
	else if (readingNumber)
	{
		bufNum = atoi(readingStr.c_str());
		flag=0;
		for (size_t i=0;i<nums.size();i++)
		{
			if (bufNum==nums[i]) flag=1;
		}
		if (!flag) nums.push_back(bufNum);
		ans.push_back(CONSTANT);
		readingNumber = false;
	}
	cout<<"Total symbols: "<<str.size()<<"\nTotal lines: "<<lineNum<<" \n\n";
	return ans;
}
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
		cout<<lexemes[i]<<' ';
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
