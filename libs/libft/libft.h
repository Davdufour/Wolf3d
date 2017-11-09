/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 17:22:34 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/13 10:43:21 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 4096

void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putnbrendl(int n);
void				ft_free_tab(char ***tab);
void				checkisvalid(char *buff);
int					iswall(char c);
void				ft_exit(int error, char *message);
char				**ft_strsplit(char const *s, char c);
void				*ft_memalloc(size_t size);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strnew(size_t size);
char				*ft_itoa(int n);
char				*ft_read_file(char *av);
char				*ft_strjoinfree(char const *s1, char const *s2);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
char				*ft_itoa(int n);
double				get_alpha(int shadow, double a);

#endif
