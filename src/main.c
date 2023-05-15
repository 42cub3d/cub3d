/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:01:47 by subcho            #+#    #+#             */
/*   Updated: 2023/05/15 17:57:15 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	drow_window(t_map *map)
{
	init_img(map);
	draw_map(map, -1);
	//mlx_hook(map->window, X_EVENT_KEY_PRESS, 0, press_key, map);
	//mlx_hook(map->window, X_EVENT_KEY_EXIT, 0, exit_game, map);
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

int	map_valid_check(t_map *map, unsigned int i, unsigned int j)
{
	while (map->map_char[++i])
	{
		j = -1;
		while (map->map_char[i][++j])
		{
			if ((i == 0 || i == map->y) || (j == 0 || j == ft_strlen(map->map_char[i])))
				if (map->map_char[i][j] != 1)
					return (1);
			if (map->map_char[i][j] == 'N' ||
				map->map_char[i][j] == 'S' ||
				map->map_char[i][j] == 'E' ||
				map->map_char[i][j] == 'W')
			{
				map->player.x = j;
				map->player.y = i;
				map->is_player_in_map = 1;
			}
			else if (map->map_char[i][j] != '\n' && map->map_char[i][j] != '0'
					&& map->map_char[i][j] != '1')
				return (0);
		}
	}
	if (map->is_player_in_map != 1)
		return (1);
	return (0);
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
	if (!map_valid_check(&map, -1, -1))
		ft_error(E_MAP_COLSED);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (0);
	map.window = mlx_new_window(map.mlx, 64, 64, "cub3d");
	if (!map.window)
		return (0);
	drow_window(&map);
}
