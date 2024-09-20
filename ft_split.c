/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:12:20 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/19 19:12:47 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**ft_split(char const *s, char c)
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