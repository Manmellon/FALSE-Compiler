#include <string>
#include <vector>
using namespace std;
#include "generator.h"
extern vector<int> nums;
extern vector<string> ids;
string treeToCode(node* tree)
{
	string code;
	code+="SECTION .text\n";
	code+="org 0x100\n";
	
	code+="mov ax, 0x4c00\n";
	code+="int 0x21\n";
	if(nums.size())
	{
		code+="SECTION .rodata\n";
	}
	if(ids.size())
	{
		code+="SECTION .bss\n";
	}
	return code;
}
