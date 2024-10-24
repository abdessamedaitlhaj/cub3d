/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:05:34 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:19:42 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*right_str(char *st_var, t_node **collected_data)
{
	char	*right_str;
	int		i;
	int		j;

	i = 0;
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (!st_var[i])
		return (st_var = NULL, NULL);
	right_str = ft_malloc(sizeof(char) * \
	(ft_strlen(st_var) - i + 1), collected_data);
	i++;
	j = 0;
	while (st_var[i])
	{
		right_str[j] = st_var[i];
		i++;
		j++;
	}
	right_str[j] = '\0';
	return (right_str);
}

static char	*extract_line(char *st_var, t_node **collected_data)
{
	char	*line;
	int		i;

	i = 0;
	if (!st_var[i])
		return (NULL);
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (st_var[i] == '\n')
	{
		line = ft_malloc(sizeof(char) * (i + 2), collected_data);
		line[i] = '\0';
		i = 0;
		while (st_var[i] && st_var[i] != '\n')
		{
			line[i] = st_var[i];
			i++;
		}
	}
	else
		line = ft_strdup(st_var, collected_data);
	return (line);
}

static char	*read_line(int fd, char *st_var, t_node **collected_data)
{
	char	*buffer;
	int		nb_bytes;

	nb_bytes = 1;
	buffer = ft_malloc(2, collected_data);
	while (nb_bytes != 0 && !ft_strchr(st_var, '\n'))
	{
		nb_bytes = read(fd, buffer, 1);
		if (nb_bytes == -1)
			error_and_free("Read failed", collected_data);
		buffer[nb_bytes] = '\0';
		st_var = ft_strjoin(st_var, buffer, collected_data);
	}
	return (st_var);
}

char	*get_next_line(int fd, t_node **collected_data)
{
	char		*line;
	static char	*st_var;

	if (fd < 0)
		return (NULL);
	st_var = read_line(fd, st_var, collected_data);
	line = extract_line(st_var, collected_data);
	if (!line)
		return (st_var = NULL, NULL);
	st_var = right_str(st_var, collected_data);
	return (line);
}
