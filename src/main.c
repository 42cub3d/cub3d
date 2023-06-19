/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:01:47 by subcho            #+#    #+#             */
/*   Updated: 2023/06/19 20:20:57 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	drow_window(t_map *map)
{
	(void)map;
	init_img(map);
	draw_map(map);
	mlx_hook(map->window, X_EVENT_KEY_PRESS, 0, press_key, map);
	mlx_hook(map->window, X_EVENT_KEY_EXIT, 0, exit_game, map);
	mlx_loop(map->mlx);
}

int	valid_argv(char **argv)
{
	char	**split;
	int		len;

	len = 0;
	split = ft_split(*argv, '.');
	while (split[len])
		len++;
	if (!ft_strncmp(split[len - 1], "cub", 4))
		return (1);
	return (0);
}

int find_longest_line(t_map *map)
{
	int ret;
	int	i;

	i = 5;
	ret = 0;
	while(++i < (int)map->y + 6)
		if (ret < (int)ft_strlen(map->map_char[i]))
			ret = (int)ft_strlen(map->map_char[i]);
	return (ret);
}

char	**make_expand_map(t_map *map)
{
	char **expand_map;
	int	i;
	int j;

	i = 0;
	expand_map = malloc(sizeof(char *) * (map->y + 2) + 1);
	map->max_map_line = find_longest_line(map);

	expand_map[0] = malloc(sizeof(char) * map->max_map_line + 3);
	ft_memset(expand_map[0], 'x', map->max_map_line + 3);
	expand_map[0][map->max_map_line + 2] = 0;

	expand_map[map->y + 1] = malloc(sizeof(char) * map->max_map_line + 3);
	ft_memset(expand_map[map->y + 1], 'x', map->max_map_line + 3);
	expand_map[map->y + 1][map->max_map_line + 2] = 0;

	while (++i <= (int)map->y)
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
	//i = 0;
	//while (expand_map[i])
	//	printf("%s\n", expand_map[i++]);
	return (expand_map);
}

int	check_closed(t_map *map, char **expanded_map)
{
	int i;
	int j;
	int	x;
	int	y;

	i = 0;
	while(++i < (int)map->y)
	{
		j = -1;
		while(expanded_map[i][++j])
		{
			if (expanded_map[i][j] == 'x')
			{
				x = -2;
				while (++x < 2)
				{
					y = -2;
					while (++y < 2)
					{
						if (i + x < 0 || j + y < 0 || (x == 0 && y == 0) || expanded_map[i + x][j + y] == 0 || j + y == (int)map->y + 2)
							continue ;
						else
							if (expanded_map[i + x][j + y] != '1' && expanded_map[i + x][j + y] != 'x')
								return (1);
					}
				}
			}
		}
	}
	return (0);
}

void	map_valid_check(t_map *map, unsigned int std, unsigned int j)
{
	unsigned int	i;
	char	**expanded_map;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (map->map_char[i + std][j] != '\0')
		{
			if (map->map_char[i + std][j] == 'N' || map->map_char[i + std][j] == 'S' ||
				map->map_char[i + std][j] == 'E' || map->map_char[i + std][j] == 'W')
			{
				map->player.x = j;
				map->player.y = i;
				map->is_player_in_map = 1;
			}
			else if (map->map_char[i + std][j] != ' ' && map->map_char[i + std][j] != '\n' 
					&& map->map_char[i + std][j] != '0' && map->map_char[i + std][j] != '1')
			{
				printf ("%d %d/n", j, i + std);
				printf ("%c", map->map_char[i + std][j]);
				return ;
			}
			j++;
		}
		i++;
	}
	expanded_map = make_expand_map(map);
	if (check_closed(map, expanded_map))
		ft_error(E_MAP_COLSED);
	if (map->is_player_in_map != 1)
		ft_error(E_MAP_VAL);
}

int	main(int argc, char **argv)
{
	t_map		map;

	if (!*(++argv) || argc == 1)
		return (0);
	if (!valid_argv(argv))
		ft_error(E_MAP_VAL);
	map.fd = open(*(argv), O_RDONLY);
	if (map.fd <= 0)
		ft_error(E_FD);
	init_map(&map, map.fd, 0);
	search_arg(&map, map.y -1, 0);
	map_valid_check(&map, 6, -1);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (0);
	map.window = mlx_new_window(map.mlx, 1600, 900, "cub3d");
	if (!map.window)
		return (0);
	drow_window(&map);
}
