/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:23:51 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/28 17:12:28 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*make_str(char *str)
{
	int		i;
	int		index;
	char	*s;
	char	*temp;

	i = -1;
	index = 0;
	s = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	if (!s)
		return (0);
	while (str[++i])
	{
		if (str[i] != '\\')
			s[index++] = str[i];
	}
	temp = ft_strdup(s);
	free(s);
	if (!temp)
		return (0);
	return (temp);
}

static int	make_str_set(t_split_info *info)
{
	int		index;
	int		word;

	index = 0;
	word = 0;
	while (index < info->str_len)
	{
		if (info->str[index])
		{
			info->result[word] = make_str(&info->str[index]);
			if (!info->result[word])
			{
				free_all(info->result, word);
				free(info->str);
				return (0);
			}
			word++;
			while (info->str[index] && index < info->str_len)
				index++;
		}
		else
			index++;
	}
	free(info->str);
	return (1);
}

static int	count_word_sub(t_split_info *info, int index, int before)
{
	int	flag;

	flag = info->str[index];
	info->word_cnt++;
	info->str[index++] = 0;
	while (index < info->str_len)
	{
		if (info->str[index] == flag && !before)
			break ;
		if (info->str[index] == '\\')
			before = 1;
		else
			before = 0;
		index++;
	}
	info->str[index++] = 0;
	return (index);
}

static void	count_word(t_split_info *info)
{
	int		index;
	int		before;

	index = 0;
	info->word_cnt = 0;
	before = 0;
	while (index < info->str_len)
	{
		if (info->str[index] == '\\')
			before = 1;
		else
			before = 0;
		if ((info->str[index] == '\'' || info->str[index] == '\"') && !before)
			index = count_word_sub(info, index, before);
		else if (!ft_isspace(info->str[index]))
		{
			info->word_cnt++;
			while (index < info->str_len && !ft_isspace(info->str[index]))
				index++;
		}
		else
			info->str[index++] = 0;
	}
}

char	**make_parse(char *str)
{
	t_split_info	string_info;

	string_info.str_len = ft_strlen(str);
	string_info.str = ft_strdup(str);
	if (!string_info.str)
		return (0);
	count_word(&string_info);
	string_info.result = (char **)ft_calloc(string_info.word_cnt + 1,
			sizeof(char *));
	if (!string_info.result)
	{
		free(string_info.str);
		return (0);
	}
	if (make_str_set(&string_info))
		return (string_info.result);
	return (0);
}
