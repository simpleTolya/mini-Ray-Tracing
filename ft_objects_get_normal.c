/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objects_get_normal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:48:03 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 18:07:22 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_get_normal_sphere(t_point *point, t_object *obj,
		t_point *normal, t_data *data)
{
	double	len;

	(void) data;
	normal->x = -(((t_sphere *)obj->obj)->center.x - point->x);
	normal->y = -(((t_sphere *)obj->obj)->center.y - point->y);
	normal->z = -(((t_sphere *)obj->obj)->center.z - point->z);
	len = sqrt(normal->x * normal->x + normal->y
			* normal->y + normal->z * normal->z);
	normal->x /= len;
	normal->y /= len;
	normal->z /= len;
	return (0);
}

int	ft_get_normal_plane(t_point *point, t_object *obj,
		t_point *normal, t_data *data)
{
	(void) point;
	(void) data;
	*normal = ((t_plane *)obj->obj)->vector;
	return (0);
}

int	ft_get_normal_cylinder(t_point *point, t_object *obj,
		t_point *normal, t_data *data)
{
	const t_cylinder	*cyl = obj->obj;
	double				m;
	double				len;

	m = (data->tmp1.x * cyl->vector.x + data->tmp1.y * cyl->vector.y
			+ data->tmp1.z * cyl->vector.z) * data->closest
		+ data->tmp2.x * cyl->vector.x + data->tmp2.y * cyl->vector.y
		+ data->tmp2.z * cyl->vector.z;
	normal->x = point->x - cyl->position.x - cyl->vector.x * m;
	normal->y = point->y - cyl->position.y - cyl->vector.y * m;
	normal->z = point->z - cyl->position.z - cyl->vector.z * m;
	len = sqrt(normal->x * normal->x + normal->y
			* normal->y + normal->z * normal->z);
	normal->x /= len;
	normal->y /= len;
	normal->z /= len;
	return (1);
}
