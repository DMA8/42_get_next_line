#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *s);
int		check_inputs_failed(char *dest, char *buff);
void	init_finish_line(int *len1, int *len2, char *dest, char *buff);
#endif