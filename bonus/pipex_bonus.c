/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:14 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/28 23:03:05 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(t_pipex *p_info, char **env, t_comm *com_str, int index)
{
	execve(com_str->str, com_str->comm, env);
	common_error(p_info, p_info->command[index + 2], 0);
}

void	check_sh(t_pipex *pipe_info, char **env, t_comm *com_str, int arg_index)
{
	if (!ft_strncmp(com_str->comm[0], "./", 2))
	{
		if (access(ft_strchr(com_str->comm[0], '/') + 1, X_OK) != 0)
			common_error(pipe_info, pipe_info->command[arg_index + 2], 126);
		else
		{
			com_str->str = ft_strdup(com_str->comm[0]);
			if (!com_str->str)
				error_occur("malloc_error");
			return (execute_command(pipe_info, env, com_str, arg_index));
		}
	}
	if (ft_strchr(com_str->comm[0], '/') && access(com_str->comm[0], X_OK) == 0)
	{
		com_str->str = ft_strdup(com_str->comm[0]);
		if (!com_str->str)
			error_occur("malloc_error");
		return (execute_command(pipe_info, env, com_str, arg_index));
	}
	return ;
}

void	parse_command(t_pipex *pipe_info, char **env, int arg_index)
{
	t_comm	com_str;
	int		i;

	i = -1;
	com_str.comm = make_parse(pipe_info->command[arg_index + 2]);
	if (!com_str.comm)
		error_occur("malloc_error");
	check_sh(pipe_info, env, &com_str, arg_index);
	if (pipe_info->path)
	{
		while (pipe_info->path[++i])
		{
			com_str.str = ft_strjoin(pipe_info->path[i], com_str.comm[0]);
			if (!com_str.str)
				error_occur("malloc_error");
			if (access(com_str.str, X_OK) == 0)
				execute_command(pipe_info, env, &com_str, arg_index);
			free(com_str.str);
		}
	}
	command_error(pipe_info, com_str.comm[0]);
}

void	child_process(t_pipex *p_info, char **env, int index, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		common_error(p_info, p_info->command[index + 2], 0);
	close(pipe_fd[1]);
	if (index == 0)
	{
		p_info->input_file_fd = open(p_info->command[1], O_RDONLY);
		if (p_info->input_file_fd < 0)
			common_error(p_info, p_info->command[1], 0);
		if (dup2(p_info->input_file_fd, STDIN_FILENO) < 0)
			common_error(p_info, p_info->command[index + 2], 0);
		close(p_info->input_file_fd);
	}
	else if (index == 1 && p_info->here_doc)
	{
		here_doc_check(p_info, env, index);
		here_doc_input(p_info, index);
	}
	else if (index == p_info->arg_count - 4)
		output_check(p_info, index);
	parse_command(p_info, env, index);
}

void	pipex(t_pipex *pipe_info, char **env, int arg_index)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
	pipe_info->pid[arg_index] = fork();
	if (pipe_info->pid[arg_index] < 0)
		common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
	else if (pipe_info->pid[arg_index] == 0)
	{
		child_process(pipe_info, env, arg_index, pipe_fd);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
		close(pipe_fd[0]);
		if (arg_index == pipe_info->arg_count - 4)
			close(STDIN_FILENO);
	}
}
