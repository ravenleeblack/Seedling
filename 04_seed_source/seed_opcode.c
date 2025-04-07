#include "seed_defs.h"
#include "seed_data.h"
#include "seed_decl.h"



unsigned char current_opcode; // Holds the opcode as we build

void handle_mnemonic(const char *mnemonic) {
    if (strcmp(mnemonic, "mov") == 0) {
        current_opcode = 0xB8; // Base for MOV reg32, imm32
        printf("Mnemonic 'mov' -> base opcode: 0x%02X\n", current_opcode);
    } else {
        printf("Error: Unknown mnemonic %s\n", mnemonic);
        current_opcode = 0; // Reset or error state
    }
}


const char *regs[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
unsigned char reg_offsets[] = {0, 1, 2, 3, 4, 5, 6, 7};

void handle_destination(const char *dest) {
    if (current_opcode == 0) {
        printf("Error: No mnemonic set\n");
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (strcmp(dest, regs[i]) == 0) {
            current_opcode += reg_offsets[i]; // Adjust opcode
            printf("Destination '%s' -> opcode now: 0x%02X\n", dest, current_opcode);
            fwrite(&current_opcode, 1, 1, bin_out); // Write opcode to file
            return;
        }
    }
    printf("Error: Unknown register %s\n", dest);
}

void handle_source(int value) {
    if (current_opcode == 0) {
        printf("Error: No mnemonic set\n");
        return;
    }

    // Convert to little-endian bytes
    unsigned char bytes[4] = {
        value & 0xFF,           // Low byte
        (value >> 8) & 0xFF,
        (value >> 16) & 0xFF,
        (value >> 24) & 0xFF   // High byte
    };
    fwrite(bytes, 1, 4, bin_out); // Write 4 bytes
    printf("Source '%d' -> bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
           value, bytes[0], bytes[1], bytes[2], bytes[3]);
}
