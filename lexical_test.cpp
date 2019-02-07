#include <iostream>
#include <vector>
#include <string>
using namespace std;
enum lexeme{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ERROR};
vector<lexeme> strToLexemes(string str)
{
	vector<lexeme> ans;
	bool readingName = false;
	bool readingNumber = false;
	string readingStr;
	for (size_t i=0;i<str.size();i++)
	{
		if (str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')
		{
			if (readingName)
			{
				readingStr+=str[i];
			}
			else
			{
				readingStr.clear();
				readingName = true;
				readingNumber = false;
			}
		}
		else if (str[i]>='0'&&str[i]<='9')
		{
			if (readingName||readingNumber)
			{
				readingStr+=str[i];
			}
			else
			{
				readingStr.clear();
				readingNumber = true;
			}
		}
		else
		{ 
			if (readingName)
			{
				ans.push_back(NAME);
				readingName = false;
			}
			else if (readingNumber)
			{
				ans.push_back(CONSTANT);
				readingNumber = false;
			}
			switch(str[i])
			{
				case '+': ans.push_back(PLUS);break;
				case '-': ans.push_back(MINUS);break;
				case '*': ans.push_back(MULT);break;
				case '/': ans.push_back(DIV);break;
				default:
				{
					ans.push_back(ERROR);
					cout<<"Error: undefined symbol "<<str[i]<<"\n";
				}break;
			}
		}
	}
	return ans;
}
int main(int argc, char **argv)
{
	vector<lexeme> lexemes;
	string str = "@name+234+-*/*-name2+-#";
	lexemes = strToLexemes(str);
	for (size_t i=0;i<str.size();i++)
	{
		cout<<str[i];
	}
	cout<<endl;
	for (size_t i=0;i<lexemes.size();i++)
	{
		cout<<lexemes[i];
	}
	return 0;
}

