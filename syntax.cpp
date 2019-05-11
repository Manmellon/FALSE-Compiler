#include <cstdio>
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
	//struct node *parent;
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
	/*lexemes.push_back(FUNC_OPEN);
        lexemes.push_back(CONSTANT);

        lexemes.push_back(FUNC_OPEN);
        lexemes.push_back(CONSTANT);
        lexemes.push_back(FUNC_CLOSE);

        lexemes.push_back(PLUS);

        lexemes.push_back(FUNC_OPEN);
        lexemes.push_back(CONSTANT);
        lexemes.push_back(FUNC_CLOSE);
	lexemes.push_back(FUNC_CLOSE);
	lexemes.push_back(CONSTANT);
    lexemes.push_back(CONSTANT);
    */

    //Bottom works good
    /*lexemes.push_back(CONSTANT);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(CONSTANT);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(CONSTANT);
    lexemes.push_back(FUNC_CLOSE);
    lexemes.push_back(FUNC_CLOSE);
    lexemes.push_back(CONSTANT);
    lexemes.push_back(FUNC_CLOSE);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(FUNC_CLOSE);
    lexemes.push_back(FUNC_CLOSE);
    lexemes.push_back(CONSTANT);
    lexemes.push_back(CONSTANT);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(FUNC_CLOSE);
    */
	
    //lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(FUNC_OPEN);
    lexemes.push_back(FUNC_CLOSE);
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
	n->child1=n->child2=n->child3=NULL;
	//n->parent=NULL;
	return n;
}
node* function()
{
	puts("function started");
	node *n=createNode(STMT);
	n->child1 = createNode(FUNC_OPEN);
	//n->child1->parent = n;
	curLexeme++;
	curNode = n->child1;
	n->child2 = statement();
	curNode = n->child1;
	puts("returned to func");
	if(n->child2==NULL)
	{
		n->child2 = createNode(FUNC_CLOSE);
	}
	//n->child2->parent = n;
	curLexeme++;
	printf("1.cL=%d\n",curLexeme);
	printf("n->ch2->type=%d\n",n->child2->type);
	if (n->child2->type != FUNC_CLOSE)
	{

		if (lexemes[curLexeme]==FUNC_CLOSE)
		{
			n->child3 = createNode(FUNC_CLOSE);
			//n->child3->parent = n;
			//if (n->parent)
			//	curNode = n->parent->child1;
			
            curLexeme++;
		}
		else if(curLexeme>=lexemes.size())
		{
			//Missing ']' here?
			puts("Error: Missing ']' here");
		}
	}
	printf("2.cL=%d\n",curLexeme);
	/*if(curLexeme<lexemes.size()&&lexemes[curLexeme]!=FUNC_CLOSE)
	{
		if(lexemes[curLexeme]!=FUNC_CLOSE)
		{
			puts("S->SS(after function)");
			node *tmp = createNode(STMT);
			tmp->child1 = n;
			//if (n->parent)
			//    curNode = n->parent->child1;
			//else
			//   curNode = n;//new

			//printf("n->type:%d\n",n->parent->type);

			tmp->child2 = statement();
			//tmp->parent = n->parent;
			n = tmp;
		}
		else
		{
			puts("Error: Missing '[' here");
		}
	}
	else
	{
		curLexeme--;
	}*/
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
		//n->child1->parent = n;
		curLexeme++;
		//TODO: Nothing do here
		printf("cl = %d, l[cL] = %d\n",curLexeme,lexemes[curLexeme]);
		if(curLexeme<lexemes.size()&&lexemes[curLexeme]!=FUNC_CLOSE)
		{
			puts("S->SS");
			node *tmp = createNode(STMT);
			tmp->child1 = n;
			//curNode = n;//new
			tmp->child2 = statement();
			//tmp->parent = n->parent;
			n = tmp;
		}
		else if(lexemes[curLexeme]==FUNC_CLOSE)
        {
            puts("closed ]");
            curLexeme--;
            //n=NULL;
        }
	}
	else if (lexemes[curLexeme]==FUNC_OPEN)
	{
		node* prevCurNode=curNode;
		n = function();
		curNode = prevCurNode;
		puts("returned from func to stat");
		if(curLexeme<lexemes.size()&&lexemes[curLexeme]!=FUNC_CLOSE)
		{
			puts("S->SS(after function)");
			node *tmp = createNode(STMT);
			tmp->child1 = n;
			//if (n->parent)
			//    curNode = n->parent->child1;
			//else
			//   curNode = n;//new
			//printf("n->type:%d\n",n->parent->type);
			tmp->child2 = statement();
			//tmp->parent = n->parent;
			n = tmp;
		}
		else
		{
			if(lexemes[curLexeme]==FUNC_CLOSE&&(!curNode||curNode->type!=FUNC_OPEN))
				puts("Error: Missing '[' here");
			curLexeme--;
		}
		printf("cl = %d, l[cL] = %d\n",curLexeme,lexemes[curLexeme]);
	}
	else if (lexemes[curLexeme]==FUNC_CLOSE)
	{
		printf("cl = %d, l[cL] = %d\n",curLexeme,lexemes[curLexeme]);
	    printf("curNode->type:%d\n",curNode->type);
		if (curNode&&curNode->type==FUNC_OPEN)
		{
			//n = createNode(FUNC_CLOSE);//when empty []
			curLexeme--;
			//n=NULL;
		}
		else
		{
			puts("Error: Missing '[' here");
		}
		//puts("Error: Missing '[' here");
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
		/*printf("(C:%d ",t->type);
		printf("1c:");
		printTree(t->child1);
		printf("2c:");
		printTree(t->child2);
		printf("3c:");
		printTree(t->child3);
		printf(") ");
		*/
		
		if (t->type<STMT) printf("%d ",t->type);
		printTree(t->child1);
		printTree(t->child2);
		printTree(t->child3);
		
	}
}
