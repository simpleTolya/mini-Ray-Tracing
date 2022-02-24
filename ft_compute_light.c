/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:09:49 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 19:13:35 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	ft_helper(t_point *tmp2, t_point *obj_ray,
		t_data *data, double *intensity)
{
	double	r_dot_v;
	double	r_len;
	double	v_len;

	r_dot_v = tmp2->x * obj_ray->x + tmp2->y
		* obj_ray->y + tmp2->z * obj_ray->z;
	r_len = sqrt(tmp2->x * tmp2->x + tmp2->y
			* tmp2->y + tmp2->z * tmp2->z);
	v_len = sqrt(obj_ray->x * obj_ray->x + obj_ray->y
			* obj_ray->y + obj_ray->z * obj_ray->z);
	if (r_dot_v > 0)
		*intensity += data->light.ratio * pow(r_dot_v / (r_len * v_len), 500);
	if (*intensity > 1)
		*intensity = 1;
	return (*intensity);
}

static t_object	*ft_has_shadow(t_point *point, t_point *l_ray,
			t_data *data, double *tmp)
{
	t_object	*obj;

	data->t_min = 0.001;
	data->t_max = 1;
	obj = ft_closest_intersection(point, l_ray, data, tmp);
	data->t_min = 1;
	data->t_max = 100000;
	return (obj);
}

double	ft_compute_light(t_point *point, t_point *nor,
			t_point *obj_ray, t_data *data)
{
	t_point		l_ray;
	t_point		tmp2;
	t_point		tmp3;

	tmp3.x = data->ambient.ratio;
	l_ray.x = data->light.position.x - point->x;
	l_ray.y = data->light.position.y - point->y;
	l_ray.z = data->light.position.z - point->z;
	if (ft_has_shadow(point, &l_ray, data, &tmp3.y))
		return (tmp3.x);
	tmp3.y = nor->x * l_ray.x + nor->y * l_ray.y + nor->z * l_ray.z;
	if (tmp3.y > 0)
		tmp3.x += data->light.ratio * tmp3.y / sqrt(
				(nor->x * nor->x + nor->y * nor->y + nor->z * nor->z)
				* (l_ray.x * l_ray.x + l_ray.y * l_ray.y + l_ray.z * l_ray.z));
	tmp3.z = nor->x * l_ray.x + nor->y * l_ray.y + nor->z * l_ray.z;
	tmp2.x = 2 * nor->x * tmp3.z - l_ray.x;
	tmp2.y = 2 * nor->y * tmp3.z - l_ray.y;
	tmp2.z = 2 * nor->z * tmp3.z - l_ray.z;
	return (ft_helper(&tmp2, obj_ray, data, &tmp3.x));
}
