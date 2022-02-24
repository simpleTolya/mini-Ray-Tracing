/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:42:35 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 18:04:45 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_mlx *map, int x, int y, int color)
{
	register char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_point	vector3_rotate_yx(t_point a, double angle_y, double angle_x)
{
	t_point	b;

	angle_x = M_PI / 180 * -angle_x;
	b.x = a.x;
	b.y = a.y * cos(angle_x) - a.z * sin(angle_x);
	b.z = a.y * sin(angle_x) + a.z * cos(angle_x);
	angle_y = M_PI / 180 * -angle_y;
	a.x = b.x * cos(angle_y) - b.z * sin(angle_y);
	a.y = b.y;
	a.z = b.x * sin(angle_y) + b.z * cos(angle_y);
	return (a);
}

void	ft_update_angle_matrix(t_data *data)
{
	double	k;
	t_point	tmp;

	k = (data->camera.vector.x * data->vector_x.x
			+ data->camera.vector.y * data->vector_x.y
			+ data->camera.vector.z * data->vector_x.z)
		/ (data->camera.vector.x * data->camera.vector.x
			+ data->camera.vector.y * data->camera.vector.y
			+ data->camera.vector.z * data->camera.vector.z);
	tmp.x = data->vector_x.x - k * data->camera.vector.x;
	tmp.y = data->vector_x.y - k * data->camera.vector.y;
	tmp.z = data->vector_x.z - k * data->camera.vector.z;
	data->vector_x = tmp;
	k = (data->camera.vector.x * data->vector_y.x
			+ data->camera.vector.y * data->vector_y.y
			+ data->camera.vector.z * data->vector_y.z)
		/ (data->camera.vector.x * data->camera.vector.x
			+ data->camera.vector.y * data->camera.vector.y
			+ data->camera.vector.z * data->camera.vector.z);
	tmp.x = (data->vector_y.x - k * data->camera.vector.x);
	tmp.y = (data->vector_y.y - k * data->camera.vector.y);
	tmp.z = (data->vector_y.z - k * data->camera.vector.z);
	data->vector_y = tmp;
}

int	ft_exit(t_data *map)
{
	(void) map;
	exit(0);
	return (0);
}
