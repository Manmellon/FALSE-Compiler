#ifndef SYNTAX_H_
#define SYNTAX_H_
#include "lexeme.h"
struct node
{
	struct node *child1,*child2,*child3;
	//struct node *parent;
	lexeme lex;
};

node* createNode(lexeme _lex);
node* function();
node* statement();
node* program();
void printTree(node *t);
#endif
