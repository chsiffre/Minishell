/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:12:15 by charles           #+#    #+#             */
/*   Updated: 2023/08/02 14:19:39 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**check_quotes(char **strs, t_data *data)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		strs[i] = is_quote(strs[i], data);
		if (!strs[i])
			return (NULL);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

char	*is_quote(char *str, t_data *data)
{
	int		i;
	char	*ret;

	i = -1;
	ret = ft_calloc(sizeof (char), ft_strlen(str) + 1);
	if (!ret)
	{
		return (NULL);
	}
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (replace_quote(str, ret, data));
		else if (str[i] == '$')
			return (replace_all_str(str, ret, i + 1, data));
	}
	return (free(ret), str);
}

char	*replace_quote(char *str, char *ret, t_data *data)
{
	free(ret);
	ret = resize_quote(str, data);
	if (!ret)
		return (free(str), NULL);
	ret = del_quote(str, ret, data);
	return (free(str), ret);
}

char	*replace_all_str(char *str, char *ret, int i, t_data *data)
{
	if (is_var(str, i, data))
	{
		if (str[i] == '?')
			return (ft_convert_error(str, ret));
		ret = resize_var(str, data);
		if (str[i - 1])
		{
			i = 0;
			while (str[i] != '$')
				ret[data->ind++] = str[i++];
		}
		ret = replace_var(str, ret, &i, data);
		data->ind = 0;
	}
	return (ret);
}
