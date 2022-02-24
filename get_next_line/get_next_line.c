/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:59:57 by marmand           #+#    #+#             */
/*   Updated: 2021/10/15 00:14:50 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_str	str;
	char	ch;
	int		count;
	int		res;

	if (fd < 0)
		return (0);
	res = ft_buffer_read_ch(fd, &ch);
	if (res == -1 || ft_str_init(&str))
		return (0);
	while (res != -1)
	{
		if (res)
			count = ft_str_insert_char(&str, ch);
		if (res && count == -1)
		{
			free(str.array);
			return (0);
		}
		if (res == 0 || ch == '\n')
			return (ft_get_res(&str, res));
		res = ft_buffer_read_ch(fd, &ch);
	}
	return (ft_get_res(&str, res));
}
