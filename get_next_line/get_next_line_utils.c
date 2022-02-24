/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:02:56 by marmand           #+#    #+#             */
/*   Updated: 2021/10/15 13:19:45 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_buffer_read_ch(int fd, char *ch_ptr)
{
	static t_buf	buf[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX)
		return (-1);
	if (buf[fd].buffer == 0)
	{
		buf[fd].buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (buf[fd].buffer == 0)
			return (-1);
	}
	if (buf[fd].first == buf[fd].count)
	{
		buf[fd].first = 0;
		buf[fd].count = read(fd, buf[fd].buffer, BUFFER_SIZE);
	}
	if (buf[fd].count > 0)
	{
		*ch_ptr = buf[fd].buffer[buf[fd].first];
		buf[fd].first++;
		return (1);
	}
	free(buf[fd].buffer);
	buf[fd].buffer = 0;
	return (buf[fd].count);
}

int	ft_str_init(t_str *str)
{
	str->array = (char *)malloc(sizeof(char) * 10);
	if (str->array == 0)
		return (1);
	str->array[0] = 0;
	str->length = 0;
	str->size = 10;
	return (0);
}

char	*ft_strcpy(char *dst, char *src)
{
	char	*first;

	first = dst;
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
	return (first);
}

int	ft_str_insert_char(t_str *str, char ch)
{
	char	*tmp;

	if (str->length + 1 == str->size)
	{
		tmp = (char *)malloc(sizeof(char) * (2 * str->size - 1));
		if (tmp == 0)
			return (-1);
		str->size = 2 * str->size - 1;
		ft_strcpy(tmp, str->array);
		free(str->array);
		str->array = tmp;
	}
	str->array[str->length] = ch;
	str->array[str->length + 1] = 0;
	str->length++;
	return (0);
}

char	*ft_get_res(t_str *str, int flag)
{
	char	*res;

	if ((flag == -1) || (flag == 0 && str->length == 0))
	{
		free(str->array);
		return (0);
	}
	res = (char *)malloc(sizeof(char) * (str->length + 1));
	if (res == 0)
	{
		free(str->array);
		return (0);
	}
	ft_strcpy(res, str->array);
	free(str->array);
	return (res);
}
