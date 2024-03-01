#include "gc.h"

#include <stdlib.h>

static t_gc_node	**get_gc(void)
{
	static t_gc_node	*gc;

	return (&gc);
}

void	*gc_alloc(size_t size)
{
	t_gc_node	**gc;
	t_gc_node	*new_node;
	void		*addr;

	gc = get_gc();
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	addr = malloc(size);
	if (!addr)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = *gc;
	new_node->addr = addr;
	*gc = new_node;
	return (addr);
}

void	gc_free(void *addr)
{
	t_gc_node	**gc;
	t_gc_node	*current_node;
	t_gc_node	*free_node;

	gc = get_gc();
	current_node = *gc;
	free(addr);
	if (!current_node)
		return ;
	if (current_node && current_node->addr == addr)
	{
		*gc = current_node->next;
		free(current_node);
	}
	while (current_node->next && current_node->next->addr != addr)
		current_node = current_node->next;
	if (!current_node->next)
		return ;
	free_node = current_node->next;
	current_node->next = free_node->next;
	free(free_node);
}

void	gc_clear(void)
{
	t_gc_node	**gc;
	t_gc_node	*current_node;
	t_gc_node	*next_node;

	gc = get_gc();
	current_node = *gc;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->addr);
		free(current_node);
		current_node = next_node;
	}
}
