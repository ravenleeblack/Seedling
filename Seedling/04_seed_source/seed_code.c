#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


void process_code_section(enum scope_type current_scope) 
{
    code(_code_section, "code_sect");
    
    int move_counter = 0;

    while(1) 
    {
        scan(&Token);
        
        if(Token.token_rep == _period)
        {
            period(_period, ".");
            
            scan(&Token);
            end(_end, "end");
            return 0;
        }
        switch(Token.token_rep) 
        {
            case _comp_den:     process_compare_instruction(current_scope );    break;
            case _comp_bay:     process_compare_instruction(current_scope );    break;
            case _comp_aisle:     process_compare_instruction(current_scope );    break;
            case _comp_zone:     process_compare_instruction(current_scope );    break;

            case _set_flag:    process_set_flag_instruction(current_scope);    break;
            case _test:        process_test_instruction(current_scope);        break;
            case _transfer:    process_transfer_instruction(current_scope); break;
            
            case _inc_den:      process_increment_instruction(current_scope);   break;
            case _inc_dens:     process_increment_instruction(current_scope);   break;
            case _inc_bay:      process_increment_instruction(current_scope);   break;
            case _inc_bays:     process_increment_instruction(current_scope);   break;
        
            case _inc_aisle:     process_increment_instruction(current_scope);   break;
            case _inc_aisles:    process_increment_instruction(current_scope);   break;
            case _inc_zone:      process_increment_instruction(current_scope);   break;
            case _inc_zones:     process_increment_instruction(current_scope);   break;

            case _dec_den:      process_decrement_instruction(current_scope);   break;
            case _dec_dens:     process_decrement_instruction(current_scope);   break;
            case _dec_bay:      process_decrement_instruction(current_scope);   break;
            case _dec_bays:     process_decrement_instruction(current_scope);   break;
        
            case _dec_aisle:     process_decrement_instruction(current_scope);   break;
            case _dec_aisles:    process_decrement_instruction(current_scope);   break;
            case _dec_zone:      process_decrement_instruction(current_scope);   break;
            case _dec_zones:     process_decrement_instruction(current_scope);   break;

            case _call:          process_call_instruction(current_scope);       break;
            case _call_system:   process_system_instruction(current_scope);        break;

            case _add_den:   process_addition_instruction(current_scope);         break;
            case _add_bay:   process_addition_instruction(current_scope);         break;
            case _add_aisle: process_addition_instruction(current_scope);         break;
            case _add_zone:  process_addition_instruction(current_scope);         break;
    
            case _sub_den:   process_subtraction_instruction(current_scope);      break;
            case _sub_bay:   process_subtraction_instruction(current_scope);      break;
            case _sub_aisle: process_subtraction_instruction(current_scope);      break;
            case _sub_zone:  process_subtraction_instruction(current_scope);      break;
    
            case _mul_den:   process_multiplication_instruction(current_scope);   break;
            case _mul_bay:   process_multiplication_instruction(current_scope);   break;
            case _mul_aisle: process_multiplication_instruction(current_scope);   break;
            case _mul_zone:  process_multiplication_instruction(current_scope);   break;
    
            case _div_den:   process_division_instruction(current_scope);         break;
            case _div_bay:   process_division_instruction(current_scope);         break;
            case _div_aisle: process_division_instruction(current_scope);         break;
            case _div_zone:  process_division_instruction(current_scope);         break;

            /*push instructions by byte size*/
            case _push_den:    process_push_instruction(current_scope);  break;
            case _push_dens:   process_push_instruction(current_scope);  break;
            case _push_bay:    process_push_instruction(current_scope);  break;
            case _push_bays:   process_push_instruction(current_scope);  break;
            case _push_aisle:  process_push_instruction(current_scope);  break;
            case _push_aisles: process_push_instruction(current_scope);  break;
            case _push_zone:   process_push_instruction(current_scope);  break;
            case _push_zones:  process_push_instruction(current_scope);  break;
            
            case _pop_den:     process_pop_instruction(current_scope);    break;
            case _pop_dens:    process_pop_instruction(current_scope);    break;
            case _pop_bay:     process_pop_instruction(current_scope);    break;
            case _pop_bays:    process_pop_instruction(current_scope);    break;
            case _pop_aisle:   process_pop_instruction(current_scope);    break;
            case _pop_aisles:  process_pop_instruction(current_scope);    break;
            case _pop_zone:    process_pop_instruction(current_scope);    break;
            case _pop_zones:   process_pop_instruction(current_scope);    break;

            /*move instructions by byte size*/
            case _move_den:     process_move_instruction(current_scope);  break;
            case _move_dens:    process_move_instruction(current_scope);  break;
            case _move_bay:     process_move_instruction(current_scope);  break;
            case _move_bays:    process_move_instruction(current_scope);  break;
            case _move_aisle:   process_move_instruction(current_scope);  break;
            case _move_aisles:  process_move_instruction(current_scope);  break;
            case _move_zone:    process_move_instruction(current_scope);  break;
            case _move_zones:   process_move_instruction(current_scope);  break;

            /*push instructions by byte size*/
            case _jump:           process_jump_instruction(current_scope);  break;
            case _jump_zero:      process_jump_instruction(current_scope);  break;
            case _jump_less:      process_jump_instruction(current_scope);  break;
            case _jump_neg:       process_jump_instruction(current_scope);  break;
            case _jump_great:     process_jump_instruction(current_scope);  break;
            case _jump_equal:     process_jump_instruction(current_scope);  break;
            case _jump_not_equal: process_jump_instruction(current_scope);  break;
            default: break; 
        }
    }
}