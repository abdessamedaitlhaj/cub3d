#include "../include/cub3d.h"
void square(t_map_data *map, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			mlx_put_pixel(map->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
void square_red(t_map_data *map, int x, int y, int color)
{
	int i;
	int j;

	// your iin center of the square do 10 x 10

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(map->img, x -5 + j, y -5 + i, color);
			j++;
		}
		i++;
	}
}

int min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void ft_move_player(t_map_data *map, int direction)
{
	int i = 0;
	int j;
	while (i < map->map_height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				square(map, j * GRID_SIZE, i * GRID_SIZE, BLACK);
			if (map->map[i][j] == '0' || map->map[i][j] == 'N')
				square(map, j * GRID_SIZE, i * GRID_SIZE, WHITE);
			j++;
		}
		i++;
	}
	if (direction == 1)
	{
		map->player->po_y += map->player->player_speed;
		if (border(map, 0, PLAYER_SIZE / 2))
			map->player->po_y -= map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == 2)
	{
		map->player->po_y -= map->player->player_speed;
		if (border(map , 0, -PLAYER_SIZE / 2))
			map->player->po_y += map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == 3)
	{
		map->player->po_x += map->player->player_speed;
		if (border(map , PLAYER_SIZE / 2, 0))
			map->player->po_x -= map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == 4)
	{
		map->player->po_x -= map->player->player_speed;
		if (border(map , -PLAYER_SIZE / 2, 0))
			map->player->po_x += map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
}

void ft_move(mlx_key_data_t key, void* param)
{
	t_map_data *map = (t_map_data *)param;
	if (key.key == MLX_KEY_W)
		ft_move_player(map, 2);
		// puts("UP ");
	else if (key.key == MLX_KEY_S)
		ft_move_player(map, 1);
		// puts("DOWN");
	else if (key.key == MLX_KEY_RIGHT)
		ft_move_player(map, 3);
		// puts("RIGHT");
	else if (key.key == MLX_KEY_LEFT)
		ft_move_player(map, 4);
		// puts("LEFT");
}

void map_init(t_map_data *map)
{
	int i = 0;
	int j;


	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	while (i < map->map_height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				square(map, j * GRID_SIZE, i * GRID_SIZE, BLACK);
			if (map->map[i][j] == '0' || map->map[i][j] == 'N')
				square(map, j * GRID_SIZE, i * GRID_SIZE, WHITE);
			if (map->map[i][j] == 'N')
			{
				map->player->po_x = j * GRID_SIZE  + GRID_SIZE / 2;
				map->player->po_y = i * GRID_SIZE + GRID_SIZE / 2;
				square_red(map, map->player->po_x, map->player->po_y, RED);
			}
			j++;
		}
		i++;
	}
	mlx_key_hook(map->mlx, &ft_move, map);
}