#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# define WHITESPACE " \t\n"
# define METACHARACTERS " \t\n<>|&;()"

void	tokenize_op(t_scanner *scanner, t_token_list **token_list,
			t_error *error);
void	tokenize_word(t_scanner *scanner, t_token_list **token_list,
			t_error *error);

#endif