/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:51:49 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/19 16:00:15 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	wall_projection(t_map_data *map, int x, int y)
{
	double	distance_projection;
	double	wall_height;

	distance_projection = (WIDTH / 2) / tan((FOV * (PI / 180)) / 2);
	wall_height = (GRID_SIZE / map->player->distance) * distance_projection;
	return (wall_height);
}
