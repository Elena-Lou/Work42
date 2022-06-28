/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 09:25:33 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/06 17:28:45 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*toclear;

	toclear = *lst;
	while (toclear)
	{
		tmp = toclear->next;
		ft_lstdelone(toclear, del);
		toclear = tmp;
	}
	*lst = NULL;
}
