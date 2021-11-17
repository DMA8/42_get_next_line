/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:11:55 by syolando          #+#    #+#             */
/*   Updated: 2021/11/17 20:25:26 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

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
	count_len_for_two_var(&len1, &len2, dest, buff);
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
	int			nbytes_readed;
	char		*next_li;
	static char	remainder[OPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	next_li = gnl_remainder_and_update_it(remainder[fd]);
	if (nl_index(next_li) != -1)
		return (next_li);
	nbytes_readed = 1;
	while (nbytes_readed && nbytes_readed != -1)
	{
		nbytes_readed = read(fd, buff, BUFFER_SIZE);
		if (nbytes_readed == -1)
			free(next_li);
		buff[nbytes_readed] = 0;
		if (nl_index(buff) == -1 && nbytes_readed)
			next_li = ft_strjoin(next_li, buff);
		else
			return (finish_line(next_li, buff, nl_index(buff), remainder[fd]));
	}
	return (NULL);
}

// int main()
// {
// 	int	fd1;
// 	int	fd2;
// 	int	fd3;
// 	int	fd4;
// 	int	fd5;
// 	int			nbytes_readed;
// 	char		buff[BUFFER_SIZE + 1];

// 	fd1 = open("files/41_with_nl", O_RDONLY);
// 	fd2 = open("files/42_with_nl", O_RDONLY);
// 	fd3 = open("files/43_with_nl", O_RDONLY);
// 	fd4 = open("files/nl", O_RDONLY);
// 	fd5 = open("files/empty", O_RDONLY);
// 	close(fd5);
// 	nbytes_readed = read(fd5, buff, BUFFER_SIZE);

// 	printf("%d\n", fd5);
// 	printf("%d\n", nbytes_readed);

// 	printf("%s", get_next_line(fd5));
// 	printf("fd is: %d %d %d %d\n", fd1, fd2, fd3, fd4);
// 	printf("%s", get_next_line(1000));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(1001));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(1002));
// 	printf("%s", get_next_line(fd3));
// 	printf("%s", get_next_line(1003));
// 	printf("%s", get_next_line(fd4));
// 	printf("%s", get_next_line(1004));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(1005));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(1006));
// 	printf("%s", get_next_line(fd3));
// 	printf("%s", get_next_line(1007));
// 	printf("%s", get_next_line(fd4));
// 	printf("%s", get_next_line(1008));
// }
