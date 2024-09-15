/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:11:09 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/15 07:22:21 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
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

void initialize_mlx(t_ply *mpr)
{
    int WIDTH = ft_strlen(mpr->map[0]) * 50 - 50;
    int HEIGHT = ft_count_map(mpr->map) * 50;
    mpr->mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
    if (!mpr->mlx)
    {
        printf("Failed to initialize mlx\n");
        exit(1);
    }
}
int game(t_ply *mpr)
{
    initialize_mlx(mpr);
    setup_images(mpr);

    if (!mpr->wall || !mpr->player || !mpr->coin || !mpr->exit || !mpr->zero)
        return 0;
    ft_graph(mpr);
    mlx_key_hook(mpr->mlx, ft_hook, mpr);
    mlx_loop(mpr->mlx);
    mlx_terminate(mpr->mlx);
    return EXIT_SUCCESS;
}

void files(int ac, char *av[])
{
    int len;
    
    if (ac != 2)
    {
        printf("Erorr\nname of the map !!\n");
        exit(1);
    }
    len = 0;
    while (av[1][len] != '\0') 
        len++;
    if (len < 4 || av[1][len - 1] != 'r' || av[1][len - 2] != 'e' || av[1][len - 3] != 'b' || av[1][len - 4] != '.')
    {
        printf("Invalid file extension expected .ber\n");
        exit(1);
    }
}
t_ply   *allocat(void)
{
    t_ply   *cor;

    cor = NULL;
    cor = malloc(sizeof(t_ply));
    if (!cor)
        exit(1);
    cor->map = NULL;
    cor->cnb = 0;
    cor->mlx = NULL;
    cor->wall = NULL;
    cor->zero = NULL;
    cor->exit = NULL;
    cor->player = NULL;
    cor->coin = NULL;
    return cor ;
}

int main(int ac , char **av) 
{
    t_ply *cortab;

    files(ac,av);
    cortab = allocat();
    if(!cortab)
        return 1;
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
        free(cortab->map);
        free(cortab);
        return (1);
    }
}
