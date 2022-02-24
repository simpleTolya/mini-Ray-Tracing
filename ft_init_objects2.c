/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:02:59 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 17:46:45 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_get_light(t_data *data, char **strs)
{
	if (!strs[1] || !strs[2] || !strs[3] || strs[4])
		ft_error("Error: Light args: count");
	if (ft_get_coordinates(strs[1], &data->light.position))
		ft_error("Error: Light args: position");
	if (ft_strtod(strs[2], &data->light.ratio))
		ft_error("Error: Light args: ratio");
	if (ft_get_rgb(strs[3], &data->light.color))
		ft_error("Error: Light args: color");
}

void	ft_get_plane(t_data *data, char **strs)
{
	t_object	*obj;
	t_plane		*plane;

	if (!strs[1] || !strs[2] || !strs[3] || strs[4])
		ft_error("Error: Plane args: count");
	plane = malloc(sizeof(t_plane));
	obj = malloc(sizeof(t_object));
	if (plane == 0 || obj == 0)
		ft_error("Error: Plane: malloc");
	obj->get_normal = ft_get_normal_plane;
	obj->intersect = ft_intersect_plane;
	if (ft_get_coordinates(strs[1], &plane->position))
		ft_error("Error: Plane args: position");
	if (ft_get_coordinates(strs[2], &plane->vector))
		ft_error("Error: Plane args: vector");
	if (ft_get_rgb(strs[3], &obj->color))
		ft_error("Error: Plane args: color");
	obj->obj = plane;
	ft_lstadd_back(&data->lst_obj, ft_lstnew(obj));
}

void	ft_get_sphere(t_data *data, char **strs)
{
	t_sphere	*sphere;
	t_object	*obj;

	if (!strs[1] || !strs[2] || !strs[3] || strs[4])
		ft_error("Error: Sphere args: count");
	sphere = malloc(sizeof(t_sphere));
	obj = malloc(sizeof(t_object));
	if (sphere == 0 || obj == 0)
		ft_error("Error: Sphere: malloc");
	obj->get_normal = ft_get_normal_sphere;
	obj->intersect = ft_intersect_sphere;
	if (ft_get_coordinates(strs[1], &sphere->center))
		ft_error("Error: Sphere args: position");
	if (ft_strtod(strs[2], &sphere->rad))
		ft_error("Error: Sphere args: diameter");
	sphere->rad /= 2;
	if (ft_get_rgb(strs[3], &obj->color))
		ft_error("Error: Sphere args: color");
	obj->obj = sphere;
	ft_lstadd_back(&data->lst_obj, ft_lstnew(obj));
}

void	ft_get_cylinder(t_data *data, char **strs)
{
	t_cylinder	*cylinder;
	t_object	*obj;

	if (!strs[1] || !strs[2] || !strs[3] || !strs[4] || !strs[5] || strs[6])
		ft_error("Error: Cylinder args: count");
	cylinder = malloc(sizeof(t_cylinder));
	obj = malloc(sizeof(t_object));
	if (cylinder == 0 || obj == 0)
		ft_error("Error: Cylinder: malloc");
	obj->get_normal = ft_get_normal_cylinder;
	obj->intersect = ft_intersect_cylinder;
	if (ft_get_coordinates(strs[1], &cylinder->position))
		ft_error("Error: Cylinder args: position");
	if (ft_get_coordinates(strs[2], &cylinder->vector))
		ft_error("Error: Cylinder args: vector");
	if (ft_strtod(strs[3], &cylinder->radius))
		ft_error("Error: Cylinder args: diameter");
	cylinder->radius /= 2;
	if (ft_strtod(strs[4], &cylinder->height))
		ft_error("Error: Cylinder args: height");
	if (ft_get_rgb(strs[5], &obj->color))
		ft_error("Error: Cylinder args: color");
	obj->obj = cylinder;
	ft_lstadd_back(&data->lst_obj, ft_lstnew(obj));
}
