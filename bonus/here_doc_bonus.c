/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:56:51 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/28 23:03:17 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	make_temp_file(t_pipex *p_info)
{
	char	*dummy;
	int		num;

	dummy = (char *)ft_calloc(10, 1);
	if (!dummy)
		error_occur("malloc_error");
	ft_strlcpy(dummy, "/tmp/temp", 10);
	p_info->here_doc_temp = ft_strdup(dummy);
	if (!p_info->here_doc_temp)
		error_occur("malloc_error");
	num = 0;
	while (access(p_info->here_doc_temp, F_OK) == 0)
	{
		free(p_info->here_doc_temp);
		p_info->here_doc_temp = ft_strjoin(dummy, ft_itoa(num++));
		if (!p_info->here_doc_temp)
			error_occur("malloc_error");
	}
	free(dummy);
}

void	here_doc_check(t_pipex *p_info, char **env, int index)
{
	char	*str;

	make_temp_file(p_info);
	p_info->input_file_fd = open(p_info->here_doc_temp, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (p_info->input_file_fd < 0)
		common_error(p_info, p_info->here_doc_temp, 1);
	str = get_next_line(0);
	while (str)
	{
		if (!ft_strncmp(str, p_info->command[2], ft_strlen(p_info->command[2]))
			&& (!str[ft_strlen(p_info->command[2])]
				|| str[ft_strlen(p_info->command[2])] == '\n'))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, p_info->input_file_fd);
		free(str);
		str = get_next_line(0);
	}
	close(p_info->input_file_fd);
}

void	here_doc_input(t_pipex *p_info, int index)
{
	p_info->input_file_fd = open(p_info->here_doc_temp, O_RDONLY);
	if (p_info->input_file_fd < 0)
		common_error(p_info, p_info->here_doc_temp, 0);
	if (dup2(p_info->input_file_fd, STDIN_FILENO) < 0)
		common_error(p_info, p_info->command[index + 2], 0);
	close(p_info->input_file_fd);
	if (unlink(p_info->here_doc_temp) == -1)
		common_error(p_info, p_info->here_doc_temp, 0);
}

void	output_check(t_pipex *p_info, int index)
{
	if (p_info->here_doc == 1)
		p_info->output_file_fd = open(p_info->command[p_info->arg_count - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p_info->output_file_fd = open(p_info->command[p_info->arg_count - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_info->output_file_fd < 0)
		common_error(p_info, p_info->command[p_info->arg_count -1], 1);
	if (dup2(p_info->output_file_fd, STDOUT_FILENO) < 0)
		common_error(p_info, p_info->command[index + 2], 0);
	close(p_info->output_file_fd);
}
