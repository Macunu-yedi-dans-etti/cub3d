/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:30:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/10/09 15:30:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	gc_init(t_gc *gc)
{
	gc->head = NULL;
}

void	*gc_track(t_gc *gc, void *ptr)
{
	t_gc_node	*node;

	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	return (gc_track(gc, ptr));
}

void	*gc_calloc(t_gc *gc, size_t count, size_t size)
{
	void		*ptr;
	size_t		total_size;

	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (gc_track(gc, ptr));
}

char	*gc_strdup(t_gc *gc, const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = gc_malloc(gc, len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	**gc_track_array(t_gc *gc, void **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		gc_track(gc, array[i]);
		i++;
	}
	return (array);
}

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*cur;
	t_gc_node	*tmp;

	cur = gc->head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->ptr);
		free(cur);
		cur = tmp;
	}
	gc->head = NULL;
}