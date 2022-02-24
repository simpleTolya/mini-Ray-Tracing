/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:41:25 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 19:29:20 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_move_camera(int key, t_data *data)
{
	if (key == X_COORDINATE_DOWN)
		data->camera.position.x -= 5;
	if (key == X_COORDINATE_UP)
		data->camera.position.x += 5;
	if (key == Y_COORDINATE_DOWN)
		data->camera.position.y -= 5;
	if (key == Y_COORDINATE_UP)
		data->camera.position.y += 5;
	if (key == Z_COORDINATE_DOWN)
		data->camera.position.z -= 50;
	if (key == Z_COORDINATE_UP)
		data->camera.position.z += 5;
}

static void	ft_rotate_obj(t_data *data)
{
	if (data->clicked)
	{
		if (data->clicked->intersect == ft_intersect_cylinder)
			((t_cylinder *)data->clicked->obj)->vector
				= vector3_rotate_yx(((t_cylinder *)data->clicked->obj)
					->vector, 0, 5);
		else if (data->clicked->intersect == ft_intersect_plane)
			((t_plane *)data->clicked->obj)->vector
				= vector3_rotate_yx(((t_plane *)data->clicked->obj)
					->vector, 0, 5);
	}
}

static int	key_hook(int key, t_data *data)
{
	if (key == MAINP_ESC)
		ft_exit(data);
	else if (key == ARROW_UP || key == ARROW_DOWN
		|| key == ARROW_LEFT || key == ARROW_RIGHT)
	{
		if (key == ARROW_UP)
			data->camera.vector = vector3_rotate_yx(data->camera.vector, 0, 5);
		if (key == ARROW_DOWN)
			data->camera.vector = vector3_rotate_yx(data->camera.vector, 0, -5);
		if (key == ARROW_LEFT)
			data->camera.vector = vector3_rotate_yx(data->camera.vector, 5, 0);
		if (key == ARROW_RIGHT)
			data->camera.vector = vector3_rotate_yx(data->camera.vector, -5, 0);
		ft_update_angle_matrix(data);
	}
	else if (key == X_COORDINATE_DOWN || key == X_COORDINATE_UP
		|| key == Y_COORDINATE_DOWN || key == Y_COORDINATE_UP
		|| key == Z_COORDINATE_DOWN || key == Z_COORDINATE_UP)
		ft_move_camera(key, data);
	else if (key == ROTATE_KEY)
		ft_rotate_obj(data);
	else
		return (0);
	ft_render(data);
	return (0);
}

static int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	t_point	d;
	double	closest;
	int		move;

	if (keycode == MOUSE_CLICK)
	{
		d = ft_canvas_to_viewport(-(WINDOW_SIZE / 2 - x),
				WINDOW_SIZE / 2 - y, data);
		data->clicked = ft_closest_intersection(&data->camera.position,
				&d, data, &closest);
	}
	move = 0;
	if (keycode == MOUSE_UP && data->clicked)
		move = 1;
	else if (keycode == MOUSE_DOWN && data->clicked)
		move = -1;
	if (move)
	{
		if (data->clicked->intersect == ft_intersect_sphere)
			((t_sphere *)data->clicked->obj)->rad += move;
		else if (data->clicked->intersect == ft_intersect_cylinder)
			((t_cylinder *)data->clicked->obj)->radius += move;
		ft_render(data);
	}
	return (0);
}

void	ft_init_actions(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, ON_DESTROY, 0, ft_exit, data);
	mlx_key_hook(data->mlx.mlx_win, key_hook, data);
	mlx_mouse_hook(data->mlx.mlx_win, mouse_hook, data);
}
