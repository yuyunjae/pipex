/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:48:38 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 22:41:25 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*dummy1;
	t_list	*dummy2;
	void	*ptr;

	if (!lst || !f || !(*f) || !del)
		return (0);
	head = 0;
	dummy2 = lst;
	while (dummy2)
	{
		ptr = f(dummy2->content);
		dummy1 = ft_lstnew(ptr);
		if (!dummy1 || !ptr)
		{
			if (ptr)
				del(ptr);
			free(dummy1);
			ft_lstclear(&head, del);
			return (0);
		}
		dummy2 = dummy2->next;
		ft_lstadd_back(&head, dummy1);
	}
	return (head);
}
