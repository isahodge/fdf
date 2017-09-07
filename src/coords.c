/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 16:08:48 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/06 11:26:26 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WINDOW 800

void	set_local_coords(t_line **head)
{
	t_line	*end;
	t_point	*point;
	float	y_max;
	float	x_max;

	end = (*head);
	while (end->next)
		end = end->next;
	point = end->point;
	while (point->next)
		point = point->next;
	x_max = point->x;
	y_max = point->y;
	end = (*head);
	while (end)
	{
		point = end->point;
		while (point)
		{
			point->y = point->y - (y_max / 2);
			point->x = point->x - (x_max / 2);
			point = point->next;
		}
		end = end->next;
	}
}

void	set_screen_coords(t_line **head)
{
	t_line	*end;
	t_point	*point;
	float	y_min;
	float	x_min;
	float	mat[4][4];

	end = (*head);
	y_min = 0.0;
	x_min = 0.0;
	while (end)
	{
		point = end->point;
		while (point)
		{
			if (point->x < x_min)
				x_min = point->x;
			if (point->y < y_min)
				y_min = point->y;
			point = point->next;
		}
		end = end->next;
	}
	make_translate_matrix(&mat, x_min * -1, y_min * -1);
	vector_matrix_mult(head, mat);
}

double	spacing(t_line **head)
{
	int		tmp;
	double	length;
	t_line	*end;
	t_point	*point;

	end = (*head);
	tmp = 0;
	while (end)
	{
		point = end->point;
		while (point)
		{
			if (point->x > tmp)
				tmp = point->x;
			if (point->y > tmp)
				tmp = point->y;
			point = point->next;
		}
		end = end->next;
	}
	length = WINDOW / (double)tmp;
	return (length);
}

void	set_spacing(t_line **head, double spacing)
{
	t_line	*end;
	t_point	*point;

	end = (*head);
	if (spacing == 0)
		return ;
	while (end)
	{
		point = end->point;
		while (point)
		{
			point->y = spacing * point->y;
			point->x = spacing * point->x;
			point->z = spacing * point->z;
			point = point->next;
		}
		end = end->next;
	}
}

void	set_y_next(t_line **head)
{
	t_line	*set_y;
	t_line	*list;

	set_y = (*head);
	list = (*head);
	list = list->next;
	while (set_y && list)
	{
		set_y->y_next = list;
		set_y = set_y->next;
		list = list->next;
	}
}
