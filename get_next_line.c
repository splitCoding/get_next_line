/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:37 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/02 21:47:16 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		current[BUFFER_SIZE + 1];
	char		*line;
	char		*newbackup;
	int			idx;
	//올바르지 않는 fd, 올바르지 않은 BUFFER_SIZE
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	//read 실패시
	if(read_buff(current, fd) <= 0)
		return (NULL);
	if(!backup)
		backup = ft_strdup(current);
	else
	{
		newbackup = ft_strjoin(backup, current);
		free(backup);
		backup = newbackup;
	}
	if(!backup)
		return (NULL);
	while(!contains_nl(current))
	{
		if(read_buff(current, fd) < 1)
			break;
		newbackup = ft_strjoin(backup, current);
		free(backup);
		if(!newbackup)
			return (NULL);
		backup = newbackup;
		//printf("::::added backup = |%s|\n", backup);
	}
	idx = 0;
	while(backup[idx] && backup[idx] != '\n')
		idx++;
	line = ft_substr(backup, 0, ++idx);
	if(!line)
	{
		free(backup);
		return (NULL);
	}
	//printf("::::final backup = |%s|\n", backup);
	//printf("::::print line = |%s|\n", line);
	newbackup = ft_substr(backup, idx, ft_strlen(backup) - idx + 1);
	free(backup);
	if(!newbackup)
		return (NULL);
	backup = newbackup;
	return (line);
}

int	read_buff(char arr[BUFFER_SIZE + 1], int fd)
{
	int	read_result;
	int idx;

	idx = 0;
	read_result = read(fd, arr, BUFFER_SIZE);
	arr[read_result] = '\0';
	return read_result;
}

int	contains_nl(char *str)
{
	while (*str)
		if (*str++ == '\n')
			return (1);
	return (0);
}
