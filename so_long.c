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

int county_line(char *file) 
{
    char buffer[100];
    int fd;
    int nline = 1;
    int i = 0;
    
    fd = open(file, O_RDONLY);
    if(fd < 0)
        return 0;
    while (read(fd, buffer + i, 1) > 0)
    {
        if(i > 51 || nline > 28)
        {
            close(fd);
            return 0;
        }
        if(buffer[i] == '\n')
        {
            nline++;
            i = -1;
        }
        i++;
    }
    close(fd);
    return nline;
}
int ft_error_map(char **str)
{
    int i;
    int j;
    int bd;
    int coin;

    i = -1;
    j = -1;
    bd = 0;
    coin = 0;
        while(str[++i])
        {
            while(str[i][++j])
            {
                if(str[i][j] == 'C')
                    coin++;
                if(str[i][j] != '1' && str[i][j] != '0' &&str[i][j] != 'C' && str[i][j] != 'P' && str[i][j] != 'E' && str[i][j] != '\n')
                            bd++;
            }
            j = -1;
        }
        if(  coin < 1 || bd != 0 )
            return (ft_putstr("error or error inside the map"), 1);
    return 0;
}

int ft_errorscmap(char **str)
{
    int res ; 
    int player ;
    int i ;
    int j ;

    res= 0;
    player  = 0;
    i = -1;
    j= -1;
        while(str[++i])
        {
            while(str[i][++j])
            {
                if(str[i][j] == 'P')
                    player++;
                if(str[i][j] == 'E')
                    res++;
            }
            j = -1;
        }
        if(res !=1 || player != 1 )
            return (ft_putstr("error or error inside the map"), 1);
    return 0;
}
int ft_error_wall(char *tmp)
{
    int i;
    
    i = 0;
        while(tmp[i])
        {
            if(tmp[i] != '1' && tmp[i] != '\n')
                   break;
            i++;
        
        }
         if(tmp[i] != '1' && tmp[i] != '\0')
        {
                ft_putstr("error in the wall");
                return 1;
        }
    return 0;
    
}
int ft_error_frwall(char **ptr)
{
    int i =0;
    while(ptr[i])
    {
        if(ptr[i][0] != '1' && ptr[i][0] != '\n' && ptr[i][0] != '\0')
        {
            ft_putstr("error in the first wall");
            return 1;
        }
        i++;
    }
    return 0;
}
int ft_error_scwall(char **ptr)
{
    int i;
    int len;
    
    i = 0;
    len = ft_strlen(ptr[i]);
    while(ptr[i])
    {
        len = ft_strlen(ptr[i])-1;
        if((ptr[i][len-1] != '1') && ptr[i][len-1] != '\n' && ptr[i][len-1] != '\0')
        {
            ft_putstr("error in the second  wall\n");
            return 1;
        }
        i++;
    }
    return 0;
}

int ft_error_line(char **tab)
{
    int i;
    int j;
    int len;
    int k;

    k = -1;
    i = 0;
    j = ft_strlen(tab[0]);
    while(tab[++k]);
    while(tab[i])
    {
        len = ft_strlen(tab[i]);
        if(len != j  && i != k - 1)
            return (ft_putstr("line error\n"), 1);
        len++;
        i++;
    }
    if(len  != j || len <= k + 1)
        return (ft_putstr("error : something wrong\n"), 1);
    return 0;
}

void	ft_error_vmap(char **map, int x , int y)
{

	map[x][y] = '*';

	if ((map[x][y + 1] != 'E') && (map[x][y + 1] != '1') && map[x][y + 1] != '*')
		ft_error_vmap(map,x, y+ 1);
	if (map[x][y - 1] != 'E' && map[x][y - 1] != '1' && map[x][y - 1] != '*')
		ft_error_vmap(map, x , y- 1);
	if (map[x - 1][y] != 'E' && map[x - 1][y] != '1' && map[x - 1][y] != '*')
		ft_error_vmap(map, x - 1, y);
	if (map[x + 1][y] != 'E' && map[x + 1][y] != '1' && map[x + 1][y] != '*')
		ft_error_vmap(map,x+ 1, y);
}

