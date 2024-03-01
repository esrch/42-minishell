#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef struct s_gc_node
{
	struct s_gc_node	*next;
	void				*addr;
}	t_gc_node;

void	*gc_alloc(size_t size);
void	gc_free(void *addr);
void	gc_clear(void);

#endif