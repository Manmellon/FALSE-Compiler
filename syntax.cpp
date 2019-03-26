#include <iostream>
#include <vector>
using namespace std;
enum lexeme{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ASSIGNMENT,OPPNUMBER,EQUAL,
			AND,OR,DUP,DROP,SWAP,PUT,ROT,IF,WHILE,FUNC_OPEN,FUNC_CLOSE,ERROR};
const int STMT = ERROR+1;

int curLexeme;
vector<lexeme> lexemes;

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
node* function()
{
	node *n;
	return n;
}
node* statement()
{
	node *n;
	if (lexemes[curLexeme]<ERROR)
	{
		n=createNode(lexemes[curLexeme]);
	}
	else
	{
		//case '[': break;
        //case ']': ans.push_back(FUNC_CLOSE);break;
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

