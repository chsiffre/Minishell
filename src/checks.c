/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:55:39 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/10 13:46:47 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_check_redir(char **res_parse, t_data *data, char **strs, int start)
{
	int	i;

	i = start;
	while (strs[i] && strs[i][0] != '|')
	{
		strs[i] = is_quote(strs[i]);
		if (!strs[i])
			return (NULL);
		if (ft_is_redir(strs[i]))
		{
			res_parse[data->i++] = strs[i];
			i++;
			res_parse[data->i++] = strs[i];
			i++;
		}
		else
			i++;
	}
	return (res_parse);
}

int	ft_is_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '<' && !str[i + 1])
			return (1);
		else if (str[i] == '>' && !str[i + 1])
			return (1);
		else if (str[i] && str[i] == '>' && str[i + 1] == '>')
			return (1);
		else if (str[i] && str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_check_cmd(char **res_parse, t_data *d, char **strs, int start)
{
	int	i;

	i = start;
	while (strs[i] && strs[i][0] != '|')
	{
		if (strs[i + 1] && ft_is_redir(strs[i]))
			i = i + 2;
		else if (strs[i] && strs[i][0] != '|')
		{
			res_parse[d->i++] = strs[i];
			i++;
		}
	}
	return (res_parse);
}

int	ft_is_builtins(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	return (0);
}

char *is_quote(char *str)
{
	int	i;
	int	y;
	char *ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) - ft_nb_quote(str)));
	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i++;
			if (str[i] == ' ')
				i++;
			ret[y++] = str[i++];
		}
		else
			ret[y++] = str[i++];
	}
	ret[y] = 0;
	free(str);
	return (ret);
}


int ft_nb_quote(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}