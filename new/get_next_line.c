#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"



static int	nl_index(char *str)
{
	int	ind;

	ind = 0;
	while (str[ind])
	{
		if (str[ind] == '\n')
			return (ind);
		ind++;
	}
	return (-1);
}

static void	fill_remainder(char *buff, int	buff_ind, char *remainder)
{
	int	ind;

	ind = 0;
	while (buff[buff_ind])
	{
		remainder[ind] = buff[buff_ind];
		ind++;
		buff_ind++;
	}
	remainder[ind] = 0;
}

static char	*finish_line(char *dest, char *buff, int nbytes, char *remainder)
{
	int		ind;
	int		len1;
	int		len2;
	char	*newline;

	if (check_inputs_failed(dest, buff))
		return (NULL);
	init_finish_line(&len1, &len2, dest, buff);
	ind = -1;
	if (nbytes == -1)
		return (dest);
	if (nbytes > len2)
		nbytes = len2;
	newline = (char *)malloc(len1 + nbytes + 1);
	if (!newline)
		return (NULL);
	while (++ind < len1)
		newline[ind] = dest[ind];
	ind = -1;
	while (++ind <= nbytes)
		newline[len1 + ind] = buff[ind];
	newline[len1 + nbytes + 1] = 0;
	free(dest);
	fill_remainder(buff, ind, remainder);
	return (newline);
}

static char	*gnl_remainder_and_update_it(char *remainder)
{
	int		nl_ind;
	int		ind;
	char	*line;
	int		ind2;

	ind = -1;
	ind2 = 0;
	if (!remainder)
		return (NULL);
	nl_ind = nl_index(remainder);
	if (nl_ind >= 0)
		line = (char *)malloc(nl_ind + 2);
	else
		line = (char *)malloc(ft_strlen(remainder));
	if (nl_ind < 0)
		nl_ind = ft_strlen(remainder);
	while (++ind <= nl_ind)
		line[ind] = remainder[ind];
	line[ind] = 0;
	while (remainder[ind])
		remainder[ind2++] = remainder[ind++];
	while (remainder[ind2])
		remainder[ind2++] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	remainder[BUFFER_SIZE + 1];
	int			nbytes_readed;
	char		*next_line;

	if (fd < 0 || fd > 100)
		return (NULL);
	next_line = gnl_remainder_and_update_it(remainder);
	if (nl_index(next_line) != -1)
		return (next_line);
	nbytes_readed = 1;
	while (nbytes_readed)
	{
		nbytes_readed = read(fd, buff, BUFFER_SIZE);
		buff[nbytes_readed] = 0;
		if (nl_index(buff) == -1 && nbytes_readed)
			next_line = ft_strjoin(next_line, buff);
		else
			return (finish_line(next_line, buff, nl_index(buff), remainder));
	}
	return (NULL);
}
