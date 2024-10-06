#include "../include/cub3d.h"

// int ft_strlen(char *s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

double normal_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return angle;
}

double vertical_intersection(t_map_data *map, int x, int y, double angle, int color)
{
	angle = normal_angle(angle);
	int facing_right = angle < 0.5 * PI || angle > 1.5 * PI;
	int facing_left = !facing_right;
	int facing_down = angle > 0 && angle < PI;
	int facing_up = !facing_down;

	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	int wall_hit_x = 0;
	int wall_hit_y = 0;
	int Wall_content = 0;

	x_intercept = floor(x / GRID_SIZE) * GRID_SIZE;
	x_intercept += facing_right ? GRID_SIZE : 0;

	y_intercept = y + (x_intercept - x) * tan(angle);
	x_step = GRID_SIZE;
	x_step *= facing_left ? -1 : 1;

	y_step = GRID_SIZE * tan(angle);
	y_step *= (facing_up && y_step > 0) ? -1 : 1;
	y_step *= (facing_down && y_step < 0) ? -1 : 1;

	float next_vertical_x = x_intercept;
	float next_vertical_y = y_intercept;

	while (next_vertical_x >= 0 && next_vertical_x <= WIDTH && next_vertical_y >= 0 && next_vertical_y <= HEIGHT)
	{
		float x_to_check = next_vertical_x + (facing_left ? -1 : 0);
		float y_to_check = next_vertical_y;
		int check_x = (int)floor(x_to_check / GRID_SIZE);
		int check_y = (int)floor(y_to_check / GRID_SIZE);
		if (check_x < 0 || check_y < 0 || check_x >= map->max_width || check_y >= map->map_height || check_x > ft_strlen(map->map[check_y]))
			break;
		if (map->map[check_y][check_x] == '1')
		{
			wall_hit_x = next_vertical_x;
			wall_hit_y = next_vertical_y;
			Wall_content = map->map[(int)(y_to_check / GRID_SIZE)][(int)(x_to_check / GRID_SIZE)];
			return (sqrt((wall_hit_x - x) * (wall_hit_x - x) + (wall_hit_y - y) * (wall_hit_y - y)));
		}
		else
		{
			next_vertical_x += x_step;
			next_vertical_y += y_step;
		}
	}
	return (GRID_SIZE * map->max_width);
}

double horizontal_intersection(t_map_data *map, int x, int y, double angle, int color)
{
	//print angle
	// printf("angle: %f\n", map->player->player_angle);
	angle = normal_angle(angle);
	int facing_down = angle > 0 && angle < PI;
	int facing_up = !facing_down;
	int facing_right = angle < 0.5 * PI || angle > 1.5 * PI;
	int facing_left = !facing_right;

	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	int wall_hit_x = 0;
	int wall_hit_y = 0;
	int Wall_content = 0;

	y_intercept = floor(y / GRID_SIZE) * GRID_SIZE;
	y_intercept += facing_down ? GRID_SIZE : 0;

	x_intercept = x + (y_intercept - y) / tan(angle);
	y_step = GRID_SIZE;
	y_step *= facing_up ? -1 : 1;

	x_step = GRID_SIZE / tan(angle);
	x_step *= (facing_left && x_step > 0) ? -1 : 1;
	x_step *= (facing_right && x_step < 0) ? -1 : 1;

	float next_horizontal_x = x_intercept;
	float next_horizontal_y = y_intercept;

	while (next_horizontal_x >= 0 && next_horizontal_x <= WIDTH && next_horizontal_y >= 0 && next_horizontal_y <= HEIGHT)
	{
		float x_to_check = next_horizontal_x;
		float y_to_check = next_horizontal_y + (facing_up ? -1 : 0);
		int check_x = (int)floor(x_to_check / GRID_SIZE);
		int check_y = (int)floor(y_to_check / GRID_SIZE);
		if (check_x < 0 || check_y < 0 || check_x >= map->max_width || check_y >= map->map_height || check_x > ft_strlen(map->map[check_y]))
			break;
		if (map->map[check_y][check_x] == '1')
		{
			wall_hit_x = next_horizontal_x;
			wall_hit_y = next_horizontal_y;
			Wall_content = map->map[(int)(y_to_check / GRID_SIZE)][(int)(x_to_check / GRID_SIZE)];
			return (sqrt((wall_hit_x - x) * (wall_hit_x - x) + (wall_hit_y - y) * (wall_hit_y - y)));
		}
		else
		{
			next_horizontal_x += x_step;
			next_horizontal_y += y_step;
		}
	}
	// return (GRID_SIZE * map->max_width);

}

void min_intersection (t_map_data *map, int x, int y, double angle, int color)
{
	// color always red
	double distance;
	map->player->distance = horizontal_intersection(map, x, y, angle, color);
	printf("horizontal_distance: %f\n", map->player->distance);
	distance = vertical_intersection(map, x, y, angle, color);

	if (map->player->distance > distance)
		map->player->distance = distance;
}
void draw_ray(t_map_data *map, int x, int y, int color)
{
	printf("ray_distance: %f\n", map->player->ray_distance);
	int i;
	i = 0;
	double angle =  map->player->player_angle - ((FOV / 2) * (PI / 180));
	angle = angle < 0 ? 2 * PI + angle : angle;
	angle = angle > 2 * PI ? angle - 2 * PI : angle;
	while (i < WIDTH)
	{
		min_intersection(map, x, y, angle, color);
		// map->player->distance = 60;
		put_line(map->img, x, y, x + map->player->distance * cos(angle), y + map->player->distance * sin(angle));
		angle += map->player->ray_distance;
		i++;
	}
}

