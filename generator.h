#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <string>
using namespace std;
#include "syntax.h"
string generateCode(node* tree);
string treeToCode(node* tree);
#endif
