/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:21:41 by enena             #+#    #+#             */
/*   Updated: 2021/11/27 19:35:50 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Function creates a copy of the SLL list [lst]
// and applies the function [f] to each node
// Returns pointer to begin new SLL list.
// In case of memory allocation error,
// clears the created list and returns with [del]
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin_lst;
	t_list	*curr;

	begin_lst = NULL;
	if (lst && f && del)
	{
		begin_lst = ft_lstnew(f(lst->content));
		if (!(begin_lst))
			ft_lstdelone(begin_lst, del);
		if (!(begin_lst))
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			curr = ft_lstnew(f(lst->content));
			if (!(curr))
				ft_lstclear(&begin_lst, del);
			if (!(curr))
				return (begin_lst);
			ft_lstadd_back(&begin_lst, curr);
			lst = lst->next;
		}
	}
	return (begin_lst);
}
