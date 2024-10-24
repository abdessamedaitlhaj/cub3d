/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:03:04 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/23 17:57:54 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_move_player(t_map_data *map, int direction)
{
	double	old_x;
	double	old_y;

	if (direction == UP)
		move_up(map, old_x, old_y);
	if (direction == DOWN)
		move_down(map, old_x, old_y);
	if (direction == RIGHT)
		move_right(map, old_x, old_y);
	if (direction == LEFT)
		move_left(map, old_x, old_y);
}

void	ft_rotate_player(t_map_data *map, mlx_key_data_t key)
{
	double	epsilon;

	epsilon = 0.000001;
	if (key.key == MLX_KEY_RIGHT)
	{
		map->player->player_angle += map->player->rotation_speed;
		if (map->player->player_angle > 2 * PI)
			map->player->player_angle = 0;
		ft_move_player(map, 0);
	}
	if (key.key == MLX_KEY_LEFT)
	{
		map->player->player_angle -= map->player->rotation_speed;
		if (map->player->player_angle <= 0)
			map->player->player_angle = 2 * PI - epsilon;
		ft_move_player(map, 0);
	}
}

void	ft_move(mlx_key_data_t key, void *param)
{
	t_map_data	*map;

	map = (t_map_data *)param;
	if (key.key == MLX_KEY_ESCAPE)
	{
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

void	map_init(t_map_data *map)
{
	int	i;
	int	j;

	i = -1;
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	while (++i < map->map_height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N')
			{
				map->player->po_x = j * GRID_SIZE + GRID_SIZE / 2;
				map->player->po_y = i * GRID_SIZE + GRID_SIZE / 2;
				map->player->player_speed = SPEED * (GRID_SIZE / 64);
				map->player->rotation_speed = ROTATION_SPEED;
				map->player->player_angle = 90 * (PI / 180);
			}
			j++;
		}
	}
	mlx_key_hook(map->mlx, &ft_move, map);
	mlx_loop_hook(map->mlx, &draw_ray, map);
	mlx_loop(map->mlx);
}
