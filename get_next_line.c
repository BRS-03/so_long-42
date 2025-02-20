/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:13:45 by yobourai          #+#    #+#             */
/*   Updated: 2025/02/19 01:09:45 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *ptr)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(ptr) + 1);
	if (!str)
		return (NULL);
	while (ptr[i] && ptr)
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_saveline(char *str)
{
	char	*new;
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	size = ft_strchr(str);
	if (size == 0)
		return (NULL);
	new = &str[size];
	if (!new)
		return (NULL);
	ptr = (char *)malloc(ft_strlen(str) - size + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (new && new[i])
	{
		ptr[i] = new[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_newline(char *ptr)
{
	int		i;
	char	*str;
	int		size;

	i = -1;
	size = ft_strchr(ptr);
	if (!size)
		size = ft_strlen(ptr);
	if (!size)
		return (NULL);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	while (ptr && (ptr[++i] && ptr[i] != '\n'))
		str[i] = ptr[i];
	if (ft_strchr(ptr))
	{
		str[i] = '\n';
		str[i + 1] = '\0';
	}
	else
		str[i] = '\0';
	return (str);
}

void	ft_read(char **str, char **ptr, int fd, ssize_t nbyte)
{
	char	*tmp;

	*str = (char *)malloc(BUFFER_SIZE + 1);
	if (!*str)
	{
		ft_free(ptr);
		return ;
	}
	while (nbyte > 0)
	{
		nbyte = read(fd, *str, BUFFER_SIZE);
		(*str)[nbyte] = '\0';
		tmp = ft_strjoin(*ptr, *str);
		if (!tmp)
		{
			ft_free(ptr);
			ft_free(str);
			return ;
		}
		ft_free(ptr);
		*ptr = tmp;
		if (ft_strchr(*str) || nbyte == 0)
			break ;
	}
	ft_free(str);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	ssize_t		nbyte;
	char		*str;
	char		*tmp;

	nbyte = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free(&ptr), NULL);
	ft_read(&str, &ptr, fd, nbyte);
	if (!ptr)
		return (NULL);
	str = ft_newline(ptr);
	if (!str)
		return (ft_free(&ptr), NULL);
	tmp = ptr;
	ptr = ft_saveline(tmp);
	return (ft_free(&tmp), str);
}
