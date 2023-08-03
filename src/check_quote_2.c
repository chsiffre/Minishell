/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:14:00 by charles           #+#    #+#             */
/*   Updated: 2023/08/03 16:09:55 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_int_len(int n)
{
	int	i;
	int	y;

	i = 1;
	if (n < 0)
	{
		y = -n;
		i++;
	}
	else
		y = n;
	while (y >= 10)
	{
		y = y / 10;
		i++;
	}
	return (i);
}

char	*resize_quote(char *str, t_data *data)
{
	int		i;
	int		new_size;
	char	quote;

	i = -1;
	quote = 0;
	new_size = 0;
	while (str[++i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				check_size(str, &i, &new_size, data);
				if (str[i] && str[i] == '$')
					continue ;
				else if (str[i])
					i++;
			}
		}
		else
			new_size++;
	}
	return (malloc(sizeof (char) * new_size + 1));
}

void	check_size(char *str, int *i, int *new_size, t_data *data)
{
	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
	{
		while (str[*i] && str[*i + 1]
			&& str[*i + 2] && (str[*i] == '$' && str[*i + 1] == '?'))
		{
			(*new_size) += ft_int_len(g_error_last);
			(*i)++;
		}
	}
	else if (str[*i] == '$' && if_expand(str) && is_var(str, *i, data))
		(*new_size) += var_exist(str, i, data);
	else if (str[*i] == '$' && if_expand(str) && !is_var(str, *i, data))
	{
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
	}
	else
		(*new_size)++;
}

char	*ft_check_quote_var(char *str, int i, char	*ret, t_data *data)
{
	int	quote;

	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[(i)++];
			while (str[i] && str[i] != quote)
			{
				if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
					return (ret = ft_convert_error(str, ret), ret);
				if (str[i] == '$' && if_expand(str) && is_var(str, i, data))
					ret = replace_var(str, ret, &i, data);
				else if (str[i])
					ret[data->ind++] = str[(i)++];
			}
		}
		else
			ret[data->ind++] = str[i++];
	}
	ret[data->ind] = '\0';
	data->ind = 0;
	return (ret);
}

char	*del_quote(char *str, char *ret, t_data *data)
{
	int	i;

	i = 0;
	ret = ft_check_quote_var(str, i, ret, data);
	return (ret);
}
