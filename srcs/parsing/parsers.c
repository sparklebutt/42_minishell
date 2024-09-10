/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/09/10 21:30:57 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ a function to take an array and turn it into a string
and return to caller, note this should be multip-puprose, also note
any array sent in must end in NULL~~*/
static char *array_to_string(char **array)
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
	//free_array(array);
	return (*&new_string);
}

/*~~ using this to return a dollar count instead of using strchr so we
can redirect the expansion parser based on if the token comes in as one
big string instead of seperate tokens. Since the out put needs to be 
one whole string too, this was easier than other options ~~*/
void		dollar_counter(char *string, t_tokens *tokens)
{
	int	i;
	
	i = 0;
	tokens->dollar_count = 0;
	//tokens->dollar_num = 0;
	while (string[i])
	{
		if (string[i] == '$')
			tokens->dollar_count++;
		i++;
	}
}

bool	set_check(char *string, bool ver, int *x, char c, int len) // stick the ver bool in struct
{
	(*x)++;
	while (string[*x] && string[*x] != c)
	{
		(*x)++;
		if (string[*x] == c)
		{
			ver = !ver;	
		}
		if ((*x) == len - 1)
			break ;
	}
	return (ver);
}
static int find_redirect(char *string) // we hve multiples of this function
{
	if (ft_strchr(string, '>') != NULL)
		return (1);
	if (ft_strchr(string, '<') != NULL)
		return (1);
	return (0);
}

// similar to quotes_handling (combine them?), maybe add bools into struct
/*~~this functions handles when there are quotes straight after $symbol, i could not
find a case where this type of syntax is expandable eg $"USER".
it might be wise to consider if this is the case for other symbols we need to handle~~*/
int		simple_quote_check(char *s, int i)
{
	int x = i;
	int counter = 0;
	while (s[x])
	{
		if (s[x] == '$')
			counter++;
		x++;
	}
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '\'' || (s[i + 1] == '"') || (counter < 2 && s[i + 1] == '$')))
			return (-1);
		if (s[i] == '$' && counter < 2)
		{
			if (i == 0)
				return (0); //saftey check ?
		 	if (s[i - 1] != '\'' && s[i - 1] != '"')
				return (0);
		}
		i++;
	}
	return (1);
}

bool	confirm_expansion(char *string, int len, int x)
{
	bool	s;
	bool	d;
	int		simple_ret;
	
	s = false;
	d = false;
	simple_ret = simple_quote_check(string, x);
	
	if (simple_ret == -1)
		return (false);
	if (simple_ret == 0)
		return (true); 
	while (string[x] && x < len)
	{
		if (string[x] == '\'')
			s = set_check(string, s, &x, '\'', len);
		else if (string[x] == '"')
			d = set_check(string, d, &x, '"', len);
		x++;
	}
	return ((d && !s) || (!d && !s));
}
/*~~ a fucntion that redirects the input to be handled based on if we handle
just a string or if we need to handle a newly ade array that will be later re adjusted
to be a string in our tokens array ~~*/
void	handle_expansion(t_data *data, int len, int i, char *new)
{
	t_tokens	*tokens;
	char		*tmp;

	// cut this smaller
	tmp = NULL;
	tokens = data->tokens;
	if (data->simple == false)
	{
		if (ft_strchr(data->tmp->exp_array[i], '"') != NULL
		|| ft_strchr(data->tmp->exp_array[i], '\'') != NULL)
		{
			new = clean_quotes(data->tmp->exp_array[i], len, 0, 0);
			tmp = look_if_expansions(data, data->env, new, 0);
			free_string(data->tmp->exp_array[i]);
			data->tmp->exp_array[i] = ft_strdup((tmp));
			free_string(tmp);
		}
		else
		{
			data->tmp->exp_array[i] = look_if_expansions(data, data->env, data->tmp->exp_array[i], 0);
		}
	}
	else
	{
		if (ft_strchr(tokens->args[i], '"') != NULL
		|| ft_strchr(tokens->args[i], '\'') != NULL)
		{
			new = clean_quotes(tokens->args[i], len, 0, 0);
			free_string(tokens->args[i]);	// maybe not needed if we free inside already but it doesn't hurt, this fixed an error, vilja
			tokens->args[i] = look_if_expansions(data, data->env, new, 0);
		}
		else
		{
			// free_string(tokens->args[i]); // this breaks everything, was new but naaaah, might still be needed
			tokens->args[i] = look_if_expansions(data, data->env, tokens->args[i], 0);
		}
	}
}

int	clean_if_multi_dollar_handle(t_data *data, t_tokens *tokens, int i)
{
	//char *tmp;

	//tmp = NULL;
	if (data->simple == false && tokens->dollar_count > 1)
	{
		free_string(tokens->args[i]);
		//tmp = array_to_string(data->tmp->exp_array);
		tokens->args[i] = array_to_string(data->tmp->exp_array);//ft_strdup(tmp);
		//free_string(tmp);
		data->simple = true;
		// printf("This is arrays address = %p\n", data->tmp->exp_array);
		free_array(data->tmp->exp_array); // MALLOCED VARIABLE
	}
	else 
		return (0);
	return (0);
}

int	multi_dollar_handle(t_data *data, t_tokens *tokens, int i)
{
	int index;
	size_t len;
	static char		*new; // potentially not needed

	len = 0;
	index = 0;
	data->simple = false;
	data->tmp->exp_array = ft_split_expansions(tokens, tokens->args[i]); // MALLOCED VARIABLE
	if (data->tmp->exp_array == NULL)
	{
		printf("malloc fail handleing required\n"); // REWRITE
		return (-1);
	}
	while (data->tmp->exp_array[index] != NULL)
	{
		len = ft_strlen(data->tmp->exp_array[index]);
		if (confirm_expansion(data->tmp->exp_array[index], len, 0) == true)
			handle_expansion(data, len - 1, index, new);
		else
			clean_rest_of_quotes(data, index, len);
		index++;
	}
	return (0);
}

int	 no_dollar_handle(t_tokens *tokens, t_data *data, int i)
{
	if (ft_strlen(tokens->args[i]) == 1 && tokens->args[i][0] == '~') // some people say we don't need to handle this, but we do already?
	{
		free_string(tokens->args[i]);
		tokens->args[i] = replace_squiggly_line(data, data->env);
	}
	data->simple = true;
	if (ft_strchr(tokens->args[i], '\'') != NULL || ft_strchr(tokens->args[i], '"') != NULL)
		clean_rest_of_quotes(data, i, 0);	
	return (0);
}

int	expansion_parser(t_tokens *tokens, t_data *data)
{
	int				i;
	size_t			len;
	static char		*new;

	i = 0;
	len = 0;
	data->simple = true;
	while (tokens->args[i])
	{	
		dollar_counter(tokens->args[i], tokens);
		len = ft_strlen(tokens->args[i]);
		if (tokens->dollar_count > 0)
		{
			// can everything in this if statement be put in it's own function, fyi this is 30 lines long
			// cut this smaller
			if (tokens->dollar_count > 1)
				multi_dollar_handle(data, tokens, i);			
			else if (confirm_expansion(tokens->args[i], len, 0) == true)
			{
				data->simple = true;
				handle_expansion(data, len - 1, i, new);
			}
			else if (tokens->args[i])
				clean_rest_of_quotes(data, i, len);
			data->simple = false;
		}
		else if (tokens->args[i] != NULL && find_redirect(tokens->args[i]) == 0 && tokens->dollar_count == 0)
			no_dollar_handle(tokens, data, i);
		clean_if_multi_dollar_handle(data, tokens, i);
		i++;
	}
	return (0);
}
