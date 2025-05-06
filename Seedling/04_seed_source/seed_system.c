#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


// Function to process the lend instruction
void process_system_instruction(enum scope_type current_scope) 
{
    call_system(_call_system, "call_system");
    encode_system_instruction();

    scan(&Token);
    semicolon(_semicolon, ";");
}