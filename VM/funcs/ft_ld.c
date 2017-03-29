/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabbah <nsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:14:24 by nsabbah           #+#    #+#             */
/*   Updated: 2017/03/29 12:41:09 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/vm.h"

/*
** Instructions:
** Take a random argument and a registry. Load the value of the first argument
** in the registry. Its opcode is 10 in binary and it will change the carry.
**
** Should the IND part should be % MEM_SIZE or similar?
*/
# define IR 0b11010000
# define DR 0b10010000

void	ft_ld(t_env *e, t_cursor *cursor)
{
	char		acb;
	int			value;
	int			opc_ind;
	unsigned short		r;

	opc_ind = cursor->index;
	acb = e->a[MODA(opc_ind + 1)].hex;
	if (DR == ZMASK(acb))
	{
		value = get_bytes(e, cursor, opc_ind + 2);
		// printf("V = %i\n", value);
		if (e->a[MODA(opc_ind + 2 + 4)].hex - 1 >= 1 && e->a[MODA(opc_ind + 2 + 4)].hex - 1 <= REG_NUMBER)
		{
			cursor->reg[e->a[MODA(opc_ind + 2 + 4)].hex - 1] = value;
			if (value == 0)
				cursor->carry = 1;
			else
				cursor->carry = 0;
		}
		ft_update_cursor(e, cursor, 7);
	}
	else if (IR == ZMASK(acb))
	{
		r = ((ZMASK(e->a[MODA(opc_ind + 2)].hex) << 8) | ZMASK(e->a[MODA(opc_ind + 3)].hex));
		value = get_bytes(e, cursor, (short)r);
		// printf("v = %x\n", value);
		if (e->a[MODA(opc_ind + 2 + 2)].hex - 1 >= 1 && e->a[MODA(opc_ind + 2 + 2)].hex - 1 <= REG_NUMBER)
		{
			cursor->reg[e->a[MODA(opc_ind + 2 + 2)].hex - 1] = value;
			if (value == 0)
				cursor->carry = 1;
			else
				cursor->carry = 0;
		}
		ft_update_cursor(e, cursor, 5);
	}
}
