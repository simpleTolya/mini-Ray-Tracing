/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:01:23 by marmand           #+#    #+#             */
/*   Updated: 2021/10/15 13:53:37 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_buf
{
	char	*buffer;
	int		count;
	int		first;
}	t_buf;

typedef struct s_str
{
	char	*array;
	int		size;
	int		length;
}	t_str;

char	*get_next_line(int fd);
int		ft_buffer_read_ch(int fd, char *ch_ptr);
int		ft_str_init(t_str *str);
char	*ft_strcpy(char *dst, char *src);
int		ft_str_insert_char(t_str *str, char ch);
char	*ft_get_res(t_str *str, int flag);

#endif