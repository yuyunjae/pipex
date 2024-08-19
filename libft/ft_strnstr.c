/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:30:23 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 15:36:53 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	j;

	if (haystack == 0 && len == 0)
		return (0);
	i = 0;
	s1 = (char *)haystack;
	s2 = (char *)needle;
	if (*s2 == 0)
		return (s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s1[i + j] == s2[j] && i + j < len)
		{
			j++;
			if (s2[j] == 0)
				return (s1 + i);
		}
		i++;
	}
	return (0);
}
