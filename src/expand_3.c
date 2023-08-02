/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:07 by charles           #+#    #+#             */
/*   Updated: 2023/08/02 17:17:34 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_return_error_last(char *ret, char *str, int i, int y)
{
	if (str[i] && str[0] == '\"')
			i++;
	while (str[i])
	{
		while (str[i] && str[i] == '$')
		{
			ret = ft_strjoin(ret, ft_itoa(g_error_last));
			if (!ret)
				return (NULL);
			while (ret[y])
				y++;
			i++;
			if (str[i])
				i++;
		}
		if (str[i] && str[i] == '\"' && !str[i + 1])
			break ;
		else if (str[i])
			ret[y++] = str[i];
		i++;
	}
	ret[y] = '\0';
	printf("%s\n", ret);
	return (ret);
}

int	ft_count_other_char(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1])
				i = i + 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*ft_convert_error(char *str, char *ret)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	if (ret)
		free(ret);
	ret = malloc((ft_int_len(g_error_last) * (ft_strlen(str) / 2) + ft_count_other_char(str)) + 1);
	if (!ret)
		return (NULL);
	return (ft_return_error_last(ret, str, i, y));
}
