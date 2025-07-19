/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:15 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/14 20:58:55 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if ('1' <= str[i] && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + (str[i++] - '0');
		if (nb <= 0)
			return (0);
	}
	if (str[i])
		return (0);
	return (nb);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s_start;
	char	*s;
	int		sl1;
	int		sl2;

	if (!s1 || !s2)
		return (NULL);
	sl1 = ft_strlen(s1);
	sl2 = ft_strlen(s2);
	s = malloc(sl1 + sl2 + 1);
	if (!s)
	{
		ft_simple_perror("malloc");
		return (NULL);
	}
	s_start = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (s_start);
}

void	ft_simple_perror(char *cmd)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ERRCOM, ft_strlen(ERRCOM));
}
