/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:03:04 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/23 03:04:21 by aait-lha         ###   ########.fr       */
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



void cursor_func(double xpos, double ypos, void *param)
{
    t_map_data *map;
    static double last_x = -1;
    double rotation_speed;
    double x_offset;
    double epsilon;
    
    (void)ypos;  // We don't need vertical mouse movement for this implementation
    map = (t_map_data *)param;
    epsilon = 0.000001;
    rotation_speed = 0.002;  // Adjust this value to control rotation sensitivity
    
    // Initialize last_x on first call
    if (last_x == -1)
    {
        last_x = xpos;
        return;
    }
    
    // Calculate the offset from last position
    x_offset = xpos - last_x;
    
    // Update player angle based on mouse movement
    map->player->player_angle += x_offset * rotation_speed;
    
    // Normalize the angle between 0 and 2*PI
    if (map->player->player_angle >= 2 * PI)
        map->player->player_angle = 0 + epsilon;
    if (map->player->player_angle <= 0)
        map->player->player_angle = 2 * PI - epsilon;
	printf("angle: %f\n", map->player->player_angle);
    
    // Store current position for next frame
    last_x = xpos;
    
    // Center the cursor to prevent hitting screen edges
    if (xpos <= 10 || xpos >= WIDTH - 10)
    {
        mlx_set_mouse_pos(map->mlx, WIDTH / 2, HEIGHT / 2);
        last_x = WIDTH / 2;
    }
}

void	map_init(t_map_data *map)
{
	int	i;
	int	j;

	i = 0;
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	while (i < map->map_height)
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
		i++;
	}
	mlx_key_hook(map->mlx, &ft_move, map);
	mlx_cursor_hook(map->mlx, &cursor_func, map);
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(map->mlx, &draw_ray, map);
	mlx_loop(map->mlx);
}
