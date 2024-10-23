/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:52:36 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/21 11:12:39 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_valid_vertical(t_vintersection *inter, t_map_data *map)
{
	return (inter->check_x < 0 || inter->check_y < 0
		|| inter->check_x >= map->max_width
		|| inter->check_y >= map->map_height
		|| inter->check_x > ft_strlen(map->map[inter->check_y]));
}

double	wall_hit_vertical(t_vintersection *inter, t_map_data *map, int x, int y)
{
	inter->wall_hit_x = inter->next_vertical_x;
	inter->wall_hit_y = inter->next_vertical_y;
	inter->wall_content = map->map[(int)(inter->y_to_check / GRID_SIZE)] \
	[(int)(inter->x_to_check / GRID_SIZE)];
	map->wall_hit_x_v = inter->wall_hit_x;
	map->wall_hit_y_v = inter->wall_hit_y;
	return (sqrt((inter->wall_hit_x - x) * (inter->wall_hit_x - x)
			+ (inter->wall_hit_y - y) * (inter->wall_hit_y - y)));
}

double	wall_hit_horizontal(t_intersection *inter, t_map_data *map
					, int x, int y)
{
	inter->wall_hit_x = inter->next_horizontal_x;
	inter->wall_hit_y = inter->next_horizontal_y;
	inter->wall_content = map->map[(int)(inter->y_to_check / GRID_SIZE)] \
	[(int)(inter->x_to_check / GRID_SIZE)];
	map->wall_hit_x_h = inter->wall_hit_x;
	map->wall_hit_y_h = inter->wall_hit_y;
	return (sqrt((inter->wall_hit_x - x) * (inter->wall_hit_x - x)
			+ (inter->wall_hit_y - y) * (inter->wall_hit_y - y)));
}

int	check_valid(t_intersection *inter, t_map_data *map)
{
	return (inter->check_x < 0 || inter->check_y < 0
		|| inter->check_x >= map->max_width
		|| inter->check_y >= map->map_height
		|| inter->check_x > ft_strlen(map->map[inter->check_y]));
}
