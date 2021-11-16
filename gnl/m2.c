#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *str);
#define size_buff 1

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

	len1 = ft_strlen(dest);
	len2 = ft_strlen(buff);
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
	fill_remainder(buff, ind, remainder);
	return (newline);
}
static char	*get_line_from_remainder_and_update_it(char *remainder)
{
	int		nl_ind;
	int		ind;
	char	*line;
	int		ind2;

	ind = -1;
	ind2 = 0;
	nl_ind = nl_index(remainder);
	if (nl_ind >= 0)
		line = (char *)malloc(nl_ind + 1);
	else
		line = (char *)malloc(ft_strlen(remainder));
	if (nl_ind < 0)
		nl_ind = ft_strlen(remainder);
	while (++ind <= nl_ind)
		line[ind] = remainder[ind];
	while (remainder[ind])
		remainder[ind2++] = remainder[ind++];
	while (remainder[ind2])
		remainder[ind2++] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	char		buff[size_buff + 1];
	static char remainder[size_buff + 1];
	int			nbytes_readed;
	char		*next_line;

	next_line = ft_strdup(get_line_from_remainder_and_update_it(remainder));
	nbytes_readed = 1;
	while (nbytes_readed)
	{
		nbytes_readed = read(fd, buff, size_buff);
		buff[nbytes_readed] = 0;
		if (nl_index(buff) == -1 && nbytes_readed)
			next_line = ft_strjoin(next_line, buff);
		else
			return (finish_line(next_line, buff, nl_index(buff), remainder));
	}
	return (next_line);
}

int main()
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));
	printf("ANSWER: %s",get_next_line(fd));




}