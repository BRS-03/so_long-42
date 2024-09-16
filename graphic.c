/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:23:32 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 05:08:12 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	cnb(t_ply *ply)
{
	int	x;
	int	y;
	int	collectable;

	x = 0;
	y = 0;
	collectable = 0;
	while (ply->map[y])
	{
		while (ply->map[y][x])
		{
			if (ply->map[y][x] == 'C')
				collectable++;
			x++;
		}
		x = 0;
		y++;
	}
	ply->cnb = collectable;
	return (collectable);
}

void	ft_exit(t_ply *ply)
{
	ft_putstr("You win :)\n");
	ftt_free(ply->map);
	free(ply->map);
	free(ply);
	exit(0);
}

void	update_player_position(t_ply *prm, int new_y, int new_x)
{
	int	k;

	k = prm->cnb;
	if (prm->map[new_y][new_x] == 'C')
		k--;
	else if (prm->map[new_y][new_x] == 'E' && prm->cnb == 0)
		ft_exit(prm);
	if (prm->map[new_y][new_x] != 'E')
	{
		prm->map[new_y][new_x] = 'p';
		prm->map[prm->y][prm->x] = '0';
		mlx_image_to_window(prm->mlx, prm->zero, prm->x * 50, prm->y * 50);
		prm->y = new_y;
		prm->x = new_x;
		mlx_image_to_window(prm->mlx, prm->player, prm->x * 50, prm->y * 50);
	}
}

void	handle_movement(t_ply *prm, int dy, int dx, mlx_key_data_t keyboard)
{
	int	new_y;
	int	new_x;

	new_y = prm->y + dy;
	new_x = prm->x + dx;
	if (prm->map[new_y][new_x] != '1' && (keyboard.action == MLX_PRESS
			|| keyboard.action == MLX_REPEAT))
	{
		if ((prm->map[new_y][new_x] != 'E' && prm->cnb >= 0) ||
		(prm->map[new_y][new_x] == 'E' && prm->cnb == 0))
		{
			prm->move++;
			printf("move: [%d]\n", prm->move);
		}
		update_player_position(prm, new_y, new_x);
	}
}

void	ft_graph(t_ply *mpr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mpr->map[i])
	{
		j = 0;
		while (mpr->map[i][j])
		{
			if (mpr->map[i][j] == '1')
				mlx_image_to_window(mpr->mlx, mpr->wall, j * 50, i * 50);
			if (mpr->map[i][j] == '0' || mpr->map[i][j] == 'P')
				mlx_image_to_window(mpr->mlx, mpr->zero, j * 50, i * 50);
			if (mpr->map[i][j] == 'P')
				mlx_image_to_window(mpr->mlx, mpr->player, j * 50, i * 50);
			if (mpr->map[i][j] == 'C')
				mlx_image_to_window(mpr->mlx, mpr->coin, j * 50, i * 50);
			if (mpr->map[i][j] == 'E')
				mlx_image_to_window(mpr->mlx, mpr->exit, j * 50, i * 50);
			j++;
		}
		i++;
	}
}
