#include "ast.h"

/** Returns the node in the AST following the given path.
 * 
 * path is a string containing L or R to follow a path.
 * If path is NULL, returns NULL.
 * If path is empty, returns the root.
 * If path contains an invalid character, returns NULL.
 * If the path reaches a NULL and should continue, returns NULL.
 * Otherwise, returns the node that was reached.
*/
t_ast_node	*ast_at(t_ast_node *ast, char *path)
{
	if (!path)
		return (NULL);
	if (!*path)
		return (ast);
	while (*path)
	{
		if (*path == 'L')
			ast = ast->left;
		else if (*path == 'R')
			ast = ast->right;
		else
			return (NULL);
		if (!ast)
			return (NULL);
		path++;
	}
	return (ast);
}