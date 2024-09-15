/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 07:24:55 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/15 07:24:57 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
