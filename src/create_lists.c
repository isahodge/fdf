/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:22:14 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/07 12:53:31 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		*create_point(void)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		return (NULL);
	new->x = 0;
	new->y = 0;
	new->z = 0;
	new->r = 0;
	new->next = NULL;
	return (new);
}

t_line		*create_line(void)
{
	t_line	*new;

	if (!(new = (t_line*)ft_memalloc(sizeof(t_line))))
		return (NULL);
	new->point = create_point();
	new->y_next = NULL;
	new->next = NULL;
	return (new);
}

void		append_point(t_point **point, t_point *create_point)
{
	t_append	**append;

	append = (t_append**)point;
	(*(append))->next = (t_append*)create_point;
	*append = (t_append*)create_point;
}

t_bres		*create_bres(void)
{
	t_bres	*new;

	if (!(new = (t_bres*)malloc(sizeof(t_bres))))
		return (NULL);
	new->x = 0;
	new->y = 0;
	new->dx = 0;
	new->dy = 0;
	new->swap = 0;
	new->s1 = 0;
	new->s2 = 0;
	new->d = 0;
	new->dst_point = NULL;
	return (new);
}

t_events	*create_events(void *mlx, void *win, t_line *line)
{
	t_events	*new;

	if (!(new = (t_events*)malloc(sizeof(t_events))))
		return (NULL);
	new->mlx = mlx;
	new->win = win;
	new->keycode = 0;
	new->line = line;
	return (new);
}
