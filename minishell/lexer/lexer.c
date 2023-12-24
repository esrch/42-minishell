#include "lexer.h"

void	lexer_init(t_lexer *lexer, char *source)
{
	lexer->source = source;
	lexer->start = 0;
	lexer->current = 0;
}