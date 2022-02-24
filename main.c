/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:24:33 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 18:02:18 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_get_object(t_data *data, char **strs)
{
	if (ft_strncmp(strs[0], "A", 2) == 0)
		ft_get_ambient(data, strs);
	else if (ft_strncmp(strs[0], "C", 2) == 0)
		ft_get_camera(data, strs);
	else if (ft_strncmp(strs[0], "L", 2) == 0)
		ft_get_light(data, strs);
	else if (ft_strncmp(strs[0], "pl", 3) == 0)
		ft_get_plane(data, strs);
	else if (ft_strncmp(strs[0], "sp", 3) == 0)
		ft_get_sphere(data, strs);
	else if (ft_strncmp(strs[0], "cy", 3) == 0)
		ft_get_cylinder(data, strs);
	else
		ft_error("Undefined object type");
}

void	ft_get_objs(t_data *data, const char *filename)
{
	char	*line;
	char	**strs;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error: File");
	line = get_next_line(fd);
	while (line)
	{
		strs = ft_split(line, ' ');
		if (strs && strs[0] && ft_strncmp(strs[0], "\n", 2))
			ft_get_object(data, strs);
		ft_clear_strs(strs);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_init_data(t_data *data, const char *filename)
{
	char	*dot_ptr;

	dot_ptr = ft_strrchr(filename, '.');
	if (dot_ptr == 0)
		ft_error("Error: file name");
	if (ft_strncmp(dot_ptr, ".rt", 4) != 0)
		ft_error("Error: file name");
	ft_memset(data, 0, sizeof(t_data));
	ft_get_objs(data, filename);
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == 0)
		ft_error("Error: mlx");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			WINDOW_SIZE, WINDOW_SIZE, "miniRT");
	if (data->mlx.mlx_win == 0)
		ft_error("Error: mlx");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WINDOW_SIZE, WINDOW_SIZE);
	if (data->mlx.img == 0)
		ft_error("Error: mlx");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	data->t_min = 1;
	data->t_max = 100000;
	data->clicked = 0;
}

void	ft_init_angle_matrix(t_data *data)
{
	double	a;

	a = data->camera.vector.x / (data->camera.vector.x * data->camera.vector.x
			+ data->camera.vector.y * data->camera.vector.y
			+ data->camera.vector.z * data->camera.vector.z);
	data->vector_x.x = 1 - a * data->camera.vector.x;
	data->vector_x.y = -a * data->camera.vector.y;
	data->vector_x.z = -a * data->camera.vector.z;
	if (fabs(data->vector_x.x) < 0.00001)
		data->vector_x.z = -1;
	else if (fabs(data->vector_x.x - 2) < 0.00001)
		data->vector_x.z = 1;
	a = data->camera.vector.y / (data->camera.vector.x * data->camera.vector.x
			+ data->camera.vector.y * data->camera.vector.y
			+ data->camera.vector.z * data->camera.vector.z);
	data->vector_y.x = -a * data->camera.vector.x;
	data->vector_y.y = 1 - a * data->camera.vector.y;
	data->vector_y.z = -a * data->camera.vector.z;
	if (fabs(data->vector_y.y) < 0.000001)
		data->vector_y.z = -1;
	else if (fabs(data->vector_y.y - 2) < 0.000001)
		data->vector_y.z = 1;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		write(2, "Bad arguments\n", 14);
		return (1);
	}
	ft_init_data(&data, argv[1]);
	ft_init_angle_matrix(&data);
	ft_init_actions(&data);
	ft_render(&data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
