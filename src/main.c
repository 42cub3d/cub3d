/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:01:47 by subcho            #+#    #+#             */
/*   Updated: 2023/06/19 15:22:50 by gkwon            ###   ########.fr       */
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

int	dfs(t_map *map, int x, int y, int pre_x, int pre_y)
{
	int	i;
	int	j;

	if (map->map_visited[y][x] && x == map->first_start_dfs[0] && y == map->first_start_dfs[1])
		return (1);
	if (map->map_visited[y][x])
		return (0);
	map->map_visited[y][x] = 1;
	if (x == pre_x && y == pre_y)
	{
		if (map->map_char[y + 1 + 6][x] == '1')
		{
			if (dfs(map, x, y + 1, 0, 0) == 1)
				return (1);
		}
		else if (map->map_char[y + 6][x + 1] == '1')
		{
			if (dfs(map, x + 1, y, 0, 0) == 1)
				return (1);
		}
		return (0);
	}
	else
	{
		i = -2;
		while (++i < 2)
		{
			j = -2;
			while (++j < 2)
			{
				if (x + i >= 0 && y + j >= 0 && i != j && !(i && j) && y + j < (int)map->y && x + i < (int)ft_strlen(map->map_char[y + 6])
					&& (map->map_char[y + j + 6][x + i] == '1'))
					if (!(x + i == pre_x && y + j == pre_y))
						if (dfs(map, x + i, y + j, x, y) == 1)
							return (1);
			}
		}
	}
	return (0);
}

void	find_first(t_map *map)
{
	int i;
	int j;

	map->first_start_dfs = malloc(sizeof(int) * 2);
	j = -1;
	while (++j < (int)map->y)
	{
		i = -1;
		while (++i < (int)ft_strlen(map->map_char[6 + j]))
		{
			if (map->map_char[6 + j][i] == '1')
			{
				map->first_start_dfs[0] = i;
				map->first_start_dfs[1] = j;
				printf("i : %d, j : %d\n", i, j);
				return ;
			}
		}
	}
	free(map->first_start_dfs);
	map->first_start_dfs = 0;
}

void	map_valid_check(t_map *map, unsigned int std, unsigned int j)
{
	unsigned int	i;

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
	find_first(map);
	if (!(map->first_start_dfs))
		ft_error(E_MAP_VAL);
	if (dfs(map, map->first_start_dfs[0], map->first_start_dfs[1], map->first_start_dfs[0], map->first_start_dfs[1]) == 0)
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
