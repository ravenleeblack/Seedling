#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"

// Function to convert universal scope label into nasm
void encode_universal_label(const char *label_name)
{
	fprintf(temp_text, "global _start\n", label_name);
	fprintf(temp_text, "_start:\n", label_name);
}

// Function to convert global scope label into nasm
void encode_global_label(const char *label_name)
{
    if (strcmp(label_name, "main") == 0)  
    {
        fprintf(temp_text, "%s:\n", label_name);  // Just print the label
    }
    else  
    {
        fprintf(temp_text, "global %s\n", label_name);  // Declare as global
        fprintf(temp_text, "%s:\n", label_name);        // Print the label
    }
}

// Function to convert global block scope label into nasm
void encode_global_block_label(const char *label)
{
	fprintf(temp_text, "%s:\n", label);
}



// Function to convert local scope label into nasm
void encode_local_label(const char *label_name)
{
	fprintf(temp_text, "\n");
	fprintf(temp_text, ".%s:\n", label_name);
}

// Function to convert local block scope label into nasm
void encode_local_block_label(const char *label_name)
{
	fprintf(temp_text, "%s:\n", label_name);
}

// Function to add ret onto end of global scope label
void encode_pass_arg_label()
{
	fprintf(temp_text, "    ret\n");
}

void encode_extern_label(const char *label_name)
{
	fprintf(temp_text, "    extern %s\n", label_name);
}

void encode_use_label(const char *label_name)
{
	fprintf(temp_text, "\n");
    fprintf(temp_text, "    %%include \"%s.asm\"\n", label_name);
}



// Function to encode a Seedling call function instruction to NASM
void encode_call_function_instruction(const char *child_name)
{
	fprintf(temp_text, "    call .%s\n", child_name);
}

// Function to encode a Seedling call manager instruction to NASM
void encode_call_manager_instruction(const char *label)
{
	if (strcmp(label, "main") == 0)  
    {
        fprintf(temp_text, "    call %s\n", label);
		fprintf(temp_text, "\n");
    }
    else  
    {
       fprintf(temp_text, "    call %s\n", label);
    }
}



void encode_align_instruction(int architecture)
{
}

// function to convert a seedling declaration into nasm
void encode_declare_instruction(const char *ident, int byte_size, int type)
{
	switch (byte_size)
	{
		case 1: fprintf(temp_bss, "    %s resb %d\n", ident, type); break;
		case 2: fprintf(temp_bss, "    %s resw %d\n", ident, type); break;
		case 4: fprintf(temp_bss, "    %s resd %d\n", ident, type); break;
		case 8: fprintf(temp_bss, "    %s resq %d\n", ident, type); break;
		default: break;
	}
}

void encode_add_reg_with_num_section(phrase_retrievel num_value)
{
	fprintf(temp_text, "    + %d\n", num_value.phrase_num_value);
}

void encode_sub_reg_with_num_section(phrase_retrievel num_value)
{
	fprintf(temp_text, "    - %d\n", num_value.phrase_num_value);
}


void encode_assign_with_num_section(char *hold_name, int byte_size, phrase_retrievel num_value)
{
    switch (byte_size)
    {
        case 1: fprintf(temp_data, "    %s db %d\n", hold_name, num_value.phrase_num_value); break;
        case 2: fprintf(temp_data, "    %s dw %d\n", hold_name, num_value.phrase_num_value); break;
        case 4: fprintf(temp_data, "    %s dd %d\n", hold_name, num_value.phrase_num_value); break;
        case 8: fprintf(temp_data, "    %s dq %lld\n", hold_name, num_value.phrase_num_value); break;
        default: break;
    }
}

// function to convert a seedling placeholder assignment into nasm
void encode_assign_hold_instruction(char *ident, int byte_size, phrase_retrievel num_value)
{
	switch (byte_size)
	{
		case 1: fprintf(temp_text, "    mov byte [%s], %d\n", ident, num_value.phrase_num_value); break;
		case 2: fprintf(temp_text, "    mov word [%s], %d\n", ident, num_value.phrase_num_value); break;
		case 4: fprintf(temp_text, "    mov dword [%s], %d\n", ident, num_value.phrase_num_value); break;
		case 8: fprintf(temp_text, "    mov qword [%s], %d\n", ident, num_value.phrase_num_value); break;
		default: break;
	}
}

