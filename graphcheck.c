/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:23:45 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 03:49:58 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_hook(mlx_key_data_t keyboard, void *param)
{
	t_ply	*prm;

	prm = (t_ply *)param;
	prm->cnb = cnb(prm);
	if (keyboard.key == MLX_KEY_ESCAPE)
	{
		ft_putstr("game exit ;(\n");
		ftt_free(prm->map);
		free(prm->map);
		free(prm);
		exit(0);
	}
	if (keyboard.key == MLX_KEY_UP)
		handle_movement(prm, -1, 0, keyboard);
	else if (keyboard.key == MLX_KEY_DOWN)
		handle_movement(prm, 1, 0, keyboard);
	else if (keyboard.key == MLX_KEY_LEFT)
		handle_movement(prm, 0, -1, keyboard);
	else if (keyboard.key == MLX_KEY_RIGHT)
		handle_movement(prm, 0, 1, keyboard);
}

void	ft_init(t_ply *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'P')
			{
				info->y = i;
				info->x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	handle_image_load_failure(t_ply *mpr, int count)
{
	if (count >= 1)
		mlx_delete_image(mpr->mlx, mpr->wall);
	if (count >= 2)
		mlx_delete_image(mpr->mlx, mpr->player);
	if (count >= 3)
		mlx_delete_image(mpr->mlx, mpr->coin);
	if (count >= 4)
		mlx_delete_image(mpr->mlx, mpr->exit);
	mlx_terminate(mpr->mlx);
	ft_putstr("img not loaded\n");
}

mlx_image_t	*load_texture_as_image(t_ply *mpr, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mpr->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	return (image);
}

void	setup_images(t_ply *mpr)
{
	mpr->wall = load_texture_as_image(mpr, "./images.png");
	if (!mpr->wall)
		handle_image_load_failure(mpr, 0);
	mpr->player = load_texture_as_image(mpr, "./player.png");
	if (!mpr->player)
		handle_image_load_failure(mpr, 1);
	mpr->coin = load_texture_as_image(mpr, "./imagesCOIN.png");
	if (!mpr->coin)
		handle_image_load_failure(mpr, 2);
	mpr->exit = load_texture_as_image(mpr, "./exit.png");
	if (!mpr->exit)
		handle_image_load_failure(mpr, 3);
	mpr->zero = load_texture_as_image(mpr, "./wero.png");
	if (!mpr->zero)
		handle_image_load_failure(mpr, 4);
}
