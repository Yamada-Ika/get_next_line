/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:03:25 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/03 11:21:44 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strcdup(const char *s1, int c)
{
	char	*s2;
	size_t	s1_len;

	if (c == '\0')
		s1_len = ft_strclen(s1, '\0');
	else
		s1_len = ft_strclen(s1, c) + 1;
	s2 = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, s1_len + 1);
	return (s2);
}

static char	*ft_nlseparate(char *str, char **after_newline)
{
	size_t	len_before_nl;
	char	*before_newline;

	len_before_nl = ft_strclen(str, '\n') + 1;
	before_newline = ft_strcdup(str, '\n');
	*after_newline = ft_strcdup(str + len_before_nl, '\0');
	ft_free_s((void **)&str);
	if (before_newline == NULL || *after_newline == NULL)
	{
		ft_free_s((void **)&before_newline);
		ft_free_s((void **)after_newline);
		return (NULL);
	}
	return (before_newline);
}

static char	*ft_hstrjoin_s(char **s1, char **s2)
{
	char	*joined_str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL || *s1 == NULL || *s2 == NULL)
		return (NULL);
	s1_len = ft_strclen(*s1, '\0');
	s2_len = ft_strclen(*s2, '\0');
	joined_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (joined_str == NULL)
	{
		ft_free_s((void **)s1);
		ft_free_s((void **)s2);
		return (NULL);
	}
	ft_strlcpy(joined_str, *s1, s1_len + 1);
	ft_strlcpy(joined_str + s1_len, *s2, s2_len + 1);
	ft_free_s((void **)s1);
	ft_free_s((void **)s2);
	return (joined_str);
}

static ssize_t	ft_read(int fd, char **buf)
{
	ssize_t	read_bytes;

	*buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (*buf == NULL)
		return (-1);
	read_bytes = read(fd, *buf, BUFFER_SIZE);
	if (read_bytes < 0)
		return (-1);
	(*buf)[read_bytes] = '\0';
	return (read_bytes);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save[FD_MAX] = {NULL};
	ssize_t		read_bytes;

	if (fd < 0 || fd == STDOUT_FILENO || fd == STDERR_FILENO
		|| FD_MAX < fd || BUFFER_SIZE < 0)
		return (NULL);
	if (save[fd] == NULL)
		save[fd] = ft_strcdup("", '\0');
	while (save[fd] != NULL)
	{
		if (ft_strchr(save[fd], '\n'))
			return (ft_nlseparate(save[fd], &save[fd]));
		read_bytes = ft_read(fd, &buf);
		if (read_bytes < 0 || (!read_bytes && !ft_strclen(save[fd], '\0')))
		{
			ft_free_s((void **)&buf);
			ft_free_s((void **)&save[fd]);
			break ;
		}
		if (read_bytes < BUFFER_SIZE && !(ft_strchr(buf, '\n')))
			return (ft_hstrjoin_s(&save[fd], &buf));
		save[fd] = ft_hstrjoin_s(&save[fd], &buf);
	}
	return (NULL);
}