// function to convert a seedling table assignment into nasm
void encode_assign_table_instruction(char *ident, int byte_size, phrase_retrievel num_value)
{
	switch (byte_size)
	{
		case 1: fprintf(temp_bss, "    %s resb %d\n", ident, num_value.phrase_num_value); break;
		case 2: fprintf(temp_bss, "    %s resw %d\n", ident, num_value.phrase_num_value); break;
		case 4: fprintf(temp_bss, "    %s resd %d\n", ident, num_value.phrase_num_value); break;
		case 8: fprintf(temp_bss, "    %s resq %d\n", ident, num_value.phrase_num_value); break;
		default: break;
	}
}

// function to convert seedling arch type arch_08, arch_16, arch_32, arch_64 into a into nasm bit directive
void encode_arch_instruction(int architecture)
{
	switch (architecture)
	{
		case 8:  fprintf(output, "[bit %d]\n", architecture); break;
		case 16: fprintf(output, "[bit %d]\n", architecture); break;
		case 32: fprintf(output, "[bit %d]\n", architecture); break;
		case 64: fprintf(output, "[bit %d]\n", architecture); break;
		default: printf("Unknown architecture encoding\n");   break;
	}
}


void encode_arith_dest_instruction(int arith_type, int current_size, phrase_retrievel dest)
{
	if (dest.type != NULL)
	{
		switch(dest.type)
		{
			case phrase_fetch:   fprintf(temp_text, "[%s], ", dest.phrase); break;

			case phrase_num:
			switch(current_size)
			{
				case 8:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_num_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_num_value); break;
						default: break;
					}
				break;
				case 16:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_num_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_num_value); break;
						default: break;
					}
				break;
				case 32:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_num_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_num_value); break;
						default: break;
					}
				break;
				case 64:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_num_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_num_value); break;
						default: break;
					}
				break;
				default: break;
			}
			break;
			case phrase_register:
			switch(current_size)
			{
				case 8:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_reg_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_reg_value); break;
						default: break;
					}
				break;
				case 16:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_reg_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_reg_value); break;
						default: break;
					}
				break;
				case 32:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_reg_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_reg_value); break;
						default: break;
					}
				break;
				case 64:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, "    add %s,", dest.phrase_reg_value); break;
						case 2:  fprintf(temp_text, "    sub %s,", dest.phrase_reg_value); break;
						default: break;
					}
				break;
				default: break;
			}
			break;
			default: break;
		}
	}
}

