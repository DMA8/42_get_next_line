/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:11:55 by syolando          #+#    #+#             */
/*   Updated: 2021/11/20 16:40:16 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static void	fill_remainder(char *buff, int	buff_ind, char *remainder)
{
	int	ind;

	if (!buff || !remainder || buff_ind >= strlen_mod(buff))
		return ;
	ind = 0;
	while (buff[buff_ind])
	{
		remainder[ind] = buff[buff_ind];
		ind++;
		buff_ind++;
	}
	remainder[ind] = 0;
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
	free(dest);
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

static int	free_line_if_fd_bad(int nbytes_readed, char *line_to_free)
{
	int	is_a_crash;

	is_a_crash = 0;
	if (nbytes_readed == -1 || nbytes_readed > BUFFER_SIZE)
	{
		free(line_to_free);
		is_a_crash = 1;
	}
	return (is_a_crash);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	int			nbytes_readed;
	char		*next_line;
	static char	remainder[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = gnl_remainder_and_update_it(remainder);
	if (nl_index(next_line) != -1)
		return (next_line);
	nbytes_readed = 1;
	while (nbytes_readed && nbytes_readed != -1)
	{
		nbytes_readed = read(fd, buff, BUFFER_SIZE);
		if (free_line_if_fd_bad(nbytes_readed, next_line))
			break ;
		buff[nbytes_readed] = 0;
		if (nl_index(buff) == -1 && nbytes_readed)
			next_line = ft_strjoin(next_line, buff);
		else
			return (finish_line(next_line, buff, nl_index(buff), remainder));
	}
	return (NULL);
}
