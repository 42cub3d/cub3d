/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:30:46 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/12 17:29:41 by gkwon            ###   ########.fr       */
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

void	reset_buffer(int **buffer)
{
	int	i;
	int	j;

	i = 0;
	while (i < screenHeight)
	{
		j = 0;
		while (j < screenWidth)
		{
			buffer[i][j] = 0;
			j++;
		}
		i++;
	}
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

void	set_pro_attri(t_map *map, t_player *player, t_img *img, t_DDA *dda)
{
	set_player(player);
	map->player = player;
	map->move_speed = 0.1;
	map->rot_speed = 0.3;
	map->img = img;
	map->dda = dda;
	map->dda->pitch = 100;
}
