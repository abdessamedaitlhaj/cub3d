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

void put_line(mlx_image_t *img, int x0, int y0, int x1, int y1)
{

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        // printf("x0 = %d   ------ y0 = %d\n", x0, y0);
        mlx_put_pixel(img, x0, y0, RED);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }

}

// void    draw_line1(int x0, int y0, int x1, int y1, t_data *data)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = x0 < x1 ? 1 : -1;
//     int sy = y0 < y1 ? 1 : -1;
//     int err = dx - dy;

//     while (1)
//     {
//         // printf("x0 = %d   ------ y0 = %d\n", x0, y0);
//         mlx_put_pixel(data->img, x0, y0, RED);
//         if (x0 == x1 && y0 == y1)
//             break;
//         int e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }
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
	// drw line to show the direction of the player using the angle of the player
	// draw_ray(map, x, y, color);
	int distance = 100;
	put_line(map->img, x, y, x + distance * cos(map->player->player_angle), y + distance * sin(map->player->player_angle));
	double angle =  (FOV / 2) * (PI / 180);
	put_line(map->img, x, y, x + 60 * cos(map->player->player_angle + angle), y + 60 * sin(map->player->player_angle + angle));
	put_line(map->img, x, y, x + 60 * cos(map->player->player_angle - angle), y + 60 * sin(map->player->player_angle - angle));

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
	

	double old_x;
	double old_y;
	if (direction == UP)
	{
		old_x = map->player->po_x;
		old_y = map->player->po_y;
		map->player->po_y = old_y - map->player->player_speed * sin(map->player->player_angle);
		map->player->po_x = old_x - map->player->player_speed * cos(map->player->player_angle);
		if (ft_border(map))
		{
			map->player->po_y = old_y;
			map->player->po_x = old_x;
		}
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == DOWN)
	{
		old_x = map->player->po_x;
		old_y = map->player->po_y;
		map->player->po_y = old_y + map->player->player_speed * sin(map->player->player_angle);
		map->player->po_x = old_x + map->player->player_speed * cos(map->player->player_angle);
		if (ft_border(map))
		{
			map->player->po_y = old_y;
			map->player->po_x = old_x;
		}
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == RIGHT)
	{
    old_x = map->player->po_x;
    old_y = map->player->po_y;
    double temp_angle = map->player->player_angle - M_PI / 2; // Subtract 90 degrees from the current angle
    map->player->po_y = old_y + map->player->player_speed * sin(temp_angle);
    map->player->po_x = old_x + map->player->player_speed * cos(temp_angle);
    if (ft_border(map))
    {
        map->player->po_y = old_y;
        map->player->po_x = old_x;
    }
    square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	else if (direction == LEFT)
	{
    old_x = map->player->po_x;
    old_y = map->player->po_y;
    double temp_angle = map->player->player_angle + M_PI / 2; // Add 90 degrees to the current angle
    map->player->po_y = old_y + map->player->player_speed * sin(temp_angle);
    map->player->po_x = old_x + map->player->player_speed * cos(temp_angle);
    if (ft_border(map))
    {
        map->player->po_y = old_y;
        map->player->po_x = old_x;
    }
    square_red(map, map->player->po_x, map->player->po_y, RED);
	}
	if (direction == 0)
	{
		square_red(map, map->player->po_x, map->player->po_y, RED);
	}
}

void ft_move(mlx_key_data_t key, void* param)
{
	t_map_data *map = (t_map_data *)param;
	if (key.key == MLX_KEY_W)
		ft_move_player(map, DOWN);
	else if (key.key == MLX_KEY_S)
		ft_move_player(map, UP);
	else if (key.key == MLX_KEY_RIGHT)
		ft_move_player(map, RIGHT);
	else if (key.key == MLX_KEY_LEFT)
		ft_move_player(map, LEFT);
	else if (key.key == MLX_KEY_D)
	{
		map->player->player_angle += map->player->rotation_speed;
		if (map->player->player_angle > 2 * PI)
			map->player->player_angle = 0;
		ft_move_player(map, 0);
	}
	else if (key.key == MLX_KEY_A)
	{
		map->player->player_angle -= map->player->rotation_speed;
		if (map->player->player_angle < 0)
			map->player->player_angle = 2 * PI;
		ft_move_player(map, 0);
	}
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
				map->player->player_speed = SPEED;
				map->player->rotation_speed = ROTATION_SPEED;
				map->player->player_angle = 90 * (PI / 180);
				square_red(map, map->player->po_x, map->player->po_y, RED);

			}
			j++;
		}
		i++;
	}
	mlx_key_hook(map->mlx, &ft_move, map);
}