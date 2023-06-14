/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:01:47 by subcho            #+#    #+#             */
/*   Updated: 2023/06/14 15:56:35 by subcho           ###   ########.fr       */
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

int	map_valid_check(t_map *map, unsigned int std, unsigned int j)
{
	unsigned int	i;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (map->map_char[i + std][j] != '\n' && map->map_char[i + std][j] != '\0')
		{
			if ((i == 0 || i == map->y - 1) || (j == 0 || j == ft_strlen(map->map_char[i + std]) - 1))
				if (map->map_char[i + std][j] != '1')
					return (1);
			if (map->map_char[i + std][j] == 'N' ||
				map->map_char[i + std][j] == 'S' ||
				map->map_char[i + std][j] == 'E' ||
				map->map_char[i + std][j] == 'W')
			{
				map->player.x = j;
				map->player.y = i + std;
				map->is_player_in_map = 1;
			}
			else if (map->map_char[i + std][j] != '\n' && map->map_char[i + std][j] != '0'
					&& map->map_char[i + std][j] != '1')
				return (0);
			j++;
		}
		i++;
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
	search_arg(&map, map.y -1, 0);
	if (map_valid_check(&map, 6, -1))
		ft_error(E_MAP_COLSED);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (0);
	map.window = mlx_new_window(map.mlx, 1600, 900, "cub3d");
	if (!map.window)
		return (0);
	drow_window(&map);
}
