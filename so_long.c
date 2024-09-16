/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:11:09 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 05:15:47 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_mlx(t_ply *mpr)
{
	int	width;
	int	height;

	width = ft_strlen(mpr->map[0]) * 50 - 50;
	height = ft_count_map(mpr->map) * 50;
	mpr->mlx = mlx_init(width, height, "so_long", false);
	if (!mpr->mlx)
	{
		printf("Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
}

int	game(t_ply *mpr)
{
	initialize_mlx(mpr);
	setup_images(mpr);
	if (!mpr->wall || !mpr->player || !mpr->coin || !mpr->exit || !mpr->zero)
		return (0);
	ft_graph(mpr);
	mlx_key_hook(mpr->mlx, ft_hook, mpr);
	mlx_loop(mpr->mlx);
	mlx_terminate(mpr->mlx);
	return (EXIT_SUCCESS);
}

void	files(int ac, char *av[])
{
	int	len;

	if (ac != 2)
	{
		printf("Error: name of the map !!\n");
		exit(EXIT_FAILURE);
	}
	len = 0;
	while (av[1][len] != '\0')
		len++;
	if (len < 4 || av[1][len - 1] != 'r' || av[1][len - 2] != 'e' || av[1][len
		- 3] != 'b' || av[1][len - 4] != '.')
	{
		printf("Invalid file extension expected .ber\n");
		exit(EXIT_FAILURE);
	}
}

t_ply	*allocat(void)
{
	t_ply	*cor;

	cor = NULL;
	cor = malloc(sizeof(t_ply));
	if (!cor)
		exit(1);
	cor->map = NULL;
	cor->cnb = 0;
	cor->move = 0;
	cor->mlx = NULL;
	cor->wall = NULL;
	cor->zero = NULL;
	cor->exit = NULL;
	cor->player = NULL;
	cor->coin = NULL;
	return (cor);
}

int	main(int ac, char **av)
{
	t_ply	*cortab;

	files(ac, av);
	cortab = allocat();
	if (!cortab)
		return (1);
	cortab->map = ft_read_map(av[1]);
	if (!cortab->map)
	{
		free(cortab);
		printf("error\n");
		return (1);
	}
	parsse_error(cortab);
	ft_init(cortab);
	if (!game(cortab))
	{
		ftt_free(cortab->map);
		if (cortab->map)
			free(cortab->map);
		if (cortab)
			free(cortab);
		return (1);
	}
}
