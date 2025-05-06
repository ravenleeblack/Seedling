#include "seed_defs.h"  
#include "seed_data.h"   
#include "seed_decl.h"


/*Reset only file-specific state (but not global flags) before processing each source file.*/
void reset_file_state(void)
{
    comp_line_pos = 0;
    putback_char = 0;

    is_main_entry = 0;

    global_id = 0;
    local_id = 0;
    global_block_id = 0;
    local_block_id = 0;

    seed_in = NULL;
    seed_out = NULL;

    RejCount = 0;
}

/* Global initialization (called once at startup)*/
void initialize(void)
{
    comp_line_pos = 0;
    putback_char = '\n';

    debug_flag = 0;
    scope_table_flag = 0;
    treemap_flag = 0;
    output_flag = 0;
    assembly_flag = 0;

    nasm_flag = 0;
    rootling_flag = 0;

    is_main_entry = 0;

    global_id = 0;
    local_id = 0;
    global_block_id = 0;
    local_block_id = 0;

    seed_in = NULL;
    seed_out = NULL;
    debug_table_out = NULL;
    scope_table_out = NULL;
    nasm_out = NULL;
    root_out = NULL;
    output = NULL;
    first_pass = 0;
}


char extern_file_name[64];

int universal_label_counter = 0;
int global_label_counter = 0;
int global_block_label_counter = 0;
int local_label_counter = 0;
int local_block_label_counter = 0;


/*A simple structure to hold the list of source files.*/
typedef struct {
    char** files;
    int count;
    int capacity;
} source_file_list;

source_file_list* create_file_list(int capacity) 
{
    source_file_list* list = malloc(sizeof(source_file_list));
    if (!list) return NULL;
    list->files = malloc(capacity * sizeof(char*));
    if (!list->files) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = capacity;
    return list;
}

void add_file_to_list(source_file_list* list, const char* filename)
{
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        char** new_files = realloc(list->files, list->capacity * sizeof(char*));
        if (!new_files) {
            fprintf(stderr, "Error: Unable to allocate memory for file list\n");
            exit(1);
        }
        list->files = new_files;
    }
    list->files[list->count++] = strdup(filename);
}

void free_file_list(source_file_list* list) 
{
    for (int i = 0; i < list->count; i++) {
        free(list->files[i]);
    }
    free(list->files);
    free(list);
}


/*Opens the three temporary files in "w+" mode (clears the file and allows reading).*/
void open_temp_files(void)
{
    temp_data = fopen("temp_data.asm", "w+");
    if (!temp_data) {
        fprintf(stderr, "Error: Unable to open temp_data.asm\n");
        exit(1);
    }

    temp_bss = fopen("temp_bss.asm", "w+");
    if (!temp_bss) {
        fprintf(stderr, "Error: Unable to open temp_bss.asm\n");
        exit(1);
    }

    temp_text = fopen("temp_text.asm", "w+");
    if (!temp_text) {
        fprintf(stderr, "Error: Unable to open temp_text.asm\n");
        exit(1);
    }
}


/*Copies the contents of an open FILE pointer into the given output FILE. It reads until EOF without flushing the input pointer first.*/
void copy_temp_content(FILE* src, FILE* output)
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), src)) {
        fputs(buffer, output);
    }
}


/* Writes the contents of the open temporary file pointers into the final output file.
   The file pointers must be rewound (set to the beginning) before calling this function.
*/
void write_nasm_sections_from_fp(const char* output_filename)
{
    FILE* output = fopen(output_filename, "a");
    if (!output) {
        fprintf(stderr, "Error: Unable to open output file %s: %s\n", output_filename, strerror(errno));
        return;
    }

    // For each temp file, if its file size is nonzero, write the section header and then its contents.
    // Note: We do not flush these temp files before copying.
    long size;

    // temp_data.asm --> section .data
    fseek(temp_data, 0, SEEK_END);
    size = ftell(temp_data);
    if (size > 0) {
        rewind(temp_data);
        fprintf(output, "section .data\n");
        copy_temp_content(temp_data, output);
    }

    // temp_bss.asm --> section .bss
    fseek(temp_bss, 0, SEEK_END);
    size = ftell(temp_bss);
    if (size > 0) {
        rewind(temp_bss);
        fprintf(output, "\nsection .bss\n");
        copy_temp_content(temp_bss, output);
    }

    // temp_text.asm --> section .text
    fseek(temp_text, 0, SEEK_END);
    size = ftell(temp_text);
    if (size > 0) {
        rewind(temp_text);
        fprintf(output, "\nsection .text\n");
        copy_temp_content(temp_text, output);
    }

    fclose(output);
}


