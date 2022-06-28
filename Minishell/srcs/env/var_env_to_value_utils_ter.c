/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_to_value_utils_ter.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:04:19 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 21:05:04 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_void_new_value_to_lst(t_list *tmp, char *new_value, t_struct *root)
{
	int	type;

	new_value = ft_strdup("");
	type = ((t_token_cmd *)tmp->content)->type;
	add_element(new_value, type, root, tmp);
	free(new_value);
}
