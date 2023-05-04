/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:00:03 by lucas             #+#    #+#             */
/*   Updated: 2023/04/04 13:09:37 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_echo_env(t_data *data, char *str)
{
	t_env	*tmp;
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = data->env;
	if (str[i] == '$')
		i++;
	name = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!name)
		return (NULL);
	while (str[i])
		name[j++] = str[i++];
	name[j++] = '=';
	name[j] = '\0';
	while (tmp)
	{
		if (ft_compare_str(tmp->name, name))
			return (free(name), tmp->value);
		tmp = tmp->next;
	}
	return (free(name), "");
}

void	ft_echo(t_data *data)
{
	if (ft_compare_str(data->cmd[1], "-n"))
	{
		if (data->cmd[2][0] == '$')
			printf("%s", ft_echo_env(data, data->cmd[2]));
		else
			printf("%s", data->cmd[2]);
	}
	else
	{
		if (data->cmd[1][0] == '$')
			printf("%s\n", ft_echo_env(data, data->cmd[1]));
		else
			printf("%s\n", data->cmd[1]);
	}
}