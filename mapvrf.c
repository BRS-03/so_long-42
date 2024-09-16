/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvrf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:25:12 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 02:48:52 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_count_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	handle_allocation_error(t_ply *kask, char **tmp)
{
	ftt_free(kask->map);
	if (kask->map)
		free(kask->map);
	ftt_free(tmp);
	if (tmp)
		free(tmp);
	free(kask);
	exit(1);
}

void	copy_map(t_ply *kask, char **tmp)
{
	int	i;

	i = 0;
	while (kask->map[i])
	{
		tmp[i] = ft_strdup(kask->map[i]);
		if (!tmp[i])
			handle_allocation_error(kask, tmp);
		i++;
	}
	tmp[i] = NULL;
}

void	check_map_errors(t_ply *kask, char **tmp)
{
	if (ft_error_map(kask->map) == 1 || ft_error_wall(kask->map[0]) == 1
		|| ft_errorscmap(kask->map) == 1
		|| ft_error_wall(kask->map[ft_count_map(kask->map) - 1]) == 1
		|| ft_error_frwall(kask->map) == 1 || ft_error_scwall(kask->map) == 1
		|| ft_error_line(kask->map) == 1)
	{
		handle_allocation_error(kask, tmp);
	}
}
