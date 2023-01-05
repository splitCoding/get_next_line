/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:06:37 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/05 14:46:52 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*update;
	char		now[BUFFER_SIZE + 1];
	char		*line;

	if (!validate(fd, read_buff(now, fd), backup))
		return (backup = NULL);
	backup = add_or_make_backup(&backup, now);
	while (!contains_nl(now) && !contains_nl(backup) && read_buff(now, fd) > 0)
		if (!backup || !add_or_make_backup(&backup, now))
			return (backup = NULL);
	line = get_one_line(backup);
	if (!line)
		return (backup = NULL);
	update = ft_substr(backup, strlen(line),
			strlen(backup) - strlen(line) + 1);
	free(backup);
	if (!update)
	{
		free(line);
		return (backup = NULL);
	}
	backup = update;
	return (line);
}

char	*add_or_make_backup(char **backup, char current[BUFFER_SIZE + 1])
{
	char	*updated;

	if (!*backup)
		*backup = ft_strjoin("", current);
	else
	{
		updated = ft_strjoin(*backup, current);
		free(*backup);
		*backup = updated;
	}
	return (*backup);
}

int	validate(int fd, int read_result, char *backup)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (read_result == -1)
	{
		if (backup)
			free(backup);
		return (0);
	}
	if (read_result == 0)
	{
		if (!backup)
			return (0);
		if (!*backup)
		{
			free(backup);
			return (0);
		}
		return (1);
	}
	return (1);
}

char	*get_one_line(char *backup)
{
	char	*line;
	int		idx;

	idx = 0;
	if (!backup)
		return (NULL);
	while (backup[idx] && backup[idx] != '\n')
		idx++;
	line = ft_substr(backup, 0, ++idx);
	if (!line)
	{
		free(backup);
		return (NULL);
	}
	return (line);
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
