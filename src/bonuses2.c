/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:05:11 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/06 11:37:26 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_color(t_line **line, int z_min, int z_max)
{
	t_line	*end;
	t_point	*point;

	end = (*line);
	while (end)
	{
		point = end->point;
		while (point)
		{
			if (point->z < 0)
				point->r = 0xFF - (0xFF / (z_min * -1)) * point->z * -1;
			else if (point->z > 0)
				point->r = 0xFF - (0xFF / z_max) * point->z;
			else
				point->r = 0xFF;
			point = point->next;
		}
		end = end->next;
	}
}

void	legend(t_events *events)
{
	mlx_string_put(events->mlx, events->win, 10, 750, 0xFF0000, "Legend:");
	mlx_string_put(events->mlx, events->win, 100, 750, 0xFF0F00,
			"Up, Down, Left, Right with arrow keys");
	mlx_string_put(events->mlx, events->win, 500, 750, 0xFFFF00,
			"W and S to scale");
}

int		redraw(t_events *events)
{
	mlx_clear_window(events->mlx, events->win);
	draw_line_right(&events->mlx, &events->win, &events->line);
	draw_line_down(&events->mlx, &events->win, &events->line);
	return (0);
}
