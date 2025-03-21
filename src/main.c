/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:01:47 by subcho            #+#    #+#             */
/*   Updated: 2023/07/22 18:51:39 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	drow_window(t_map *map)
{
	(void)map;
	set_texture(map);
	mlx_loop_hook(map->mlx, raycasting, map);
	mlx_hook(map->win, X_EVENT_KEY_PRESS, 0, press_key, map);
	mlx_hook(map->win, X_EVENT_KEY_EXIT, 0, exit_game, map);
	mlx_loop(map->mlx);
}

bool	check_condition(t_map *map, char **em, int i, int j)
{
	if (i + map->t_i < 0 || j + map->t_j < 0)
		return (1);
	if (i + map->t_i > (int)map->x)
		return (1);
	if (j + map->t_j > (int)ft_strlen(em[i + map->t_i]))
		return (1);
	if (em[i + map->t_i][j + map->t_j] == 0)
		return (1);
	if ((map->t_i == 0 && map->t_j == 0) || em[i + map->t_i] == 0)
		return (1);
	return (0);
}

int	check_closed(t_map *map, char **em, int i, int j)
{
	while (++i < (int)map->x + 2)
	{
		j = -1;
		while (em[i][++j])
		{
			if (em[i][j] == 'x')
			{
				map->t_i = -2;
				while (++map->t_i < 2)
				{
					map->t_j = -2;
					while (++map->t_j < 2)
					{
						if (check_condition(map, em, i, j))
							continue ;
						else if (em[i + map->t_i][j + map->t_j] != '1'
							&& em[i + map->t_i][j + map->t_j] != 'x')
							return (1);
					}
				}
			}
		}
	}
	return (ft_free_expand_map(em, -1));
}

void	map_valid_check(t_map *map, unsigned int std, unsigned int j,
		unsigned int i)
{
	while (++i < map->x)
	{
		j = -1;
		while (map->map_char[i + std][++j] != '\0')
		{
			if (map->map_char[i + std][j] == 'N' || map->map_char[i
				+ std][j] == 'S' ||
				map->map_char[i + std][j] == 'E' || map->map_char[i
					+ std][j] == 'W')
				set_player_attri(map, i, j, std);
			else if (map->map_char[i + std][j] != ' ' && map->map_char[i
					+ std][j] != '\n' && map->map_char[i + std][j] != '0'
					&& map->map_char[i + std][j] != '1')
				ft_error(E_MAP_VAL);
		}
	}
	if (check_closed(map, make_expand_map(map, 0, 0), -1, 0))
		ft_error(E_MAP_COLSED);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_DDA		dda;
	t_draw_info	draw_info;
	t_img		img;

	map.draw_info = &draw_info;
	set_pro_attri(&map, &player, &img, &dda);
	if (!*(++argv) || argc == 1)
		return (0);
	if (!check_extension(*argv, "cub"))
		ft_error(E_MAP_VAL);
	check(&map, argv);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (0);
	map.win = mlx_new_window(map.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	if (!map.win)
		return (0);
	map.map_char += 6;
	drow_window(&map);
}
