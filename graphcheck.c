/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:23:45 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/15 07:23:48 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void ft_hook(mlx_key_data_t keyboard, void *param)
{
    t_ply *prm = (t_ply *)param;
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

void    ft_init(t_ply *info)
{
    int i = 0;
    int j =0;
    while(info->map[i])
    {
        j= 0;
        while (info->map[i][j])
        {
            if(info->map[i][j] == 'P')
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

void handle_image_load_failure(t_ply *mpr, mlx_image_t *images[], int count)
{
    int i;

    i = -1;
    while(++i < count)
    {
        if (images[i])
            mlx_delete_image(mpr->mlx, images[i]);
    }
    mlx_terminate(mpr->mlx);
    printf("img not loaded\n");
}

mlx_image_t* load_texture_as_image(t_ply *mpr, const char *path)
{
    mlx_texture_t *texture = mlx_load_png(path);
    if (!texture)
    {
        handle_image_load_failure(mpr, NULL, 0);
        return NULL;
    }
    mlx_image_t *image = mlx_texture_to_image(mpr->mlx, texture);
    mlx_delete_texture(texture);
    if (!image)
        handle_image_load_failure(mpr, NULL, 0);
    return image;
}

void setup_images(t_ply *mpr)
{
    mlx_image_t *textures[] = {
        load_texture_as_image(mpr, "./images.png"),
        load_texture_as_image(mpr, "./player.png"),
        load_texture_as_image(mpr, "./imagesCOIN.png"),
        load_texture_as_image(mpr, "./exit.png"),
        load_texture_as_image(mpr, "./wero.png")
    };
    if (!textures[0] || !textures[1] || !textures[2] || !textures[3] || !textures[4])
    {
        handle_image_load_failure(mpr, textures, 5);
        return;
    }
    mpr->wall = textures[0];
    mpr->player = textures[1];
    mpr->coin = textures[2];
    mpr->exit = textures[3];
    mpr->zero = textures[4];
}