void	ft_player(char **map)
{
	int	x;
	int	y;

    x = 0;
    y = 0;
	while (map[y][x])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				ft_error_vmap(map, y, x);
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	ft_error_chmap(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
                    ft_putstr("map invalid \n");
                    return (1);
            }
			j++;
		}
		j= 0;
		i++;
	}
	return (0);
}

int ft_count_map(char **map)
{
    int i = 0;
    while(map[i])
        i++;
    return i;
}

// void parsse_error(t_ply *kask)
// {
//     char **tmp = malloc( (ft_count_map(kask->map) + 1) * sizeof(char *));
//     if(!tmp)
//     {
//         ftt_free(kask->map);
//         free(kask->map);
//         free(kask);
//         exit(1);
//     }
//     int i;

//     i = 0;
//     while(kask->map[i])
//     {
//         tmp[i] = ft_strdup(kask->map[i]);
//         if(!tmp[i])
//         {
//             ftt_free(tmp);
//             ftt_free(kask->map);
//             free(kask->map);
//             free(kask);
//             exit(1);
//         }
//         i++;
//     }
//     tmp[i] = NULL;
//     if(ft_error_map(kask->map) == 1 || ft_error_wall(kask->map[0]) == 1 || ft_errorscmap(kask->map) == 1 || ft_error_wall(kask->map[i-1]) == 1 || ft_error_frwall(kask->map) == 1 ||
//     ft_error_scwall(kask->map) == 1 || ft_error_line(kask->map) == 1)
//     {
//         ftt_free(kask->map);
//         ftt_free(tmp);
//         free(tmp);
//         free(kask->map);
//         free(kask);
//         exit(1);
//     }
//     ft_player(tmp);
//     if(ft_error_chmap(tmp) == 1)
//     {
//         ftt_free(kask->map);
//         ftt_free(tmp);
//         free(tmp);
//         free(kask->map);
//         free(kask);
//         exit(1);
//     }
//     ftt_free(tmp);
//     free(tmp);
// }

void handle_allocation_error(t_ply *kask, char **tmp)
{
    ftt_free(kask->map);
    free(kask->map);
    ftt_free(tmp);
    free(tmp);
    free(kask);
    exit(1);
}

