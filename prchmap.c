/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prchmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:41:04 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 04:49:45 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_error_vmap(char **map, int x, int y, int *flag)
{
	map[x][y] = '*';
	if (map[x][y + 1] != '1' && map[x][y + 1] != 'E' && map[x][y + 1] != '*')
		ft_error_vmap(map, x, y + 1, flag);
	if (map[x][y - 1] != '1' && map[x][y - 1] != 'E' && map[x][y - 1] != '*')
		ft_error_vmap(map, x, y - 1, flag);
	if (map[x - 1][y] != '1' && map[x - 1][y] != 'E' && map[x - 1][y] != '*')
		ft_error_vmap(map, x - 1, y, flag);
	if (map[x + 1][y] != '1' && map[x + 1][y] != 'E' && map[x + 1][y] != '*')
		ft_error_vmap(map, x + 1, y, flag);
	if (map[x][y + 1] == 'E' || map[x][y - 1] == 'E' || map[x + 1][y] == 'E' ||
	map[x - 1][y] == 'E')
		*flag = 1;
}

void	ft_player(char **map, int *flag)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y][x])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				ft_error_vmap(map, y, x, flag);
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	ft_error_chmap(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
				ft_putstr("map invalid \n");
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
