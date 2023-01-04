/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:37 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/04 21:14:38 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*prev;
	char		*new;
	char		now[BUFFER_SIZE + 1];
	char		*line;

	if (!validate(fd, read_buff(now, fd), prev))
		return (NULL);
	add_or_make_backup(&prev, now);
	while (!contains_nl(now) && !contains_nl(prev) && read_buff(now, fd) > 0)
		add_or_make_backup(&prev, now);
	line = get_one_line(prev);
	if (!line)
	{
		free(prev);
		return (NULL);
	}
	new = ft_substr(prev, ft_strlen(line), ft_strlen(prev) - ft_strlen(line));
	free(prev);
	if (!new)
	{
		free(line);
		return (NULL);
	}
	prev = new;
	return (line);
}

int	validate(int fd, int read_result, char *backup)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (read_result == -1)
	{
		if (backup)
		{
			free(backup);
			backup = NULL;
		}
		return (0);
	}
	if (read_result == 0)
	{
		if (!backup)
			return (0);
		if (*backup)
			return (1);
		free(backup);
		return (0);
	}
	return (1);
}

char	*get_one_line(char *backup)
{
	char	*line;
	int		idx;

	idx = 0;
	if(!backup)
		return (NULL);
	while (backup[idx] && backup[idx] != '\n')
		idx++;
	line = ft_substr(backup, 0, ++idx);
	if (!line)
		return (NULL);
	return (line);
}

char	*add_or_make_backup(char **backup, char current[BUFFER_SIZE + 1])
{
	char	*updated;

	if (!*backup)
	{
		free(*backup);
		*backup = ft_strjoin("", current);
		if (!*backup)
			return (NULL);
	}
	else
	{
		updated = ft_strjoin(*backup, current);
		if (!updated)
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
