/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:37 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/04 17:46:12 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*update;
	char		current[BUFFER_SIZE + 1];
	char		*line;

	//fd, buffersize, read 검증 
	//printf(":::gnl called:::\n");
	//if(!backup)
	//	printf(":::backuplen = %zu backup = %s:::\n", ft_strlen(backup), backup);
	if(!validate(fd, read_buff(current, fd), backup))
		return (NULL);
	add_or_make_backup(&backup, current);
	//printf(":::backuplen = %zu backup = %s:::\n", ft_strlen(backup), backup);
	while(!contains_nl(current) && !contains_nl(backup) && read_buff(current, fd) > 0)
		add_or_make_backup(&backup, current);
	line = get_one_line(backup);
	if(!line)
	{
		if(!backup)
			free(backup);
		return (NULL);
	}
	update = ft_substr(backup, ft_strlen(line), ft_strlen(backup) - ft_strlen(line));
	if(!update)
	{
		free(backup);
		free(line);
		return (NULL);
	}
	free(backup);
	backup = update;
	//printf(":::backuplen = %zu backup = %s:::\n", ft_strlen(backup), backup);
	return line;
}

//int	validate(int fd, int read_result, char *backup)
//{
//	if(fd < 0 || BUFFER_SIZE < 1)
//		return (0);
//	if(read_result == 0 || read_result == -1)
//	{
//		if(backup)
//			free(backup);
//		return (0);
//	}
//	return (1);
//}

int	validate(int fd, int read_result, char *backup)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	//printf("read_result = %d\n", read_result);
	if (read_result == -1)
	{
		if(backup)
			free(backup);
		return (0);
	}
	if (read_result == 0)
	{
		if(backup)
		{
			if(*backup)
				return (1);
			else
			{
				free(backup);
				return (0);
			}
		}
		return (0);
	}
	return (1);
}

char	*get_one_line(char *backup)
{
	char	*line;
	int		idx;

	idx = 0;
	while(backup[idx] && backup[idx] != '\n')
		idx++;
	line = ft_substr(backup, 0, ++idx);
	if(!line)
		return (NULL);
	return (line);
}

char	*add_or_make_backup(char **backup, char current[BUFFER_SIZE + 1])
{
	char	*updated;

	if(!*backup)
	{
		*backup = ft_strjoin("",current);
		if(!*backup)
			return (NULL);
	}
	else
	{
		updated = ft_strjoin(*backup, current);
		if(!updated)
			return (NULL);
		free(*backup);
		*backup = updated;
	}
	return (*backup);
}

int	read_buff(char current[BUFFER_SIZE + 1], int fd)
{
	int	read_result;

	read_result = read(fd, current, BUFFER_SIZE);
	if (read_result <= 0)
	{
		current[0] = '\0';
		return (read_result);
	}
	current[read_result] = '\0';
	return (read_result);
}
