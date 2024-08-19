/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:38:32 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 19:16:03 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in(char const *set, char c)
{
	int	set_len;
	int	i;

	set_len = ft_strlen(set);
	i = 0;
	while (i < set_len)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		length;
	int		i;
	int		start;

	length = ft_strlen(s1);
	i = 0;
	while (i < length)
	{
		if (!ft_is_in(set, s1[i]))
			break ;
		i++;
	}
	start = i;
	i = length - 1;
	while (i >= 0)
	{
		if (!ft_is_in(set, s1[i]))
			break ;
		i--;
	}
	str = ft_substr(s1, start, i + 1 - start);
	return (str);
}
