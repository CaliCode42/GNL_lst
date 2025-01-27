/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:58:18 by tcali             #+#    #+#             */
/*   Updated: 2025/01/27 11:58:32 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*ft_join_free(char *s1, char *s2)
{
	char	*temp;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	if (s1 == NULL)
	{
		temp = ft_strdup(s2);
		return (free(s2), temp);
	}
	temp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (temp);
}

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *source)
{
	int		i;
	char	*copy;

	if (!source)
		return (NULL);
	i = 0;
	copy = malloc (sizeof(char) * (ft_strlen(source) + 1));
	if (!copy)
		return (NULL);
	while (source[i])
	{
		copy[i] = source[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*joined;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc (sizeof(char) * (s1_len + s2_len + 1));
	if (!joined)
		return (NULL);
	while (i < s1_len)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i - s1_len < s2_len)
	{
		joined[i] = s2[i - s1_len];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}
