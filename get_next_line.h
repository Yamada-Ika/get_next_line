/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:05:00 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/01 23:11:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define FD_MAX 256

char	*get_next_line(int fd);
void	ft_free_s(void **ptr);
size_t	ft_strclen(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);

#endif
