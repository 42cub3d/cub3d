/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:28:12 by subcho            #+#    #+#             */
/*   Updated: 2023/07/20 17:40:45 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	set_direction_ew(t_map *map, char direction)
{
	if (direction == 'E')
	{
		map->player->dir_x = 0;
		map->player->dir_y = 1;
		map->player->plane_x = 0.66;
		map->player->plane_y = 0;
	}
	if (direction == 'W')
	{
		map->player->dir_x = 0;
		map->player->dir_y = -1;
		map->player->plane_x = -0.66;
		map->player->plane_y = 0;
	}
}

void	set_direction_sn(t_map *map, char direction)
{
	if (direction == 'S')
	{
		map->player->dir_x = 1;
		map->player->dir_y = 0;
		map->player->plane_x = 0;
		map->player->plane_y = -0.66;
	}
	if (direction == 'N')
	{
		map->player->dir_x = -1;
		map->player->dir_y = 0;
		map->player->plane_x = 0;
		map->player->plane_y = 0.66;
	}
}

int	ft_free_expand_map(char **em, int i)
{
	while (em[++i])
		free(em[i]);
	free(em);
	return (0);
}

void	set_player_attri(t_map *map, int i, int j, unsigned int std)
{
	map->player->pos_x = i + 0.5;
	map->player->pos_y = j + 0.5;
	set_direction_ew(map, map->map_char[i + std][j]);
	set_direction_sn(map, map->map_char[i + std][j]);
	if (map->is_player_in_map)
		ft_error(E_MAP_PLAYER);
	map->is_player_in_map = 1;
	map->map_char[i + std][j] = '0';
}
