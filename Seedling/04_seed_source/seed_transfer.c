#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


void process_transfer_instruction(enum scope_type current_scope) 
{
    phrase_retrievel dest_index;
    phrase_retrievel src_index;
    
    transfer(_transfer, "transfer");

    scan(&Token);
    colon(_colon, ":");
  
    scan(&Token);
    dest_index = parse_first_phrase(current_scope, current_architecture);           // Handle destination operand or destination phrase
    encode_transfer_dest_instruction(current_architecture, dest_index);

    scan(&Token);
    comma(_comma, ",");

    scan(&Token);
    src_index = parse_second_phrase(current_scope, 8);           // Handle destination operand or destination phrase
    encode_transfer_src_instruction(current_architecture, src_index, third_index);

    scan(&Token);
    semicolon(_semicolon, ";");
}