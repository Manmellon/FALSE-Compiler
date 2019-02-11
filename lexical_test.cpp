#include <iostream>
#include <vector>
#include <string>
using namespace std;
enum lexeme{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ASSIGNMENT,OPPNUMBER,EQUAL,AND,OR,DUP,DROP,SWAP,PUT,ROT,IF,WHILE,ERROR};
vector<lexeme> strToLexemes(string str)
{
	vector<lexeme> ans;
	bool readingName = false;
	bool readingNumber = false;
	bool readingCommentary = false;
	string readingStr;
	int lineNum = 1, columnNum=0;
	for (size_t i=0;i<str.size();i++, columnNum++)
	{
	    if (!readingCommentary)
        {
            if (str[i]=='{') {readingCommentary=true; continue;}
            if (str[i]=='}') {cout<<"Error: illegal closing brace at line "<<lineNum<<", column "<<columnNum<<" \n"; continue;}
            if (str[i]==' ') continue;
            if (str[i]=='\n') {lineNum++; columnNum=0; continue;}
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
	cout<<"Total symbols: "<<str.size()<<"\nTotal lines: "<<lineNum<<" \n\n";
	return ans;
}
int main(int argc, char **argv)
{
	vector<lexeme> lexemes;
	string str = "SANYA{@name+234+-*/}*-\n}name2+-#\n99^9";
	lexemes = strToLexemes(str);
	for (size_t i=0;i<str.size();i++)
	{
		cout<<str[i];
	}
	cout<<"\n"<<endl;
	for (size_t i=0;i<lexemes.size();i++)
	{
		cout<<lexemes[i];
	}
	return 0;
}
