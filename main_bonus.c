/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:50:42 by tcali             #+#    #+#             */
/*   Updated: 2025/01/27 11:52:34 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int 	fd1;
	int		fd2;
	int		fd3;
	char	*line;
	int		count1;
	int		count2;
	int		count3;
	int		maxline;

	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	// Ouvre trois fichiers différents
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("Error opening files");
		return (1);
	}
	printf("File '%s' opened successfully.\n\n", argv[1]);
	printf("File '%s' opened successfully.\n\n", argv[2]);
	printf("File '%s' opened successfully.\n\n", argv[3]);
	maxline = 10;
	count1 = 0;
	count2 = 0;
	count3 = 0;
	// Lecture alternée sur les trois fichiers
	printf("===== Lecture alternée =====\n");
	while (maxline-- > 0)
	{
		line = get_next_line(fd1);
		if (line == NULL)
		{
			printf("\nEnd of file or error detected.\n");
			break ;
		}
		count1++;
		printf("[%d]: %s\n", count1, line);
		if (line)
		{
			free(line);
			line = NULL;
		}
		
		line = get_next_line(fd2);
		if (line == NULL)
		{
			printf("\nEnd of file or error detected.\n");
			break ;
		}
		count2++;
		printf("[%d]: %s\n", count2, line);
		if (line)
		{
			free(line);
			line = NULL;
		}

		line = get_next_line(fd3);
		if (line == NULL)
		{
			printf("\nEnd of file or error detected.\n");
			break ;
		}
		count3++;
		printf("[%d]: %s\n", count3, line);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (maxline <= 0)
		printf("Error: Potential infinite loop detected.\n");
	// Fermeture des fichiers
	close(fd1);
	close(fd2);
	close(fd3);
	printf("File closed. Total lines read fd1: %d\n", count1);
	printf("File closed. Total lines read fd2: %d\n", count2);
	printf("File closed. Total lines read fd3: %d\n", count3);
	return (0);
}
