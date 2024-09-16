/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcingmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:25:39 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 05:15:01 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	county_line(char *file)
{
	char	buffer[100];
	int		fd;
	int		nline;
	int		i;

	nline = 1;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, buffer + i, 1) > 0)
	{
		if (i > 51 || nline > 28)
		{
			close(fd);
			return (0);
		}
		if (buffer[i] == '\n')
		{
			nline++;
			i = -1;
		}
		i++;
	}
	return (close(fd), nline);
}

int	ft_error_map(char **str)
{
	int	i;
	int	j;
	int	bd;
	int	coin;

	i = -1;
	j = -1;
	bd = 0;
	coin = 0;
	while (str[++i])
	{
		while (str[i][++j])
		{
			if (str[i][j] == 'C')
				coin++;
			if (str[i][j] != '1' && str[i][j] != '0' && str[i][j] != 'C'
				&& str[i][j] != 'P' && str[i][j] != 'E' && str[i][j] != '\n')
				bd++;
		}
		j = -1;
	}
	if (coin < 1 || bd != 0)
		return (ft_putstr("something wrong\n"), 1);
	return (0);
}

int	ft_errorscmap(char **str)
{
	int	res;
	int	player;
	int	i;
	int	j;

	res = 0;
	player = 0;
	i = -1;
	j = -1;
	while (str[++i])
	{
		while (str[i][++j])
		{
			if (str[i][j] == 'P')
				player++;
			if (str[i][j] == 'E')
				res++;
		}
		j = -1;
	}
	if (res != 1 || player != 1)
		return (ft_putstr("something wrong\n"), 1);
	return (0);
}

int	ft_error_wall(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != '1' && tmp[i] != '\n')
			break ;
		i++;
	}
	if (tmp[i] != '1' && tmp[i] != '\0')
	{
		ft_putstr("error in the wall\n");
		return (1);
	}
	return (0);
}
