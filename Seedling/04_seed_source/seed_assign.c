#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"

void process_assign_section(enum scope_type current_scope)
{
    assign(_assign_section, "assign_sect");
   
    while(1)    // loop the .assign section body and get all the assigments
    {
        scan(&Token);
        
        if(Token.token_rep == _period)
        {
            period(_period, ".");
            
            scan(&Token);
            end(_end, "end");
            assign_flag = 0;  // Reset here after all assignments are done
            return 0;
        }
        if(Token.token_rep == _assign)
        {
            phrase_retrievel src_index;

            assign(_assign, "assign");

            scan(&Token);
            colon(_colon, ":");

            scan(&Token);
            ident(_ident, Text); 
            strcpy(assign_buffer, Text);

            switch(current_scope)
            {
                case scope_universal:    search_universal_scope(Text);    break;  
                case scope_global:       search_global_scope(Text);       break;
                case scope_global_block: search_global_block_scope(Text); break;
                case scope_local:        search_local_scope(Text);        break;
                case scope_local_block:  search_local_block_scope(Text);  break;
                default: error("seeding error: assign error: Invalid scope");           break;
            }

            scan(&Token);
            assigner(_assigner, "=");

            scan(&Token);
            src_index = parse_num_literal(current_scope); 
               
            if(assign_flag == 1)  
            {
                encode_assign_table_instruction(assign_buffer, 4, src_index);
            } 
            else
            {
                //encode_assign_hold_instruction(assign_buffer, 4, src_index);
                encode_assign_with_num_section(assign_buffer, 4, src_index);
            }

            scan(&Token);
            semicolon(_semicolon, ";");
        }
        if(Token.token_rep == _load_elem)
        {
            phrase_retrievel src_index;
            load_elem(_load_elem, "load_elem");

            scan(&Token);
            colon(_colon, ":");

            scan(&Token);
            ident(_ident, Text); 
            strcpy(assign_buffer, Text);

            switch(current_scope)
            {
                case scope_universal:    search_universal_scope(Text);    break;  
                case scope_global:       search_global_scope(Text);       break;
                case scope_global_block: search_global_block_scope(Text); break;
                case scope_local:        search_local_scope(Text);        break;
                case scope_local_block:  search_local_block_scope(Text);  break;
                default: error("seeding error: assign error: Invalid scope");           break;
            }

            scan(&Token);
            assigner(_assigner, "=");

            scan(&Token);
            src_index = parse_elem_literal(current_scope, 4); 
            encode_assign_table_instruction(assign_buffer, 4, src_index);
        }
    }
}


/* Here we have the .assign section for seedling. In nasm doe it  goes your variable, how many bytes, and value.
So encode_assign_section is handling 2 parts of that. We pass the ident we found earlier as the first argument then
we pass the num literal as the value for the .data section in nasm. The encode_assign_section function handles the
byte right now but we will need to handle it differently later so that we gain access to all the avaiable byte sizes.

Outside that this function is failry understandable. We parse the section keyword .assign, then we parse the actual
assignments. Where we always have assign: name = 5;  So we always have the keyword assign followed by colon for read
ability then we have our placeholder or variable we going to give some value then we assign that placeholder a num literl
value. This will be different later. We will have to add other data type values later. It will be in the sense that
since we have already declare the placeholder in .declare then we need to assign the proper data type value in .assign
instead of just having whole number value like we do right now. Then like most things we end with a semicolon.  */