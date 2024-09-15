/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:23:32 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/15 07:38:49 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int cnb(t_ply *ply)
{
    int    x;
    int    y;
    int    collectable;

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

void ft_exit(t_ply  *ply)
{
    ft_putstr("You win :)\n");
    free(ply->map);
    free(ply);
    exit(0);
}
void update_player_position(t_ply *prm, int new_y, int new_x)
{
    if (prm->map[new_y][new_x] == 'C')
        prm->cnb--;
    else if (prm->map[new_y][new_x] == 'E' && prm->cnb == 0)
        ft_exit(prm);

    if (prm->map[new_y][new_x] != 'E')
    {
        prm->map[new_y][new_x] = 'P';
        prm->map[prm->y][prm->x] = '0';
        mlx_image_to_window(prm->mlx, prm->zero, prm->x * 50, prm->y * 50);
        prm->y = new_y;
        prm->x = new_x;
        mlx_image_to_window(prm->mlx, prm->player, prm->x * 50, prm->y * 50);
    }
}

void handle_movement(t_ply *prm, int dy, int dx, mlx_key_data_t keyboard)
{
    int new_y = prm->y + dy;
    int new_x = prm->x + dx;
int i = 0;
    if (prm->map[new_y][new_x] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT))
    {
        prm->i++;
        printf("mpve : %d\n",i);
        update_player_position(prm, new_y, new_x);
        
    }
}
