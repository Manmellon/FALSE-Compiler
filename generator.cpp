#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include "generator.h"
extern vector<int> nums;
extern vector<string> ids;
string treeToCode(node* tree)
{
	string code;
	bool isFloatStack=false;
	code+="SECTION .text\n";
	code+="org 0x100\n";
	switch(tree->lex.type)
	{
		case STMT:treeToCode(tree->child1);treeToCode(tree->child2);break;
	}
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
