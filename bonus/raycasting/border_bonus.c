/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:46:41 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 19:46:42 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/cub3d_bonus.h"

int	border(t_map_data *map, int border_x, int border_y)
{
	int	index_y;
	int	index_x;

	if (map != NULL && map->player != NULL)
	{
		index_y = (int)((map->player->po_y + border_y) / GRID_SIZE);
		index_x = (int)((map->player->po_x + border_x) / GRID_SIZE);
		if (index_y >= 0 && index_y < map->map_height && index_x >= 0
			&& index_x < map->max_width)
		{
			if (map->map[index_y][index_x] == '1')
			{
				return (1);
			}
		}
	}
	return (0);
}

int	ft_border(t_map_data *map)
{
	int	player_size;

	player_size = PLAYER_SIZE * (GRID_SIZE / 64);
	if (border(map, player_size / 2 + OFFSET, player_size / 2 + OFFSET)
		|| border(map, -player_size / 2 - OFFSET, player_size / 2 + OFFSET)
		|| border(map, player_size / 2 + OFFSET, -player_size / 2 - OFFSET)
		|| border(map, -player_size / 2 - OFFSET, -player_size / 2 - OFFSET))
		return (1);
	return (0);
}
