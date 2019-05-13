#include <string>
using namespace std;
#include "generator.h"
string treeToCode(node* tree)
{
	string code;
	code+="SECTION .text\n";
	code+="org 0x100\n";
	
	code+="mov ax, 0x4c00\n";
	code+="int 0x21\n";
	return code;
}
