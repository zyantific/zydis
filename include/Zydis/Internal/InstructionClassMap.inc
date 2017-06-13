static const ZydisInstructionParts instructionClassMap[] =
{
    /*00*/ { 0, { {  0,  0,  0 } }, { { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*01*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { {  8,  8,  8 }, ZYDIS_TRUE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*02*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_MODRM, { {  0,  0,  0 } }, { { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*03*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 16, 32, 32 }, ZYDIS_TRUE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*04*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_MODRM | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { {  8,  8,  8 }, ZYDIS_TRUE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*05*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_MODRM | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 16, 32, 32 }, ZYDIS_TRUE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*06*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_MODRM | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { {  8,  8,  8 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*07*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 16, 32, 32 }, ZYDIS_TRUE, ZYDIS_TRUE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*08*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 32, 32, 32 }, ZYDIS_TRUE, ZYDIS_TRUE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*09*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0 | ZYDIS_INSTRPART_FLAG_HAS_IMM1, { {  0,  0,  0 } }, { { { 16, 32, 32 }, ZYDIS_TRUE, ZYDIS_TRUE }, { { 16, 16, 16 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*0A*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0 | ZYDIS_INSTRPART_FLAG_HAS_IMM1, { {  0,  0,  0 } }, { { { 16, 16, 16 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  8,  8,  8 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*0B*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { {  8,  8,  8 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*0C*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { {  8,  8,  8 }, ZYDIS_TRUE, ZYDIS_TRUE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*0D*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_DISP, { { 16, 32, 64 } }, { { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*0E*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 16, 32, 64 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*0F*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 16, 16, 16 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } },
    /*10*/ { 0 | ZYDIS_INSTRPART_FLAG_HAS_MODRM | ZYDIS_INSTRPART_FLAG_HAS_IMM0, { {  0,  0,  0 } }, { { { 32, 32, 32 }, ZYDIS_FALSE, ZYDIS_FALSE }, { {  0,  0,  0 }, ZYDIS_FALSE, ZYDIS_FALSE } } }
};
