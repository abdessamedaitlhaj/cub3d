#include "../include/cub3d.h"
void square(t_map_data *map, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < map->element_height)
	{
		j = 0;
		while (j < map->element_width)
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

	i = 0;
	while (i < map->element_height)
	{
		j = 0;
		while (j < map->element_width)
		{
			if(i > map->element_height / 2 && i < map->element_height / 2 + 10 && j > map->element_width / 2  - 5 && j < map->element_width / 2 + 5)
				mlx_put_pixel(map->img, x + j, y + i, color);
			else
				mlx_put_pixel(map->img, x + j, y + i, WHITE);
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
				square(map, j * map->element_width, i * map->element_height, BLACK);
			if (map->map[i][j] == '0' || map->map[i][j] == 'N')
				square(map, j * map->element_width, i * map->element_height, WHITE);
			j++;
		}
		i++;
	}
	if (direction == 1)
	{
		map->player->po_y += map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == 2)
	{
		map->player->po_y -= map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == 3)
	{
		map->player->po_x += map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == 4)
	{
		map->player->po_x -= map->player->player_speed;
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
}

void ft_move(mlx_key_data_t key, void* param)
{
	t_map_data *map = (t_map_data *)param;
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		ft_move_player(map, 1);
		// puts("UP ");
	else if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		ft_move_player(map, 2);
		// puts("DOWN");
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		ft_move_player(map, 3);
		// puts("RIGHT");
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		ft_move_player(map, 4);
		// puts("LEFT");
}

void map_init(t_map_data *map)
{
	int i = 0;
	int j;


	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	map->element_height = min(map->element_width, map->element_height);
	map->element_width = map->element_height;
	while (i < map->map_height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				square(map, j * map->element_width, i * map->element_height, BLACK);
			else if (map->map[i][j] == '0')
				square(map, j * map->element_width, i * map->element_height, WHITE);
			else if (map->map[i][j] == 'N')
			{
				map->player->po_x = j * map->element_width ;
				map->player->po_y = i * map->element_height;
				square_red(map, j * map->element_width, i * map->element_height, RED);
			}
			j++;
		}
		i++;
	}
	mlx_key_hook(map->mlx, &ft_move, map);
}