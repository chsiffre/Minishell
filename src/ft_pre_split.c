/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/07/04 09:51:26 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pre_split(char *str)
{
	int		new_size;
	char	*copy;

	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	new_size = ft_strlen(str);
	new_size = resize_pre_split(str, &new_size);
	if (quote_open(str))
	{
		printf("quote open\n");
		exit(1);
	}
	str = ft_calloc((new_size + 1), sizeof(char));
	if (!str)
		return (NULL);
	str = ft_str_replace(str, copy, new_size);
	if (!str)
		return (NULL);
	return (free(copy), str);
}

char	*ft_str_replace(char *str, char *copy, int new_size)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (i < new_size)
	{
		str = check_chevron(str, copy, &i, &y);
		str = check_pipes(str, copy, &i, &y);
		if (!str)
			return (free (copy), NULL);
	}
	str[i] = '\0';
	return (str);
}

char	*check_chevron(char *str, char *copy, int *i, int *y)
{
	if (copy[*i] && (copy[*i] == '<' || copy[*i] == '>'))
	{
		if (*i != 0 && (copy[*i - 1] && copy[*i - 1] != ' '
				&& copy[*i - 1] != '<' && copy[*i - 1] != '>'))
		{
			str[(*y)++] = ' ';
			if (copy[*i])
				str[(*y)++] = copy[(*i)++];
			if (copy[*i] && copy[*i] != '<'
				&& copy[*i] != '>' && copy[*i] != ' ')
			{
				str[(*y)++] = ' ';
				str[(*y)++] = copy[(*i)++];
			}
			return (str);
		}
		else if (copy[*i + 1] && (copy[*i + 1] != '<'
				&& copy[*i + 1] != '>' && copy[*i + 1] != ' '))
		{
			str[(*y)++] = copy[(*i)++];
			str[(*y)++] = ' ';
			str[(*y)++] = copy[(*i)++];
		}
	}
	return (str);
}

char	*check_pipes(char *str, char *copy, int *i, int *y)
{
	if (copy[*i] && copy[*i + 1] && (copy[*i] == '|' && copy[*i + 1] == '|'))
		return (NULL);
	if (copy[*i] && ((copy[*i] != ' ' && copy[*i + 1] && copy[*i + 1] == '|')
			|| (copy[*i] == '|' && copy[*i + 1] && copy[*i + 1] != ' ')))
	{
		if (copy[*i])
			str[(*y)++] = copy[(*i)++];
		str[(*y)++] = ' ';
	}
	else
		str[(*y)++] = copy[(*i)++];
	return (str);
}

int	quote_open(char *str)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] != quote && str[i])
				i++;
			if (!str[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	resize_pre_split(char *str, int *new_size)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i != 0 && str[i] && (str[i] == '<' || str[i] == '>'))
		{
			if (str[i + 1] && str[i + 1] != '<'
				&& str[i + 1] != '>' && str[i + 1] != ' ')
				(*new_size)++;
			if (str[i - 1] && str[i - 1] != ' ')
				(*new_size)++;
		}
		if (i != 0 && str[i] && str[i] == '|'
			&& str[i - 1] && str[i - 1] != ' ')
			(*new_size)++;
		if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != ' ')
			(*new_size)++;
		i++;
	}
	return (*new_size);
}

int	empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_not_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	not_parse(char *str)
{
	int		i;
	char	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		{
			c = str[i];
			while (str[i] && (str[i] == c || is_space(str[i])))
				i++;
		}
		else if (str[i] == '$' && (!str[i + 1] || is_space(str[i + 1])))
			return (printf("$: command not found\n"), 1);
		else if (str[i] && ft_is_not_space(str[i]))
			return (0);
		if (str[i])
			i++;
	}
	if (c == '<' || c == '>')
		ft_syntax_error("`newline'");
	else if (c == '|')
		ft_syntax_error("`|'");
	return (1);
}

int	ft_is_not_space(char c)
{
	if ((c >= 0 && c <= 8) || (c >= 16 && c < 32) 
		|| (c >= 33 && c < 127))
		return (1);
	return (0);
}

int	is_space(char caractere) 
{
	if (caractere == ' ' || caractere == '\t' || caractere == '\n'
		|| caractere == '\v' || caractere == '\f' || caractere == '\r')
		return (1);
	else
		return (0);
}

static int	int_len(int n)
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

static char	*ft_itoa_2(long y, long n, int i, char *ret)
{
	if (n == 0)
	{
		ret[1] = '\0';
		ret[0] = 48;
		return (ret);
	}
	ret[i] = '\0';
	i--;
	while (i >= 0)
	{
		ret[i--] = (y % 10) + '0';
		y = y / 10;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}

char	*ft_n_itoa(int n, char *ret)
{
	long	i;
	int		y;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	else
		i = int_len(n);
	if (n < 0 && n != -2147483648)
		y = -n;
	else
		y = n;
	return (ft_itoa_2(y, n, i, ret));
}