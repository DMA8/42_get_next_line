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

static int	free_line_if_fd_bad(int nb_readed, char *line_free, char **rem)
{
	int	is_a_crash;

	is_a_crash = 0;
	if (nb_readed == -1)
	{
		free(line_free);
		free(rem[0]);
		rem[0] = NULL;
		is_a_crash = 1;
	}
	if (nb_readed == -2)
	{
		free(rem[0]);
		rem[0] = NULL;
	}
	return (is_a_crash);
}

static char	*fill_remainder(char *buff, int	buff_ind, char **remainder)
{
	int		ind;
	char	*remainder_malloc;

	if (!buff || buff_ind >= strlen_mod(buff))
		return (NULL);
	ind = 0;
	while (buff[buff_ind + ind])
		ind++;
	remainder_malloc = (char *)malloc(ind + 1);
	if (!remainder_malloc)
		return (NULL);
	ind = 0;
	while (buff[buff_ind])
		remainder_malloc[ind++] = buff[buff_ind++];
	remainder_malloc[ind] = 0;
	remainder[0] = remainder_malloc;
	return (*remainder);
}

static char	*finish_line(char *dest, char *buff, int indx_nl, char **remainder)
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
	*remainder = fill_remainder(buff, ind, remainder);
	free(dest);
	return (newline);
}

static char	*gnl_remainder_and_update_it(char *line, char **remainder)
{
	int		index_nl;
	int		ind;
	int		ind2;

	if (!*remainder)
		return (NULL);
	ind = -1;
	ind2 = 0;
	index_nl = nl_index(remainder[0]);
	if (index_nl < 0)
		index_nl = strlen_mod(*remainder) - 1;
	line = (char *)malloc(index_nl + 2);
	if (!line)
		return (NULL);
	while (++ind <= index_nl)
		line[ind] = *(remainder[0] + ind);
	line[ind] = 0;
	while (*(remainder[0] + ind))
		*(remainder[0] + ind2++) = *(remainder[0] + ind++);
	while (*(remainder[0] + ind2))
		*(remainder[0] + ind2++) = 0;
	if (!remainder[0][0])
		free_line_if_fd_bad(-2, NULL, remainder);
	return (line);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	int			nbytes_readed;
	char		*next_li;
	static char	*rem_m[8193];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_li = (NULL);
	next_li = gnl_remainder_and_update_it(next_li, &rem_m[fd]);
	if (nl_index(next_li) != -1)
		return (next_li);
	nbytes_readed = 1;
	while (nbytes_readed && nbytes_readed != -1)
	{
		nbytes_readed = read(fd, buff, BUFFER_SIZE);
		if (free_line_if_fd_bad(nbytes_readed, next_li, &rem_m[fd]))
			break ;
		buff[nbytes_readed] = 0;
		if (nl_index(buff) == -1 && nbytes_readed)
			next_li = ft_strjoin(next_li, buff);
		else
			return (finish_line(next_li, buff, nl_index(buff), &rem_m[fd]));
	}
	return (NULL);
}
