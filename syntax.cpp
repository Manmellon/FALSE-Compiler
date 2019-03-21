#include <iostream>
#include <vector>
using namespace std;
enum lexeme{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ASSIGNMENT,OPPNUMBER,EQUAL,
			AND,OR,DUP,DROP,SWAP,PUT,ROT,IF,WHILE,FUNC_OPEN,FUNC_CLOSE,ERROR};
const int STMT = ERROR+1;

int curLexeme;

struct node
{
	struct node *child1,*child2,*child3;
	int type, value;
};
node* createNode(int _type)
{
	node *n = new node;
	n->type = _type;
	n->child1=n->child2=n->child3=NULL;
	return n;
}
node* program()
{
	node *n = createNode(STMT);
	return n;
}
int main(int argc, char **argv)
{
	curLexeme = 0;
	return 0;
}

