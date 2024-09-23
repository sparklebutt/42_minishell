/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/09/23 11:21:47 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*array_to_string(char **array)
{
	char	*new_string;
	int		index;
	int		new_string_len;
	int		i;

	index = 0;
	i = 0;
	new_string = NULL;
	new_string_len = 0;
	if (!array)
		return (NULL);
	while (array[index] != NULL)
	{
		new_string_len += ft_strlen(array[index]);
		index++;
	}
	new_string = ft_calloc(new_string_len + 1, sizeof(char));
	index = 0;
	while (array[index] != NULL)
	{
		ft_strcpy(new_string + i, array[index]);
		index++;
		i = ft_strlen(new_string);
	}
	return (*&new_string);
}

int	clean_if_multi_dollar_handle(t_data *data, t_tokens *tokens, int i)
{
	if (data->simple == false && tokens->dollar_count > 1)
	{
		tokens->args[i] = free_string(tokens->args[i]);
		tokens->args[i] = array_to_string(data->tmp->exp_array);
		data->simple = true;
		free_array(data->tmp->exp_array);
	}
	return (0);
}

/*~~ a fucntion that redirects the input to be handled based on if we handle
just a string or if we need to handle a newly added array that will be
later re adjusted to be a string in our tokens array ~~*/
void	handle_expansion(t_data *data, int len, int i, char *new)
{
	char	**args;
	int		flag;

	args = data->tokens->args;
	flag = 0;
	if (data->simple == false)
		simple_flagged(data, new, len, i);
	else
	{
		flag = check_next(args[i + 1], ft_strlen(args[i]));
		if (ft_strchr(args[i], '"') != NULL || ft_strchr(args[i], '\'') != NULL)
		{
			new = clean_quotes(args[i], len, 0, 0);
			args[i] = free_string(args[i]);
			args[i] = look_if_expans(data, data->env, new, flag);
		}
		else
			args[i] = look_if_expans(data, data->env, args[i], flag);
	}
}

int	expansion_parser_help(t_tokens *tokens, t_data *data, char *new, int i)
{
	size_t			len;

	len = ft_strlen(tokens->args[i]);
	if (tokens->dollar_count > 1)
		multi_dollar_handle(data, tokens, i);
	else if (confirm_expansion(tokens->args[i], len, 0) == true)
	{
		data->simple = true;
		handle_expansion(data, len - 1, i, new);
	}
	else if (tokens->args[i])
	{
		data->simple = true;
		clean_rest_of_quotes(data, i, len);
	}
	data->simple = false;
	return (0);
}

int	expansion_parser(t_tokens *tokens, t_data *data)
{
	int				i;
	static char		*new;

	i = 0;
	data->simple = true;
	while (tokens->args[i])
	{	
		dollar_counter(tokens->args[i], tokens);
		if (tokens->dollar_count > 0)
			expansion_parser_help(tokens, data, new, i);
		if (tokens->args[i] != NULL && tokens->dollar_count == 0)
		{
			data->simple = true;
			if (ft_strchr(tokens->args[i], '\'') != NULL
				|| ft_strchr(tokens->args[i], '"') != NULL)
				clean_rest_of_quotes(data, i, 0);
		}
		clean_if_multi_dollar_handle(data, tokens, i);
		i++;
	}
	return (0);
}
