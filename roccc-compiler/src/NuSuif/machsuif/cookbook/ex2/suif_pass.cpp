/* file "ex2/suif_pass.cpp" */

/*
    Copyright (c) 2000 The President and Fellows of Harvard College

    All rights reserved.

    This software is provided under the terms described in
    the "machine/copyright.h" include file.
*/

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma implementation "ex2/suif_pass.h"
#endif

#include <machine/pass.h>
#include <machine/machine.h>

#include "ex2.h"
#include "suif_pass.h"

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif

extern "C" void
init_ex2(SuifEnv *suif_env)
{
    static bool init_done = false;

    if (init_done)
	return;
    init_done = true;

    ModuleSubSystem *mSubSystem = suif_env->get_module_subsystem();
    mSubSystem->register_module(new Ex2SuifPass(suif_env));

    // initialize the libraries required by this OPI pass
    init_suifpasses(suif_env);
    init_machine(suif_env);
}

Ex2SuifPass::Ex2SuifPass(SuifEnv *suif_env, const IdString& name)
    : PipelinablePass(suif_env, name)
{
    the_suif_env = suif_env;	// bind suif_env into our global environment
}

Ex2SuifPass::~Ex2SuifPass()
{
    // empty
}

void
Ex2SuifPass::initialize()
{
    PipelinablePass::initialize();

    // Create grammar for parsing the command line.  This must occur
    // after the parent class's initialize routine has been executed.
    _command_line->set_description("cookbook example #2");

    // zero or more file names
    file_names = new OptionString("file name");
    OptionLoop *files =
	new OptionLoop(file_names,
		       "names of optional input and/or output files");
    _command_line->add(files);
}

bool
Ex2SuifPass::parse_command_line(TokenStream *command_line_stream)
{
    o_fname = empty_id_string;

    if (!PipelinablePass::parse_command_line(command_line_stream))
	return false;

    o_fname = process_file_names(file_names);

    return true;
}

void
Ex2SuifPass::execute()
{
    PipelinablePass::execute();

    // Process the output file name, if any.
    if (!o_fname.is_empty())
        the_suif_env->write(o_fname.chars());
}

void
Ex2SuifPass::do_file_set_block(FileSetBlock *fsb)
{
    claim(o_fname.is_empty() || fsb->get_file_block_count() == 1,
	  "Command-line output file => file set must be a singleton");

    set_opi_predefined_types(fsb);
}

void
Ex2SuifPass::do_file_block(FileBlock *fb)
{
    claim(has_note(fb, k_target_lib),
	  "expected target_lib annotation on file block");

    focus(fb);

    ex2.initialize();
}

void
Ex2SuifPass::do_procedure_definition(ProcedureDefinition *pd)
{
    focus(pd);
    ex2.do_opt_unit(pd);
    defocus(pd);
}

void
Ex2SuifPass::finalize()
{ 
    ex2.finalize();
}
