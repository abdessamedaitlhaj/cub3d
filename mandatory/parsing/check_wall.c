/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:11:12 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 20:11:27 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	last_char_check(t_map_data *map, char *line, size_t i)
{
	if (!line[i])
	{
		i--;
		while (ft_isspace(line[i]))
			i--;
		if (line[i] != '1')
			error("Map is not surrounded by walls\n", map->fd, map);
	}
}

void	check_wall(char *line, t_map_data *map)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			error("Map is not surrounded by walls\n", map->fd, map);
		i++;
	}
}
