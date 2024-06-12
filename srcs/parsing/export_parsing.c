/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:57:49 by araveala          #+#    #+#             */
/*   Updated: 2024/06/06 18:37:18 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(t_data *data, int i, int x)
{
	char character;

	if (x == -1)
	{
		printf("minishell : not a valid identifier (no exit plan yet)\n");
		return (1);
	}
	character = data->tokens->args[i][x];
	// printf("char = %c\n", character);
	if (character == '<')
	{
		// or <<
		// could return number value for handling
		printf("handle < \n");
		return (2);
	}
	if (character == '>')
	{
		// or >>
		// could return number value for handling
		printf("handle > \n");
		return (2);
	}
	if (character == '$' && ft_strchr(data->tokens->args[i], '=') == NULL)
	{
		printf("does some declare -x stuff, may not need to handle the same as org shell\n");
		return (2);
	}
	// here we can add && and || they do some wierd shit ...*does nothing here
	if (ft_isalpha(character) == 0 && character != '_')
	{
		printf("minishell : not a valid identifier (no exit plan yet)\n");
		return (1);
	}
	else
		return (0);
}

// may not need to return int
int	validate_it(t_data *data, char *string, int i)
{
	int	x;

	x = 0;
	printf("string = %s\n", string);
	// string is only here if we need to do some quick null check or such
	// assumin quotes are handled eg check there is an equal number of them , remove them .
	if (data->tokens->array_count == 1)
	{
		printf("shows env list but with declare -x infront of each env aswell as failed attempts\n");
		// or error and return
		return (1);
	}
	while (data->tokens->args[i][x] != '\0')
	{
		if (x == 0)
		{
			if (check_char(data, i, x) != 0)
			{
				//	free_array(&data->tokens->args[i]);
				return (1);
			}
		}
		//	printf("whats in the args[i] ~~ %s\n", data->tokens->args[i]);
		if (ft_strchr(data->tokens->args[i], '=') == NULL)
		{
			printf("there is no equals, only return\n");
			//we need to check the next line, this one is invalid
			return (2); // to repeat loop on new i continue
		}
		// we have dealt with name
		// next validate value
		while (data->tokens->args[i][x] != '\0')
		{
			while (data->tokens->args[i][x] == '=')
			{
				// multiple = signs are valid and will be copied over
				// spaces do not need to be handled as array should have quotes handled
				x++;
				if (data->tokens->args[i][x] != '=')
				{
					// we have reached the value
					if (data->tokens->args[i][x] == '$')
					{
						printf("handle $ sign\n");
						// check for existing NAME replace or new
						// copy from tokens->args[i] up to x, no further.
						// if there are multiple = sign eg something=$beep=boop == something=(-beep)=boop=else
						// eg return (3);
					}
					if (data->tokens->args[i][x] == '>') // or >, <, <<
						printf("special character warning\n");
					// here doc nonsense
					// special characters such as >><< apply here if ="is not in quotes"
					// an invalid character will break process and print all valid collected up to this point
				}
			}
			x++;
		}
	}
	// check for existing NAME
	// copy from tokens->args[i] up to x
	// always keep adding to env as we go, or prep new array with valid input only 
	printf("valid input for export (func validate_it)\n");
	return (0); //hopefully completley valid
}

///~~~****davey jones locker ****~~~~~////
///~~~~~~ft_strim front and some quote handling playaround~~~~~~~///




/*static int  ft_check_front(char const *s1, char const *set)
{
    int i;

    i = 0;
	printf("string in the new trim = %s\n", s1);
    while (ft_strchr(set, s1[i]))
    {
       if (s1[i] == '\0')
            return (1);
        i++;
    }
    return (i);
	}*/

 /*static	char *ignore_quotes(char *string)
{
	int i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '"')
		{
			i++;
		}
	}
	}*/

  /* static int quote_check(char *string, int f)
{
	int i;
	int x;
	
	i = 0;
	x = 0;

//	if (string[f] != '"' || string[f] != 39)
//		return (0);
//	if (string[f] == '"')
//	{
		while (string[f] != '\0')
		{
			while (string[f] == '"' && x == 0)
			{
				i++;
				f++;
			}
			while (string[f] == '"')
			{
				f++;
				x++;
			}
			f++;
		}
		if (x == i)
			// we have eeven number of quotes 
			return (i); 
		else if (x > i)
			return (-1);

//	}
//	else if (string[f] == 39)
//	{
		while (string[f] != '\0')
		{
			while (string[f] == 39)
			{
				f++;
				i++;
			}
			f++;
			while (string[f] == 39)
			{
				f++;
				x++;
			}
			if (x == i)
				// we have eeven number of quotes 
				return (i);
//		} 
	
//	if (x != 0)
//		return (-1);
	return (0);
}*/
 
