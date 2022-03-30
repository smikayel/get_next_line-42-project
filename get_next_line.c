/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smikayel <smikayel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:49:05 by smikayel          #+#    #+#             */
/*   Updated: 2022/03/30 20:00:47 by smikayel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	where_endline(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i + 1);
		i++;
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

int is_endl(char *stash)
{
	int i;

	i = 0;
	while (stash[i++] != '\0')
		if(stash[i] == '\n')
			return (1);
	return (0);
}

int	len_at_endl(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		if (str[len] == '\n')
			return (len);
		len++;
	}
	return (-2);
}

char *parse_line(char *stash)
{
	char *line;
	int len;

	len = len_at_endl(stash) + 1;
	if (len == -1)
	{
		free(line);
		return (NULL);
	}
	line = ft_substr(stash, 0, len);
	return (line);
}

char *ch_stash(char *stash)
{
	char *new_stash;
	int len;

	len = len_at_endl(stash) + 1;
	if (len == ft_strlen(stash))
		new_stash = NULL;
	else
		new_stash = ft_substr(stash, len, ft_strlen(stash));
	return (new_stash);
}

char *get_next_line(fd)
{
	static char *stash;
	char buff[BUFFER_SIZE + 1];
	char *line;
	int bytes;

	line = NULL;
	while (1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (BUFFER_SIZE <= 0)
		{
			return (NULL);
		}
		if (!bytes && !stash)
		{
			free(line);
			return (NULL);
		}
		buff[BUFFER_SIZE] = '\0';
		if(!stash)
			stash = ft_strdup(buff);
		else
			stash = ft_strjoin(stash, buff);
		if (is_endl(stash))
			break ;
	}
	line = parse_line(stash);
	stash = ch_stash(stash);

	return (line);
}

int main()
{
	int fd = open("text.txt", O_RDONLY);
	int	i = 55;

	while (i--)
		printf("%s",get_next_line(fd));
		//get_next_line(fd);
}
