/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:05:37 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/19 15:52:51 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_index(t_gnl *fd_line, const char *s, int c)
{
	int	i;

	i = 0;
	c = c % 256;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == 0 && s[i] == 0)
		return (i);
	if (fd_line->eof == 1 && i > 0)
		return (i - 1);
	return (-1);
}

int	extand_content(t_gnl *fd_line, int length)
{
	char	*str;

	str = (char *)ft_calloc(sizeof(char), length + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, fd_line->content, ft_strlen(fd_line->content) + 1);
	if (fd_line->content)
		free(fd_line->content);
	fd_line->content = str;
	return (1);
}
