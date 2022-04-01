#include "get_next_line.h"

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

char	*ft_strjoin(char *s1, char *s2)
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
	free(s1);
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

//===================================



int is_endl(char *saved)
{
	int index;

	index = 0;
	while (saved[index] != '\0')
	{
		if (saved[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

int endl_index(char *stash)
{
	int i;

	i = 0;
	while (stash[i] != '\0')
	{
		if(stash[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char *get_next_line(int fd)
{
	int bytes;
	char buff[BUFFER_SIZE + 1];
	static char *stash;
	char *line;
	char *ptr;

	while(1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		buff[bytes] = '\0';
		if (bytes == -1)
			return (NULL);
		if (bytes > 0)
		{
			if(!stash)
				stash = ft_strdup(buff);
			else
				stash = ft_strjoin(stash, buff);
			if (is_endl(stash) == 1)
				break ;
		}
		else
		{
			if (!stash)
				return (NULL);
			else
			{
				if (is_endl(stash) == 1)
				{
					line = ft_substr(stash, 0, endl_index(stash) + 1);
					ptr = stash;
					stash = ft_substr(stash, endl_index(stash) + 1, ft_strlen(stash));
					free(ptr);
					return (line);
				}
				else
				{
					line = ft_strdup(stash);
					ptr = stash;
					free(stash);
					stash = NULL;
					return (line);
				}
			}
		}
	}

	line = ft_substr(stash, 0, endl_index(stash) + 1);
	ptr = stash;
	stash = ft_substr(stash, endl_index(stash) + 1, ft_strlen(stash));


	free(ptr);
	return (line);
}




// int main()
// {
// 	int fd;
// 	int i = 5;

// 	fd = open("nl", O_RDONLY);
// 	while(i--)
// 		printf("%s",get_next_line(fd));
// 		//get_next_line(fd);
// }