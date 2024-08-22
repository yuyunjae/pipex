/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:55:22 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/23 06:08:48 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	ft_strtol(char *str, int sign)
{
	unsigned long	i;
	unsigned long	ans;
	unsigned long	before;

	i = 0;
	ans = 0;
	before = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		ans = ans * 10 + str[i] - '0';
		if (before > ans && sign == -1)
			return (0);
		else if (before > ans && sign == 1)
			return (-1);
		else if (ans >= (long)9223372036854775807 && sign == 1)
			return (-1);
		else if (ans > (long)9223372036854775807 && sign == -1)
			return (0);
		before = ans;
		i++;
	}
	return (sign * ans);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	sign = 1;
	i = 0;
	ans = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return ((int)ft_strtol((char *)(str + i), sign));
}
