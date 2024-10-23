/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:43 by ael-hara          #+#    #+#             */
/*   Updated: 2024/10/19 20:58:27 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_adjust_color(int color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	a = (color >> 24) & 0xFF;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return (((int)b << 24) | ((int)g << 16) \
		| ((int)r << 8) | (int)a);
}

double	correct_distance(double distance, double angle, double player_angle)
{
	double	correct_distance;

	correct_distance = distance * cos(angle - player_angle);
	return (correct_distance);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	background(t_map_data *map)
{
	int	i;
	int	j;
	int	ceilings;
	int	floors;

	i = 0;
	ceilings = get_rgba(map->ceiling->red, map->ceiling->green,
			map->ceiling->blue, 255);
	floors = get_rgba(map->floor->red, map->floor->green,
			map->floor->blue, 255);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(map->img, i, j, ceilings);
			else
				mlx_put_pixel(map->img, i, j, floors);
			j++;
		}
		i++;
	}
}
