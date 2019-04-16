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
	struct node *parent;
	int type, value;
};
node *curNode;

node* createNode(int _type);
node* function();
node* statement();
node* program();
void printTree(node *t);
int main(int argc, char **argv)
{
	curLexeme = 0;
	/*lexemes.push_back(FUNC_OPEN);
	lexemes.push_back(DUP);
	lexemes.push_back(MULT);
	lexemes.push_back(FUNC_CLOSE);
	lexemes.push_back(NAME);
	lexemes.push_back((lexeme)0);//number from name's table
	lexemes.push_back(ASSIGNMENT);
	*/
	/*lexemes.push_back(CONSTANT);
	lexemes.push_back(CONSTANT);
	lexemes.push_back(MULT);
	*/
	lexemes.push_back(FUNC_OPEN);
	lexemes.push_back(CONSTANT);
	lexemes.push_back(FUNC_OPEN);
	lexemes.push_back(FUNC_CLOSE);
	lexemes.push_back(NAME);
	lexemes.push_back(FUNC_CLOSE);
	node *tree = program();
	for(size_t i=0;i<lexemes.size();i++)
	{
		printf("%d ",lexemes[i]);
	}
	puts("");
	printTree(tree);
	return 0;
}

node* createNode(int _type)
{
	node *n = new node;
	n->type = _type;
	n->child1=n->child2=n->child3=n->parent=NULL;
	return n;
}
node* function()
{
	puts("function started");
	node *n=createNode(STMT);
	n->child1 = createNode(FUNC_OPEN);
	n->child1->parent = n;
	curLexeme++;
	curNode = n->child1;
	n->child2 = statement();
	if(n->child2==NULL)
	{
		n->child2 = createNode(FUNC_CLOSE);
	}
	n->child2->parent = n;
	curLexeme++;
	printf("%d\n",curLexeme);
	printf("%d\n",n->child2->type);
	if (n->child2->type != FUNC_CLOSE)
	{
		if (lexemes[curLexeme]==FUNC_CLOSE)
		{
			n->child3 = createNode(FUNC_CLOSE);
			n->child3->parent = n;
			if (n->parent)
				curNode = n->parent->child1;
		}
		else if(curLexeme>=lexemes.size())
		{
			//Missing ']' here?
			puts("Error: Missing ']' here");
		}
	}
	if(curLexeme<lexemes.size())
	{
		puts("S->SS");
		node *tmp = createNode(STMT);
		tmp->child1 = n;
		tmp->child2 = statement();
		tmp->parent = n->parent;
		n = tmp;
	}
	puts("function ended");
	return n;
}
node* statement()
{
	puts("statement started");
	node *n = createNode(STMT);
	if (lexemes[curLexeme]<FUNC_OPEN)
	{
		n->child1=createNode(lexemes[curLexeme]);
		n->child1->parent = n;
		curLexeme++;
		if(curLexeme<lexemes.size())
		{
			puts("S->SS");
			node *tmp = createNode(STMT);
			tmp->child1 = n;
			tmp->child2 = statement();
			tmp->parent = n->parent;
			n = tmp;
		}
	}
	else if (lexemes[curLexeme]==FUNC_OPEN)
	{
		n = function();
	}
	else if (lexemes[curLexeme]==FUNC_CLOSE)
	{
		if (curNode&&curNode->type==FUNC_OPEN)
		{
			//n = createNode(FUNC_CLOSE);//when empty []
			//curLexeme--;
			n=NULL;
		}
		else
		{
			//Missing '[' here
			puts("Error: Missing '[' here");
		}
	}
	else
	{
		//Unknown Lexeme
	}
	puts("statement ended");
	return n;
}
node* program()
{
	//node *n = createNode(STMT);
	//n->child1 = statement();
	curNode = NULL;
	node *n = statement();
	return n;
}

void printTree(node *t)//C 1 2 3
{
	if(t)
	{
		//printf("(C:%d ",t->type);
		if (t->type<STMT) printf("%d ",t->type);
		//printf("1c:");
		printTree(t->child1);
		//printf("2c:");
		printTree(t->child2);
		//printf("3c:");
		printTree(t->child3);
		//printf(") ");
	}
}
