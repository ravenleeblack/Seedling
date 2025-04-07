#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"



void process_local_block_label(int parent_global_id)
{
    local_block(_local_block, "local_block");
    scan(&Token);
    ident(_ident, Text);
    local_block_id = insert_local_block_scope(Text, scope_local_block_tool, scope_local_block_label);
    encode_local_block_label(Text);
    local_block_label_counter++;

    scan(&Token);
    colon(_colon, ":");

    process_sections(scope_local_block);

    process_local_block_child_labels(local_block_id);
}


void process_local_block_child_labels(int parent_global_id)   
{
    while(1)
    {
        scan(&Token);

        if(Token.token_rep == _local ||Token.token_rep == _end_section || Token.token_rep == _enfi)
        {
            reject_token(&Token);
            break;
        }

        if(Token.token_rep == _local_block)
        {
            process_local_block_label(parent_global_id);
        }
    }
}