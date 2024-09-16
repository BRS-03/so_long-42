/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_prc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:24:07 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 03:24:36 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_error_frwall(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0] != '1' && ptr[i][0] != '\n' && ptr[i][0] != '\0')
		{
			ft_putstr("error in the first wall");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_error_scwall(char **ptr)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(ptr[i]);
	while (ptr[i])
	{
		len = ft_strlen(ptr[i]) - 1;
		if ((ptr[i][len - 1] != '1') && ptr[i][len - 1] != '\n' && ptr[i][len
			- 1] != '\0')
		{
			ft_putstr("error in the second  wall\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_error_line(char **tab)
{
	int	i;
	int	j;
	int	len;
	int	k;

	k = -1;
	i = 0;
	j = ft_strlen(tab[0]);
	while (tab[++k])
		;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		if (len != j && i != k - 1)
			return (ft_putstr("line error\n"), 1);
		len++;
		i++;
	}
	if (len != j || len <= k + 1)
		return (ft_putstr("error : something wrong\n"), 1);
	return (0);
}
