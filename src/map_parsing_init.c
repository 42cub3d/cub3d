/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:29:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/15 17:52:14 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	init_arg(t_map *map, int i)
{
	char	**tmp_rgb;

	map->img->n_wall = ft_strdup(map->map_argv[0][1]);
	map->img->s_wall = ft_strdup(map->map_argv[1][1]);
	map->img->w_wall = ft_strdup(map->map_argv[2][1]);
	map->img->e_wall = ft_strdup(map->map_argv[3][1]);
	tmp_rgb = ft_split(map->map_argv[4], ',');
	while (++i < 3)
		map->floor_color[i] = ft_atio(tmp_rgb[i]);
	i = -1;
	tmp_rgb = ft_split(map->map_argv[5], ',');
	while (++i < 3)
		map->ceiling_color[i] = ft_atio(tmp_rgb[i]);
}

int	search_arg(t_map *map, int i, int j)
{
	static char	*campass[] = {"NO", "SO", "WE", "EA", "F ", "C "};

	while (map->map_char[i][0] != '\n')
		i--;
	map->map_char += i;
	map->y -= i;
	while (map->map_char[i][0] == '\n')
		i--;
	while (j < 6 && map->map_char[i])
	{
		if (ft_strncmp(map->map_char[i], campass[j], 2) == 0)
			map->map_argv[j++] = ft_strdup(map->map_char[i--] + 2);
		while (map->map_char[i][0] == '\n')
			i--;
	}
	if (i != -1)
		return (1);
	return (init_arg(map, -1));
}

void	init_map(t_map *map, int fd, int cnt)
{
	char	*line;

	line = get_next_line(fd);
	if (cnt == 0 && !line)
		ft_error(PARSINGERR);
	if (!line)
	{
		map->map_char = malloc(sizeof(char *) * (cnt + 1));
		map->y = cnt;
	}
	if (line)
		init_map(map, fd, cnt + 1);
	map->map_char[cnt] = line;
	search_arg(map, map->y, 0);
}
