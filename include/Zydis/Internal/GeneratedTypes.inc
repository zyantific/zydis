typedef struct ZydisInstructionDefinition_
{
    uint32_t mnemonic : 11;
    uint32_t operandsId : 9;
    uint32_t evexBFunctionality : 2;
    uint32_t hasEvexAAA : 1;
    uint32_t hasEvexZ : 1;
    uint32_t acceptsLock : 1;
    uint32_t acceptsREP : 1;
    uint32_t acceptsREPEREPNE : 1;
    uint32_t acceptsXACQUIRE : 1;
    uint32_t acceptsXRELEASE : 1;
    uint32_t acceptsHLEWithoutLock : 1;
    uint32_t acceptsBranchHints : 1;
} ZydisInstructionDefinition;