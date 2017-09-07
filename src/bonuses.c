/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 21:11:57 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/06 11:17:25 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int keycode, t_events *events)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 126)
		translate(events, 0, -10);
	if (keycode == 125)
		translate(events, 0, 10);
	if (keycode == 123)
		translate(events, -10, 0);
	if (keycode == 124)
		translate(events, 10, 0);
	if (keycode == 13)
		scale(events, 1.1, 1.1, 1.1);
	if (keycode == 1)
		scale(events, 0.9, 0.9, 0.9);
	if (keycode == 37)
		legend(events);
	return (0);
}

void	z_min_max(t_line **line)
{
	t_line	*end;
	t_point	*point;
	int		z_min;
	int		z_max;

	z_min = 1;
	z_max = 1;
	end = (*line);
	while (end)
	{
		point = end->point;
		while (point)
		{
			if (point->z < z_min)
				z_min = point->z;
			if (point->z > z_max)
				z_max = point->z;
			point = point->next;
		}
		end = end->next;
	}
	set_color(line, z_min, z_max);
}

int		color(t_bres *bres, int i, t_point *point)
{
	int		color;
	int		length;
	float	tmp;

	if (point->z == 0 && bres->dst_point->z == 0)
		return (0xFFFFFF);
	if (point->z == bres->dst_point->z)
		return (bres->dst_point->r << 16 | 255 << 8 | 255);
	length = (int)sqrt((bres->dx * bres->dx) + (bres->dy * bres->dy));
	tmp = ((float)i / length) * (point->r - bres->dst_point->r);
	color = (point->r - (int)tmp) << 16 | 255 << 8 | 255;
	return (color);
}

void	translate(t_events *events, int x, int y)
{
	float	mat[4][4];

	mlx_clear_window(events->mlx, events->win);
	make_translate_matrix(&mat, x, y);
	vector_matrix_mult(&events->line, mat);
	draw_line_right(&events->mlx, &events->win, &events->line);
	draw_line_down(&events->mlx, &events->win, &events->line);
}

void	scale(t_events *events, float x, float y, float z)
{
	float	mat[4][4];

	mlx_clear_window(events->mlx, events->win);
	make_scale_matrix(&mat, x, y, z);
	scale_x_y_z(&events->line, mat);
	draw_line_right(&events->mlx, &events->win, &events->line);
	draw_line_down(&events->mlx, &events->win, &events->line);
}
