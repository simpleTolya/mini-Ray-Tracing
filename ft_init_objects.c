/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:46:27 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 18:07:38 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_get_rgb(const char *rgb, int *color)
{
	char	**strs;
	int		tmp;

	strs = ft_split(rgb, ',');
	if (!strs || !strs[0] || !strs[1] || !strs[2] || strs[3])
		return (ft_clear_strs(strs));
	if (ft_strtoi(strs[0], &tmp))
		return (ft_clear_strs(strs));
	*color = tmp << 16;
	if (ft_strtoi(strs[1], &tmp))
		return (ft_clear_strs(strs));
	*color += tmp << 8;
	if (ft_strtoi(strs[2], &tmp))
		return (ft_clear_strs(strs));
	*color += tmp;
	ft_clear_strs(strs);
	return (0);
}

int	ft_get_coordinates(const char *str, t_point *point)
{
	char	**strs;

	strs = ft_split(str, ',');
	if (!strs || !strs[0] || !strs[1] || !strs[2] || strs[3])
		return (ft_clear_strs(strs));
	if (ft_strtod(strs[0], &point->x))
		return (ft_clear_strs(strs));
	if (ft_strtod(strs[1], &point->y))
		return (ft_clear_strs(strs));
	if (ft_strtod(strs[2], &point->z))
		return (ft_clear_strs(strs));
	return (0);
}

void	ft_get_ambient(t_data *data, char **strs)
{
	if (!strs[1] || !strs[2] || strs[3])
		ft_error("Error: Ambient args: count");
	if (ft_strtod(strs[1], &data->ambient.ratio))
		ft_error("Error: Ambient args: ratio");
	if (ft_get_rgb(strs[2], &data->ambient.color))
		ft_error("Error: Ambient args: rgb");
}

void	ft_get_camera(t_data *data, char **strs)
{
	if (!strs[1] || !strs[2] || !strs[3] || strs[4])
		ft_error("Error: Camera args: count");
	if (ft_get_coordinates(strs[1], &data->camera.position))
		ft_error("Error: Camera args: position");
	if (ft_get_coordinates(strs[2], &data->camera.vector))
		ft_error("Error: Camera args: vector");
	if (ft_strtod(strs[3], &data->camera.fov))
		ft_error("Error: Camera args: fov");
}
