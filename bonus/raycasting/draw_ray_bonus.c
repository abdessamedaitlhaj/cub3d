/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:37:15 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/23 18:16:29 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_vertical(t_vintersection *inter, int x, int y, double angle)
{
	inter->angle = normal_angle(angle);
	inter->facing_right = inter->angle < 0.5 * PI || inter->angle > 1.5 * PI;
	inter->facing_left = !inter->facing_right;
	inter->facing_down = inter->angle > 0 && inter->angle < PI;
	inter->facing_up = !inter->facing_down;
	inter->x_intercept = floor(x / GRID_SIZE) * GRID_SIZE;
	if (inter->facing_right)
		inter->x_intercept += GRID_SIZE;
	inter->y_intercept = y + (inter->x_intercept - x) * tan(inter->angle);
	inter->x_step = GRID_SIZE;
	if (inter->facing_left)
		inter->x_step *= -1;
	inter->y_step = GRID_SIZE * tan(inter->angle);
	if (inter->facing_up && inter->y_step > 0)
		inter->y_step *= -1;
	if (inter->facing_down && inter->y_step < 0)
		inter->y_step *= -1;
	inter->next_vertical_x = inter->x_intercept;
	inter->next_vertical_y = inter->y_intercept;
	inter->wall_hit_x = 0;
	inter->wall_hit_y = 0;
}

double	vertical_intersection(t_map_data *map, int x, int y, double angle)
{
	t_vintersection	inter;

	init_vertical(&inter, x, y, angle);
	while (inter.next_vertical_x >= 0 && inter.next_vertical_y >= 0)
	{
		inter.x_to_check = inter.next_vertical_x;
		if (inter.facing_left)
			inter.x_to_check -= 1;
		inter.y_to_check = inter.next_vertical_y;
		inter.check_x = (int)floor(inter.x_to_check / GRID_SIZE);
		inter.check_y = (int)floor(inter.y_to_check / GRID_SIZE);
		if (check_valid_vertical(&inter, map))
			break ;
		if (map->map[inter.check_y][inter.check_x] == '1')
			return (wall_hit_vertical(&inter, map, x, y));
		else
		{
			inter.next_vertical_x += inter.x_step;
			inter.next_vertical_y += inter.y_step;
		}
	}
	map->wall_hit_x_v = map->max_width * GRID_SIZE;
	map->wall_hit_y_v = map->max_width * GRID_SIZE;
	return (GRID_SIZE * map->max_width);
}

void	init_horizontal(t_intersection *inter, int x, int y, double angle)
{
	inter->angle = normal_angle(angle);
	inter->facing_down = inter->angle > 0 && inter->angle < PI;
	inter->facing_up = !inter->facing_down;
	inter->facing_right = inter->angle < 0.5 * PI || inter->angle > 1.5 * PI;
	inter->facing_left = !inter->facing_right;
	inter->y_intercept = floor(y / GRID_SIZE) * GRID_SIZE;
	if (inter->facing_down)
		inter->y_intercept += GRID_SIZE;
	inter->x_intercept = x + (inter->y_intercept - y) / tan(inter->angle);
	inter->y_step = GRID_SIZE;
	if (inter->facing_up)
		inter->y_step *= -1;
	inter->x_step = GRID_SIZE / tan(inter->angle);
	if (inter->facing_left && inter->x_step > 0)
		inter->x_step *= -1;
	if (inter->facing_right && inter->x_step < 0)
		inter->x_step *= -1;
	inter->next_horizontal_x = inter->x_intercept;
	inter->next_horizontal_y = inter->y_intercept;
	inter->wall_hit_x = 0;
	inter->wall_hit_y = 0;
	inter->wall_content = 0;
}

double	horizontal_intersection(t_map_data *map, int x, int y, double angle)
{
	t_intersection	inter;

	init_horizontal(&inter, x, y, angle);
	while (inter.next_horizontal_x >= 0 && inter.next_horizontal_y >= 0)
	{
		inter.x_to_check = inter.next_horizontal_x;
		inter.y_to_check = inter.next_horizontal_y;
		if (inter.facing_up)
			inter.y_to_check = inter.next_horizontal_y - 1;
		inter.check_x = (int)floor(inter.x_to_check / GRID_SIZE);
		inter.check_y = (int)floor(inter.y_to_check / GRID_SIZE);
		if (check_valid(&inter, map))
			break ;
		if (map->map[inter.check_y][inter.check_x] == '1')
			return (wall_hit_horizontal(&inter, map, x, y));
		else
		{
			inter.next_horizontal_x += inter.x_step;
			inter.next_horizontal_y += inter.y_step;
		}
	}
	map->wall_hit_x_h = map->max_width * GRID_SIZE;
	map->wall_hit_y_h = map->max_width * GRID_SIZE;
	return (GRID_SIZE * map->max_width);
}

void	min_intersection(t_map_data *map, int x, int y, double angle)
{
	double	distance;

	map->vertical = 0;
	map->player->distance = horizontal_intersection(map, x, y, angle);
	map->wall_hit_x = map->wall_hit_x_h;
	map->wall_hit_y = map->wall_hit_y_h;
	distance = vertical_intersection(map, x, y, angle);
	if (map->player->distance > distance)
	{
		map->wall_hit_x = map->wall_hit_x_v;
		map->wall_hit_y = map->wall_hit_y_v;
		map->player->distance = distance;
		map->vertical = 1;
	}
}
