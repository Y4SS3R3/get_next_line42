/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:14:18 by ymassiou          #+#    #+#             */
/*   Updated: 2023/12/04 15:19:27 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*set_line(char *save)
{
	ssize_t	i;
	char	*result;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	result = ft_substr(save, 0, i);
	return (result);
}

static char	*prepare_next(char *save)
{
	ssize_t	i;
	char	*result;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	result = ft_strdup(save + i);
	free(save);
	return (result);
}

static char	*fill_the_line(char *save, char *buffer, int fd)
{
	ssize_t	rbytes;

	rbytes = 1;
	while (!ft_strchr(save, '\n') && rbytes)
	{
		rbytes = read(fd, buffer, BUFFER_SIZE);
		if (rbytes == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[rbytes] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	if (save && save[0] == '\0')
	{
		free(save);
		return (NULL);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	save[fd] = fill_the_line(save[fd], buffer, fd);
	line = set_line(save[fd]);
	save[fd] = prepare_next(save[fd]);
	return (line);
}
// int main()
// {
// 	int fd = open("hh1.txt", O_RDONLY);
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// }
