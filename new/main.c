/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghyep <sanghyep@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:08:08 by sanghyep          #+#    #+#             */
/*   Updated: 2023/01/03 17:35:05 by sanghyep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main ()
{
	int	fd;
	fd = open("./test.txt", O_RDONLY);
	
	char *line = get_next_line(fd);
	printf("get_next_line = %s\n", line);
	//while(line = get_next_line(fd))
	while(line)
	{
		line = get_next_line(fd);
		printf("get_next_line = %s\n", line);
	}
}