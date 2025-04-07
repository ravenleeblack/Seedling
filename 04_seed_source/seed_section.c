#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"


/* have to setup up different process sections functiond for each scope so that we can handle
specific footer synax for each different scope. For example right now main global should be the
only one allowed to call yield. Everyone else should either pass_arg a register for a stack
related global or local or pass_arg the num_value as zero so theres no return label. Debating
on global and local block labels if its worth adding in the ability to jump from an un-limited
loop when the condition is met and jump to its foot so we can return that way instead of having
to call an additional label. The language is already kind of wordy.*/
void process_sections(enum scope_type current_scope)
{
    scan(&Token);
    lbracket(_lbracket, "{");

    while(1)
    {
        scan(&Token);

        if(Token.token_rep == _period)
        {
            period(_period, ".");
            
            scan(&Token);
            switch(Token.token_rep)
            { 
                case _file_section:     process_file_section(current_scope);        break;
                case _declare_section:  process_declare_section(current_scope);     break;
                case _assign_section:   process_assign_section(current_scope);      break;
                case _literal_section:  process_literal_section(current_scope);     break;
                case _code_section:     process_code_section(current_scope);        break;

                case _arch_8_section:   process_arch_section(current_scope);        break;
                case _arch_16_section:  process_arch_section(current_scope);        break;
                case _arch_32_section:  process_arch_section(current_scope);        break;
                case _arch_64_section:  process_arch_section(current_scope);        break;
                default: break;
            }
        }
        else if(Token.token_rep == _rbracket)
        {
            rbracket(_rbracket, "}");

            scan(&Token);
            if(Token.token_rep == _pass_arg)
            {
                 process_pass_arg_instruction(current_scope);
            }
            if(Token.token_rep == _call)
            {
                /*special case: we need to setup up the flags for main to call yield only*/
                call(_call, "call");
    
                scan(&Token);
                ident(_ident, Text);
                strcpy(manager_call_buffer, Text);

                switch (current_scope)
                {
                    case scope_universal:    search_universal_scope(Text);    break;
                    case scope_global:       search_global_scope(Text);       break;
                    case scope_global_block: search_global_block_scope(Text); break;
                    case scope_local:        search_local_scope(Text);        break;
                    case scope_local_block:  search_local_block_scope(Text);  break;
                    default: error("ident error: invalid ident token"); break;
                }

                encode_call_manager_instruction(manager_call_buffer);
                
                scan(&Token);
                semicolon(_semicolon, ";");
            }
            return 0;
        }
    }
}

