/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:05:57 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/16 18:36:41 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_wordcpy(char const *w, int wordlen)
{
	char	*dst;

	dst = ft_substr(w, 0, wordlen);
	return (dst);
}

static int	ft_checkmalloc(char **tab, char const *s, int index)
{
	if (!s && index > 0)
	{
		while (index > 0)
		{
			free(tab[index - 1]);
			index--;
		}
		free(tab);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (j < ft_wordcount(s, c))
			tab[j++] = ft_wordcpy(&s[i], ft_wordlen(&s[i], c));
		i += ft_wordlen(&s[i], c);
		if (j > 0 && ft_checkmalloc(tab, tab[j - 1], i) == 0)
			return (NULL);
	}
	tab[j] = NULL;
	return (tab);
}
