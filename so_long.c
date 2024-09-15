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
    int i = 0;
    int j = 0;
    int res = 0;
    int coin = 0;
    int player = 0;
    int bd = 0;
        while(str[i])
        {
            while(str[i][j])
            {
                if(str[i][j] == 'P')
                    player++;
                if(str[i][j] == 'E')
                    res++;
                if(str[i][j] == 'C')
                    coin++;
                if(str[i][j] != '1' &&str[i][j] != '0' &&str[i][j] != 'C' && str[i][j] != 'P' && str[i][j] != 'E' && str[i][j] != '\n' )
                            bd++;
                j++;
            }
            j = 0;
            i++;
        }
        if(res !=1 || coin < 1 || player != 1 || bd != 0 )
        {
            ft_putstr("error or error inside the map");
            return 1;
        }
    return 0;
}

int ft_error_wall(char *tmp)
{
    int i = 0;
        while(tmp[i])
        {
            if(tmp[i] == '1' && tmp[i] == '\n')
                   i++;
            else
                break;
        
        }
        if(tmp[i] == '1' && tmp[i] == '\0')
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
    int i =0;
    int len = ft_strlen(ptr[i]);
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
    int i ;
    int j ;
    int len ;
    int k ;

    k = 0;
    i = 0 ;
    j = ft_strlen(tab[0]);
    while(tab[k])
        k++;
    while(tab[i])
    {
        len = ft_strlen(tab[i]);
        if(len != j  && i != k-1) 
        {
            ft_putstr("line error\n");
            return 1;
        }
        len++;
        i++;
    }
    if(len  != j || len <= k +1)
    {
        ft_putstr("error ; map is not rectangular or line error in last \n");
        return 1;
    }
    return 0;
}

void	ft_error_vmap(char **map, int x , int y)
{

	map[x][y] = '*';

	if ((map[x][y + 1] != '1') && map[x][y + 1] != '*')
		ft_error_vmap(map,x, y+ 1);
	if (map[x][y - 1] != '1' && map[x][y - 1] != '*')
		ft_error_vmap(map, x , y- 1);
	if (map[x - 1][y] != '1' && map[x - 1][y] != '*')
		ft_error_vmap(map, x - 1, y);
	if (map[x + 1][y] != '1' && map[x + 1][y] != '*')
		ft_error_vmap(map,x+ 1, y);
}

void	ft_player(char **map)
{
	int	x=0;
	int	y=0;

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
	int	i=0;
	int	j=0;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
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

void parsse_error(t_ply *kask)
{
    char **tmp = malloc( (ft_count_map(kask->map) + 1) * sizeof(char *));
    if(!tmp)
    {
        ftt_free(kask->map);
        free(kask->map);
        free(kask);
        exit(1);
    }
    int i;
    i = 0;
    while(kask->map[i])
    {
        tmp[i] = ft_strdup(kask->map[i]);
        if(!tmp[i])
        {
            ftt_free(tmp);
            ftt_free(kask->map);
            free(kask->map);
            free(kask);
            exit(1);
        }
        i++;
    }
    tmp[i] = NULL;
    if(ft_error_map(kask->map) == 1 || ft_error_wall(kask->map[0]) == 1 || ft_error_wall(kask->map[i-1]) == 1 || ft_error_frwall(kask->map) == 1 ||
    ft_error_scwall(kask->map) == 1 || ft_error_line(kask->map) == 1)
    {
        ftt_free(kask->map);
        ftt_free(tmp);
        free(tmp);
        free(kask->map);
        free(kask);
        exit(1);
    }
    ft_player(tmp);
    if(ft_error_chmap(tmp) == 1)
    {
        ftt_free(kask->map);
        ftt_free(tmp);
        free(tmp);
        free(kask->map);
        free(kask);
        exit(1);
    }
    ftt_free(tmp);
    free(tmp);
}

char **ft_read_map(char *mp)
{
    int line_count;
    line_count = county_line(mp);
    if (!line_count)
        return (NULL);
    int fd = open(mp, O_RDONLY);
    char **map = malloc((line_count + 1) * sizeof(char *));
    if (!map)
    {
        close(fd);
        return (NULL);
    }
    int i;
    i = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL || line_count > i) //to remove 
    {
        map[i] = line;
        i++;
    }
    map[i] = NULL;
    if (i != line_count)
    {
        close(fd);
        ftt_free(map);
        free(map);
        return (NULL);
    }
    close(fd);
    return map;
}

void print_map(char **map)
{
    int j = 0;

    while(map[j])
    {
        printf("%s",map[j]);
        j++;
    }
    printf("\n");
}

