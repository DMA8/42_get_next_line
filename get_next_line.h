/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:12:30 by syolando          #+#    #+#             */
/*   Updated: 2021/11/17 20:00:26 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define MAX_FD 254
# define MAX_BUFFER_SIZE 1000000

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *s);
int		check_inputs_failed(char *dest, char *buff);
void	count_len_for_two_var(int *len1, int *len2, char *dest, char *buff);
int		nl_index(char *str);

#endif