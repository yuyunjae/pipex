/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:01:25 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/23 07:56:11 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>

typedef struct s_pipex
{
	pid_t	*pid;
	int		arg_count;
	int		input_file_fd;
	char	output_file_fd;
	char	**path;
	char	**command;
} t_pipex;

typedef struct s_comm
{
	char	*str;
	char	**comm;
}	t_comm;

typedef struct s_split_info
{
	int		str_len;
	char	*str;
	int		word_cnt;
	char	**result;
}	t_split_info;

void	common_error(t_pipex *pipe_info, char *str, int option);
void	command_error(t_pipex *pipe_info, char *str);
void	error_occur(char *s);
void	wait_process(t_pipex *pipe_info);
char	**parse_path(char **env);
void	pipex_setting(t_pipex *pipe_info, int argc, char **argv, char **env);
void	execute_command(t_pipex *pipe_info, char **env, t_comm *com_str, int arg_index);
void	parse_command(t_pipex *pipe_info, char **env, int arg_index);
void	child_process(t_pipex *pipe_info, char **env, int arg_index, int pipe_fd[2]);
void	pipex(t_pipex *pipe_info, char **env, int arg_index);

char	**make_parse(char *str);

void	free_all(char **ans, char index);
char	**pipex_split(char const *s, char c);
char	**fix_split(char const *s, char c);

#endif
