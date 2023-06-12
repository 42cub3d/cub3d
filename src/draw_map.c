/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/06/12 19:32:49 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_map(t_map *map)
{
	int				c_color;
	int				f_color;	
	unsigned int	w;
	unsigned int	h;

	//mlx_put_image_to_window(map->mlx, map->window, map->img->n_wall, 0, 0);
	h = 6;
	c_color = create_rgb(map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
	f_color = create_rgb(map->floor_color[0], map->floor_color[1], map->floor_color[2]);
	while (h < map->y + 6)
	{
		w = 0;
		while (w < ft_strlen(map->map_char[h]))
		{
			if (map->map_char[h][w] == '1') // ceiling
				mlx_pixel_put(map->mlx, map->window, h, w, c_color);
			else if (map->map_char[h][w] == '0') // floor
				mlx_pixel_put(map->mlx, map->window, h, w, f_color);
			w++;
		}
		h++;
	}
}

void	init_img(t_map *map)
{
	int		img_w;
	int		img_h;
	char	*str;

	str = map->img->w_wall;
	map->img->w_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
	str = map->img->n_wall;
	map->img->n_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
	str = map->img->s_wall;
	map->img->s_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
	str = map->img->e_wall;
	map->img->e_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
}
