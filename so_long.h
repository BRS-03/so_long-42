/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:26:04 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/15 07:36:14 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "get_next_line.h"


#include "MLX42.h"
#include <fcntl.h>
#include <unistd.h>


typedef struct s_ply
{
    char **map;
    int x;
    int y;
    int cnb;
    mlx_t* mlx;
    mlx_image_t* wall;
    mlx_image_t* zero;
    mlx_image_t* exit;
    mlx_image_t* player;
    mlx_image_t* coin;
}t_ply;

void initialize_mlx(t_ply *mpr);
int game(t_ply *mpr);
void files(int ac, char *av[])
t_ply   *allocat(void);
int county_line(char *file) 
int ft_error_map(char **str)
int ft_errorscmap(char **str)
int ft_error_wall(char *tmp)
int ft_count_map(char **map)
void handle_allocation_error(t_ply *kask, char **tmp)
void copy_map(t_ply *kask, char **tmp)
void check_map_errors(t_ply *kask, char **tmp)
char **ft_read_map(char *mp)
void validate_player_and_characters(char **tmp, t_ply *kask)
void parsse_error(t_ply *kask)
int ft_error_frwall(char **ptr)
int ft_error_scwall(char **ptr)
int ft_error_line(char **tab)
void	ft_error_vmap(char **map, int x , int y)
void	ft_player(char **map)
int	ft_error_chmap(char **map)
int cnb(t_ply *ply)
void ft_exit(t_ply  *ply)
void update_player_position(t_ply *prm, int new_y, int new_x)
void handle_movement(t_ply *prm, int dy, int dx, mlx_key_data_t keyboard)
void ft_hook(mlx_key_data_t keyboard, void *param)
void    ft_init(t_ply *info)
void handle_image_load_failure(t_ply *mpr, mlx_image_t *images[], int count)
mlx_image_t* load_texture_as_image(t_ply *mpr, const char *path)
void setup_images(t_ply *mpr)