void ft_graph(t_ply *mpr)
{
    int i = 0;
    int j =0;
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

int cnb(char **ply)
{
    int i = 0;
    int j =0;
    int cnb = 0;
    while(ply[i])
    {
        j= 0;
        while (ply[i][j])
        {
            if(ply[i][j] == 'C')
                cnb++;
            j++;
        }
        i++;
    }
    return cnb;
}

void ft_exit(char  **ply)
{
    int x = 0;
    int y = 0;
    int cn = cnb(ply);
    while(ply[y])
    {
        x = 0;
        while (ply[y][x])
        {
            if(ply[y][x] == 'C')
                    cn--;
            x++;
        }
        y++;
    }
    if(ply[y][x] == 'E' && cnb(ply) == 0)
    {
        ft_putstr("you win\n");
        ftt_free(ply);
        return ;
    }
    return ;
}

void ft_hook( mlx_key_data_t keyboard ,void* param)
{
    t_ply *prm = (t_ply*)param;
	if (keyboard.key == MLX_KEY_ESCAPE )
	{
        ft_putstr("game exit");
        ftt_free(prm->map);
        free(prm->map);
        free(prm);
        exit(0);
    }
    if (keyboard.key == MLX_KEY_UP && prm->map[prm->y - 1][prm->x] != '1'&& (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)) 
    {
        ft_putstr("UP\n");
            prm->map[prm->y - 1][prm->x] = 'P';
            prm->map[prm->y][prm->x] = '0' ;
            mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
            prm->y -= 1;
            mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
    }     
	else if(keyboard.key ==MLX_KEY_DOWN && prm->map[prm->y + 1][prm->x] != '1'   && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)) 
     {
        ft_putstr("DOWN\n");
            prm->map[prm->y + 1][prm->x] = 'P';
            prm->map[prm->y][prm->x] = '0' ;
            mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
            prm->y += 1;
            mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
    }
	else if (keyboard.key == MLX_KEY_LEFT && (prm->map[prm->y][prm->x - 1] != '1'  && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)))
    {
        ft_putstr("LEFT\n");
            prm->map[prm->y][prm->x - 1] = 'P';
            prm->map[prm->y][prm->x] = '0' ;
            mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
            prm->x -= 1;
            mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
    }
	else if (keyboard.key == MLX_KEY_RIGHT && prm->map[prm->y][prm->x + 1] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT))
    {
        ft_putstr("RIGHT\n");
            prm->map[prm->y][prm->x + 1] = 'P';
            prm->map[prm->y][prm->x] = '0' ;
            mlx_image_to_window(prm->mlx, prm->zero, prm->x*50, prm->y*50);
            prm->x += 1;
            mlx_image_to_window(prm->mlx, prm->player, prm->x*50, prm->y*50);
    }
    else if(keyboard.key == MLX_KEY_RIGHT && prm->map[prm->y - 1][prm->x] == 'E' && prm->cnb == 0)
    {
            ft_exit(prm->map);
              exit(0);
    }
    else if(keyboard.key == MLX_KEY_RIGHT && prm->map[prm->y + 1][prm->x] == 'E' && prm->cnb == 0)
    {
            ft_exit(prm->map);
              exit(0);
    }
    else if(prm->map[prm->y][prm->x - 1] == 'E' && prm->cnb == 0 &&keyboard.key == MLX_KEY_RIGHT)
    {
            ft_exit(prm->map);
              exit(0);
    }
    else if(keyboard.key == MLX_KEY_RIGHT && prm->map[prm->y][prm->x + 1] == 'E' && prm->cnb == 0)
    {
            ft_exit(prm->map);
              exit(0);
    }
    print_map(prm->map);
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

int game(t_ply *mpr)
{
    mlx_texture_t* texture;
    int WIDTH = ft_strlen(mpr->map[0])* 50 - 50;
    int HEIGHT = ft_count_map(mpr->map) * 50 ;
	if (!(mpr->mlx = mlx_init(WIDTH, HEIGHT, "so_long", false)))
        return(0);
    texture = mlx_load_png("./images.png");
    if (!texture)
    {
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    mpr->wall = mlx_texture_to_image(mpr->mlx, texture);
    mlx_delete_texture(texture);
    if (!mpr->wall)
    {
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    texture = mlx_load_png("./player.png");
    if (!texture)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        exit(1);
    }
    mpr->player = mlx_texture_to_image(mpr->mlx, texture);
    mlx_delete_texture(texture);
    if (!mpr->player)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    texture = mlx_load_png("./imagesCOIN.png");
    if (!texture)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_delete_image(mpr->mlx, mpr->player);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    mpr->coin = mlx_texture_to_image(mpr->mlx, texture);
    mlx_delete_texture(texture);
    if (!mpr->coin)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_delete_image(mpr->mlx, mpr->player);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    texture = mlx_load_png("./exit.png");
    if (!texture)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_delete_image(mpr->mlx, mpr->player);
        mlx_delete_image(mpr->mlx, mpr->coin);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    mpr->exit = mlx_texture_to_image(mpr->mlx, texture);
    mlx_delete_texture(texture);
    if (!mpr->exit)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_delete_image(mpr->mlx, mpr->player);
        mlx_delete_image(mpr->mlx, mpr->coin);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    texture = mlx_load_png("./wero.png");
    if (!texture)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_delete_image(mpr->mlx, mpr->player);
        mlx_delete_image(mpr->mlx, mpr->coin);
        mlx_delete_image(mpr->mlx, mpr->exit);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    mpr->zero = mlx_texture_to_image(mpr->mlx, texture);
    mlx_delete_texture(texture);
    if (!mpr->zero)
    {
        mlx_delete_image(mpr->mlx, mpr->wall);
        mlx_delete_image(mpr->mlx, mpr->player);
        mlx_delete_image(mpr->mlx, mpr->coin);
        mlx_delete_image(mpr->mlx, mpr->exit);
        mlx_terminate(mpr->mlx);
        printf("img not loadedd\n");
        return (0);
    }
    ft_graph(mpr);
	mlx_key_hook(mpr->mlx, ft_hook, mpr);    
    mlx_loop(mpr->mlx);
	mlx_terminate(mpr->mlx);
	return (EXIT_SUCCESS);
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

int main(int ac , char *av[]) 
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