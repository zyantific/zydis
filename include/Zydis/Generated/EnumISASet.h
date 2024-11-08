/**
 * Defines the `ZydisISASet` enum.
 */
typedef enum ZydisISASet_
{
    ZYDIS_ISA_SET_INVALID,
    ZYDIS_ISA_SET_ADOX_ADCX,
    ZYDIS_ISA_SET_AES,
    ZYDIS_ISA_SET_AMD,
    ZYDIS_ISA_SET_AMD3DNOW,
    ZYDIS_ISA_SET_AMD_INVLPGB,
    ZYDIS_ISA_SET_AMX_BF16,
    ZYDIS_ISA_SET_AMX_FP16,
    ZYDIS_ISA_SET_AMX_INT8,
    ZYDIS_ISA_SET_AMX_TILE,
    ZYDIS_ISA_SET_APX_F,
    ZYDIS_ISA_SET_APX_F_ADX,
    ZYDIS_ISA_SET_APX_F_AMX,
    ZYDIS_ISA_SET_APX_F_BMI1,
    ZYDIS_ISA_SET_APX_F_BMI2,
    ZYDIS_ISA_SET_APX_F_CET,
    ZYDIS_ISA_SET_APX_F_CMPCCXADD,
    ZYDIS_ISA_SET_APX_F_ENQCMD,
    ZYDIS_ISA_SET_APX_F_INVPCID,
    ZYDIS_ISA_SET_APX_F_KOPB,
    ZYDIS_ISA_SET_APX_F_KOPD,
    ZYDIS_ISA_SET_APX_F_KOPQ,
    ZYDIS_ISA_SET_APX_F_KOPW,
    ZYDIS_ISA_SET_APX_F_LZCNT,
    ZYDIS_ISA_SET_APX_F_MOVBE,
    ZYDIS_ISA_SET_APX_F_MOVDIR64B,
    ZYDIS_ISA_SET_APX_F_MOVDIRI,
    ZYDIS_ISA_SET_APX_F_POPCNT,
    ZYDIS_ISA_SET_APX_F_RAO_INT,
    ZYDIS_ISA_SET_APX_F_USER_MSR,
    ZYDIS_ISA_SET_APX_F_VMX,
    ZYDIS_ISA_SET_AVX,
    ZYDIS_ISA_SET_AVX2,
    ZYDIS_ISA_SET_AVX2GATHER,
    ZYDIS_ISA_SET_AVX512BW_128,
    ZYDIS_ISA_SET_AVX512BW_128N,
    ZYDIS_ISA_SET_AVX512BW_256,
    ZYDIS_ISA_SET_AVX512BW_512,
    ZYDIS_ISA_SET_AVX512BW_KOP,
    ZYDIS_ISA_SET_AVX512CD_128,
    ZYDIS_ISA_SET_AVX512CD_256,
    ZYDIS_ISA_SET_AVX512CD_512,
    ZYDIS_ISA_SET_AVX512DQ_128,
    ZYDIS_ISA_SET_AVX512DQ_128N,
    ZYDIS_ISA_SET_AVX512DQ_256,
    ZYDIS_ISA_SET_AVX512DQ_512,
    ZYDIS_ISA_SET_AVX512DQ_KOP,
    ZYDIS_ISA_SET_AVX512DQ_SCALAR,
    ZYDIS_ISA_SET_AVX512ER_512,
    ZYDIS_ISA_SET_AVX512ER_SCALAR,
    ZYDIS_ISA_SET_AVX512F_128,
    ZYDIS_ISA_SET_AVX512F_128N,
    ZYDIS_ISA_SET_AVX512F_256,
    ZYDIS_ISA_SET_AVX512F_512,
    ZYDIS_ISA_SET_AVX512F_KOP,
    ZYDIS_ISA_SET_AVX512F_SCALAR,
    ZYDIS_ISA_SET_AVX512PF_512,
    ZYDIS_ISA_SET_AVX512_4FMAPS_512,
    ZYDIS_ISA_SET_AVX512_4FMAPS_SCALAR,
    ZYDIS_ISA_SET_AVX512_4VNNIW_512,
    ZYDIS_ISA_SET_AVX512_BF16_128,
    ZYDIS_ISA_SET_AVX512_BF16_256,
    ZYDIS_ISA_SET_AVX512_BF16_512,
    ZYDIS_ISA_SET_AVX512_BITALG_128,
    ZYDIS_ISA_SET_AVX512_BITALG_256,
    ZYDIS_ISA_SET_AVX512_BITALG_512,
    ZYDIS_ISA_SET_AVX512_FP16_128,
    ZYDIS_ISA_SET_AVX512_FP16_128N,
    ZYDIS_ISA_SET_AVX512_FP16_256,
    ZYDIS_ISA_SET_AVX512_FP16_512,
    ZYDIS_ISA_SET_AVX512_FP16_SCALAR,
    ZYDIS_ISA_SET_AVX512_GFNI_128,
    ZYDIS_ISA_SET_AVX512_GFNI_256,
    ZYDIS_ISA_SET_AVX512_GFNI_512,
    ZYDIS_ISA_SET_AVX512_IFMA_128,
    ZYDIS_ISA_SET_AVX512_IFMA_256,
    ZYDIS_ISA_SET_AVX512_IFMA_512,
    ZYDIS_ISA_SET_AVX512_VAES_128,
    ZYDIS_ISA_SET_AVX512_VAES_256,
    ZYDIS_ISA_SET_AVX512_VAES_512,
    ZYDIS_ISA_SET_AVX512_VBMI2_128,
    ZYDIS_ISA_SET_AVX512_VBMI2_256,
    ZYDIS_ISA_SET_AVX512_VBMI2_512,
    ZYDIS_ISA_SET_AVX512_VBMI_128,
    ZYDIS_ISA_SET_AVX512_VBMI_256,
    ZYDIS_ISA_SET_AVX512_VBMI_512,
    ZYDIS_ISA_SET_AVX512_VNNI_128,
    ZYDIS_ISA_SET_AVX512_VNNI_256,
    ZYDIS_ISA_SET_AVX512_VNNI_512,
    ZYDIS_ISA_SET_AVX512_VP2INTERSECT_128,
    ZYDIS_ISA_SET_AVX512_VP2INTERSECT_256,
    ZYDIS_ISA_SET_AVX512_VP2INTERSECT_512,
    ZYDIS_ISA_SET_AVX512_VPCLMULQDQ_128,
    ZYDIS_ISA_SET_AVX512_VPCLMULQDQ_256,
    ZYDIS_ISA_SET_AVX512_VPCLMULQDQ_512,
    ZYDIS_ISA_SET_AVX512_VPOPCNTDQ_128,
    ZYDIS_ISA_SET_AVX512_VPOPCNTDQ_256,
    ZYDIS_ISA_SET_AVX512_VPOPCNTDQ_512,
    ZYDIS_ISA_SET_AVXAES,
    ZYDIS_ISA_SET_AVX_GFNI,
    ZYDIS_ISA_SET_AVX_IFMA,
    ZYDIS_ISA_SET_AVX_NE_CONVERT,
    ZYDIS_ISA_SET_AVX_VNNI,
    ZYDIS_ISA_SET_AVX_VNNI_INT16,
    ZYDIS_ISA_SET_AVX_VNNI_INT8,
    ZYDIS_ISA_SET_BMI1,
    ZYDIS_ISA_SET_BMI2,
    ZYDIS_ISA_SET_CET,
    ZYDIS_ISA_SET_CLDEMOTE,
    ZYDIS_ISA_SET_CLFLUSHOPT,
    ZYDIS_ISA_SET_CLFSH,
    ZYDIS_ISA_SET_CLWB,
    ZYDIS_ISA_SET_CLZERO,
    ZYDIS_ISA_SET_CMOV,
    ZYDIS_ISA_SET_CMPXCHG16B,
    ZYDIS_ISA_SET_ENQCMD,
    ZYDIS_ISA_SET_F16C,
    ZYDIS_ISA_SET_FAT_NOP,
    ZYDIS_ISA_SET_FCMOV,
    ZYDIS_ISA_SET_FCOMI,
    ZYDIS_ISA_SET_FMA,
    ZYDIS_ISA_SET_FMA4,
    ZYDIS_ISA_SET_FRED,
    ZYDIS_ISA_SET_FXSAVE,
    ZYDIS_ISA_SET_FXSAVE64,
    ZYDIS_ISA_SET_GFNI,
    ZYDIS_ISA_SET_HRESET,
    ZYDIS_ISA_SET_I186,
    ZYDIS_ISA_SET_I286PROTECTED,
    ZYDIS_ISA_SET_I286REAL,
    ZYDIS_ISA_SET_I386,
    ZYDIS_ISA_SET_I486,
    ZYDIS_ISA_SET_I486REAL,
    ZYDIS_ISA_SET_I86,
    ZYDIS_ISA_SET_ICACHE_PREFETCH,
    ZYDIS_ISA_SET_INVPCID,
    ZYDIS_ISA_SET_KEYLOCKER,
    ZYDIS_ISA_SET_KEYLOCKER_WIDE,
    ZYDIS_ISA_SET_KNCE,
    ZYDIS_ISA_SET_KNCJKBR,
    ZYDIS_ISA_SET_KNCSTREAM,
    ZYDIS_ISA_SET_KNCV,
    ZYDIS_ISA_SET_KNC_MISC,
    ZYDIS_ISA_SET_KNC_PF_HINT,
    ZYDIS_ISA_SET_LAHF,
    ZYDIS_ISA_SET_LKGS,
    ZYDIS_ISA_SET_LONGMODE,
    ZYDIS_ISA_SET_LWP,
    ZYDIS_ISA_SET_LZCNT,
    ZYDIS_ISA_SET_MCOMMIT,
    ZYDIS_ISA_SET_MONITOR,
    ZYDIS_ISA_SET_MONITORX,
    ZYDIS_ISA_SET_MOVBE,
    ZYDIS_ISA_SET_MOVDIR,
    ZYDIS_ISA_SET_MPX,
    ZYDIS_ISA_SET_MSRLIST,
    ZYDIS_ISA_SET_PADLOCK_ACE,
    ZYDIS_ISA_SET_PADLOCK_PHE,
    ZYDIS_ISA_SET_PADLOCK_PMM,
    ZYDIS_ISA_SET_PADLOCK_RNG,
    ZYDIS_ISA_SET_PAUSE,
    ZYDIS_ISA_SET_PBNDKB,
    ZYDIS_ISA_SET_PCLMULQDQ,
    ZYDIS_ISA_SET_PCOMMIT,
    ZYDIS_ISA_SET_PCONFIG,
    ZYDIS_ISA_SET_PENTIUMMMX,
    ZYDIS_ISA_SET_PENTIUMREAL,
    ZYDIS_ISA_SET_PKU,
    ZYDIS_ISA_SET_POPCNT,
    ZYDIS_ISA_SET_PPRO,
    ZYDIS_ISA_SET_PREFETCHWT1,
    ZYDIS_ISA_SET_PREFETCH_NOP,
    ZYDIS_ISA_SET_PT,
    ZYDIS_ISA_SET_RAO_INT,
    ZYDIS_ISA_SET_RDPID,
    ZYDIS_ISA_SET_RDPMC,
    ZYDIS_ISA_SET_RDPRU,
    ZYDIS_ISA_SET_RDRAND,
    ZYDIS_ISA_SET_RDSEED,
    ZYDIS_ISA_SET_RDTSCP,
    ZYDIS_ISA_SET_RDWRFSGS,
    ZYDIS_ISA_SET_RTM,
    ZYDIS_ISA_SET_SERIALIZE,
    ZYDIS_ISA_SET_SGX,
    ZYDIS_ISA_SET_SGX_ENCLV,
    ZYDIS_ISA_SET_SHA,
    ZYDIS_ISA_SET_SHA512,
    ZYDIS_ISA_SET_SM3,
    ZYDIS_ISA_SET_SM4,
    ZYDIS_ISA_SET_SMAP,
    ZYDIS_ISA_SET_SMX,
    ZYDIS_ISA_SET_SNP,
    ZYDIS_ISA_SET_SSE,
    ZYDIS_ISA_SET_SSE2,
    ZYDIS_ISA_SET_SSE2MMX,
    ZYDIS_ISA_SET_SSE3,
    ZYDIS_ISA_SET_SSE3X87,
    ZYDIS_ISA_SET_SSE4,
    ZYDIS_ISA_SET_SSE42,
    ZYDIS_ISA_SET_SSE4A,
    ZYDIS_ISA_SET_SSEMXCSR,
    ZYDIS_ISA_SET_SSE_PREFETCH,
    ZYDIS_ISA_SET_SSSE3,
    ZYDIS_ISA_SET_SSSE3MMX,
    ZYDIS_ISA_SET_SVM,
    ZYDIS_ISA_SET_TBM,
    ZYDIS_ISA_SET_TDX,
    ZYDIS_ISA_SET_TSX_LDTRK,
    ZYDIS_ISA_SET_UINTR,
    ZYDIS_ISA_SET_VAES,
    ZYDIS_ISA_SET_VMFUNC,
    ZYDIS_ISA_SET_VPCLMULQDQ,
    ZYDIS_ISA_SET_VTX,
    ZYDIS_ISA_SET_WAITPKG,
    ZYDIS_ISA_SET_WRMSRNS,
    ZYDIS_ISA_SET_X87,
    ZYDIS_ISA_SET_XOP,
    ZYDIS_ISA_SET_XSAVE,
    ZYDIS_ISA_SET_XSAVEC,
    ZYDIS_ISA_SET_XSAVEOPT,
    ZYDIS_ISA_SET_XSAVES,

    /**
     * Maximum value of this enum.
     */
    ZYDIS_ISA_SET_MAX_VALUE = ZYDIS_ISA_SET_XSAVES,
    /**
     * The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_ISA_SET_REQUIRED_BITS = ZYAN_BITS_TO_REPRESENT(ZYDIS_ISA_SET_MAX_VALUE)
} ZydisISASet;
