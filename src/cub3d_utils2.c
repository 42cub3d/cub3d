/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:11:33 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/16 22:54:28 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	find_longest_line(t_map *map)
{
	int	ret;
	int	i;

	i = 5;
	ret = 0;
	while (++i < (int)map->x + 6)
		if (ret < (int)ft_strlen(map->map_char[i]))
			ret = (int)ft_strlen(map->map_char[i]);
	return (ret);
}

void	check(t_map *map, char **argv)
{
	map->fd = open(*(argv), O_RDONLY);
	if (map->fd <= 0)
		ft_error(E_FD);
	init_map(map, map->fd, 0);
	search_arg(map, map->x - 1, 0);
	map_valid_check(map, 6, -1, -1);
	if (map->is_player_in_map != 1)
		ft_error(E_MAP_VAL);
}

void	print_map(char **map, int x)
{
	int	i;

	i = -1;
	while (++i < x)
		printf("%s\n", map[i]);
}

char	**make_expand_map(t_map *map, int i, int j)
{
	char	**expand_map;

	expand_map = malloc(sizeof(char *) * (map->x + 3));
	map->max_map_line = find_longest_line(map);
	expand_map[0] = malloc(sizeof(char) * map->max_map_line + 3);
	ft_memset(expand_map[0], 'x', map->max_map_line + 3);
	expand_map[0][map->max_map_line + 2] = 0;
	expand_map[map->x + 1] = malloc(sizeof(char) * map->max_map_line + 3);
	expand_map[map->x + 2] = 0;
	ft_memset(expand_map[map->x + 1], 'x', map->max_map_line + 3);
	expand_map[map->x + 1][map->max_map_line + 2] = 0;
	while (++i <= (int)map->x)
	{
		expand_map[i] = malloc(sizeof(char) * map->max_map_line + 3);
		ft_memset(expand_map[i], 'x', map->max_map_line + 3);
		expand_map[i][map->max_map_line + 2] = 0;
		j = 0;
		while (++j <= (int)ft_strlen(map->map_char[i + 5]))
		{
			if (map->map_char[i + 5][j - 1] != '\n')
				expand_map[i][j] = map->map_char[i + 5][j - 1];
			if (map->map_char[i + 5][j - 1] == ' ')
				expand_map[i][j] = 'x';
		}
	}
	print_map(expand_map, map->x + 2);
	return (expand_map);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_pixel_size(t_map *map)
{
	if (map->x > (unsigned int)map->max_map_line)
		return (300 / map->x);
	return (400 / map->max_map_line);
}
