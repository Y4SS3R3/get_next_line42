#include "get_next_line.h"

static  char *set_line(char *save)
{
	int		i;
	char	*result;

	i = 0;
	while(save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	result = malloc(i + 1);
	if (result == NULL)
		return (NULL);
	result = ft_substr(save, 0, i);
	return (result);
}
static char *prepare_next(char *tmp)
{
	int	i;
	char	*result;

	i = 0;
	while(tmp[i] && tmp[i] != '\n')
		i++;
	if(tmp[i] == '\n')
		i++;
	result = ft_strdup(tmp + i);
	if (result == NULL)
		return (NULL);
	return (result);
}
static char *fill_the_line(char *save, int fd)
{
	int	rbytes;
	char	*buffer;
	char		*tmp;

	rbytes = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (!ft_strchr(save, '\n') && rbytes)
	{
		rbytes = read(fd, buffer, BUFFER_SIZE);
		if (rbytes == 0)
			break ;
		if (rbytes == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[rbytes] = '\0';
		tmp = save;
		save = ft_strjoin(tmp, buffer);
	}
	free(buffer);
	return (save);
}

char *get_next_line(int fd)
{
	static char *save;
	char 		*line;

	line = NULL;
	if (fd < 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	save = fill_the_line(save, fd);
	if (save == NULL)
	{
		free(save);
		return (NULL);
	}
	line = set_line(save);
	if (*line == 0)
		return (NULL);
	save = prepare_next(save);
	return (line);
}
// int main()
// {
// 	int fd = open("hh1.txt", O_RDONLY);
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// }
