#include <sstream>
#include <string>
#include <vector>
#include <iostream>//delete
using namespace std;
#include "generator.h"
extern vector<int> intConsts;
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
	//cout<<tree->child1->lex.type;
	switch(tree->lex.type)
	{
		case STMT:
		{
			if(tree->child1)code+=treeToCode(tree->child1);//looks bad
			if(tree->child2)code+=treeToCode(tree->child2);
		}break;
		case NAME:
		{
		}break;
		case CONSTANT:
		{
			if(isFloatStack)code+="fld ";
			else code+="push dword "+to_string(intConsts[tree->lex.value])+"\n";
			//code+="[consts+"+to_string(tree->lex.value)+"]\n";
		}break;
		case PLUS:
		{
			if(isFloatStack)
			{
				code+="fld \n";
				code+="fld \n";
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
				code+="fld \n";
				code+="fld \n";
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
				code+="fld \n";
				code+="fld \n";
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
				code+="fld \n";
				code+="fld \n";
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
				code+="fstp \n";
			}
			else
			{
				code+="pop \n";
			}
		}break;
		case OPPNUMBER:
		{
			if(isFloatStack)
			{
				code+="fstp eax\n";
				code+="fld \n";
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
