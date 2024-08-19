/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:53:04 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 22:39:44 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	total;

	total = count * size;
	if (size != 0 && ((size_t)(total / size) != count))
		return (0);
	if (total == 0)
		str = (char *)malloc(total + 1);
	else
		str = (char *)malloc(total);
	if (!str)
		return (0);
	if (!total)
		ft_bzero(str, 1);
	else
		ft_bzero(str, total);
	return (str);
}
