/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:42:28 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 19:14:49 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_back_strdup(char *s, int i, int sign)
{
	char	*str;
	int		index;

	index = 0;
	if (sign == -1)
		str = (char *)malloc(sizeof(char) * (i + 2));
	else
		str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	if (sign == -1)
		str[index++] = '-';
	while (i--)
	{
		str[index++] = s[i];
	}
	str[index] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*str;
	int		i;
	char	s[12];

	sign = 1;
	i = 0;
	if (n < 0)
		sign = -1;
	else if (n == 0)
		s[i++] = '0';
	while (n > 0)
	{
		s[i++] = n % 10 + '0';
		n /= 10;
	}
	while (n < 0)
	{
		s[i++] = '0' - n % 10;
		n /= 10;
	}
	str = ft_back_strdup(s, i, sign);
	if (!str)
		return (0);
	return (str);
}
