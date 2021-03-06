/* file "x86_halt/recipe.h" */

/*
    Copyright (c) 2000 The President and Fellows of Harvard College

    All rights reserved.

    This software is provided under the terms described in
    the "machine/copyright.h" include file.
*/

#ifndef X86_HALT_RECIPE_H
#define X86_HALT_RECIPE_H

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma interface "x86_halt/recipe.h"
#endif

#include <machine/machine.h>
#include <cfg/cfg.h>
#include <halt/halt.h>

extern Vector<HaltRecipe*> halt_recipes_x86;

void init_halt_recipes_x86();
void clear_halt_recipes_x86();

class HaltRecipeX86 : public HaltRecipe {
  public:
    HaltRecipeX86();

  protected:
    virtual void static_args(HaltLabelNote);
    virtual void build_save_set(NatSet *save, const NatSet *live);
    virtual void setup_stack();
    virtual void save_state(NatSet *save);
    virtual void insert_args();
    virtual void insert_call(ProcSym*);
    virtual void clean_args();
    virtual void restore_state(NatSet *save);
    virtual void destroy_stack();

    void fp_state_builder(NatSet*);
    int jcc_to_setcc(int opcode);

    // some useful values
    Opnd cur_stack_loc;		// [esp]
    Opnd next_stack_loc;	// [esp - 4]
    int bytes_pushed;		// # bytes pushed onto the stack by save_state

};


class HaltRecipeX86Startup : public HaltRecipeX86 {
  public:
    HaltRecipeX86Startup() { }
    virtual ~HaltRecipeX86Startup() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *,
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Cbr : public HaltRecipeX86 {
  public:
    HaltRecipeX86Cbr() { }
    virtual ~HaltRecipeX86Cbr() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *,
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Entry : public HaltRecipeX86 {
  public:
    HaltRecipeX86Entry() { }
    virtual ~HaltRecipeX86Entry() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *,
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Exit : public HaltRecipeX86 {
  public:
    HaltRecipeX86Exit() { }
    virtual ~HaltRecipeX86Exit() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *,
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Mbr : public HaltRecipeX86 {
  public:
    HaltRecipeX86Mbr() { }
    virtual ~HaltRecipeX86Mbr() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Load : public HaltRecipeX86 {
  public:
    HaltRecipeX86Load() { }
    virtual ~HaltRecipeX86Load() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
    int num_bytes_ld (InstrHandle h);
};

class HaltRecipeX86Store : public HaltRecipeX86 {
  public:
    HaltRecipeX86Store() { }
    virtual ~HaltRecipeX86Store() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
    int num_bytes_st (InstrHandle h);
};

class HaltRecipeX86Block : public HaltRecipeX86 {
  public:
    HaltRecipeX86Block() { }
    virtual ~HaltRecipeX86Block() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Cycle : public HaltRecipeX86 {
  public:
    HaltRecipeX86Cycle() { }
    virtual ~HaltRecipeX86Cycle() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Setjmp : public HaltRecipeX86 {
  public:
    HaltRecipeX86Setjmp() { }
    virtual ~HaltRecipeX86Setjmp() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
};

class HaltRecipeX86Longjmp : public HaltRecipeX86 {
  public:
    HaltRecipeX86Longjmp() { }
    virtual ~HaltRecipeX86Longjmp() { }

    // target and instrumentation-kind specific handler
    virtual void operator()(HaltLabelNote, InstrHandle, CfgNode *, 
			    const NatSet *before, const NatSet *after);
};

#endif /* X86_HALT_RECIPE_H */
