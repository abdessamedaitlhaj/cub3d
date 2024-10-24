/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:12:20 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:14:56 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static int	malloc_tab(t_split_args *args, t_node **collected_data)
{
	int		k;
	int		j;

	k = 0;
	while (args->s[k] && !ft_isspace(args->s[k]))
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

char	**ft_split(char const *s, t_node **collected_data)
{
	int				total_length;
	t_split_args	args;

	args = (t_split_args){NULL, s, ' ', 0};
	if (!args.s)
		return (NULL);
	total_length = count_words(args.s);
	args.tab = ft_malloc(sizeof(char *) * (total_length + 1), collected_data);
	args.i = 0;
	while (args.i < total_length)
	{
		while (*args.s && ft_isspace(*args.s))
			args.s++;
		malloc_tab(&args, collected_data);
		while (*args.s && !ft_isspace(*args.s))
			args.s++;
		args.i++;
	}
	args.tab[args.i] = NULL;
	return (args.tab);
}
