/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_b.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:55:35 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 09:14:50 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_B_H
# define GET_NEXT_LINE_B_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	*ft_calloc_b(int count);
void	free_string_b(char **string);

int		nl_len(char *str, int redirect);
char	*ft_strdup_b(char *s1, int x);
char	*ft_strjoin_b(char *s1, char *s2);
char	*build_line(char *buffer, char *line);
char	*read_to_line(char *buffer, char *s_line, int read_len);
char	*get_next_line(int fd);
char	*get_the_line(char *line);
char	*get_left_overs(char *str);

#endif