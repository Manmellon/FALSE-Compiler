#include <iostream>
#include <vector>
using namespace std;
enum lexeme{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ASSIGNMENT,OPPNUMBER,EQUAL,
			AND,OR,DUP,DROP,SWAP,PUT,ROT,IF,WHILE,FUNC_OPEN,FUNC_CLOSE,ERROR};
const int STMT = ERROR+1;

size_t curLexeme;
vector<lexeme> lexemes;

struct node
{
	struct node *child1,*child2,*child3;
	int type, value;
};
node* curNode;

node* createNode(int _type);
node* function();
node* statement();
node* program();

int main(int argc, char **argv)
{
	curLexeme = 0;
	lexemes.push_back(FUNC_OPEN);
	lexemes.push_back(DUP);
	lexemes.push_back(MULT);
	lexemes.push_back(FUNC_CLOSE);
	lexemes.push_back(NAME);
	lexemes.push_back((lexeme)0);//number from name's table
	lexemes.push_back(ASSIGNMENT);
	return 0;
}

node* createNode(int _type)
{
	node *n = new node;
	n->type = _type;
	n->child1=n->child2=n->child3=NULL;
	return n;
}
node* function()
{
	node *n=createNode(STMT);
	n->child1 = createNode(FUNC_OPEN);
	curLexeme++;
	curNode = n->child1;
	n->child2 = statement();
	curLexeme++;
	if (n->child2->type != FUNC_CLOSE)
	{
		if (curLexeme==FUNC_CLOSE)
		{
			n->child3 = createNode(FUNC_CLOSE);
		}
		else
		{
			
		}
	}
	return n;
}
node* statement()
{
	node *n;
	if (lexemes[curLexeme]<FUNC_OPEN)
	{
		n=createNode(lexemes[curLexeme]);
		if(curLexeme+1<lexemes.size())
		{
			n->child1 = n;
			n=createNode(STMT);
			n->child2 = statement();
		}
	}
	else if (lexemes[curLexeme]==FUNC_OPEN)
	{
		n = function();
	}
	else if (lexemes[curLexeme]==FUNC_CLOSE)
	{
		if (curNode->type==FUNC_OPEN)
		{
			n = createNode(FUNC_CLOSE);//when empty []
		}
		else
		{
			//Missing '[' here
		}
	}
	else
	{
		//Unknown Lexeme
	}
	return n;
}
node* program()
{
	//node *n = createNode(STMT);
	//n->child1 = statement();
	node *n = statement();
	return n;
}