/*Flushes and closes the temporary files.*/
void close_temp_files(void)
{
    if (temp_data) { fflush(temp_data); fclose(temp_data); }
    if (temp_bss)  { fflush(temp_bss);  fclose(temp_bss); }
    if (temp_text) { fflush(temp_text); fclose(temp_text); }
}

/*
  Main processing loop.
  For each source file, the following occurs:
    1. Reset file-specific state.
    2. Open the source file.
    3. Open the 3 temp files (in "w+" mode).
    4. Call begin_prog() to process the source file which has output functions that write output to the temp files.
    5. Rewind the temp files and copy their contents into the final output file (using the proper filename and .asm extension).
    6. Flush and close the temp files.
    7. Close the source file.
*/


int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input file> ...\n", argv[0]);
        return 1;
    }

    int result = 0;
    initialize();

    source_file_list* file_list = create_file_list(40);
    if (!file_list) {
        fprintf(stderr, "Error: Unable to create file list\n");
        return 1;
    }

    // Initialize the scope table system.
    cleanup_scope_table_system();
    init_scope_table_system();

    // Parse command-line arguments.
    for (int i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "-o") == 0) 
        {
            output_flag = 1;
        } 
        else if (strcmp(argv[i], "-d") == 0) 
        {
            debug_flag = 1;
            debug_table_out = fopen("debug.txt", "w");
            if (!debug_table_out) {
                fprintf(stderr, "Error: Unable to open scope_table.txt: %s\n", strerror(errno));
                free_file_list(file_list);
                return 1;
            }
        } 
        else if (strcmp(argv[i], "-n") == 0) 
        {
            nasm_flag = 1;                         //create a nasm output
        }
        else if (strcmp(argv[i], "-t") == 0) 
        {
            scope_table_flag = 1;
            scope_table_out = fopen("scope_table.txt", "w");
            if (!scope_table_out) {
                fprintf(stderr, "Error: Unable to open scope_table.txt: %s\n", strerror(errno));
                free_file_list(file_list);
                return 1;
            }
        } 
        else if (argv[i][0] != '-')
        {
            add_file_to_list(file_list, argv[i]);
        }
    }

    printf("Number of files: %d\n", file_list->count);
    // Process each source file.
    for (int i = 0; i < file_list->count; i++) 
    {
        printf("File %d: %s\n", i, file_list->files[i]);

        reset_file_state();

        // Open the temporary files in "w+" mode.
        open_temp_files();

        // Open the current source file.
        seed_in = fopen(file_list->files[i], "r");
        if (!seed_in) {
            fprintf(stderr, "Error: Unable to open input file %s: %s\n", file_list->files[i], strerror(errno));
            free_file_list(file_list);
            return 1;
        }

        printf("Calling begin_prog() for %s\n", file_list->files[i]);

        // Process the source file (begin_prog() writes to the temp files).
        RejCount = 0;  // Reset rejection buffer explicitly
        clearerr(seed_in);  // Clear any EOF/error state
        rewind(seed_in);    // Ensure we start at the beginning

        result = begin_prog();
        
        printf("Finished begin_prog() for %s with result %d\n", file_list->files[i], result);

        // Build the output filename based on the source file name.
        strncpy(output_filename, file_list->files[i], sizeof(output_filename) - 5);
        char* dot = strrchr(output_filename, '.');
        if (dot) *dot = '\0';
        strncat(output_filename, ".asm", sizeof(output_filename) - strlen(output_filename) - 1);

        // Step 5: Rewind the temp files and copy their contents to the output file.
        if (nasm_flag) {
            rewind(temp_data);
            rewind(temp_bss);
            rewind(temp_text);
            write_nasm_sections_from_fp(output_filename);
        }

       
        close_temp_files();  // Step 6: Flush and close the temp files.
        fclose(seed_in);     // Step 7: Close the source file.
    }

    if (scope_table_flag && scope_table_out) {
        print_all_scope_tables(scope_table_out);
        fclose(scope_table_out);
    }

    cleanup_scope_table_system();
    free_file_list(file_list);
    return result;
}
