#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


void process_push_instruction(enum scope_type current_scope) 
{
    phrase_retrievel src_index;
 
    /* or it can be said that we use den for 8 bit, bay for 16 bit, aisle for 32 bit, and zone fore for 64 bit*/
    switch(Token.token_rep)
    {
        case _push_den:    push_den(_push_den, "push_den");          current_architecture = 8;     break;   // 1 unsigned byte
        case _push_dens:   push_dens(_push_dens, "push_dens");       current_architecture = 8;     break;   // 1 signed byte
        case _push_bay:    push_bay(_push_bay, "push_bay");          current_architecture = 16;    break;   // 2 unsigned byte
        case _push_bays:   push_bays(_push_bays, "push_bays");       current_architecture = 16;    break;   // 2 signed byte
        case _push_aisle:  push_aisle(_push_aisle, "push_aisle");    current_architecture = 32;    break;   // 4 unsigned byte
        case _push_aisles: push_aisles(_push_aisles, "push_aisles"); current_architecture = 32;    break;   // 4 signed byte
        case _push_zone:   push_zone(_push_zone, "push_zone");       current_architecture = 64;    break;   // 8 unsigned byte
        case _push_zones:  push_zones(_push_zones, "push_zones");    current_architecture = 64;    break;   // 8 signed byte
    }

    scan(&Token);
    colon(_colon, ":");

    scan(&Token);
    src_index = parse_second_phrase(current_scope, current_architecture);
    encode_push_instruction(current_architecture, src_index);
    
    scan(&Token);
    semicolon(_semicolon, ";");
}

void process_pop_instruction(enum scope_type current_scope) 
{
    phrase_retrievel src_index;

    /* or it can be said that we use den for 8 bit, bay for 16 bit, aisle for 32 bit, and zone for 64 bit */
    switch(Token.token_rep)
    {
        case _pop_den:    pop_den(_pop_den, "pop_den");          current_architecture = 8;    break;   // 1 unsigned byte
        case _pop_dens:   pop_dens(_pop_dens, "pop_dens");       current_architecture = 8;    break;   // 1 signed byte
        case _pop_bay:    pop_bay(_pop_bay, "pop_bay");          current_architecture = 16;   break;   // 2 unsigned byte
        case _pop_bays:   pop_bays(_pop_bays, "pop_bays");       current_architecture = 16;   break;   // 2 signed byte
        case _pop_aisle:  pop_aisle(_pop_aisle, "pop_aisle");    current_architecture = 32;   break;   // 4 unsigned byte
        case _pop_aisles: pop_aisles(_pop_aisles, "pop_aisles"); current_architecture = 32;   break;   // 4 signed byte
        case _pop_zone:   pop_zone(_pop_zone, "pop_zone");       current_architecture = 64;   break;   // 8 unsigned byte
        case _pop_zones:  pop_zones(_pop_zones, "pop_zones");    current_architecture = 64;   break;   // 8 signed byte
        default: break;
    }
  
    scan(&Token);
    colon(_colon, ":");

    scan(&Token);
    src_index = parse_first_phrase(current_scope, current_architecture);           // Handle destination operand or destination phrase
    encode_pop_instruction(current_architecture, src_index);
    
    scan(&Token);
    semicolon(_semicolon, ";");
}