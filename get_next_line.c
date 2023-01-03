/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:37 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/03 17:32:37 by sanghyep         ###   ########.fr       */
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
	//더이상 읽을게 없거나 실패시 NULL 반환
		//backup 존재시 free
	if(read_buff(current, fd) <= 0)
	{
		if(backup)
			free(backup);
		return (NULL);
	}
	//backup이 존재하지 않았다면 
	if(backup)
	{
		newbackup = ft_strjoin(backup, current);
		free(backup);
		backup = newbackup;
	}
	else
		backup = ft_strdup(current);
	if(!backup)
		return (NULL);
	while(!contains_nl(current))
	{
		if(read_buff(current, fd) == 0)
		{
			idx = 0;
			while(backup[idx] && backup[idx] != '\n')
				idx++;
			line = ft_substr(backup, 0, ++idx);
			if(!line)
			{
				free(backup);
				return (NULL);
			}
			free(backup);
			return (line);
		}
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
	{
		free(line);
		return (NULL);
	}
	backup = newbackup;
	return (line);
}

int	read_buff(char arr[BUFFER_SIZE + 1], int fd)
{
	int	read_result;
	int idx;
	
	idx = 0;
	read_result = read(fd, arr, BUFFER_SIZE);
	if(read_result == -1)
		read_result = 0;
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

void	make_or_add_backup(char *backup, char current[BUFFER_SIZE + 1])
{
	char	*updated;
	if (!backup)
	{
		backup = ft_strdup(current);
		return ;
	}
	updated = ft_strjoin(backup, current);
	free(backup);
	backup = updated;
}


char	*find_line(char *backup)
{
	char	*line;
	char	*updated;
	int		idx;

	idx = 0;
	if(!backup)
		return (NULL);
	printf(":::before substr:::\n");
	while(backup[idx] && backup[idx] != '\n')
		idx++;
	printf(":::after substr:::\n");
	line = ft_substr(backup, 0, ++idx);
	if(!line)
	{
		free(backup);
		return (NULL);
	}
	updated = ft_substr(backup, idx, ft_strlen(backup) - idx + 1);
	free(backup);
	if(!updated)
	{
		free(line);
		return (NULL);
	}
	backup = updated;
	return (line);
}
