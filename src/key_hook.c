/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 04:08:00 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/11 14:24:19 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	exit_game(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	exit(0);
}

//int	press_key(int key_code, t_map *map)
//{
//	if (key_code == KEY_ESC)
//		exit_game(map);
//	if (key_code == KEY_W)
//		move(map, KEY_W);
//	if (key_code == KEY_A)
//		move(map, KEY_A);
//	if (key_code == KEY_S)
//		move(map, KEY_S);
//	if (key_code == KEY_D)
//		move(map, KEY_D);
//	return (0);
//}

void	next_mom(t_map *map, unsigned int *x, unsigned int *y, int key)
{
	*x = map->player->pos_x;
	*y = map->player->pos_y;
	if (key == KEY_W)
		(*y)--;
	else if (key == KEY_S)
		(*y)++;
	else if (key == KEY_A)
		(*x)--;
	else if (key == KEY_D)
		(*x)++;
}

void	move(t_map *map, int key)
{
	unsigned int	nx;
	unsigned int	ny;

	next_mom(map, &nx, &ny, key);
	if (map->map_char[ny][nx] != '1' && map->map_char[ny][nx] != 'E')
	{
		map->map_char[(int)map->player->pos_y][(int)map->player->pos_x] = '0';
		map->map_char[ny][nx] = 'P';
		map->player->pos_x = nx;
		map->player->pos_y = ny;
		draw_map(map);
	}
}
