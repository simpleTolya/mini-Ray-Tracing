/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:28:56 by marmand           #+#    #+#             */
/*   Updated: 2022/02/21 18:05:04 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int	ft_clear_strs(char **strs)
{
	int	i;

	if (!strs)
		return (-1);
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (-1);
}

int	ft_strtoi(const char *str, int *num)
{
	long long	res;
	int			sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	if (*str != 0 && *str != '\n')
		return (1);
	*num = (res * sign);
	return (0);
}

static void	ft_get_denumerator(const char **str, double *den)
{
	int	count;

	*den = 0;
	if (**str == '.')
	{
		(*str)++;
		count = 0;
		while (**str >= '0' && **str <= '9')
		{
			count++;
			*den *= 10;
			*den += (**str - '0');
			(*str)++;
		}
		while (count)
		{
			*den /= 10;
			count--;
		}
	}
}

int	ft_strtod(const char *str, double *res)
{
	double	num;
	double	den;
	double	sign;

	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += (*str - '0');
		str++;
	}
	ft_get_denumerator(&str, &den);
	if (*str != 0 && *str != '\n')
		return (1);
	*res = (sign) * (num + den);
	return (0);
}
