/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:37:03 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:14:40 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	store_we_ea(char *type, char *path, t_map_data *map)
{
	if (ft_strncmp(type, "WE", 2) == 0)
	{
		map->texture->texture_w = mlx_load_png(ft_strdup(path, \
		&map->collected_data));
		if (!map->texture->texture_w)
			error("Texture not found\n", -1, map);
	}
	else if (ft_strncmp(type, "EA", 2) == 0)
	{
		map->texture->texture_e = mlx_load_png(ft_strdup(path, \
		&map->collected_data));
		if (!map->texture->texture_e)
			error("Texture not found\n", -1, map);
	}
}

void	store_no_so(char *type, char *path, t_map_data *map)
{
	if (ft_strncmp(type, "NO", 2) == 0)
	{
		map->texture->texture_n = mlx_load_png(ft_strdup(path, \
		&map->collected_data));
		if (!map->texture->texture_n)
			error("Texture not found\n", -1, map);
	}
	else if (ft_strncmp(type, "SO", 2) == 0)
	{
		map->texture->texture_s = mlx_load_png(ft_strdup(path, \
		&map->collected_data));
		if (!map->texture->texture_s)
			error("Texture not found\n", -1, map);
	}
	store_we_ea(type, path, map);
}