void copy_map(t_ply *kask, char **tmp)
{
    int i;
    
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

void check_map_errors(t_ply *kask, char **tmp)
{
    if (ft_error_map(kask->map) == 1 ||
        ft_error_wall(kask->map[0]) == 1 ||
        ft_errorscmap(kask->map) == 1 ||
        ft_error_wall(kask->map[ft_count_map(kask->map) - 1]) == 1 ||
        ft_error_frwall(kask->map) == 1 ||
        ft_error_scwall(kask->map) == 1 ||
        ft_error_line(kask->map) == 1)
    {
        handle_allocation_error(kask, tmp);
    }
}

void validate_player_and_characters(char **tmp, t_ply *kask)
{
    ft_player(tmp);
    if (ft_error_chmap(tmp) == 1)
        handle_allocation_error(kask, tmp);
}

void parsse_error(t_ply *kask)
{
    char **tmp;
    
    tmp  = malloc((ft_count_map(kask->map) + 1) * sizeof(char *));
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

char **ft_read_map(char *mp)
{
    int line_count;
    int i;
    char *line;
    int fd ;
    char **map;

    i = 0;
    line_count = county_line(mp);
    if (!line_count)
        return (NULL);
    fd = open(mp, O_RDONLY);
    map = malloc((line_count + 1) * sizeof(char *));
    if (!map)
        return (close(fd),NULL);
    while ((line = get_next_line(fd)) != NULL || line_count > i) 
        map[i++] = line;
    map[i] = NULL;
    if (i != line_count)
    {
        close(fd);
        ftt_free(map);
        return (free(map),NULL);
    }
    return (close(fd), map);
}

// void print_map(char **map)
// {
//     int j;
    
//     j = 0;
//     while(map[j])
//     {
//         printf("%s",map[j]);
//         j++;
//     }
//     printf("\n");
// }

void ft_graph(t_ply *mpr)
{
    int i ;
    int j ;
    
    i= 0;
    j=0;
    while(mpr->map[i])
    {
        j= 0;
        while (mpr->map[i][j])
        {
            if(mpr->map[i][j] == '1')
                mlx_image_to_window(mpr->mlx, mpr->wall, j*50,i*50 );
            if(mpr->map[i][j] == '0' || mpr->map[i][j] == 'P')
                mlx_image_to_window(mpr->mlx, mpr->zero, j*50,i*50 );
            if(mpr->map[i][j] == 'C')
                mlx_image_to_window(mpr->mlx, mpr->coin, j*50,i*50 );
            if(mpr->map[i][j] == 'E')
                mlx_image_to_window(mpr->mlx, mpr->exit, j*50,i*50 ) ;
            if(mpr->map[i][j] == 'P')
                mlx_image_to_window(mpr->mlx, mpr->player, j*50,i*50 );
            j++;
        }
        i++;
    }
}
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
    ft_putstr("You win\n");
    free(ply->map);
    free(ply);
    exit(0);
}
void update_player_position(t_ply *prm, int new_y, int new_x)
{
    if (prm->map[new_y][new_x] == 'C') {
        prm->cnb--;
    } else if (prm->map[new_y][new_x] == 'E' && prm->cnb == 0) {
        ft_exit(prm);
    }

    if (prm->map[new_y][new_x] != 'E') {
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

    if (prm->map[new_y][new_x] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)) {
        update_player_position(prm, new_y, new_x);
    }
}
void ft_hook(mlx_key_data_t keyboard, void *param)
{
    t_ply *prm = (t_ply *)param;
    prm->cnb = cnb(prm);

    if (keyboard.key == MLX_KEY_ESCAPE) {
        ft_putstr("game exit");
        ftt_free(prm->map);
        free(prm->map);
        free(prm);
        exit(0);
    }

    if (keyboard.key == MLX_KEY_UP) {
        handle_movement(prm, -1, 0, keyboard);
    } else if (keyboard.key == MLX_KEY_DOWN) {
        handle_movement(prm, 1, 0, keyboard);
    } else if (keyboard.key == MLX_KEY_LEFT) {
        handle_movement(prm, 0, -1, keyboard);
    } else if (keyboard.key == MLX_KEY_RIGHT) {
        handle_movement(prm, 0, 1, keyboard);
    }
}

// void ft_hook( mlx_key_data_t keyboard , void *param)
// {
//     t_ply *prm = (t_ply *) param ;
//      prm->cnb = cnb(prm);
//     if (keyboard.key == MLX_KEY_ESCAPE )
//     {
//         ft_putstr("game exit");
//         ftt_free(prm->map);
//         free(prm->map);
//         free(prm);
//         exit(0);
//     }
//     if (keyboard.key == MLX_KEY_UP && prm->map[prm->y - 1][prm->x] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)) 
//     {
//        if (prm->map[prm->y - 1][prm->x] == 'C'){
//            prm->cnb--;
//        }
//        else if (prm->map[prm->y - 1][prm->x] == 'E' && prm->cnb == 0)
//                 ft_exit(prm);
//         if (prm->map[prm->y - 1][prm->x] != 'E'){
//            prm->map[prm->y - 1][prm->x] = 'P';
//             prm->map[prm->y][prm->x] = '0' ;
//             mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
//             prm->y -= 1;
//             mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
//                 }
//     }     
//     else if (keyboard.key == MLX_KEY_DOWN && prm->map[prm->y + 1][prm->x] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT))
//     {
//        if (prm->map[prm->y + 1][prm->x] == 'C'){
//            prm->cnb--;
//        }
//         else if (prm->map[prm->y + 1][prm->x] == 'E' && prm->cnb == 0)
//                 ft_exit(prm);
//         if (prm->map[prm->y + 1][prm->x] != 'E'){

//         prm->map[prm->y + 1][prm->x] = 'P';
//         prm->map[prm->y][prm->x] = '0' ;
//         mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
//         prm->y += 1;
//         mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
//         }
//     }
//     else if (keyboard.key == MLX_KEY_LEFT && (prm->map[prm->y][prm->x - 1] != '1'  && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)))
//     {
//        if (prm->map[prm->y][prm->x - 1] == 'C'){
//            prm->cnb--;
//        }
//         else if (prm->map[prm->y][prm->x -1] == 'E' && prm->cnb == 0)
//                 ft_exit(prm);
//         if (prm->map[prm->y][prm->x - 1] != 'E'){
//             prm->map[prm->y][prm->x - 1] = 'P';
//             prm->map[prm->y][prm->x] = '0' ;
//             mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
//             prm->x -= 1;
//             mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
//                 }
//     }
//     else if (keyboard.key == MLX_KEY_RIGHT && prm->map[prm->y][prm->x + 1] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT))
//     {
//        if (prm->map[prm->y][prm->x + 1] == 'C'){
//            prm->cnb--;
//        }
//         else if (prm->map[prm->y][prm->x + 1] == 'E' && prm->cnb == 0)
//                 ft_exit(prm);
//         if (prm->map[prm->y][prm->x + 1] != 'E'){
//             prm->map[prm->y][prm->x + 1] = 'P';
//             prm->map[prm->y][prm->x] = '0' ;
//             mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
//             prm->x += 1;
//             mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
//                 }
//     }
// }

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

// int game(t_ply *mpr)
// {
//     mlx_texture_t* texture;
//     int WIDTH = ft_strlen(mpr->map[0])* 50 - 50;
//     int HEIGHT = ft_count_map(mpr->map) * 50 ;
// 	if (!(mpr->mlx = mlx_init(WIDTH, HEIGHT, "so_long", false)))
//         return(0);
//     texture = mlx_load_png("./images.png");
//     if (!texture)
//     {
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     mpr->wall = mlx_texture_to_image(mpr->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!mpr->wall)
//     {
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     texture = mlx_load_png("./player.png");
//     if (!texture)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         exit(1);
//     }
//     mpr->player = mlx_texture_to_image(mpr->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!mpr->player)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     texture = mlx_load_png("./imagesCOIN.png");
//     if (!texture)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_delete_image(mpr->mlx, mpr->player);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     mpr->coin = mlx_texture_to_image(mpr->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!mpr->coin)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_delete_image(mpr->mlx, mpr->player);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     texture = mlx_load_png("./exit.png");
//     if (!texture)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_delete_image(mpr->mlx, mpr->player);
//         mlx_delete_image(mpr->mlx, mpr->coin);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     mpr->exit = mlx_texture_to_image(mpr->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!mpr->exit)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_delete_image(mpr->mlx, mpr->player);
//         mlx_delete_image(mpr->mlx, mpr->coin);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     texture = mlx_load_png("./wero.png");
//     if (!texture)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_delete_image(mpr->mlx, mpr->player);
//         mlx_delete_image(mpr->mlx, mpr->coin);
//         mlx_delete_image(mpr->mlx, mpr->exit);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     mpr->zero = mlx_texture_to_image(mpr->mlx, texture);
//     mlx_delete_texture(texture);
//     if (!mpr->zero)
//     {
//         mlx_delete_image(mpr->mlx, mpr->wall);
//         mlx_delete_image(mpr->mlx, mpr->player);
//         mlx_delete_image(mpr->mlx, mpr->coin);
//         mlx_delete_image(mpr->mlx, mpr->exit);
//         mlx_terminate(mpr->mlx);
//         printf("img not loadedd\n");
//         return (0);
//     }
//     ft_graph(mpr);
// 	mlx_key_hook(mpr->mlx, ft_hook, mpr);    
//     mlx_loop(mpr->mlx);
// 	mlx_terminate(mpr->mlx);
// 	return (EXIT_SUCCESS);
// }

// Handle deletion of images if any texture fails to load
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

// Setup images using the paths provided
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