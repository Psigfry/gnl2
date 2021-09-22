/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psigfry <psigfry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:55:57 by psigfry           #+#    #+#             */
/*   Updated: 2021/09/17 13:55:57 by psigfry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_ending(char *line, char **text)
{
	int		i;
	int		j;
	char	*tmp;

	if (!*text)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	free(line);
	if (!ft_strchr(*text, '\n'))
	{
		line = ft_substr(*text, 0, ft_strlen(*text));
		free(*text);
		*text = NULL;
		return (line);
	}
	i = ft_strlen(*text);
	j = ft_strlen(ft_strchr(*text, '\n'));
	line = ft_substr(*text, 0, i - j + 1);
	tmp = *text;
	*text = ft_substr(ft_strchr(*text, '\n'), 1, j - 1);
	free(tmp);
	printf("%s", line);
	return (line);
}

static void	ft_buffer(int fd, char *buff, char **text)
{
	int		i;
	char	*tmp;

	if(!*text || ft_strchr(*text, '\n'))
	{
		i = read(fd, buff, BUFF_SIZE);
		while(i)
		{
			buff[i] = '\0';
			if(*text)
			{
				tmp = *text;
				*text = ft_strjoin(*text, buff);
				free(tmp);
			}
			else
				*text = ft_substr(buff, 0, i);
			if(ft_strchr(buff, '\n'))
				break;
			i = read(fd, buff, BUFF_SIZE);
		}
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*text;

	line = malloc(BUFF_SIZE + 1);
	buff = malloc(BUFF_SIZE + 1);
	if(BUFF_SIZE < 1 || !fd || !line || !buff
		|| read(fd,0,0) == -1)
	{
		free(buff);
		free(line);
		line = NULL;
		return 0;
	}
	ft_buffer(fd, buff, &text);
	return (ft_ending(line, &text));
}

int	main(void)
{
	int	fd;

	fd = open("a.txt", O_RDONLY);
	get_next_line(fd);
	return 0;
}