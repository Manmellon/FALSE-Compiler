#include <cstdio>
#include <iostream>
#include <vector>

#include "syntax.h"
using namespace std;
size_t curLexeme;
vector<lexeme> lexemes;
node *curNode;

vector<int> arrSizes;

node* createNode(lexeme _lex)
{
	node *n = new node;
	n->lex = _lex;
	n->child1=n->child2=n->child3=NULL;
	//n->parent=NULL;
	return n;
}
node* function()
{
	//puts("function started");
	lexeme tmpLexeme;
	tmpLexeme.type = STMT;
	node *n=createNode(tmpLexeme);
	tmpLexeme.type = FUNC_OPEN;
	n->child1 = createNode(tmpLexeme);
	//n->child1->parent = n;
	curLexeme++;
	curNode = n->child1;
	n->child2 = statement();
	curNode = n->child1;
	//puts("returned to func");
	if(n->child2==NULL)
	{
		tmpLexeme.type = FUNC_CLOSE;
		n->child2 = createNode(tmpLexeme);
	}
	//n->child2->parent = n;
	curLexeme++;
	//printf("1.cL=%d\n",curLexeme);
	//printf("n->ch2->type=%d\n",n->child2->lex.type);
	if (n->child2->lex.type != FUNC_CLOSE)
	{

		if (lexemes[curLexeme].type==FUNC_CLOSE)
		{
			tmpLexeme.type = FUNC_CLOSE;
			n->child3 = createNode(tmpLexeme);
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
	//printf("2.cL=%d\n",curLexeme);
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
	//puts("function ended");
	return n;
}
node* statement()
{
	//puts("statement started");
	lexeme tmpLexeme;
	tmpLexeme.type = STMT;
	node *n = createNode(tmpLexeme);
	
	if (lexemes[curLexeme].type<FUNC_OPEN)
	{
		n->child1=createNode(lexemes[curLexeme]);
		//n->child1->parent = n;
		curLexeme++;
		//TODO: Nothing do here
		//printf("cl = %d, l[cL] = %d\n",curLexeme,lexemes[curLexeme].type);
		if(curLexeme<lexemes.size()&&lexemes[curLexeme].type!=FUNC_CLOSE)
		{
			//puts("S->SS");
			tmpLexeme.type = STMT;
			node *tmp = createNode(tmpLexeme);
			tmp->child1 = n;
			//curNode = n;//new
			tmp->child2 = statement();
			//tmp->parent = n->parent;
			n = tmp;
		}
		else if(lexemes[curLexeme].type==FUNC_CLOSE)
        {
            //puts("closed ]");
            curLexeme--;
            //n=NULL;
        }
	}
	else if (lexemes[curLexeme].type==FUNC_OPEN)
	{
		node* prevCurNode=curNode;
		n = function();
		curNode = prevCurNode;
		//puts("returned from func to stat");
		if(curLexeme<lexemes.size()&&lexemes[curLexeme].type!=FUNC_CLOSE)
		{
			//puts("S->SS(after function)");
			tmpLexeme.type = STMT;
			node *tmp = createNode(tmpLexeme);
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
			if(lexemes[curLexeme].type==FUNC_CLOSE&&(!curNode||curNode->lex.type!=FUNC_OPEN))
				puts("Error: Missing '[' here");
			curLexeme--;
		}
		//printf("cl = %d, l[cL] = %d\n",curLexeme,lexemes[curLexeme].type);
	}
	else if (lexemes[curLexeme].type==FUNC_CLOSE)
	{
		//printf("cl = %d, l[cL] = %d\n",curLexeme,lexemes[curLexeme].type);
	    //printf("curNode->type:%d\n",curNode->lex.type);
		if (curNode&&curNode->lex.type==FUNC_OPEN)
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
	else if (lexemes[curLexeme].type==ARRAY_OPEN)
	{
		lexeme tmpLexeme;
		tmpLexeme.type=ARRAY_OPEN;
		n->child1 = createNode(tmpLexeme);
		//node* prevCurNode=curNode;
		//curNode = n->child1;
		curLexeme++;
		if (lexemes[curLexeme].type==INT_CONST||
			lexemes[curLexeme].type==FLOAT_CONST)
		{
			tmpLexeme.type=lexemes[curLexeme].type;
			n->child2 = createNode(tmpLexeme);
			curLexeme++;
			if (lexemes[curLexeme].type==ARRAY_CLOSE)
			{
				tmpLexeme.type=ARRAY_CLOSE;
				n->child3 = createNode(tmpLexeme);
				arrSizes.push_back((int)lexemes[curLexeme].value);
			}
			else
			{
				puts("Error: Missing ')' here");
				//curLexeme--;
			}
			curLexeme++;
			if(curLexeme<lexemes.size())
			{
				//after array
				tmpLexeme.type = STMT;
				node *tmp = createNode(tmpLexeme);
				cout<<"CYKA N ="<<n<<endl;
				tmp->child1 = n;
				tmp->child2 = statement();
				n = tmp;
			}
			else
			{
				curLexeme--;
			}
		}
		else if (lexemes[curLexeme].type==ARRAY_CLOSE)
		{
			tmpLexeme.type=ARRAY_CLOSE;
			n->child3 = createNode(tmpLexeme);
			arrSizes.push_back((int)lexemes[curLexeme].value);
			curLexeme++;
			if(curLexeme<lexemes.size())
			{
				//after array
				tmpLexeme.type = STMT;
				node *tmp = createNode(tmpLexeme);
				tmp->child1 = n;
				tmp->child2 = statement();
				n = tmp;
			}
			else
			{
				//curLexeme--;
			}
		}
		else
		{
			puts("Error: array init must contain number or nothing");
		}
		
	}
	else if (lexemes[curLexeme].type==ARRAY_CLOSE)
	{
		puts("Error: Missing '(' here");
	}
	else
	{
		//Unknown Lexeme
	}
	//puts("statement ended");
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
		/*
		printf("(C:%d ",t->lex.type);
		printf("1c:");
		printTree(t->child1);
		printf("2c:");
		printTree(t->child2);
		printf("3c:");
		printTree(t->child3);
		printf(") ");
		*/
		
		if (t->lex.type<STMT) printf("%d ",t->lex.type);
		printTree(t->child1);
		printTree(t->child2);
		printTree(t->child3);
		
	}
}
