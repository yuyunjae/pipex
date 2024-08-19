/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:14 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/19 23:35:01 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_leaks(void)
{
	system("leaks pipex");
}

void	error_occur(const char *s)
{
	perror(s);
	exit(1);
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
				error_occur("malloc_eror");
			return (str);
		}
	}
	error_occur(NULL); // no PATH environment variable
	return (0);
}

void	execute_command(char *file, char **command, char **env)
{
	int	i;

	i = -1;
	if (execve(file, command, env) == -1)
		error_occur("execve에서 에러"); // command error (ls +0 같은..)
	free(file);
	while (command[++i])
		free(command[i]);
	free(command);
}

void	parse_command(t_pipex *pipe_info, char **env, int arg_index)
{
	char	**command;
	char	*str;
	int		i;

	i = -1;
	command = ft_split(pipe_info->command[arg_index + 2], ' ');
	// ft_putendl_fd("error1", 2);
	if (!command)
		error_occur("parse_command error1");
	// ft_putendl_fd("error2", 2);
	if (access(command[0], X_OK) != -1)
	{
		// ft_putendl_fd("error3", 2);
		str = ft_strdup(command[0]);
		if (!str)
			error_occur("parse_command error2");
		return (execute_command(str, command, env));
	}
	// ft_putendl_fd("error4", 2);
	while (pipe_info->path[++i])
	{
		// ft_putendl_fd("error5", 2);

		str = ft_strjoin(pipe_info->path[i], command[0]);

		// ft_putendl_fd(str, 2);

		if (!str)
			error_occur("parse_command error3");
		if (access(str, X_OK) != -1)
			return (execute_command(str, command, env));
		free(str);
	}
	// ft_putendl_fd("error6", 2);
	error_occur("parse_command error4"); // 해당 명령어 못찾음.
}

void	child_process(t_pipex *pipe_info, char **env, int arg_index)
{
	if (dup2(pipe_info->fd[arg_index][1], STDOUT_FILENO) == -1)
		error_occur("file check11");
	close(pipe_info->fd[arg_index][0]);
	close(pipe_info->fd[arg_index][1]);
	if (arg_index == 0)
	{
		pipe_info->input_file_fd = open(pipe_info->command[1], O_RDONLY, 0644);
		if (pipe_info->input_file_fd == -1)
			error_occur("file check11");
		if (dup2(pipe_info->input_file_fd, STDIN_FILENO) == -1)
			error_occur("file check11");
		close(pipe_info->input_file_fd);
	}
	else if (arg_index == pipe_info->arg_count - 4)
	{
		pipe_info->output_file_fd = open(pipe_info->command[pipe_info->arg_count - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (pipe_info->output_file_fd == -1)
			error_occur("file check11");
		if (dup2(pipe_info->output_file_fd, STDOUT_FILENO) == -1)
			error_occur("file check11");
		close(pipe_info->output_file_fd);
	}
	parse_command(pipe_info, env, arg_index);
}

void	pipex(t_pipex *pipe_info, char **env, int arg_index)
{
	if (pipe(pipe_info->fd[arg_index]) == -1)
		error_occur(NULL);
	pipe_info->pid[arg_index] = fork();
	if (pipe_info->pid[arg_index] == -1)
		error_occur(NULL);
	else if (pipe_info->pid[arg_index] == 0)
	{
		// child
		child_process(pipe_info, env, arg_index);
		exit(0);
	}
	else
	{
		// parent
		if (dup2(pipe_info->fd[arg_index][0], STDIN_FILENO) == -1) // read -> fd = 0;
			error_occur(NULL);
		close(pipe_info->fd[arg_index][1]); // write close
		close(pipe_info->fd[arg_index][0]); // read close
		// 마지막에 output file을 0번 fd가 가르키고 있는데, 이것도 닫아야하는가..
		// if (arg_index < pipe_info->arg_count - 4)
		// 	close(0);
	}
}

void	pipex_setting(t_pipex *pipe_info, int argc, char **argv, char **env)
{
	int	i;

	i = -1;
	pipe_info->arg_count = argc;
	pipe_info->command = argv;
	pipe_info->path = parse_path(env);
	if (!pipe_info->path)
		error_occur(NULL);

	// pipe_info->input_file_fd = open(argv[1], O_RDONLY, 0644);
	// pipe_info->output_file_fd = open(argv[argc -1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	pipe_info->pid = (pid_t *)malloc(sizeof(pid_t) * (pipe_info->arg_count - 3));
	pipe_info->fd = (int **)malloc(sizeof(int *) * (pipe_info->arg_count - 3));
	// 나중에 open한거 따로 닫아줘야함.
	// if (pipe_info->input_file_fd == -1 || pipe_info->output_file_fd == -1 || !pipe_info->pid || !pipe_info->fd)
	if (!pipe_info->pid || !pipe_info->fd)
		error_occur(NULL);
	while (++i < pipe_info->arg_count - 3)
	{
		pipe_info->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_info->fd[i])
			error_occur(NULL);
	}
}

void	wait_process(t_pipex *pipe_info)
{
	int	i;

	i = -1;
	while (++i < pipe_info->arg_count - 3)
	{
		if (waitpid(pipe_info->pid[i], NULL, 0) == -1)
			error_occur(NULL);
	}
}

int main(int argc, char **argv, char **env)
{
	t_pipex	pipe_info;
	int		i;

	if (argc != 5)
		return (1);
	ft_memset(&pipe_info, 0, sizeof(t_pipex));
	pipex_setting(&pipe_info, argc, argv, env);
	i = -1;
	while (++i < pipe_info.arg_count - 3)
	{
		pipex(&pipe_info, env, i);
	}
	wait_process(&pipe_info);

	// atexit(check_leaks);
	exit(0);
}
