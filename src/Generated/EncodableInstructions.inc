const ZydisEncodableInstruction encodableInstructions[] =
{
    /* ------------------------------------------------------------------------------------------ */
    /* AAA                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0000*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0000, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AAD                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0001*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0001, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AAM                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0002*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0002, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AAS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0003*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0003, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0004*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0004, { 0 } },
    /*0005*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0005, { 0 } },
    /*0006*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0006, { 0 } },
    /*0007*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0007, { 0 } },
    /*0008*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0008, { 0 } },
    /*0009*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0009, { 0 } },
    /*000A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x000A, { 0 } },
    /*000B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x000B, { 0 } },
    /*000C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x000C, { 0 } },
    /*000D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x000D, { 0 } },
    /*000E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x000E, { 0 } },
    /*000F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x000F, { 0 } },
    /*0010*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0010, { 0 } },
    /*0011*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0011, { 0 } },
    /*0012*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0012, { 0 } },
    /*0013*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0013, { 0 } },
    /*0014*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0014, { 0 } },
    /*0015*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0015, { 0 } },
    /*0016*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0016, { 0 } },
    /*0017*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0017, { 0 } },
    /*0018*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0018, { 0 } },
    /*0019*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0019, { 0 } },
    /*001A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x001A, { 0 } },
    /*001B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x001B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADCX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*001C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x001C, { 0 } },
    /*001D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x001D, { 0 } },
    /*001E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x001E, { 0 } },
    /*001F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x001F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADD                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0020*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0020, { 0 } },
    /*0021*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0021, { 0 } },
    /*0022*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0022, { 0 } },
    /*0023*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0023, { 0 } },
    /*0024*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0024, { 0 } },
    /*0025*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0025, { 0 } },
    /*0026*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0026, { 0 } },
    /*0027*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0027, { 0 } },
    /*0028*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0028, { 0 } },
    /*0029*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0029, { 0 } },
    /*002A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x002A, { 0 } },
    /*002B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x002B, { 0 } },
    /*002C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x002C, { 0 } },
    /*002D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x002D, { 0 } },
    /*002E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x002E, { 0 } },
    /*002F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x002F, { 0 } },
    /*0030*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0030, { 0 } },
    /*0031*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0031, { 0 } },
    /*0032*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0032, { 0 } },
    /*0033*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0033, { 0 } },
    /*0034*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0034, { 0 } },
    /*0035*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0035, { 0 } },
    /*0036*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0036, { 0 } },
    /*0037*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0037, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADDPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0038*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0038, { 0 } },
    /*0039*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0039, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADDPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*003A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x003A, { 0 } },
    /*003B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x003B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADDSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*003C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x003C, { 0 } },
    /*003D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x003D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADDSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*003E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x003E, { 0 } },
    /*003F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x003F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADDSUBPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0040*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0040, { 0 } },
    /*0041*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0041, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADDSUBPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0042*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0042, { 0 } },
    /*0043*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0043, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ADOX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0044*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0044, { 0 } },
    /*0045*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0045, { 0 } },
    /*0046*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0046, { 0 } },
    /*0047*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0047, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AESDEC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0048*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0048, { 0 } },
    /*0049*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0049, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AESDECLAST                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*004A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x004A, { 0 } },
    /*004B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x004B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AESENC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*004C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x004C, { 0 } },
    /*004D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x004D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AESENCLAST                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*004E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x004E, { 0 } },
    /*004F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x004F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AESIMC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0050*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0050, { 0 } },
    /*0051*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0051, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AESKEYGENASSIST                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0052*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0052, { 0 } },
    /*0053*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0053, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* AND                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0054*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0054, { 0 } },
    /*0055*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0055, { 0 } },
    /*0056*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0056, { 0 } },
    /*0057*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0057, { 0 } },
    /*0058*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0058, { 0 } },
    /*0059*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0059, { 0 } },
    /*005A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x005A, { 0 } },
    /*005B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x005B, { 0 } },
    /*005C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x005C, { 0 } },
    /*005D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x005D, { 0 } },
    /*005E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x005E, { 0 } },
    /*005F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x005F, { 0 } },
    /*0060*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0060, { 0 } },
    /*0061*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0061, { 0 } },
    /*0062*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0062, { 0 } },
    /*0063*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0063, { 0 } },
    /*0064*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0064, { 0 } },
    /*0065*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0065, { 0 } },
    /*0066*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0066, { 0 } },
    /*0067*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0067, { 0 } },
    /*0068*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0068, { 0 } },
    /*0069*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0069, { 0 } },
    /*006A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x006A, { 0 } },
    /*006B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x006B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ANDN                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*006C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0000, { 0 } },
    /*006D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0001, { 0 } },
    /*006E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0002, { 0 } },
    /*006F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0003, { 0 } },
    /*0070*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0004, { 0 } },
    /*0071*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0005, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ANDNPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0072*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x006C, { 0 } },
    /*0073*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x006D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ANDNPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0074*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x006E, { 0 } },
    /*0075*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x006F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ANDPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0076*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0070, { 0 } },
    /*0077*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0071, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ANDPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0078*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0072, { 0 } },
    /*0079*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0073, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ARPL                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*007A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0074, { 0 } },
    /*007B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0075, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BEXTR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*007C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0006, { 0 } },
    /*007D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0007, { 0 } },
    /*007E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0008, { 0 } },
    /*007F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0009, { 0 } },
    /*0080*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x000A, { 0 } },
    /*0081*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x000B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BEXTR_XOP                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0082*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0000, { 0 } },
    /*0083*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0001, { 0 } },
    /*0084*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0002, { 0 } },
    /*0085*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0003, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLCFILL                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0086*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0004, { 0 } },
    /*0087*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0005, { 0 } },
    /*0088*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0006, { 0 } },
    /*0089*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0007, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLCI                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*008A*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0008, { 0 } },
    /*008B*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0009, { 0 } },
    /*008C*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x000A, { 0 } },
    /*008D*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x000B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLCIC                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*008E*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x000C, { 0 } },
    /*008F*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x000D, { 0 } },
    /*0090*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x000E, { 0 } },
    /*0091*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x000F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLCMSK                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0092*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0010, { 0 } },
    /*0093*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0011, { 0 } },
    /*0094*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0012, { 0 } },
    /*0095*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0013, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLCS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0096*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0014, { 0 } },
    /*0097*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0015, { 0 } },
    /*0098*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0016, { 0 } },
    /*0099*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0017, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLENDPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*009A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0076, { 0 } },
    /*009B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0077, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLENDPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*009C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0078, { 0 } },
    /*009D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0079, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLENDVPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*009E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x007A, { 0 } },
    /*009F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x007B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLENDVPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x007C, { 0 } },
    /*00A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x007D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLSFILL                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00A2*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0018, { 0 } },
    /*00A3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0019, { 0 } },
    /*00A4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x001A, { 0 } },
    /*00A5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x001B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLSI                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00A6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x000C, { 0 } },
    /*00A7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x000D, { 0 } },
    /*00A8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x000E, { 0 } },
    /*00A9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x000F, { 0 } },
    /*00AA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0010, { 0 } },
    /*00AB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0011, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLSIC                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00AC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x001C, { 0 } },
    /*00AD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x001D, { 0 } },
    /*00AE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x001E, { 0 } },
    /*00AF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x001F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLSMSK                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00B0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0012, { 0 } },
    /*00B1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0013, { 0 } },
    /*00B2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0014, { 0 } },
    /*00B3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0015, { 0 } },
    /*00B4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0016, { 0 } },
    /*00B5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0017, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BLSR                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00B6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0018, { 0 } },
    /*00B7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0019, { 0 } },
    /*00B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x001A, { 0 } },
    /*00B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x001B, { 0 } },
    /*00BA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x001C, { 0 } },
    /*00BB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x001D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDCL                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00BC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x007E, { 0 } },
    /*00BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x007F, { 0 } },
    /*00BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0080, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDCN                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0081, { 0 } },
    /*00C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0082, { 0 } },
    /*00C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0083, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDCU                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0084, { 0 } },
    /*00C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0085, { 0 } },
    /*00C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0086, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDLDX                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0087, { 0 } },
    /*00C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0088, { 0 } },
    /*00C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0089, { 0 } },
    /*00C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x008A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDMK                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x008B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDMOV                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x008C, { 0 } },
    /*00CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x008D, { 0 } },
    /*00CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x008E, { 0 } },
    /*00CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x008F, { 0 } },
    /*00CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0090, { 0 } },
    /*00CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0091, { 0 } },
    /*00D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0092, { 0 } },
    /*00D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0093, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BNDSTX                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0094, { 0 } },
    /*00D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0095, { 0 } },
    /*00D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0096, { 0 } },
    /*00D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0097, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BOUND                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0098, { 0 } },
    /*00D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0099, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BSF                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x009A, { 0 } },
    /*00D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x009B, { 0 } },
    /*00DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x009C, { 0 } },
    /*00DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x009D, { 0 } },
    /*00DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x009E, { 0 } },
    /*00DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x009F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BSR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A0, { 0 } },
    /*00DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A1, { 0 } },
    /*00E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A2, { 0 } },
    /*00E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A3, { 0 } },
    /*00E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A4, { 0 } },
    /*00E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BSWAP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BT                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A7, { 0 } },
    /*00E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A8, { 0 } },
    /*00E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00A9, { 0 } },
    /*00E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00AA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BTC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00AB, { 0 } },
    /*00EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00AC, { 0 } },
    /*00EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00AD, { 0 } },
    /*00EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00AE, { 0 } },
    /*00ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00AF, { 0 } },
    /*00EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BTR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B1, { 0 } },
    /*00F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B2, { 0 } },
    /*00F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B3, { 0 } },
    /*00F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B4, { 0 } },
    /*00F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B5, { 0 } },
    /*00F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BTS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B7, { 0 } },
    /*00F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B8, { 0 } },
    /*00F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00B9, { 0 } },
    /*00F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00BA, { 0 } },
    /*00F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00BB, { 0 } },
    /*00FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00BC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* BZHI                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*00FB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x001E, { 0 } },
    /*00FC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x001F, { 0 } },
    /*00FD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0020, { 0 } },
    /*00FE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0021, { 0 } },
    /*00FF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0022, { 0 } },
    /*0100*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0023, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CALL                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0101*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00BD, { 0 } },
    /*0102*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00BE, { 0 } },
    /*0103*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00BF, { 0 } },
    /*0104*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CALL_FAR                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0105*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C1, { 0 } },
    /*0106*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CBW                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0107*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CDQ                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0108*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CDQE                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0109*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLAC                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*010A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*010B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLD                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*010C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLEVICT0                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*010D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0024, { 0 } },
    /*010E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0000, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLEVICT1                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*010F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0025, { 0 } },
    /*0110*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0001, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLFLUSH                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0111*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00C9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLFLUSHOPT                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0112*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLGI                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0113*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLI                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0114*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLRSSBSY                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0115*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00CD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLTS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0116*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLWB                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0117*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00CF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CLZERO                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0118*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0119*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*011A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D2, { 0 } },
    /*011B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVBE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*011C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D4, { 0 } },
    /*011D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVL                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*011E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D6, { 0 } },
    /*011F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVLE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0120*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D8, { 0 } },
    /*0121*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0122*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00DA, { 0 } },
    /*0123*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00DB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNBE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0124*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00DC, { 0 } },
    /*0125*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNL                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0126*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00DE, { 0 } },
    /*0127*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00DF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNLE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0128*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E0, { 0 } },
    /*0129*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNO                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*012A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E2, { 0 } },
    /*012B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*012C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E4, { 0 } },
    /*012D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*012E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E6, { 0 } },
    /*012F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVNZ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0130*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E8, { 0 } },
    /*0131*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00E9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVO                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0132*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00EA, { 0 } },
    /*0133*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00EB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0134*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00EC, { 0 } },
    /*0135*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00ED, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0136*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00EE, { 0 } },
    /*0137*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00EF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMOVZ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0138*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F0, { 0 } },
    /*0139*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMP                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*013A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F2, { 0 } },
    /*013B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F3, { 0 } },
    /*013C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F4, { 0 } },
    /*013D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F5, { 0 } },
    /*013E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F6, { 0 } },
    /*013F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F7, { 0 } },
    /*0140*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F8, { 0 } },
    /*0141*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00F9, { 0 } },
    /*0142*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00FA, { 0 } },
    /*0143*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00FB, { 0 } },
    /*0144*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00FC, { 0 } },
    /*0145*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00FD, { 0 } },
    /*0146*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00FE, { 0 } },
    /*0147*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x00FF, { 0 } },
    /*0148*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0100, { 0 } },
    /*0149*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0101, { 0 } },
    /*014A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0102, { 0 } },
    /*014B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0103, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*014C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0104, { 0 } },
    /*014D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0105, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*014E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0106, { 0 } },
    /*014F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0107, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPSB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0150*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0108, { 0 } },
    /*0151*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0109, { 0 } },
    /*0152*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x010A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0153*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x010B, { 0 } },
    /*0154*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x010C, { 0 } },
    /*0155*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x010D, { 0 } },
    /*0156*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x010E, { 0 } },
    /*0157*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x010F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPSQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0158*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0110, { 0 } },
    /*0159*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0111, { 0 } },
    /*015A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0112, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*015B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0113, { 0 } },
    /*015C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0114, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPSW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*015D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0115, { 0 } },
    /*015E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0116, { 0 } },
    /*015F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0117, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPXCHG                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0160*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0118, { 0 } },
    /*0161*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0119, { 0 } },
    /*0162*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x011A, { 0 } },
    /*0163*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x011B, { 0 } },
    /*0164*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x011C, { 0 } },
    /*0165*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x011D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPXCHG16B                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0166*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x011E, { 0 } },
    /*0167*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x011F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CMPXCHG8B                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0168*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0120, { 0 } },
    /*0169*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0121, { 0 } },
    /*016A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0122, { 0 } },
    /*016B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0123, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* COMISD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*016C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0124, { 0 } },
    /*016D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0125, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* COMISS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*016E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0126, { 0 } },
    /*016F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0127, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CPUID                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0170*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0128, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CQO                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0171*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0129, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CRC32                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0172*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x012A, { 0 } },
    /*0173*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x012B, { 0 } },
    /*0174*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x012C, { 0 } },
    /*0175*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x012D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTDQ2PD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0176*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x012E, { 0 } },
    /*0177*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x012F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTDQ2PS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0178*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0130, { 0 } },
    /*0179*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0131, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPD2DQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*017A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0132, { 0 } },
    /*017B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0133, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPD2PI                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*017C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0134, { 0 } },
    /*017D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0135, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPD2PS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*017E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0136, { 0 } },
    /*017F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0137, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPI2PD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0180*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0138, { 0 } },
    /*0181*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0139, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPI2PS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0182*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x013A, { 0 } },
    /*0183*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x013B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPS2DQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0184*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x013C, { 0 } },
    /*0185*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x013D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPS2PD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0186*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x013E, { 0 } },
    /*0187*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x013F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTPS2PI                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0188*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0140, { 0 } },
    /*0189*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0141, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTSD2SI                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*018A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0142, { 0 } },
    /*018B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0143, { 0 } },
    /*018C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0144, { 0 } },
    /*018D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0145, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTSD2SS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*018E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0146, { 0 } },
    /*018F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0147, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTSI2SD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0190*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0148, { 0 } },
    /*0191*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0149, { 0 } },
    /*0192*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x014A, { 0 } },
    /*0193*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x014B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTSI2SS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0194*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x014C, { 0 } },
    /*0195*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x014D, { 0 } },
    /*0196*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x014E, { 0 } },
    /*0197*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x014F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTSS2SD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0198*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0150, { 0 } },
    /*0199*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0151, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTSS2SI                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*019A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0152, { 0 } },
    /*019B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0153, { 0 } },
    /*019C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0154, { 0 } },
    /*019D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0155, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTTPD2DQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*019E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0156, { 0 } },
    /*019F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0157, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTTPD2PI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0158, { 0 } },
    /*01A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0159, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTTPS2DQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01A2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x015A, { 0 } },
    /*01A3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x015B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTTPS2PI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01A4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x015C, { 0 } },
    /*01A5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x015D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTTSD2SI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01A6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x015E, { 0 } },
    /*01A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x015F, { 0 } },
    /*01A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0160, { 0 } },
    /*01A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0161, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CVTTSS2SI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0162, { 0 } },
    /*01AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0163, { 0 } },
    /*01AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0164, { 0 } },
    /*01AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0165, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CWD                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0166, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* CWDE                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0167, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DAA                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0168, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DAS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0169, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DEC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x016A, { 0 } },
    /*01B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x016B, { 0 } },
    /*01B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x016C, { 0 } },
    /*01B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x016D, { 0 } },
    /*01B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x016E, { 0 } },
    /*01B7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x016F, { 0 } },
    /*01B8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0170, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DELAY                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0026, { 0 } },
    /*01BA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0027, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DIV                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01BB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0171, { 0 } },
    /*01BC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0172, { 0 } },
    /*01BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0173, { 0 } },
    /*01BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0174, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DIVPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0175, { 0 } },
    /*01C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0176, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DIVPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0177, { 0 } },
    /*01C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0178, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DIVSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0179, { 0 } },
    /*01C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x017A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DIVSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x017B, { 0 } },
    /*01C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x017C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DPPD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x017D, { 0 } },
    /*01C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x017E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* DPPS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x017F, { 0 } },
    /*01CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0180, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* EMMS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0181, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ENCLS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0182, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ENCLU                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0183, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ENDBR32                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0184, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ENDBR64                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0185, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ENTER                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0186, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* EXTRACTPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0187, { 0 } },
    /*01D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0188, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* F2XM1                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0189, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FABS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x018A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FADD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x018B, { 0 } },
    /*01D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x018C, { 0 } },
    /*01D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x018D, { 0 } },
    /*01D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x018E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FADDP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x018F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FBLD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0190, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FBSTP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0191, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCHS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0192, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0193, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVBE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0194, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0195, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVNB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0196, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVNBE                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0197, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVNE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0198, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVNU                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0199, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCMOVU                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x019A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCOM                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x019B, { 0 } },
    /*01E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x019C, { 0 } },
    /*01E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x019D, { 0 } },
    /*01E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x019E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCOMI                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x019F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCOMIP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCOMP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A1, { 0 } },
    /*01EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A2, { 0 } },
    /*01ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A3, { 0 } },
    /*01EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A4, { 0 } },
    /*01EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCOMPP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FCOS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FDECSTP                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FDISI8087_NOP                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01A9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FDIV                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01AA, { 0 } },
    /*01F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01AB, { 0 } },
    /*01F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01AC, { 0 } },
    /*01F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01AD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FDIVP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01AE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FDIVR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01AF, { 0 } },
    /*01FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B0, { 0 } },
    /*01FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B1, { 0 } },
    /*01FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FDIVRP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FEMMS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FENI8087_NOP                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*01FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FFREE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0200*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FFREEP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0201*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FIADD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0202*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B8, { 0 } },
    /*0203*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01B9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FICOM                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0204*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01BA, { 0 } },
    /*0205*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01BB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FICOMP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0206*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01BC, { 0 } },
    /*0207*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01BD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FIDIV                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0208*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01BE, { 0 } },
    /*0209*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01BF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FIDIVR                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*020A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C0, { 0 } },
    /*020B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FILD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*020C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C2, { 0 } },
    /*020D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C3, { 0 } },
    /*020E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FIMUL                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*020F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C5, { 0 } },
    /*0210*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FINCSTP                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0211*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FIST                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0212*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C8, { 0 } },
    /*0213*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01C9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FISTP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0214*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01CA, { 0 } },
    /*0215*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01CB, { 0 } },
    /*0216*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FISTTP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0217*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01CD, { 0 } },
    /*0218*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01CE, { 0 } },
    /*0219*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01CF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FISUB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*021A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D0, { 0 } },
    /*021B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FISUBR                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*021C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D2, { 0 } },
    /*021D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLD                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*021E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D4, { 0 } },
    /*021F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D5, { 0 } },
    /*0220*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D6, { 0 } },
    /*0221*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLD1                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0222*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDCW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0223*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDENV                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0224*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01DA, { 0 } },
    /*0225*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01DB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDL2E                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0226*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01DC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDL2T                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0227*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDLG2                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0228*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01DE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDLN2                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0229*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01DF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDPI                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*022A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FLDZ                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*022B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FMUL                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*022C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E2, { 0 } },
    /*022D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E3, { 0 } },
    /*022E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E4, { 0 } },
    /*022F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FMULP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0230*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNCLEX                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0231*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNINIT                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0232*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNOP                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0233*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01E9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNSAVE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0234*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01EA, { 0 } },
    /*0235*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01EB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNSTCW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0236*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01EC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNSTENV                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0237*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01ED, { 0 } },
    /*0238*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01EE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FNSTSW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0239*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01EF, { 0 } },
    /*023A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FPATAN                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*023B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FPREM                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*023C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FPREM1                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*023D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FPTAN                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*023E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FRNDINT                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*023F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FRSTOR                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0240*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F6, { 0 } },
    /*0241*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSCALE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0242*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSETPM287_NOP                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0243*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSIN                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0244*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01FA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSINCOS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0245*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01FB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSQRT                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0246*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01FC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FST                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0247*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01FD, { 0 } },
    /*0248*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01FE, { 0 } },
    /*0249*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x01FF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSTP                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*024A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0200, { 0 } },
    /*024B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0201, { 0 } },
    /*024C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0202, { 0 } },
    /*024D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0203, { 0 } },
    /*024E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0204, { 0 } },
    /*024F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0205, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSTPNCE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0250*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0206, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSUB                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0251*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0207, { 0 } },
    /*0252*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0208, { 0 } },
    /*0253*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0209, { 0 } },
    /*0254*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x020A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSUBP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0255*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x020B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSUBR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0256*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x020C, { 0 } },
    /*0257*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x020D, { 0 } },
    /*0258*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x020E, { 0 } },
    /*0259*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x020F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FSUBRP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*025A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0210, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FTST                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*025B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0211, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FUCOM                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*025C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0212, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FUCOMI                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*025D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0213, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FUCOMIP                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*025E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0214, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FUCOMP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*025F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0215, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FUCOMPP                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0260*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0216, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FWAIT                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0261*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0217, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXAM                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0262*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0218, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXCH                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0263*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0219, { 0 } },
    /*0264*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x021A, { 0 } },
    /*0265*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x021B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXRSTOR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0266*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x021C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXRSTOR64                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0267*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x021D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXSAVE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0268*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x021E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXSAVE64                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0269*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x021F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FXTRACT                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*026A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0220, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FYL2X                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*026B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0221, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* FYL2XP1                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*026C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0222, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* GETSEC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*026D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0223, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* HADDPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*026E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0224, { 0 } },
    /*026F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0225, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* HADDPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0270*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0226, { 0 } },
    /*0271*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0227, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* HLT                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0272*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0228, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* HSUBPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0273*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0229, { 0 } },
    /*0274*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x022A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* HSUBPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0275*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x022B, { 0 } },
    /*0276*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x022C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* IDIV                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0277*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x022D, { 0 } },
    /*0278*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x022E, { 0 } },
    /*0279*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x022F, { 0 } },
    /*027A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0230, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* IMUL                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*027B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0231, { 0 } },
    /*027C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0232, { 0 } },
    /*027D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0233, { 0 } },
    /*027E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0234, { 0 } },
    /*027F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0235, { 0 } },
    /*0280*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0236, { 0 } },
    /*0281*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0237, { 0 } },
    /*0282*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0238, { 0 } },
    /*0283*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0239, { 0 } },
    /*0284*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x023A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* IN                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0285*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x023B, { 0 } },
    /*0286*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x023C, { 0 } },
    /*0287*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x023D, { 0 } },
    /*0288*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x023E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0289*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x023F, { 0 } },
    /*028A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0240, { 0 } },
    /*028B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0241, { 0 } },
    /*028C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0242, { 0 } },
    /*028D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0243, { 0 } },
    /*028E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0244, { 0 } },
    /*028F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0245, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INCSSPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0290*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0246, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INCSSPQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0291*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0247, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INSB                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0292*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0248, { 0 } },
    /*0293*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0249, { 0 } },
    /*0294*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x024A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INSD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0295*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x024B, { 0 } },
    /*0296*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x024C, { 0 } },
    /*0297*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x024D, { 0 } },
    /*0298*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x024E, { 0 } },
    /*0299*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x024F, { 0 } },
    /*029A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0250, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INSERTPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*029B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0251, { 0 } },
    /*029C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0252, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INSW                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*029D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0253, { 0 } },
    /*029E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0254, { 0 } },
    /*029F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0255, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INT                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0256, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INT1                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0257, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INT3                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0258, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INTO                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0259, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INVD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x025A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INVEPT                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x025B, { 0 } },
    /*02A6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x025C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INVLPG                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x025D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INVLPGA                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x025E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INVPCID                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x025F, { 0 } },
    /*02AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0260, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* INVVPID                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0261, { 0 } },
    /*02AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0262, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* IRET                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0263, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* IRETD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0264, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* IRETQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0265, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JB                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0266, { 0 } },
    /*02B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0267, { 0 } },
    /*02B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0268, { 0 } },
    /*02B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0269, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JBE                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x026A, { 0 } },
    /*02B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x026B, { 0 } },
    /*02B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x026C, { 0 } },
    /*02B7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x026D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JCXZ                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02B8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x026E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JECXZ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02B9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x026F, { 0 } },
    /*02BA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0270, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JKNZD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02BB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0028, { 0 } },
    /*02BC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0029, { 0 } },
    /*02BD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x002A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JKZD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02BE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x002B, { 0 } },
    /*02BF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x002C, { 0 } },
    /*02C0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x002D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JL                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0271, { 0 } },
    /*02C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0272, { 0 } },
    /*02C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0273, { 0 } },
    /*02C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0274, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JLE                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0275, { 0 } },
    /*02C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0276, { 0 } },
    /*02C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0277, { 0 } },
    /*02C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0278, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JMP                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0279, { 0 } },
    /*02CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x027A, { 0 } },
    /*02CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x027B, { 0 } },
    /*02CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x027C, { 0 } },
    /*02CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x027D, { 0 } },
    /*02CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x027E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JMP_FAR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x027F, { 0 } },
    /*02D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0280, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNB                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0281, { 0 } },
    /*02D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0282, { 0 } },
    /*02D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0283, { 0 } },
    /*02D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0284, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNBE                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0285, { 0 } },
    /*02D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0286, { 0 } },
    /*02D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0287, { 0 } },
    /*02D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0288, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNL                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0289, { 0 } },
    /*02DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x028A, { 0 } },
    /*02DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x028B, { 0 } },
    /*02DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x028C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNLE                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x028D, { 0 } },
    /*02DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x028E, { 0 } },
    /*02DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x028F, { 0 } },
    /*02E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0290, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNO                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0291, { 0 } },
    /*02E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0292, { 0 } },
    /*02E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0293, { 0 } },
    /*02E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0294, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNP                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0295, { 0 } },
    /*02E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0296, { 0 } },
    /*02E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0297, { 0 } },
    /*02E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0298, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0299, { 0 } },
    /*02EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x029A, { 0 } },
    /*02EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x029B, { 0 } },
    /*02EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x029C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JNZ                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x029D, { 0 } },
    /*02EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x029E, { 0 } },
    /*02EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x029F, { 0 } },
    /*02F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JO                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A1, { 0 } },
    /*02F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A2, { 0 } },
    /*02F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A3, { 0 } },
    /*02F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JP                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A5, { 0 } },
    /*02F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A6, { 0 } },
    /*02F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A7, { 0 } },
    /*02F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JRCXZ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02A9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JS                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02AA, { 0 } },
    /*02FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02AB, { 0 } },
    /*02FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02AC, { 0 } },
    /*02FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02AD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* JZ                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*02FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02AE, { 0 } },
    /*02FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02AF, { 0 } },
    /*0300*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B0, { 0 } },
    /*0301*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KADDB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0302*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x002E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KADDD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0303*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x002F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KADDQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0304*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0030, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KADDW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0305*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0031, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KAND                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0306*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0032, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0307*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0033, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0308*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0034, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDN                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0309*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0035, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDNB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*030A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0036, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDND                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*030B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0037, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDNQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*030C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0038, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDNR                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*030D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0039, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDNW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*030E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x003A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*030F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x003B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KANDW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0310*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x003C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KCONCATH                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0311*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x003D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KCONCATL                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0312*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x003E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KEXTRACT                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0313*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x003F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMERGE2L1H                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0314*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0040, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMERGE2L1L                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0315*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0041, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMOV                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0316*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0042, { 0 } },
    /*0317*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0043, { 0 } },
    /*0318*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0044, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMOVB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0319*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0045, { 0 } },
    /*031A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0046, { 0 } },
    /*031B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0047, { 0 } },
    /*031C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0048, { 0 } },
    /*031D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0049, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMOVD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*031E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x004A, { 0 } },
    /*031F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x004B, { 0 } },
    /*0320*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x004C, { 0 } },
    /*0321*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x004D, { 0 } },
    /*0322*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x004E, { 0 } },
    /*0323*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x004F, { 0 } },
    /*0324*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0050, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMOVQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0325*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0051, { 0 } },
    /*0326*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0052, { 0 } },
    /*0327*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0053, { 0 } },
    /*0328*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0054, { 0 } },
    /*0329*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0055, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KMOVW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*032A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0056, { 0 } },
    /*032B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0057, { 0 } },
    /*032C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0058, { 0 } },
    /*032D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0059, { 0 } },
    /*032E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x005A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KNOT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*032F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x005B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KNOTB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0330*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x005C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KNOTD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0331*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x005D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KNOTQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0332*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x005E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KNOTW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0333*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x005F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KOR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0334*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0060, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORB                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0335*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0061, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0336*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0062, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORQ                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0337*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0063, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORTESTB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0338*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0064, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORTESTD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0339*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0065, { 0 } },
    /*033A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0066, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORTESTQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*033B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0067, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORTESTW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*033C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0068, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KORW                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*033D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0069, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTLB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*033E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x006A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTLD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*033F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x006B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTLQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0340*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x006C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTLW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0341*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x006D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTRB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0342*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x006E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTRD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0343*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x006F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTRQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0344*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0070, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KSHIFTRW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0345*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0071, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KTESTB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0346*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0072, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KTESTD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0347*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0073, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KTESTQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0348*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0074, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KTESTW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0349*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0075, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KUNPCKBW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*034A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0076, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KUNPCKDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*034B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0077, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KUNPCKWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*034C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0078, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXNOR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*034D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0079, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXNORB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*034E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x007A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXNORD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*034F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x007B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXNORQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0350*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x007C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXNORW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0351*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x007D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXOR                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0352*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x007E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXORB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0353*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x007F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXORD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0354*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0080, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXORQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0355*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0081, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* KXORW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0356*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0082, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LAHF                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0357*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LAR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0358*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B3, { 0 } },
    /*0359*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LDDQU                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*035A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LDMXCSR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*035B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LDS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*035C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LEA                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*035D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LEAVE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*035E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02B9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LES                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*035F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LFENCE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0360*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02BB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LFS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0361*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02BC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LGDT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0362*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02BD, { 0 } },
    /*0363*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02BE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LGS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0364*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02BF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LIDT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0365*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C0, { 0 } },
    /*0366*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LLDT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0367*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C2, { 0 } },
    /*0368*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LLWPCB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0369*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0020, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LMSW                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*036A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C4, { 0 } },
    /*036B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LODSB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*036C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C6, { 0 } },
    /*036D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C7, { 0 } },
    /*036E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LODSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*036F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02C9, { 0 } },
    /*0370*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02CA, { 0 } },
    /*0371*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LODSQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0372*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02CC, { 0 } },
    /*0373*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02CD, { 0 } },
    /*0374*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LODSW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0375*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02CF, { 0 } },
    /*0376*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D0, { 0 } },
    /*0377*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LOOP                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0378*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LOOPE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0379*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D3, { 0 } },
    /*037A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D4, { 0 } },
    /*037B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D5, { 0 } },
    /*037C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LOOPNE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*037D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D7, { 0 } },
    /*037E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D8, { 0 } },
    /*037F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02D9, { 0 } },
    /*0380*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02DA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LSL                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0381*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02DB, { 0 } },
    /*0382*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02DC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LSS                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0383*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LTR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0384*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02DE, { 0 } },
    /*0385*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02DF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LWPINS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0386*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0021, { 0 } },
    /*0387*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0022, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LWPVAL                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0388*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0023, { 0 } },
    /*0389*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0024, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* LZCNT                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*038A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E0, { 0 } },
    /*038B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E1, { 0 } },
    /*038C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0083, { 0 } },
    /*038D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0084, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MASKMOVDQU                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*038E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MASKMOVQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*038F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MAXPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0390*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E4, { 0 } },
    /*0391*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MAXPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0392*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E6, { 0 } },
    /*0393*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MAXSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0394*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E8, { 0 } },
    /*0395*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02E9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MAXSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0396*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02EA, { 0 } },
    /*0397*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02EB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MFENCE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0398*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02EC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MINPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0399*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02ED, { 0 } },
    /*039A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02EE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MINPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*039B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02EF, { 0 } },
    /*039C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MINSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*039D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F1, { 0 } },
    /*039E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MINSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*039F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F3, { 0 } },
    /*03A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MONITOR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F5, { 0 } },
    /*03A2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F6, { 0 } },
    /*03A3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F7, { 0 } },
    /*03A4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOV                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03A5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02F9, { 0 } },
    /*03A6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02FA, { 0 } },
    /*03A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02FB, { 0 } },
    /*03A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02FC, { 0 } },
    /*03A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02FD, { 0 } },
    /*03AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02FE, { 0 } },
    /*03AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x02FF, { 0 } },
    /*03AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0300, { 0 } },
    /*03AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0301, { 0 } },
    /*03AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0302, { 0 } },
    /*03AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0303, { 0 } },
    /*03B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0304, { 0 } },
    /*03B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0305, { 0 } },
    /*03B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0306, { 0 } },
    /*03B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0307, { 0 } },
    /*03B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0308, { 0 } },
    /*03B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0309, { 0 } },
    /*03B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x030A, { 0 } },
    /*03B7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x030B, { 0 } },
    /*03B8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x030C, { 0 } },
    /*03B9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x030D, { 0 } },
    /*03BA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x030E, { 0 } },
    /*03BB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x030F, { 0 } },
    /*03BC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0310, { 0 } },
    /*03BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0311, { 0 } },
    /*03BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0312, { 0 } },
    /*03BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0313, { 0 } },
    /*03C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0314, { 0 } },
    /*03C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0315, { 0 } },
    /*03C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0316, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVAPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0317, { 0 } },
    /*03C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0318, { 0 } },
    /*03C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0319, { 0 } },
    /*03C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x031A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVAPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x031B, { 0 } },
    /*03C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x031C, { 0 } },
    /*03C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x031D, { 0 } },
    /*03CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x031E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVBE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x031F, { 0 } },
    /*03CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0320, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0321, { 0 } },
    /*03CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0322, { 0 } },
    /*03CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0323, { 0 } },
    /*03D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0324, { 0 } },
    /*03D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0325, { 0 } },
    /*03D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0326, { 0 } },
    /*03D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0327, { 0 } },
    /*03D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0328, { 0 } },
    /*03D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0329, { 0 } },
    /*03D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x032A, { 0 } },
    /*03D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x032B, { 0 } },
    /*03D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x032C, { 0 } },
    /*03D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x032D, { 0 } },
    /*03DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x032E, { 0 } },
    /*03DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x032F, { 0 } },
    /*03DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0330, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVDDUP                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0331, { 0 } },
    /*03DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0332, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVDQ2Q                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0333, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVDQA                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0334, { 0 } },
    /*03E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0335, { 0 } },
    /*03E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0336, { 0 } },
    /*03E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0337, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVDQU                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0338, { 0 } },
    /*03E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0339, { 0 } },
    /*03E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x033A, { 0 } },
    /*03E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x033B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVHLPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x033C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVHPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x033D, { 0 } },
    /*03EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x033E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVHPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x033F, { 0 } },
    /*03EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0340, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVLHPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0341, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVLPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0342, { 0 } },
    /*03EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0343, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVLPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0344, { 0 } },
    /*03F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0345, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVMSKPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0346, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVMSKPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0347, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVNTDQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0348, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVNTDQA                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0349, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVNTI                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x034A, { 0 } },
    /*03F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x034B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVNTPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x034C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVNTPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x034D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVNTQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x034E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVQ                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*03FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x034F, { 0 } },
    /*03FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0350, { 0 } },
    /*03FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0351, { 0 } },
    /*03FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0352, { 0 } },
    /*03FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0353, { 0 } },
    /*0400*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0354, { 0 } },
    /*0401*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0355, { 0 } },
    /*0402*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0356, { 0 } },
    /*0403*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0357, { 0 } },
    /*0404*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0358, { 0 } },
    /*0405*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0359, { 0 } },
    /*0406*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x035A, { 0 } },
    /*0407*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x035B, { 0 } },
    /*0408*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x035C, { 0 } },
    /*0409*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x035D, { 0 } },
    /*040A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x035E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVQ2DQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*040B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x035F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*040C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0360, { 0 } },
    /*040D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0361, { 0 } },
    /*040E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0362, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*040F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0363, { 0 } },
    /*0410*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0364, { 0 } },
    /*0411*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0365, { 0 } },
    /*0412*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0366, { 0 } },
    /*0413*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0367, { 0 } },
    /*0414*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0368, { 0 } },
    /*0415*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0369, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSHDUP                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0416*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x036A, { 0 } },
    /*0417*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x036B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSLDUP                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0418*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x036C, { 0 } },
    /*0419*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x036D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*041A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x036E, { 0 } },
    /*041B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x036F, { 0 } },
    /*041C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0370, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*041D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0371, { 0 } },
    /*041E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0372, { 0 } },
    /*041F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0373, { 0 } },
    /*0420*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0374, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0421*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0375, { 0 } },
    /*0422*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0376, { 0 } },
    /*0423*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0377, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSX                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0424*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0378, { 0 } },
    /*0425*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0379, { 0 } },
    /*0426*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x037A, { 0 } },
    /*0427*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x037B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVSXD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0428*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x037C, { 0 } },
    /*0429*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x037D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVUPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*042A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x037E, { 0 } },
    /*042B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x037F, { 0 } },
    /*042C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0380, { 0 } },
    /*042D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0381, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVUPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*042E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0382, { 0 } },
    /*042F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0383, { 0 } },
    /*0430*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0384, { 0 } },
    /*0431*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0385, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MOVZX                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0432*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0386, { 0 } },
    /*0433*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0387, { 0 } },
    /*0434*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0388, { 0 } },
    /*0435*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0389, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MPSADBW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0436*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x038A, { 0 } },
    /*0437*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x038B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MUL                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0438*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x038C, { 0 } },
    /*0439*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x038D, { 0 } },
    /*043A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x038E, { 0 } },
    /*043B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x038F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MULPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*043C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0390, { 0 } },
    /*043D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0391, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MULPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*043E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0392, { 0 } },
    /*043F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0393, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MULSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0440*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0394, { 0 } },
    /*0441*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0395, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MULSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0442*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0396, { 0 } },
    /*0443*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0397, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MULX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0444*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0085, { 0 } },
    /*0445*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0086, { 0 } },
    /*0446*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0087, { 0 } },
    /*0447*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0088, { 0 } },
    /*0448*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0089, { 0 } },
    /*0449*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x008A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* MWAIT                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*044A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0398, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* NEG                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*044B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0399, { 0 } },
    /*044C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x039A, { 0 } },
    /*044D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x039B, { 0 } },
    /*044E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x039C, { 0 } },
    /*044F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x039D, { 0 } },
    /*0450*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x039E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* NOP                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0451*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x039F, { 0 } },
    /*0452*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A0, { 0 } },
    /*0453*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A1, { 0 } },
    /*0454*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A2, { 0 } },
    /*0455*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A3, { 0 } },
    /*0456*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A4, { 0 } },
    /*0457*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A5, { 0 } },
    /*0458*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A6, { 0 } },
    /*0459*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A7, { 0 } },
    /*045A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A8, { 0 } },
    /*045B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03A9, { 0 } },
    /*045C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03AA, { 0 } },
    /*045D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03AB, { 0 } },
    /*045E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03AC, { 0 } },
    /*045F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03AD, { 0 } },
    /*0460*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03AE, { 0 } },
    /*0461*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03AF, { 0 } },
    /*0462*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B0, { 0 } },
    /*0463*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B1, { 0 } },
    /*0464*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B2, { 0 } },
    /*0465*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B3, { 0 } },
    /*0466*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B4, { 0 } },
    /*0467*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B5, { 0 } },
    /*0468*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B6, { 0 } },
    /*0469*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B7, { 0 } },
    /*046A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B8, { 0 } },
    /*046B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03B9, { 0 } },
    /*046C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03BA, { 0 } },
    /*046D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03BB, { 0 } },
    /*046E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03BC, { 0 } },
    /*046F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03BD, { 0 } },
    /*0470*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03BE, { 0 } },
    /*0471*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03BF, { 0 } },
    /*0472*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C0, { 0 } },
    /*0473*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C1, { 0 } },
    /*0474*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C2, { 0 } },
    /*0475*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C3, { 0 } },
    /*0476*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C4, { 0 } },
    /*0477*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C5, { 0 } },
    /*0478*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C6, { 0 } },
    /*0479*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C7, { 0 } },
    /*047A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C8, { 0 } },
    /*047B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03C9, { 0 } },
    /*047C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03CA, { 0 } },
    /*047D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03CB, { 0 } },
    /*047E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03CC, { 0 } },
    /*047F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03CD, { 0 } },
    /*0480*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03CE, { 0 } },
    /*0481*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03CF, { 0 } },
    /*0482*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D0, { 0 } },
    /*0483*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D1, { 0 } },
    /*0484*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D2, { 0 } },
    /*0485*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D3, { 0 } },
    /*0486*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D4, { 0 } },
    /*0487*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D5, { 0 } },
    /*0488*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D6, { 0 } },
    /*0489*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* NOT                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*048A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D8, { 0 } },
    /*048B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03D9, { 0 } },
    /*048C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03DA, { 0 } },
    /*048D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03DB, { 0 } },
    /*048E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03DC, { 0 } },
    /*048F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* OR                                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0490*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03DE, { 0 } },
    /*0491*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03DF, { 0 } },
    /*0492*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E0, { 0 } },
    /*0493*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E1, { 0 } },
    /*0494*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E2, { 0 } },
    /*0495*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E3, { 0 } },
    /*0496*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E4, { 0 } },
    /*0497*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E5, { 0 } },
    /*0498*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E6, { 0 } },
    /*0499*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E7, { 0 } },
    /*049A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E8, { 0 } },
    /*049B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03E9, { 0 } },
    /*049C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03EA, { 0 } },
    /*049D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03EB, { 0 } },
    /*049E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03EC, { 0 } },
    /*049F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03ED, { 0 } },
    /*04A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03EE, { 0 } },
    /*04A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03EF, { 0 } },
    /*04A2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F0, { 0 } },
    /*04A3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F1, { 0 } },
    /*04A4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F2, { 0 } },
    /*04A5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F3, { 0 } },
    /*04A6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F4, { 0 } },
    /*04A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ORPD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F6, { 0 } },
    /*04A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ORPS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F8, { 0 } },
    /*04AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* OUT                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03FA, { 0 } },
    /*04AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03FB, { 0 } },
    /*04AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03FC, { 0 } },
    /*04AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03FD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* OUTSB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03FE, { 0 } },
    /*04B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x03FF, { 0 } },
    /*04B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0400, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* OUTSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0401, { 0 } },
    /*04B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0402, { 0 } },
    /*04B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0403, { 0 } },
    /*04B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0404, { 0 } },
    /*04B7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0405, { 0 } },
    /*04B8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0406, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* OUTSW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04B9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0407, { 0 } },
    /*04BA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0408, { 0 } },
    /*04BB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0409, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PABSB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04BC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x040A, { 0 } },
    /*04BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x040B, { 0 } },
    /*04BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x040C, { 0 } },
    /*04BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x040D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PABSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x040E, { 0 } },
    /*04C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x040F, { 0 } },
    /*04C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0410, { 0 } },
    /*04C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0411, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PABSW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0412, { 0 } },
    /*04C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0413, { 0 } },
    /*04C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0414, { 0 } },
    /*04C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0415, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PACKSSDW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0416, { 0 } },
    /*04C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0417, { 0 } },
    /*04CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0418, { 0 } },
    /*04CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0419, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PACKSSWB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x041A, { 0 } },
    /*04CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x041B, { 0 } },
    /*04CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x041C, { 0 } },
    /*04CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x041D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PACKUSDW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x041E, { 0 } },
    /*04D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x041F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PACKUSWB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0420, { 0 } },
    /*04D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0421, { 0 } },
    /*04D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0422, { 0 } },
    /*04D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0423, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0424, { 0 } },
    /*04D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0425, { 0 } },
    /*04D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0426, { 0 } },
    /*04D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0427, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0428, { 0 } },
    /*04DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0429, { 0 } },
    /*04DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x042A, { 0 } },
    /*04DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x042B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x042C, { 0 } },
    /*04DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x042D, { 0 } },
    /*04E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x042E, { 0 } },
    /*04E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x042F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDSB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0430, { 0 } },
    /*04E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0431, { 0 } },
    /*04E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0432, { 0 } },
    /*04E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0433, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDSW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0434, { 0 } },
    /*04E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0435, { 0 } },
    /*04E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0436, { 0 } },
    /*04E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0437, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDUSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0438, { 0 } },
    /*04EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0439, { 0 } },
    /*04EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x043A, { 0 } },
    /*04ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x043B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDUSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x043C, { 0 } },
    /*04EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x043D, { 0 } },
    /*04F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x043E, { 0 } },
    /*04F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x043F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PADDW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0440, { 0 } },
    /*04F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0441, { 0 } },
    /*04F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0442, { 0 } },
    /*04F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0443, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PALIGNR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0444, { 0 } },
    /*04F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0445, { 0 } },
    /*04F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0446, { 0 } },
    /*04F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0447, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PAND                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0448, { 0 } },
    /*04FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0449, { 0 } },
    /*04FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x044A, { 0 } },
    /*04FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x044B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PANDN                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*04FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x044C, { 0 } },
    /*04FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x044D, { 0 } },
    /*0500*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x044E, { 0 } },
    /*0501*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x044F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PAUSE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0502*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0450, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PAVGB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0503*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0451, { 0 } },
    /*0504*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0452, { 0 } },
    /*0505*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0453, { 0 } },
    /*0506*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0454, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PAVGUSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0507*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0000, { 0 } },
    /*0508*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0001, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PAVGW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0509*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0455, { 0 } },
    /*050A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0456, { 0 } },
    /*050B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0457, { 0 } },
    /*050C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0458, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PBLENDVB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*050D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0459, { 0 } },
    /*050E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x045A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PBLENDW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*050F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x045B, { 0 } },
    /*0510*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x045C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCLMULQDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0511*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x045D, { 0 } },
    /*0512*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x045E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPEQB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0513*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x045F, { 0 } },
    /*0514*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0460, { 0 } },
    /*0515*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0461, { 0 } },
    /*0516*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0462, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPEQD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0517*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0463, { 0 } },
    /*0518*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0464, { 0 } },
    /*0519*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0465, { 0 } },
    /*051A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0466, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPEQQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*051B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0467, { 0 } },
    /*051C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0468, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPEQW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*051D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0469, { 0 } },
    /*051E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x046A, { 0 } },
    /*051F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x046B, { 0 } },
    /*0520*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x046C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPESTRI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0521*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x046D, { 0 } },
    /*0522*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x046E, { 0 } },
    /*0523*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x046F, { 0 } },
    /*0524*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0470, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPESTRM                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0525*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0471, { 0 } },
    /*0526*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0472, { 0 } },
    /*0527*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0473, { 0 } },
    /*0528*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0474, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPGTB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0529*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0475, { 0 } },
    /*052A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0476, { 0 } },
    /*052B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0477, { 0 } },
    /*052C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0478, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPGTD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*052D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0479, { 0 } },
    /*052E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x047A, { 0 } },
    /*052F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x047B, { 0 } },
    /*0530*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x047C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPGTQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0531*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x047D, { 0 } },
    /*0532*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x047E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPGTW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0533*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x047F, { 0 } },
    /*0534*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0480, { 0 } },
    /*0535*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0481, { 0 } },
    /*0536*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0482, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPISTRI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0537*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0483, { 0 } },
    /*0538*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0484, { 0 } },
    /*0539*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0485, { 0 } },
    /*053A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0486, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PCMPISTRM                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*053B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0487, { 0 } },
    /*053C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0488, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PDEP                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*053D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x008B, { 0 } },
    /*053E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x008C, { 0 } },
    /*053F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x008D, { 0 } },
    /*0540*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x008E, { 0 } },
    /*0541*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x008F, { 0 } },
    /*0542*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0090, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PEXT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0543*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0091, { 0 } },
    /*0544*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0092, { 0 } },
    /*0545*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0093, { 0 } },
    /*0546*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0094, { 0 } },
    /*0547*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0095, { 0 } },
    /*0548*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0096, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PEXTRB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0549*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0489, { 0 } },
    /*054A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x048A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PEXTRD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*054B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x048B, { 0 } },
    /*054C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x048C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PEXTRQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*054D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x048D, { 0 } },
    /*054E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x048E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PEXTRW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*054F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x048F, { 0 } },
    /*0550*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0490, { 0 } },
    /*0551*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0491, { 0 } },
    /*0552*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0492, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PF2ID                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0553*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0002, { 0 } },
    /*0554*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0003, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PF2IW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0555*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0004, { 0 } },
    /*0556*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0005, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFACC                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0557*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0006, { 0 } },
    /*0558*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0007, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFADD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0559*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0008, { 0 } },
    /*055A*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0009, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFCMPEQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*055B*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x000A, { 0 } },
    /*055C*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x000B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFCMPGE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*055D*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x000C, { 0 } },
    /*055E*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x000D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFCMPGT                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*055F*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x000E, { 0 } },
    /*0560*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x000F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFCPIT1                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0561*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0010, { 0 } },
    /*0562*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0011, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFMAX                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0563*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0012, { 0 } },
    /*0564*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0013, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFMIN                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0565*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0014, { 0 } },
    /*0566*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0015, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFMUL                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0567*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0016, { 0 } },
    /*0568*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0017, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFNACC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0569*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0018, { 0 } },
    /*056A*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0019, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFPNACC                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*056B*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x001A, { 0 } },
    /*056C*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x001B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFRCP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*056D*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x001C, { 0 } },
    /*056E*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x001D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFRCPIT2                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*056F*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x001E, { 0 } },
    /*0570*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x001F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFRSQIT1                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0571*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0020, { 0 } },
    /*0572*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0021, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFSQRT                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0573*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0022, { 0 } },
    /*0574*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0023, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFSUB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0575*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0024, { 0 } },
    /*0576*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0025, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PFSUBR                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0577*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0026, { 0 } },
    /*0578*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0027, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHADDD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0579*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0493, { 0 } },
    /*057A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0494, { 0 } },
    /*057B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0495, { 0 } },
    /*057C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0496, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHADDSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*057D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0497, { 0 } },
    /*057E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0498, { 0 } },
    /*057F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0499, { 0 } },
    /*0580*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x049A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHADDW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0581*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x049B, { 0 } },
    /*0582*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x049C, { 0 } },
    /*0583*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x049D, { 0 } },
    /*0584*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x049E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHMINPOSUW                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0585*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x049F, { 0 } },
    /*0586*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHSUBD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0587*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A1, { 0 } },
    /*0588*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A2, { 0 } },
    /*0589*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A3, { 0 } },
    /*058A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHSUBSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*058B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A5, { 0 } },
    /*058C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A6, { 0 } },
    /*058D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A7, { 0 } },
    /*058E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PHSUBW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*058F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04A9, { 0 } },
    /*0590*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04AA, { 0 } },
    /*0591*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04AB, { 0 } },
    /*0592*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04AC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PI2FD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0593*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0028, { 0 } },
    /*0594*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x0029, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PI2FW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0595*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x002A, { 0 } },
    /*0596*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x002B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PINSRB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0597*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04AD, { 0 } },
    /*0598*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04AE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PINSRD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0599*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04AF, { 0 } },
    /*059A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PINSRQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*059B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B1, { 0 } },
    /*059C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PINSRW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*059D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B3, { 0 } },
    /*059E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B4, { 0 } },
    /*059F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B5, { 0 } },
    /*05A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMADDUBSW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B7, { 0 } },
    /*05A2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B8, { 0 } },
    /*05A3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04B9, { 0 } },
    /*05A4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMADDWD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05A5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04BB, { 0 } },
    /*05A6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04BC, { 0 } },
    /*05A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04BD, { 0 } },
    /*05A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04BE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMAXSB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04BF, { 0 } },
    /*05AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMAXSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C1, { 0 } },
    /*05AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMAXSW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C3, { 0 } },
    /*05AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C4, { 0 } },
    /*05AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C5, { 0 } },
    /*05B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMAXUB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C7, { 0 } },
    /*05B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C8, { 0 } },
    /*05B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04C9, { 0 } },
    /*05B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMAXUD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04CB, { 0 } },
    /*05B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMAXUW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05B7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04CD, { 0 } },
    /*05B8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMINSB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05B9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04CF, { 0 } },
    /*05BA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMINSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05BB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D1, { 0 } },
    /*05BC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMINSW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D3, { 0 } },
    /*05BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D4, { 0 } },
    /*05BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D5, { 0 } },
    /*05C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMINUB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D7, { 0 } },
    /*05C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D8, { 0 } },
    /*05C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04D9, { 0 } },
    /*05C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04DA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMINUD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04DB, { 0 } },
    /*05C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04DC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMINUW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04DD, { 0 } },
    /*05C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04DE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVMSKB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04DF, { 0 } },
    /*05CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVSXBD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E1, { 0 } },
    /*05CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVSXBQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E3, { 0 } },
    /*05CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVSXBW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E5, { 0 } },
    /*05D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVSXDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E7, { 0 } },
    /*05D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVSXWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04E9, { 0 } },
    /*05D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04EA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVSXWQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04EB, { 0 } },
    /*05D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04EC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVZXBD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04ED, { 0 } },
    /*05D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04EE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVZXBQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04EF, { 0 } },
    /*05DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVZXBW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F1, { 0 } },
    /*05DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVZXDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F3, { 0 } },
    /*05DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVZXWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F5, { 0 } },
    /*05E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMOVZXWQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F7, { 0 } },
    /*05E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULDQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04F9, { 0 } },
    /*05E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04FA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULHRSW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04FB, { 0 } },
    /*05E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04FC, { 0 } },
    /*05E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04FD, { 0 } },
    /*05E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04FE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULHRW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05E9*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x002C, { 0 } },
    /*05EA*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x002D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULHUW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x04FF, { 0 } },
    /*05EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0500, { 0 } },
    /*05ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0501, { 0 } },
    /*05EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0502, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULHW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0503, { 0 } },
    /*05F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0504, { 0 } },
    /*05F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0505, { 0 } },
    /*05F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0506, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULLD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0507, { 0 } },
    /*05F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0508, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULLW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0509, { 0 } },
    /*05F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x050A, { 0 } },
    /*05F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x050B, { 0 } },
    /*05F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x050C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PMULUDQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x050D, { 0 } },
    /*05FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x050E, { 0 } },
    /*05FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x050F, { 0 } },
    /*05FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0510, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POP                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*05FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0511, { 0 } },
    /*05FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0512, { 0 } },
    /*05FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0513, { 0 } },
    /*0600*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0514, { 0 } },
    /*0601*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0515, { 0 } },
    /*0602*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0516, { 0 } },
    /*0603*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0517, { 0 } },
    /*0604*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0518, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POPA                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0605*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0519, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POPAD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0606*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x051A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POPCNT                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0607*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x051B, { 0 } },
    /*0608*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x051C, { 0 } },
    /*0609*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0097, { 0 } },
    /*060A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0098, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POPF                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*060B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x051D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POPFD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*060C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x051E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POPFQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*060D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x051F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* POR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*060E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0520, { 0 } },
    /*060F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0521, { 0 } },
    /*0610*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0522, { 0 } },
    /*0611*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0523, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCH_EXCLUSIVE                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0612*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0524, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCH_RESERVED                                                                          */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0613*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0525, { 0 } },
    /*0614*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0526, { 0 } },
    /*0615*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0527, { 0 } },
    /*0616*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0528, { 0 } },
    /*0617*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0529, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCHNTA                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0618*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x052A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCHT0                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0619*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x052B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCHT1                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*061A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x052C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCHT2                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*061B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x052D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCHW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*061C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x052E, { 0 } },
    /*061D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x052F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PREFETCHWT1                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*061E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0530, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSADBW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*061F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0531, { 0 } },
    /*0620*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0532, { 0 } },
    /*0621*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0533, { 0 } },
    /*0622*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0534, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSHUFB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0623*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0535, { 0 } },
    /*0624*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0536, { 0 } },
    /*0625*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0537, { 0 } },
    /*0626*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0538, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSHUFD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0627*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0539, { 0 } },
    /*0628*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x053A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSHUFHW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0629*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x053B, { 0 } },
    /*062A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x053C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSHUFLW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*062B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x053D, { 0 } },
    /*062C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x053E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSHUFW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*062D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x053F, { 0 } },
    /*062E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0540, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSIGNB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*062F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0541, { 0 } },
    /*0630*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0542, { 0 } },
    /*0631*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0543, { 0 } },
    /*0632*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0544, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSIGND                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0633*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0545, { 0 } },
    /*0634*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0546, { 0 } },
    /*0635*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0547, { 0 } },
    /*0636*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0548, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSIGNW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0637*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0549, { 0 } },
    /*0638*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x054A, { 0 } },
    /*0639*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x054B, { 0 } },
    /*063A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x054C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSLLD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*063B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x054D, { 0 } },
    /*063C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x054E, { 0 } },
    /*063D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x054F, { 0 } },
    /*063E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0550, { 0 } },
    /*063F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0551, { 0 } },
    /*0640*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0552, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSLLDQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0641*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0553, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSLLQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0642*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0554, { 0 } },
    /*0643*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0555, { 0 } },
    /*0644*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0556, { 0 } },
    /*0645*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0557, { 0 } },
    /*0646*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0558, { 0 } },
    /*0647*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0559, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSLLW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0648*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x055A, { 0 } },
    /*0649*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x055B, { 0 } },
    /*064A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x055C, { 0 } },
    /*064B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x055D, { 0 } },
    /*064C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x055E, { 0 } },
    /*064D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x055F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSRAD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*064E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0560, { 0 } },
    /*064F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0561, { 0 } },
    /*0650*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0562, { 0 } },
    /*0651*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0563, { 0 } },
    /*0652*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0564, { 0 } },
    /*0653*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0565, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSRAW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0654*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0566, { 0 } },
    /*0655*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0567, { 0 } },
    /*0656*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0568, { 0 } },
    /*0657*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0569, { 0 } },
    /*0658*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x056A, { 0 } },
    /*0659*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x056B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSRLD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*065A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x056C, { 0 } },
    /*065B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x056D, { 0 } },
    /*065C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x056E, { 0 } },
    /*065D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x056F, { 0 } },
    /*065E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0570, { 0 } },
    /*065F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0571, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSRLDQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0660*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0572, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSRLQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0661*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0573, { 0 } },
    /*0662*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0574, { 0 } },
    /*0663*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0575, { 0 } },
    /*0664*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0576, { 0 } },
    /*0665*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0577, { 0 } },
    /*0666*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0578, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSRLW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0667*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0579, { 0 } },
    /*0668*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x057A, { 0 } },
    /*0669*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x057B, { 0 } },
    /*066A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x057C, { 0 } },
    /*066B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x057D, { 0 } },
    /*066C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x057E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*066D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x057F, { 0 } },
    /*066E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0580, { 0 } },
    /*066F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0581, { 0 } },
    /*0670*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0582, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0671*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0583, { 0 } },
    /*0672*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0584, { 0 } },
    /*0673*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0585, { 0 } },
    /*0674*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0586, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0675*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0587, { 0 } },
    /*0676*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0588, { 0 } },
    /*0677*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0589, { 0 } },
    /*0678*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x058A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBSB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0679*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x058B, { 0 } },
    /*067A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x058C, { 0 } },
    /*067B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x058D, { 0 } },
    /*067C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x058E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBSW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*067D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x058F, { 0 } },
    /*067E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0590, { 0 } },
    /*067F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0591, { 0 } },
    /*0680*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0592, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBUSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0681*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0593, { 0 } },
    /*0682*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0594, { 0 } },
    /*0683*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0595, { 0 } },
    /*0684*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0596, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBUSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0685*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0597, { 0 } },
    /*0686*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0598, { 0 } },
    /*0687*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0599, { 0 } },
    /*0688*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x059A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSUBW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0689*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x059B, { 0 } },
    /*068A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x059C, { 0 } },
    /*068B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x059D, { 0 } },
    /*068C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x059E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PSWAPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*068D*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x002E, { 0 } },
    /*068E*/ { ZYDIS_INSTRUCTION_ENCODING_3DNOW  , 0x002F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PTEST                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*068F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x059F, { 0 } },
    /*0690*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PTWRITE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0691*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A1, { 0 } },
    /*0692*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKHBW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0693*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A3, { 0 } },
    /*0694*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A4, { 0 } },
    /*0695*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A5, { 0 } },
    /*0696*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKHDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0697*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A7, { 0 } },
    /*0698*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A8, { 0 } },
    /*0699*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05A9, { 0 } },
    /*069A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05AA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKHQDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*069B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05AB, { 0 } },
    /*069C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05AC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKHWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*069D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05AD, { 0 } },
    /*069E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05AE, { 0 } },
    /*069F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05AF, { 0 } },
    /*06A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKLBW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06A1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B1, { 0 } },
    /*06A2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B2, { 0 } },
    /*06A3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B3, { 0 } },
    /*06A4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKLDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06A5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B5, { 0 } },
    /*06A6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B6, { 0 } },
    /*06A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B7, { 0 } },
    /*06A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKLQDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05B9, { 0 } },
    /*06AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUNPCKLWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05BB, { 0 } },
    /*06AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05BC, { 0 } },
    /*06AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05BD, { 0 } },
    /*06AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05BE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUSH                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05BF, { 0 } },
    /*06B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C0, { 0 } },
    /*06B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C1, { 0 } },
    /*06B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C2, { 0 } },
    /*06B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C3, { 0 } },
    /*06B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C4, { 0 } },
    /*06B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C5, { 0 } },
    /*06B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C6, { 0 } },
    /*06B7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C7, { 0 } },
    /*06B8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C8, { 0 } },
    /*06B9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05C9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUSHA                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06BA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUSHAD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06BB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUSHF                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06BC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUSHFD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05CD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PUSHFQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* PXOR                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05CF, { 0 } },
    /*06C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D0, { 0 } },
    /*06C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D1, { 0 } },
    /*06C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RCL                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D3, { 0 } },
    /*06C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D4, { 0 } },
    /*06C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D5, { 0 } },
    /*06C6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D6, { 0 } },
    /*06C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D7, { 0 } },
    /*06C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D8, { 0 } },
    /*06C9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05D9, { 0 } },
    /*06CA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05DA, { 0 } },
    /*06CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05DB, { 0 } },
    /*06CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05DC, { 0 } },
    /*06CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05DD, { 0 } },
    /*06CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05DE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RCPPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05DF, { 0 } },
    /*06D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RCPSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E1, { 0 } },
    /*06D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RCR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E3, { 0 } },
    /*06D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E4, { 0 } },
    /*06D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E5, { 0 } },
    /*06D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E6, { 0 } },
    /*06D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E7, { 0 } },
    /*06D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E8, { 0 } },
    /*06D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05E9, { 0 } },
    /*06DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05EA, { 0 } },
    /*06DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05EB, { 0 } },
    /*06DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05EC, { 0 } },
    /*06DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05ED, { 0 } },
    /*06DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05EE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDFSBASE                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05EF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDGSBASE                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDMSR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDPKRU                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDPMC                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDRAND                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDSEED                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDSSPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDSSPQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDTSC                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RDTSCP                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RET                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05FA, { 0 } },
    /*06EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05FB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RET_FAR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05FC, { 0 } },
    /*06ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05FD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ROL                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05FE, { 0 } },
    /*06EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x05FF, { 0 } },
    /*06F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0600, { 0 } },
    /*06F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0601, { 0 } },
    /*06F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0602, { 0 } },
    /*06F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0603, { 0 } },
    /*06F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0604, { 0 } },
    /*06F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0605, { 0 } },
    /*06F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0606, { 0 } },
    /*06F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0607, { 0 } },
    /*06F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0608, { 0 } },
    /*06F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0609, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ROR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*06FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x060A, { 0 } },
    /*06FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x060B, { 0 } },
    /*06FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x060C, { 0 } },
    /*06FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x060D, { 0 } },
    /*06FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x060E, { 0 } },
    /*06FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x060F, { 0 } },
    /*0700*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0610, { 0 } },
    /*0701*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0611, { 0 } },
    /*0702*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0612, { 0 } },
    /*0703*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0613, { 0 } },
    /*0704*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0614, { 0 } },
    /*0705*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0615, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RORX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0706*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0099, { 0 } },
    /*0707*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x009A, { 0 } },
    /*0708*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x009B, { 0 } },
    /*0709*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x009C, { 0 } },
    /*070A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x009D, { 0 } },
    /*070B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x009E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ROUNDPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*070C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0616, { 0 } },
    /*070D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0617, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ROUNDPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*070E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0618, { 0 } },
    /*070F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0619, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ROUNDSD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0710*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x061A, { 0 } },
    /*0711*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x061B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* ROUNDSS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0712*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x061C, { 0 } },
    /*0713*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x061D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RSM                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0714*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x061E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RSQRTPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0715*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x061F, { 0 } },
    /*0716*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0620, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RSQRTSS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0717*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0621, { 0 } },
    /*0718*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0622, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* RSTORSSP                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0719*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0623, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SAHF                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*071A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0624, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SALC                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*071B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0625, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SAR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*071C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0626, { 0 } },
    /*071D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0627, { 0 } },
    /*071E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0628, { 0 } },
    /*071F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0629, { 0 } },
    /*0720*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x062A, { 0 } },
    /*0721*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x062B, { 0 } },
    /*0722*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x062C, { 0 } },
    /*0723*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x062D, { 0 } },
    /*0724*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x062E, { 0 } },
    /*0725*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x062F, { 0 } },
    /*0726*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0630, { 0 } },
    /*0727*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0631, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SARX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0728*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x009F, { 0 } },
    /*0729*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A0, { 0 } },
    /*072A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A1, { 0 } },
    /*072B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A2, { 0 } },
    /*072C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A3, { 0 } },
    /*072D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SAVESSP                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*072E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0632, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SBB                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*072F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0633, { 0 } },
    /*0730*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0634, { 0 } },
    /*0731*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0635, { 0 } },
    /*0732*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0636, { 0 } },
    /*0733*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0637, { 0 } },
    /*0734*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0638, { 0 } },
    /*0735*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0639, { 0 } },
    /*0736*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x063A, { 0 } },
    /*0737*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x063B, { 0 } },
    /*0738*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x063C, { 0 } },
    /*0739*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x063D, { 0 } },
    /*073A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x063E, { 0 } },
    /*073B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x063F, { 0 } },
    /*073C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0640, { 0 } },
    /*073D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0641, { 0 } },
    /*073E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0642, { 0 } },
    /*073F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0643, { 0 } },
    /*0740*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0644, { 0 } },
    /*0741*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0645, { 0 } },
    /*0742*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0646, { 0 } },
    /*0743*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0647, { 0 } },
    /*0744*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0648, { 0 } },
    /*0745*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0649, { 0 } },
    /*0746*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x064A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SCASB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0747*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x064B, { 0 } },
    /*0748*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x064C, { 0 } },
    /*0749*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x064D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SCASD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*074A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x064E, { 0 } },
    /*074B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x064F, { 0 } },
    /*074C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0650, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SCASQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*074D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0651, { 0 } },
    /*074E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0652, { 0 } },
    /*074F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0653, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SCASW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0750*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0654, { 0 } },
    /*0751*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0655, { 0 } },
    /*0752*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0656, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETB                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0753*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0657, { 0 } },
    /*0754*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0658, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETBE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0755*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0659, { 0 } },
    /*0756*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x065A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETL                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0757*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x065B, { 0 } },
    /*0758*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x065C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETLE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0759*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x065D, { 0 } },
    /*075A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x065E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*075B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x065F, { 0 } },
    /*075C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0660, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNBE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*075D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0661, { 0 } },
    /*075E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0662, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNL                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*075F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0663, { 0 } },
    /*0760*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0664, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNLE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0761*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0665, { 0 } },
    /*0762*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0666, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNO                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0763*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0667, { 0 } },
    /*0764*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0668, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNP                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0765*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0669, { 0 } },
    /*0766*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x066A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0767*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x066B, { 0 } },
    /*0768*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x066C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETNZ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0769*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x066D, { 0 } },
    /*076A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x066E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETO                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*076B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x066F, { 0 } },
    /*076C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0670, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETP                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*076D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0671, { 0 } },
    /*076E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0672, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETS                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*076F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0673, { 0 } },
    /*0770*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0674, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETSSBSY                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0771*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0675, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SETZ                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0772*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0676, { 0 } },
    /*0773*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0677, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SFENCE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0774*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0678, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SGDT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0775*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0679, { 0 } },
    /*0776*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x067A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA1MSG1                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0777*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x067B, { 0 } },
    /*0778*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x067C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA1MSG2                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0779*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x067D, { 0 } },
    /*077A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x067E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA1NEXTE                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*077B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x067F, { 0 } },
    /*077C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0680, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA1RNDS4                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*077D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0681, { 0 } },
    /*077E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0682, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA256MSG1                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*077F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0683, { 0 } },
    /*0780*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0684, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA256MSG2                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0781*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0685, { 0 } },
    /*0782*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0686, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHA256RNDS2                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0783*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0687, { 0 } },
    /*0784*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0688, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHL                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0785*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0689, { 0 } },
    /*0786*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x068A, { 0 } },
    /*0787*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x068B, { 0 } },
    /*0788*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x068C, { 0 } },
    /*0789*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x068D, { 0 } },
    /*078A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x068E, { 0 } },
    /*078B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x068F, { 0 } },
    /*078C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0690, { 0 } },
    /*078D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0691, { 0 } },
    /*078E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0692, { 0 } },
    /*078F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0693, { 0 } },
    /*0790*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0694, { 0 } },
    /*0791*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0695, { 0 } },
    /*0792*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0696, { 0 } },
    /*0793*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0697, { 0 } },
    /*0794*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0698, { 0 } },
    /*0795*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0699, { 0 } },
    /*0796*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x069A, { 0 } },
    /*0797*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x069B, { 0 } },
    /*0798*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x069C, { 0 } },
    /*0799*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x069D, { 0 } },
    /*079A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x069E, { 0 } },
    /*079B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x069F, { 0 } },
    /*079C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHLD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*079D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A1, { 0 } },
    /*079E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A2, { 0 } },
    /*079F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A3, { 0 } },
    /*07A0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHLX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07A1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A5, { 0 } },
    /*07A2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A6, { 0 } },
    /*07A3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A7, { 0 } },
    /*07A4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A8, { 0 } },
    /*07A5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00A9, { 0 } },
    /*07A6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00AA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07A7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A5, { 0 } },
    /*07A8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A6, { 0 } },
    /*07A9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A7, { 0 } },
    /*07AA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A8, { 0 } },
    /*07AB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06A9, { 0 } },
    /*07AC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06AA, { 0 } },
    /*07AD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06AB, { 0 } },
    /*07AE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06AC, { 0 } },
    /*07AF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06AD, { 0 } },
    /*07B0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06AE, { 0 } },
    /*07B1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06AF, { 0 } },
    /*07B2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHRD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07B3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B1, { 0 } },
    /*07B4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B2, { 0 } },
    /*07B5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B3, { 0 } },
    /*07B6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHRX                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07B7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00AB, { 0 } },
    /*07B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00AC, { 0 } },
    /*07B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00AD, { 0 } },
    /*07BA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00AE, { 0 } },
    /*07BB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00AF, { 0 } },
    /*07BC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHUFPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07BD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B5, { 0 } },
    /*07BE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SHUFPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07BF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B7, { 0 } },
    /*07C0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SIDT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07C1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06B9, { 0 } },
    /*07C2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SKINIT                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07C3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06BB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SLDT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07C4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06BC, { 0 } },
    /*07C5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06BD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SLWPCB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07C6*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0025, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SMSW                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07C7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06BE, { 0 } },
    /*07C8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06BF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SPFLT                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07C9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B1, { 0 } },
    /*07CA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SQRTPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07CB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C0, { 0 } },
    /*07CC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SQRTPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07CD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C2, { 0 } },
    /*07CE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SQRTSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07CF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C4, { 0 } },
    /*07D0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SQRTSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C6, { 0 } },
    /*07D2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STAC                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STC                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06C9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STD                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STGI                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STI                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STMXCSR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06CD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STOSB                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07D9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06CE, { 0 } },
    /*07DA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06CF, { 0 } },
    /*07DB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STOSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07DC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D1, { 0 } },
    /*07DD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D2, { 0 } },
    /*07DE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STOSQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07DF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D4, { 0 } },
    /*07E0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D5, { 0 } },
    /*07E1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STOSW                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07E2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D7, { 0 } },
    /*07E3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D8, { 0 } },
    /*07E4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* STR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07E5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06DA, { 0 } },
    /*07E6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06DB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SUB                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07E7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06DC, { 0 } },
    /*07E8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06DD, { 0 } },
    /*07E9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06DE, { 0 } },
    /*07EA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06DF, { 0 } },
    /*07EB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E0, { 0 } },
    /*07EC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E1, { 0 } },
    /*07ED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E2, { 0 } },
    /*07EE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E3, { 0 } },
    /*07EF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E4, { 0 } },
    /*07F0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E5, { 0 } },
    /*07F1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E6, { 0 } },
    /*07F2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E7, { 0 } },
    /*07F3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E8, { 0 } },
    /*07F4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06E9, { 0 } },
    /*07F5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06EA, { 0 } },
    /*07F6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06EB, { 0 } },
    /*07F7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06EC, { 0 } },
    /*07F8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06ED, { 0 } },
    /*07F9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06EE, { 0 } },
    /*07FA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06EF, { 0 } },
    /*07FB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F0, { 0 } },
    /*07FC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F1, { 0 } },
    /*07FD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F2, { 0 } },
    /*07FE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SUBPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*07FF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F4, { 0 } },
    /*0800*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SUBPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0801*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F6, { 0 } },
    /*0802*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SUBSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0803*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F8, { 0 } },
    /*0804*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SUBSS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0805*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06FA, { 0 } },
    /*0806*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06FB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SWAPGS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0807*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06FC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SYSCALL                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0808*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06FD, { 0 } },
    /*0809*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06FE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SYSENTER                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*080A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x06FF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SYSEXIT                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*080B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0700, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* SYSRET                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*080C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0701, { 0 } },
    /*080D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0702, { 0 } },
    /*080E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0703, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* T1MSKC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*080F*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0026, { 0 } },
    /*0810*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0027, { 0 } },
    /*0811*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0028, { 0 } },
    /*0812*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0029, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* TEST                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0813*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0704, { 0 } },
    /*0814*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0705, { 0 } },
    /*0815*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0706, { 0 } },
    /*0816*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0707, { 0 } },
    /*0817*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0708, { 0 } },
    /*0818*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0709, { 0 } },
    /*0819*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x070A, { 0 } },
    /*081A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x070B, { 0 } },
    /*081B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x070C, { 0 } },
    /*081C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x070D, { 0 } },
    /*081D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x070E, { 0 } },
    /*081E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x070F, { 0 } },
    /*081F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0710, { 0 } },
    /*0820*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0711, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* TZCNT                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0821*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0712, { 0 } },
    /*0822*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0713, { 0 } },
    /*0823*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B3, { 0 } },
    /*0824*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* TZCNTI                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0825*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B5, { 0 } },
    /*0826*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* TZMSK                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0827*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x002A, { 0 } },
    /*0828*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x002B, { 0 } },
    /*0829*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x002C, { 0 } },
    /*082A*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x002D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UCOMISD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*082B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0714, { 0 } },
    /*082C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0715, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UCOMISS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*082D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0716, { 0 } },
    /*082E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0717, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UD2                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*082F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0718, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UNPCKHPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0830*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0719, { 0 } },
    /*0831*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x071A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UNPCKHPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0832*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x071B, { 0 } },
    /*0833*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x071C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UNPCKLPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0834*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x071D, { 0 } },
    /*0835*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x071E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* UNPCKLPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0836*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x071F, { 0 } },
    /*0837*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0720, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* V4FMADDPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0838*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0000, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* V4FMADDSS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0839*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0001, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* V4FNMADDPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*083A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0002, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* V4FNMADDSS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*083B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0003, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDNPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*083C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0002, { 0 } },
    /*083D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0003, { 0 } },
    /*083E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0004, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDNPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*083F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0005, { 0 } },
    /*0840*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0006, { 0 } },
    /*0841*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0007, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0842*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B7, { 0 } },
    /*0843*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B8, { 0 } },
    /*0844*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00B9, { 0 } },
    /*0845*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00BA, { 0 } },
    /*0846*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0004, { 0 } },
    /*0847*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0005, { 0 } },
    /*0848*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0006, { 0 } },
    /*0849*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0007, { 0 } },
    /*084A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0008, { 0 } },
    /*084B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0009, { 0 } },
    /*084C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x000A, { 0 } },
    /*084D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0008, { 0 } },
    /*084E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0009, { 0 } },
    /*084F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x000A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0850*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00BB, { 0 } },
    /*0851*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00BC, { 0 } },
    /*0852*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00BD, { 0 } },
    /*0853*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00BE, { 0 } },
    /*0854*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x000B, { 0 } },
    /*0855*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x000C, { 0 } },
    /*0856*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x000D, { 0 } },
    /*0857*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x000E, { 0 } },
    /*0858*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x000F, { 0 } },
    /*0859*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0010, { 0 } },
    /*085A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0011, { 0 } },
    /*085B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x000B, { 0 } },
    /*085C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x000C, { 0 } },
    /*085D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x000D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*085E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00BF, { 0 } },
    /*085F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C0, { 0 } },
    /*0860*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0012, { 0 } },
    /*0861*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0013, { 0 } },
    /*0862*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0014, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDSETSPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0863*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x000E, { 0 } },
    /*0864*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x000F, { 0 } },
    /*0865*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0010, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0866*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C1, { 0 } },
    /*0867*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C2, { 0 } },
    /*0868*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0015, { 0 } },
    /*0869*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0016, { 0 } },
    /*086A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0017, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDSUBPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*086B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C3, { 0 } },
    /*086C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C4, { 0 } },
    /*086D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C5, { 0 } },
    /*086E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VADDSUBPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*086F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C7, { 0 } },
    /*0870*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C8, { 0 } },
    /*0871*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00C9, { 0 } },
    /*0872*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VAESDEC                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0873*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00CB, { 0 } },
    /*0874*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VAESDECLAST                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0875*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00CD, { 0 } },
    /*0876*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VAESENC                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0877*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00CF, { 0 } },
    /*0878*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VAESENCLAST                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0879*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D1, { 0 } },
    /*087A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VAESIMC                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*087B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D3, { 0 } },
    /*087C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VAESKEYGENASSIST                                                                           */ 
    /* ------------------------------------------------------------------------------------------ */
    /*087D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D5, { 0 } },
    /*087E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VALIGND                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*087F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0018, { 0 } },
    /*0880*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0019, { 0 } },
    /*0881*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x001A, { 0 } },
    /*0882*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x001B, { 0 } },
    /*0883*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x001C, { 0 } },
    /*0884*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x001D, { 0 } },
    /*0885*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0011, { 0 } },
    /*0886*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0012, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VALIGNQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0887*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x001E, { 0 } },
    /*0888*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x001F, { 0 } },
    /*0889*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0020, { 0 } },
    /*088A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0021, { 0 } },
    /*088B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0022, { 0 } },
    /*088C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0023, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VANDNPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*088D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D7, { 0 } },
    /*088E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D8, { 0 } },
    /*088F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00D9, { 0 } },
    /*0890*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00DA, { 0 } },
    /*0891*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0024, { 0 } },
    /*0892*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0025, { 0 } },
    /*0893*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0026, { 0 } },
    /*0894*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0027, { 0 } },
    /*0895*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0028, { 0 } },
    /*0896*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0029, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VANDNPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0897*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00DB, { 0 } },
    /*0898*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00DC, { 0 } },
    /*0899*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00DD, { 0 } },
    /*089A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00DE, { 0 } },
    /*089B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x002A, { 0 } },
    /*089C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x002B, { 0 } },
    /*089D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x002C, { 0 } },
    /*089E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x002D, { 0 } },
    /*089F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x002E, { 0 } },
    /*08A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x002F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VANDPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08A1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00DF, { 0 } },
    /*08A2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E0, { 0 } },
    /*08A3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E1, { 0 } },
    /*08A4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E2, { 0 } },
    /*08A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0030, { 0 } },
    /*08A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0031, { 0 } },
    /*08A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0032, { 0 } },
    /*08A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0033, { 0 } },
    /*08A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0034, { 0 } },
    /*08AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0035, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VANDPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08AB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E3, { 0 } },
    /*08AC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E4, { 0 } },
    /*08AD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E5, { 0 } },
    /*08AE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E6, { 0 } },
    /*08AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0036, { 0 } },
    /*08B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0037, { 0 } },
    /*08B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0038, { 0 } },
    /*08B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0039, { 0 } },
    /*08B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x003A, { 0 } },
    /*08B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x003B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBLENDMPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x003C, { 0 } },
    /*08B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x003D, { 0 } },
    /*08B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x003E, { 0 } },
    /*08B8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x003F, { 0 } },
    /*08B9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0040, { 0 } },
    /*08BA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0041, { 0 } },
    /*08BB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0013, { 0 } },
    /*08BC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0014, { 0 } },
    /*08BD*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0015, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBLENDMPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08BE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0042, { 0 } },
    /*08BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0043, { 0 } },
    /*08C0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0044, { 0 } },
    /*08C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0045, { 0 } },
    /*08C2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0046, { 0 } },
    /*08C3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0047, { 0 } },
    /*08C4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0016, { 0 } },
    /*08C5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0017, { 0 } },
    /*08C6*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0018, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBLENDPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08C7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E7, { 0 } },
    /*08C8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E8, { 0 } },
    /*08C9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00E9, { 0 } },
    /*08CA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00EA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBLENDPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08CB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00EB, { 0 } },
    /*08CC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00EC, { 0 } },
    /*08CD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00ED, { 0 } },
    /*08CE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00EE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBLENDVPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08CF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00EF, { 0 } },
    /*08D0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F0, { 0 } },
    /*08D1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F1, { 0 } },
    /*08D2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBLENDVPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08D3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F3, { 0 } },
    /*08D4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F4, { 0 } },
    /*08D5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F5, { 0 } },
    /*08D6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTF128                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08D7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTF32X2                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0048, { 0 } },
    /*08D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0049, { 0 } },
    /*08DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x004A, { 0 } },
    /*08DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x004B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTF32X4                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08DC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x004C, { 0 } },
    /*08DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x004D, { 0 } },
    /*08DE*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0019, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTF32X8                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x004E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTF64X2                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x004F, { 0 } },
    /*08E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0050, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTF64X4                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0051, { 0 } },
    /*08E3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x001A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTI128                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08E4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTI32X2                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0052, { 0 } },
    /*08E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0053, { 0 } },
    /*08E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0054, { 0 } },
    /*08E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0055, { 0 } },
    /*08E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0056, { 0 } },
    /*08EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0057, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTI32X4                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0058, { 0 } },
    /*08EC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0059, { 0 } },
    /*08ED*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x001B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTI32X8                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08EE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x005A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTI64X2                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x005B, { 0 } },
    /*08F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x005C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTI64X4                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x005D, { 0 } },
    /*08F2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x001C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTSD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08F3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00F9, { 0 } },
    /*08F4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00FA, { 0 } },
    /*08F5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x005E, { 0 } },
    /*08F6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x005F, { 0 } },
    /*08F7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0060, { 0 } },
    /*08F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0061, { 0 } },
    /*08F9*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x001D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VBROADCASTSS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*08FA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00FB, { 0 } },
    /*08FB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00FC, { 0 } },
    /*08FC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00FD, { 0 } },
    /*08FD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00FE, { 0 } },
    /*08FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0062, { 0 } },
    /*08FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0063, { 0 } },
    /*0900*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0064, { 0 } },
    /*0901*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0065, { 0 } },
    /*0902*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0066, { 0 } },
    /*0903*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0067, { 0 } },
    /*0904*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x001E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCMPPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0905*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x00FF, { 0 } },
    /*0906*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0100, { 0 } },
    /*0907*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0101, { 0 } },
    /*0908*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0102, { 0 } },
    /*0909*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0068, { 0 } },
    /*090A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0069, { 0 } },
    /*090B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x006A, { 0 } },
    /*090C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x006B, { 0 } },
    /*090D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x006C, { 0 } },
    /*090E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x006D, { 0 } },
    /*090F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x006E, { 0 } },
    /*0910*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x001F, { 0 } },
    /*0911*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0020, { 0 } },
    /*0912*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0021, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCMPPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0913*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0103, { 0 } },
    /*0914*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0104, { 0 } },
    /*0915*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0105, { 0 } },
    /*0916*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0106, { 0 } },
    /*0917*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x006F, { 0 } },
    /*0918*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0070, { 0 } },
    /*0919*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0071, { 0 } },
    /*091A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0072, { 0 } },
    /*091B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0073, { 0 } },
    /*091C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0074, { 0 } },
    /*091D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0075, { 0 } },
    /*091E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0022, { 0 } },
    /*091F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0023, { 0 } },
    /*0920*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0024, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCMPSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0921*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0107, { 0 } },
    /*0922*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0108, { 0 } },
    /*0923*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0076, { 0 } },
    /*0924*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0077, { 0 } },
    /*0925*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0078, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCMPSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0926*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0109, { 0 } },
    /*0927*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x010A, { 0 } },
    /*0928*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0079, { 0 } },
    /*0929*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x007A, { 0 } },
    /*092A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x007B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCOMISD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*092B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x010B, { 0 } },
    /*092C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x010C, { 0 } },
    /*092D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x007C, { 0 } },
    /*092E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x007D, { 0 } },
    /*092F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x007E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCOMISS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0930*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x010D, { 0 } },
    /*0931*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x010E, { 0 } },
    /*0932*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x007F, { 0 } },
    /*0933*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0080, { 0 } },
    /*0934*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0081, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCOMPRESSPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0935*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0082, { 0 } },
    /*0936*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0083, { 0 } },
    /*0937*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0084, { 0 } },
    /*0938*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0085, { 0 } },
    /*0939*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0086, { 0 } },
    /*093A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0087, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCOMPRESSPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*093B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0088, { 0 } },
    /*093C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0089, { 0 } },
    /*093D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x008A, { 0 } },
    /*093E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x008B, { 0 } },
    /*093F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x008C, { 0 } },
    /*0940*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x008D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTDQ2PD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0941*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x010F, { 0 } },
    /*0942*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0110, { 0 } },
    /*0943*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0111, { 0 } },
    /*0944*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0112, { 0 } },
    /*0945*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x008E, { 0 } },
    /*0946*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x008F, { 0 } },
    /*0947*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0090, { 0 } },
    /*0948*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0091, { 0 } },
    /*0949*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0092, { 0 } },
    /*094A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0093, { 0 } },
    /*094B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0025, { 0 } },
    /*094C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0026, { 0 } },
    /*094D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0027, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTDQ2PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*094E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0113, { 0 } },
    /*094F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0114, { 0 } },
    /*0950*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0115, { 0 } },
    /*0951*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0116, { 0 } },
    /*0952*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0094, { 0 } },
    /*0953*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0095, { 0 } },
    /*0954*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0096, { 0 } },
    /*0955*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0097, { 0 } },
    /*0956*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0098, { 0 } },
    /*0957*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0099, { 0 } },
    /*0958*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x009A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTFXPNTDQ2PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0959*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0028, { 0 } },
    /*095A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0029, { 0 } },
    /*095B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x002A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTFXPNTPD2DQ                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*095C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x002B, { 0 } },
    /*095D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x002C, { 0 } },
    /*095E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x002D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTFXPNTPD2UDQ                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*095F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x002E, { 0 } },
    /*0960*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x002F, { 0 } },
    /*0961*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0030, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTFXPNTPS2DQ                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0962*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0031, { 0 } },
    /*0963*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0032, { 0 } },
    /*0964*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0033, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTFXPNTPS2UDQ                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0965*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0034, { 0 } },
    /*0966*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0035, { 0 } },
    /*0967*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0036, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTFXPNTUDQ2PS                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0968*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0037, { 0 } },
    /*0969*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0038, { 0 } },
    /*096A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0039, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPD2DQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*096B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0117, { 0 } },
    /*096C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0118, { 0 } },
    /*096D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0119, { 0 } },
    /*096E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x011A, { 0 } },
    /*096F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x009B, { 0 } },
    /*0970*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x009C, { 0 } },
    /*0971*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x009D, { 0 } },
    /*0972*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x009E, { 0 } },
    /*0973*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x009F, { 0 } },
    /*0974*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A0, { 0 } },
    /*0975*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPD2PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0976*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x011B, { 0 } },
    /*0977*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x011C, { 0 } },
    /*0978*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x011D, { 0 } },
    /*0979*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x011E, { 0 } },
    /*097A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A2, { 0 } },
    /*097B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A3, { 0 } },
    /*097C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A4, { 0 } },
    /*097D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A5, { 0 } },
    /*097E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A6, { 0 } },
    /*097F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A7, { 0 } },
    /*0980*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A8, { 0 } },
    /*0981*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x003A, { 0 } },
    /*0982*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x003B, { 0 } },
    /*0983*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x003C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPD2QQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0984*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00A9, { 0 } },
    /*0985*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00AA, { 0 } },
    /*0986*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00AB, { 0 } },
    /*0987*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00AC, { 0 } },
    /*0988*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00AD, { 0 } },
    /*0989*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00AE, { 0 } },
    /*098A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00AF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPD2UDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*098B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B0, { 0 } },
    /*098C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B1, { 0 } },
    /*098D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B2, { 0 } },
    /*098E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B3, { 0 } },
    /*098F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B4, { 0 } },
    /*0990*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B5, { 0 } },
    /*0991*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPD2UQQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0992*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B7, { 0 } },
    /*0993*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B8, { 0 } },
    /*0994*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00B9, { 0 } },
    /*0995*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00BA, { 0 } },
    /*0996*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00BB, { 0 } },
    /*0997*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00BC, { 0 } },
    /*0998*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00BD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPH2PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0999*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x011F, { 0 } },
    /*099A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0120, { 0 } },
    /*099B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0121, { 0 } },
    /*099C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0122, { 0 } },
    /*099D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00BE, { 0 } },
    /*099E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00BF, { 0 } },
    /*099F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C0, { 0 } },
    /*09A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C1, { 0 } },
    /*09A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C2, { 0 } },
    /*09A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C3, { 0 } },
    /*09A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPS2DQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09A4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0123, { 0 } },
    /*09A5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0124, { 0 } },
    /*09A6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0125, { 0 } },
    /*09A7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0126, { 0 } },
    /*09A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C5, { 0 } },
    /*09A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C6, { 0 } },
    /*09AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C7, { 0 } },
    /*09AB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C8, { 0 } },
    /*09AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00C9, { 0 } },
    /*09AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00CA, { 0 } },
    /*09AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPS2PD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09AF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0127, { 0 } },
    /*09B0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0128, { 0 } },
    /*09B1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0129, { 0 } },
    /*09B2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x012A, { 0 } },
    /*09B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00CC, { 0 } },
    /*09B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00CD, { 0 } },
    /*09B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00CE, { 0 } },
    /*09B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00CF, { 0 } },
    /*09B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D0, { 0 } },
    /*09B8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D1, { 0 } },
    /*09B9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D2, { 0 } },
    /*09BA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x003D, { 0 } },
    /*09BB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x003E, { 0 } },
    /*09BC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x003F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPS2PH                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09BD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x012B, { 0 } },
    /*09BE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x012C, { 0 } },
    /*09BF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x012D, { 0 } },
    /*09C0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x012E, { 0 } },
    /*09C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D3, { 0 } },
    /*09C2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D4, { 0 } },
    /*09C3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D5, { 0 } },
    /*09C4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D6, { 0 } },
    /*09C5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D7, { 0 } },
    /*09C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D8, { 0 } },
    /*09C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPS2QQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00DA, { 0 } },
    /*09C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00DB, { 0 } },
    /*09CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00DC, { 0 } },
    /*09CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00DD, { 0 } },
    /*09CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00DE, { 0 } },
    /*09CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00DF, { 0 } },
    /*09CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPS2UDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09CF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E1, { 0 } },
    /*09D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E2, { 0 } },
    /*09D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E3, { 0 } },
    /*09D2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E4, { 0 } },
    /*09D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E5, { 0 } },
    /*09D4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E6, { 0 } },
    /*09D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTPS2UQQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E8, { 0 } },
    /*09D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00E9, { 0 } },
    /*09D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00EA, { 0 } },
    /*09D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00EB, { 0 } },
    /*09DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00EC, { 0 } },
    /*09DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00ED, { 0 } },
    /*09DC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00EE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTQQ2PD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00EF, { 0 } },
    /*09DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F0, { 0 } },
    /*09DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F1, { 0 } },
    /*09E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F2, { 0 } },
    /*09E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F3, { 0 } },
    /*09E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F4, { 0 } },
    /*09E3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTQQ2PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09E4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F6, { 0 } },
    /*09E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F7, { 0 } },
    /*09E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F8, { 0 } },
    /*09E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00F9, { 0 } },
    /*09E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00FA, { 0 } },
    /*09E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00FB, { 0 } },
    /*09EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00FC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSD2SI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09EB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x012F, { 0 } },
    /*09EC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0130, { 0 } },
    /*09ED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0131, { 0 } },
    /*09EE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0132, { 0 } },
    /*09EF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0133, { 0 } },
    /*09F0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0134, { 0 } },
    /*09F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00FD, { 0 } },
    /*09F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00FE, { 0 } },
    /*09F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x00FF, { 0 } },
    /*09F4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0100, { 0 } },
    /*09F5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0101, { 0 } },
    /*09F6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0102, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSD2SS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09F7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0135, { 0 } },
    /*09F8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0136, { 0 } },
    /*09F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0103, { 0 } },
    /*09FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0104, { 0 } },
    /*09FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0105, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSD2USI                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*09FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0106, { 0 } },
    /*09FD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0107, { 0 } },
    /*09FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0108, { 0 } },
    /*09FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0109, { 0 } },
    /*0A00*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x010A, { 0 } },
    /*0A01*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x010B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSI2SD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A02*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0137, { 0 } },
    /*0A03*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0138, { 0 } },
    /*0A04*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0139, { 0 } },
    /*0A05*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x013A, { 0 } },
    /*0A06*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x013B, { 0 } },
    /*0A07*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x013C, { 0 } },
    /*0A08*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x010C, { 0 } },
    /*0A09*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x010D, { 0 } },
    /*0A0A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x010E, { 0 } },
    /*0A0B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x010F, { 0 } },
    /*0A0C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0110, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSI2SS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A0D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x013D, { 0 } },
    /*0A0E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x013E, { 0 } },
    /*0A0F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x013F, { 0 } },
    /*0A10*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0140, { 0 } },
    /*0A11*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0141, { 0 } },
    /*0A12*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0142, { 0 } },
    /*0A13*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0111, { 0 } },
    /*0A14*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0112, { 0 } },
    /*0A15*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0113, { 0 } },
    /*0A16*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0114, { 0 } },
    /*0A17*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0115, { 0 } },
    /*0A18*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0116, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSS2SD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A19*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0143, { 0 } },
    /*0A1A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0144, { 0 } },
    /*0A1B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0117, { 0 } },
    /*0A1C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0118, { 0 } },
    /*0A1D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0119, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSS2SI                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A1E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0145, { 0 } },
    /*0A1F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0146, { 0 } },
    /*0A20*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0147, { 0 } },
    /*0A21*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0148, { 0 } },
    /*0A22*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0149, { 0 } },
    /*0A23*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x014A, { 0 } },
    /*0A24*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x011A, { 0 } },
    /*0A25*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x011B, { 0 } },
    /*0A26*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x011C, { 0 } },
    /*0A27*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x011D, { 0 } },
    /*0A28*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x011E, { 0 } },
    /*0A29*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x011F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTSS2USI                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A2A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0120, { 0 } },
    /*0A2B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0121, { 0 } },
    /*0A2C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0122, { 0 } },
    /*0A2D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0123, { 0 } },
    /*0A2E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0124, { 0 } },
    /*0A2F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0125, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPD2DQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A30*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x014B, { 0 } },
    /*0A31*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x014C, { 0 } },
    /*0A32*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x014D, { 0 } },
    /*0A33*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x014E, { 0 } },
    /*0A34*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0126, { 0 } },
    /*0A35*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0127, { 0 } },
    /*0A36*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0128, { 0 } },
    /*0A37*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0129, { 0 } },
    /*0A38*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x012A, { 0 } },
    /*0A39*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x012B, { 0 } },
    /*0A3A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x012C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPD2QQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A3B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x012D, { 0 } },
    /*0A3C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x012E, { 0 } },
    /*0A3D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x012F, { 0 } },
    /*0A3E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0130, { 0 } },
    /*0A3F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0131, { 0 } },
    /*0A40*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0132, { 0 } },
    /*0A41*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0133, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPD2UDQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A42*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0134, { 0 } },
    /*0A43*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0135, { 0 } },
    /*0A44*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0136, { 0 } },
    /*0A45*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0137, { 0 } },
    /*0A46*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0138, { 0 } },
    /*0A47*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0139, { 0 } },
    /*0A48*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x013A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPD2UQQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A49*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x013B, { 0 } },
    /*0A4A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x013C, { 0 } },
    /*0A4B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x013D, { 0 } },
    /*0A4C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x013E, { 0 } },
    /*0A4D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x013F, { 0 } },
    /*0A4E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0140, { 0 } },
    /*0A4F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0141, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPS2DQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A50*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x014F, { 0 } },
    /*0A51*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0150, { 0 } },
    /*0A52*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0151, { 0 } },
    /*0A53*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0152, { 0 } },
    /*0A54*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0142, { 0 } },
    /*0A55*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0143, { 0 } },
    /*0A56*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0144, { 0 } },
    /*0A57*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0145, { 0 } },
    /*0A58*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0146, { 0 } },
    /*0A59*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0147, { 0 } },
    /*0A5A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0148, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPS2QQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A5B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0149, { 0 } },
    /*0A5C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x014A, { 0 } },
    /*0A5D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x014B, { 0 } },
    /*0A5E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x014C, { 0 } },
    /*0A5F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x014D, { 0 } },
    /*0A60*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x014E, { 0 } },
    /*0A61*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x014F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPS2UDQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A62*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0150, { 0 } },
    /*0A63*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0151, { 0 } },
    /*0A64*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0152, { 0 } },
    /*0A65*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0153, { 0 } },
    /*0A66*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0154, { 0 } },
    /*0A67*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0155, { 0 } },
    /*0A68*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0156, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTPS2UQQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A69*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0157, { 0 } },
    /*0A6A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0158, { 0 } },
    /*0A6B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0159, { 0 } },
    /*0A6C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x015A, { 0 } },
    /*0A6D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x015B, { 0 } },
    /*0A6E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x015C, { 0 } },
    /*0A6F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x015D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTSD2SI                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A70*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0153, { 0 } },
    /*0A71*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0154, { 0 } },
    /*0A72*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0155, { 0 } },
    /*0A73*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0156, { 0 } },
    /*0A74*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0157, { 0 } },
    /*0A75*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0158, { 0 } },
    /*0A76*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x015E, { 0 } },
    /*0A77*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x015F, { 0 } },
    /*0A78*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0160, { 0 } },
    /*0A79*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0161, { 0 } },
    /*0A7A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0162, { 0 } },
    /*0A7B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0163, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTSD2USI                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A7C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0164, { 0 } },
    /*0A7D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0165, { 0 } },
    /*0A7E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0166, { 0 } },
    /*0A7F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0167, { 0 } },
    /*0A80*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0168, { 0 } },
    /*0A81*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0169, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTSS2SI                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A82*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0159, { 0 } },
    /*0A83*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x015A, { 0 } },
    /*0A84*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x015B, { 0 } },
    /*0A85*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x015C, { 0 } },
    /*0A86*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x015D, { 0 } },
    /*0A87*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x015E, { 0 } },
    /*0A88*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x016A, { 0 } },
    /*0A89*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x016B, { 0 } },
    /*0A8A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x016C, { 0 } },
    /*0A8B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x016D, { 0 } },
    /*0A8C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x016E, { 0 } },
    /*0A8D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x016F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTTSS2USI                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A8E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0170, { 0 } },
    /*0A8F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0171, { 0 } },
    /*0A90*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0172, { 0 } },
    /*0A91*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0173, { 0 } },
    /*0A92*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0174, { 0 } },
    /*0A93*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0175, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTUDQ2PD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A94*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0176, { 0 } },
    /*0A95*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0177, { 0 } },
    /*0A96*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0178, { 0 } },
    /*0A97*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0179, { 0 } },
    /*0A98*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x017A, { 0 } },
    /*0A99*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x017B, { 0 } },
    /*0A9A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0040, { 0 } },
    /*0A9B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0041, { 0 } },
    /*0A9C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0042, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTUDQ2PS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0A9D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x017C, { 0 } },
    /*0A9E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x017D, { 0 } },
    /*0A9F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x017E, { 0 } },
    /*0AA0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x017F, { 0 } },
    /*0AA1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0180, { 0 } },
    /*0AA2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0181, { 0 } },
    /*0AA3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0182, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTUQQ2PD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AA4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0183, { 0 } },
    /*0AA5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0184, { 0 } },
    /*0AA6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0185, { 0 } },
    /*0AA7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0186, { 0 } },
    /*0AA8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0187, { 0 } },
    /*0AA9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0188, { 0 } },
    /*0AAA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0189, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTUQQ2PS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AAB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x018A, { 0 } },
    /*0AAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x018B, { 0 } },
    /*0AAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x018C, { 0 } },
    /*0AAE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x018D, { 0 } },
    /*0AAF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x018E, { 0 } },
    /*0AB0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x018F, { 0 } },
    /*0AB1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0190, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTUSI2SD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AB2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0191, { 0 } },
    /*0AB3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0192, { 0 } },
    /*0AB4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0193, { 0 } },
    /*0AB5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0194, { 0 } },
    /*0AB6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0195, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VCVTUSI2SS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AB7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0196, { 0 } },
    /*0AB8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0197, { 0 } },
    /*0AB9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0198, { 0 } },
    /*0ABA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0199, { 0 } },
    /*0ABB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x019A, { 0 } },
    /*0ABC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x019B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDBPSADBW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ABD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x019C, { 0 } },
    /*0ABE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x019D, { 0 } },
    /*0ABF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x019E, { 0 } },
    /*0AC0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x019F, { 0 } },
    /*0AC1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A0, { 0 } },
    /*0AC2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDIVPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AC3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x015F, { 0 } },
    /*0AC4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0160, { 0 } },
    /*0AC5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0161, { 0 } },
    /*0AC6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0162, { 0 } },
    /*0AC7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A2, { 0 } },
    /*0AC8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A3, { 0 } },
    /*0AC9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A4, { 0 } },
    /*0ACA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A5, { 0 } },
    /*0ACB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A6, { 0 } },
    /*0ACC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A7, { 0 } },
    /*0ACD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDIVPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ACE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0163, { 0 } },
    /*0ACF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0164, { 0 } },
    /*0AD0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0165, { 0 } },
    /*0AD1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0166, { 0 } },
    /*0AD2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01A9, { 0 } },
    /*0AD3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01AA, { 0 } },
    /*0AD4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01AB, { 0 } },
    /*0AD5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01AC, { 0 } },
    /*0AD6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01AD, { 0 } },
    /*0AD7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01AE, { 0 } },
    /*0AD8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01AF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDIVSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AD9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0167, { 0 } },
    /*0ADA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0168, { 0 } },
    /*0ADB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B0, { 0 } },
    /*0ADC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B1, { 0 } },
    /*0ADD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDIVSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ADE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0169, { 0 } },
    /*0ADF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x016A, { 0 } },
    /*0AE0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B3, { 0 } },
    /*0AE1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B4, { 0 } },
    /*0AE2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDPPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AE3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x016B, { 0 } },
    /*0AE4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x016C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VDPPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AE5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x016D, { 0 } },
    /*0AE6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x016E, { 0 } },
    /*0AE7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x016F, { 0 } },
    /*0AE8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0170, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VERR                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AE9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0721, { 0 } },
    /*0AEA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0722, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VERW                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AEB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0723, { 0 } },
    /*0AEC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0724, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXP223PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AED*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0043, { 0 } },
    /*0AEE*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0044, { 0 } },
    /*0AEF*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0045, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXP2PD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AF0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B6, { 0 } },
    /*0AF1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B7, { 0 } },
    /*0AF2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXP2PS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AF3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01B9, { 0 } },
    /*0AF4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01BA, { 0 } },
    /*0AF5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01BB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXPANDPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AF6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01BC, { 0 } },
    /*0AF7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01BD, { 0 } },
    /*0AF8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01BE, { 0 } },
    /*0AF9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01BF, { 0 } },
    /*0AFA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C0, { 0 } },
    /*0AFB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXPANDPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0AFC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C2, { 0 } },
    /*0AFD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C3, { 0 } },
    /*0AFE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C4, { 0 } },
    /*0AFF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C5, { 0 } },
    /*0B00*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C6, { 0 } },
    /*0B01*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTF128                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B02*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0171, { 0 } },
    /*0B03*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0172, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTF32X4                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B04*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C8, { 0 } },
    /*0B05*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01C9, { 0 } },
    /*0B06*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01CA, { 0 } },
    /*0B07*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTF32X8                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B08*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01CC, { 0 } },
    /*0B09*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01CD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTF64X2                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B0A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01CE, { 0 } },
    /*0B0B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01CF, { 0 } },
    /*0B0C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D0, { 0 } },
    /*0B0D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTF64X4                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B0E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D2, { 0 } },
    /*0B0F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTI128                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B10*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0173, { 0 } },
    /*0B11*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0174, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTI32X4                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B12*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D4, { 0 } },
    /*0B13*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D5, { 0 } },
    /*0B14*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D6, { 0 } },
    /*0B15*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTI32X8                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B16*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D8, { 0 } },
    /*0B17*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTI64X2                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B18*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01DA, { 0 } },
    /*0B19*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01DB, { 0 } },
    /*0B1A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01DC, { 0 } },
    /*0B1B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTI64X4                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B1C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01DE, { 0 } },
    /*0B1D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01DF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VEXTRACTPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B1E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0175, { 0 } },
    /*0B1F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0176, { 0 } },
    /*0B20*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E0, { 0 } },
    /*0B21*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFIXUPIMMPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B22*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E2, { 0 } },
    /*0B23*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E3, { 0 } },
    /*0B24*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E4, { 0 } },
    /*0B25*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E5, { 0 } },
    /*0B26*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E6, { 0 } },
    /*0B27*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E7, { 0 } },
    /*0B28*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFIXUPIMMPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B29*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01E9, { 0 } },
    /*0B2A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01EA, { 0 } },
    /*0B2B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01EB, { 0 } },
    /*0B2C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01EC, { 0 } },
    /*0B2D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01ED, { 0 } },
    /*0B2E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01EE, { 0 } },
    /*0B2F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01EF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFIXUPIMMSD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B30*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F0, { 0 } },
    /*0B31*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F1, { 0 } },
    /*0B32*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFIXUPIMMSS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B33*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F3, { 0 } },
    /*0B34*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F4, { 0 } },
    /*0B35*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFIXUPNANPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B36*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0046, { 0 } },
    /*0B37*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0047, { 0 } },
    /*0B38*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0048, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFIXUPNANPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B39*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0049, { 0 } },
    /*0B3A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x004A, { 0 } },
    /*0B3B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x004B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD132PD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B3C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0177, { 0 } },
    /*0B3D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0178, { 0 } },
    /*0B3E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0179, { 0 } },
    /*0B3F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x017A, { 0 } },
    /*0B40*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F6, { 0 } },
    /*0B41*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F7, { 0 } },
    /*0B42*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F8, { 0 } },
    /*0B43*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01F9, { 0 } },
    /*0B44*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01FA, { 0 } },
    /*0B45*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01FB, { 0 } },
    /*0B46*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01FC, { 0 } },
    /*0B47*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x004C, { 0 } },
    /*0B48*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x004D, { 0 } },
    /*0B49*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x004E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD132PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B4A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x017B, { 0 } },
    /*0B4B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x017C, { 0 } },
    /*0B4C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x017D, { 0 } },
    /*0B4D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x017E, { 0 } },
    /*0B4E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01FD, { 0 } },
    /*0B4F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01FE, { 0 } },
    /*0B50*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x01FF, { 0 } },
    /*0B51*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0200, { 0 } },
    /*0B52*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0201, { 0 } },
    /*0B53*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0202, { 0 } },
    /*0B54*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0203, { 0 } },
    /*0B55*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x004F, { 0 } },
    /*0B56*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0050, { 0 } },
    /*0B57*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0051, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD132SD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B58*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x017F, { 0 } },
    /*0B59*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0180, { 0 } },
    /*0B5A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0204, { 0 } },
    /*0B5B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0205, { 0 } },
    /*0B5C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0206, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD132SS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B5D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0181, { 0 } },
    /*0B5E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0182, { 0 } },
    /*0B5F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0207, { 0 } },
    /*0B60*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0208, { 0 } },
    /*0B61*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0209, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD213PD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B62*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0183, { 0 } },
    /*0B63*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0184, { 0 } },
    /*0B64*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0185, { 0 } },
    /*0B65*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0186, { 0 } },
    /*0B66*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x020A, { 0 } },
    /*0B67*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x020B, { 0 } },
    /*0B68*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x020C, { 0 } },
    /*0B69*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x020D, { 0 } },
    /*0B6A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x020E, { 0 } },
    /*0B6B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x020F, { 0 } },
    /*0B6C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0210, { 0 } },
    /*0B6D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0052, { 0 } },
    /*0B6E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0053, { 0 } },
    /*0B6F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0054, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD213PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B70*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0187, { 0 } },
    /*0B71*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0188, { 0 } },
    /*0B72*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0189, { 0 } },
    /*0B73*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x018A, { 0 } },
    /*0B74*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0211, { 0 } },
    /*0B75*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0212, { 0 } },
    /*0B76*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0213, { 0 } },
    /*0B77*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0214, { 0 } },
    /*0B78*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0215, { 0 } },
    /*0B79*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0216, { 0 } },
    /*0B7A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0217, { 0 } },
    /*0B7B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0055, { 0 } },
    /*0B7C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0056, { 0 } },
    /*0B7D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0057, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD213SD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B7E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x018B, { 0 } },
    /*0B7F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x018C, { 0 } },
    /*0B80*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0218, { 0 } },
    /*0B81*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0219, { 0 } },
    /*0B82*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x021A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD213SS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B83*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x018D, { 0 } },
    /*0B84*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x018E, { 0 } },
    /*0B85*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x021B, { 0 } },
    /*0B86*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x021C, { 0 } },
    /*0B87*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x021D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD231PD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B88*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x018F, { 0 } },
    /*0B89*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0190, { 0 } },
    /*0B8A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0191, { 0 } },
    /*0B8B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0192, { 0 } },
    /*0B8C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x021E, { 0 } },
    /*0B8D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x021F, { 0 } },
    /*0B8E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0220, { 0 } },
    /*0B8F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0221, { 0 } },
    /*0B90*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0222, { 0 } },
    /*0B91*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0223, { 0 } },
    /*0B92*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0224, { 0 } },
    /*0B93*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0058, { 0 } },
    /*0B94*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0059, { 0 } },
    /*0B95*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x005A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD231PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0B96*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0193, { 0 } },
    /*0B97*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0194, { 0 } },
    /*0B98*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0195, { 0 } },
    /*0B99*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0196, { 0 } },
    /*0B9A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0225, { 0 } },
    /*0B9B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0226, { 0 } },
    /*0B9C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0227, { 0 } },
    /*0B9D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0228, { 0 } },
    /*0B9E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0229, { 0 } },
    /*0B9F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x022A, { 0 } },
    /*0BA0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x022B, { 0 } },
    /*0BA1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x005B, { 0 } },
    /*0BA2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x005C, { 0 } },
    /*0BA3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x005D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD231SD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BA4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0197, { 0 } },
    /*0BA5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0198, { 0 } },
    /*0BA6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x022C, { 0 } },
    /*0BA7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x022D, { 0 } },
    /*0BA8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x022E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD231SS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BA9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0199, { 0 } },
    /*0BAA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x019A, { 0 } },
    /*0BAB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x022F, { 0 } },
    /*0BAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0230, { 0 } },
    /*0BAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0231, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADD233PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BAE*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x005E, { 0 } },
    /*0BAF*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x005F, { 0 } },
    /*0BB0*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0060, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BB1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x019B, { 0 } },
    /*0BB2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x019C, { 0 } },
    /*0BB3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x019D, { 0 } },
    /*0BB4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x019E, { 0 } },
    /*0BB5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x019F, { 0 } },
    /*0BB6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A0, { 0 } },
    /*0BB7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A1, { 0 } },
    /*0BB8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BB9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A3, { 0 } },
    /*0BBA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A4, { 0 } },
    /*0BBB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A5, { 0 } },
    /*0BBC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A6, { 0 } },
    /*0BBD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A7, { 0 } },
    /*0BBE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A8, { 0 } },
    /*0BBF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01A9, { 0 } },
    /*0BC0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01AA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BC1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01AB, { 0 } },
    /*0BC2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01AC, { 0 } },
    /*0BC3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01AD, { 0 } },
    /*0BC4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01AE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BC5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01AF, { 0 } },
    /*0BC6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B0, { 0 } },
    /*0BC7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B1, { 0 } },
    /*0BC8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUB132PD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BC9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B3, { 0 } },
    /*0BCA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B4, { 0 } },
    /*0BCB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B5, { 0 } },
    /*0BCC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B6, { 0 } },
    /*0BCD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0232, { 0 } },
    /*0BCE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0233, { 0 } },
    /*0BCF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0234, { 0 } },
    /*0BD0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0235, { 0 } },
    /*0BD1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0236, { 0 } },
    /*0BD2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0237, { 0 } },
    /*0BD3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0238, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUB132PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BD4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B7, { 0 } },
    /*0BD5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B8, { 0 } },
    /*0BD6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01B9, { 0 } },
    /*0BD7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01BA, { 0 } },
    /*0BD8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0239, { 0 } },
    /*0BD9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x023A, { 0 } },
    /*0BDA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x023B, { 0 } },
    /*0BDB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x023C, { 0 } },
    /*0BDC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x023D, { 0 } },
    /*0BDD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x023E, { 0 } },
    /*0BDE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x023F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUB213PD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BDF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01BB, { 0 } },
    /*0BE0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01BC, { 0 } },
    /*0BE1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01BD, { 0 } },
    /*0BE2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01BE, { 0 } },
    /*0BE3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0240, { 0 } },
    /*0BE4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0241, { 0 } },
    /*0BE5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0242, { 0 } },
    /*0BE6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0243, { 0 } },
    /*0BE7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0244, { 0 } },
    /*0BE8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0245, { 0 } },
    /*0BE9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0246, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUB213PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BEA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01BF, { 0 } },
    /*0BEB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C0, { 0 } },
    /*0BEC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C1, { 0 } },
    /*0BED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C2, { 0 } },
    /*0BEE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0247, { 0 } },
    /*0BEF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0248, { 0 } },
    /*0BF0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0249, { 0 } },
    /*0BF1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x024A, { 0 } },
    /*0BF2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x024B, { 0 } },
    /*0BF3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x024C, { 0 } },
    /*0BF4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x024D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUB231PD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0BF5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C3, { 0 } },
    /*0BF6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C4, { 0 } },
    /*0BF7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C5, { 0 } },
    /*0BF8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C6, { 0 } },
    /*0BF9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x024E, { 0 } },
    /*0BFA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x024F, { 0 } },
    /*0BFB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0250, { 0 } },
    /*0BFC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0251, { 0 } },
    /*0BFD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0252, { 0 } },
    /*0BFE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0253, { 0 } },
    /*0BFF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0254, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUB231PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C00*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C7, { 0 } },
    /*0C01*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C8, { 0 } },
    /*0C02*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01C9, { 0 } },
    /*0C03*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01CA, { 0 } },
    /*0C04*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0255, { 0 } },
    /*0C05*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0256, { 0 } },
    /*0C06*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0257, { 0 } },
    /*0C07*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0258, { 0 } },
    /*0C08*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0259, { 0 } },
    /*0C09*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x025A, { 0 } },
    /*0C0A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x025B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUBPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C0B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01CB, { 0 } },
    /*0C0C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01CC, { 0 } },
    /*0C0D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01CD, { 0 } },
    /*0C0E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01CE, { 0 } },
    /*0C0F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01CF, { 0 } },
    /*0C10*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D0, { 0 } },
    /*0C11*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D1, { 0 } },
    /*0C12*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMADDSUBPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C13*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D3, { 0 } },
    /*0C14*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D4, { 0 } },
    /*0C15*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D5, { 0 } },
    /*0C16*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D6, { 0 } },
    /*0C17*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D7, { 0 } },
    /*0C18*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D8, { 0 } },
    /*0C19*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01D9, { 0 } },
    /*0C1A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01DA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB132PD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C1B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01DB, { 0 } },
    /*0C1C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01DC, { 0 } },
    /*0C1D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01DD, { 0 } },
    /*0C1E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01DE, { 0 } },
    /*0C1F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x025C, { 0 } },
    /*0C20*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x025D, { 0 } },
    /*0C21*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x025E, { 0 } },
    /*0C22*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x025F, { 0 } },
    /*0C23*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0260, { 0 } },
    /*0C24*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0261, { 0 } },
    /*0C25*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0262, { 0 } },
    /*0C26*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0061, { 0 } },
    /*0C27*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0062, { 0 } },
    /*0C28*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0063, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB132PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C29*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01DF, { 0 } },
    /*0C2A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E0, { 0 } },
    /*0C2B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E1, { 0 } },
    /*0C2C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E2, { 0 } },
    /*0C2D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0263, { 0 } },
    /*0C2E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0264, { 0 } },
    /*0C2F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0265, { 0 } },
    /*0C30*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0266, { 0 } },
    /*0C31*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0267, { 0 } },
    /*0C32*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0268, { 0 } },
    /*0C33*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0269, { 0 } },
    /*0C34*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0064, { 0 } },
    /*0C35*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0065, { 0 } },
    /*0C36*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0066, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB132SD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C37*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E3, { 0 } },
    /*0C38*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E4, { 0 } },
    /*0C39*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x026A, { 0 } },
    /*0C3A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x026B, { 0 } },
    /*0C3B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x026C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB132SS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C3C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E5, { 0 } },
    /*0C3D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E6, { 0 } },
    /*0C3E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x026D, { 0 } },
    /*0C3F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x026E, { 0 } },
    /*0C40*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x026F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB213PD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C41*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E7, { 0 } },
    /*0C42*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E8, { 0 } },
    /*0C43*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01E9, { 0 } },
    /*0C44*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01EA, { 0 } },
    /*0C45*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0270, { 0 } },
    /*0C46*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0271, { 0 } },
    /*0C47*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0272, { 0 } },
    /*0C48*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0273, { 0 } },
    /*0C49*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0274, { 0 } },
    /*0C4A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0275, { 0 } },
    /*0C4B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0276, { 0 } },
    /*0C4C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0067, { 0 } },
    /*0C4D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0068, { 0 } },
    /*0C4E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0069, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB213PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C4F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01EB, { 0 } },
    /*0C50*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01EC, { 0 } },
    /*0C51*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01ED, { 0 } },
    /*0C52*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01EE, { 0 } },
    /*0C53*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0277, { 0 } },
    /*0C54*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0278, { 0 } },
    /*0C55*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0279, { 0 } },
    /*0C56*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x027A, { 0 } },
    /*0C57*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x027B, { 0 } },
    /*0C58*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x027C, { 0 } },
    /*0C59*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x027D, { 0 } },
    /*0C5A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x006A, { 0 } },
    /*0C5B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x006B, { 0 } },
    /*0C5C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x006C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB213SD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C5D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01EF, { 0 } },
    /*0C5E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F0, { 0 } },
    /*0C5F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x027E, { 0 } },
    /*0C60*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x027F, { 0 } },
    /*0C61*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0280, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB213SS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C62*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F1, { 0 } },
    /*0C63*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F2, { 0 } },
    /*0C64*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0281, { 0 } },
    /*0C65*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0282, { 0 } },
    /*0C66*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0283, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB231PD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C67*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F3, { 0 } },
    /*0C68*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F4, { 0 } },
    /*0C69*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F5, { 0 } },
    /*0C6A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F6, { 0 } },
    /*0C6B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0284, { 0 } },
    /*0C6C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0285, { 0 } },
    /*0C6D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0286, { 0 } },
    /*0C6E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0287, { 0 } },
    /*0C6F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0288, { 0 } },
    /*0C70*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0289, { 0 } },
    /*0C71*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x028A, { 0 } },
    /*0C72*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x006D, { 0 } },
    /*0C73*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x006E, { 0 } },
    /*0C74*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x006F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB231PS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C75*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F7, { 0 } },
    /*0C76*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F8, { 0 } },
    /*0C77*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01F9, { 0 } },
    /*0C78*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01FA, { 0 } },
    /*0C79*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x028B, { 0 } },
    /*0C7A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x028C, { 0 } },
    /*0C7B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x028D, { 0 } },
    /*0C7C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x028E, { 0 } },
    /*0C7D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x028F, { 0 } },
    /*0C7E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0290, { 0 } },
    /*0C7F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0291, { 0 } },
    /*0C80*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0070, { 0 } },
    /*0C81*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0071, { 0 } },
    /*0C82*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0072, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB231SD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C83*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01FB, { 0 } },
    /*0C84*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01FC, { 0 } },
    /*0C85*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0292, { 0 } },
    /*0C86*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0293, { 0 } },
    /*0C87*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0294, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUB231SS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C88*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01FD, { 0 } },
    /*0C89*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01FE, { 0 } },
    /*0C8A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0295, { 0 } },
    /*0C8B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0296, { 0 } },
    /*0C8C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0297, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADD132PD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C8D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x01FF, { 0 } },
    /*0C8E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0200, { 0 } },
    /*0C8F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0201, { 0 } },
    /*0C90*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0202, { 0 } },
    /*0C91*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0298, { 0 } },
    /*0C92*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0299, { 0 } },
    /*0C93*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x029A, { 0 } },
    /*0C94*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x029B, { 0 } },
    /*0C95*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x029C, { 0 } },
    /*0C96*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x029D, { 0 } },
    /*0C97*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x029E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADD132PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0C98*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0203, { 0 } },
    /*0C99*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0204, { 0 } },
    /*0C9A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0205, { 0 } },
    /*0C9B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0206, { 0 } },
    /*0C9C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x029F, { 0 } },
    /*0C9D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A0, { 0 } },
    /*0C9E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A1, { 0 } },
    /*0C9F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A2, { 0 } },
    /*0CA0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A3, { 0 } },
    /*0CA1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A4, { 0 } },
    /*0CA2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADD213PD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CA3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0207, { 0 } },
    /*0CA4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0208, { 0 } },
    /*0CA5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0209, { 0 } },
    /*0CA6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x020A, { 0 } },
    /*0CA7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A6, { 0 } },
    /*0CA8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A7, { 0 } },
    /*0CA9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A8, { 0 } },
    /*0CAA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02A9, { 0 } },
    /*0CAB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02AA, { 0 } },
    /*0CAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02AB, { 0 } },
    /*0CAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02AC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADD213PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CAE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x020B, { 0 } },
    /*0CAF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x020C, { 0 } },
    /*0CB0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x020D, { 0 } },
    /*0CB1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x020E, { 0 } },
    /*0CB2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02AD, { 0 } },
    /*0CB3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02AE, { 0 } },
    /*0CB4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02AF, { 0 } },
    /*0CB5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B0, { 0 } },
    /*0CB6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B1, { 0 } },
    /*0CB7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B2, { 0 } },
    /*0CB8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADD231PD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CB9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x020F, { 0 } },
    /*0CBA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0210, { 0 } },
    /*0CBB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0211, { 0 } },
    /*0CBC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0212, { 0 } },
    /*0CBD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B4, { 0 } },
    /*0CBE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B5, { 0 } },
    /*0CBF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B6, { 0 } },
    /*0CC0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B7, { 0 } },
    /*0CC1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B8, { 0 } },
    /*0CC2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02B9, { 0 } },
    /*0CC3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADD231PS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CC4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0213, { 0 } },
    /*0CC5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0214, { 0 } },
    /*0CC6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0215, { 0 } },
    /*0CC7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0216, { 0 } },
    /*0CC8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02BB, { 0 } },
    /*0CC9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02BC, { 0 } },
    /*0CCA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02BD, { 0 } },
    /*0CCB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02BE, { 0 } },
    /*0CCC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02BF, { 0 } },
    /*0CCD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C0, { 0 } },
    /*0CCE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADDPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CCF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0217, { 0 } },
    /*0CD0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0218, { 0 } },
    /*0CD1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0219, { 0 } },
    /*0CD2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x021A, { 0 } },
    /*0CD3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x021B, { 0 } },
    /*0CD4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x021C, { 0 } },
    /*0CD5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x021D, { 0 } },
    /*0CD6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x021E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBADDPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CD7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x021F, { 0 } },
    /*0CD8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0220, { 0 } },
    /*0CD9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0221, { 0 } },
    /*0CDA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0222, { 0 } },
    /*0CDB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0223, { 0 } },
    /*0CDC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0224, { 0 } },
    /*0CDD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0225, { 0 } },
    /*0CDE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0226, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CDF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0227, { 0 } },
    /*0CE0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0228, { 0 } },
    /*0CE1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0229, { 0 } },
    /*0CE2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x022A, { 0 } },
    /*0CE3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x022B, { 0 } },
    /*0CE4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x022C, { 0 } },
    /*0CE5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x022D, { 0 } },
    /*0CE6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x022E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CE7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x022F, { 0 } },
    /*0CE8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0230, { 0 } },
    /*0CE9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0231, { 0 } },
    /*0CEA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0232, { 0 } },
    /*0CEB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0233, { 0 } },
    /*0CEC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0234, { 0 } },
    /*0CED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0235, { 0 } },
    /*0CEE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0236, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBSD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CEF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0237, { 0 } },
    /*0CF0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0238, { 0 } },
    /*0CF1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0239, { 0 } },
    /*0CF2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x023A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFMSUBSS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CF3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x023B, { 0 } },
    /*0CF4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x023C, { 0 } },
    /*0CF5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x023D, { 0 } },
    /*0CF6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x023E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD132PD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0CF7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x023F, { 0 } },
    /*0CF8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0240, { 0 } },
    /*0CF9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0241, { 0 } },
    /*0CFA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0242, { 0 } },
    /*0CFB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C2, { 0 } },
    /*0CFC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C3, { 0 } },
    /*0CFD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C4, { 0 } },
    /*0CFE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C5, { 0 } },
    /*0CFF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C6, { 0 } },
    /*0D00*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C7, { 0 } },
    /*0D01*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C8, { 0 } },
    /*0D02*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0073, { 0 } },
    /*0D03*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0074, { 0 } },
    /*0D04*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0075, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD132PS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D05*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0243, { 0 } },
    /*0D06*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0244, { 0 } },
    /*0D07*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0245, { 0 } },
    /*0D08*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0246, { 0 } },
    /*0D09*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02C9, { 0 } },
    /*0D0A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02CA, { 0 } },
    /*0D0B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02CB, { 0 } },
    /*0D0C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02CC, { 0 } },
    /*0D0D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02CD, { 0 } },
    /*0D0E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02CE, { 0 } },
    /*0D0F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02CF, { 0 } },
    /*0D10*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0076, { 0 } },
    /*0D11*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0077, { 0 } },
    /*0D12*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0078, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD132SD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D13*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0247, { 0 } },
    /*0D14*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0248, { 0 } },
    /*0D15*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D0, { 0 } },
    /*0D16*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D1, { 0 } },
    /*0D17*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD132SS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D18*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0249, { 0 } },
    /*0D19*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x024A, { 0 } },
    /*0D1A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D3, { 0 } },
    /*0D1B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D4, { 0 } },
    /*0D1C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD213PD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D1D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x024B, { 0 } },
    /*0D1E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x024C, { 0 } },
    /*0D1F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x024D, { 0 } },
    /*0D20*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x024E, { 0 } },
    /*0D21*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D6, { 0 } },
    /*0D22*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D7, { 0 } },
    /*0D23*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D8, { 0 } },
    /*0D24*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02D9, { 0 } },
    /*0D25*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02DA, { 0 } },
    /*0D26*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02DB, { 0 } },
    /*0D27*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02DC, { 0 } },
    /*0D28*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0079, { 0 } },
    /*0D29*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x007A, { 0 } },
    /*0D2A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x007B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD213PS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D2B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x024F, { 0 } },
    /*0D2C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0250, { 0 } },
    /*0D2D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0251, { 0 } },
    /*0D2E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0252, { 0 } },
    /*0D2F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02DD, { 0 } },
    /*0D30*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02DE, { 0 } },
    /*0D31*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02DF, { 0 } },
    /*0D32*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E0, { 0 } },
    /*0D33*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E1, { 0 } },
    /*0D34*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E2, { 0 } },
    /*0D35*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E3, { 0 } },
    /*0D36*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x007C, { 0 } },
    /*0D37*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x007D, { 0 } },
    /*0D38*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x007E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD213SD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D39*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0253, { 0 } },
    /*0D3A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0254, { 0 } },
    /*0D3B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E4, { 0 } },
    /*0D3C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E5, { 0 } },
    /*0D3D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD213SS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D3E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0255, { 0 } },
    /*0D3F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0256, { 0 } },
    /*0D40*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E7, { 0 } },
    /*0D41*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E8, { 0 } },
    /*0D42*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02E9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD231PD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D43*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0257, { 0 } },
    /*0D44*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0258, { 0 } },
    /*0D45*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0259, { 0 } },
    /*0D46*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x025A, { 0 } },
    /*0D47*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02EA, { 0 } },
    /*0D48*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02EB, { 0 } },
    /*0D49*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02EC, { 0 } },
    /*0D4A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02ED, { 0 } },
    /*0D4B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02EE, { 0 } },
    /*0D4C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02EF, { 0 } },
    /*0D4D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F0, { 0 } },
    /*0D4E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x007F, { 0 } },
    /*0D4F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0080, { 0 } },
    /*0D50*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0081, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD231PS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D51*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x025B, { 0 } },
    /*0D52*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x025C, { 0 } },
    /*0D53*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x025D, { 0 } },
    /*0D54*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x025E, { 0 } },
    /*0D55*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F1, { 0 } },
    /*0D56*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F2, { 0 } },
    /*0D57*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F3, { 0 } },
    /*0D58*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F4, { 0 } },
    /*0D59*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F5, { 0 } },
    /*0D5A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F6, { 0 } },
    /*0D5B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F7, { 0 } },
    /*0D5C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0082, { 0 } },
    /*0D5D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0083, { 0 } },
    /*0D5E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0084, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD231SD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D5F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x025F, { 0 } },
    /*0D60*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0260, { 0 } },
    /*0D61*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F8, { 0 } },
    /*0D62*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02F9, { 0 } },
    /*0D63*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02FA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADD231SS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D64*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0261, { 0 } },
    /*0D65*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0262, { 0 } },
    /*0D66*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02FB, { 0 } },
    /*0D67*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02FC, { 0 } },
    /*0D68*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02FD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADDPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D69*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0263, { 0 } },
    /*0D6A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0264, { 0 } },
    /*0D6B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0265, { 0 } },
    /*0D6C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0266, { 0 } },
    /*0D6D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0267, { 0 } },
    /*0D6E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0268, { 0 } },
    /*0D6F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0269, { 0 } },
    /*0D70*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x026A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADDPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D71*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x026B, { 0 } },
    /*0D72*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x026C, { 0 } },
    /*0D73*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x026D, { 0 } },
    /*0D74*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x026E, { 0 } },
    /*0D75*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x026F, { 0 } },
    /*0D76*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0270, { 0 } },
    /*0D77*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0271, { 0 } },
    /*0D78*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0272, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADDSD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D79*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0273, { 0 } },
    /*0D7A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0274, { 0 } },
    /*0D7B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0275, { 0 } },
    /*0D7C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0276, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMADDSS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D7D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0277, { 0 } },
    /*0D7E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0278, { 0 } },
    /*0D7F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0279, { 0 } },
    /*0D80*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x027A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB132PD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D81*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x027B, { 0 } },
    /*0D82*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x027C, { 0 } },
    /*0D83*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x027D, { 0 } },
    /*0D84*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x027E, { 0 } },
    /*0D85*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02FE, { 0 } },
    /*0D86*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x02FF, { 0 } },
    /*0D87*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0300, { 0 } },
    /*0D88*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0301, { 0 } },
    /*0D89*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0302, { 0 } },
    /*0D8A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0303, { 0 } },
    /*0D8B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0304, { 0 } },
    /*0D8C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0085, { 0 } },
    /*0D8D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0086, { 0 } },
    /*0D8E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0087, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB132PS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D8F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x027F, { 0 } },
    /*0D90*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0280, { 0 } },
    /*0D91*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0281, { 0 } },
    /*0D92*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0282, { 0 } },
    /*0D93*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0305, { 0 } },
    /*0D94*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0306, { 0 } },
    /*0D95*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0307, { 0 } },
    /*0D96*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0308, { 0 } },
    /*0D97*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0309, { 0 } },
    /*0D98*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x030A, { 0 } },
    /*0D99*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x030B, { 0 } },
    /*0D9A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0088, { 0 } },
    /*0D9B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0089, { 0 } },
    /*0D9C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x008A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB132SD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0D9D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0283, { 0 } },
    /*0D9E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0284, { 0 } },
    /*0D9F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x030C, { 0 } },
    /*0DA0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x030D, { 0 } },
    /*0DA1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x030E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB132SS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DA2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0285, { 0 } },
    /*0DA3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0286, { 0 } },
    /*0DA4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x030F, { 0 } },
    /*0DA5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0310, { 0 } },
    /*0DA6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0311, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB213PD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DA7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0287, { 0 } },
    /*0DA8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0288, { 0 } },
    /*0DA9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0289, { 0 } },
    /*0DAA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x028A, { 0 } },
    /*0DAB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0312, { 0 } },
    /*0DAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0313, { 0 } },
    /*0DAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0314, { 0 } },
    /*0DAE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0315, { 0 } },
    /*0DAF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0316, { 0 } },
    /*0DB0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0317, { 0 } },
    /*0DB1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0318, { 0 } },
    /*0DB2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x008B, { 0 } },
    /*0DB3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x008C, { 0 } },
    /*0DB4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x008D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB213PS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DB5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x028B, { 0 } },
    /*0DB6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x028C, { 0 } },
    /*0DB7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x028D, { 0 } },
    /*0DB8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x028E, { 0 } },
    /*0DB9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0319, { 0 } },
    /*0DBA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x031A, { 0 } },
    /*0DBB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x031B, { 0 } },
    /*0DBC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x031C, { 0 } },
    /*0DBD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x031D, { 0 } },
    /*0DBE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x031E, { 0 } },
    /*0DBF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x031F, { 0 } },
    /*0DC0*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x008E, { 0 } },
    /*0DC1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x008F, { 0 } },
    /*0DC2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0090, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB213SD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DC3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x028F, { 0 } },
    /*0DC4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0290, { 0 } },
    /*0DC5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0320, { 0 } },
    /*0DC6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0321, { 0 } },
    /*0DC7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0322, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB213SS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DC8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0291, { 0 } },
    /*0DC9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0292, { 0 } },
    /*0DCA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0323, { 0 } },
    /*0DCB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0324, { 0 } },
    /*0DCC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0325, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB231PD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DCD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0293, { 0 } },
    /*0DCE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0294, { 0 } },
    /*0DCF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0295, { 0 } },
    /*0DD0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0296, { 0 } },
    /*0DD1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0326, { 0 } },
    /*0DD2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0327, { 0 } },
    /*0DD3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0328, { 0 } },
    /*0DD4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0329, { 0 } },
    /*0DD5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x032A, { 0 } },
    /*0DD6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x032B, { 0 } },
    /*0DD7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x032C, { 0 } },
    /*0DD8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0091, { 0 } },
    /*0DD9*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0092, { 0 } },
    /*0DDA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0093, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB231PS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DDB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0297, { 0 } },
    /*0DDC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0298, { 0 } },
    /*0DDD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0299, { 0 } },
    /*0DDE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x029A, { 0 } },
    /*0DDF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x032D, { 0 } },
    /*0DE0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x032E, { 0 } },
    /*0DE1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x032F, { 0 } },
    /*0DE2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0330, { 0 } },
    /*0DE3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0331, { 0 } },
    /*0DE4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0332, { 0 } },
    /*0DE5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0333, { 0 } },
    /*0DE6*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0094, { 0 } },
    /*0DE7*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0095, { 0 } },
    /*0DE8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0096, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB231SD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DE9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x029B, { 0 } },
    /*0DEA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x029C, { 0 } },
    /*0DEB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0334, { 0 } },
    /*0DEC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0335, { 0 } },
    /*0DED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0336, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUB231SS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DEE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x029D, { 0 } },
    /*0DEF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x029E, { 0 } },
    /*0DF0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0337, { 0 } },
    /*0DF1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0338, { 0 } },
    /*0DF2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0339, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUBPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DF3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x029F, { 0 } },
    /*0DF4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A0, { 0 } },
    /*0DF5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A1, { 0 } },
    /*0DF6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A2, { 0 } },
    /*0DF7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A3, { 0 } },
    /*0DF8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A4, { 0 } },
    /*0DF9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A5, { 0 } },
    /*0DFA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUBPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0DFB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A7, { 0 } },
    /*0DFC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A8, { 0 } },
    /*0DFD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02A9, { 0 } },
    /*0DFE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02AA, { 0 } },
    /*0DFF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02AB, { 0 } },
    /*0E00*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02AC, { 0 } },
    /*0E01*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02AD, { 0 } },
    /*0E02*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02AE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUBSD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E03*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02AF, { 0 } },
    /*0E04*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B0, { 0 } },
    /*0E05*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B1, { 0 } },
    /*0E06*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFNMSUBSS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E07*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B3, { 0 } },
    /*0E08*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B4, { 0 } },
    /*0E09*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B5, { 0 } },
    /*0E0A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFPCLASSPD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E0B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x033A, { 0 } },
    /*0E0C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x033B, { 0 } },
    /*0E0D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x033C, { 0 } },
    /*0E0E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x033D, { 0 } },
    /*0E0F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x033E, { 0 } },
    /*0E10*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x033F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFPCLASSPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E11*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0340, { 0 } },
    /*0E12*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0341, { 0 } },
    /*0E13*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0342, { 0 } },
    /*0E14*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0343, { 0 } },
    /*0E15*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0344, { 0 } },
    /*0E16*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0345, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFPCLASSSD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E17*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0346, { 0 } },
    /*0E18*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0347, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFPCLASSSS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E19*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0348, { 0 } },
    /*0E1A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0349, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFRCZPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E1B*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x002E, { 0 } },
    /*0E1C*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x002F, { 0 } },
    /*0E1D*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0030, { 0 } },
    /*0E1E*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0031, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFRCZPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E1F*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0032, { 0 } },
    /*0E20*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0033, { 0 } },
    /*0E21*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0034, { 0 } },
    /*0E22*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0035, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFRCZSD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E23*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0036, { 0 } },
    /*0E24*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0037, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VFRCZSS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E25*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0038, { 0 } },
    /*0E26*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0039, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERDPD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E27*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B7, { 0 } },
    /*0E28*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B8, { 0 } },
    /*0E29*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x034A, { 0 } },
    /*0E2A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x034B, { 0 } },
    /*0E2B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x034C, { 0 } },
    /*0E2C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0097, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERDPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E2D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02B9, { 0 } },
    /*0E2E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02BA, { 0 } },
    /*0E2F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x034D, { 0 } },
    /*0E30*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x034E, { 0 } },
    /*0E31*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x034F, { 0 } },
    /*0E32*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0098, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF0DPD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E33*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0350, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF0DPS                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E34*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0351, { 0 } },
    /*0E35*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0099, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF0HINTDPD                                                                          */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E36*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x009A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF0HINTDPS                                                                          */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E37*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x009B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF0QPD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E38*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0352, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF0QPS                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E39*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0353, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF1DPD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E3A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0354, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF1DPS                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E3B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0355, { 0 } },
    /*0E3C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x009C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF1QPD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E3D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0356, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERPF1QPS                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E3E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0357, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERQPD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E3F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02BB, { 0 } },
    /*0E40*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02BC, { 0 } },
    /*0E41*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0358, { 0 } },
    /*0E42*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0359, { 0 } },
    /*0E43*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x035A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGATHERQPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E44*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02BD, { 0 } },
    /*0E45*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02BE, { 0 } },
    /*0E46*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x035B, { 0 } },
    /*0E47*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x035C, { 0 } },
    /*0E48*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x035D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETEXPPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E49*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x035E, { 0 } },
    /*0E4A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x035F, { 0 } },
    /*0E4B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0360, { 0 } },
    /*0E4C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0361, { 0 } },
    /*0E4D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0362, { 0 } },
    /*0E4E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0363, { 0 } },
    /*0E4F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0364, { 0 } },
    /*0E50*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x009D, { 0 } },
    /*0E51*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x009E, { 0 } },
    /*0E52*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x009F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETEXPPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E53*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0365, { 0 } },
    /*0E54*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0366, { 0 } },
    /*0E55*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0367, { 0 } },
    /*0E56*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0368, { 0 } },
    /*0E57*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0369, { 0 } },
    /*0E58*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x036A, { 0 } },
    /*0E59*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x036B, { 0 } },
    /*0E5A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A0, { 0 } },
    /*0E5B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A1, { 0 } },
    /*0E5C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETEXPSD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E5D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x036C, { 0 } },
    /*0E5E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x036D, { 0 } },
    /*0E5F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x036E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETEXPSS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E60*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x036F, { 0 } },
    /*0E61*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0370, { 0 } },
    /*0E62*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0371, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETMANTPD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E63*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0372, { 0 } },
    /*0E64*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0373, { 0 } },
    /*0E65*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0374, { 0 } },
    /*0E66*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0375, { 0 } },
    /*0E67*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0376, { 0 } },
    /*0E68*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0377, { 0 } },
    /*0E69*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0378, { 0 } },
    /*0E6A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A3, { 0 } },
    /*0E6B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A4, { 0 } },
    /*0E6C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETMANTPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E6D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0379, { 0 } },
    /*0E6E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x037A, { 0 } },
    /*0E6F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x037B, { 0 } },
    /*0E70*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x037C, { 0 } },
    /*0E71*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x037D, { 0 } },
    /*0E72*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x037E, { 0 } },
    /*0E73*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x037F, { 0 } },
    /*0E74*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A6, { 0 } },
    /*0E75*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A7, { 0 } },
    /*0E76*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETMANTSD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E77*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0380, { 0 } },
    /*0E78*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0381, { 0 } },
    /*0E79*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0382, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGETMANTSS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E7A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0383, { 0 } },
    /*0E7B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0384, { 0 } },
    /*0E7C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0385, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGMAXABSPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E7D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00A9, { 0 } },
    /*0E7E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00AA, { 0 } },
    /*0E7F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00AB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGMAXPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E80*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00AC, { 0 } },
    /*0E81*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00AD, { 0 } },
    /*0E82*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00AE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGMAXPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E83*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00AF, { 0 } },
    /*0E84*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B0, { 0 } },
    /*0E85*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGMINPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E86*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B2, { 0 } },
    /*0E87*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B3, { 0 } },
    /*0E88*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VGMINPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E89*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B5, { 0 } },
    /*0E8A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B6, { 0 } },
    /*0E8B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VHADDPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E8C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02BF, { 0 } },
    /*0E8D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C0, { 0 } },
    /*0E8E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C1, { 0 } },
    /*0E8F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VHADDPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E90*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C3, { 0 } },
    /*0E91*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C4, { 0 } },
    /*0E92*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C5, { 0 } },
    /*0E93*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VHSUBPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E94*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C7, { 0 } },
    /*0E95*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C8, { 0 } },
    /*0E96*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02C9, { 0 } },
    /*0E97*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VHSUBPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E98*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02CB, { 0 } },
    /*0E99*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02CC, { 0 } },
    /*0E9A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02CD, { 0 } },
    /*0E9B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTF128                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E9C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02CF, { 0 } },
    /*0E9D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTF32X4                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0E9E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0386, { 0 } },
    /*0E9F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0387, { 0 } },
    /*0EA0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0388, { 0 } },
    /*0EA1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0389, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTF32X8                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EA2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x038A, { 0 } },
    /*0EA3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x038B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTF64X2                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EA4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x038C, { 0 } },
    /*0EA5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x038D, { 0 } },
    /*0EA6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x038E, { 0 } },
    /*0EA7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x038F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTF64X4                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EA8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0390, { 0 } },
    /*0EA9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0391, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTI128                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EAA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D1, { 0 } },
    /*0EAB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTI32X4                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0392, { 0 } },
    /*0EAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0393, { 0 } },
    /*0EAE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0394, { 0 } },
    /*0EAF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0395, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTI32X8                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EB0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0396, { 0 } },
    /*0EB1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0397, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTI64X2                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EB2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0398, { 0 } },
    /*0EB3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0399, { 0 } },
    /*0EB4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x039A, { 0 } },
    /*0EB5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x039B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTI64X4                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EB6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x039C, { 0 } },
    /*0EB7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x039D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VINSERTPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EB8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D3, { 0 } },
    /*0EB9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D4, { 0 } },
    /*0EBA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x039E, { 0 } },
    /*0EBB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x039F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLDDQU                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EBC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D5, { 0 } },
    /*0EBD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLDMXCSR                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EBE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKHD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EBF*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKHPD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC0*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00B9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKHPS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKHQ                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00BB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKLD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00BC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKLPD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00BD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKLPS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00BE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOADUNPACKLQ                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC6*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00BF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VLOG2PS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EC7*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C0, { 0 } },
    /*0EC8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C1, { 0 } },
    /*0EC9*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMASKMOVDQU                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ECA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMASKMOVPD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ECB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02D9, { 0 } },
    /*0ECC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02DA, { 0 } },
    /*0ECD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02DB, { 0 } },
    /*0ECE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02DC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMASKMOVPS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ECF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02DD, { 0 } },
    /*0ED0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02DE, { 0 } },
    /*0ED1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02DF, { 0 } },
    /*0ED2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMAXPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0ED3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E1, { 0 } },
    /*0ED4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E2, { 0 } },
    /*0ED5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E3, { 0 } },
    /*0ED6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E4, { 0 } },
    /*0ED7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A0, { 0 } },
    /*0ED8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A1, { 0 } },
    /*0ED9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A2, { 0 } },
    /*0EDA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A3, { 0 } },
    /*0EDB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A4, { 0 } },
    /*0EDC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A5, { 0 } },
    /*0EDD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMAXPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EDE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E5, { 0 } },
    /*0EDF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E6, { 0 } },
    /*0EE0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E7, { 0 } },
    /*0EE1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E8, { 0 } },
    /*0EE2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A7, { 0 } },
    /*0EE3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A8, { 0 } },
    /*0EE4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03A9, { 0 } },
    /*0EE5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03AA, { 0 } },
    /*0EE6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03AB, { 0 } },
    /*0EE7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03AC, { 0 } },
    /*0EE8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03AD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMAXSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EE9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02E9, { 0 } },
    /*0EEA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02EA, { 0 } },
    /*0EEB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03AE, { 0 } },
    /*0EEC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03AF, { 0 } },
    /*0EED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMAXSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EEE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02EB, { 0 } },
    /*0EEF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02EC, { 0 } },
    /*0EF0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B1, { 0 } },
    /*0EF1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B2, { 0 } },
    /*0EF2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMCALL                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EF3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0725, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMCLEAR                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EF4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0726, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMFUNC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EF5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0727, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMINPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0EF6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02ED, { 0 } },
    /*0EF7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02EE, { 0 } },
    /*0EF8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02EF, { 0 } },
    /*0EF9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F0, { 0 } },
    /*0EFA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B4, { 0 } },
    /*0EFB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B5, { 0 } },
    /*0EFC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B6, { 0 } },
    /*0EFD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B7, { 0 } },
    /*0EFE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B8, { 0 } },
    /*0EFF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03B9, { 0 } },
    /*0F00*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMINPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F01*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F1, { 0 } },
    /*0F02*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F2, { 0 } },
    /*0F03*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F3, { 0 } },
    /*0F04*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F4, { 0 } },
    /*0F05*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03BB, { 0 } },
    /*0F06*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03BC, { 0 } },
    /*0F07*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03BD, { 0 } },
    /*0F08*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03BE, { 0 } },
    /*0F09*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03BF, { 0 } },
    /*0F0A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C0, { 0 } },
    /*0F0B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMINSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F0C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F5, { 0 } },
    /*0F0D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F6, { 0 } },
    /*0F0E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C2, { 0 } },
    /*0F0F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C3, { 0 } },
    /*0F10*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMINSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F11*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F7, { 0 } },
    /*0F12*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F8, { 0 } },
    /*0F13*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C5, { 0 } },
    /*0F14*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C6, { 0 } },
    /*0F15*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMLAUNCH                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F16*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0728, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMLOAD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F17*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0729, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMMCALL                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F18*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x072A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVAPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F19*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02F9, { 0 } },
    /*0F1A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02FA, { 0 } },
    /*0F1B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02FB, { 0 } },
    /*0F1C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02FC, { 0 } },
    /*0F1D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02FD, { 0 } },
    /*0F1E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02FE, { 0 } },
    /*0F1F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x02FF, { 0 } },
    /*0F20*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0300, { 0 } },
    /*0F21*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C8, { 0 } },
    /*0F22*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03C9, { 0 } },
    /*0F23*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03CA, { 0 } },
    /*0F24*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03CB, { 0 } },
    /*0F25*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03CC, { 0 } },
    /*0F26*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03CD, { 0 } },
    /*0F27*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03CE, { 0 } },
    /*0F28*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03CF, { 0 } },
    /*0F29*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D0, { 0 } },
    /*0F2A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D1, { 0 } },
    /*0F2B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D2, { 0 } },
    /*0F2C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D3, { 0 } },
    /*0F2D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C3, { 0 } },
    /*0F2E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C4, { 0 } },
    /*0F2F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C5, { 0 } },
    /*0F30*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVAPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F31*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0301, { 0 } },
    /*0F32*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0302, { 0 } },
    /*0F33*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0303, { 0 } },
    /*0F34*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0304, { 0 } },
    /*0F35*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0305, { 0 } },
    /*0F36*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0306, { 0 } },
    /*0F37*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0307, { 0 } },
    /*0F38*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0308, { 0 } },
    /*0F39*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D4, { 0 } },
    /*0F3A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D5, { 0 } },
    /*0F3B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D6, { 0 } },
    /*0F3C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D7, { 0 } },
    /*0F3D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D8, { 0 } },
    /*0F3E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03D9, { 0 } },
    /*0F3F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03DA, { 0 } },
    /*0F40*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03DB, { 0 } },
    /*0F41*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03DC, { 0 } },
    /*0F42*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03DD, { 0 } },
    /*0F43*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03DE, { 0 } },
    /*0F44*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03DF, { 0 } },
    /*0F45*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C7, { 0 } },
    /*0F46*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C8, { 0 } },
    /*0F47*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00C9, { 0 } },
    /*0F48*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F49*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0309, { 0 } },
    /*0F4A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x030A, { 0 } },
    /*0F4B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x030B, { 0 } },
    /*0F4C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x030C, { 0 } },
    /*0F4D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x030D, { 0 } },
    /*0F4E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x030E, { 0 } },
    /*0F4F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x030F, { 0 } },
    /*0F50*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0310, { 0 } },
    /*0F51*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E0, { 0 } },
    /*0F52*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E1, { 0 } },
    /*0F53*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E2, { 0 } },
    /*0F54*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDDUP                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F55*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0311, { 0 } },
    /*0F56*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0312, { 0 } },
    /*0F57*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0313, { 0 } },
    /*0F58*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0314, { 0 } },
    /*0F59*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E4, { 0 } },
    /*0F5A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E5, { 0 } },
    /*0F5B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E6, { 0 } },
    /*0F5C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E7, { 0 } },
    /*0F5D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E8, { 0 } },
    /*0F5E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03E9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQA                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F5F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0315, { 0 } },
    /*0F60*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0316, { 0 } },
    /*0F61*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0317, { 0 } },
    /*0F62*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0318, { 0 } },
    /*0F63*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0319, { 0 } },
    /*0F64*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x031A, { 0 } },
    /*0F65*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x031B, { 0 } },
    /*0F66*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x031C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQA32                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F67*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03EA, { 0 } },
    /*0F68*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03EB, { 0 } },
    /*0F69*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03EC, { 0 } },
    /*0F6A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03ED, { 0 } },
    /*0F6B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03EE, { 0 } },
    /*0F6C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03EF, { 0 } },
    /*0F6D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F0, { 0 } },
    /*0F6E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F1, { 0 } },
    /*0F6F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F2, { 0 } },
    /*0F70*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F3, { 0 } },
    /*0F71*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F4, { 0 } },
    /*0F72*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F5, { 0 } },
    /*0F73*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00CB, { 0 } },
    /*0F74*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00CC, { 0 } },
    /*0F75*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00CD, { 0 } },
    /*0F76*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQA64                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F77*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F6, { 0 } },
    /*0F78*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F7, { 0 } },
    /*0F79*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F8, { 0 } },
    /*0F7A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03F9, { 0 } },
    /*0F7B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03FA, { 0 } },
    /*0F7C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03FB, { 0 } },
    /*0F7D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03FC, { 0 } },
    /*0F7E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03FD, { 0 } },
    /*0F7F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03FE, { 0 } },
    /*0F80*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x03FF, { 0 } },
    /*0F81*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0400, { 0 } },
    /*0F82*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0401, { 0 } },
    /*0F83*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00CF, { 0 } },
    /*0F84*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D0, { 0 } },
    /*0F85*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D1, { 0 } },
    /*0F86*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQU                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F87*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x031D, { 0 } },
    /*0F88*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x031E, { 0 } },
    /*0F89*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x031F, { 0 } },
    /*0F8A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0320, { 0 } },
    /*0F8B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0321, { 0 } },
    /*0F8C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0322, { 0 } },
    /*0F8D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0323, { 0 } },
    /*0F8E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0324, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQU16                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F8F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0402, { 0 } },
    /*0F90*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0403, { 0 } },
    /*0F91*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0404, { 0 } },
    /*0F92*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0405, { 0 } },
    /*0F93*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0406, { 0 } },
    /*0F94*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0407, { 0 } },
    /*0F95*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0408, { 0 } },
    /*0F96*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0409, { 0 } },
    /*0F97*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x040A, { 0 } },
    /*0F98*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x040B, { 0 } },
    /*0F99*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x040C, { 0 } },
    /*0F9A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x040D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQU32                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0F9B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x040E, { 0 } },
    /*0F9C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x040F, { 0 } },
    /*0F9D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0410, { 0 } },
    /*0F9E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0411, { 0 } },
    /*0F9F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0412, { 0 } },
    /*0FA0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0413, { 0 } },
    /*0FA1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0414, { 0 } },
    /*0FA2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0415, { 0 } },
    /*0FA3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0416, { 0 } },
    /*0FA4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0417, { 0 } },
    /*0FA5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0418, { 0 } },
    /*0FA6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0419, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQU64                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FA7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x041A, { 0 } },
    /*0FA8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x041B, { 0 } },
    /*0FA9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x041C, { 0 } },
    /*0FAA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x041D, { 0 } },
    /*0FAB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x041E, { 0 } },
    /*0FAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x041F, { 0 } },
    /*0FAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0420, { 0 } },
    /*0FAE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0421, { 0 } },
    /*0FAF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0422, { 0 } },
    /*0FB0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0423, { 0 } },
    /*0FB1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0424, { 0 } },
    /*0FB2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0425, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVDQU8                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FB3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0426, { 0 } },
    /*0FB4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0427, { 0 } },
    /*0FB5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0428, { 0 } },
    /*0FB6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0429, { 0 } },
    /*0FB7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x042A, { 0 } },
    /*0FB8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x042B, { 0 } },
    /*0FB9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x042C, { 0 } },
    /*0FBA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x042D, { 0 } },
    /*0FBB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x042E, { 0 } },
    /*0FBC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x042F, { 0 } },
    /*0FBD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0430, { 0 } },
    /*0FBE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0431, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVHLPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FBF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0325, { 0 } },
    /*0FC0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0432, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVHPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FC1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0326, { 0 } },
    /*0FC2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0327, { 0 } },
    /*0FC3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0433, { 0 } },
    /*0FC4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0434, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVHPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FC5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0328, { 0 } },
    /*0FC6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0329, { 0 } },
    /*0FC7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0435, { 0 } },
    /*0FC8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0436, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVLHPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FC9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x032A, { 0 } },
    /*0FCA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0437, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVLPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FCB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x032B, { 0 } },
    /*0FCC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x032C, { 0 } },
    /*0FCD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0438, { 0 } },
    /*0FCE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0439, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVLPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FCF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x032D, { 0 } },
    /*0FD0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x032E, { 0 } },
    /*0FD1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x043A, { 0 } },
    /*0FD2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x043B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVMSKPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FD3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x032F, { 0 } },
    /*0FD4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0330, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVMSKPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FD5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0331, { 0 } },
    /*0FD6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0332, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNRAPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FD7*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNRAPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FD8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNRNGOAPD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FD9*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNRNGOAPS                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FDA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNTDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FDB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0333, { 0 } },
    /*0FDC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0334, { 0 } },
    /*0FDD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x043C, { 0 } },
    /*0FDE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x043D, { 0 } },
    /*0FDF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x043E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNTDQA                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FE0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0335, { 0 } },
    /*0FE1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0336, { 0 } },
    /*0FE2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x043F, { 0 } },
    /*0FE3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0440, { 0 } },
    /*0FE4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0441, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNTPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FE5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0337, { 0 } },
    /*0FE6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0338, { 0 } },
    /*0FE7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0442, { 0 } },
    /*0FE8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0443, { 0 } },
    /*0FE9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0444, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVNTPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FEA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0339, { 0 } },
    /*0FEB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x033A, { 0 } },
    /*0FEC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0445, { 0 } },
    /*0FED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0446, { 0 } },
    /*0FEE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0447, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FEF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x033B, { 0 } },
    /*0FF0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x033C, { 0 } },
    /*0FF1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x033D, { 0 } },
    /*0FF2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x033E, { 0 } },
    /*0FF3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x033F, { 0 } },
    /*0FF4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0340, { 0 } },
    /*0FF5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0341, { 0 } },
    /*0FF6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0342, { 0 } },
    /*0FF7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0448, { 0 } },
    /*0FF8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0449, { 0 } },
    /*0FF9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x044A, { 0 } },
    /*0FFA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x044B, { 0 } },
    /*0FFB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x044C, { 0 } },
    /*0FFC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x044D, { 0 } },
    /*0FFD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x044E, { 0 } },
    /*0FFE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x044F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*0FFF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0343, { 0 } },
    /*1000*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0344, { 0 } },
    /*1001*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0345, { 0 } },
    /*1002*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0346, { 0 } },
    /*1003*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0450, { 0 } },
    /*1004*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0451, { 0 } },
    /*1005*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0452, { 0 } },
    /*1006*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0453, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVSHDUP                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1007*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0347, { 0 } },
    /*1008*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0348, { 0 } },
    /*1009*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0349, { 0 } },
    /*100A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x034A, { 0 } },
    /*100B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0454, { 0 } },
    /*100C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0455, { 0 } },
    /*100D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0456, { 0 } },
    /*100E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0457, { 0 } },
    /*100F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0458, { 0 } },
    /*1010*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0459, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVSLDUP                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1011*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x034B, { 0 } },
    /*1012*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x034C, { 0 } },
    /*1013*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x034D, { 0 } },
    /*1014*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x034E, { 0 } },
    /*1015*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x045A, { 0 } },
    /*1016*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x045B, { 0 } },
    /*1017*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x045C, { 0 } },
    /*1018*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x045D, { 0 } },
    /*1019*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x045E, { 0 } },
    /*101A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x045F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*101B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x034F, { 0 } },
    /*101C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0350, { 0 } },
    /*101D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0351, { 0 } },
    /*101E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0352, { 0 } },
    /*101F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0460, { 0 } },
    /*1020*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0461, { 0 } },
    /*1021*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0462, { 0 } },
    /*1022*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0463, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVUPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1023*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0353, { 0 } },
    /*1024*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0354, { 0 } },
    /*1025*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0355, { 0 } },
    /*1026*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0356, { 0 } },
    /*1027*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0357, { 0 } },
    /*1028*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0358, { 0 } },
    /*1029*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0359, { 0 } },
    /*102A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x035A, { 0 } },
    /*102B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0464, { 0 } },
    /*102C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0465, { 0 } },
    /*102D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0466, { 0 } },
    /*102E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0467, { 0 } },
    /*102F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0468, { 0 } },
    /*1030*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0469, { 0 } },
    /*1031*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x046A, { 0 } },
    /*1032*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x046B, { 0 } },
    /*1033*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x046C, { 0 } },
    /*1034*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x046D, { 0 } },
    /*1035*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x046E, { 0 } },
    /*1036*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x046F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMOVUPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1037*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x035B, { 0 } },
    /*1038*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x035C, { 0 } },
    /*1039*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x035D, { 0 } },
    /*103A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x035E, { 0 } },
    /*103B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x035F, { 0 } },
    /*103C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0360, { 0 } },
    /*103D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0361, { 0 } },
    /*103E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0362, { 0 } },
    /*103F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0470, { 0 } },
    /*1040*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0471, { 0 } },
    /*1041*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0472, { 0 } },
    /*1042*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0473, { 0 } },
    /*1043*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0474, { 0 } },
    /*1044*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0475, { 0 } },
    /*1045*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0476, { 0 } },
    /*1046*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0477, { 0 } },
    /*1047*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0478, { 0 } },
    /*1048*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0479, { 0 } },
    /*1049*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x047A, { 0 } },
    /*104A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x047B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMPSADBW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*104B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0363, { 0 } },
    /*104C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0364, { 0 } },
    /*104D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0365, { 0 } },
    /*104E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0366, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMPTRLD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*104F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x072B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMPTRST                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1050*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x072C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMREAD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1051*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x072D, { 0 } },
    /*1052*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x072E, { 0 } },
    /*1053*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x072F, { 0 } },
    /*1054*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0730, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMRESUME                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1055*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0731, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMRUN                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1056*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0732, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMSAVE                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1057*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0733, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMULPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1058*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0367, { 0 } },
    /*1059*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0368, { 0 } },
    /*105A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0369, { 0 } },
    /*105B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x036A, { 0 } },
    /*105C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x047C, { 0 } },
    /*105D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x047D, { 0 } },
    /*105E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x047E, { 0 } },
    /*105F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x047F, { 0 } },
    /*1060*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0480, { 0 } },
    /*1061*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0481, { 0 } },
    /*1062*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0482, { 0 } },
    /*1063*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D7, { 0 } },
    /*1064*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D8, { 0 } },
    /*1065*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMULPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1066*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x036B, { 0 } },
    /*1067*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x036C, { 0 } },
    /*1068*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x036D, { 0 } },
    /*1069*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x036E, { 0 } },
    /*106A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0483, { 0 } },
    /*106B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0484, { 0 } },
    /*106C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0485, { 0 } },
    /*106D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0486, { 0 } },
    /*106E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0487, { 0 } },
    /*106F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0488, { 0 } },
    /*1070*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0489, { 0 } },
    /*1071*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00DA, { 0 } },
    /*1072*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00DB, { 0 } },
    /*1073*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00DC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMULSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1074*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x036F, { 0 } },
    /*1075*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0370, { 0 } },
    /*1076*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x048A, { 0 } },
    /*1077*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x048B, { 0 } },
    /*1078*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x048C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMULSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1079*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0371, { 0 } },
    /*107A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0372, { 0 } },
    /*107B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x048D, { 0 } },
    /*107C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x048E, { 0 } },
    /*107D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x048F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMWRITE                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*107E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0734, { 0 } },
    /*107F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0735, { 0 } },
    /*1080*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0736, { 0 } },
    /*1081*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0737, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMXOFF                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1082*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0738, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VMXON                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1083*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0739, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VORPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1084*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0373, { 0 } },
    /*1085*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0374, { 0 } },
    /*1086*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0375, { 0 } },
    /*1087*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0376, { 0 } },
    /*1088*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0490, { 0 } },
    /*1089*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0491, { 0 } },
    /*108A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0492, { 0 } },
    /*108B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0493, { 0 } },
    /*108C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0494, { 0 } },
    /*108D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0495, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VORPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*108E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0377, { 0 } },
    /*108F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0378, { 0 } },
    /*1090*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0379, { 0 } },
    /*1091*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x037A, { 0 } },
    /*1092*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0496, { 0 } },
    /*1093*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0497, { 0 } },
    /*1094*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0498, { 0 } },
    /*1095*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0499, { 0 } },
    /*1096*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x049A, { 0 } },
    /*1097*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x049B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VP4DPWSSD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1098*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x049C, { 0 } },
    /*1099*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x049D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VP4DPWSSDS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*109A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x049E, { 0 } },
    /*109B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x049F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPABSB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*109C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x037B, { 0 } },
    /*109D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x037C, { 0 } },
    /*109E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x037D, { 0 } },
    /*109F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x037E, { 0 } },
    /*10A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A0, { 0 } },
    /*10A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A1, { 0 } },
    /*10A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A2, { 0 } },
    /*10A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A3, { 0 } },
    /*10A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A4, { 0 } },
    /*10A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPABSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10A6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x037F, { 0 } },
    /*10A7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0380, { 0 } },
    /*10A8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0381, { 0 } },
    /*10A9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0382, { 0 } },
    /*10AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A6, { 0 } },
    /*10AB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A7, { 0 } },
    /*10AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A8, { 0 } },
    /*10AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04A9, { 0 } },
    /*10AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04AA, { 0 } },
    /*10AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04AB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPABSQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04AC, { 0 } },
    /*10B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04AD, { 0 } },
    /*10B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04AE, { 0 } },
    /*10B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04AF, { 0 } },
    /*10B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B0, { 0 } },
    /*10B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPABSW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10B6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0383, { 0 } },
    /*10B7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0384, { 0 } },
    /*10B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0385, { 0 } },
    /*10B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0386, { 0 } },
    /*10BA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B2, { 0 } },
    /*10BB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B3, { 0 } },
    /*10BC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B4, { 0 } },
    /*10BD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B5, { 0 } },
    /*10BE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B6, { 0 } },
    /*10BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSSDW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10C0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0387, { 0 } },
    /*10C1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0388, { 0 } },
    /*10C2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0389, { 0 } },
    /*10C3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x038A, { 0 } },
    /*10C4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B8, { 0 } },
    /*10C5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04B9, { 0 } },
    /*10C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04BA, { 0 } },
    /*10C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04BB, { 0 } },
    /*10C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04BC, { 0 } },
    /*10C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04BD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSSWB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10CA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x038B, { 0 } },
    /*10CB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x038C, { 0 } },
    /*10CC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x038D, { 0 } },
    /*10CD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x038E, { 0 } },
    /*10CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04BE, { 0 } },
    /*10CF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04BF, { 0 } },
    /*10D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C0, { 0 } },
    /*10D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C1, { 0 } },
    /*10D2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C2, { 0 } },
    /*10D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTOREHD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10D4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTOREHPD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10D5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00DE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTOREHPS                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10D6*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00DF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTOREHQ                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10D7*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTORELD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10D8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTORELPD                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10D9*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTORELPS                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10DA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKSTORELQ                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10DB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKUSDW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10DC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x038F, { 0 } },
    /*10DD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0390, { 0 } },
    /*10DE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0391, { 0 } },
    /*10DF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0392, { 0 } },
    /*10E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C4, { 0 } },
    /*10E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C5, { 0 } },
    /*10E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C6, { 0 } },
    /*10E3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C7, { 0 } },
    /*10E4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C8, { 0 } },
    /*10E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04C9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPACKUSWB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10E6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0393, { 0 } },
    /*10E7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0394, { 0 } },
    /*10E8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0395, { 0 } },
    /*10E9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0396, { 0 } },
    /*10EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04CA, { 0 } },
    /*10EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04CB, { 0 } },
    /*10EC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04CC, { 0 } },
    /*10ED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04CD, { 0 } },
    /*10EE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04CE, { 0 } },
    /*10EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04CF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADCD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10F0*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E5, { 0 } },
    /*10F1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E6, { 0 } },
    /*10F2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10F3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0397, { 0 } },
    /*10F4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0398, { 0 } },
    /*10F5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0399, { 0 } },
    /*10F6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x039A, { 0 } },
    /*10F7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D0, { 0 } },
    /*10F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D1, { 0 } },
    /*10F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D2, { 0 } },
    /*10FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D3, { 0 } },
    /*10FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D4, { 0 } },
    /*10FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*10FD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x039B, { 0 } },
    /*10FE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x039C, { 0 } },
    /*10FF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x039D, { 0 } },
    /*1100*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x039E, { 0 } },
    /*1101*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D6, { 0 } },
    /*1102*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D7, { 0 } },
    /*1103*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D8, { 0 } },
    /*1104*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04D9, { 0 } },
    /*1105*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04DA, { 0 } },
    /*1106*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04DB, { 0 } },
    /*1107*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E8, { 0 } },
    /*1108*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00E9, { 0 } },
    /*1109*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00EA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*110A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x039F, { 0 } },
    /*110B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A0, { 0 } },
    /*110C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A1, { 0 } },
    /*110D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A2, { 0 } },
    /*110E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04DC, { 0 } },
    /*110F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04DD, { 0 } },
    /*1110*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04DE, { 0 } },
    /*1111*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04DF, { 0 } },
    /*1112*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E0, { 0 } },
    /*1113*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1114*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A3, { 0 } },
    /*1115*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A4, { 0 } },
    /*1116*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A5, { 0 } },
    /*1117*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A6, { 0 } },
    /*1118*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E2, { 0 } },
    /*1119*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E3, { 0 } },
    /*111A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E4, { 0 } },
    /*111B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E5, { 0 } },
    /*111C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E6, { 0 } },
    /*111D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDSETCD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*111E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00EB, { 0 } },
    /*111F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00EC, { 0 } },
    /*1120*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00ED, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDSETSD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1121*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00EE, { 0 } },
    /*1122*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00EF, { 0 } },
    /*1123*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1124*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A7, { 0 } },
    /*1125*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A8, { 0 } },
    /*1126*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03A9, { 0 } },
    /*1127*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03AA, { 0 } },
    /*1128*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E8, { 0 } },
    /*1129*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04E9, { 0 } },
    /*112A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04EA, { 0 } },
    /*112B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04EB, { 0 } },
    /*112C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04EC, { 0 } },
    /*112D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04ED, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDUSB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*112E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03AB, { 0 } },
    /*112F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03AC, { 0 } },
    /*1130*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03AD, { 0 } },
    /*1131*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03AE, { 0 } },
    /*1132*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04EE, { 0 } },
    /*1133*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04EF, { 0 } },
    /*1134*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F0, { 0 } },
    /*1135*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F1, { 0 } },
    /*1136*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F2, { 0 } },
    /*1137*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDUSW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1138*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03AF, { 0 } },
    /*1139*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B0, { 0 } },
    /*113A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B1, { 0 } },
    /*113B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B2, { 0 } },
    /*113C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F4, { 0 } },
    /*113D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F5, { 0 } },
    /*113E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F6, { 0 } },
    /*113F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F7, { 0 } },
    /*1140*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F8, { 0 } },
    /*1141*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPADDW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1142*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B3, { 0 } },
    /*1143*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B4, { 0 } },
    /*1144*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B5, { 0 } },
    /*1145*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B6, { 0 } },
    /*1146*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04FA, { 0 } },
    /*1147*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04FB, { 0 } },
    /*1148*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04FC, { 0 } },
    /*1149*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04FD, { 0 } },
    /*114A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04FE, { 0 } },
    /*114B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x04FF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPALIGNR                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*114C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B7, { 0 } },
    /*114D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B8, { 0 } },
    /*114E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03B9, { 0 } },
    /*114F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03BA, { 0 } },
    /*1150*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0500, { 0 } },
    /*1151*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0501, { 0 } },
    /*1152*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0502, { 0 } },
    /*1153*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0503, { 0 } },
    /*1154*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0504, { 0 } },
    /*1155*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0505, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPAND                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1156*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03BB, { 0 } },
    /*1157*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03BC, { 0 } },
    /*1158*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03BD, { 0 } },
    /*1159*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03BE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPANDD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*115A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0506, { 0 } },
    /*115B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0507, { 0 } },
    /*115C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0508, { 0 } },
    /*115D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0509, { 0 } },
    /*115E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x050A, { 0 } },
    /*115F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x050B, { 0 } },
    /*1160*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F1, { 0 } },
    /*1161*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F2, { 0 } },
    /*1162*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPANDN                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1163*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03BF, { 0 } },
    /*1164*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C0, { 0 } },
    /*1165*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C1, { 0 } },
    /*1166*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPANDND                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1167*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x050C, { 0 } },
    /*1168*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x050D, { 0 } },
    /*1169*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x050E, { 0 } },
    /*116A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x050F, { 0 } },
    /*116B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0510, { 0 } },
    /*116C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0511, { 0 } },
    /*116D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F4, { 0 } },
    /*116E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F5, { 0 } },
    /*116F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPANDNQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1170*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0512, { 0 } },
    /*1171*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0513, { 0 } },
    /*1172*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0514, { 0 } },
    /*1173*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0515, { 0 } },
    /*1174*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0516, { 0 } },
    /*1175*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0517, { 0 } },
    /*1176*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F7, { 0 } },
    /*1177*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F8, { 0 } },
    /*1178*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPANDQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1179*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0518, { 0 } },
    /*117A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0519, { 0 } },
    /*117B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x051A, { 0 } },
    /*117C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x051B, { 0 } },
    /*117D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x051C, { 0 } },
    /*117E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x051D, { 0 } },
    /*117F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00FA, { 0 } },
    /*1180*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00FB, { 0 } },
    /*1181*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00FC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPAVGB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1182*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C3, { 0 } },
    /*1183*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C4, { 0 } },
    /*1184*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C5, { 0 } },
    /*1185*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C6, { 0 } },
    /*1186*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x051E, { 0 } },
    /*1187*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x051F, { 0 } },
    /*1188*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0520, { 0 } },
    /*1189*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0521, { 0 } },
    /*118A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0522, { 0 } },
    /*118B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0523, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPAVGW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*118C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C7, { 0 } },
    /*118D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C8, { 0 } },
    /*118E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03C9, { 0 } },
    /*118F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03CA, { 0 } },
    /*1190*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0524, { 0 } },
    /*1191*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0525, { 0 } },
    /*1192*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0526, { 0 } },
    /*1193*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0527, { 0 } },
    /*1194*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0528, { 0 } },
    /*1195*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0529, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1196*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03CB, { 0 } },
    /*1197*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03CC, { 0 } },
    /*1198*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03CD, { 0 } },
    /*1199*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDMB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*119A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x052A, { 0 } },
    /*119B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x052B, { 0 } },
    /*119C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x052C, { 0 } },
    /*119D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x052D, { 0 } },
    /*119E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x052E, { 0 } },
    /*119F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x052F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDMD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0530, { 0 } },
    /*11A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0531, { 0 } },
    /*11A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0532, { 0 } },
    /*11A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0533, { 0 } },
    /*11A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0534, { 0 } },
    /*11A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0535, { 0 } },
    /*11A6*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00FD, { 0 } },
    /*11A7*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00FE, { 0 } },
    /*11A8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x00FF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDMQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0536, { 0 } },
    /*11AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0537, { 0 } },
    /*11AB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0538, { 0 } },
    /*11AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0539, { 0 } },
    /*11AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x053A, { 0 } },
    /*11AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x053B, { 0 } },
    /*11AF*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0100, { 0 } },
    /*11B0*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0101, { 0 } },
    /*11B1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0102, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDMW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x053C, { 0 } },
    /*11B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x053D, { 0 } },
    /*11B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x053E, { 0 } },
    /*11B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x053F, { 0 } },
    /*11B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0540, { 0 } },
    /*11B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0541, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDVB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03CF, { 0 } },
    /*11B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D0, { 0 } },
    /*11BA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D1, { 0 } },
    /*11BB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBLENDW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11BC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D3, { 0 } },
    /*11BD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D4, { 0 } },
    /*11BE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D5, { 0 } },
    /*11BF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBROADCASTB                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11C0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D7, { 0 } },
    /*11C1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D8, { 0 } },
    /*11C2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03D9, { 0 } },
    /*11C3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03DA, { 0 } },
    /*11C4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0542, { 0 } },
    /*11C5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0543, { 0 } },
    /*11C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0544, { 0 } },
    /*11C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0545, { 0 } },
    /*11C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0546, { 0 } },
    /*11C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0547, { 0 } },
    /*11CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0548, { 0 } },
    /*11CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0549, { 0 } },
    /*11CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x054A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBROADCASTD                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11CD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03DB, { 0 } },
    /*11CE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03DC, { 0 } },
    /*11CF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03DD, { 0 } },
    /*11D0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03DE, { 0 } },
    /*11D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x054B, { 0 } },
    /*11D2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x054C, { 0 } },
    /*11D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x054D, { 0 } },
    /*11D4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x054E, { 0 } },
    /*11D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x054F, { 0 } },
    /*11D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0550, { 0 } },
    /*11D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0551, { 0 } },
    /*11D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0552, { 0 } },
    /*11D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0553, { 0 } },
    /*11DA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0103, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBROADCASTMB2Q                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0554, { 0 } },
    /*11DC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0555, { 0 } },
    /*11DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0556, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBROADCASTMW2D                                                                            */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0557, { 0 } },
    /*11DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0558, { 0 } },
    /*11E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0559, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBROADCASTQ                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11E1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03DF, { 0 } },
    /*11E2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E0, { 0 } },
    /*11E3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E1, { 0 } },
    /*11E4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E2, { 0 } },
    /*11E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x055A, { 0 } },
    /*11E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x055B, { 0 } },
    /*11E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x055C, { 0 } },
    /*11E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x055D, { 0 } },
    /*11E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x055E, { 0 } },
    /*11EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x055F, { 0 } },
    /*11EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0560, { 0 } },
    /*11EC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0561, { 0 } },
    /*11ED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0562, { 0 } },
    /*11EE*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0104, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPBROADCASTW                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11EF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E3, { 0 } },
    /*11F0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E4, { 0 } },
    /*11F1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E5, { 0 } },
    /*11F2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E6, { 0 } },
    /*11F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0563, { 0 } },
    /*11F4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0564, { 0 } },
    /*11F5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0565, { 0 } },
    /*11F6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0566, { 0 } },
    /*11F7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0567, { 0 } },
    /*11F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0568, { 0 } },
    /*11F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0569, { 0 } },
    /*11FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x056A, { 0 } },
    /*11FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x056B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCLMULQDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11FC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E7, { 0 } },
    /*11FD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMOV                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*11FE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x003A, { 0 } },
    /*11FF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x003B, { 0 } },
    /*1200*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x003C, { 0 } },
    /*1201*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x003D, { 0 } },
    /*1202*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x003E, { 0 } },
    /*1203*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x003F, { 0 } },
    /*1204*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0040, { 0 } },
    /*1205*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0041, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1206*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x056C, { 0 } },
    /*1207*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x056D, { 0 } },
    /*1208*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x056E, { 0 } },
    /*1209*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x056F, { 0 } },
    /*120A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0570, { 0 } },
    /*120B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0571, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*120C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0572, { 0 } },
    /*120D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0573, { 0 } },
    /*120E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0574, { 0 } },
    /*120F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0575, { 0 } },
    /*1210*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0576, { 0 } },
    /*1211*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0577, { 0 } },
    /*1212*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0105, { 0 } },
    /*1213*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0106, { 0 } },
    /*1214*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0107, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPEQB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1215*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03E9, { 0 } },
    /*1216*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03EA, { 0 } },
    /*1217*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03EB, { 0 } },
    /*1218*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03EC, { 0 } },
    /*1219*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0578, { 0 } },
    /*121A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0579, { 0 } },
    /*121B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x057A, { 0 } },
    /*121C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x057B, { 0 } },
    /*121D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x057C, { 0 } },
    /*121E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x057D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPEQD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*121F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03ED, { 0 } },
    /*1220*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03EE, { 0 } },
    /*1221*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03EF, { 0 } },
    /*1222*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F0, { 0 } },
    /*1223*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x057E, { 0 } },
    /*1224*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x057F, { 0 } },
    /*1225*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0580, { 0 } },
    /*1226*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0581, { 0 } },
    /*1227*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0582, { 0 } },
    /*1228*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0583, { 0 } },
    /*1229*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0108, { 0 } },
    /*122A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0109, { 0 } },
    /*122B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x010A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPEQQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*122C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F1, { 0 } },
    /*122D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F2, { 0 } },
    /*122E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F3, { 0 } },
    /*122F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F4, { 0 } },
    /*1230*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0584, { 0 } },
    /*1231*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0585, { 0 } },
    /*1232*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0586, { 0 } },
    /*1233*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0587, { 0 } },
    /*1234*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0588, { 0 } },
    /*1235*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0589, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPEQW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1236*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F5, { 0 } },
    /*1237*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F6, { 0 } },
    /*1238*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F7, { 0 } },
    /*1239*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F8, { 0 } },
    /*123A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x058A, { 0 } },
    /*123B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x058B, { 0 } },
    /*123C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x058C, { 0 } },
    /*123D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x058D, { 0 } },
    /*123E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x058E, { 0 } },
    /*123F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x058F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPESTRI                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1240*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03F9, { 0 } },
    /*1241*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03FA, { 0 } },
    /*1242*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03FB, { 0 } },
    /*1243*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03FC, { 0 } },
    /*1244*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03FD, { 0 } },
    /*1245*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03FE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPESTRM                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1246*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x03FF, { 0 } },
    /*1247*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0400, { 0 } },
    /*1248*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0401, { 0 } },
    /*1249*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0402, { 0 } },
    /*124A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0403, { 0 } },
    /*124B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0404, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPGTB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*124C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0405, { 0 } },
    /*124D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0406, { 0 } },
    /*124E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0407, { 0 } },
    /*124F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0408, { 0 } },
    /*1250*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0590, { 0 } },
    /*1251*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0591, { 0 } },
    /*1252*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0592, { 0 } },
    /*1253*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0593, { 0 } },
    /*1254*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0594, { 0 } },
    /*1255*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0595, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPGTD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1256*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0409, { 0 } },
    /*1257*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x040A, { 0 } },
    /*1258*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x040B, { 0 } },
    /*1259*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x040C, { 0 } },
    /*125A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0596, { 0 } },
    /*125B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0597, { 0 } },
    /*125C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0598, { 0 } },
    /*125D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0599, { 0 } },
    /*125E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x059A, { 0 } },
    /*125F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x059B, { 0 } },
    /*1260*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x010B, { 0 } },
    /*1261*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x010C, { 0 } },
    /*1262*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x010D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPGTQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1263*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x040D, { 0 } },
    /*1264*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x040E, { 0 } },
    /*1265*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x040F, { 0 } },
    /*1266*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0410, { 0 } },
    /*1267*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x059C, { 0 } },
    /*1268*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x059D, { 0 } },
    /*1269*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x059E, { 0 } },
    /*126A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x059F, { 0 } },
    /*126B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A0, { 0 } },
    /*126C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPGTW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*126D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0411, { 0 } },
    /*126E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0412, { 0 } },
    /*126F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0413, { 0 } },
    /*1270*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0414, { 0 } },
    /*1271*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A2, { 0 } },
    /*1272*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A3, { 0 } },
    /*1273*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A4, { 0 } },
    /*1274*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A5, { 0 } },
    /*1275*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A6, { 0 } },
    /*1276*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPISTRI                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1277*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0415, { 0 } },
    /*1278*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0416, { 0 } },
    /*1279*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0417, { 0 } },
    /*127A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0418, { 0 } },
    /*127B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0419, { 0 } },
    /*127C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x041A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPISTRM                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*127D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x041B, { 0 } },
    /*127E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x041C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPLTD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*127F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x010E, { 0 } },
    /*1280*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x010F, { 0 } },
    /*1281*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0110, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1282*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A8, { 0 } },
    /*1283*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05A9, { 0 } },
    /*1284*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05AA, { 0 } },
    /*1285*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05AB, { 0 } },
    /*1286*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05AC, { 0 } },
    /*1287*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05AD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPUB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1288*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05AE, { 0 } },
    /*1289*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05AF, { 0 } },
    /*128A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B0, { 0 } },
    /*128B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B1, { 0 } },
    /*128C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B2, { 0 } },
    /*128D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPUD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*128E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B4, { 0 } },
    /*128F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B5, { 0 } },
    /*1290*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B6, { 0 } },
    /*1291*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B7, { 0 } },
    /*1292*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B8, { 0 } },
    /*1293*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05B9, { 0 } },
    /*1294*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0111, { 0 } },
    /*1295*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0112, { 0 } },
    /*1296*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0113, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPUQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1297*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05BA, { 0 } },
    /*1298*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05BB, { 0 } },
    /*1299*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05BC, { 0 } },
    /*129A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05BD, { 0 } },
    /*129B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05BE, { 0 } },
    /*129C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05BF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPUW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*129D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C0, { 0 } },
    /*129E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C1, { 0 } },
    /*129F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C2, { 0 } },
    /*12A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C3, { 0 } },
    /*12A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C4, { 0 } },
    /*12A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCMPW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C6, { 0 } },
    /*12A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C7, { 0 } },
    /*12A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C8, { 0 } },
    /*12A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05C9, { 0 } },
    /*12A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05CA, { 0 } },
    /*12A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12A9*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0042, { 0 } },
    /*12AA*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0043, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12AB*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0044, { 0 } },
    /*12AC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0045, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMPRESSD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05CC, { 0 } },
    /*12AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05CD, { 0 } },
    /*12AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05CE, { 0 } },
    /*12B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05CF, { 0 } },
    /*12B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D0, { 0 } },
    /*12B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMPRESSQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D2, { 0 } },
    /*12B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D3, { 0 } },
    /*12B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D4, { 0 } },
    /*12B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D5, { 0 } },
    /*12B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D6, { 0 } },
    /*12B8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12B9*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0046, { 0 } },
    /*12BA*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0047, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMUB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12BB*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0048, { 0 } },
    /*12BC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0049, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMUD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12BD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x004A, { 0 } },
    /*12BE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x004B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMUQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12BF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x004C, { 0 } },
    /*12C0*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x004D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMUW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12C1*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x004E, { 0 } },
    /*12C2*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x004F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCOMW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12C3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0050, { 0 } },
    /*12C4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0051, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCONFLICTD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12C5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D8, { 0 } },
    /*12C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05D9, { 0 } },
    /*12C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05DA, { 0 } },
    /*12C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05DB, { 0 } },
    /*12C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05DC, { 0 } },
    /*12CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPCONFLICTQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05DE, { 0 } },
    /*12CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05DF, { 0 } },
    /*12CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E0, { 0 } },
    /*12CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E1, { 0 } },
    /*12CF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E2, { 0 } },
    /*12D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERM2F128                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12D1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x041D, { 0 } },
    /*12D2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x041E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERM2I128                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12D3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x041F, { 0 } },
    /*12D4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0420, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E4, { 0 } },
    /*12D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E5, { 0 } },
    /*12D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E6, { 0 } },
    /*12D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E7, { 0 } },
    /*12D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E8, { 0 } },
    /*12DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05E9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12DB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0421, { 0 } },
    /*12DC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0422, { 0 } },
    /*12DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05EA, { 0 } },
    /*12DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05EB, { 0 } },
    /*12DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05EC, { 0 } },
    /*12E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05ED, { 0 } },
    /*12E1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0114, { 0 } },
    /*12E2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0115, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMF32X4                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12E3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0116, { 0 } },
    /*12E4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0117, { 0 } },
    /*12E5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0118, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMI2B                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05EE, { 0 } },
    /*12E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05EF, { 0 } },
    /*12E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F0, { 0 } },
    /*12E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F1, { 0 } },
    /*12EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F2, { 0 } },
    /*12EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMI2D                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12EC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F4, { 0 } },
    /*12ED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F5, { 0 } },
    /*12EE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F6, { 0 } },
    /*12EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F7, { 0 } },
    /*12F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F8, { 0 } },
    /*12F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05F9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMI2PD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05FA, { 0 } },
    /*12F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05FB, { 0 } },
    /*12F4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05FC, { 0 } },
    /*12F5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05FD, { 0 } },
    /*12F6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05FE, { 0 } },
    /*12F7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x05FF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMI2PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0600, { 0 } },
    /*12F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0601, { 0 } },
    /*12FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0602, { 0 } },
    /*12FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0603, { 0 } },
    /*12FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0604, { 0 } },
    /*12FD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0605, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMI2Q                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*12FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0606, { 0 } },
    /*12FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0607, { 0 } },
    /*1300*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0608, { 0 } },
    /*1301*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0609, { 0 } },
    /*1302*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x060A, { 0 } },
    /*1303*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x060B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMI2W                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1304*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x060C, { 0 } },
    /*1305*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x060D, { 0 } },
    /*1306*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x060E, { 0 } },
    /*1307*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x060F, { 0 } },
    /*1308*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0610, { 0 } },
    /*1309*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0611, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMIL2PD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*130A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0423, { 0 } },
    /*130B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0424, { 0 } },
    /*130C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0425, { 0 } },
    /*130D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0426, { 0 } },
    /*130E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0427, { 0 } },
    /*130F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0428, { 0 } },
    /*1310*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0429, { 0 } },
    /*1311*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x042A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMIL2PS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1312*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x042B, { 0 } },
    /*1313*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x042C, { 0 } },
    /*1314*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x042D, { 0 } },
    /*1315*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x042E, { 0 } },
    /*1316*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x042F, { 0 } },
    /*1317*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0430, { 0 } },
    /*1318*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0431, { 0 } },
    /*1319*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0432, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMILPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*131A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0433, { 0 } },
    /*131B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0434, { 0 } },
    /*131C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0435, { 0 } },
    /*131D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0436, { 0 } },
    /*131E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0437, { 0 } },
    /*131F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0438, { 0 } },
    /*1320*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0439, { 0 } },
    /*1321*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x043A, { 0 } },
    /*1322*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0612, { 0 } },
    /*1323*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0613, { 0 } },
    /*1324*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0614, { 0 } },
    /*1325*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0615, { 0 } },
    /*1326*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0616, { 0 } },
    /*1327*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0617, { 0 } },
    /*1328*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0618, { 0 } },
    /*1329*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0619, { 0 } },
    /*132A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x061A, { 0 } },
    /*132B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x061B, { 0 } },
    /*132C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x061C, { 0 } },
    /*132D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x061D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMILPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*132E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x043B, { 0 } },
    /*132F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x043C, { 0 } },
    /*1330*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x043D, { 0 } },
    /*1331*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x043E, { 0 } },
    /*1332*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x043F, { 0 } },
    /*1333*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0440, { 0 } },
    /*1334*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0441, { 0 } },
    /*1335*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0442, { 0 } },
    /*1336*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x061E, { 0 } },
    /*1337*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x061F, { 0 } },
    /*1338*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0620, { 0 } },
    /*1339*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0621, { 0 } },
    /*133A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0622, { 0 } },
    /*133B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0623, { 0 } },
    /*133C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0624, { 0 } },
    /*133D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0625, { 0 } },
    /*133E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0626, { 0 } },
    /*133F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0627, { 0 } },
    /*1340*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0628, { 0 } },
    /*1341*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0629, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1342*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0443, { 0 } },
    /*1343*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0444, { 0 } },
    /*1344*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x062A, { 0 } },
    /*1345*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x062B, { 0 } },
    /*1346*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x062C, { 0 } },
    /*1347*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x062D, { 0 } },
    /*1348*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x062E, { 0 } },
    /*1349*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x062F, { 0 } },
    /*134A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0630, { 0 } },
    /*134B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0631, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*134C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0445, { 0 } },
    /*134D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0446, { 0 } },
    /*134E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0632, { 0 } },
    /*134F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0633, { 0 } },
    /*1350*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0634, { 0 } },
    /*1351*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0635, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1352*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0447, { 0 } },
    /*1353*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0448, { 0 } },
    /*1354*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0636, { 0 } },
    /*1355*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0637, { 0 } },
    /*1356*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0638, { 0 } },
    /*1357*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0639, { 0 } },
    /*1358*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x063A, { 0 } },
    /*1359*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x063B, { 0 } },
    /*135A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x063C, { 0 } },
    /*135B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x063D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMT2B                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*135C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x063E, { 0 } },
    /*135D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x063F, { 0 } },
    /*135E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0640, { 0 } },
    /*135F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0641, { 0 } },
    /*1360*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0642, { 0 } },
    /*1361*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0643, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMT2D                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1362*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0644, { 0 } },
    /*1363*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0645, { 0 } },
    /*1364*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0646, { 0 } },
    /*1365*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0647, { 0 } },
    /*1366*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0648, { 0 } },
    /*1367*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0649, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMT2PD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1368*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x064A, { 0 } },
    /*1369*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x064B, { 0 } },
    /*136A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x064C, { 0 } },
    /*136B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x064D, { 0 } },
    /*136C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x064E, { 0 } },
    /*136D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x064F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMT2PS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*136E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0650, { 0 } },
    /*136F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0651, { 0 } },
    /*1370*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0652, { 0 } },
    /*1371*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0653, { 0 } },
    /*1372*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0654, { 0 } },
    /*1373*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0655, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMT2Q                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1374*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0656, { 0 } },
    /*1375*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0657, { 0 } },
    /*1376*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0658, { 0 } },
    /*1377*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0659, { 0 } },
    /*1378*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x065A, { 0 } },
    /*1379*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x065B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMT2W                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*137A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x065C, { 0 } },
    /*137B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x065D, { 0 } },
    /*137C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x065E, { 0 } },
    /*137D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x065F, { 0 } },
    /*137E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0660, { 0 } },
    /*137F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0661, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPERMW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1380*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0662, { 0 } },
    /*1381*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0663, { 0 } },
    /*1382*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0664, { 0 } },
    /*1383*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0665, { 0 } },
    /*1384*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0666, { 0 } },
    /*1385*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0667, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPEXPANDD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1386*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0668, { 0 } },
    /*1387*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0669, { 0 } },
    /*1388*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x066A, { 0 } },
    /*1389*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x066B, { 0 } },
    /*138A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x066C, { 0 } },
    /*138B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x066D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPEXPANDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*138C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x066E, { 0 } },
    /*138D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x066F, { 0 } },
    /*138E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0670, { 0 } },
    /*138F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0671, { 0 } },
    /*1390*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0672, { 0 } },
    /*1391*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0673, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPEXTRB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1392*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0449, { 0 } },
    /*1393*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x044A, { 0 } },
    /*1394*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0674, { 0 } },
    /*1395*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0675, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPEXTRD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1396*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x044B, { 0 } },
    /*1397*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x044C, { 0 } },
    /*1398*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x044D, { 0 } },
    /*1399*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x044E, { 0 } },
    /*139A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0676, { 0 } },
    /*139B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0677, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPEXTRQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*139C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x044F, { 0 } },
    /*139D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0450, { 0 } },
    /*139E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0678, { 0 } },
    /*139F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0679, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPEXTRW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13A0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0451, { 0 } },
    /*13A1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0452, { 0 } },
    /*13A2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0453, { 0 } },
    /*13A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x067A, { 0 } },
    /*13A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x067B, { 0 } },
    /*13A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x067C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPGATHERDD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13A6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0454, { 0 } },
    /*13A7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0455, { 0 } },
    /*13A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x067D, { 0 } },
    /*13A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x067E, { 0 } },
    /*13AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x067F, { 0 } },
    /*13AB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0119, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPGATHERDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13AC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0456, { 0 } },
    /*13AD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0457, { 0 } },
    /*13AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0680, { 0 } },
    /*13AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0681, { 0 } },
    /*13B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0682, { 0 } },
    /*13B1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x011A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPGATHERQD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13B2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0458, { 0 } },
    /*13B3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0459, { 0 } },
    /*13B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0683, { 0 } },
    /*13B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0684, { 0 } },
    /*13B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0685, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPGATHERQQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13B7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x045A, { 0 } },
    /*13B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x045B, { 0 } },
    /*13B9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0686, { 0 } },
    /*13BA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0687, { 0 } },
    /*13BB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0688, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDBD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13BC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0052, { 0 } },
    /*13BD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0053, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDBQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13BE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0054, { 0 } },
    /*13BF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0055, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDBW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13C0*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0056, { 0 } },
    /*13C1*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0057, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13C2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x045C, { 0 } },
    /*13C3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x045D, { 0 } },
    /*13C4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x045E, { 0 } },
    /*13C5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x045F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13C6*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0058, { 0 } },
    /*13C7*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0059, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDSW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13C8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0460, { 0 } },
    /*13C9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0461, { 0 } },
    /*13CA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0462, { 0 } },
    /*13CB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0463, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDUBD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13CC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x005A, { 0 } },
    /*13CD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x005B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDUBQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13CE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x005C, { 0 } },
    /*13CF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x005D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDUBW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13D0*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x005E, { 0 } },
    /*13D1*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x005F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDUDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13D2*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0060, { 0 } },
    /*13D3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0061, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDUWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13D4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0062, { 0 } },
    /*13D5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0063, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDUWQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13D6*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0064, { 0 } },
    /*13D7*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0065, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13D8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0464, { 0 } },
    /*13D9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0465, { 0 } },
    /*13DA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0466, { 0 } },
    /*13DB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0467, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13DC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0066, { 0 } },
    /*13DD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0067, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHADDWQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13DE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0068, { 0 } },
    /*13DF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0069, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHMINPOSUW                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13E0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0468, { 0 } },
    /*13E1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0469, { 0 } },
    /*13E2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x046A, { 0 } },
    /*13E3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x046B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHSUBBW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13E4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x006A, { 0 } },
    /*13E5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x006B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHSUBD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13E6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x046C, { 0 } },
    /*13E7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x046D, { 0 } },
    /*13E8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x046E, { 0 } },
    /*13E9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x046F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHSUBDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13EA*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x006C, { 0 } },
    /*13EB*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x006D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHSUBSW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13EC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0470, { 0 } },
    /*13ED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0471, { 0 } },
    /*13EE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0472, { 0 } },
    /*13EF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0473, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHSUBW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13F0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0474, { 0 } },
    /*13F1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0475, { 0 } },
    /*13F2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0476, { 0 } },
    /*13F3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0477, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPHSUBWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13F4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x006E, { 0 } },
    /*13F5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x006F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPINSRB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13F6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0478, { 0 } },
    /*13F7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0479, { 0 } },
    /*13F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0689, { 0 } },
    /*13F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x068A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPINSRD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*13FA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x047A, { 0 } },
    /*13FB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x047B, { 0 } },
    /*13FC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x047C, { 0 } },
    /*13FD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x047D, { 0 } },
    /*13FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x068B, { 0 } },
    /*13FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x068C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPINSRQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1400*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x047E, { 0 } },
    /*1401*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x047F, { 0 } },
    /*1402*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x068D, { 0 } },
    /*1403*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x068E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPINSRW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1404*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0480, { 0 } },
    /*1405*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0481, { 0 } },
    /*1406*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x068F, { 0 } },
    /*1407*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0690, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPLZCNTD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1408*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0691, { 0 } },
    /*1409*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0692, { 0 } },
    /*140A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0693, { 0 } },
    /*140B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0694, { 0 } },
    /*140C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0695, { 0 } },
    /*140D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0696, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPLZCNTQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*140E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0697, { 0 } },
    /*140F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0698, { 0 } },
    /*1410*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0699, { 0 } },
    /*1411*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x069A, { 0 } },
    /*1412*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x069B, { 0 } },
    /*1413*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x069C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSDD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1414*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0070, { 0 } },
    /*1415*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0071, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSDQH                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1416*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0072, { 0 } },
    /*1417*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0073, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSDQL                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1418*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0074, { 0 } },
    /*1419*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0075, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSSDD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*141A*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0076, { 0 } },
    /*141B*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0077, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSSDQH                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*141C*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0078, { 0 } },
    /*141D*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0079, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSSDQL                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*141E*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x007A, { 0 } },
    /*141F*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x007B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSSWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1420*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x007C, { 0 } },
    /*1421*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x007D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSSWW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1422*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x007E, { 0 } },
    /*1423*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x007F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1424*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0080, { 0 } },
    /*1425*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0081, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMACSWW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1426*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0082, { 0 } },
    /*1427*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0083, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADCSSWD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1428*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0084, { 0 } },
    /*1429*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0085, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADCSWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*142A*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0086, { 0 } },
    /*142B*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0087, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADD231D                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*142C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x011B, { 0 } },
    /*142D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x011C, { 0 } },
    /*142E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x011D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADD233D                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*142F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x011E, { 0 } },
    /*1430*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x011F, { 0 } },
    /*1431*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0120, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADD52HUQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1432*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x069D, { 0 } },
    /*1433*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x069E, { 0 } },
    /*1434*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x069F, { 0 } },
    /*1435*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A0, { 0 } },
    /*1436*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A1, { 0 } },
    /*1437*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADD52LUQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1438*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A3, { 0 } },
    /*1439*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A4, { 0 } },
    /*143A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A5, { 0 } },
    /*143B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A6, { 0 } },
    /*143C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A7, { 0 } },
    /*143D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADDUBSW                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*143E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0482, { 0 } },
    /*143F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0483, { 0 } },
    /*1440*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0484, { 0 } },
    /*1441*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0485, { 0 } },
    /*1442*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06A9, { 0 } },
    /*1443*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06AA, { 0 } },
    /*1444*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06AB, { 0 } },
    /*1445*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06AC, { 0 } },
    /*1446*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06AD, { 0 } },
    /*1447*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06AE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMADDWD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1448*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0486, { 0 } },
    /*1449*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0487, { 0 } },
    /*144A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0488, { 0 } },
    /*144B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0489, { 0 } },
    /*144C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06AF, { 0 } },
    /*144D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B0, { 0 } },
    /*144E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B1, { 0 } },
    /*144F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B2, { 0 } },
    /*1450*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B3, { 0 } },
    /*1451*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMASKMOVD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1452*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x048A, { 0 } },
    /*1453*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x048B, { 0 } },
    /*1454*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x048C, { 0 } },
    /*1455*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x048D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMASKMOVQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1456*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x048E, { 0 } },
    /*1457*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x048F, { 0 } },
    /*1458*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0490, { 0 } },
    /*1459*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0491, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*145A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0492, { 0 } },
    /*145B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0493, { 0 } },
    /*145C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0494, { 0 } },
    /*145D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0495, { 0 } },
    /*145E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B5, { 0 } },
    /*145F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B6, { 0 } },
    /*1460*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B7, { 0 } },
    /*1461*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B8, { 0 } },
    /*1462*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06B9, { 0 } },
    /*1463*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06BA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXSD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1464*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0496, { 0 } },
    /*1465*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0497, { 0 } },
    /*1466*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0498, { 0 } },
    /*1467*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0499, { 0 } },
    /*1468*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06BB, { 0 } },
    /*1469*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06BC, { 0 } },
    /*146A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06BD, { 0 } },
    /*146B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06BE, { 0 } },
    /*146C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06BF, { 0 } },
    /*146D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C0, { 0 } },
    /*146E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0121, { 0 } },
    /*146F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0122, { 0 } },
    /*1470*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0123, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXSQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1471*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C1, { 0 } },
    /*1472*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C2, { 0 } },
    /*1473*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C3, { 0 } },
    /*1474*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C4, { 0 } },
    /*1475*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C5, { 0 } },
    /*1476*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1477*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x049A, { 0 } },
    /*1478*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x049B, { 0 } },
    /*1479*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x049C, { 0 } },
    /*147A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x049D, { 0 } },
    /*147B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C7, { 0 } },
    /*147C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C8, { 0 } },
    /*147D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06C9, { 0 } },
    /*147E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06CA, { 0 } },
    /*147F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06CB, { 0 } },
    /*1480*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06CC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXUB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1481*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x049E, { 0 } },
    /*1482*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x049F, { 0 } },
    /*1483*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A0, { 0 } },
    /*1484*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A1, { 0 } },
    /*1485*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06CD, { 0 } },
    /*1486*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06CE, { 0 } },
    /*1487*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06CF, { 0 } },
    /*1488*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D0, { 0 } },
    /*1489*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D1, { 0 } },
    /*148A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXUD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*148B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A2, { 0 } },
    /*148C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A3, { 0 } },
    /*148D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A4, { 0 } },
    /*148E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A5, { 0 } },
    /*148F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D3, { 0 } },
    /*1490*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D4, { 0 } },
    /*1491*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D5, { 0 } },
    /*1492*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D6, { 0 } },
    /*1493*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D7, { 0 } },
    /*1494*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D8, { 0 } },
    /*1495*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0124, { 0 } },
    /*1496*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0125, { 0 } },
    /*1497*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0126, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXUQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1498*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06D9, { 0 } },
    /*1499*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06DA, { 0 } },
    /*149A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06DB, { 0 } },
    /*149B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06DC, { 0 } },
    /*149C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06DD, { 0 } },
    /*149D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06DE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMAXUW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*149E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A6, { 0 } },
    /*149F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A7, { 0 } },
    /*14A0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A8, { 0 } },
    /*14A1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04A9, { 0 } },
    /*14A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06DF, { 0 } },
    /*14A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E0, { 0 } },
    /*14A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E1, { 0 } },
    /*14A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E2, { 0 } },
    /*14A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E3, { 0 } },
    /*14A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14A8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04AA, { 0 } },
    /*14A9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04AB, { 0 } },
    /*14AA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04AC, { 0 } },
    /*14AB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04AD, { 0 } },
    /*14AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E5, { 0 } },
    /*14AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E6, { 0 } },
    /*14AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E7, { 0 } },
    /*14AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E8, { 0 } },
    /*14B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06E9, { 0 } },
    /*14B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06EA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINSD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14B2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04AE, { 0 } },
    /*14B3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04AF, { 0 } },
    /*14B4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B0, { 0 } },
    /*14B5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B1, { 0 } },
    /*14B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06EB, { 0 } },
    /*14B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06EC, { 0 } },
    /*14B8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06ED, { 0 } },
    /*14B9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06EE, { 0 } },
    /*14BA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06EF, { 0 } },
    /*14BB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F0, { 0 } },
    /*14BC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0127, { 0 } },
    /*14BD*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0128, { 0 } },
    /*14BE*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0129, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINSQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F1, { 0 } },
    /*14C0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F2, { 0 } },
    /*14C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F3, { 0 } },
    /*14C2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F4, { 0 } },
    /*14C3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F5, { 0 } },
    /*14C4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14C5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B2, { 0 } },
    /*14C6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B3, { 0 } },
    /*14C7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B4, { 0 } },
    /*14C8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B5, { 0 } },
    /*14C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F7, { 0 } },
    /*14CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F8, { 0 } },
    /*14CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06F9, { 0 } },
    /*14CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06FA, { 0 } },
    /*14CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06FB, { 0 } },
    /*14CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06FC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINUB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14CF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B6, { 0 } },
    /*14D0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B7, { 0 } },
    /*14D1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B8, { 0 } },
    /*14D2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04B9, { 0 } },
    /*14D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06FD, { 0 } },
    /*14D4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06FE, { 0 } },
    /*14D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x06FF, { 0 } },
    /*14D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0700, { 0 } },
    /*14D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0701, { 0 } },
    /*14D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0702, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINUD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14D9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04BA, { 0 } },
    /*14DA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04BB, { 0 } },
    /*14DB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04BC, { 0 } },
    /*14DC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04BD, { 0 } },
    /*14DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0703, { 0 } },
    /*14DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0704, { 0 } },
    /*14DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0705, { 0 } },
    /*14E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0706, { 0 } },
    /*14E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0707, { 0 } },
    /*14E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0708, { 0 } },
    /*14E3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x012A, { 0 } },
    /*14E4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x012B, { 0 } },
    /*14E5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x012C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINUQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0709, { 0 } },
    /*14E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x070A, { 0 } },
    /*14E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x070B, { 0 } },
    /*14E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x070C, { 0 } },
    /*14EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x070D, { 0 } },
    /*14EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x070E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMINUW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14EC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04BE, { 0 } },
    /*14ED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04BF, { 0 } },
    /*14EE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C0, { 0 } },
    /*14EF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C1, { 0 } },
    /*14F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x070F, { 0 } },
    /*14F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0710, { 0 } },
    /*14F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0711, { 0 } },
    /*14F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0712, { 0 } },
    /*14F4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0713, { 0 } },
    /*14F5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0714, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVB2M                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14F6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0715, { 0 } },
    /*14F7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0716, { 0 } },
    /*14F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0717, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVD2M                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0718, { 0 } },
    /*14FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0719, { 0 } },
    /*14FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x071A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVDB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*14FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x071B, { 0 } },
    /*14FD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x071C, { 0 } },
    /*14FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x071D, { 0 } },
    /*14FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x071E, { 0 } },
    /*1500*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x071F, { 0 } },
    /*1501*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0720, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVDW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1502*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0721, { 0 } },
    /*1503*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0722, { 0 } },
    /*1504*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0723, { 0 } },
    /*1505*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0724, { 0 } },
    /*1506*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0725, { 0 } },
    /*1507*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0726, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVM2B                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1508*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0727, { 0 } },
    /*1509*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0728, { 0 } },
    /*150A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0729, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVM2D                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*150B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x072A, { 0 } },
    /*150C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x072B, { 0 } },
    /*150D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x072C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVM2Q                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*150E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x072D, { 0 } },
    /*150F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x072E, { 0 } },
    /*1510*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x072F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVM2W                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1511*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0730, { 0 } },
    /*1512*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0731, { 0 } },
    /*1513*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0732, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVMSKB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1514*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C2, { 0 } },
    /*1515*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVQ2M                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1516*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0733, { 0 } },
    /*1517*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0734, { 0 } },
    /*1518*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0735, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVQB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1519*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0736, { 0 } },
    /*151A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0737, { 0 } },
    /*151B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0738, { 0 } },
    /*151C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0739, { 0 } },
    /*151D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x073A, { 0 } },
    /*151E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x073B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVQD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*151F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x073C, { 0 } },
    /*1520*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x073D, { 0 } },
    /*1521*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x073E, { 0 } },
    /*1522*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x073F, { 0 } },
    /*1523*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0740, { 0 } },
    /*1524*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0741, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVQW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1525*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0742, { 0 } },
    /*1526*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0743, { 0 } },
    /*1527*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0744, { 0 } },
    /*1528*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0745, { 0 } },
    /*1529*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0746, { 0 } },
    /*152A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0747, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSDB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*152B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0748, { 0 } },
    /*152C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0749, { 0 } },
    /*152D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x074A, { 0 } },
    /*152E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x074B, { 0 } },
    /*152F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x074C, { 0 } },
    /*1530*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x074D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSDW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1531*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x074E, { 0 } },
    /*1532*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x074F, { 0 } },
    /*1533*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0750, { 0 } },
    /*1534*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0751, { 0 } },
    /*1535*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0752, { 0 } },
    /*1536*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0753, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSQB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1537*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0754, { 0 } },
    /*1538*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0755, { 0 } },
    /*1539*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0756, { 0 } },
    /*153A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0757, { 0 } },
    /*153B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0758, { 0 } },
    /*153C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0759, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSQD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*153D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x075A, { 0 } },
    /*153E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x075B, { 0 } },
    /*153F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x075C, { 0 } },
    /*1540*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x075D, { 0 } },
    /*1541*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x075E, { 0 } },
    /*1542*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x075F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSQW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1543*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0760, { 0 } },
    /*1544*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0761, { 0 } },
    /*1545*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0762, { 0 } },
    /*1546*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0763, { 0 } },
    /*1547*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0764, { 0 } },
    /*1548*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0765, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSWB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1549*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0766, { 0 } },
    /*154A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0767, { 0 } },
    /*154B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0768, { 0 } },
    /*154C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0769, { 0 } },
    /*154D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x076A, { 0 } },
    /*154E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x076B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSXBD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*154F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C4, { 0 } },
    /*1550*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C5, { 0 } },
    /*1551*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C6, { 0 } },
    /*1552*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C7, { 0 } },
    /*1553*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x076C, { 0 } },
    /*1554*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x076D, { 0 } },
    /*1555*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x076E, { 0 } },
    /*1556*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x076F, { 0 } },
    /*1557*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0770, { 0 } },
    /*1558*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0771, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSXBQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1559*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C8, { 0 } },
    /*155A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04C9, { 0 } },
    /*155B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04CA, { 0 } },
    /*155C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04CB, { 0 } },
    /*155D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0772, { 0 } },
    /*155E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0773, { 0 } },
    /*155F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0774, { 0 } },
    /*1560*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0775, { 0 } },
    /*1561*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0776, { 0 } },
    /*1562*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0777, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSXBW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1563*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04CC, { 0 } },
    /*1564*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04CD, { 0 } },
    /*1565*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04CE, { 0 } },
    /*1566*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04CF, { 0 } },
    /*1567*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0778, { 0 } },
    /*1568*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0779, { 0 } },
    /*1569*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x077A, { 0 } },
    /*156A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x077B, { 0 } },
    /*156B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x077C, { 0 } },
    /*156C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x077D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSXDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*156D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D0, { 0 } },
    /*156E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D1, { 0 } },
    /*156F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D2, { 0 } },
    /*1570*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D3, { 0 } },
    /*1571*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x077E, { 0 } },
    /*1572*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x077F, { 0 } },
    /*1573*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0780, { 0 } },
    /*1574*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0781, { 0 } },
    /*1575*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0782, { 0 } },
    /*1576*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0783, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSXWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1577*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D4, { 0 } },
    /*1578*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D5, { 0 } },
    /*1579*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D6, { 0 } },
    /*157A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D7, { 0 } },
    /*157B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0784, { 0 } },
    /*157C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0785, { 0 } },
    /*157D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0786, { 0 } },
    /*157E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0787, { 0 } },
    /*157F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0788, { 0 } },
    /*1580*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0789, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVSXWQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1581*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D8, { 0 } },
    /*1582*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04D9, { 0 } },
    /*1583*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04DA, { 0 } },
    /*1584*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04DB, { 0 } },
    /*1585*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x078A, { 0 } },
    /*1586*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x078B, { 0 } },
    /*1587*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x078C, { 0 } },
    /*1588*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x078D, { 0 } },
    /*1589*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x078E, { 0 } },
    /*158A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x078F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVUSDB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*158B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0790, { 0 } },
    /*158C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0791, { 0 } },
    /*158D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0792, { 0 } },
    /*158E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0793, { 0 } },
    /*158F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0794, { 0 } },
    /*1590*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0795, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVUSDW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1591*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0796, { 0 } },
    /*1592*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0797, { 0 } },
    /*1593*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0798, { 0 } },
    /*1594*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0799, { 0 } },
    /*1595*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x079A, { 0 } },
    /*1596*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x079B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVUSQB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1597*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x079C, { 0 } },
    /*1598*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x079D, { 0 } },
    /*1599*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x079E, { 0 } },
    /*159A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x079F, { 0 } },
    /*159B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A0, { 0 } },
    /*159C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVUSQD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*159D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A2, { 0 } },
    /*159E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A3, { 0 } },
    /*159F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A4, { 0 } },
    /*15A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A5, { 0 } },
    /*15A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A6, { 0 } },
    /*15A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVUSQW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A8, { 0 } },
    /*15A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07A9, { 0 } },
    /*15A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07AA, { 0 } },
    /*15A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07AB, { 0 } },
    /*15A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07AC, { 0 } },
    /*15A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07AD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVUSWB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07AE, { 0 } },
    /*15AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07AF, { 0 } },
    /*15AB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B0, { 0 } },
    /*15AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B1, { 0 } },
    /*15AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B2, { 0 } },
    /*15AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVW2M                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B4, { 0 } },
    /*15B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B5, { 0 } },
    /*15B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVWB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B7, { 0 } },
    /*15B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B8, { 0 } },
    /*15B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07B9, { 0 } },
    /*15B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07BA, { 0 } },
    /*15B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07BB, { 0 } },
    /*15B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07BC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVZXBD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04DC, { 0 } },
    /*15B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04DD, { 0 } },
    /*15BA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04DE, { 0 } },
    /*15BB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04DF, { 0 } },
    /*15BC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07BD, { 0 } },
    /*15BD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07BE, { 0 } },
    /*15BE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07BF, { 0 } },
    /*15BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C0, { 0 } },
    /*15C0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C1, { 0 } },
    /*15C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVZXBQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15C2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E0, { 0 } },
    /*15C3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E1, { 0 } },
    /*15C4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E2, { 0 } },
    /*15C5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E3, { 0 } },
    /*15C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C3, { 0 } },
    /*15C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C4, { 0 } },
    /*15C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C5, { 0 } },
    /*15C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C6, { 0 } },
    /*15CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C7, { 0 } },
    /*15CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVZXBW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15CC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E4, { 0 } },
    /*15CD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E5, { 0 } },
    /*15CE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E6, { 0 } },
    /*15CF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E7, { 0 } },
    /*15D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07C9, { 0 } },
    /*15D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07CA, { 0 } },
    /*15D2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07CB, { 0 } },
    /*15D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07CC, { 0 } },
    /*15D4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07CD, { 0 } },
    /*15D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07CE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVZXDQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15D6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E8, { 0 } },
    /*15D7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04E9, { 0 } },
    /*15D8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04EA, { 0 } },
    /*15D9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04EB, { 0 } },
    /*15DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07CF, { 0 } },
    /*15DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D0, { 0 } },
    /*15DC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D1, { 0 } },
    /*15DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D2, { 0 } },
    /*15DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D3, { 0 } },
    /*15DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVZXWD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15E0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04EC, { 0 } },
    /*15E1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04ED, { 0 } },
    /*15E2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04EE, { 0 } },
    /*15E3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04EF, { 0 } },
    /*15E4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D5, { 0 } },
    /*15E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D6, { 0 } },
    /*15E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D7, { 0 } },
    /*15E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D8, { 0 } },
    /*15E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07D9, { 0 } },
    /*15E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07DA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMOVZXWQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15EA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F0, { 0 } },
    /*15EB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F1, { 0 } },
    /*15EC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F2, { 0 } },
    /*15ED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F3, { 0 } },
    /*15EE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07DB, { 0 } },
    /*15EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07DC, { 0 } },
    /*15F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07DD, { 0 } },
    /*15F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07DE, { 0 } },
    /*15F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07DF, { 0 } },
    /*15F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULDQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15F4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F4, { 0 } },
    /*15F5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F5, { 0 } },
    /*15F6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F6, { 0 } },
    /*15F7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F7, { 0 } },
    /*15F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E1, { 0 } },
    /*15F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E2, { 0 } },
    /*15FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E3, { 0 } },
    /*15FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E4, { 0 } },
    /*15FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E5, { 0 } },
    /*15FD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULHD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*15FE*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x012D, { 0 } },
    /*15FF*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x012E, { 0 } },
    /*1600*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x012F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULHRSW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1601*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F8, { 0 } },
    /*1602*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04F9, { 0 } },
    /*1603*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04FA, { 0 } },
    /*1604*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04FB, { 0 } },
    /*1605*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E7, { 0 } },
    /*1606*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E8, { 0 } },
    /*1607*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07E9, { 0 } },
    /*1608*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07EA, { 0 } },
    /*1609*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07EB, { 0 } },
    /*160A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07EC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULHUD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*160B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0130, { 0 } },
    /*160C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0131, { 0 } },
    /*160D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0132, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULHUW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*160E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04FC, { 0 } },
    /*160F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04FD, { 0 } },
    /*1610*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04FE, { 0 } },
    /*1611*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x04FF, { 0 } },
    /*1612*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07ED, { 0 } },
    /*1613*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07EE, { 0 } },
    /*1614*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07EF, { 0 } },
    /*1615*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F0, { 0 } },
    /*1616*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F1, { 0 } },
    /*1617*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULHW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1618*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0500, { 0 } },
    /*1619*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0501, { 0 } },
    /*161A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0502, { 0 } },
    /*161B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0503, { 0 } },
    /*161C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F3, { 0 } },
    /*161D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F4, { 0 } },
    /*161E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F5, { 0 } },
    /*161F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F6, { 0 } },
    /*1620*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F7, { 0 } },
    /*1621*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULLD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1622*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0504, { 0 } },
    /*1623*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0505, { 0 } },
    /*1624*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0506, { 0 } },
    /*1625*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0507, { 0 } },
    /*1626*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07F9, { 0 } },
    /*1627*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07FA, { 0 } },
    /*1628*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07FB, { 0 } },
    /*1629*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07FC, { 0 } },
    /*162A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07FD, { 0 } },
    /*162B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07FE, { 0 } },
    /*162C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0133, { 0 } },
    /*162D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0134, { 0 } },
    /*162E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0135, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULLQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*162F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x07FF, { 0 } },
    /*1630*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0800, { 0 } },
    /*1631*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0801, { 0 } },
    /*1632*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0802, { 0 } },
    /*1633*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0803, { 0 } },
    /*1634*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0804, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULLW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1635*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0508, { 0 } },
    /*1636*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0509, { 0 } },
    /*1637*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x050A, { 0 } },
    /*1638*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x050B, { 0 } },
    /*1639*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0805, { 0 } },
    /*163A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0806, { 0 } },
    /*163B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0807, { 0 } },
    /*163C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0808, { 0 } },
    /*163D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0809, { 0 } },
    /*163E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x080A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULTISHIFTQB                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*163F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x080B, { 0 } },
    /*1640*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x080C, { 0 } },
    /*1641*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x080D, { 0 } },
    /*1642*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x080E, { 0 } },
    /*1643*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x080F, { 0 } },
    /*1644*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0810, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPMULUDQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1645*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x050C, { 0 } },
    /*1646*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x050D, { 0 } },
    /*1647*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x050E, { 0 } },
    /*1648*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x050F, { 0 } },
    /*1649*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0811, { 0 } },
    /*164A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0812, { 0 } },
    /*164B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0813, { 0 } },
    /*164C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0814, { 0 } },
    /*164D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0815, { 0 } },
    /*164E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0816, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPOPCNTD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*164F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0817, { 0 } },
    /*1650*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0818, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPOPCNTQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1651*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0819, { 0 } },
    /*1652*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x081A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPOR                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1653*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0510, { 0 } },
    /*1654*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0511, { 0 } },
    /*1655*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0512, { 0 } },
    /*1656*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0513, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPORD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1657*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x081B, { 0 } },
    /*1658*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x081C, { 0 } },
    /*1659*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x081D, { 0 } },
    /*165A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x081E, { 0 } },
    /*165B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x081F, { 0 } },
    /*165C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0820, { 0 } },
    /*165D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0136, { 0 } },
    /*165E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0137, { 0 } },
    /*165F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0138, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPORQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1660*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0821, { 0 } },
    /*1661*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0822, { 0 } },
    /*1662*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0823, { 0 } },
    /*1663*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0824, { 0 } },
    /*1664*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0825, { 0 } },
    /*1665*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0826, { 0 } },
    /*1666*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0139, { 0 } },
    /*1667*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x013A, { 0 } },
    /*1668*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x013B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPPERM                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1669*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0088, { 0 } },
    /*166A*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0089, { 0 } },
    /*166B*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x008A, { 0 } },
    /*166C*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x008B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCH0                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*166D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0514, { 0 } },
    /*166E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x013C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCH1                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*166F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0515, { 0 } },
    /*1670*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x013D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCH2                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1671*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0516, { 0 } },
    /*1672*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x013E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCHE0                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1673*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0517, { 0 } },
    /*1674*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x013F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCHE1                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1675*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0518, { 0 } },
    /*1676*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0140, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCHE2                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1677*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0519, { 0 } },
    /*1678*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0141, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCHENTA                                                                              */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1679*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x051A, { 0 } },
    /*167A*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0142, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPREFETCHNTA                                                                               */ 
    /* ------------------------------------------------------------------------------------------ */
    /*167B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x051B, { 0 } },
    /*167C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0143, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROLD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*167D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0827, { 0 } },
    /*167E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0828, { 0 } },
    /*167F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0829, { 0 } },
    /*1680*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x082A, { 0 } },
    /*1681*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x082B, { 0 } },
    /*1682*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x082C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROLQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1683*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x082D, { 0 } },
    /*1684*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x082E, { 0 } },
    /*1685*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x082F, { 0 } },
    /*1686*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0830, { 0 } },
    /*1687*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0831, { 0 } },
    /*1688*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0832, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROLVD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1689*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0833, { 0 } },
    /*168A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0834, { 0 } },
    /*168B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0835, { 0 } },
    /*168C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0836, { 0 } },
    /*168D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0837, { 0 } },
    /*168E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0838, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROLVQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*168F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0839, { 0 } },
    /*1690*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x083A, { 0 } },
    /*1691*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x083B, { 0 } },
    /*1692*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x083C, { 0 } },
    /*1693*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x083D, { 0 } },
    /*1694*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x083E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPRORD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1695*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x083F, { 0 } },
    /*1696*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0840, { 0 } },
    /*1697*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0841, { 0 } },
    /*1698*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0842, { 0 } },
    /*1699*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0843, { 0 } },
    /*169A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0844, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPRORQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*169B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0845, { 0 } },
    /*169C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0846, { 0 } },
    /*169D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0847, { 0 } },
    /*169E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0848, { 0 } },
    /*169F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0849, { 0 } },
    /*16A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x084A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPRORVD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x084B, { 0 } },
    /*16A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x084C, { 0 } },
    /*16A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x084D, { 0 } },
    /*16A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x084E, { 0 } },
    /*16A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x084F, { 0 } },
    /*16A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0850, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPRORVQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0851, { 0 } },
    /*16A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0852, { 0 } },
    /*16A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0853, { 0 } },
    /*16AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0854, { 0 } },
    /*16AB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0855, { 0 } },
    /*16AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0856, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROTB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16AD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x008C, { 0 } },
    /*16AE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x008D, { 0 } },
    /*16AF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x008E, { 0 } },
    /*16B0*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x008F, { 0 } },
    /*16B1*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0090, { 0 } },
    /*16B2*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0091, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROTD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16B3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0092, { 0 } },
    /*16B4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0093, { 0 } },
    /*16B5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0094, { 0 } },
    /*16B6*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0095, { 0 } },
    /*16B7*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0096, { 0 } },
    /*16B8*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0097, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROTQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16B9*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0098, { 0 } },
    /*16BA*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x0099, { 0 } },
    /*16BB*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x009A, { 0 } },
    /*16BC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x009B, { 0 } },
    /*16BD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x009C, { 0 } },
    /*16BE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x009D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPROTW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16BF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x009E, { 0 } },
    /*16C0*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x009F, { 0 } },
    /*16C1*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A0, { 0 } },
    /*16C2*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A1, { 0 } },
    /*16C3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A2, { 0 } },
    /*16C4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSADBW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16C5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x051C, { 0 } },
    /*16C6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x051D, { 0 } },
    /*16C7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x051E, { 0 } },
    /*16C8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x051F, { 0 } },
    /*16C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0857, { 0 } },
    /*16CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0858, { 0 } },
    /*16CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0859, { 0 } },
    /*16CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x085A, { 0 } },
    /*16CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x085B, { 0 } },
    /*16CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x085C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSBBD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16CF*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0144, { 0 } },
    /*16D0*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0145, { 0 } },
    /*16D1*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0146, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSBBRD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16D2*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0147, { 0 } },
    /*16D3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0148, { 0 } },
    /*16D4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0149, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSCATTERDD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x085D, { 0 } },
    /*16D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x085E, { 0 } },
    /*16D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x085F, { 0 } },
    /*16D8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x014A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSCATTERDQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0860, { 0 } },
    /*16DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0861, { 0 } },
    /*16DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0862, { 0 } },
    /*16DC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x014B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSCATTERQD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0863, { 0 } },
    /*16DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0864, { 0 } },
    /*16DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0865, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSCATTERQQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0866, { 0 } },
    /*16E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0867, { 0 } },
    /*16E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0868, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHAB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16E3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A4, { 0 } },
    /*16E4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A5, { 0 } },
    /*16E5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A6, { 0 } },
    /*16E6*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHAD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16E7*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A8, { 0 } },
    /*16E8*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00A9, { 0 } },
    /*16E9*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00AA, { 0 } },
    /*16EA*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00AB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHAQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16EB*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00AC, { 0 } },
    /*16EC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00AD, { 0 } },
    /*16ED*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00AE, { 0 } },
    /*16EE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00AF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHAW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16EF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B0, { 0 } },
    /*16F0*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B1, { 0 } },
    /*16F1*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B2, { 0 } },
    /*16F2*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHLB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16F3*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B4, { 0 } },
    /*16F4*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B5, { 0 } },
    /*16F5*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B6, { 0 } },
    /*16F6*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHLD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16F7*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B8, { 0 } },
    /*16F8*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00B9, { 0 } },
    /*16F9*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00BA, { 0 } },
    /*16FA*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00BB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHLQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16FB*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00BC, { 0 } },
    /*16FC*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00BD, { 0 } },
    /*16FD*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00BE, { 0 } },
    /*16FE*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00BF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHLW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*16FF*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00C0, { 0 } },
    /*1700*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00C1, { 0 } },
    /*1701*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00C2, { 0 } },
    /*1702*/ { ZYDIS_INSTRUCTION_ENCODING_XOP    , 0x00C3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHUFB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1703*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0520, { 0 } },
    /*1704*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0521, { 0 } },
    /*1705*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0522, { 0 } },
    /*1706*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0523, { 0 } },
    /*1707*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0869, { 0 } },
    /*1708*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x086A, { 0 } },
    /*1709*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x086B, { 0 } },
    /*170A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x086C, { 0 } },
    /*170B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x086D, { 0 } },
    /*170C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x086E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHUFD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*170D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0524, { 0 } },
    /*170E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0525, { 0 } },
    /*170F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0526, { 0 } },
    /*1710*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0527, { 0 } },
    /*1711*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x086F, { 0 } },
    /*1712*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0870, { 0 } },
    /*1713*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0871, { 0 } },
    /*1714*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0872, { 0 } },
    /*1715*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0873, { 0 } },
    /*1716*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0874, { 0 } },
    /*1717*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x014C, { 0 } },
    /*1718*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x014D, { 0 } },
    /*1719*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x014E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHUFHW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*171A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0528, { 0 } },
    /*171B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0529, { 0 } },
    /*171C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x052A, { 0 } },
    /*171D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x052B, { 0 } },
    /*171E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0875, { 0 } },
    /*171F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0876, { 0 } },
    /*1720*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0877, { 0 } },
    /*1721*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0878, { 0 } },
    /*1722*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0879, { 0 } },
    /*1723*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x087A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSHUFLW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1724*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x052C, { 0 } },
    /*1725*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x052D, { 0 } },
    /*1726*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x052E, { 0 } },
    /*1727*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x052F, { 0 } },
    /*1728*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x087B, { 0 } },
    /*1729*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x087C, { 0 } },
    /*172A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x087D, { 0 } },
    /*172B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x087E, { 0 } },
    /*172C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x087F, { 0 } },
    /*172D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0880, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSIGNB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*172E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0530, { 0 } },
    /*172F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0531, { 0 } },
    /*1730*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0532, { 0 } },
    /*1731*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0533, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSIGND                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1732*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0534, { 0 } },
    /*1733*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0535, { 0 } },
    /*1734*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0536, { 0 } },
    /*1735*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0537, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSIGNW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1736*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0538, { 0 } },
    /*1737*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0539, { 0 } },
    /*1738*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x053A, { 0 } },
    /*1739*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x053B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*173A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x053C, { 0 } },
    /*173B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x053D, { 0 } },
    /*173C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x053E, { 0 } },
    /*173D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x053F, { 0 } },
    /*173E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0540, { 0 } },
    /*173F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0541, { 0 } },
    /*1740*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0881, { 0 } },
    /*1741*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0882, { 0 } },
    /*1742*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0883, { 0 } },
    /*1743*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0884, { 0 } },
    /*1744*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0885, { 0 } },
    /*1745*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0886, { 0 } },
    /*1746*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0887, { 0 } },
    /*1747*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0888, { 0 } },
    /*1748*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0889, { 0 } },
    /*1749*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x088A, { 0 } },
    /*174A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x088B, { 0 } },
    /*174B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x088C, { 0 } },
    /*174C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x014F, { 0 } },
    /*174D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0150, { 0 } },
    /*174E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0151, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLDQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*174F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0542, { 0 } },
    /*1750*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0543, { 0 } },
    /*1751*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x088D, { 0 } },
    /*1752*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x088E, { 0 } },
    /*1753*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x088F, { 0 } },
    /*1754*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0890, { 0 } },
    /*1755*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0891, { 0 } },
    /*1756*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0892, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1757*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0544, { 0 } },
    /*1758*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0545, { 0 } },
    /*1759*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0546, { 0 } },
    /*175A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0547, { 0 } },
    /*175B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0548, { 0 } },
    /*175C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0549, { 0 } },
    /*175D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0893, { 0 } },
    /*175E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0894, { 0 } },
    /*175F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0895, { 0 } },
    /*1760*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0896, { 0 } },
    /*1761*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0897, { 0 } },
    /*1762*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0898, { 0 } },
    /*1763*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0899, { 0 } },
    /*1764*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x089A, { 0 } },
    /*1765*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x089B, { 0 } },
    /*1766*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x089C, { 0 } },
    /*1767*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x089D, { 0 } },
    /*1768*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x089E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLVD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1769*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x054A, { 0 } },
    /*176A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x054B, { 0 } },
    /*176B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x054C, { 0 } },
    /*176C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x054D, { 0 } },
    /*176D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x089F, { 0 } },
    /*176E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A0, { 0 } },
    /*176F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A1, { 0 } },
    /*1770*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A2, { 0 } },
    /*1771*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A3, { 0 } },
    /*1772*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A4, { 0 } },
    /*1773*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0152, { 0 } },
    /*1774*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0153, { 0 } },
    /*1775*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0154, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLVQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1776*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x054E, { 0 } },
    /*1777*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x054F, { 0 } },
    /*1778*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0550, { 0 } },
    /*1779*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0551, { 0 } },
    /*177A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A5, { 0 } },
    /*177B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A6, { 0 } },
    /*177C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A7, { 0 } },
    /*177D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A8, { 0 } },
    /*177E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08A9, { 0 } },
    /*177F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08AA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLVW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1780*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08AB, { 0 } },
    /*1781*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08AC, { 0 } },
    /*1782*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08AD, { 0 } },
    /*1783*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08AE, { 0 } },
    /*1784*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08AF, { 0 } },
    /*1785*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSLLW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1786*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0552, { 0 } },
    /*1787*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0553, { 0 } },
    /*1788*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0554, { 0 } },
    /*1789*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0555, { 0 } },
    /*178A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0556, { 0 } },
    /*178B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0557, { 0 } },
    /*178C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B1, { 0 } },
    /*178D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B2, { 0 } },
    /*178E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B3, { 0 } },
    /*178F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B4, { 0 } },
    /*1790*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B5, { 0 } },
    /*1791*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B6, { 0 } },
    /*1792*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B7, { 0 } },
    /*1793*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B8, { 0 } },
    /*1794*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08B9, { 0 } },
    /*1795*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08BA, { 0 } },
    /*1796*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08BB, { 0 } },
    /*1797*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08BC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRAD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1798*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0558, { 0 } },
    /*1799*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0559, { 0 } },
    /*179A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x055A, { 0 } },
    /*179B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x055B, { 0 } },
    /*179C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x055C, { 0 } },
    /*179D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x055D, { 0 } },
    /*179E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08BD, { 0 } },
    /*179F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08BE, { 0 } },
    /*17A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08BF, { 0 } },
    /*17A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C0, { 0 } },
    /*17A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C1, { 0 } },
    /*17A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C2, { 0 } },
    /*17A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C3, { 0 } },
    /*17A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C4, { 0 } },
    /*17A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C5, { 0 } },
    /*17A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C6, { 0 } },
    /*17A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C7, { 0 } },
    /*17A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C8, { 0 } },
    /*17AA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0155, { 0 } },
    /*17AB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0156, { 0 } },
    /*17AC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0157, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRAQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08C9, { 0 } },
    /*17AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08CA, { 0 } },
    /*17AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08CB, { 0 } },
    /*17B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08CC, { 0 } },
    /*17B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08CD, { 0 } },
    /*17B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08CE, { 0 } },
    /*17B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08CF, { 0 } },
    /*17B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D0, { 0 } },
    /*17B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D1, { 0 } },
    /*17B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D2, { 0 } },
    /*17B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D3, { 0 } },
    /*17B8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRAVD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x055E, { 0 } },
    /*17BA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x055F, { 0 } },
    /*17BB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0560, { 0 } },
    /*17BC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0561, { 0 } },
    /*17BD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D5, { 0 } },
    /*17BE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D6, { 0 } },
    /*17BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D7, { 0 } },
    /*17C0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D8, { 0 } },
    /*17C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08D9, { 0 } },
    /*17C2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08DA, { 0 } },
    /*17C3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0158, { 0 } },
    /*17C4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0159, { 0 } },
    /*17C5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x015A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRAVQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08DB, { 0 } },
    /*17C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08DC, { 0 } },
    /*17C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08DD, { 0 } },
    /*17C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08DE, { 0 } },
    /*17CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08DF, { 0 } },
    /*17CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRAVW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E1, { 0 } },
    /*17CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E2, { 0 } },
    /*17CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E3, { 0 } },
    /*17CF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E4, { 0 } },
    /*17D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E5, { 0 } },
    /*17D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRAW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17D2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0562, { 0 } },
    /*17D3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0563, { 0 } },
    /*17D4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0564, { 0 } },
    /*17D5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0565, { 0 } },
    /*17D6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0566, { 0 } },
    /*17D7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0567, { 0 } },
    /*17D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E7, { 0 } },
    /*17D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E8, { 0 } },
    /*17DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08E9, { 0 } },
    /*17DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08EA, { 0 } },
    /*17DC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08EB, { 0 } },
    /*17DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08EC, { 0 } },
    /*17DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08ED, { 0 } },
    /*17DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08EE, { 0 } },
    /*17E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08EF, { 0 } },
    /*17E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F0, { 0 } },
    /*17E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F1, { 0 } },
    /*17E3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17E4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0568, { 0 } },
    /*17E5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0569, { 0 } },
    /*17E6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x056A, { 0 } },
    /*17E7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x056B, { 0 } },
    /*17E8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x056C, { 0 } },
    /*17E9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x056D, { 0 } },
    /*17EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F3, { 0 } },
    /*17EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F4, { 0 } },
    /*17EC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F5, { 0 } },
    /*17ED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F6, { 0 } },
    /*17EE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F7, { 0 } },
    /*17EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F8, { 0 } },
    /*17F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08F9, { 0 } },
    /*17F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08FA, { 0 } },
    /*17F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08FB, { 0 } },
    /*17F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08FC, { 0 } },
    /*17F4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08FD, { 0 } },
    /*17F5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08FE, { 0 } },
    /*17F6*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x015B, { 0 } },
    /*17F7*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x015C, { 0 } },
    /*17F8*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x015D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLDQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*17F9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x056E, { 0 } },
    /*17FA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x056F, { 0 } },
    /*17FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x08FF, { 0 } },
    /*17FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0900, { 0 } },
    /*17FD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0901, { 0 } },
    /*17FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0902, { 0 } },
    /*17FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0903, { 0 } },
    /*1800*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0904, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1801*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0570, { 0 } },
    /*1802*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0571, { 0 } },
    /*1803*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0572, { 0 } },
    /*1804*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0573, { 0 } },
    /*1805*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0574, { 0 } },
    /*1806*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0575, { 0 } },
    /*1807*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0905, { 0 } },
    /*1808*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0906, { 0 } },
    /*1809*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0907, { 0 } },
    /*180A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0908, { 0 } },
    /*180B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0909, { 0 } },
    /*180C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x090A, { 0 } },
    /*180D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x090B, { 0 } },
    /*180E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x090C, { 0 } },
    /*180F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x090D, { 0 } },
    /*1810*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x090E, { 0 } },
    /*1811*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x090F, { 0 } },
    /*1812*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0910, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLVD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1813*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0576, { 0 } },
    /*1814*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0577, { 0 } },
    /*1815*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0578, { 0 } },
    /*1816*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0579, { 0 } },
    /*1817*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0911, { 0 } },
    /*1818*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0912, { 0 } },
    /*1819*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0913, { 0 } },
    /*181A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0914, { 0 } },
    /*181B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0915, { 0 } },
    /*181C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0916, { 0 } },
    /*181D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x015E, { 0 } },
    /*181E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x015F, { 0 } },
    /*181F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0160, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLVQ                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1820*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x057A, { 0 } },
    /*1821*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x057B, { 0 } },
    /*1822*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x057C, { 0 } },
    /*1823*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x057D, { 0 } },
    /*1824*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0917, { 0 } },
    /*1825*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0918, { 0 } },
    /*1826*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0919, { 0 } },
    /*1827*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x091A, { 0 } },
    /*1828*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x091B, { 0 } },
    /*1829*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x091C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLVW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*182A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x091D, { 0 } },
    /*182B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x091E, { 0 } },
    /*182C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x091F, { 0 } },
    /*182D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0920, { 0 } },
    /*182E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0921, { 0 } },
    /*182F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0922, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSRLW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1830*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x057E, { 0 } },
    /*1831*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x057F, { 0 } },
    /*1832*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0580, { 0 } },
    /*1833*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0581, { 0 } },
    /*1834*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0582, { 0 } },
    /*1835*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0583, { 0 } },
    /*1836*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0923, { 0 } },
    /*1837*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0924, { 0 } },
    /*1838*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0925, { 0 } },
    /*1839*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0926, { 0 } },
    /*183A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0927, { 0 } },
    /*183B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0928, { 0 } },
    /*183C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0929, { 0 } },
    /*183D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x092A, { 0 } },
    /*183E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x092B, { 0 } },
    /*183F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x092C, { 0 } },
    /*1840*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x092D, { 0 } },
    /*1841*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x092E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBB                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1842*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0584, { 0 } },
    /*1843*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0585, { 0 } },
    /*1844*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0586, { 0 } },
    /*1845*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0587, { 0 } },
    /*1846*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x092F, { 0 } },
    /*1847*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0930, { 0 } },
    /*1848*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0931, { 0 } },
    /*1849*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0932, { 0 } },
    /*184A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0933, { 0 } },
    /*184B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0934, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*184C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0588, { 0 } },
    /*184D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0589, { 0 } },
    /*184E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x058A, { 0 } },
    /*184F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x058B, { 0 } },
    /*1850*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0935, { 0 } },
    /*1851*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0936, { 0 } },
    /*1852*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0937, { 0 } },
    /*1853*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0938, { 0 } },
    /*1854*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0939, { 0 } },
    /*1855*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x093A, { 0 } },
    /*1856*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0161, { 0 } },
    /*1857*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0162, { 0 } },
    /*1858*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0163, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1859*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x058C, { 0 } },
    /*185A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x058D, { 0 } },
    /*185B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x058E, { 0 } },
    /*185C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x058F, { 0 } },
    /*185D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x093B, { 0 } },
    /*185E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x093C, { 0 } },
    /*185F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x093D, { 0 } },
    /*1860*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x093E, { 0 } },
    /*1861*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x093F, { 0 } },
    /*1862*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0940, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBRD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1863*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0164, { 0 } },
    /*1864*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0165, { 0 } },
    /*1865*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0166, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBRSETBD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1866*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0167, { 0 } },
    /*1867*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0168, { 0 } },
    /*1868*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0169, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBSB                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1869*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0590, { 0 } },
    /*186A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0591, { 0 } },
    /*186B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0592, { 0 } },
    /*186C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0593, { 0 } },
    /*186D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0941, { 0 } },
    /*186E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0942, { 0 } },
    /*186F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0943, { 0 } },
    /*1870*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0944, { 0 } },
    /*1871*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0945, { 0 } },
    /*1872*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0946, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBSETBD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1873*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x016A, { 0 } },
    /*1874*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x016B, { 0 } },
    /*1875*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x016C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBSW                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1876*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0594, { 0 } },
    /*1877*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0595, { 0 } },
    /*1878*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0596, { 0 } },
    /*1879*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0597, { 0 } },
    /*187A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0947, { 0 } },
    /*187B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0948, { 0 } },
    /*187C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0949, { 0 } },
    /*187D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x094A, { 0 } },
    /*187E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x094B, { 0 } },
    /*187F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x094C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBUSB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1880*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0598, { 0 } },
    /*1881*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0599, { 0 } },
    /*1882*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x059A, { 0 } },
    /*1883*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x059B, { 0 } },
    /*1884*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x094D, { 0 } },
    /*1885*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x094E, { 0 } },
    /*1886*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x094F, { 0 } },
    /*1887*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0950, { 0 } },
    /*1888*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0951, { 0 } },
    /*1889*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0952, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBUSW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*188A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x059C, { 0 } },
    /*188B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x059D, { 0 } },
    /*188C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x059E, { 0 } },
    /*188D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x059F, { 0 } },
    /*188E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0953, { 0 } },
    /*188F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0954, { 0 } },
    /*1890*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0955, { 0 } },
    /*1891*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0956, { 0 } },
    /*1892*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0957, { 0 } },
    /*1893*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0958, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPSUBW                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1894*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A0, { 0 } },
    /*1895*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A1, { 0 } },
    /*1896*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A2, { 0 } },
    /*1897*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A3, { 0 } },
    /*1898*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0959, { 0 } },
    /*1899*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x095A, { 0 } },
    /*189A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x095B, { 0 } },
    /*189B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x095C, { 0 } },
    /*189C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x095D, { 0 } },
    /*189D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x095E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTERNLOGD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*189E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x095F, { 0 } },
    /*189F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0960, { 0 } },
    /*18A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0961, { 0 } },
    /*18A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0962, { 0 } },
    /*18A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0963, { 0 } },
    /*18A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0964, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTERNLOGQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0965, { 0 } },
    /*18A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0966, { 0 } },
    /*18A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0967, { 0 } },
    /*18A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0968, { 0 } },
    /*18A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0969, { 0 } },
    /*18A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x096A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTEST                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18AA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A4, { 0 } },
    /*18AB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A5, { 0 } },
    /*18AC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A6, { 0 } },
    /*18AD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTMB                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18AE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x096B, { 0 } },
    /*18AF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x096C, { 0 } },
    /*18B0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x096D, { 0 } },
    /*18B1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x096E, { 0 } },
    /*18B2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x096F, { 0 } },
    /*18B3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0970, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTMD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18B4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0971, { 0 } },
    /*18B5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0972, { 0 } },
    /*18B6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0973, { 0 } },
    /*18B7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0974, { 0 } },
    /*18B8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0975, { 0 } },
    /*18B9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0976, { 0 } },
    /*18BA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x016D, { 0 } },
    /*18BB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x016E, { 0 } },
    /*18BC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x016F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTMQ                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18BD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0977, { 0 } },
    /*18BE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0978, { 0 } },
    /*18BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0979, { 0 } },
    /*18C0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x097A, { 0 } },
    /*18C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x097B, { 0 } },
    /*18C2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x097C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTMW                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18C3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x097D, { 0 } },
    /*18C4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x097E, { 0 } },
    /*18C5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x097F, { 0 } },
    /*18C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0980, { 0 } },
    /*18C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0981, { 0 } },
    /*18C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0982, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTNMB                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0983, { 0 } },
    /*18CA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0984, { 0 } },
    /*18CB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0985, { 0 } },
    /*18CC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0986, { 0 } },
    /*18CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0987, { 0 } },
    /*18CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0988, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTNMD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18CF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0989, { 0 } },
    /*18D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x098A, { 0 } },
    /*18D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x098B, { 0 } },
    /*18D2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x098C, { 0 } },
    /*18D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x098D, { 0 } },
    /*18D4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x098E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTNMQ                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x098F, { 0 } },
    /*18D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0990, { 0 } },
    /*18D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0991, { 0 } },
    /*18D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0992, { 0 } },
    /*18D9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0993, { 0 } },
    /*18DA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0994, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPTESTNMW                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18DB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0995, { 0 } },
    /*18DC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0996, { 0 } },
    /*18DD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0997, { 0 } },
    /*18DE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0998, { 0 } },
    /*18DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0999, { 0 } },
    /*18E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x099A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKHBW                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18E1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A8, { 0 } },
    /*18E2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05A9, { 0 } },
    /*18E3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05AA, { 0 } },
    /*18E4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05AB, { 0 } },
    /*18E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x099B, { 0 } },
    /*18E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x099C, { 0 } },
    /*18E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x099D, { 0 } },
    /*18E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x099E, { 0 } },
    /*18E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x099F, { 0 } },
    /*18EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKHDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18EB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05AC, { 0 } },
    /*18EC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05AD, { 0 } },
    /*18ED*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05AE, { 0 } },
    /*18EE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05AF, { 0 } },
    /*18EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A1, { 0 } },
    /*18F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A2, { 0 } },
    /*18F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A3, { 0 } },
    /*18F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A4, { 0 } },
    /*18F3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A5, { 0 } },
    /*18F4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKHQDQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18F5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B0, { 0 } },
    /*18F6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B1, { 0 } },
    /*18F7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B2, { 0 } },
    /*18F8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B3, { 0 } },
    /*18F9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A7, { 0 } },
    /*18FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A8, { 0 } },
    /*18FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09A9, { 0 } },
    /*18FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09AA, { 0 } },
    /*18FD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09AB, { 0 } },
    /*18FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09AC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKHWD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*18FF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B4, { 0 } },
    /*1900*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B5, { 0 } },
    /*1901*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B6, { 0 } },
    /*1902*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B7, { 0 } },
    /*1903*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09AD, { 0 } },
    /*1904*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09AE, { 0 } },
    /*1905*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09AF, { 0 } },
    /*1906*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B0, { 0 } },
    /*1907*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B1, { 0 } },
    /*1908*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKLBW                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1909*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B8, { 0 } },
    /*190A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05B9, { 0 } },
    /*190B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05BA, { 0 } },
    /*190C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05BB, { 0 } },
    /*190D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B3, { 0 } },
    /*190E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B4, { 0 } },
    /*190F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B5, { 0 } },
    /*1910*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B6, { 0 } },
    /*1911*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B7, { 0 } },
    /*1912*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKLDQ                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1913*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05BC, { 0 } },
    /*1914*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05BD, { 0 } },
    /*1915*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05BE, { 0 } },
    /*1916*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05BF, { 0 } },
    /*1917*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09B9, { 0 } },
    /*1918*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09BA, { 0 } },
    /*1919*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09BB, { 0 } },
    /*191A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09BC, { 0 } },
    /*191B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09BD, { 0 } },
    /*191C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09BE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKLQDQ                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*191D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C0, { 0 } },
    /*191E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C1, { 0 } },
    /*191F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C2, { 0 } },
    /*1920*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C3, { 0 } },
    /*1921*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09BF, { 0 } },
    /*1922*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C0, { 0 } },
    /*1923*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C1, { 0 } },
    /*1924*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C2, { 0 } },
    /*1925*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C3, { 0 } },
    /*1926*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPUNPCKLWD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1927*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C4, { 0 } },
    /*1928*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C5, { 0 } },
    /*1929*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C6, { 0 } },
    /*192A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C7, { 0 } },
    /*192B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C5, { 0 } },
    /*192C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C6, { 0 } },
    /*192D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C7, { 0 } },
    /*192E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C8, { 0 } },
    /*192F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09C9, { 0 } },
    /*1930*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09CA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPXOR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1931*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C8, { 0 } },
    /*1932*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05C9, { 0 } },
    /*1933*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05CA, { 0 } },
    /*1934*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05CB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPXORD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1935*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09CB, { 0 } },
    /*1936*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09CC, { 0 } },
    /*1937*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09CD, { 0 } },
    /*1938*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09CE, { 0 } },
    /*1939*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09CF, { 0 } },
    /*193A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D0, { 0 } },
    /*193B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0170, { 0 } },
    /*193C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0171, { 0 } },
    /*193D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0172, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VPXORQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*193E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D1, { 0 } },
    /*193F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D2, { 0 } },
    /*1940*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D3, { 0 } },
    /*1941*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D4, { 0 } },
    /*1942*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D5, { 0 } },
    /*1943*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D6, { 0 } },
    /*1944*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0173, { 0 } },
    /*1945*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0174, { 0 } },
    /*1946*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0175, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRANGEPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1947*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D7, { 0 } },
    /*1948*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D8, { 0 } },
    /*1949*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09D9, { 0 } },
    /*194A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09DA, { 0 } },
    /*194B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09DB, { 0 } },
    /*194C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09DC, { 0 } },
    /*194D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRANGEPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*194E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09DE, { 0 } },
    /*194F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09DF, { 0 } },
    /*1950*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E0, { 0 } },
    /*1951*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E1, { 0 } },
    /*1952*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E2, { 0 } },
    /*1953*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E3, { 0 } },
    /*1954*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRANGESD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1955*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E5, { 0 } },
    /*1956*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E6, { 0 } },
    /*1957*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E7, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRANGESS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1958*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E8, { 0 } },
    /*1959*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09E9, { 0 } },
    /*195A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09EA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP14PD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*195B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09EB, { 0 } },
    /*195C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09EC, { 0 } },
    /*195D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09ED, { 0 } },
    /*195E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09EE, { 0 } },
    /*195F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09EF, { 0 } },
    /*1960*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP14PS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1961*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F1, { 0 } },
    /*1962*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F2, { 0 } },
    /*1963*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F3, { 0 } },
    /*1964*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F4, { 0 } },
    /*1965*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F5, { 0 } },
    /*1966*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP14SD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1967*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F7, { 0 } },
    /*1968*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP14SS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1969*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09F9, { 0 } },
    /*196A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09FA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP23PS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*196B*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0176, { 0 } },
    /*196C*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0177, { 0 } },
    /*196D*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0178, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP28PD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*196E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09FB, { 0 } },
    /*196F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09FC, { 0 } },
    /*1970*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09FD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP28PS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1971*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09FE, { 0 } },
    /*1972*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x09FF, { 0 } },
    /*1973*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A00, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP28SD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1974*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A01, { 0 } },
    /*1975*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A02, { 0 } },
    /*1976*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A03, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCP28SS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1977*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A04, { 0 } },
    /*1978*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A05, { 0 } },
    /*1979*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A06, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCPPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*197A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05CC, { 0 } },
    /*197B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05CD, { 0 } },
    /*197C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05CE, { 0 } },
    /*197D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05CF, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRCPSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*197E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D0, { 0 } },
    /*197F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VREDUCEPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1980*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A07, { 0 } },
    /*1981*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A08, { 0 } },
    /*1982*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A09, { 0 } },
    /*1983*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A0A, { 0 } },
    /*1984*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A0B, { 0 } },
    /*1985*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A0C, { 0 } },
    /*1986*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A0D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VREDUCEPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1987*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A0E, { 0 } },
    /*1988*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A0F, { 0 } },
    /*1989*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A10, { 0 } },
    /*198A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A11, { 0 } },
    /*198B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A12, { 0 } },
    /*198C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A13, { 0 } },
    /*198D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A14, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VREDUCESD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*198E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A15, { 0 } },
    /*198F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A16, { 0 } },
    /*1990*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A17, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VREDUCESS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1991*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A18, { 0 } },
    /*1992*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A19, { 0 } },
    /*1993*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A1A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRNDFXPNTPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1994*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0179, { 0 } },
    /*1995*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x017A, { 0 } },
    /*1996*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x017B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRNDFXPNTPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1997*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x017C, { 0 } },
    /*1998*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x017D, { 0 } },
    /*1999*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x017E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRNDSCALEPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*199A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A1B, { 0 } },
    /*199B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A1C, { 0 } },
    /*199C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A1D, { 0 } },
    /*199D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A1E, { 0 } },
    /*199E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A1F, { 0 } },
    /*199F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A20, { 0 } },
    /*19A0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A21, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRNDSCALEPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19A1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A22, { 0 } },
    /*19A2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A23, { 0 } },
    /*19A3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A24, { 0 } },
    /*19A4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A25, { 0 } },
    /*19A5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A26, { 0 } },
    /*19A6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A27, { 0 } },
    /*19A7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A28, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRNDSCALESD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19A8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A29, { 0 } },
    /*19A9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A2A, { 0 } },
    /*19AA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A2B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRNDSCALESS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19AB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A2C, { 0 } },
    /*19AC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A2D, { 0 } },
    /*19AD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A2E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VROUNDPD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19AE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D2, { 0 } },
    /*19AF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D3, { 0 } },
    /*19B0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D4, { 0 } },
    /*19B1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D5, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VROUNDPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19B2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D6, { 0 } },
    /*19B3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D7, { 0 } },
    /*19B4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D8, { 0 } },
    /*19B5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05D9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VROUNDSD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19B6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05DA, { 0 } },
    /*19B7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05DB, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VROUNDSS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19B8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05DC, { 0 } },
    /*19B9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05DD, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT14PD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19BA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A2F, { 0 } },
    /*19BB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A30, { 0 } },
    /*19BC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A31, { 0 } },
    /*19BD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A32, { 0 } },
    /*19BE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A33, { 0 } },
    /*19BF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A34, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT14PS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19C0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A35, { 0 } },
    /*19C1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A36, { 0 } },
    /*19C2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A37, { 0 } },
    /*19C3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A38, { 0 } },
    /*19C4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A39, { 0 } },
    /*19C5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A3A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT14SD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19C6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A3B, { 0 } },
    /*19C7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A3C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT14SS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19C8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A3D, { 0 } },
    /*19C9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A3E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT23PS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19CA*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x017F, { 0 } },
    /*19CB*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0180, { 0 } },
    /*19CC*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0181, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT28PD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19CD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A3F, { 0 } },
    /*19CE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A40, { 0 } },
    /*19CF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A41, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT28PS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19D0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A42, { 0 } },
    /*19D1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A43, { 0 } },
    /*19D2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A44, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT28SD                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19D3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A45, { 0 } },
    /*19D4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A46, { 0 } },
    /*19D5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A47, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRT28SS                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19D6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A48, { 0 } },
    /*19D7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A49, { 0 } },
    /*19D8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A4A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRTPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19D9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05DE, { 0 } },
    /*19DA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05DF, { 0 } },
    /*19DB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E0, { 0 } },
    /*19DC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E1, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VRSQRTSS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19DD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E2, { 0 } },
    /*19DE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCALEFPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19DF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A4B, { 0 } },
    /*19E0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A4C, { 0 } },
    /*19E1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A4D, { 0 } },
    /*19E2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A4E, { 0 } },
    /*19E3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A4F, { 0 } },
    /*19E4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A50, { 0 } },
    /*19E5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A51, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCALEFPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19E6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A52, { 0 } },
    /*19E7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A53, { 0 } },
    /*19E8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A54, { 0 } },
    /*19E9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A55, { 0 } },
    /*19EA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A56, { 0 } },
    /*19EB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A57, { 0 } },
    /*19EC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A58, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCALEFSD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19ED*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A59, { 0 } },
    /*19EE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A5A, { 0 } },
    /*19EF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A5B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCALEFSS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19F0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A5C, { 0 } },
    /*19F1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A5D, { 0 } },
    /*19F2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A5E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCALEPS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19F3*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0182, { 0 } },
    /*19F4*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0183, { 0 } },
    /*19F5*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0184, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERDPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19F6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A5F, { 0 } },
    /*19F7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A60, { 0 } },
    /*19F8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A61, { 0 } },
    /*19F9*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0185, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERDPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19FA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A62, { 0 } },
    /*19FB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A63, { 0 } },
    /*19FC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A64, { 0 } },
    /*19FD*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0186, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF0DPD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19FE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A65, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF0DPS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*19FF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A66, { 0 } },
    /*1A00*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0187, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF0HINTDPD                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A01*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0188, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF0HINTDPS                                                                         */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A02*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0189, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF0QPD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A03*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A67, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF0QPS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A04*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A68, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF1DPD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A05*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A69, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF1DPS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A06*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A6A, { 0 } },
    /*1A07*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x018A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF1QPD                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A08*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A6B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERPF1QPS                                                                             */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A09*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A6C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERQPD                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A0A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A6D, { 0 } },
    /*1A0B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A6E, { 0 } },
    /*1A0C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A6F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSCATTERQPS                                                                                */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A0D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A70, { 0 } },
    /*1A0E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A71, { 0 } },
    /*1A0F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A72, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSHUFF32X4                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A10*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A73, { 0 } },
    /*1A11*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A74, { 0 } },
    /*1A12*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A75, { 0 } },
    /*1A13*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A76, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSHUFF64X2                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A14*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A77, { 0 } },
    /*1A15*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A78, { 0 } },
    /*1A16*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A79, { 0 } },
    /*1A17*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A7A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSHUFI32X4                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A18*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A7B, { 0 } },
    /*1A19*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A7C, { 0 } },
    /*1A1A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A7D, { 0 } },
    /*1A1B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A7E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSHUFI64X2                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A1C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A7F, { 0 } },
    /*1A1D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A80, { 0 } },
    /*1A1E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A81, { 0 } },
    /*1A1F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A82, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSHUFPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A20*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E4, { 0 } },
    /*1A21*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E5, { 0 } },
    /*1A22*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E6, { 0 } },
    /*1A23*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E7, { 0 } },
    /*1A24*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A83, { 0 } },
    /*1A25*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A84, { 0 } },
    /*1A26*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A85, { 0 } },
    /*1A27*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A86, { 0 } },
    /*1A28*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A87, { 0 } },
    /*1A29*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A88, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSHUFPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A2A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E8, { 0 } },
    /*1A2B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05E9, { 0 } },
    /*1A2C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05EA, { 0 } },
    /*1A2D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05EB, { 0 } },
    /*1A2E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A89, { 0 } },
    /*1A2F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A8A, { 0 } },
    /*1A30*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A8B, { 0 } },
    /*1A31*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A8C, { 0 } },
    /*1A32*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A8D, { 0 } },
    /*1A33*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A8E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSQRTPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A34*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05EC, { 0 } },
    /*1A35*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05ED, { 0 } },
    /*1A36*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05EE, { 0 } },
    /*1A37*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05EF, { 0 } },
    /*1A38*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A8F, { 0 } },
    /*1A39*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A90, { 0 } },
    /*1A3A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A91, { 0 } },
    /*1A3B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A92, { 0 } },
    /*1A3C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A93, { 0 } },
    /*1A3D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A94, { 0 } },
    /*1A3E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A95, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSQRTPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A3F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F0, { 0 } },
    /*1A40*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F1, { 0 } },
    /*1A41*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F2, { 0 } },
    /*1A42*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F3, { 0 } },
    /*1A43*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A96, { 0 } },
    /*1A44*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A97, { 0 } },
    /*1A45*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A98, { 0 } },
    /*1A46*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A99, { 0 } },
    /*1A47*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A9A, { 0 } },
    /*1A48*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A9B, { 0 } },
    /*1A49*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A9C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSQRTSD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A4A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F4, { 0 } },
    /*1A4B*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F5, { 0 } },
    /*1A4C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A9D, { 0 } },
    /*1A4D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A9E, { 0 } },
    /*1A4E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0A9F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSQRTSS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A4F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F6, { 0 } },
    /*1A50*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F7, { 0 } },
    /*1A51*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA0, { 0 } },
    /*1A52*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA1, { 0 } },
    /*1A53*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSTMXCSR                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A54*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSUBPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A55*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05F9, { 0 } },
    /*1A56*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05FA, { 0 } },
    /*1A57*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05FB, { 0 } },
    /*1A58*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05FC, { 0 } },
    /*1A59*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA3, { 0 } },
    /*1A5A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA4, { 0 } },
    /*1A5B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA5, { 0 } },
    /*1A5C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA6, { 0 } },
    /*1A5D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA7, { 0 } },
    /*1A5E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA8, { 0 } },
    /*1A5F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AA9, { 0 } },
    /*1A60*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x018B, { 0 } },
    /*1A61*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x018C, { 0 } },
    /*1A62*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x018D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSUBPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A63*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05FD, { 0 } },
    /*1A64*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05FE, { 0 } },
    /*1A65*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x05FF, { 0 } },
    /*1A66*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0600, { 0 } },
    /*1A67*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AAA, { 0 } },
    /*1A68*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AAB, { 0 } },
    /*1A69*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AAC, { 0 } },
    /*1A6A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AAD, { 0 } },
    /*1A6B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AAE, { 0 } },
    /*1A6C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AAF, { 0 } },
    /*1A6D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB0, { 0 } },
    /*1A6E*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x018E, { 0 } },
    /*1A6F*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x018F, { 0 } },
    /*1A70*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0190, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSUBRPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A71*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0191, { 0 } },
    /*1A72*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0192, { 0 } },
    /*1A73*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0193, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSUBRPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A74*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0194, { 0 } },
    /*1A75*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0195, { 0 } },
    /*1A76*/ { ZYDIS_INSTRUCTION_ENCODING_MVEX   , 0x0196, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSUBSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A77*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0601, { 0 } },
    /*1A78*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0602, { 0 } },
    /*1A79*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB1, { 0 } },
    /*1A7A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB2, { 0 } },
    /*1A7B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB3, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VSUBSS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A7C*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0603, { 0 } },
    /*1A7D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0604, { 0 } },
    /*1A7E*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB4, { 0 } },
    /*1A7F*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB5, { 0 } },
    /*1A80*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB6, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VTESTPD                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A81*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0605, { 0 } },
    /*1A82*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0606, { 0 } },
    /*1A83*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0607, { 0 } },
    /*1A84*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0608, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VTESTPS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A85*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0609, { 0 } },
    /*1A86*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x060A, { 0 } },
    /*1A87*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x060B, { 0 } },
    /*1A88*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x060C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VUCOMISD                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A89*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x060D, { 0 } },
    /*1A8A*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x060E, { 0 } },
    /*1A8B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB7, { 0 } },
    /*1A8C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB8, { 0 } },
    /*1A8D*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AB9, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VUCOMISS                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A8E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x060F, { 0 } },
    /*1A8F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0610, { 0 } },
    /*1A90*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ABA, { 0 } },
    /*1A91*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ABB, { 0 } },
    /*1A92*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ABC, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VUNPCKHPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A93*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0611, { 0 } },
    /*1A94*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0612, { 0 } },
    /*1A95*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0613, { 0 } },
    /*1A96*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0614, { 0 } },
    /*1A97*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ABD, { 0 } },
    /*1A98*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ABE, { 0 } },
    /*1A99*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ABF, { 0 } },
    /*1A9A*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC0, { 0 } },
    /*1A9B*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC1, { 0 } },
    /*1A9C*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC2, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VUNPCKHPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1A9D*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0615, { 0 } },
    /*1A9E*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0616, { 0 } },
    /*1A9F*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0617, { 0 } },
    /*1AA0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0618, { 0 } },
    /*1AA1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC3, { 0 } },
    /*1AA2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC4, { 0 } },
    /*1AA3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC5, { 0 } },
    /*1AA4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC6, { 0 } },
    /*1AA5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC7, { 0 } },
    /*1AA6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC8, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VUNPCKLPD                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AA7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0619, { 0 } },
    /*1AA8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x061A, { 0 } },
    /*1AA9*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x061B, { 0 } },
    /*1AAA*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x061C, { 0 } },
    /*1AAB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AC9, { 0 } },
    /*1AAC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ACA, { 0 } },
    /*1AAD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ACB, { 0 } },
    /*1AAE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ACC, { 0 } },
    /*1AAF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ACD, { 0 } },
    /*1AB0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ACE, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VUNPCKLPS                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AB1*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x061D, { 0 } },
    /*1AB2*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x061E, { 0 } },
    /*1AB3*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x061F, { 0 } },
    /*1AB4*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0620, { 0 } },
    /*1AB5*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ACF, { 0 } },
    /*1AB6*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD0, { 0 } },
    /*1AB7*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD1, { 0 } },
    /*1AB8*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD2, { 0 } },
    /*1AB9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD3, { 0 } },
    /*1ABA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD4, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VXORPD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1ABB*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0621, { 0 } },
    /*1ABC*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0622, { 0 } },
    /*1ABD*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0623, { 0 } },
    /*1ABE*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0624, { 0 } },
    /*1ABF*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD5, { 0 } },
    /*1AC0*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD6, { 0 } },
    /*1AC1*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD7, { 0 } },
    /*1AC2*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD8, { 0 } },
    /*1AC3*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AD9, { 0 } },
    /*1AC4*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ADA, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VXORPS                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AC5*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0625, { 0 } },
    /*1AC6*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0626, { 0 } },
    /*1AC7*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0627, { 0 } },
    /*1AC8*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0628, { 0 } },
    /*1AC9*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ADB, { 0 } },
    /*1ACA*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ADC, { 0 } },
    /*1ACB*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ADD, { 0 } },
    /*1ACC*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ADE, { 0 } },
    /*1ACD*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0ADF, { 0 } },
    /*1ACE*/ { ZYDIS_INSTRUCTION_ENCODING_EVEX   , 0x0AE0, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VZEROALL                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1ACF*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x0629, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* VZEROUPPER                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD0*/ { ZYDIS_INSTRUCTION_ENCODING_VEX    , 0x062A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WBINVD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x073A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRFSBASE                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x073B, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRGSBASE                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x073C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRMSR                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x073D, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRPKRU                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x073E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRSSD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x073F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRSSQ                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0740, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRUSSD                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0741, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* WRUSSQ                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AD9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0742, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XADD                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1ADA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0743, { 0 } },
    /*1ADB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0744, { 0 } },
    /*1ADC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0745, { 0 } },
    /*1ADD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0746, { 0 } },
    /*1ADE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0747, { 0 } },
    /*1ADF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0748, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XCHG                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AE0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0749, { 0 } },
    /*1AE1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x074A, { 0 } },
    /*1AE2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x074B, { 0 } },
    /*1AE3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x074C, { 0 } },
    /*1AE4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x074D, { 0 } },
    /*1AE5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x074E, { 0 } },
    /*1AE6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x074F, { 0 } },
    /*1AE7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0750, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XGETBV                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AE8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0751, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XLAT                                                                                       */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AE9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0752, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XOR                                                                                        */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1AEA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0753, { 0 } },
    /*1AEB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0754, { 0 } },
    /*1AEC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0755, { 0 } },
    /*1AED*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0756, { 0 } },
    /*1AEE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0757, { 0 } },
    /*1AEF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0758, { 0 } },
    /*1AF0*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0759, { 0 } },
    /*1AF1*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x075A, { 0 } },
    /*1AF2*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x075B, { 0 } },
    /*1AF3*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x075C, { 0 } },
    /*1AF4*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x075D, { 0 } },
    /*1AF5*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x075E, { 0 } },
    /*1AF6*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x075F, { 0 } },
    /*1AF7*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0760, { 0 } },
    /*1AF8*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0761, { 0 } },
    /*1AF9*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0762, { 0 } },
    /*1AFA*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0763, { 0 } },
    /*1AFB*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0764, { 0 } },
    /*1AFC*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0765, { 0 } },
    /*1AFD*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0766, { 0 } },
    /*1AFE*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0767, { 0 } },
    /*1AFF*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0768, { 0 } },
    /*1B00*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0769, { 0 } },
    /*1B01*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x076A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XORPD                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B02*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x076B, { 0 } },
    /*1B03*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x076C, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XORPS                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B04*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x076D, { 0 } },
    /*1B05*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x076E, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XRSTOR                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B06*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x076F, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XRSTOR64                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B07*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0770, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XRSTORS                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B08*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0771, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XRSTORS64                                                                                  */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B09*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0772, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVE                                                                                      */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B0A*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0773, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVE64                                                                                    */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B0B*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0774, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVEC                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B0C*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0775, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVEC64                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B0D*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0776, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVEOPT                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B0E*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0777, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVEOPT64                                                                                 */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B0F*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0778, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVES                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B10*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x0779, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSAVES64                                                                                   */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B11*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x077A, { 0 } },
    /* ------------------------------------------------------------------------------------------ */
    /* XSETBV                                                                                     */ 
    /* ------------------------------------------------------------------------------------------ */
    /*1B12*/ { ZYDIS_INSTRUCTION_ENCODING_DEFAULT, 0x077B, { 0 } }
};
