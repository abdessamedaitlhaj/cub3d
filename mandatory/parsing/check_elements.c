/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:52:27 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:21:35 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_color_format(char *format, t_map_data *map, char type)
{
	map->comp2 = ft_split2(format, ',', &map->collected_data);
	if (count_strings(map->comp2) != 3)
		error("Color format is invalid\n", map->fd, map);
	if (type == 'F')
	{
		map->floor = ft_malloc(sizeof(t_color_data), &map->collected_data);
		map->floor->red = ft_atoi(map->comp2[0], map);
		map->floor->green = ft_atoi(map->comp2[1], map);
		map->floor->blue = ft_atoi(map->comp2[2], map);
	}
	if (type == 'C')
	{
		map->ceiling = ft_malloc(sizeof(t_color_data), &map->collected_data);
		map->ceiling->red = ft_atoi(map->comp2[0], map);
		map->ceiling->green = ft_atoi(map->comp2[1], map);
		map->ceiling->blue = ft_atoi(map->comp2[2], map);
	}
}

int	check_colors(t_map_data *map)
{
	if (!ft_isdigit(map->comp1[0][0]) && ft_strlen(map->comp1[0]) == 1)
	{
		if (map->comp1[0][0] != 'F' && map->comp1[0][0] != 'C')
			error("Color character is invalid\n", map->fd, map);
		if (map->comp1[0][0] == 'F')
			check_color_format(map->comp1[1], map, 'F');
		if (map->comp1[0][0] == 'C')
			check_color_format(map->comp1[1], map, 'C');
		map->elements++;
		if (map->elements > 6)
			error("Too many elements\n", map->fd, map);
		return (0);
	}
	return (1);
}

int	check_textures(t_map_data *map)
{
	if (!ft_isdigit(map->comp1[0][0]) && ft_strlen(map->comp1[0]) == 2)
	{
		if (ft_strncmp(map->comp1[0], "NO", 2) && \
		ft_strncmp(map->comp1[0], "SO", 2) && \
		ft_strncmp(map->comp1[0], "WE", 2) && \
		ft_strncmp(map->comp1[0], "EA", 2))
			error("Texture symboles are invalid\n", map->fd, map);
		if (ft_strncmp(map->comp1[0], "NO", 2) == 0)
			store_no_so(map->comp1[0], map->comp1[1], map);
		if (ft_strncmp(map->comp1[0], "SO", 2) == 0)
			store_no_so(map->comp1[0], map->comp1[1], map);
		if (ft_strncmp(map->comp1[0], "WE", 2) == 0)
			store_we_ea(map->comp1[0], map->comp1[1], map);
		if (ft_strncmp(map->comp1[0], "EA", 2) == 0)
			store_we_ea(map->comp1[0], map->comp1[1], map);
		map->elements++;
		if (map->elements > 6)
			error("Too many elements\n", map->fd, map);
		return (0);
	}
	return (1);
}

int	element_type(char *line, t_map_data *map)
{
	map->comp1 = ft_split(line, &map->collected_data);
	if (!map->comp1)
		error("Memory allocation failed\n", map->fd, map);
	if (!ft_isdigit(map->comp1[0][0]) && count_strings(map->comp1) != 2)
	{
		if (map->elements == 6)
			error("Not a map\n", map->fd, map);
		error("Color or texture path format is invalid\n", map->fd, map);
	}
	if (!check_colors(map))
		return (0);
	else if (!check_textures(map))
		return (0);
	return (1);
}
