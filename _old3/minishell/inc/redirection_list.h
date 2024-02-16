#ifndef REDIRECTION_LIST_H
# define REDIRECTION_LIST_H

# include "defines.h"

typedef enum s_redirection_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redirection_type;

typedef struct s_redirection_list
{
	struct s_redirection_list	*next;
	t_redirection_type			type;
	char						*filename;
	int							here_doc_fd;
	char						*here_doc_terminator;
}	t_redirection_list;

t_status	redirection_list_add_file(t_redirection_list **list, t_redirection_type type,
				char *file);
t_status	redirection_list_add_heredoc(t_redirection_list **list, char *terminator);
void		redirection_list_clear(t_redirection_list *list);

#endif /* REDIRECTION_LIST_H */