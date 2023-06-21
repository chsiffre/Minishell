/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:00:03 by lucas             #+#    #+#             */
/*   Updated: 2023/06/21 13:40:07 by chsiffre         ###   ########.fr       */
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
	char *ret;
	int i;
	int option;
	
	i = 0;
	ret = "";
	if (ft_compare_str(data->lst->content[1], "-n"))
	{
		option = 1;
		i++;
	}
	else
		option = 0;
	while (data->lst->content[++i])
		ret = new_join(ret, data->lst->content[i], data->res_split[i]);
	if (option == 1)
		printf("%s", ret);
	else
		printf("%s\n", ret);
}
