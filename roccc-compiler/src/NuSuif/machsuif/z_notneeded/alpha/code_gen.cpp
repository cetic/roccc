/* file "alpha/code_gen.cpp" */

/*
    Copyright (c) 2000 The President and Fellows of Harvard College

    All rights reserved.

    This software is provided under the terms described in
    the "machine/copyright.h" include file.
*/

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma implementation "alpha/code_gen.h"
#endif

#include <machine/machine.h>

#include <alpha/code_gen.h>

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif

/* CodeGenAlpha::init() -- This routine completes the initialization of
 * the variables needed during translation of the current procedure.
 */
void
CodeGenAlpha::init(OptUnit *unit)
{
    CodeGen::init(unit);

    claim(struct_lds.empty());
}


/*
 * CodeGenAlpha::finish() -- Finalize code generation:
 *
 * o  Make sure the struct_lds list has been consumed by corresponding
 *    stores.
 *
 * o  Do base-class finalizations, e.g., record any information gathered
 *    during code generation that needs to be kept for later passes by
 *    placing it in annotations.
 */
void
CodeGenAlpha::finish(OptUnit *unit)
{
    claim(struct_lds.empty());

    CodeGen::finish(unit);
}
