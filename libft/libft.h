/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:29:16 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 17:53:55 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>

typedef enum e_bool
{
	T_FALSE,
	T_TRUE
}				t_bool;

void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *str, char c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

int				ft_atoi(const char *str);

int				ft_isalpha(int str);
int				ft_isalnum(int str);
int				ft_isdigit(int str);
int				ft_isprint(int str);
int				ft_isascii(int str);

unsigned int	ft_strlcat(char *dest, const char *src, size_t size);
unsigned int	ft_strlcpy(char *dest, const char *src, size_t size);
char			*ft_strnstr(const char *str, const char *to_find, size_t size);
char			*ft_strdup(char *src);
char			*ft_strchr(const char *str, int ch);
char			*ft_strrchr(const char *str, int ch);
void			*ft_calloc(size_t nmemb, size_t size);

int				ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				ft_tolower(int c);
int				ft_toupper(int c);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;
#endif