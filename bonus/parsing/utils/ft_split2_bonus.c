/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradais <paradais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:53:14 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 02:10:04 by paradais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	count_words(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	if (!*s)
		return (0);
	while (*s && *s != c)
		s++;
	return (1 + count_words(s, c));
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

static int	malloc_tab(char **tab, char const *s, char c, int i)
{
	int		k;
	int		j;

	k = 0;
	while (s[k] && s[k] != c)
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

char	**ft_split2(char const *s, char c)
{
	int		total_length;
	int		i;
	char	**tab;

	if (!s)
		return (NULL);
	total_length = count_words(s, c);
	tab = malloc(sizeof(char *) * (total_length + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < total_length)
	{
		while (*s && *s == c)
			s++;
		if (!malloc_tab(tab, s, c, i))
			return (NULL);
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
