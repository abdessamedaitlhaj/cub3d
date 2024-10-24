/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:53:14 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 18:53:52 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static int	malloc_tab(t_split_args *args, t_node **collected_data)
{
	int		k;
	int		j;

	k = 0;
	while (args->s[k] && args->s[k] != args->c)
		k++;
	args->tab[args->i] = ft_malloc(sizeof(char) * (k + 1), collected_data);
	j = 0;
	while (j < k)
	{
		args->tab[args->i][j] = args->s[j];
		j++;
	}
	args->tab[args->i][j] = '\0';
	return (1);
}

char	**ft_split2(char const *s, char c, t_node **collected_data)
{
	int				total_length;
	t_split_args	args;

	args = (t_split_args){NULL, s, c, 0};
	if (!args.s)
		return (NULL);
	total_length = count_words(args.s, args.c);
	args.tab = ft_malloc(sizeof(char *) * (total_length + 1), collected_data);
	args.i = 0;
	while (args.i < total_length)
	{
		while (*args.s && *args.s == args.c)
			args.s++;
		malloc_tab(&args, collected_data);
		while (*args.s && *args.s != args.c)
			args.s++;
		args.i++;
	}
	args.tab[args.i] = NULL;
	return (args.tab);
}
