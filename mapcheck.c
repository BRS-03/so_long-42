/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:24:55 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 04:22:50 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_read_map(char *mp)
{
	int		line_count;
	int		i;
	char	*line;
	int		fd;
	char	**map;

	i = -1;
	line_count = county_line(mp);
	if (!line_count)
		return (NULL);
	fd = open(mp, O_RDONLY);
	map = malloc((line_count + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line != NULL || line_count > i)
	{
		map[++i] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (close(fd), map);
}

void	validate_player_and_characters(char **tmp, t_ply *kask)
{
	int	flag;

	flag = 0;
	ft_player(tmp, &flag);
	if (!flag || ft_error_chmap(tmp) == 1)
		handle_allocation_error(kask, tmp);
}

void	parsse_error(t_ply *kask)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc((ft_count_map(kask->map) + 1) * sizeof(char *));
	if (!tmp)
	{
		handle_allocation_error(kask, NULL);
	}
	copy_map(kask, tmp);
	check_map_errors(kask, tmp);
	validate_player_and_characters(tmp, kask);
	ftt_free(tmp);
	free(tmp);
}
