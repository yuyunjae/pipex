/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:13:31 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 15:41:03 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s);
	if (i <= start || len == 0)
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	i = ft_strlen(s + start);
	if (len > i)
		len = i;
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
