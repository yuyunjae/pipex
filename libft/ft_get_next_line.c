/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:04:45 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/19 15:53:50 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_fd_head(t_gnl **fd_head, int fd)
{
	t_gnl	*dummy;
	t_gnl	*trash;

	dummy = *fd_head;
	trash = *fd_head;
	if (!fd_head || !*fd_head)
		return (0);
	while (dummy)
	{
		if (dummy->fd == fd)
		{
			if (dummy == *fd_head)
				(*fd_head) = (*fd_head)->next_node;
			else
				trash->next_node = dummy->next_node;
			if (dummy->content)
				free(dummy->content);
			free(dummy);
			return (0);
		}
		trash = dummy;
		dummy = dummy->next_node;
	}
	return (0);
}

static char	*remake_head(t_gnl **head, t_gnl *fd_line, int point)
{
	char	*new_content;
	char	*return_line;

	return_line = (char *)ft_calloc(sizeof(char), point + 2);
	new_content = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (new_content && return_line)
	{
		ft_strlcpy(return_line, fd_line->content, point + 2);
		ft_strlcpy(new_content, fd_line->content + point + 1, BUFFER_SIZE + 1);
		free(fd_line->content);
		fd_line->content = new_content;
		if (fd_line->eof && !ft_strlen(fd_line->content))
			free_fd_head(head, fd_line->fd);
		return (return_line);
	}
	free(new_content);
	free(return_line);
	return (free_fd_head(head, fd_line->fd));
}

static t_gnl	*check_fd(t_gnl **head, int fd)
{
	t_gnl	*dummy;
	t_gnl	*dummy_before;

	dummy = *head;
	while (dummy)
	{
		if (dummy->fd == fd)
			return (dummy);
		dummy_before = dummy;
		dummy = dummy->next_node;
	}
	dummy = (t_gnl *)ft_calloc(sizeof(t_gnl), 1);
	if (!dummy)
		return (0);
	dummy->content = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!dummy->content)
	{
		free(dummy);
		return (0);
	}
	if (!*head)
		*head = dummy;
	else
		dummy_before->next_node = dummy;
	return (dummy);
}

static int	read_file(t_gnl **head, t_gnl *fd_l, int *length)
{
	int		r_s;

	if (*length - ft_strlen(fd_l->content) < BUFFER_SIZE +1)
	{
		*length *= 2;
		if (!extand_content(fd_l, *length))
		{
			free_fd_head(head, fd_l->fd);
			return (0);
		}
	}
	r_s = read(fd_l->fd, fd_l->content
			+ ft_strlen(fd_l->content), BUFFER_SIZE);
	if (r_s == -1)
	{
		free_fd_head(head, fd_l->fd);
		return (0);
	}
	else if (r_s == 0)
		fd_l->eof = 1;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl	*head;
	t_gnl			*fd_line;
	int				length;
	int				point;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	fd_line = check_fd(&head, fd);
	if (!fd_line)
		return (0);
	fd_line->fd = fd;
	point = ft_strchr_index(fd_line, fd_line->content, '\n');
	length = BUFFER_SIZE;
	while (point == -1 && !fd_line->eof)
	{
		if (!read_file(&head, fd_line, &length))
			return (0);
		point = ft_strchr_index(fd_line, fd_line->content, '\n');
		if (point >= 0 || fd_line->eof)
			break ;
	}
	if (!ft_strlen(fd_line->content) && fd_line->eof)
		return (free_fd_head(&head, fd));
	return (remake_head(&head, fd_line, point));
}
