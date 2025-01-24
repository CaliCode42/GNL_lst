/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:09:51 by tcali             #+#    #+#             */
/*   Updated: 2025/01/24 11:04:54 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h" 

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		count;
	int		maxline;

	maxline = 5;
	// Vérifie le nombre d'arguments
	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	count = 0;
	// Ouvre le fichier passé en argument
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	printf("File '%s' opened successfully.\n\n", argv[1]);
	// Lire chaque ligne
	while (maxline-- > 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("\nEnd of file or error detected.\n");
			break ;
		}
		count++;
		printf("[%d]: %s\n", count, line);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (maxline <= 0)
		printf("Error: Potential infinite loop detected.\n");
	// Fermer le fichier
	close(fd);
	printf("File closed. Total lines read: %d\n", count);
	return (0);
}
