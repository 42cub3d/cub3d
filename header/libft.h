/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:09:46 by subcho            #+#    #+#             */
/*   Updated: 2023/05/16 16:09:50 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strndup(const char *s1, size_t n);
size_t	ft_strlenlf(const char *s);
char	*get_txt(char *txt, int fd, ssize_t buffer_size);
char	*find_lf_or_eof(char *txt, char *buffer, int fd, ssize_t buffer_size);
int		ft_printf(const char *format, ...);
int		ft_formatch(char c, va_list ap);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putaddress(void *v);
int		ft_putnbr(int n);
int		ft_putunsinednbr(unsigned int n);
int		ft_putlowerhex(unsigned int n);
int		ft_putupperhex(unsigned int n);
int		ft_getaddress(unsigned long long pointer_address);
int		get_total_count(char *str, char c);
int		get_word_count(char *str, char c);
char	*get_word(char *str, int word_count);
char	**free_null(char **result, int total_count);
char	**ft_split(char const *s, char c);
int		get_len(int n);
char	*get_result(int n, char *result, int len, int flag);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

#endif