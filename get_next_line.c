/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:03:25 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/22 00:30:19 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ssize_t read(int fd, void *container, size_t count);

/*
BUFFER_SIZE分のメモリを確保する
BUFFER_SIZE分の文字数をreadでbufに読み込む
*/

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

int ft_strnllen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

void	ft_nlsubstr(const char *str, char **befor_newline, char **after_newline)
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
}

void	ft_free_s(char	**ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*get_next_line(int fd)
{
	char		*container;
	char		*buf_ptr_for_free;
	char		*new_line_ptr;
	char		*new_line_in_str;
	char		*line; // 出力する文字列のポインタを格納
	char		*before_newline;
	char		*after_newline;
	static char	*buf; // 初期値はNULL
	ssize_t		read_bytes;
	int i = 0;

	if (buf == NULL)
		buf = ft_strdup("");
	while (1)
	{
		container = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (container == NULL)
			return (NULL);
		read_bytes = read(fd, container, BUFFER_SIZE - 1);
		if (read_bytes == -1 || read_bytes == 0 && ft_strlen(buf) == 0)
		{
			ft_free_s(&container);
			ft_free_s(&buf);
			return (NULL);
		}
		container[read_bytes] = '\0';
		buf_ptr_for_free = buf;
		buf = ft_strjoin(buf, container);
		ft_free_s(&buf_ptr_for_free);
		buf_ptr_for_free = buf;
		ft_nlsubstr(buf, &before_newline, &after_newline);
		ft_free_s(&buf_ptr_for_free);
		if (read_bytes < BUFFER_SIZE - 1 && ft_strlen(before_newline) == 0)
		{
			line = ft_strdup(after_newline);
			buf = ft_strdup(before_newline);
		}
		else
		{
			line = ft_strdup(before_newline);
			buf = ft_strdup(after_newline);
		}
		ft_free_s(&buf_ptr_for_free);
		ft_free_s(&container);
		ft_free_s(&after_newline);
		ft_free_s(&before_newline);
		if (ft_strlen(line) != 0)
			return (line);
		i++;
	}
	return (NULL);
}

// int	ft_forward_look_for_newline(const char *str)
// {
// 	int	i;
// 	int	count;

// 	count = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != '\n')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// int ft_strnllen(const char *str)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\n')
// 			return (count);
// 		count++;
// 		i++;
// 	}
// 	return (-1);
// }

// void	ft_nlsubstr(const char *str, char **befor_newline, char **after_newline)
// {
// 	int	start;
// 	int	len;

// 	start = ft_forward_look_for_newline(str);
// 	len = ft_strnllen(str + start);
// 	if (len == -1)
// 		len = ft_strlen(str + start);
// 	*befor_newline = ft_substr(str, start, len);
// 	*after_newline = ft_substr(str + start + len, ft_forward_look_for_newline(str + start + len), ft_strlen(str + start + len));
// }

// int main(void) {
// 	char *str = ft_strdup("\n\nabc\nng\nfefebf");
// 	char *before_newline;
// 	char *after_newline;

// 	ft_nlsubstr(str, &before_newline, &after_newline);
// 	printf("before_newline : %s\n", before_newline);
// 	printf("after_newline : %s\n", after_newline);
// 	free(before_newline);
// 	free(after_newline);
// }
