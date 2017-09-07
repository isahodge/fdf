/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 20:47:59 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/07 12:52:39 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef	struct		s_point
{
	struct s_point	*next;
	float			x;
	float			y;
	float			z;
	int				r;
}					t_point;

typedef struct		s_line
{
	struct s_line	*next;
	struct s_line	*y_next;
	t_point			*point;
}					t_line;

typedef struct		s_append
{
	struct s_append	*next;
}					t_append;

typedef struct		s_bres
{
	float			x;
	float			y;
	float			dx;
	float			dy;
	int				swap;
	int				s1;
	int				s2;
	int				d;
	t_point			*dst_point;
}					t_bres;

typedef struct		s_events
{
	void			*mlx;
	void			*win;
	int				keycode;
	t_line			*line;
}					t_events;

t_point				*create_point(void);
t_line				*create_line(void);
void				append_point(t_point **point, t_point *create_point);
void				set_y_next(t_line **head);
double				spacing(t_line **head);
void				set_spacing(t_line **head, double spacing);
void				draw_line_right(void **mlx, void **win, t_line **line);
void				draw_line_down(void **mlx, void **win, t_line **line);
void				transform_3d_to_2d(t_line **line, int x_angle, int y_angle);
void				set_local_coords(t_line **head);
void				set_screen_coords(t_line **head);
void				make_x_matrix(float (*mat)[4][4], float a);
void				make_y_matrix(float (*mat)[4][4], float a);
void				make_z_matrix(float (*mat)[4][4], float a);
void				make_translate_matrix(float (*mat)[4][4], float x, float y);
void				vector_matrix_mult(t_line **line, float mat[4][4]);
void				vector_matrix_mult2(t_point **vec_point, float mat[4][4]);
t_bres				*create_bres(void);
int					color(t_bres *bres, int i, t_point *point);
void				make_scale_matrix(float (*mat)[4][4], float x, float y,
		float z);
t_events			*create_events(void *mlx, void *win, t_line *line);
void				translate(t_events *events, int x, int y);
void				scale(t_events *event, float x, float y, float z);
int					key_press(int keycode, t_events *events);
void				scale_x_y_z(t_line **line, float mat[4][4]);
void				z_min_max(t_line **line);
void				set_color(t_line **line, int z_min, int z_max);
void				legend(t_events *events);
int					redraw(t_events *events);
#endif
