/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 19:12:17 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/06 11:37:36 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WINDOW 800

int		ft_error(int ret)
{
	if (ret == 1)
	{
		ft_putstr("usage: ./fdf source_file\n");
		return (ret);
	}
	if (ret == 2)
	{
		ft_putstr("Error: bad file\n");
		return (ret);
	}
	return (ret);
}

void	open_win(t_line **line)
{
	void		*mlx;
	void		*win;
	int			(*key)();
	int			(*rd)();
	t_events	*events;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW + 100, WINDOW + 100, "mlx 42");
	set_local_coords(line);
	set_y_next(line);
	z_min_max(line);
	transform_3d_to_2d(line, -35, -45);
	set_screen_coords(line);
	set_spacing(line, spacing(line));
	draw_line_right(&mlx, &win, line);
	draw_line_down(&mlx, &win, line);
	events = create_events(mlx, win, (*line));
	key = &key_press;
	rd = &redraw;
	mlx_key_hook(win, key, events);
	mlx_expose_hook(win, rd, events);
	mlx_loop(mlx);
}

void	parse(t_point **point, char *str, int y)
{
	char	**arr;
	int		i;
	t_point	*end;

	end = (*point);
	arr = ft_split(str);
	i = 0;
	while (arr[i])
	{
		end->z = ft_atoi(arr[i]);
		end->y = y;
		end->x = i;
		if (arr[i + 1] != NULL)
			append_point(&end, create_point());
		i++;
	}
}

void	save_data(char *str, t_line **line, t_line **head, int y)
{
	t_line	*tmp;

	tmp = create_line();
	if ((*line) != NULL)
		(*line)->next = tmp;
	parse(&tmp->point, str, y);
	(*line) = tmp;
	if (y == 0)
		(*head) = (*line);
	tmp = tmp->next;
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_line	*line;
	t_line	*head;
	int		y;

	y = 0;
	if (argc != 2)
		return (ft_error(1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error(2));
	line = NULL;
	while (get_next_line(fd, &str) == 1)
	{
		save_data(str, &line, &head, y);
		y++;
	}
	if (!line)
		return (ft_error(2));
	line->next = NULL;
	open_win(&head);
	return (0);
}
