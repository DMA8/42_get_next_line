#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strlcat_ptr_stop(char *dst, const char *src, const char *stop_pointer, char *appendix);

char	*get_next_line(int fd)
{
	char		*buff;
	char		*next_line;
	char		*nl_detector;
	static char	*appendix;

	buff = (char *)malloc(11);
	next_line = (char *)malloc(sizeof(char *));
	nl_detector = NULL;
	if (appendix)
	{
		next_line = ft_strdup(appendix);
		free(appendix);
	}
	while (!nl_detector)
	{
		read(fd, buff, 11);
		nl_detector = ft_strchr(buff, '\n');
		if (nl_detector)
		{
			appendix = ft_strdup(nl_detector + 1);
			next_line = ft_strlcat_ptr_stop(next_line, buff, nl_detector, appendix);
		}
		else
			next_line = ft_strjoin(next_line, buff);
		if (buff[ft_strlen(buff) + 1] == EOF)
			nl_detector = buff;
	}
	nl_detector = NULL;
	return (next_line);
}
int	main()
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
		printf("%s", get_next_line(fd));


}