/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:23:18 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/03 15:20:16 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rope;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	else
	{
		rope = ft_lstnew(f(lst->content));
		if (!rope)
		{
			ft_lstclear(&rope, del);
			return (NULL);
		}
		lst = lst->next;
		while (lst)
		{
			tmp = ft_lstnew(f(lst->content));
			ft_lstadd_back(&rope, tmp);
			lst = lst->next;
		}
	}
	return (rope);
}
