/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:08:31 by subcho            #+#    #+#             */
/*   Updated: 2023/05/15 22:23:08 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <../minilibx/mlx.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define E_MAP_VAL "MAP ELEMENT IS NOT SUPOSSED TO BE"
# define E_FD "MAP OEPN FAILED"
# define PARSINGERR "PARSING FAILED"
# define E_MAP_COLSED "MAP IS NOT COLSED"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_player
{
	unsigned int	x;
	unsigned int	y;
	char			direction;
}					t_player;

typedef struct s_img
{
	void			*w_wall;
	void			*n_wall;
	void			*e_wall;
	void			*s_wall;
}					t_img;

typedef struct s_map
{
	void			*mlx;
	void			*window;
	int				fd;
	unsigned int	y;
	struct s_player	player;
	char			**map_argv;
	char			**map_char;
	bool			is_player_in_map;
	struct s_img	*img;
	int				floor_color[3];
	int				ceiling_color[3];
}					t_map;

/* ===============src=============== */

void	ft_error(char *strerr);
void	draw_map(t_map *map, unsigned int h);
void	init_img(t_map *map);
int		exit_game(t_map *map);
int		press_key(int key_code, t_map *map);
void	next_mom(t_map *map, unsigned int *x, unsigned int *y, int key);
void	move(t_map *map, int key);
void	drow_window(t_map *map);
int		valid_argv(char **argv);
int		map_valid_check(t_map *map, unsigned int i, unsigned int j);
int		init_arg(t_map *map, int i);
void	init_map(t_map *map, int fd, int cnt);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
