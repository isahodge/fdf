/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 20:32:44 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/05 18:19:07 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WINDOW 800

int		sign(float n)
{
	if (n < 0)
		return (-1);
	if (n > 0)
		return (1);
	return (0);
}

void	bres_init(t_bres **bres, t_point *point, t_point *dst_point)
{
	int	tmp;

	tmp = 0;
	(*bres)->swap = 0;
	(*bres)->x = point->x;
	(*bres)->y = point->y;
	(*bres)->dx = fabsf(dst_point->x - point->x);
	(*bres)->dy = fabsf(dst_point->y - point->y);
	(*bres)->s1 = sign(dst_point->x - point->x);
	(*bres)->s2 = sign(dst_point->y - point->y);
	(*bres)->dst_point = dst_point;
	if ((*bres)->dy > (*bres)->dx)
	{
		tmp = (*bres)->dx;
		(*bres)->dx = (*bres)->dy;
		(*bres)->dy = tmp;
		(*bres)->swap = 1;
	}
	(*bres)->d = 2 * (int)(*bres)->dy - (int)(*bres)->dx;
}

void	bresenhams(t_bres **bres, void **mlx, void **win, t_point *point)
{
	int i;

	i = 0;
	while (i < (*bres)->dx)
	{
		mlx_pixel_put((*mlx), (*win), (*bres)->x, (*bres)->y,
				color((*bres), i, point));
		while ((*bres)->d >= 0)
		{
			(*bres)->d = (*bres)->d - 2 * (*bres)->dx;
			if ((*bres)->swap)
				(*bres)->x += (*bres)->s1;
			else
				(*bres)->y += (*bres)->s2;
		}
		(*bres)->d = (*bres)->d + 2 * (*bres)->dy;
		if ((*bres)->swap)
			(*bres)->y += (*bres)->s2;
		else
			(*bres)->x += (*bres)->s1;
		i++;
	}
}

void	draw_line_down(void **mlx, void **win, t_line **line)
{
	t_line	*end;
	t_point	*point;
	t_point	*next_line;
	t_bres	*bres;

	end = (*line);
	bres = create_bres();
	while (end)
	{
		point = end->point;
		if (end->y_next != NULL)
			next_line = end->y_next->point;
		while (point && next_line)
		{
			bres_init(&bres, point, next_line);
			bresenhams(&bres, mlx, win, point);
			point = point->next;
			next_line = next_line->next;
		}
		end = end->next;
	}
}

void	draw_line_right(void **mlx, void **win, t_line **line)
{
	t_line	*end;
	t_point	*point;
	t_bres	*bres;

	end = (*line);
	bres = create_bres();
	while (end)
	{
		point = end->point;
		while (point->next != NULL)
		{
			bres_init(&bres, point, point->next);
			bresenhams(&bres, mlx, win, point);
			point = point->next;
		}
		end = end->next;
	}
}
