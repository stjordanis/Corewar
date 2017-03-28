/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabbah <nsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:14:24 by nsabbah           #+#    #+#             */
/*   Updated: 2017/03/28 14:04:27 by nsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/vm.h"

/*
** Instructions: Apply an | (bit-to-bit or) over the first two arguments
** or store the result in a registry, which is the third argument.
** Opcode 0x06. Modifies the carry.
** T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG
*/

static void	ft_or_4(t_env *e, t_cursor *cursor, t_var v)
{
	if (ZMASK(v.acb) == DIR)
	{
		v.r1 = e->a[MODA(cursor->index + 8)].hex;
		if (ft_is_reg(v.r1, v.r1, v.r1) && (cursor->carry = 1))
			cursor->reg[v.r1 - 1] = get_dir(e, cursor, 2, 4) |
				get_ind(e, cursor, 6);
		cursor->index += 9;
	}
	else if (ZMASK(v.acb) == IIR)
	{
		v.r1 = e->a[MODA(cursor->index + 6)].hex;
		if (ft_is_reg(v.r1, v.r1, v.r1) && (cursor->carry = 1))
			cursor->reg[v.r1 - 1] = get_ind(e, cursor, 2) |
				get_ind(e, cursor, 4);
		cursor->index += 7;
	}
	else if (ZMASK(v.acb) == IDR)
	{
		v.r1 = e->a[MODA(cursor->index + 8)].hex;
		if (ft_is_reg(v.r1, v.r1, v.r1) && (cursor->carry = 1))
			cursor->reg[v.r1 - 1] = get_ind(e, cursor, 2) |
				get_dir(e, cursor, 4, 4);
		cursor->index += 9;
	}
}

static void	ft_or_3(t_env *e, t_cursor *cursor, t_var v)
{
	if (ZMASK(v.acb) == DRR)
	{
		v.r1 = e->a[MODA(cursor->index + 6)].hex;
		v.r2 = e->a[MODA(cursor->index + 7)].hex;
		if (ft_is_reg(v.r1, v.r2, v.r2) && (cursor->carry = 1))
			cursor->reg[v.r2 - 1] = cursor->reg[v.r1 - 1] |
				get_dir(e, cursor, 2, 4);
		cursor->index += 8;
	}
	else if (ZMASK(v.acb) == DDR)
	{
		v.r1 = e->a[MODA(cursor->index + 10)].hex;
		if (ft_is_reg(v.r1, v.r1, v.r1) && (cursor->carry = 1))
			cursor->reg[v.r1 - 1] = get_dir(e, cursor, 2, 4) |
				get_dir(e, cursor, 6, 4);
		cursor->index += 11;
	}
	else
		ft_or_4(e, cursor, v);
}

static void	ft_or_2(t_env *e, t_cursor *cursor, t_var v)
{
	if (ZMASK(v.acb) == RIR)
	{
		v.r1 = e->a[MODA(cursor->index + 2)].hex;
		v.r2 = e->a[MODA(cursor->index + 5)].hex;
		if (ft_is_reg(v.r1, v.r2, v.r2) && (cursor->carry = 1))
			cursor->reg[v.r2 - 1] = cursor->reg[v.r1 - 1] |
				get_ind(e, cursor, 3);
		cursor->index += 6;
	}
	else if (ZMASK(v.acb) == IRR)
	{
		v.r1 = e->a[MODA(cursor->index + 4)].hex;
		v.r2 = e->a[MODA(cursor->index + 5)].hex;
		if (ft_is_reg(v.r1, v.r2, v.r2) && (cursor->carry = 1))
			cursor->reg[v.r2 - 1] = cursor->reg[v.r1 - 1] |
				get_ind(e, cursor, 2);
		cursor->index += 6;
	}
	else
		ft_or_3(e, cursor, v);
}

void		ft_or(t_env *e, t_cursor *cursor)
{
	t_var	v;

	v.acb = e->a[MODA(cursor->index + 1)].hex;
	if (ZMASK(v.acb) == RRR)
	{
		v.r1 = e->a[MODA(cursor->index + 2)].hex;
		v.r2 = e->a[MODA(cursor->index + 3)].hex;
		v.r3 = e->a[MODA(cursor->index + 4)].hex;
		if (ft_is_reg(v.r1, v.r2, v.r3) && (cursor->carry = 1))
			cursor->reg[v.r3 - 1] = cursor->reg[v.r1 - 1] |
				cursor->reg[v.r2 - 1];
		cursor->index += 5;
	}
	else if (ZMASK(v.acb) == RDR)
	{
		v.r1 = e->a[MODA(cursor->index + 2)].hex;
		v.r2 = e->a[MODA(cursor->index + 7)].hex;
		if (ft_is_reg(v.r1, v.r2, v.r2) && (cursor->carry = 1))
			cursor->reg[v.r2 - 1] = cursor->reg[v.r1 - 1] |
				get_dir(e, cursor, 3, 4);
		cursor->index += 8;
	}
	else
		ft_or_2(e, cursor, v);
}
