#include <sstream>
#include <string>
#include <vector>
#include <iostream>//delete
using namespace std;
#include "generator.h"
extern vector<int> nums;
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
	if(nums.size())
	{
		code+="SECTION .rodata\n";
		for(size_t i=0;i<nums.size();i++)
		{
			stringstream hexNum;
			hexNum<<hex<<nums[i];
			code+="dd 0x"+hexNum.str()+"\n";
		}
	}
	if(ids.size())
	{
		code+="SECTION .bss\n";
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
		}break;
		case PLUS:
		{
		}break;
		case MINUS:
		{
		}break;
		case MULT:
		{
		}break;
		case DIV:
		{
		}break;
		case ASSIGNMENT:
		{
		}break;
		case OPPNUMBER:
		{
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
