/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:14:36 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/04 22:47:49 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned char	*uc_dst;
	unsigned char	*uc_src;

	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	i = 0;
	j = len;
	if (uc_dst > uc_src)
	{
		while (j-- > 0)
			uc_dst[j] = uc_src[j];
	}
	else if (uc_dst < uc_src)
	{
		while (j > i)
		{
			uc_dst[i] = uc_src[i];
			i++;
		}
	}
	return (dst);
}
