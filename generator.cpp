#include <sstream>
#include <string>
#include <vector>
#include <iostream>//delete
using namespace std;
#include "generator.h"
extern vector<int> intConsts;
extern vector<float> floatConsts;
extern vector<string> ids;
extern vector<int> arrSizes;
bool isFloatStack;
int funcCount;
int labelCount;
vector<int> funcNumbers;
string generateCode(node* tree)
{
	string code;
	isFloatStack=false;
	funcCount=-1;
	labelCount=-1;
	code+="SECTION .text\n";
	code+="org 0x100\n";
	
	code+=treeToCode(tree);
	
	code+="mov ax, 0x4c00\n";
	code+="int 0x21\n";
	/*if(intConsts.size())
	{
		code+="SECTION .rodata\n";
		code+="consts:\n";
		for(size_t i=0;i<intConsts.size();i++)
		{
			//stringstream hexNum;
			//hexNum<<hex<<intConsts[i];
			code+="dd "+to_string(intConsts[i])+"\n";//hexNum.str()+"\n";
		}
	}*/
	if(ids.size()||arrSizes.size())
	{
		code+="SECTION .bss\n";
		if(ids.size())
		{
			code+="vars:\n";
			code+="resd "+to_string(ids.size())+"\n";
			
		}
		cout<<"arrsize="<<arrSizes.size()<<endl;
		if (arrSizes.size())
		{
			for(size_t i=0;i<arrSizes.size();i++)
			{
				code+="arr"+to_string(i)+":"+to_string(arrSizes[i])+"\n";
			}
			
		}
	}
	return code;
}
string treeToCode(node* tree)
{
	string code;
	cout<<tree->lex.type<<"\n";
	switch(tree->lex.type)
	{
		case STMT:
		{
			if(tree->child1)code+=treeToCode(tree->child1);//looks bad
			if(tree->child2)code+=treeToCode(tree->child2);
			if(tree->child3)code+=treeToCode(tree->child3);
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
				//code+="fstp eax\n";
				//code+="mov [eax], ebx\n";
				code+="fstp dword [bx]\n";
			}
			else
			{
				code+="pop ebx\n";
				//code+="pop eax\n";
				//code+="mov [eax], ebx\n";
				code+="pop dword [bx]\n";
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
			if(isFloatStack)
			{
				code+="fcom\n";
				//code+="";//we need push bool then(register CR?)
			}
			else
			{
				code+="pop ebx\npop eax\nsub eax, ebx\nsub eax, 1\nsbb eax, eax\npush eax\n";
			}
		}break;
		case MORE:
		{
			if(isFloatStack)
			{
				code+="fcom\n";
			}
			else
			{
				labelCount++;
				code+="pop ebx\npop eax\nsub ecx, ecx\ncmp eax, ebx\njle l"
				+to_string(labelCount)+"\ndec ecx\nl"+to_string(labelCount)+":\npush ecx\n";
			}
		}break;
		case LESS:
		{
			if(isFloatStack)
			{
				code+="fcom\n";
			}
			else
			{
				code+="pop ebx\npop eax\nsub ecx, ecx\ncmp eax, ebx\njge .local\ndec ecx\n.local:\npush ecx\n";
			}
		}break;
		case AND:
		{
			if(isFloatStack)
			{
				code+="fstp ebx\nfstp eax\n";
			}
			else
			{
				code+="pop ebx\npop eax\n";
            }
            code+="or eax, eax\nsetne al\nor ebx, ebx\nsetne bl\nand al, bl\nneg al\nmovsx eax, al\n";
            if(isFloatStack)
            {
				code+="fld eax\n";
			}
			else
			{
				code+="push eax\n";
			}
		}break;
		case OR:
		{
			if(isFloatStack)
			{
			}
			else
			{
				code+="pop ebx\npop eax\n";
            }
            code+="or eax, eax\nsetne al\nor ebx, ebx\nsetne bl\nor al, bl\nneg al\nmovsx eax, al\n";
            if(isFloatStack)
            {
				code+="fld eax\n";
			}
			else
			{
				code+="push eax\n";
			}
		}break;
		case DUP:
		{
			if(isFloatStack)
            {
				code+="fstp eax\nfld eax\nfld eax\n";
			}
			else
			{
				code+="pop eax\npush eax\npush eax\n";
			}
		}break;
		case DROP:
		{
			if(isFloatStack)
            {
				code+="fstp eax\n";
			}
			else
			{
				code+="pop eax\n";
			}
		}break;
		case SWAP:
		{
			if(isFloatStack)
            {
				code+="fstp ebx\nfstp eax\nfld ebx\nfld eax\n";
			}
			else
			{
				code+="pop ebx\npop eax\npush ebx\npush eax\n";
			}
		}break;
		case PUT:
		{
			if(isFloatStack)
			{
				code+="fstp ebx\n";
				code+="fld dword [bx]\n";
			}
			else
			{
				code+="pop ebx\n";
				code+="push dword [bx]\n";
			}
		}break;
		case ROT:
		{
			if(isFloatStack)
            {
				code+="fstp ecx\nfstp ebx\nfstp eax\nfld ebx\nfld ecx\nfld eax\n";
			}
			else
			{
				code+="pop ecx\npop ebx\npop eax\npush ebx\npush ecx\npush eax\n";
			}
		}break;
		case IF:
		{
			if(isFloatStack)
            {
			}
			else
			{
				labelCount++;
				code+="pop ebx\npop eax\nor eax, eax\nje l"+to_string(labelCount)+
				"jmp bx\nl"+to_string(labelCount)+":\n";
			}
		}break;
		case WHILE:
		{
			if(isFloatStack)
            {
			}
			else
			{
				labelCount++;
				code+="pop ebx\npop eax\nsub bp, 4\nmov word [bp], bx\nmov word [bp + 2], ax\nmov bx, word [bp + 2]\nsub bp, 2";
				code+="jmp bx\npop eax\nor eax, eax\nje l"+to_string(labelCount)+"jmp bx\nl"+to_string(labelCount)+":\n";
			}
		}break;
		case CALL:
		{
			if(isFloatStack)
            {
				code+="fstp ebx\njmp bx\n";
			}
			else
			{
				code+="pop ebx\njmp bx\n";
			}
		}break;
		case CHANGE:
		{
			isFloatStack = !isFloatStack;
		}break;
		case SEND:
		{
			if(isFloatStack)
            {
				
			}
			else
			{
				code+="pop eax\nfild eax\n";
			}
		}
		case FUNC_OPEN:
		{
			funcCount++;
			code+="jmp fc"+to_string(funcCount)+"\n";
			code+="fo"+to_string(funcCount)+":\n";
			funcNumbers.push_back(funcCount);

			//if(tree->child2)code+=treeToCode(tree->child2);
			//if(tree->child3)code+=treeToCode(tree->child3);
		}break;
		case FUNC_CLOSE:
		{
			//cout<<"IM HERE\n";
			code+="fc"+to_string(funcNumbers[funcNumbers.size()-1])+":\n";
			code+="push fo"+to_string(funcNumbers[funcNumbers.size()-1])+"\n";
			funcNumbers.pop_back();
		}break;
		default:break;
	}
	return code;
}
