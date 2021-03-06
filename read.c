#define MAP_OPCODE(x, func) case x: func; prefix = NULL; break;
#define MULTIMAP_BEGIN(x) case x: fread(&modrm, 1, 1, binary); reg[R_RIP]++;
#define MULTIMAP_END(x) break;
#define MAP_EXTENSION(ext, func) if ((modrm | (ext << 3)) == modrm) func
#define DEF_PREFIX(x) case x: prefix = op; reg[R_RIP]++; break;

uint8_t prefix = NULL;
int step(bool forgiving, bool verbose) {
    uint8_t op;
    uint8_t op2;
    uint8_t modrm;
    fread(&op, 1, 1, binary);
    reg[R_RIP]++;
    if (verbose) printf("Read opcode 0x%02x\n", op);
    switch (op) {
        MAP_OPCODE(0x00, std_op(prefix, add, 0));
        MAP_OPCODE(0x01, std_op(prefix, add, 1));
        MAP_OPCODE(0x02, std_op(prefix, add, 2));
        MAP_OPCODE(0x03, std_op(prefix, add, 3));
        MAP_OPCODE(0x04, std_op(prefix, add, 4));
        MAP_OPCODE(0x05, std_op(prefix, add, 5));
        MAP_OPCODE(0x08, std_op(prefix, or, 0));
        MAP_OPCODE(0x09, std_op(prefix, or, 1));
        MAP_OPCODE(0x0A, std_op(prefix, or, 2));
        MAP_OPCODE(0x0B, std_op(prefix, or, 3));
        MAP_OPCODE(0x0C, std_op(prefix, or, 4));
        MAP_OPCODE(0x0D, std_op(prefix, or, 5));
        MAP_OPCODE(0x20, std_op(prefix, and, 0));
        MAP_OPCODE(0x21, std_op(prefix, and, 1));
        MAP_OPCODE(0x22, std_op(prefix, and, 2));
        MAP_OPCODE(0x23, std_op(prefix, and, 3));
        MAP_OPCODE(0x24, std_op(prefix, and, 4));
        MAP_OPCODE(0x25, std_op(prefix, and, 5));
        MAP_OPCODE(0x28, std_op(prefix, sub, 0));
        MAP_OPCODE(0x29, std_op(prefix, sub, 1));
        MAP_OPCODE(0x2A, std_op(prefix, sub, 2));
        MAP_OPCODE(0x2B, std_op(prefix, sub, 3));
        MAP_OPCODE(0x2C, std_op(prefix, sub, 4));
        MAP_OPCODE(0x2D, std_op(prefix, sub, 5));
        MAP_OPCODE(0x30, std_op(prefix, xor, 0));
        MAP_OPCODE(0x31, std_op(prefix, xor, 1));
        MAP_OPCODE(0x32, std_op(prefix, xor, 2));
        MAP_OPCODE(0x33, std_op(prefix, xor, 3));
        MAP_OPCODE(0x34, std_op(prefix, xor, 4));
        MAP_OPCODE(0x35, std_op(prefix, xor, 5));
        MAP_OPCODE(0x38, std_op(prefix, cmp, 0));
        MAP_OPCODE(0x39, std_op(prefix, cmp, 1));
        MAP_OPCODE(0x3A, std_op(prefix, cmp, 2));
        MAP_OPCODE(0x3B, std_op(prefix, cmp, 3));
        MAP_OPCODE(0x3C, std_op(prefix, cmp, 4));
        MAP_OPCODE(0x3D, std_op(prefix, cmp, 5));
        DEF_PREFIX(0x40);
        DEF_PREFIX(0x41);
        DEF_PREFIX(0x42);
        DEF_PREFIX(0x43);
        DEF_PREFIX(0x44);
        DEF_PREFIX(0x45);
        DEF_PREFIX(0x46);
        DEF_PREFIX(0x47);
        DEF_PREFIX(0x48);
        DEF_PREFIX(0x49);
        DEF_PREFIX(0x4A);
        DEF_PREFIX(0x4B);
        DEF_PREFIX(0x4C);
        DEF_PREFIX(0x4D);
        DEF_PREFIX(0x4E);
        DEF_PREFIX(0x4F);
        MAP_OPCODE(0x50, push(0));
        MAP_OPCODE(0x51, push(1));
        MAP_OPCODE(0x52, push(2));
        MAP_OPCODE(0x53, push(3));
        MAP_OPCODE(0x54, push(4));
        MAP_OPCODE(0x55, push(5));
        MAP_OPCODE(0x56, push(6));
        MAP_OPCODE(0x57, push(7));
        MAP_OPCODE(0x58, pop(0));
        MAP_OPCODE(0x59, pop(1));
        MAP_OPCODE(0x5A, pop(2));
        MAP_OPCODE(0x5B, pop(3));
        MAP_OPCODE(0x5C, pop(4));
        MAP_OPCODE(0x5D, pop(5));
        MAP_OPCODE(0x5E, pop(6));
        MAP_OPCODE(0x5F, pop(7));
        DEF_PREFIX(0x66);
        MAP_OPCODE(0x74, jump((reg[R_FLAGS] & FL_ZF) == FL_ZF, 8, false));
        MAP_OPCODE(0x75, jump((reg[R_FLAGS] | ~FL_ZF) == ~FL_ZF, 8, false));
        MAP_OPCODE(0x78, jump((reg[R_FLAGS] & FL_SF) == FL_SF, 8, false));
        MAP_OPCODE(0x79, jump((reg[R_FLAGS] | ~FL_SF) == ~FL_SF, 8, false));
        MAP_OPCODE(0x7A, jump((reg[R_FLAGS] & FL_PF) == FL_PF, 8, false));
        MAP_OPCODE(0x7B, jump((reg[R_FLAGS] | ~FL_PF) == ~FL_PF, 8, false));
        MULTIMAP_BEGIN(0x80)
            MAP_EXTENSION(0, std_op(prefix, add, 6));
            MAP_EXTENSION(1, std_op(prefix, or, 6)); 
            MAP_EXTENSION(4, std_op(prefix, and, 6)); 
            MAP_EXTENSION(5, std_op(prefix, sub, 6)); 
            MAP_EXTENSION(6, std_op(prefix, xor, 6)); 
            MAP_EXTENSION(7, std_op(prefix, cmp, 6)); 
        MULTIMAP_END(0x80)
        MULTIMAP_BEGIN(0x81)
            MAP_EXTENSION(0, std_op(prefix, add, 7));
            MAP_EXTENSION(1, std_op(prefix, or, 7)); 
            MAP_EXTENSION(4, std_op(prefix, and, 7)); 
            MAP_EXTENSION(5, std_op(prefix, sub, 7)); 
            MAP_EXTENSION(6, std_op(prefix, xor, 7)); 
            MAP_EXTENSION(7, std_op(prefix, cmp, 7)); 
        MULTIMAP_END(0x81)
        MULTIMAP_BEGIN(0x83)
            MAP_EXTENSION(0, std_op(prefix, add, 8));
            MAP_EXTENSION(1, std_op(prefix, or, 8)); 
            MAP_EXTENSION(4, std_op(prefix, and, 8)); 
            MAP_EXTENSION(5, std_op(prefix, sub, 8)); 
            MAP_EXTENSION(6, std_op(prefix, xor, 8)); 
            MAP_EXTENSION(7, std_op(prefix, cmp, 8)); 
        MULTIMAP_END(0x83)
        MAP_OPCODE(0x88, std_op(prefix, mov, 0));
        MAP_OPCODE(0x89, std_op(prefix, mov, 1));
        MAP_OPCODE(0x8A, std_op(prefix, mov, 2));
        MAP_OPCODE(0x8B, std_op(prefix, mov, 3));
        //MAP_OPCODE(0x99, cwd());
        MAP_OPCODE(0xC3, exit(0));
        MAP_OPCODE(0xC6, mem_imm(prefix, mov, 0));
        MAP_OPCODE(0xC7, mem_imm(prefix, mov, 1));
        MAP_OPCODE(0xE9, jump(true, 16, false));
        MAP_OPCODE(0xEB, jump(true, 8, false));
        MAP_OPCODE(0xEA, jump(true, 16, true));
        MAP_OPCODE(0xF0, /* Nothing, as no multithreading exists at the moment. */);
        MULTIMAP_BEGIN(0xF6)
            MAP_EXTENSION(0, std_op(prefix, test, 4));
        MULTIMAP_END(0xF6)
        MULTIMAP_BEGIN(0xF7)
            MAP_EXTENSION(0, std_op(prefix, test, 5));
        MULTIMAP_END(0xF7)
    /* MULTIMAP_BEGIN(0xF6) */
    /*     MAP_EXTENSION(4, ax_op(mul, 8, modrm)); */
    /*     MAP_EXTENSION(6, ax_op(udiv, 8, modrm)); */
    /* MULTIMAP_END(0xF6) */
    /* MULTIMAP_BEGIN(0xF7) */
    /*     MAP_EXTENSION(4, ax_op(mul, 16, modrm)); */
    /*     MAP_EXTENSION(6, ax_op(udiv, 16, modrm)); */
    /* MULTIMAP_END(0xF7) */
            MAP_OPCODE(0xF8, reg[R_FLAGS] &= ~FL_CF);
    case 0x0F:
        fread(&op2, 1, 1, binary);
        reg[R_RIP]++;
        switch(op2) {
            MAP_OPCODE(0x84, jump((reg[R_FLAGS] & FL_ZF) == FL_ZF, 16, false));
            MAP_OPCODE(0x85, jump((reg[R_FLAGS] | ~FL_ZF) == ~FL_ZF, 16, false));
            MAP_OPCODE(0x88, jump((reg[R_FLAGS] & FL_SF) == FL_SF, 16, false));
            MAP_OPCODE(0x89, jump((reg[R_FLAGS] | ~FL_SF) == ~FL_SF, 16, false));
            MAP_OPCODE(0x8A, jump((reg[R_FLAGS] & FL_PF) == FL_PF, 16, false));
            MAP_OPCODE(0x8B, jump((reg[R_FLAGS] | ~FL_PF) == ~FL_PF, 16, false));
            MAP_OPCODE(0x8D, jump((reg[R_FLAGS] & FL_SF) == (reg[R_FLAGS] & FL_OF), 16, false));
            MAP_OPCODE(0xAF, std_op(prefix, imul, 3));
        default:
            if (forgiving) printf("Bad two-byte opcode 0x%02x%02x at 0x%02llx! Skipping...\n", op, op2, reg[R_RIP]-1);
            else exit(1);
            break;
        }
        break;
    default:
        if (forgiving) printf("Bad opcode 0x%02x at 0x%02llx! Skipping...\n", op, reg[R_RIP]-1);
        else exit(1);
        break;
    }
    return 0;
}
