/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:30:46 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/22 18:05:13 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_error(char *strerr)
{
	ft_putstr_fd("ERROR : ", 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	set_player(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

void	reset_buffer(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREENHEIGHT)
	{
		j = 0;
		while (j < SCREENWIDTH)
		{
			map->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	check_extension(char *argv, char *ext)
{
	char	**split;
	int		len;

	len = 0;
	split = ft_split(argv, '.');
	while (split[len])
		len++;
	if (!ft_strncmp(ext, "cub", 4) && ft_strchr(split[0], '/'))
		if (!*(ft_strchr(split[0], '/') + 1))
			ft_error(E_EXTENSION);
	if (!ft_strncmp(split[len - 1], ext, ft_strlen(ext) + 1))
	{
		while (len)
			free(split[--len]);
		free(split);
		return (1);
	}
	ft_error(E_EXTENSION);
	return (0);
}

void	set_pro_attri(t_map *map, t_player *player, t_img *img, t_DDA *dda)
{
	set_player(player);
	map->player = player;
	map->move_speed = 0.1;
	map->rot_speed = 0.1;
	map->img = img;
	map->dda = dda;
	map->dda->pitch = 100;
}
