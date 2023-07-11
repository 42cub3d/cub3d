/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:01:47 by subcho            #+#    #+#             */
/*   Updated: 2023/07/11 17:06:14 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	drow_window(t_map *map)
{
	(void)map;
	//init_img(map);
	set_texture(map);
	//draw_map(map);
	mlx_loop_hook(map->mlx, raycasting, map);
	mlx_hook(map->win, X_EVENT_KEY_PRESS, 0, press_key, map);
	mlx_hook(map->win, X_EVENT_KEY_EXIT, 0, exit_game, map);
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
	while(++i < (int)map->x + 6)
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
	expand_map = malloc(sizeof(char *) * (map->x + 2) + 1);
	map->max_map_line = find_longest_line(map);

	expand_map[0] = malloc(sizeof(char) * map->max_map_line + 3);
	ft_memset(expand_map[0], 'x', map->max_map_line + 3);
	expand_map[0][map->max_map_line + 2] = 0;

	expand_map[map->x + 1] = malloc(sizeof(char) * map->max_map_line + 3);
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
	while(++i < (int)map->x)
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
						if (i + x < 0 || j + y < 0 || (x == 0 && y == 0) || expanded_map[i + x][j + y] == 0 || j + y == (int)map->x + 2)
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
	while (i < map->x)
	{
		j = 0;
		while (map->map_char[i + std][j] != '\0')
		{
			if (map->map_char[i + std][j] == 'N' || map->map_char[i + std][j] == 'S' ||
				map->map_char[i + std][j] == 'E' || map->map_char[i + std][j] == 'W')
			{
				map->player->pos_x = i + 0.5;
				map->player->pos_y = j + 0.5;
				map->is_player_in_map = 1;
				map->map_char[i + std][j] = '0';
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

void print_map(t_map *map)
{
	int i;

	i = 0;
	while (map->map_char[i])
		printf("%s\n", map->map_char[i++]);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_DDA		dda;
	t_draw_info	draw_info;
	t_img		img;

	set_player(&player);
	map.player = &player;
	map.move_speed = 0.5;
	map.rot_speed = 0.3;
	map.img = &img;
	map.dda = &dda;
	map.dda->pitch = 100;
	map.draw_info = &draw_info;

	if (!*(++argv) || argc == 1)
		return (0);
	if (!valid_argv(argv))
		ft_error(E_MAP_VAL);
	map.fd = open(*(argv), O_RDONLY);
	if (map.fd <= 0)
		ft_error(E_FD);
	init_map(&map, map.fd, 0);
	search_arg(&map, map.x -1, 0);
	map_valid_check(&map, 6, -1);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (0);
	map.win = mlx_new_window(map.mlx, screenWidth, screenHeight, "cub3d");
	if (!map.win)
		return (0);
	map.map_char += 6;
	print_map(&map);
	drow_window(&map);
}
