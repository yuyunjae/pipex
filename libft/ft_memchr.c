/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:54:58 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/04 22:47:47 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	find_c;
	unsigned char	*str;
	size_t			i;

	i = 0;
	find_c = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == find_c)
			return (str + i);
		i++;
	}
	return (0);
}
