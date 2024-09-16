/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 06:34:55 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/16 02:01:10 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		county_line(char *filee);
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strjoin(char *ptr, char *str);
int		ft_strchr(char *str);
char	*ft_saveline(char *str);
char	*ft_newline(char *ptr);
char	*ft_strdup(char *ptr);
void	ft_free(char **str);
void	ftt_free(char **str);
void	ft_read(char **str, char **ptr, int fd, ssize_t nbyte);

#endif
