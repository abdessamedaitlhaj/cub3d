/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:37:03 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/25 21:37:10 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_texture(char *type, char *path, t_map_data *map)
{
	if (ft_strncmp(type, "NO", 2) == 0)
		map->texture->north = ft_strdup(path);
	if (ft_strncmp(type, "SO", 2) == 0)
		map->texture->south = ft_strdup(path);
	if (ft_strncmp(type, "WE", 2) == 0)
		map->texture->weast = ft_strdup(path);
	if (ft_strncmp(type, "EA", 2) == 0)
		map->texture->east = ft_strdup(path);
}

