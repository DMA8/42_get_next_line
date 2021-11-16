#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(const char *s)
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


	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
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

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')

		return ((char *)(s + i));
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*ans;
	int		len_src;
	int		ind;

	ind = 0;
	len_src = ft_strlen(str);
	ans = (char *)malloc((len_src + 1) * sizeof(char ));
	if (!ans)
		return (NULL);
	while (ind < len_src)
	{
		ans[ind] = str[ind];
		ind++;
	}
	ans[ind] = 0;
	free(str);
	return (ans);
}

char	*ft_strlcat_ptr_stop(char *dst, const char *src, const char *stop_pointer)
{
	int		len_dst;
	int		ind;
	char	*tmp;

	tmp = dst;
	if (!dst)
		dst = (char *)malloc(stop_pointer - src + 1);
	else
		dst = (char *)malloc(ft_strlen(dst) + stop_pointer - src + 1);
	ind = -1;
	while (tmp[ind++])
		dst[ind] = tmp[ind];
	len_dst = ft_strlen(tmp);
	free(tmp);
	ind = -1;
	while (src[ind++] && src[ind] != '\n')
		dst[len_dst + ind] = src[ind];
	dst[len_dst + ind] = '\n';
	dst[len_dst + ind + 1] = 0;
	ind++;
	return (dst);
}
