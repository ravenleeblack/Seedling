#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"

int process_universal_label(void)
{
    universal(_universal, "universal");

    scan(&Token);
    ident(_ident, Text);
    
    universal_id = insert_universal_scope(Text, scope_universal_tool, scope_universal_label);
    encode_universal_label(Text);
    universal_label_counter++;
    
    scan(&Token);
    colon(_colon, ":");

    if((strcmp(Text, "start") == 0))   // strcpy the universal scope label. There has to be a start for entry and can only be one.
    {
        is_entry_point = 1;

        process_sections(scope_universal);  // we need to create a process_universal_sections function
    }
    else
    {
       fprintf(stderr, " scope label error: There can only be one universal label and that label must be the start label.\n");
    }

    return 0;
}


// Seedling is scoped based instead of sections based like other assemblers. This mean our program is seperated into different
// scopes. For each of the scope we find a label will be tied to that scope so we call them scope labels.

// Set flag if this is the entry point. We also do not want more then one universal label in a project. A universal _start
// is in the main file and handles all universals. It wouldnt work if we had other universal label names. We want one place
// to find all the universal data we need that is outside global and local labels. So we take the approach that there will
// always be one file, the main file, that has all universal scope data. Then  everything is connected to that file by either
// the use directive or by being external. So we either have the preprocessor bring in the file we need or we link any
// external dependecies our selves. Right now the assembler will take many files as arguments. It just needs to be linked
// together when it in it output form of nasm right now. I want to get it turned into machine code as soon as I can. 

/* Here we match the universal scope keyword then scan for the label. We insert that label into
the scope table, we also use the ident, as the entry point seedling and the nasm output. We then
get the colon to end the line and start parsing the body of the scope label. We use a loop and we 
process all sections until we hit a end_section. The end_section is our loop condition. Its how we
break out of the loop. So we can start parsing the global scope and its label.*/
