/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:09:57 by brandebr          #+#    #+#             */
/*   Updated: 2023/07/18 19:06:12 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clear_buffer(char *buffer, char *line)
{
	int	i;
	int	j;
	char	*willy;

	i = ft_strlen(line);
	j = ft_strlen(buffer);
	if (j - i <= 0)
	{
		free(buffer);
		return (NULL);
	}
	willy = malloc(j - i + 1);
	if (!willy)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while(buffer[i] != '\0')
	{
		willy[j] = buffer[i];
		j++;
		i++;
	}
	willy[j] = '\0';
	free(buffer);
	return (willy);
}

static char	*read_file(int fd)
{
	char	*store;
	char	*warehouse;
	int		bytes_read;

	warehouse = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	store = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!store)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, store, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(store);
			return (NULL);
		}
		store[bytes_read] = '\0';
		warehouse = ft_strjoin(warehouse, store); // Si strjoin 
	}
	free(store);
	return (warehouse);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char)); // whileque guardar 
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] != '\0')
		line[i++] = '\n';
	line[i] = '\0';
	return line;
}

char *get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	int		i;
	int		j;
	char 		*temp;

	i = 0;
	j = 0;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer || !ft_strchr(buffer, '\n'))
		buffer = read_file(fd);
	if (!buffer)
		return NULL;
	line = get_line(buffer);
	if (!line)
		return NULL;
	if (buffer)
		buffer = clear_buffer(buffer, line);
	return line;
}
/*

int main(void)
{
	char *line;
	int fd;

	fd = open("./fsoares/variable_nls.txt", O_RDONLY);
		line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return 0;
}
*/
/*
int	main(void)
{
	char	*line;
	char	fd;
	//int	i = 0;

    fd = open("file.txt", O_RDONLY);
	//line =  get_line(&fd);
	line =  get_next_line(fd);
    // line = read_file(fd);
    printf("%s", line);
    close(fd);
    return 0;
}
*/
/*
// join and free
char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

// delete line find
char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	// line == buffer
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

// take line for return
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	// if no line return NULL
	if (!buffer[i])
		return (NULL);
	// go to the eol
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// malloc to eol
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	// line = buffer
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	// if eol is \0 or \n, replace eol by \n
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	// malloc if res dont exist
	if (!res)
		res = ft_calloc(1, 1);
	// malloc buffer
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		// while not eof read
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		// 0 to end for leak
		buffer[byte_read] = 0;
		// join and free
		res = ft_free(res, buffer);
		// quit if \n find
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	// error handling
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
*/
/*
char	*get_line(char *buffer)
{
	char	*line;
	int	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = -1;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[++i] = '\n';
	return (line);
}

char	*next_line(char *buffer)
{
	int	i;
	int	j;
	char	*line;

	i = 0;
	while (buffer [i] && buffer[i] != '\n')
		i++;
	if (!buffer)
	{
		free(buffer);
		return (NULL);

	}
	line =ft_calloc((ft_strlen(buffer) -i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}


char	*join_n_free(char *buffer, char *buf)
{
	char	*aux;

	aux = ft_strjoin(buffer, buf);
	free(buffer);
	return (aux);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int	bytes_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char)) ;
	bytes_read = 1;
	whivimle (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;// ?
		res = join_n_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static	char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer =  next_line(buffer);
	return (line);
}*/
/*
int	main(void)
{
	int	fd;
	char	buf[256];
	int	chars_read;

	fd = open("file.txt", O_RDONLY);
	while ((chars_read = read(fd, buf, 25)))
	{
		buf[chars_read] = '\0';
		printf("buf: %s\n", buf);
	}
	return (0);
}*/
/*

fd = open("file.txt", O_RDWR | O_CREAT, O_APPEND);
dup2(fd, 1);
printf("%d", fd);
write(1, "hello", 5);
*/
