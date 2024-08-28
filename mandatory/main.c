/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:40:38 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/28 20:11:59 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**parse_path(char **env)
{
	int		i;
	int		index;
	char	**str;

	i = -1;
	index = -1;
	if (!env)
		error_occur("no env!");
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			str = pipex_split(env[i] + 5, ':');
			if (!str)
				error_occur("malloc_error");
			return (str);
		}
	}
	str = pipex_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
	if (!str)
		error_occur("malloc_error");
	return (str);
}

static void	pipex_setting(t_pipex *pipe_info, int argc, char **argv, char **env)
{
	int		i;
	char	*str;

	i = -1;
	pipe_info->arg_count = argc;
	pipe_info->command = argv;
	pipe_info->path = parse_path(env);
	if (ft_strncmp(argv[0], "./", 2) == 0)
		argv[0] = &argv[0][2];
	pipe_info->pid = (pid_t *)malloc(sizeof(pid_t)
			* (pipe_info->arg_count - 3));
	if (!pipe_info->pid)
		error_occur("malloc_error");
}

static void	wait_process(t_pipex *pipe_info)
{
	int	i;
	int	status;
	int	exit_status;

	i = -1;
	exit_status = 0;
	while (++i < pipe_info->arg_count - 3)
	{
		if (waitpid(pipe_info->pid[i], &status, 0) == -1)
			error_occur("waitpid_error");
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
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
		pipex(&pipe_info, env, i);
	}
	wait_process(&pipe_info);
	if (pipe_info.path)
	{
		i = -1;
		while (pipe_info.path[++i])
			free(pipe_info.path[i]);
		free(pipe_info.path);
	}
	free(pipe_info.pid);
	exit(0);
}
