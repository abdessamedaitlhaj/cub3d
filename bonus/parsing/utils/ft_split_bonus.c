/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradais <paradais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:12:20 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 02:09:51 by paradais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	count_words(char const *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (!*s)
		return (0);
	while (*s && !ft_isspace(*s))
		s++;
	return (1 + count_words(s));
}

static void	free_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

static int	malloc_tab(char **tab, char const *s, int i)
{
	int		k;
	int		j;

	k = 0;
	while (s[k] && !ft_isspace(s[k]))
		k++;
	tab[i] = malloc(sizeof(char) * (k + 1));
	if (!tab[i])
	{
		free_tab(tab, i);
		return (0);
	}
	j = 0;
	while (j < k)
	{
		tab[i][j] = s[j];
		j++;
	}
	tab[i][j] = '\0';
	return (1);
}

char	**ft_split(char const *s)
{
	int		total_length;
	int		i;
	char	**tab;

	if (!s)
		return (NULL);
	total_length = count_words(s);
	tab = malloc(sizeof(char *) * (total_length + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < total_length)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!malloc_tab(tab, s, i))
			return (NULL);
		while (*s && !ft_isspace(*s))
			s++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
