/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:03:03 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/25 15:11:40 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *newl);
void	ft_lstadd_back(t_list **lst, t_list *newl);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t l);
size_t	ft_strlcpy(char *dest, const char *src, size_t l);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_strchcpy(char *dest, char *src, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t l);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t l);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

int		ft_atoi(const char *s);
char	*ft_itoa(int n);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

void	*ft_memset(void *s, int c, size_t l);
void	ft_bzero(void *s, size_t l);
void	*ft_memcpy(void *dest, const void *src, size_t l);
void	*ft_memmove(void *dest, const void *src, size_t l);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t l);
int		ft_memcmp(const void *s1, const void *s2, size_t l);

// ft_printf

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_conversion(va_list args, char format);
int		ft_printstr(char *str);
int		ft_printnbr(int nbr, int *c);
int		ft_printunsigned(unsigned int nbr, int *c);
int		ft_printptr(unsigned long long ptr, int *c);
int		ft_printhex(unsigned long long nbr, char format, int *c);
int		ft_len(unsigned long long nbr);
int		ft_check_error(int value, int check);

#endif