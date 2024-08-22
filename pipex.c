/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:14 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/23 08:21:36 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void check_leaks(void)
// {
// 	system("leaks pipex");
// }

void	common_error(t_pipex *pipe_info, char *str, int option)
{
	char	*error_msg;

	ft_putstr_fd(pipe_info->command[0], 2);
	ft_putstr_fd(": ", 2);
	error_msg = strerror(errno);
	ft_putstr_fd(str, 2);
	//ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	//ft_putstr_fd(pipe_info->command[arg_index + 2], 2);
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
	//ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	//ft_putstr_fd(pipe_info->command[arg_index + 2], 2);
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

char	**parse_path(char **env)
{
	int		i;
	int		index;
	char	**str;

	i = -1;
	index = -1;
	if (!env)
		error_occur("no env!"); // 수정필요
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			str = pipex_split(env[i] + 5, ':'); // 제발
			if (!str)
				error_occur("malloc_error");
			return (str);
		}
	}
	error_occur("no path error"); // no PATH environment variable
	return (0);
}

void	execute_command(t_pipex *pipe_info, char **env, t_comm *com_str, int arg_index)
{
	// int	i;

	// i = -1;
	execve(com_str->str, com_str->comm, env);
	common_error(pipe_info, pipe_info->command[arg_index + 2], 0);

	// if (execve(com_str->str, com_str->comm, env) == -1)
	// 	common_error(pipe_info, pipe_info->command[arg_index + 2]);
	// free(com_str->str);
	// while (com_str->comm[++i])
	// 	free(com_str->comm[i]);
	// free(com_str->comm);
	// exit(0);
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
	if (access(com_str->comm[0], X_OK) == 0)
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
	while (pipe_info->path[++i])
	{
		com_str.str = ft_strjoin(pipe_info->path[i], com_str.comm[0]);
		if (!com_str.str)
			error_occur("malloc_error");
		if (access(com_str.str, X_OK) == 0)
			execute_command(pipe_info, env, &com_str, arg_index);
		free(com_str.str);
	}
	command_error(pipe_info, com_str.comm[0]); // 해당 명령어 못찾음.
}

		// ft_putnbr_fd(i, 2);
		// ft_putstr_fd(": ", 2);
		// ft_putstr_fd(com_str.comm[0], 2);
		// ft_putstr_fd(": ", 2);
		// ft_putnbr_fd((int)&com_str.comm[0], 2);
		// ft_putendl_fd("  ", 2);

void	child_process(t_pipex *pipe_info, char **env, int arg_index, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
	close(pipe_fd[1]);
	if (arg_index == 0)
	{
		pipe_info->input_file_fd = open(pipe_info->command[1], O_RDONLY);
		if (pipe_info->input_file_fd < 0)
			common_error(pipe_info, pipe_info->command[1], 0);
		if (dup2(pipe_info->input_file_fd, STDIN_FILENO) < 0)
			common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
		close(pipe_info->input_file_fd);
	}
	else if (arg_index == pipe_info->arg_count - 4)
	{
		pipe_info->output_file_fd = open(pipe_info->command[pipe_info->arg_count - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (access(pipe_info->command[pipe_info->arg_count - 1], W_OK) < 0)
		// 	common_error(pipe_info, pipe_info->arg_count -3, 1);
		if (pipe_info->output_file_fd < 0)
			common_error(pipe_info, pipe_info->command[pipe_info->arg_count -1], 0);
		if (dup2(pipe_info->output_file_fd, STDOUT_FILENO) < 0)
			common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
		close(pipe_info->output_file_fd);
	}
	parse_command(pipe_info, env, arg_index);
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
		close(pipe_fd[1]); // write close
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0) // read -> fd = 0;
			common_error(pipe_info, pipe_info->command[arg_index + 2], 0);
		close(pipe_fd[0]); // read close
		// 마지막에 output file을 0번 fd가 가르키고 있는데, 이것도 닫아야하는가..
		if (arg_index == pipe_info->arg_count - 4)
			close(STDIN_FILENO);
	}
}

void	pipex_setting(t_pipex *pipe_info, int argc, char **argv, char **env)
{
	int		i;
	char	*str;

	i = -1;
	pipe_info->arg_count = argc;
	pipe_info->command = argv;
	pipe_info->path = parse_path(env);
	if (!pipe_info->path)
		error_occur("malloc_error");
	if (ft_strncmp(argv[0], "./", 2) == 0)
		argv[0] = &argv[0][2];
	pipe_info->pid = (pid_t *)malloc(sizeof(pid_t) * (pipe_info->arg_count - 3));
	if (!pipe_info->pid)
		error_occur("malloc_error");
	// pipe_info->fd = (int **)malloc(sizeof(int *) * (pipe_info->arg_count - 3));
	// if (!pipe_info->pid || !pipe_info->fd)
	// 	error_occur("malloc_error");
	// while (++i < pipe_info->arg_count - 3)
	// {
	// 	pipe_info->fd[i] = (int *)malloc(sizeof(int) * 2);
	// 	if (!pipe_info->fd[i])
	// 		error_occur("malloc_error");
	// }
}

void	wait_process(t_pipex *pipe_info)
{
	int	i;
	int	status;
	int	exit_status;

	i = -1;
	exit_status = 0;
	while (++i < pipe_info->arg_count - 3)
	{
		if (waitpid(pipe_info->pid[i], &status, 0) == -1)
			error_occur("waitpid_erorr");
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(EXIT_FAILURE);
}

#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	t_pipex	pipe_info;
	int		i;

	if (argc != 5)
		exit(EXIT_FAILURE);
	ft_memset(&pipe_info, 0, sizeof(t_pipex));
	pipex_setting(&pipe_info, argc, argv, env);
	i = -1;
	while (++i < pipe_info.arg_count - 3)
	{
		//printf("%s\n", argv[i + 2]);
		pipex(&pipe_info, env, i);
	}
	wait_process(&pipe_info);
	// atexit(check_leaks);
	exit(0);
}