void encode_arith_src_instruction(int arith_type, int current_size, phrase_retrievel src)
{
	if (src.type != NULL)
	{
		switch(src.type)
		{
			case phrase_fetch: fprintf(temp_text, "[%s]\n", src.phrase); break;
			case phrase_mark:       fprintf(temp_text, " '0'\n"); break;
			case phrase_ident:     fprintf(temp_text, " %s\n", src.phrase); break;
			case phrase_num:       
	
			switch(current_size)
			{
				case 8:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						case 2:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				case 16:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						case 2:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				case 32:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						case 2:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				case 64:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						case 2:  fprintf(temp_text, " %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				default: break;
			}
			break;
			case phrase_register:  

			switch(current_size)
			{
				case 8:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						case 2:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				case 16:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						case 2:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						case 3:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						case 4:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				case 32:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						case 2:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				case 64:
					switch (arith_type)
					{
						case 1:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						case 2:  fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				default: break;
			}
			break;
			default: break;
		}
	}
}

void encode_arith_src_two_instruction(int arith_type, int current_size, phrase_retrievel src)
{
	if (src.type != NULL)
	{
		switch(src.type)
		{
			case phrase_ident:     fprintf(temp_text, "     %s\n", src.phrase); break;
			case phrase_num:       
	
			switch(current_size)
			{
				case 8:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %d\n", src.phrase_num_value); break;
						case 4:  fprintf(temp_text, "    div %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				case 16:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %d\n", src.phrase_num_value); break;
						case 4:  fprintf(temp_text, "    div %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				case 32:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %d\n", src.phrase_num_value); break;
						case 4:  fprintf(temp_text, "    div %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				case 64:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %d\n", src.phrase_num_value); break;
						case 4:  fprintf(temp_text, "    div %d\n", src.phrase_num_value); break;
						default: break;
					}
				break;
				default: break;
			}
			break;
			case phrase_register:  

			switch(current_size)
			{
				case 8:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %s\n", src.phrase_reg_value); break;
						case 4:  fprintf(temp_text, "    div %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				case 16:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %s\n", src.phrase_reg_value); break;
						case 4:  fprintf(temp_text, "    div %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				case 32:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %s\n", src.phrase_reg_value); break;
						case 4:  fprintf(temp_text, "    div %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				case 64:
					switch (arith_type)
					{
						case 3:  fprintf(temp_text, "    mul %s\n", src.phrase_reg_value); break;
						case 4:  fprintf(temp_text, "    div %s\n", src.phrase_reg_value); break;
						default: break;
					}
				break;
				default: break;
			}
			break;
			default: break;
		}
	}
}


void encode_compare_instruction(int byte_size, phrase_retrievel dest, phrase_retrievel src, phrase_retrievel third_index)
{
	fprintf(temp_text, "    cmp ");

	if (dest.type != NULL)
	{
		encode_destination_phrase(byte_size, dest);
	}
	if (src.type != NULL)
	{
		encode_source_phrase(byte_size, src, third_index);
	}
}

void encode_move_dest_instruction(int byte_size, phrase_retrievel dest)
{
	fprintf(temp_text, "    mov ");

	if (dest.type != NULL)
	{
		encode_destination_phrase(byte_size, dest);
	}
}

void encode_move_src_instruction(int byte_size, phrase_retrievel src, phrase_retrievel third_index)
{
	if (src.type != NULL)
	{
		encode_source_phrase(byte_size, src, third_index);
	}
}

void encode_destination_phrase(int byte_size, phrase_retrievel dest)
{
	switch (dest.type)
	{
		case phrase_ident:     fprintf(temp_text, "%s, ", dest.phrase); break;
		case phrase_num:       fprintf(temp_text, "%d, ", dest.phrase_num_value); break;
		case phrase_pointer:   fprintf(temp_text, "[%s], ", dest.phrase); break;
        case phrase_fetch:
		{

            // Output with size prefix
            switch (byte_size) {
                case 8:  fprintf(temp_text, " [%s], ", dest.phrase); break;
                case 16: fprintf(temp_text, " [%s], ", dest.phrase); break;
                case 32: fprintf(temp_text, " [%s], ", dest.phrase); break;
                case 64: fprintf(temp_text, " [%s], ", dest.phrase); break;
                default: break;
            }
        } break;
		case phrase_register:  fprintf(temp_text, "%s, ", dest.phrase_reg_value); break;
		case phrase_address:
		{
			switch (byte_size)
			{
				case 8:  fprintf(temp_text, " byte [%s], ", dest.phrase_reg_value); break;
				case 16: fprintf(temp_text, " word [%s], ", dest.phrase_reg_value); break;
				case 32: fprintf(temp_text, " dword [%s], ", dest.phrase_reg_value); break;
				case 64: fprintf(temp_text, " qword [%s], ", dest.phrase_reg_value); break;
				default: break;
			}
		} break;
		case phrase_hex:
		{
            switch (byte_size)
            {
                case 8:  fprintf(temp_text, "0x%02X, ", dest.phrase_hex_value); break;
                case 16: fprintf(temp_text, "0x%04X, ", dest.phrase_hex_value); break;
                case 32: fprintf(temp_text, "0x%08X, ", dest.phrase_hex_value); break;
                case 64: fprintf(temp_text, "0x%016llX, ", (unsigned long long)dest.phrase_hex_value); break;
                default: break;
            }
		} break;
		default: break;
	}
}


void encode_source_phrase(int byte_size, phrase_retrievel src, phrase_retrievel third_index)
{
	switch (src.type)
	{
		case phrase_ident:    fprintf(temp_text, "%s\n", src.phrase); break;
		case phrase_num:      fprintf(temp_text, "%d\n", src.phrase_num_value);   break;
		case phrase_pointer: 
		
		 if(third_index.type == NULL)
		 {
             fprintf(temp_text, "[%s]\n", src.phrase);
		 } 
		 else
		 {
			 fprintf(temp_text, "[%s + %d]\n", src.phrase, third_index.phrase_num_value);
		 }      
		 
		 break;
		 case phrase_fetch:
		{
            // Output with size prefix
            switch (byte_size) {
                case 8:  fprintf(temp_text, "[%s]\n", src.phrase); break;
                case 16: fprintf(temp_text, "[%s]\n", src.phrase); break;
                case 32: fprintf(temp_text, "[%s]\n", src.phrase); break;
                case 64: fprintf(temp_text, "[%s]\n", src.phrase); break;
                default: break;
            }
        } break;
		case phrase_register: fprintf(temp_text, "%s\n", src.phrase_reg_value);   break;
		case phrase_address:
		{
			switch (byte_size)
			{
				case 8:  fprintf(temp_text, "byte [%s]\n", src.phrase_reg_value);  break;
				case 16: fprintf(temp_text, "word [%s]\n", src.phrase_reg_value);  break;
				case 32: fprintf(temp_text, "dword [%s]\n", src.phrase); break;
				case 64: fprintf(temp_text, "qword[%s]\n", src.phrase_reg_value);  break;
				default: break;
			}
		} break;
		case phrase_hex:
		{
			switch (byte_size)
			{
                case 8:  fprintf(temp_text, "0x%02X\n", src.phrase_hex_value); break;
                case 16: fprintf(temp_text, "0x%04X\n", src.phrase_hex_value); break;
                case 32: fprintf(temp_text, "0x%08X\n", src.phrase_hex_value); break;
                case 64: fprintf(temp_text, "0x%016llX\n", (unsigned long long)src.phrase_hex_value); break;
                default:  break;
			}
		}break;
		default:break;
	}
}

// Function to encode a Seedling push instruction to NASM
void encode_push_instruction(int byte_size, phrase_retrievel src)
{
	if (src.type != NULL)
	{
		switch (src.type)
		{
			case phrase_pointer:
			{
				switch (byte_size)
				{
					case 8:  fprintf(temp_text, "    push byte [%s]\n", src.phrase); break;
					case 16: fprintf(temp_text, "    push word [%s]\n", src.phrase); break;
					case 32: fprintf(temp_text, "    push dword [%s]\n", src.phrase); break;
					case 64: fprintf(temp_text, "    push qword [%s]\n", src.phrase); break;
					default: break;
				}
			}
			break;
			case phrase_address:
			{
				switch (byte_size)
				{
					case 8:  fprintf(temp_text, "    push byte [%s]\n", src.phrase);  break;
					case 16: fprintf(temp_text, "    push word [%s]\n", src.phrase);  break;
					case 32: fprintf(temp_text, "    push dword [%s]\n", src.phrase); break;
					case 64: fprintf(temp_text, "    push qword [%s]\n", src.phrase); break;
					default: break;
				}
			}
			break;
			case phrase_fetch:
			{
				switch (byte_size)
				{
					case 8:  fprintf(temp_text, "    push byte [%s]\n", src.phrase); break;
					case 16: fprintf(temp_text, "    push word [%s]\n", src.phrase); break;
					case 32: fprintf(temp_text, "    push dword [%s]\n", src.phrase); break;
					case 64: fprintf(temp_text, "    push qword [%s]\n", src.phrase); break;
					default: break;
				}
			}
			break;
			case phrase_register:
			{
				switch (byte_size)
				{
				case 8:  fprintf(temp_text, "    push %s\n", src.phrase_reg_value);  break;
				case 16: fprintf(temp_text, "    push %s\n", src.phrase_reg_value);  break;
				case 32: fprintf(temp_text, "    push %s\n", src.phrase_reg_value); break;
				case 64: fprintf(temp_text, "    push %s\n", src.phrase_reg_value); break;
				default: break;
				}
			}
			break;
			default: break;
		}
	}
}

// Function to encode a Seedling pop instruction to NASM
void encode_pop_instruction(int byte_size, phrase_retrievel src)
{
	if (src.type != NULL)
	{
		switch (src.type)
		{
			case phrase_pointer:  fprintf(temp_text, "    pop [%s]\n", src.phrase);  break;
			case phrase_address:  fprintf(temp_text, "    pop [%s]\n", src.phrase);  break;
			case phrase_fetch:    fprintf(temp_text, "    pop [%s]\n", src.phrase);  break;
			case phrase_register:
			{
				switch (byte_size)
				{
				case 8:  fprintf(temp_text, "    pop %s\n", src.phrase_reg_value);  break;
				case 16: fprintf(temp_text, "    pop %s\n", src.phrase_reg_value);  break;
				case 32: fprintf(temp_text, "    pop %s\n", src.phrase_reg_value); break;
				case 64: fprintf(temp_text, "    pop %s\n", src.phrase_reg_value); break;
				default: break;
				}
			}
			break;
			default:break;
		}
	}
}



void encode_jump_instruction(int jump_value, const char *operation)
{
	switch (jump_value)
	{
		case 1:  fprintf(temp_text, "    jmp %s\n", operation);  break;  // Unconditional
		case 2:  fprintf(temp_text, "    jz  %s\n", operation);  break;  // Zero (equal)
		case 3:  fprintf(temp_text, "    jnz %s\n", operation);  break;  // Not zero (not equal)
		case 4:  fprintf(temp_text, "    jl  %s\n", operation);  break;  // Less than
		case 5:  fprintf(temp_text, "    jg  %s\n", operation);  break;  // Greater than
		case 6:  fprintf(temp_text, "    je  %s\n", operation);  break;  // Equal
		case 7:  fprintf(temp_text, "    jne %s\n", operation);  break;  // Not equal
		default: fprintf(temp_text, "    ; Invalid jump type: %d\n", jump_value);break;
	}
}


void encode_register_instruction(phrase_retrievel src)
{
	fprintf(temp_text, "%s", src.phrase);
}

// Function to encode a Seedling set flag instruction to NASM
void encode_set_flag_instruction(phrase_retrievel dest, phrase_retrievel src)
{
	fprintf(temp_text, "    xor %s, %s\n", dest.phrase, src.phrase);
}

// Function to encode a Seedling test instruction to NASM
void encode_test_instruction(phrase_retrievel dest, phrase_retrievel src)
{
	fprintf(temp_text, "    test ");

	// Check if the phrase in dest is not NULL
	if (dest.phrase != NULL)
	{
		fprintf(temp_text, "%s, ", dest.phrase);
	}

	// Check if the phrase in src is not NULL
	if (src.phrase != NULL)
	{
		fprintf(temp_text, "%s\n", src.phrase);
	}
}

void encode_increment_instruction(phrase_retrievel src)
{
	fprintf(temp_text, "    inc %s\n", src.phrase);
}

void encode_decrement_instruction(phrase_retrievel src)
{
	fprintf(temp_text, "    dec %s\n", src.phrase);
}


// Function to encode a Seedling number to NASM
void encode_number(int num)
{
	fprintf(temp_text, "    mov eax, 0x%X\n", num);
}


// Function to encode a Seedling literal section to NASM
void encode_literal_with_num_section(char *hold_name, char *src, phrase_retrievel num_value)
{
	fprintf(temp_data, "    %s db \"\\%s\", %d\n", hold_name, src, num_value.phrase_num_value);
}

/*
void encode_literal_with_hex_section(char *hold_name, char *src, phrase_retrievel hex_value)
{
	fprintf(temp_data, "    %s db \"%s\", 0x%02X\n", hold_name, src, hex_value.phrase_hex_values);  // Use correct NASM format for hex values
}

*/

void encode_literal_with_hex_section(char *hold_name, char *src, phrase_retrievel hex_value)
{
    fprintf(temp_data, "    %s db \"%s\"", hold_name, src); // Print the string
    for (int i = 0; i < hex_value.phrase_hex_count; i++) {
        // Use %X without padding, but cap at 8-bit values for db
        fprintf(temp_data, ", 0x%02X", (unsigned char)hex_value.phrase_hex_values[i]);
    }
    fprintf(temp_data, "\n"); // End the line
}

void encode_file_section(const char *label_name, const char *label_strand, int length)
{
	fprintf(temp_data, "    %s db \"%s\", %d\n", label_name, label_strand, length);
}

// Function to encode a Seedling lend instruction to NASM
void encode_system_instruction()
{
	fprintf(temp_text, "    int 0x80\n");
}




void encode_transfer_dest_instruction(int byte_size, phrase_retrievel dest)
{
	fprintf(temp_text, "    movzx ");   // need to worry about signed also eventually movsx

	if (dest.type != NULL)
	{
		encode_transfer_destination_phrase(byte_size, dest);
	}
}

void encode_transfer_src_instruction(int byte_size, phrase_retrievel src, phrase_retrievel third_index)
{
	if (src.type != NULL)
	{
		encode_transfer_source_phrase(byte_size, src, third_index);
	}
}


void encode_transfer_destination_phrase(int byte_size, phrase_retrievel dest)
{
	switch (dest.type)
	{
		case phrase_register:  fprintf(temp_text, "%s, ", dest.phrase_reg_value); break;
		case phrase_fetch:
		{
			switch (byte_size)
			{
				case 8:  fprintf(temp_text, "[%s], ", dest.phrase);  break;
				case 16: fprintf(temp_text, "[%s], ", dest.phrase);  break;
				case 32: fprintf(temp_text, "[%s], ", dest.phrase); break;
				case 64: fprintf(temp_text, "[%s], ", dest.phrase); break;
				default: break;
			}
		}
		default: break;
	}
}


void encode_transfer_source_phrase(int byte_size, phrase_retrievel src, phrase_retrievel third_index)
{
	switch (src.type)
	{
		case phrase_register:   fprintf(temp_text, " %s\n", src.phrase_reg_value); break;
		case phrase_address:
		{
			switch (byte_size)
			{
				case 8:  fprintf(temp_text, "push byte [%s]\n", src.phrase);  break;
				case 16: fprintf(temp_text, "push word [%s]\n", src.phrase);  break;
				case 32: fprintf(temp_text, "push dword [%s]\n", src.phrase); break;
				case 64: fprintf(temp_text, "push qword [%s]\n", src.phrase); break;
				default: break;
			}
		}
		default: break;
	}
}

void encode_log_phrase(int byte_size, char *log_name, char *offset_name, phrase_retrievel src)
{
    if (first_pass == 0) {      // Only print label on first call
        fprintf(temp_data, "    %s:\n", log_name);
        first_pass = 1;         // Mark as done
    }

	switch (byte_size)
	{
		case 1:  fprintf(temp_data, "        %s db %d\n", offset_name, src.phrase_num_value); break;
		case 2: fprintf(temp_data, "        %s dd %d\n", offset_name, src.phrase_num_value); break;
		case 4: fprintf(temp_data, "        %s dw %d\n", offset_name, src.phrase_num_value); break;
		case 8: fprintf(temp_data, "        %s dq %d\n", offset_name, src.phrase_num_value); break;
		default: break;
	}
}

void encode_list_phrase(int byte_size, char *list_name, char *index_name, phrase_retrievel src)
{
    if (first_pass == 0) {      // Only print label on first call
        fprintf(temp_data, "  %s:\n", list_name);
        first_pass = 1;         // Mark as done
    }

	switch (byte_size)
	{
		case 1:  fprintf(temp_data, "    %s equ %d\n", index_name, src.phrase_num_value); break;
		case 2: fprintf(temp_data, "    %s equ %d\n", index_name, src.phrase_num_value); break;
		case 4: fprintf(temp_data, "    %s equ %d\n", index_name, src.phrase_num_value); break;
		case 8: fprintf(temp_data, "    %s equ %d\n", index_name, src.phrase_num_value); break;
		default: break;
	}
}