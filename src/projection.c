/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:33:01 by ihodge            #+#    #+#             */
/*   Updated: 2017/09/05 21:03:57 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matrix_mult(float (*mat1)[4][4], float (*mat2)[4][4],
		float (*prod)[4][4])
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			(*prod)[i][j] = (*mat1)[i][0] * (*mat2)[0][j] + (*mat1)[i][1] *
				(*mat2)[1][j] + (*mat1)[i][2] * (*mat2)[2][j] + (*mat1)[i][3] *
				(*mat2)[3][j];
			j++;
		}
		i++;
	}
}

void	vector_matrix_mult2(t_point **vec_point, float mat[4][4])
{
	t_point	*tmp_point;

	tmp_point = (*vec_point);
	(*vec_point)->x = tmp_point->x * mat[0][0] + tmp_point->y * mat[0][1]
		+ (tmp_point->z * mat[0][2]) + mat[0][3];
	(*vec_point)->y = tmp_point->x * mat[1][0] + tmp_point->y * mat[1][1]
		+ (tmp_point->z * mat[1][2]) + mat[1][3];
}

void	scale_x_y_z(t_line **line, float mat[4][4])
{
	t_line	*vec;
	t_point	*vec_point;
	t_point	*tmp_point;

	vec = (*line);
	while (vec)
	{
		vec_point = vec->point;
		tmp_point = vec_point;
		while (vec_point)
		{
			vec_point->x = tmp_point->x * mat[0][0] + tmp_point->y * mat[0][1]
				+ tmp_point->z * mat[0][2] + mat[0][3];
			vec_point->y = tmp_point->x * mat[1][0] + tmp_point->y * mat[1][1]
				+ tmp_point->z * mat[1][2] + mat[1][3];
			vec_point->z = tmp_point->x * mat[2][0] + tmp_point->y * mat[2][1]
				+ tmp_point->z * mat[2][2] + mat[2][3];
			tmp_point = tmp_point->next;
			vec_point = vec_point->next;
		}
		vec = vec->next;
	}
}

void	vector_matrix_mult(t_line **line, float mat[4][4])
{
	t_line	*vec;
	t_point	*vec_point;

	vec = (*line);
	while (vec)
	{
		vec_point = vec->point;
		while (vec_point)
		{
			vector_matrix_mult2(&vec_point, mat);
			vec_point = vec_point->next;
		}
		vec = vec->next;
	}
}

void	transform_3d_to_2d(t_line **line, int x_angle, int y_angle)
{
	float x_rot[4][4];
	float y_rot[4][4];
	float combo_mat[4][4];
	float x;
	float y;

	x = ((float)x_angle / 180) * M_PI;
	y = ((float)y_angle / 180) * M_PI;
	make_x_matrix(&x_rot, x);
	make_y_matrix(&y_rot, y);
	matrix_mult(&y_rot, &x_rot, &combo_mat);
	vector_matrix_mult(line, combo_mat);
}
