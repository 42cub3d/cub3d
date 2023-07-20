/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/20 17:41:51 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../header/cub3d.h"

//void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
//{
//	char	*dst;

//	dst = map->minimap.addr + (y * map->minimap.line_len
//			+ x *(map->minimap.bits_per_pixel / 8));
//	printf("addr : %c\n", *(map->minimap.addr));
//	printf("dst : %p\n", dst);
//	printf("color : %d\n", color);
//	*(unsigned int *)dst = color;
//}

//void	pixel_put_while(t_map *map, unsigned int w, unsigned int h,
//	int color)
//{
//	int	x;
//	int	y;

//	x = 0;
//	while (x < map->minimap.pixel_size)
//	{
//		y = 0;
//		while (y < map->minimap.pixel_size)
//		{
//			my_mlx_pixel_put(map, h * map->minimap.pixel_size + x,
//				w * map->minimap.pixel_size + y, color);
//			y++;
//		}
//		x++;
//	}
//}

//void	get_map_line_max(t_map *map)
//{
//	int	w;
//	int	h;
//	int	max;

//	max = -2147483648;
//	h = 0;
//	while (h < (int)map->x)
//	{
//		w = ft_strlen(map->map_char[h]);
//		if (w > max)
//			max = w;
//		h++;
//	}
//	map->max_map_line = max;
//}

//void	set_minimap(t_map *map)
//{
//	int				c_color;
//	int				f_color;
//	unsigned int	w;
//	unsigned int	h;

//	c_color = create_rgb(255, 192, 203);
//	f_color = create_rgb(255, 255, 255);
//	h = 0;
//	while (h < map->x)
//	{
//		w = 0;
//		while (w < ft_strlen(map->map_char[h]))
//		{
//			if (map->map_char[h][w] == '1')
//				pixel_put_while(map, (h - 6), w, c_color);
//			else if (map->map_char[h][w] == '0')
//				pixel_put_while(map, (h - 6), w, f_color);
//			else if (w == map->player->pos_x && h == map->player->pos_y)
//				pixel_put_while(map, (h - 6), w, create_rgb(255, 103, 129));
//			w++;
//		}
//		h++;
//	}
//}

//int	draw_map(t_map *map)
//{
//	get_map_line_max(map);
//	map->minimap.pixel_size = get_pixel_size(map);
//	map->minimap.img = mlx_new_image(map->mlx, map->minimap.pixel_size
//			* map->max_map_line, map->minimap.pixel_size * map->x);
//	map->minimap.addr = mlx_get_data_addr(
//			map->minimap.img, &map->minimap.bits_per_pixel,
//			&map->minimap.line_len, &map->minimap.endian);
//	set_minimap(map);
//	mlx_put_image_to_window(map->mlx, map->win, map->minimap.img, 0, 0);
//	mlx_destroy_image(map->mlx, map->minimap.img);
//	return (0);
//}
