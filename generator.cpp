#include <sstream>
#include <string>
#include <vector>
#include <iostream>//delete
using namespace std;
#include "generator.h"
extern vector<int> intConsts;
extern vector<float> floatConsts;
extern vector<string> ids;
bool isFloatStack;
string generateCode(node* tree)
{
	string code;
	isFloatStack=false;
	code+="SECTION .text\n";
	code+="org 0x100\n";
	
	code+=treeToCode(tree);
	
	code+="mov ax, 0x4c00\n";
	code+="int 0x21\n";
	if(intConsts.size())
	{
		code+="SECTION .rodata\n";
		code+="consts:\n";
		for(size_t i=0;i<intConsts.size();i++)
		{
			//stringstream hexNum;
			//hexNum<<hex<<intConsts[i];
			code+="dd "+to_string(intConsts[i])+"\n";//hexNum.str()+"\n";
		}
	}
	if(ids.size())
	{
		code+="SECTION .bss\n";
		code+="vars:\n";
		code+="resd "+to_string(ids.size())+"\n";
		
	}
	return code;
}
string treeToCode(node* tree)
{
	string code;
	//cout<<"HELP ME\n";
	switch(tree->lex.type)
	{
		case STMT:
		{
			if(tree->child1)code+=treeToCode(tree->child1);//looks bad
			if(tree->child2)code+=treeToCode(tree->child2);
		}break;
		case NAME:
		{
			code+="mov ebx, [vars+"+to_string(tree->lex.value)+"]\n";
			if(isFloatStack)
			{
				code+="fld ebx\n";
			}
			else
			{
				code+="push ebx\n";
			}
		}break;
		case INT_CONST:
		{
			//cout<<"HELP "<<tree->lex.value;
			if(isFloatStack)
			{
				code+="fld ";
			}
			else
			{
				code+="push dword "+to_string(intConsts[tree->lex.value])+"\n";
			}
			//code+="[consts+"+to_string(tree->lex.value)+"]\n";
		}break;
		case FLOAT_CONST:
		{
			if(isFloatStack)
			{
				code+="fld ";
			}
			else
			{
				code+="push dword "+to_string((int)floatConsts[tree->lex.value])+"\n";
			}
		}break;
		case NEG:
		{
			if(isFloatStack)
			{
				code+="fchs\n";
			}
			else
			{
				code+="pop eax\nneg eax\npush eax\n";
			}
		}
		case PLUS:
		{
			if(isFloatStack)
			{
				code+="fadd\n";	
			}
			else
			{
				code+="pop ebx\npop eax\nadd eax,ebx\npush eax\n";
			}
		}break;
		case MINUS:
		{
			if(isFloatStack)
			{
				code+="fsub\n";	
			}
			else
			{
				code+="pop ebx\npop eax\nsub eax,ebx\npush eax\n";
			}
		}break;
		case MULT:
		{
			if(isFloatStack)
			{
				code+="fmul\n";	
			}
			else
			{
				code+="pop ebx\npop eax\nimul ebx\npush eax\n";
			}
		}break;
		case DIV:
		{
			if(isFloatStack)
			{
				code+="fdiv\n";	
			}
			else
			{
				code+="pop ebx\npop eax\nidiv ebx\npush eax\n";
			}
		}break;
		case ASSIGNMENT:
		{
			if(isFloatStack)
			{
				code+="fstp ebx\n";
				code+="fstp eax\n";
				code+="mov [eax], ebx\n";
			}
			else
			{
				code+="pop ebx\n";
				code+="pop eax\n";
				code+="mov [eax], ebx\n";
			}
		}break;
		case OPPNUMBER:
		{
			if(isFloatStack)
			{
				code+="fstp eax\nnot eax\nfld eax\n";
			}
			else
			{
				code+="pop eax\nnot eax\npush eax\n";
			}

		}break;
		case EQUAL:
		{
		}break;
		case AND:
		{
		}break;
		case OR:
		{
		}break;
		case DUP:
		{
		}break;
		case DROP:
		{
		}break;
		case SWAP:
		{
		}break;
		case PUT:
		{
		}break;
		case ROT:
		{
		}break;
		case IF:
		{
		}break;
		case WHILE:
		{
		}break;
		case FUNC_OPEN:
		{
		}break;
		case FUNC_CLOSE:
		{
		}break;
		default:break;
	}
	return code;
}
