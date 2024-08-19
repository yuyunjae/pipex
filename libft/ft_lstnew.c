/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:37:13 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 22:39:49 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*first_node;

	first_node = (t_list *)malloc(sizeof(t_list));
	if (!first_node)
		return (0);
	first_node->content = content;
	first_node->next = 0;
	return (first_node);
}
