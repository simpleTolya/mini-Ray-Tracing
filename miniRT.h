/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:32:03 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 19:37:20 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_objects.h"

# define WINDOW_SIZE		1080
# define BACKGROUND_COLOR	0

# define MAINP_ESC			53
# define MAINP_SPACE		49
# define ARROW_LEFT			123
# define ARROW_RIGHT		124
# define ARROW_UP			126
# define ARROW_DOWN			125
# define MOUSE_DOWN			4
# define MOUSE_UP			5
# define MOUSE_CLICK		1
# define X_COORDINATE_UP	12
# define Y_COORDINATE_UP	13
# define Z_COORDINATE_UP	14
# define X_COORDINATE_DOWN	0
# define Y_COORDINATE_DOWN	1
# define Z_COORDINATE_DOWN	3
# define ROTATE_KEY			15
# define ON_DESTROY			17

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*lst_obj;
	t_point		vector_x;
	t_point		vector_y;
	double		t_min;
	double		t_max;
	t_point		tmp1;
	t_point		tmp2;
	double		closest;
	double		roots[2];
	t_object	*clicked;
}	t_data;

int			ft_get_rgb(const char *rgb, int *color);
int			ft_get_coordinates(const char *str, t_point *point);
void		ft_get_ambient(t_data *data, char **strs);
void		ft_get_camera(t_data *data, char **strs);
int			ft_intersect_sphere(t_point *start, t_point *end,
				t_object *obj, t_data *data);
int			ft_intersect_plane(t_point *start, t_point *end,
				t_object *obj, t_data *data);
int			ft_intersect_cylinder(t_point *start, t_point *end,
				t_object *obj, t_data *data);
int			ft_get_normal_sphere(t_point *point, t_object *obj,
				t_point *normal, t_data *data);
int			ft_get_normal_plane(t_point *point, t_object *obj,
				t_point *normal, t_data *data);
int			ft_get_normal_cylinder(t_point *point, t_object *obj,
				t_point *normal, t_data *data);
void		ft_update_angle_matrix(t_data *data);
t_object	*ft_closest_intersection(t_point *v_d, t_point *pix,
				t_data *data, double *closest);
void		ft_error(char *str);
int			ft_clear_strs(char **strs);
void		ft_init_data(t_data *data, const char *filename);
void		ft_get_objs(t_data *data, const char *filename);
void		ft_get_object(t_data *data, char **strs);
void		my_mlx_pixel_put(t_mlx *map, int x, int y, int color);
void		ft_get_ambient(t_data *data, char **strs);
void		ft_get_camera(t_data *data, char **strs);
void		ft_get_light(t_data *data, char **strs);
void		ft_get_plane(t_data *data, char **strs);
void		ft_get_sphere(t_data *data, char **strs);
void		ft_get_cylinder(t_data *data, char **strs);
int			ft_strtod(const char *str, double *res);
int			ft_strtoi(const char *str, int *num);
t_point		ft_canvas_to_viewport(double x, double y, t_data *data);
void		ft_render(t_data *data);
int			ft_exit(t_data *map);
t_point		vector3_rotate_yx(t_point a, double angle_y, double angle_x);
void		ft_init_actions(t_data *data);
double		ft_compute_light(t_point *point, t_point *nor,
				t_point *obj_ray, t_data *data);
#endif
