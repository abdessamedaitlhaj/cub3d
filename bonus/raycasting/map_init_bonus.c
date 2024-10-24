/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:03:04 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/23 18:57:31 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	init_player(t_map_data *map, int i, int j)
{
	map->player->po_x = j * GRID_SIZE + GRID_SIZE / 2;
	map->player->po_y = i * GRID_SIZE + GRID_SIZE / 2;
	map->player->player_speed = SPEED * (GRID_SIZE / 64);
	map->player->rotation_speed = ROTATION_SPEED;
	map->player->player_angle = 90 * (PI / 180);
}

void	load_and_hook(t_map_data *map)
{
	load_shot_sprites(map);
	load_reload_sprites(map);
	mlx_key_hook(map->mlx, &ft_move, map);
	mlx_cursor_hook(map->mlx, &cursor_func, map);
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(map->mlx, &draw_ray, map);
	mlx_loop_hook(map->mlx, &spirite, map);
}

void	map_init(t_map_data *map)
{
	int				i;
	int				j;
	mlx_texture_t	*texture;

	i = 0;
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	texture = mlx_load_png("bonus/sprites/idleing/1.png");
	map->img2 = mlx_texture_to_image(map->mlx, texture);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	mlx_image_to_window(map->mlx, map->img2, WIDTH / 2 - map->img2->width / 2,
		HEIGHT - map->img2->height);
	while (i < map->map_height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N')
				init_player(map, i, j);
			j++;
		}
		i++;
	}
	load_and_hook(map);
}
