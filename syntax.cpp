#include <iostream>
#include <vector>
using namespace std;

struct node
{
	struct node *child1,*child2,*child3;
	int type, value;
};
node* createNode(int _type)
{
	node *n = new node;
	n->type = _type;
	return n;
}
int main(int argc, char **argv)
{
	
	return 0;
}

