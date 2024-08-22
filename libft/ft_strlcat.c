/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:52:59 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/23 04:48:08 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	if (dst == 0 && dstsize == 0)
		return (ft_strlen(src));
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	if (d_len >= dstsize)
		return (s_len + dstsize);
	else
	{
		while (src[i] != 0 && (d_len + i + 1 < dstsize))
		{
			dst[d_len + i] = src[i];
			i++;
		}
		if (d_len + i + 1 <= dstsize)
			dst[d_len + i] = 0;
		return (d_len + s_len);
	}
}
