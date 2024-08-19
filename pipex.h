/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:01:25 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/19 23:32:08 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int 	**fd;
	pid_t	*pid;
	int		arg_count;
	int		input_file_fd;
	char	output_file_fd;
	char	**path;
	char	**command;
} t_pipex;

void	error_occur(const char *s);
void	wait_process(t_pipex *pipe_info);
char	**parse_path(char **env);
void	pipex_setting(t_pipex *pipe_info, int argc, char **argv, char **env);
void	execute_command(char *file, char **command, char **env);
void	parse_command(t_pipex *pipe_info, char **env, int arg_index);
void	child_process(t_pipex *pipe_info, char **env, int arg_index);
void	pipex(t_pipex *pipe_info, char **env, int arg_index);

char	**pipex_split(char const *s, char c);

#endif
