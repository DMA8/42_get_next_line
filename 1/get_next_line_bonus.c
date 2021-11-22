/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:11:55 by syolando          #+#    #+#             */
/*   Updated: 2021/11/20 16:40:05 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

static void	fill_remainder(char *buff, int	buff_ind, char *remainder)
{
	int		ind;
	//char	*remainder_malloc;

	if (!buff || buff_ind >= strlen_mod(buff))
		return ;
	ind = 0;
	//free(remainder);
	while (buff[buff_ind + ind])
		ind++;
	remainder = (char *)malloc(ind + 1);
	if (!remainder)
		return ;
	ind = 0;
	while (buff[buff_ind])
	{
		remainder[ind] = buff[buff_ind];
		ind++;
		buff_ind++;
	}
	remainder[ind] = 0;
	//remainder = remainder_malloc;
}

static char	*finish_line(char *dest, char *buff, int indx_nl, char *remainder)
{
	int		ind;
	int		len1;
	int		len2;
	char	*newline;

	if (check_inputs_failed(dest, buff))
		return (NULL);
	count_len_for_two_var(&len1, &len2, dest, buff);
	ind = -1;
	if (indx_nl == -1)
		return (dest);
	if (indx_nl > len2)
		indx_nl = len2;
	newline = (char *)malloc(len1 + indx_nl + 2);
	if (!newline)
		return (NULL);
	while (++ind < len1)
		newline[ind] = dest[ind];
	ind = -1;
	while (++ind <= indx_nl)
		newline[len1 + ind] = buff[ind];
	newline[len1 + indx_nl + 1] = 0;
	fill_remainder(buff, ind, remainder);
	return (newline);
}

static char	*gnl_remainder_and_update_it(char *remainder)
{
	int		index_nl;
	int		ind;
	char	*line;
	int		ind2;

	if (!remainder || !remainder[0])
		return (NULL);
	ind = -1;
	ind2 = 0;
	index_nl = nl_index(remainder);
	if (index_nl < 0)
		index_nl = strlen_mod(remainder) - 1;
	line = (char *)malloc(index_nl + 2);
	if (!line)
		return (NULL);
	while (++ind <= index_nl)
		line[ind] = remainder[ind];
	line[ind] = 0;
	while (remainder[ind])
		remainder[ind2++] = remainder[ind++];
	while (remainder[ind2])
		remainder[ind2++] = 0;
	return (line);
}

static int	free_line_if_fd_bad(int nbytes_readed, char *line_to_free, char *remainder)
{
	int	is_a_crash;

	is_a_crash = 0;
	if (nbytes_readed == -1)
	{
		free(line_to_free);
		free(remainder);
		is_a_crash = 1;
	}
	return (is_a_crash);
}

void abiba(char *rem)
{
	char *a;
	a = (char *)malloc(10);
	a[0] = 'A';
	if (rem || !rem)
		rem = a;
}
//изменить 1000
// изменить сам резерв памяти под буффер
#include <stdio.h>
char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	int			nbytes_readed;
	char		*next_li;
	static 	int *remainder[1000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	printf("%d\n", type(remainder[fd]));
	abiba(remainder[fd]);
	next_li = gnl_remainder_and_update_it(remainder[fd]);
	if (nl_index(next_li) != -1)
		return (next_li);
	nbytes_readed = 1;
	while (nbytes_readed && nbytes_readed != -1)
	{
		nbytes_readed = read(fd, buff, BUFFER_SIZE);
		if (free_line_if_fd_bad(nbytes_readed, next_li, remainder[fd]))
			break ;
		buff[nbytes_readed] = 0;
		if (nl_index(buff) == -1 && nbytes_readed)
			next_li = ft_strjoin(next_li, buff);
		else
			return (finish_line(next_li, buff, nl_index(buff), remainder[fd]));
	}
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int main()
{	
	int fd1;
	int	counter;
	counter = 10;
	fd1 = open("text", O_RDONLY);
	char *s;
	while (counter)
	{
		s = get_next_line(fd1);
		printf("%s", s);
		free(s);
		counter--;
	}
}
