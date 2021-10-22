/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:03:25 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/23 00:32:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_s(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*c_dst;
	const char	*c_src;

	if (dst == src || n == 0)
		return (dst);
	c_dst = (char *)dst;
	c_src = (const char *)src;
	i = 0;
	while (i < n)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}

static size_t	ft_min(size_t num1, size_t num2)
{
	if (num1 < num2)
		return (num1);
	return (num2);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i + 1 < dstsize && i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	substr_len = ft_min(len, s_len - (size_t)start);
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}

size_t	is_newline_in_str(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (joined_str == NULL)
		return (NULL);
	ft_memcpy(joined_str, s1, s1_len);
	ft_strlcpy(joined_str + s1_len, s2, s2_len + 1);
	return (joined_str);
}

void	print_read_str(char *container) {
	for (int i = 0; i < BUFFER_SIZE - 1; ++i) {
		printf("%02x %c ", container[i], container[i]);
	}
	putchar('\n');
}

int	ft_forward_look_for_newline(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t ft_strnllen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

void	ft_nlsubstr(char *str, char **befor_newline, char **after_newline)
{
	int	start;
	int	len;

	start = ft_forward_look_for_newline(str);
	len = ft_strnllen(str + start);
	if (len == ft_strlen(str + start))
	{
		*befor_newline = ft_strdup("");
		*after_newline = ft_strdup(str + start);
	}
	else
	{
		*befor_newline = ft_substr(str, start, len);
		*after_newline = ft_substr(str + start + len, ft_forward_look_for_newline(str + start + len), ft_strlen(str + start + len));
	}
	// ft_free_s(&str);
}

// \nを探すために使いたい
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
}

// \n以前と以降の文字列を分割したい
void	ft_nlseparate(char *str, char **befor_newline, char **after_newline)
{
	size_t	len_before_nl;

	len_before_nl = ft_strnllen(str);
	*befor_newline = ft_substr(str, 0, len_before_nl);
	*after_newline = ft_substr(str + len_before_nl, 1, ft_strlen(str) - (len_before_nl + 1));
}

ssize_t ft_read(int fd, char **container, char **buf)
{
	ssize_t		read_bytes;

	*container = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (*container == NULL)
		return (-1);
	read_bytes = read(fd, *container, BUFFER_SIZE - 1);
	if (read_bytes <= 0)
	{
		ft_free_s(buf);
		ft_free_s(container);
		return (-1);
	}
	(*container)[read_bytes] = '\0';
	return (read_bytes);
}

char	*get_nextline_from_buf(char **buf)
{
	char	*next_line;
	char	*tmp_buf;

	tmp_buf = *buf;
	ft_nlsubstr(*buf, &next_line, buf);
	ft_free_s(&tmp_buf);
	return (next_line);
}

char	*get_nextline_at_EOF(char **buf, char **container)
{
	char	*next_line;

	next_line = ft_strjoin(*buf, *container);
	ft_free_s(buf);
	ft_free_s(container);
	return (next_line);
}

char	*ft_strjoin_s(char *str1, char *str2)
{
	char	*joined_str;

	joined_str = ft_strjoin(str1, str2);
	ft_free_s(&str1);
	ft_free_s(&str2);
	return (joined_str);
}

char *get_nextline_from_container(char **container, char **buf)
{
	char *before_newline;
	char *after_newline;
	char *next_line;

	ft_nlsubstr(*container, &before_newline, &after_newline);
	ft_free_s(container);
	next_line = ft_strjoin_s(*buf, before_newline);
	*buf = after_newline;
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*container;
	static char	*buf;
	char		*tmp_buf;
	ssize_t		read_bytes;

	if (fd < 0 && _SC_OPEN_MAX < fd)
		return (NULL);
	if (buf == NULL)
		buf = ft_strdup("");
	if (ft_strchr(buf, '\n'))
		return (get_nextline_from_buf(&buf));
	while (1)
	{
		read_bytes = ft_read(fd, &container, &buf);
		if (read_bytes < 0)
			return (NULL);
		if (ft_strchr(container, '\n') != NULL)
			break ;
		if (read_bytes < BUFFER_SIZE - 1)
			return (get_nextline_at_EOF(&buf, &container));
		buf = ft_strjoin_s(buf, container);
	}
	return (get_nextline_from_container(&container, &buf));
}
