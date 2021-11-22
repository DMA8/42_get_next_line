/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:12:09 by syolando          #+#    #+#             */
/*   Updated: 2021/11/20 15:24:20 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	strlen_mod(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	ind;
	char	*ans;

	len1 = strlen_mod(s1);
	len2 = strlen_mod(s2);
	ind = -1;
	ans = (char *)malloc(len1 + len2 + 1);
	if (!ans)
		return (NULL);
	while (++ind < len1)
		ans[ind] = s1[ind];
	ind = -1;
	while (++ind < len2)
		ans[ind + len1] = s2[ind];
	ans[ind + len1] = 0;
	free(s1);
	return (ans);
}

int	check_inputs_failed(char *dest, char *buff)
{
	int	to_free;

	to_free = 0;
	if (strlen_mod(dest) + strlen_mod(buff) == 0)
	{	
		free(dest);
		to_free = 1;
	}
	return (to_free);
}

void	count_len_for_two_var(int *len1, int *len2, char *dest, char *buff)
{
	*len1 = strlen_mod(dest);
	*len2 = strlen_mod(buff);
}

int	nl_index(char *str)
{
	int	ind;

	ind = 0;
	if (!str || !str[0])
		return(-1);
	while (str[ind])
	{
		if (str[ind] == '\n')
			return (ind);
		ind++;
	}
	return (-1);
}
