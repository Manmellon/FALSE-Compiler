#ifndef LEXEME_H_
#define LEXEME_H_
enum lexemeType{NAME,CONSTANT,PLUS,MINUS,MULT,DIV,ASSIGNMENT,OPPNUMBER,EQUAL,
			AND,OR,DUP,DROP,SWAP,PUT,ROT,IF,WHILE,FUNC_OPEN,FUNC_CLOSE,ERROR};
struct lexeme
{
	lexemeType type;
	int value;
};
#endif
