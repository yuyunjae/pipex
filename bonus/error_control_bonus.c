/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:38:31 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/28 19:23:21 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	common_error(t_pipex *pipe_info, char *str, int option)
{
	char	*error_msg;

	ft_putstr_fd(pipe_info->command[0], 2);
	ft_putstr_fd(": ", 2);
	error_msg = strerror(errno);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	write(2, "\n", 1);
	if (option != 0)
		exit(option);
	exit(errno);
}

void	command_error(t_pipex *pipe_info, char *str)
{
	char	*error_msg;

	error_msg = "command not found";
	ft_putstr_fd(pipe_info->command[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	write(2, "\n", 1);
	exit(127);
}

void	error_occur(char *s)
{
	char	*str;

	if (s)
		ft_putstr_fd(s, 2);
	str = strerror(errno);
	if (errno != 0)
		ft_putstr_fd(str, 2);
	exit(errno);
}
