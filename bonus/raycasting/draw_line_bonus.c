/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:47:00 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 19:47:01 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/cub3d_bonus.h"

void	draw_line(t_map_data *map, int x, double wall_height, int *image_px)
{
	t_draw_data	data;
	int			i;
	int			pixel;

	data.start = fmax(0, HEIGHT / 2 - wall_height / 2);
	data.end = fmin(HEIGHT, HEIGHT / 2 + wall_height / 2);
	data.step = 1.0 * map->choosen_texture->height / wall_height;
	data.tex_pos = (data.start - HEIGHT / 2 + wall_height / 2) * data.step;
	i = data.start;
	while (i < data.end)
	{
		data.tex_y = (int)data.tex_pos;
		data.tex_pos += data.step;
		pixel = data.tex_y * map->choosen_texture->width
			+ (int)(map->player->x_cord);
		if (pixel >= 0 && pixel < map->choosen_texture->width
			* map->choosen_texture->height)
		{
			data.color_b = image_px[pixel];
			data.color_b = ft_adjust_color(data.color_b);
			mlx_put_pixel(map->img, x, i, data.color_b);
		}
		i++;
	}
}

void	get_xcord(t_map_data *map, double x, double y, mlx_texture_t *texture)
{
	if (map->vertical == 1)
	{
		map->player->x_cord = fmodf(map->wall_hit_y_v, GRID_SIZE)
			/ GRID_SIZE * texture->width;
	}
	else
	{
		map->player->x_cord = fmodf(map->wall_hit_x_h, GRID_SIZE)
			/ GRID_SIZE * texture->width;
	}
}

double	normal_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

mlx_texture_t	*choose_texture(t_map_data *map, double angle)
{
	mlx_texture_t	*texture;

	angle = normal_angle(angle);
	if (map->vertical)
	{
		if (angle > 1.5 * PI || angle < 0.5 * PI)
			texture = map->texture->texture_e;
		else
			texture = map->texture->texture_w;
	}
	else
	{
		if (angle > 0 && angle < PI)
			texture = map->texture->texture_n;
		else
			texture = map->texture->texture_s;
	}
	return (texture);
}
