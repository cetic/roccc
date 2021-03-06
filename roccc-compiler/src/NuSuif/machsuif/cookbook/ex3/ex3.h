/* file "ex3/ex3.h" -- Cookbook example #3 */

/*
    Copyright (c) 2000 The President and Fellows of Harvard College

    All rights reserved.

    This software is provided under the terms described in
    the "machine/copyright.h" include file.
*/

#ifndef EX3_EX3_H
#define EX3_EX3_H

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma interface "ex3/ex3.h"
#endif


class Ex3 {
  public:
    Ex3() { }

    void initialize();
    void do_opt_unit(OptUnit*);
    void finalize();

    // set pass options
    void set_reserved_reg(IdString n)	{ reserved_reg_name = n; }

  protected:
    // pass-option variables
    IdString reserved_reg_name;	// name of register to reserve (optional)

    // initialization variables
    int reserved_reg;		// its abstract number
    TypeId reserved_reg_type;	// its generic type
    Opnd reserved_reg_opnd;	// its register operand

    // markers for inserted instructions
    NoteKey k_reserved_reg_load;
    NoteKey k_store_reserved_reg;
};

#endif /* EX3_EX3_H */
