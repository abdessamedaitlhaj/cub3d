/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:05:34 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/24 18:50:53 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*right_str(char *st_var)
{
	char	*right_str;
	int		i;
	int		j;

	i = 0;
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (!st_var[i])
		return (free(st_var), st_var = NULL, NULL);
	right_str = malloc(sizeof(char) * (ft_strlen(st_var) - i + 1));
	if (!right_str)
		return (free(st_var), st_var = NULL, NULL);
	i++;
	j = 0;
	while (st_var[i])
	{
		right_str[j] = st_var[i];
		i++;
		j++;
	}
	right_str[j] = '\0';
	free(st_var);
	return (right_str);
}

static char	*extract_line(char *st_var)
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
		line = malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		line[i] = '\0';
		i = 0;
		while (st_var[i] && st_var[i] != '\n')
		{
			line[i] = st_var[i];
			i++;
		}
	}
	else
		line = ft_strdup(st_var);
	return (line);
}

static char	*read_line(int fd, char *st_var)
{
	char	*buffer;
	int		nb_bytes;

	nb_bytes = 1;
	buffer = malloc(1);
	if (!buffer)
		return (free(st_var), st_var = NULL, NULL);
	while (nb_bytes != 0 && !ft_strchr(st_var, '\n'))
	{
		nb_bytes = read(fd, buffer, 1);
		if (nb_bytes == -1)
		{
			free(buffer);
			return (free(st_var), st_var = NULL, NULL);
		}
		buffer[nb_bytes] = '\0';
		st_var = ft_strjoin(st_var, buffer);
		if (!st_var)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (st_var);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*st_var;

	if (fd < 0)
		return (NULL);
	st_var = read_line(fd, st_var);
	if (!st_var)
		return (NULL);
	line = extract_line(st_var);
	if (!line)
		return (free(st_var), st_var = NULL, NULL);
	st_var = right_str(st_var);
	return (line);
}