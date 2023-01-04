/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:40 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/04 21:14:40 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
int		validate(int fd, int read_result, char *backup);
int		read_buff(char current[BUFFER_SIZE + 1], int fd);
int		contains_nl(char *str);
char 	*add_or_make_backup(char **backup, char current[BUFFER_SIZE + 1]);
char	*get_one_line(char *backup);

char	*ft_strjoin(char const *s1, const char s2[BUFFER_SIZE + 1]);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif