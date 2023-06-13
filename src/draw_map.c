/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/06/13 16:24:52 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img_minimap *minimap, int x, int y, int color)
{
	char	*dst;

	dst = minimap->addr + (y * minimap->line_len + x * (minimap->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	pixel_put_while(t_img_minimap *minimap, unsigned int w, unsigned int h, int color)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	size;

	x = 0;
	size = 10;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			my_mlx_pixel_put(minimap, h * size + x, w * size + y, color);
			y++;
		}
		x++;
	}
}

void	set_minimap(t_map *map, t_img_minimap *minimap)
{
	int				c_color;
	int				f_color;
	unsigned int	w;
	unsigned int	h;

	c_color = create_rgb(map->ceiling_color[0], map->ceiling_color[1],
			map->ceiling_color[2]);
	f_color = create_rgb(map->floor_color[0], map->floor_color[1],
			map->floor_color[2]);
	h = 6;
	while (h < map->y + 6)
	{
		w = 0;
		while (w < ft_strlen(map->map_char[h]))
		{
			if (map->map_char[h][w] == '1') // ceiling
				pixel_put_while(minimap, h - 6, w, c_color);
			else if (map->map_char[h][w] == '0') // floor
				pixel_put_while(minimap, h - 6, w, f_color);
			else if (map->map_char[h][w] == 'N')
				pixel_put_while(minimap, h - 6, w, 0x00FFFFFF);
			w++;
		}
		h++;
	}
}

void	draw_map(t_map *map)
{
	t_img_minimap	minimap;

	minimap.img = mlx_new_image(map->mlx, 1000, 500);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel,
			&minimap.line_len, &minimap.endian);
	set_minimap(map, &minimap);
	mlx_put_image_to_window(map->mlx, map->window, minimap.img, 0, 0);
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
