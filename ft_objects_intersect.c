/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objects_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:32:06 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 18:27:41 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_intersect_sphere(t_point *start, t_point *end,
		t_object *obj, t_data *data)
{
	t_point	vec;
	t_point	k;
	double	discriminant;
	t_point	d;

	d.x = end->x - start->x;
	d.y = end->y - start->y;
	d.z = end->z - start->z;
	vec.x = start->x - ((t_sphere *)obj->obj)->center.x;
	vec.y = start->y - ((t_sphere *)obj->obj)->center.y;
	vec.z = start->z - ((t_sphere *)obj->obj)->center.z;
	k.x = d.x * d.x + d.y * d.y + d.z * d.z;
	k.y = 2 * (vec.x * d.x + vec.y * d.y + vec.z * d.z);
	k.z = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z
		- ((t_sphere *)obj->obj)->rad * ((t_sphere *)obj->obj)->rad;
	discriminant = k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0)
		return (1);
	data->roots[0] = (-k.y + sqrt(discriminant)) / (2 * k.x);
	data->roots[1] = (-k.y - sqrt(discriminant)) / (2 * k.x);
	return (0);
}

int	ft_intersect_plane(t_point *start, t_point *end,
		t_object *obj, t_data *data)
{
	t_point	vec;

	(void) data;
	vec.x = (end->x - start->x);
	vec.y = (end->y - start->y);
	vec.z = (end->z - start->z);
	data->roots[0] = ((t_plane *)obj->obj)->vector.x
		* (((t_plane *)obj->obj)->position.x - start->x)
		+ ((t_plane *)obj->obj)->vector.y
		* (((t_plane *)obj->obj)->position.y - start->y)
		+ ((t_plane *)obj->obj)->vector.z
		* (((t_plane *)obj->obj)->position.z - start->z);
	data->roots[0] /= (((t_plane *)obj->obj)->vector.x * vec.x
			+ ((t_plane *)obj->obj)->vector.y * vec.y
			+ ((t_plane *)obj->obj)->vector.z * vec.z);
	data->roots[1] = INFINITY;
	return (0);
}

int	ft_solve_quadratic(t_point *k, double *roots)
{
	double	discriminant;

	discriminant = k->y * k->y - 4 * k->x * k->z;
	if (discriminant < 0)
		return (1);
	roots[0] = (-k->y + sqrt(discriminant)) / (2 * k->x);
	roots[1] = (-k->y - sqrt(discriminant)) / (2 * k->x);
	return (0);
}

static int	ft_some_func(t_point *d, t_point *x,
		t_data *data, const t_cylinder *cyl)
{
	double	m;

	m = (d->x * cyl->vector.x + d->y * cyl->vector.y + d->z * cyl->vector.z)
		* data->roots[0] + x->x * cyl->vector.x + x->y * cyl->vector.y + x->z
		* cyl->vector.z;
	if (m < 0 || m > cyl->height)
		data->roots[0] = INFINITY;
	m = (d->x * cyl->vector.x + d->y * cyl->vector.y + d->z * cyl->vector.z)
		* data->roots[1] + x->x * cyl->vector.x + x->y * cyl->vector.y + x->z
		* cyl->vector.z;
	if (m < 0 || m > cyl->height)
		data->roots[1] = INFINITY;
	if (data->roots[0] == INFINITY && data->roots[1] == INFINITY)
		return (1);
	data->tmp1 = *d;
	data->tmp2 = *x;
	return (0);
}

int	ft_intersect_cylinder(t_point *start, t_point *end,
		t_object *obj, t_data *data)
{
	t_point				x;
	t_point				d;
	t_point				k;
	const t_cylinder	*cyl = obj->obj;

	d.x = end->x - start->x;
	d.y = end->y - start->y;
	d.z = end->z - start->z;
	x.x = start->x - cyl->position.x;
	x.y = start->y - cyl->position.y;
	x.z = start->z - cyl->position.z;
	k.x = d.x * d.x + d.y * d.y + d.z * d.z - pow(d.x * cyl->vector.x
			+ d.y * cyl->vector.y + d.z * cyl->vector.z, 2);
	k.y = (d.x * x.x + d.y * x.y + d.z * x.z)
		- (d.x * cyl->vector.x + d.y * cyl->vector.y + d.z * cyl->vector.z)
		* (x.x * cyl->vector.x + x.y * cyl->vector.y + x.z * cyl->vector.z);
	k.y *= 2;
	k.z = (x.x * x.x + x.y * x.y + x.z * x.z) - pow(x.x * cyl->vector.x
			+ x.y * cyl->vector.y + x.z * cyl->vector.z, 2)
		- cyl->radius * cyl->radius;
	if (ft_solve_quadratic(&k, data->roots))
		return (1);
	return (ft_some_func(&d, &x, data, cyl));
}
