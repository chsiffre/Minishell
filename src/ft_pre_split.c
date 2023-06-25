/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/06/25 22:31:37 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_pre_split(char *str)
{
	int new_size;
	char *copy;
	
	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	// if (!check_chevron(str))
	// 	return (free(copy), str);
	new_size = ft_strlen(str);
	new_size = resize_pre_split(str, &new_size);
	if (quote_open(str))
	{
		printf("quote open\n");
		exit(1);
	}
	str = malloc((new_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_str_replace(str, copy, new_size);
	if (!str)
		return (NULL);
	return (free(copy), str);
}

char *ft_str_replace(char *str, char *copy, int new_size)
{
	int i;
	int y;
	
	y = 0;
	i = 0;
	while (i < new_size)
	{
		str = check_chevron(str, copy, &i, &y);
		str = check_pipes(str, copy , &i, &y);
		if (!str)
			return (free (copy), NULL);
	}
	str[i] = '\0';
	return (str);
}

char *check_chevron(char *str, char *copy, int *i, int *y)
{
	if (copy[*i] && (copy[*i] == '<' || copy[*i] == '>'))
	{
		if (copy[*i - 1] && copy[*i - 1] != ' ' && copy[*i - 1] != '<' && copy[*i - 1] != '>')
		{
			str[(*y)++] = ' ';
			if (copy[*i])
				str[(*y)++] = copy[(*i)++];
			if (copy[*i] && copy[*i] != '<' && copy[*i] != '>' && copy[*i] != ' ')
			{
				str[(*y)++] = ' ';
				str[(*y)++] = copy[(*i)++];
			}
			return (str);
		}
		else if (copy[*i + 1] && copy[*i + 1] != '<' && copy[*i + 1] != '>' && copy[*i + 1] != ' ')
		{
			str[(*y)++] = copy[(*i)++];
			str[(*y)++] = ' ';
			str[(*y)++] = copy[(*i)++];
		}
	}
	return (str);
}

char *check_pipes(char *str, char *copy, int *i, int *y)
{
	if (copy[*i] && copy[*i + 1] && (copy[*i] == '|' && copy[*i + 1] == '|'))
		return (NULL);
	if ((copy[*i] != ' ' && copy[*i + 1] == '|') || (copy[*i] == '|' && copy[*i + 1] != ' '))
	{
		if (copy[*i])
			str[(*y)++] = copy[(*i)++];
		str[(*y)++] = ' ';
	}
	else
		str[(*y)++] = copy[(*i)++];
	return (str);
}

int quote_open(char *str)
{
	int	i;
	char quote;

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

int resize_pre_split(char *str, int *new_size)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (!str[i + 1])
				return (0);
			if (str[i + 1] && str[i + 1] != '<' && str[i + 1] != '>' && str[i + 1] != ' ')
				(*new_size)++;
			if (str[i - 1] && str[i - 1] != ' ')
				(*new_size)++; 
		}
		if (str[i] && str[i] == '|' && str[i - 1] != ' ')
			(*new_size)++;
		if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != ' ')
			(*new_size)++;
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

// int	check_chevron(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '<' || str[i] == '>')
// 		{
// 			if (str[i])
// 				i++;
// 			else
// 				return (0);
// 			while (str[i])
// 			{
// 				if ()
// 			}
// 		}
// 	}
// 	return ();
// }

int	ft_is_not_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '\v' && c != '\f' && c != '\r')
		return (1);
	return (0);
}