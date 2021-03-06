/* file "blpp/suif_pass.cpp" */

/*
    Copyright (c) 2000 The President and Fellows of Harvard College

    All rights reserved.

    This software is provided under the terms described in
    the "machine/copyright.h" include file.
*/

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma implementation "blpp/suif_pass.h"
#endif

#include <machine/pass.h>
#include <machine/machine.h>
#include <cfg/cfg.h>
#include <cfa/cfa.h>
#include <halt/halt.h>

#include "blpp.h"
#include "suif_pass.h"

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif

extern "C" void
init_blpp(SuifEnv *suif_env)
{
    static bool init_done = false;

    if (init_done)
	return;
    init_done = true;

    ModuleSubSystem *mSubSystem = suif_env->get_module_subsystem();
    mSubSystem->register_module(new BlppSuifPass(suif_env));

    // initialize the libraries required by this OPI pass
    init_suifpasses(suif_env);
    init_machine(suif_env);
    init_cfg(suif_env);
    init_cfa(suif_env);
    init_halt(suif_env);
}

BlppSuifPass::BlppSuifPass(SuifEnv *suif_env, const IdString& name)
    : PipelinablePass(suif_env, name)
{
    the_suif_env = suif_env;	// bind suif_env into our global environment
}

BlppSuifPass::~BlppSuifPass()
{
    // empty
}

void
BlppSuifPass::initialize()
{
    PipelinablePass::initialize();

    // Create grammar for parsing the command line.  This must occur
    // after the parent class's initialize routine has been executed.
    _command_line->set_description("Ball and Larus path profiling");

    // zero or more file names
    file_names = new OptionString("file name");
    OptionLoop *files =
	new OptionLoop(file_names,
		       "names of optional input and/or output files");
    _command_line->add(files);
    o_fname = empty_id_string;
}

bool
BlppSuifPass::parse_command_line(TokenStream *command_line_stream)
{
    blpp.proc_def = 0;

    if (!PipelinablePass::parse_command_line(command_line_stream))
	return false;

    // currently there are no command line options for this pass
    o_fname = process_file_names(file_names);

    return true;
}

void
BlppSuifPass::execute()
{
    PipelinablePass::execute();

    // Process the output file name, if any.
    if (!o_fname.is_empty())
        the_suif_env->write(o_fname.chars());
}

void
BlppSuifPass::do_file_set_block(FileSetBlock *fsb)
{
    claim(o_fname.is_empty() || fsb->get_file_block_count() == 1,
	  "Command-line output file => file set must be a singleton");

    set_opi_predefined_types(fsb);
}

void
BlppSuifPass::do_file_block(FileBlock *fb)
{
    claim(has_note(fb, k_target_lib),
	  "expected target_lib annotation on file block");

    focus(fb);

    blpp.initialize();
}

void
BlppSuifPass::do_procedure_definition(ProcedureDefinition *pd)
{
    focus(pd);
    blpp.do_opt_unit(pd);
    blpp.proc_def++;
    defocus(pd);
}

void
BlppSuifPass::finalize()
{ 
    blpp.finalize();
}
