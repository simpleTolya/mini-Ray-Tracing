/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:14:20 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 19:18:02 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTS_H
# define FT_OBJECTS_H

typedef struct s_point	t_point;
typedef struct s_object	t_object;
typedef struct s_data	t_data;
typedef int				(*t_ft_intersect)(t_point *start,
		t_point *end, t_object *obj, t_data *data);
typedef int				(*t_ft_get_normal)(t_point *point,
		t_object *obj, t_point *normal, t_data *data);

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_ambient
{
	double	ratio;
	int		color;
}			t_ambient;

typedef struct s_camera
{
	t_point	position;
	t_point	vector;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_point	position;
	double	ratio;
	int		color;
}	t_light;

typedef struct s_object
{
	t_ft_intersect	intersect;
	t_ft_get_normal	get_normal;
	int				color;
	void			*obj;
}	t_object;

typedef struct s_sphere
{
	t_point			center;
	double			rad;
}	t_sphere;

typedef struct s_plane
{
	t_point			position;
	t_point			vector;
}	t_plane;

typedef struct s_cylinder
{
	t_point			position;
	t_point			vector;
	double			radius;
	double			height;
}	t_cylinder;

#endif