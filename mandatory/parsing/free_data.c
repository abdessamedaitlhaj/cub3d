/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:45:35 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/22 21:10:37 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_comp(t_map_data *map)
{
	int	i;

	if (map->comp1)
	{
		i = 0;
		while (map->comp1[i])
		{
			free(map->comp1[i]);
			i++;
		}
		free(map->comp1);
	}
	if (map->comp2)
	{
		i = 0;
		while (map->comp2[i])
		{
			free(map->comp2[i]);
			i++;
		}
		free(map->comp2);
	}
}

void	free_textures(t_map_data *map)
{
	if (map->texture)
	{
		if (map->texture->texture_n)
			free(map->texture->texture_n);
		if (map->texture->texture_s)
			free(map->texture->texture_s);
		if (map->texture->texture_w)
			free(map->texture->texture_w);
		if (map->texture->texture_e)
			free(map->texture->texture_e);
		free(map->texture);
	}
}

void	free_data(t_map_data *map)
{
	int	i;

	i = 0;
	while (map->map && i < map->map_height)
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	if (map->map)
		free(map->map);
	if (map->player)
		free(map->player);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	free_textures(map);
	free_comp(map);
}
