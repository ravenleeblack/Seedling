#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"



int begin_prog(void)
{
    while(1)
    {
        scan(&Token);

        if(Token.token_rep == _enfi)
        {
            if(debug_flag && debug_table_out)
            {
                fprintf(debug_table_out, " universal label counters: %d\n", universal_label_counter);
                fprintf(debug_table_out, " global label counters: %d\n", global_label_counter);
                fprintf(debug_table_out, " global block label counters: %d\n", global_block_label_counter);
                fprintf(debug_table_out, " local label counters: %d\n", local_label_counter);
                fprintf(debug_table_out, " local block label counters: %d\n", local_block_label_counter);

                fprintf(debug_table_out, "==============================================================================================================\n\n");
            }
            return 0;
        }
        
        if(Token.token_rep == _universal)
        {
            process_universal_label();
        }
        else if(Token.token_rep == _global)
        {
            process_global_label();
        }
    }
    return 0;
}

/*Here is the beginning of our program. We always process universal scope first because its the
entry point for assembly and the linker. Then we prococess global scope. If it isnt one of these
two scopes then we must have reached and enfi. Since we hit the end of file. break and exit.*/

