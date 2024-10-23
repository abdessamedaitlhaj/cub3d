/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradais <paradais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 05:46:36 by paradais          #+#    #+#             */
/*   Updated: 2024/10/23 05:48:50 by paradais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		len;
	int		neg;

	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	len = ft_nbrlen(n);
	str = malloc(sizeof(char) * (len + neg + 1));
	if (!str)
		return (NULL);
	i = len + neg - 1;
	while (i >= neg)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	if (neg)
		str[0] = '-';
	str[len + neg] = '\0';
	return (str);
}

char 	*ft_strjoin2(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}