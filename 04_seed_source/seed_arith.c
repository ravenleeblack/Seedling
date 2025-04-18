#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


void process_arith_instruction(enum scope_type current_scope) 
{
    phrase_retrievel dest_index;
    phrase_retrievel src_index;
    
    int arith_label_type = 0;

    switch(Token.token_rep)
    {
        case _add_den:   add_den(_add_den, "add_den");         arith_label_type = 1;  current_architecture = 8;    break;
        case _add_bay:   add_bay(_add_bay, "add_bay");         arith_label_type = 1;  current_architecture = 16;   break;
        case _add_aisle: add_aisle(_add_aisle, "add_aisle");   arith_label_type = 1;  current_architecture = 32;   break;
        case _add_zone:  add_zone(_add_zone, "add_zone");      arith_label_type = 1;  current_architecture = 64;   break;
    
        case _sub_den:   sub_den(_sub_den, "sub_den");         arith_label_type = 2;  current_architecture = 8;    break;
        case _sub_bay:   sub_bay(_sub_bay, "sub_bay");         arith_label_type = 2;  current_architecture = 16;   break;
        case _sub_aisle: sub_aisle(_sub_aisle, "sub_aisle");   arith_label_type = 2;  current_architecture = 32;   break;
        case _sub_zone:  sub_zone(_sub_zone, "sub_zone");      arith_label_type = 2;  current_architecture = 64;   break;

        case _mul_den:   mul_den(_mul_den, "mul_den");         arith_label_type = 3;  current_architecture = 8;    break;
        case _mul_bay:   mul_bay(_mul_bay, "mul_bay");         arith_label_type = 3;  current_architecture = 16;   break;
        case _mul_aisle: mul_aisle(_mul_aisle, "mul_aisle");   arith_label_type = 3;  current_architecture = 32;   break;
        case _mul_zone:  mul_zone(_mul_zone, "mul_zone");      arith_label_type = 3;  current_architecture = 64;   break;

        case _div_den:   div_den(_div_den, "div_den");         arith_label_type = 4;  current_architecture = 8;    break;
        case _div_bay:   div_bay(_div_bay, "div_bay");         arith_label_type = 4;  current_architecture = 16;   break;
        case _div_aisle: div_aisle(_div_aisle, "div_aisle");   arith_label_type = 4;  current_architecture = 32;   break;
        case _div_zone:  div_zone(_div_zone, "div_zone");      arith_label_type = 4;  current_architecture = 64;   break;

        default: break;
    }

    scan(&Token);
    colon(_colon, ":");

    scan(&Token);        
    dest_index = parse_first_phrase(current_scope, current_architecture);                 // Handle destination operand or destination phrase
    encode_arith_dest_instruction(arith_label_type, current_architecture, dest_index);

    scan(&Token);
    comma(_comma, ",");

    scan(&Token);
    src_index = parse_second_phrase(current_scope, current_architecture);                 // Handle source operand or sorce phrase
    encode_arith_src_instruction(arith_label_type, current_architecture, src_index);

    scan(&Token);
    semicolon(_semicolon, ";"); 
}
