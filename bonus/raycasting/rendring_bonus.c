/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradais <paradais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:51:49 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/23 02:12:36 by paradais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

double	wall_projection(t_map_data *map, int x, int y)
{
	double	distance_projection;
	double	wall_height;

	distance_projection = (WIDTH / 2) / tan((FOV * (PI / 180)) / 2);
	wall_height = (GRID_SIZE / map->player->distance) * distance_projection;
	return (wall_height);
}
