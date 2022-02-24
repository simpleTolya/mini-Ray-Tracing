/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:47:51 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 19:10:03 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_point	ft_canvas_to_viewport(double x, double y, t_data *data)
{
	t_point	res;
	t_point	total;

	res.x = (x * tan(data->camera.fov / 2 * M_PI / 180))
		/ WINDOW_SIZE + data->camera.position.x;
	res.y = (y * tan(data->camera.fov / 2 * M_PI / 180))
		/ WINDOW_SIZE + data->camera.position.y;
	res.z = 1 + data->camera.position.z;
	total.x = res.x * data->vector_x.x + res.y
		* data->vector_y.x + res.z * data->camera.vector.x;
	total.y = res.x * data->vector_x.y + res.y
		* data->vector_y.y + res.z * data->camera.vector.y;
	total.z = res.x * data->vector_x.z + res.y
		* data->vector_y.z + res.z * data->camera.vector.z;
	return (total);
}

t_object	*ft_closest_intersection(t_point *v_d, t_point *pix,
		t_data *data, double *closest)
{
	const t_list	*n = data->lst_obj;
	t_object		*obj;

	*closest = INFINITY;
	obj = 0;
	while (n)
	{
		if (!((t_object *)n->content)->intersect(v_d, pix, n->content, data))
		{
			if (data->t_min <= data->roots[0] && data->roots[0]
				<= data->t_max && data->roots[0] <= *closest)
			{
				*closest = data->roots[0];
				obj = n->content;
			}
			if (data->t_min <= data->roots[1] && data->roots[1]
				<= data->t_max && data->roots[1] <= *closest)
			{
				*closest = data->roots[1];
				obj = n->content;
			}
		}
		n = n->next;
	}
	return (obj);
}

int	ft_trace_ray(t_point *view_dot, t_point *pix, t_data *data)
{
	double			closest;
	t_object		*obj;
	t_point			vectors[3];
	double			i;

	closest = INFINITY;
	obj = ft_closest_intersection(view_dot, pix, data, &closest);
	if (obj == 0)
		return (BACKGROUND_COLOR);
	vectors[0].x = view_dot->x + closest * (pix->x - view_dot->x);
	vectors[0].y = view_dot->y + closest * (pix->y - view_dot->y);
	vectors[0].z = view_dot->z + closest * (pix->z - view_dot->z);
	data->closest = closest;
	obj->get_normal(&vectors[0], obj, &vectors[1], data);
	vectors[2].x = view_dot->x - pix->x;
	vectors[2].y = view_dot->x - pix->y;
	vectors[2].z = view_dot->z - pix->z;
	i = ft_compute_light(&vectors[0], &vectors[1], &vectors[2], data);
	return (((int)(((obj->color >> 16) & 0xFF) * i) << 16)
		+ ((int)(((obj->color >> 8) & 0xFF) * i) << 8)
		+ ((int)((obj->color & 0xFF) * i)));
}

void	ft_render(t_data *data)
{
	register int	i;
	register int	j;
	t_point			d;

	i = 0;
	while (i < WINDOW_SIZE)
	{
		j = 0;
		while (j < WINDOW_SIZE)
		{
			d = ft_canvas_to_viewport(-(WINDOW_SIZE / 2 - i),
					WINDOW_SIZE / 2 - j, data);
			my_mlx_pixel_put(&data->mlx, i, j,
				ft_trace_ray(&data->camera.position, &d, data));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		data->mlx.img, 0, 0);
}
