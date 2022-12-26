/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:37 by sanghyep          #+#    #+#             */
/*   Updated: 2022/12/26 18:52:47 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		current[BUFFER_SIZE + 1];
	int			idx;
	//올바르지 않는 fd, 올바르지 않은 BUFFER_SIZE
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	//read 실패시
	if(read_buff(current, fd) == -1)
		return (NULL);
	idx = 0;
	backup = ft_strdup(current);
	while (!contains_nl(current) || read_buff(current, fd) > 0)
		backup = ft_strjoin(backup, current);
	while(current[idx])
		if(current[idx] == '\n')
			break ;
	return (ft_substr(backup, 0, idx));
}

int	read_buff(char arr[BUFFER_SIZE + 1], int fd)
{
	int	read_result;

	read_result = read(fd, arr, BUFFER_SIZE);
	arr[BUFFER_SIZE] = '\0';
	return read_result;
}

int	contains_nl(char *str)
{
	while (*str)
		if (*str++ == '\n')
			return (1);
	return (0);
}
