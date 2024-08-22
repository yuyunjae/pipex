/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:06:19 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/23 03:07:20 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_pipex_strjoin(char const *s1, char const *s2, int i)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (i == 1)
		s2_len -= 1;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str, " ", s1_len + 2);
	ft_strlcat(str, s2, s1_len + s2_len + 2);
	return (str);
}

static char	*ft_strjoin_strs(char **str_set, int start, int end)
{
	char	*str;
	char	*temp;

	str = ft_strdup(str_set[start] + 1);
	if (!str)
		error_occur("malloc_error");
	while  (++start <= end)
	{
		temp = str;
		if (start < end)
			str = ft_pipex_strjoin(temp, str_set[start], 0);
		else
			str = ft_pipex_strjoin(temp, str_set[start], 1);
		free(temp);
		if (!str)
			error_occur("malloc_error");
	}
	return (str);
}

static int	ft_str_set_len(char **str_set)
{
	int	index;

	index = 0;
	while (str_set[index])
		index++;
	return (index);
}

static char	**remake_str_set(char **str_set, int index, int i, int val)
{
	char		**return_set;
	int			point;
	const int	length = ft_str_set_len(str_set);

	if (index == i)
		return (str_set);
	return_set = (char **)ft_calloc(sizeof(char *) * (index - i + length + 1), 1);
	if (!return_set)
		error_occur("malloc_error");
	point = 0;
	while (val < length)
	{
		if (val == index)
		{
			return_set[point] = ft_strjoin_strs(str_set, index, i);
			val += i - index + 1;
		}
		else
			return_set[point] = ft_strdup(str_set[val++]);
		// ft_putendl_fd(return_set[point], 1);
		if (!return_set[point++])
			error_occur("malloc_error");
	}
	free_all(str_set, length);
	return (return_set);
}

static char	**remake_str(char **str_set, int i)
{
	char		*str;
	const int	index = i;

	if (str_set[i])
	{
		if (str_set[i] && str_set[i][0] == '\'')
		{
			while (str_set[i] && str_set[i][ft_strlen(str_set[i]) - 1] != '\'')
				i++;
			if (!str_set[i])
				i--;
			str_set = remake_str_set(str_set, index, i, 0);
		}
		else if (str_set[i] && str_set[i][0] == '\"')
		{
			while (str_set[i] && str_set[i][ft_strlen(str_set[i]) - 1] != '\"')
				i++;
			if (!str_set[i])
				i--;
			str_set = remake_str_set(str_set, index, i, 0);
		}
	}
	return (str_set);
}

char	**fix_split(char const *s, char c)
{
	char	**str_set;
	char	*str;
	int		index;

	index = -1;
	str_set = ft_split(s, c);
	if (!str_set)
		return (0);
	while (str_set[++index])
	{
		//if (!ft_strncmp(str_set[index], "awk", 3) || !ft_strncmp(str_set[index], "sed", 3))
		if ((str_set[index][0] == '\'' || str_set[index][0] == '\"'))
		{
			str_set = remake_str(str_set, index);
			if (!str_set)
				return (0);
			break ;
		}
	}
	return (str_set);
}
