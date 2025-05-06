#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


void process_log_section(enum scope_type current_scope)
{
    log_sect(_log_section, "log_sect");


    while(1)    // loop the .assign section body and get all the assigments
    {
        scan(&Token);
        
        if(Token.token_rep == _period)
        {
            period(_period, ".");
            
            scan(&Token);
            end(_end, "end");
            return 0;
        }
        if(Token.token_rep == _log)
        {
            log_label(_log, "log");

            scan(&Token);
            ident(_ident, Text);
            strcpy(log_buffer, Text);
        
            switch (current_scope)
            {
                case scope_universal:    search_universal_scope(Text);    break;
                case scope_global:       search_global_scope(Text);       break;
                case scope_global_block: search_global_block_scope(Text); break;
                case scope_local:        search_local_scope(Text);        break;
                case scope_local_block:  search_local_block_scope(Text);  break;
                default: error("ident error: invalid ident token"); break;
            }
        
            scan(&Token);
            colon(_colon, ":");

            process_log_body_section(current_scope, log_buffer);
        }
    }
}

void process_log_body_section(enum scope_type current_scope, char *log_name)
{
    while(1)    // loop the .assign section body and get all the assigments
    {
        scan(&Token);
        
        if(Token.token_rep == _end_log)
        {
            end_log(_end_log, "end_log");
            
            scan(&Token);
            semicolon(_semicolon, ";");
            return 0;
        }
        else if(Token.token_rep == _offset)
        {
            phrase_retrievel src_index;
            log_offset(_offset, "offset");

            scan(&Token);  // Get type
            declare_type = parse_type(current_scope);
            byte_size = get_byte_size(declare_type); // Get byte size
            transfer_byte_size = byte_size;

            scan(&Token);
            colon(_colon, ":");

            scan(&Token);
            ident(_ident, Text); 
            strcpy(offset_buffer, Text);

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
               
            encode_log_phrase(byte_size, log_name, offset_buffer, src_index);

            scan(&Token);
            semicolon(_semicolon, ";");
        }
    }
}

