typedef struct ZydisInstructionDefinition_
{
    uint32_t mnemonic : 11;
    uint32_t operandsId : 9;
    uint32_t evexContext : 2;
    uint32_t evexMaskPolicy : 2;
    uint32_t evexZeroMaskAccepted : 1;
    uint32_t acceptsLock : 1;
    uint32_t acceptsREP : 1;
    uint32_t acceptsREPEREPNE : 1;
    uint32_t acceptsBOUND : 1;
    uint32_t acceptsXACQUIRE : 1;
    uint32_t acceptsXRELEASE : 1;
    uint32_t acceptsHLEWithoutLock : 1;
    uint32_t acceptsBranchHints : 1;
#ifdef ZYDIS_ENABLE_FEATURE_IMPLICITLY_USED_REGISTERS
    uint8_t implicitRegistersId : 8;
#endif
#ifdef ZYDIS_ENABLE_FEATURE_AFFECTED_FLAGS
    uint8_t affectedFlagsId : 8;
#endif
#ifdef ZYDIS_ENABLE_FEATURE_CPUID
    uint8_t cpuidId : 8;
#endif
} ZydisInstructionDefinition;
