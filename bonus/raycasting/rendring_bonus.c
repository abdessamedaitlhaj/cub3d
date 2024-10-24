/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:51:49 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/23 18:17:22 by ael-hara         ###   ########.fr       */
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


void	ft_move(mlx_key_data_t key, void *param)
{
	t_map_data	*map;

	map = (t_map_data *)param;
	if (key.key == MLX_KEY_ESCAPE)
	{
		free_data(map);
		exit(0);
	}
	if (key.key == MLX_KEY_W)
		ft_move_player(map, DOWN);
	if (key.key == MLX_KEY_S)
		ft_move_player(map, UP);
	if (key.key == MLX_KEY_A)
		ft_move_player(map, RIGHT);
	if (key.key == MLX_KEY_D)
		ft_move_player(map, LEFT);
	if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_LEFT)
		ft_rotate_player(map, key);
}

void	cursor_func(double xpos, double ypos, void *param)
{
	t_map_data		*map;
	static double	last_x = -1;
	double			x_offset;

	(void)ypos;
	map = (t_map_data *)param;
	if (last_x == -1)
	{
		last_x = xpos;
		return ;
	}
	x_offset = xpos - last_x;
	map->player->player_angle += x_offset * MOUSE_SPEED;
	if (map->player->player_angle >= 2 * PI)
		map->player->player_angle = 0 + EPSILON;
	if (map->player->player_angle <= 0)
		map->player->player_angle = 2 * PI - EPSILON;
	last_x = xpos;
	if (xpos <= 10 || xpos >= WIDTH - 10)
	{
		mlx_set_mouse_pos(map->mlx, WIDTH / 2, HEIGHT / 2);
		last_x = WIDTH / 2;
	}
}
