
# define BUFFER_SIZE 42
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	joined_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		joined_str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		joined_str[j] = s2[i];
		j++;
		i++;
	}
	joined_str[j] = '\0';
	return (joined_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (ft_strlen(s) < start)
	{
		sub_str = malloc(sizeof(char));
		sub_str[0] = '\0';
		return (sub_str);
	}
	s_len = ft_strlen(s + start);
	if (s_len < len)
		len = s_len;
	sub_str = (char *)malloc(len + 1);
	if (!sub_str)
		return (NULL);
	while (i < len)
	{
		sub_str[i] = s[start];
		start++;
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

int endl_indx(char *saved)
{
	int index;

	index = 0;
	while (saved[index] != '\0')
	{
		if (saved[index] == '\n')
			return (index);
		index++;
	}
	return (-1);
}



char	*ft_strdup(const char *src)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(ft_strlen(src) + 1);
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char *get_next_line(int fd)
{
	int bytes;
	char buff[BUFFER_SIZE + 1];
	static char *saved;
	char *line;
	int endl;
	
	while (1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			return (NULL);
		}
		if (bytes == 0)
			??????????
		buff[BUFFER_SIZE] = '\0';
		if (!saved)
			saved = ft_strdup(buff);
		else
			saved = ft_strjoin(saved, buff);
		endl = endl_indx(saved);
		if (endl != -1)
			break ;
	}
	line = ft_substr(saved, 0, endl + 1);
	saved = ft_substr(saved, endl + 1, ft_strlen(saved));
	return (line);
}




int main()
{
	int fd;
	int i = 55;

	fd = open("text.txt", O_RDONLY);
	while(i--)
		printf(">>>>%s",get_next_line(fd));
}