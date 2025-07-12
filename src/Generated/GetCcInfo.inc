ZyanBool ZydisGetCcInfo(ZydisMnemonic mnemonic, ZydisSourceConditionCode *scc)
{
    switch (mnemonic)
    {
    case ZYDIS_MNEMONIC_CCMPB:
    case ZYDIS_MNEMONIC_CTESTB:
        *scc = ZYDIS_SCC_B;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPBE:
    case ZYDIS_MNEMONIC_CTESTBE:
        *scc = ZYDIS_SCC_BE;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPF:
    case ZYDIS_MNEMONIC_CTESTF:
        *scc = ZYDIS_SCC_FALSE;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPL:
    case ZYDIS_MNEMONIC_CTESTL:
        *scc = ZYDIS_SCC_L;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPLE:
    case ZYDIS_MNEMONIC_CTESTLE:
        *scc = ZYDIS_SCC_LE;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNB:
    case ZYDIS_MNEMONIC_CTESTNB:
        *scc = ZYDIS_SCC_NB;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNBE:
    case ZYDIS_MNEMONIC_CTESTNBE:
        *scc = ZYDIS_SCC_NBE;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNL:
    case ZYDIS_MNEMONIC_CTESTNL:
        *scc = ZYDIS_SCC_NL;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNLE:
    case ZYDIS_MNEMONIC_CTESTNLE:
        *scc = ZYDIS_SCC_NLE;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNO:
    case ZYDIS_MNEMONIC_CTESTNO:
        *scc = ZYDIS_SCC_NO;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNS:
    case ZYDIS_MNEMONIC_CTESTNS:
        *scc = ZYDIS_SCC_NS;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPNZ:
    case ZYDIS_MNEMONIC_CTESTNZ:
        *scc = ZYDIS_SCC_NZ;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPO:
    case ZYDIS_MNEMONIC_CTESTO:
        *scc = ZYDIS_SCC_O;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPS:
    case ZYDIS_MNEMONIC_CTESTS:
        *scc = ZYDIS_SCC_S;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPT:
    case ZYDIS_MNEMONIC_CTESTT:
        *scc = ZYDIS_SCC_TRUE;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CCMPZ:
    case ZYDIS_MNEMONIC_CTESTZ:
        *scc = ZYDIS_SCC_Z;
        return ZYAN_TRUE;
    case ZYDIS_MNEMONIC_CFCMOVB:
    case ZYDIS_MNEMONIC_CFCMOVBE:
    case ZYDIS_MNEMONIC_CFCMOVL:
    case ZYDIS_MNEMONIC_CFCMOVLE:
    case ZYDIS_MNEMONIC_CFCMOVNB:
    case ZYDIS_MNEMONIC_CFCMOVNBE:
    case ZYDIS_MNEMONIC_CFCMOVNL:
    case ZYDIS_MNEMONIC_CFCMOVNLE:
    case ZYDIS_MNEMONIC_CFCMOVNO:
    case ZYDIS_MNEMONIC_CFCMOVNP:
    case ZYDIS_MNEMONIC_CFCMOVNS:
    case ZYDIS_MNEMONIC_CFCMOVNZ:
    case ZYDIS_MNEMONIC_CFCMOVO:
    case ZYDIS_MNEMONIC_CFCMOVP:
    case ZYDIS_MNEMONIC_CFCMOVS:
    case ZYDIS_MNEMONIC_CFCMOVZ:
    case ZYDIS_MNEMONIC_CMOVB:
    case ZYDIS_MNEMONIC_CMOVBE:
    case ZYDIS_MNEMONIC_CMOVL:
    case ZYDIS_MNEMONIC_CMOVLE:
    case ZYDIS_MNEMONIC_CMOVNB:
    case ZYDIS_MNEMONIC_CMOVNBE:
    case ZYDIS_MNEMONIC_CMOVNL:
    case ZYDIS_MNEMONIC_CMOVNLE:
    case ZYDIS_MNEMONIC_CMOVNO:
    case ZYDIS_MNEMONIC_CMOVNP:
    case ZYDIS_MNEMONIC_CMOVNS:
    case ZYDIS_MNEMONIC_CMOVNZ:
    case ZYDIS_MNEMONIC_CMOVO:
    case ZYDIS_MNEMONIC_CMOVP:
    case ZYDIS_MNEMONIC_CMOVS:
    case ZYDIS_MNEMONIC_CMOVZ:
        *scc = ZYDIS_SCC_NONE;
        return ZYAN_TRUE;
    default:
        *scc = ZYDIS_SCC_NONE;
        return ZYAN_FALSE;
    }
}
