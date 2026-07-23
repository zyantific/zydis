#pragma pack(push, 1)

ZYDIS_DEFINE_SHORTSTRING_DATA(ADD, 1, "+");
static const struct ZydisPredefinedTokenADD_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_ADD = { 4, 2, { ZYDIS_TOKEN_DELIMITER, 0, '+', '\0' } };
static const ZydisPredefinedToken* const TOK_ADD = (const ZydisPredefinedToken* const)&TOK_DATA_ADD;

ZYDIS_DEFINE_SHORTSTRING_DATA(ADDR_RELATIVE, 1, "$");
static const struct ZydisPredefinedTokenADDR_RELATIVE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_ADDR_RELATIVE = { 4, 2, { ZYDIS_TOKEN_ADDRESS_REL, 0, '$', '\0' } };
static const ZydisPredefinedToken* const TOK_ADDR_RELATIVE = (const ZydisPredefinedToken* const)&TOK_DATA_ADDR_RELATIVE;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_1TO2, 7, " {1to2}");
static const struct ZydisPredefinedTokenDECO_1TO2_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_1TO2 = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, '1', 't', 'o', '2', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_1TO2 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_1TO2;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_1TO4, 7, " {1to4}");
static const struct ZydisPredefinedTokenDECO_1TO4_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_1TO4 = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, '1', 't', 'o', '4', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_1TO4 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_1TO4;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_1TO8, 7, " {1to8}");
static const struct ZydisPredefinedTokenDECO_1TO8_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_1TO8 = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, '1', 't', 'o', '8', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_1TO8 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_1TO8;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_1TO16, 8, " {1to16}");
static const struct ZydisPredefinedTokenDECO_1TO16_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_1TO16 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, '1', 't', 'o', '1', '6', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_1TO16 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_1TO16;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_1TO32, 8, " {1to32}");
static const struct ZydisPredefinedTokenDECO_1TO32_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_1TO32 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, '1', 't', 'o', '3', '2', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_1TO32 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_1TO32;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_1TO64, 8, " {1to64}");
static const struct ZydisPredefinedTokenDECO_1TO64_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_1TO64 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, '1', 't', 'o', '6', '4', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_1TO64 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_1TO64;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_4TO8, 7, " {4to8}");
static const struct ZydisPredefinedTokenDECO_4TO8_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_4TO8 = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, '4', 't', 'o', '8', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_4TO8 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_4TO8;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_4TO16, 8, " {4to16}");
static const struct ZydisPredefinedTokenDECO_4TO16_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_4TO16 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, '4', 't', 'o', '1', '6', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_4TO16 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_4TO16;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_8TO16, 8, " {8to16}");
static const struct ZydisPredefinedTokenDECO_8TO16_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_8TO16 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, '8', 't', 'o', '1', '6', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_8TO16 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_8TO16;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_AAAA, 7, " {aaaa}");
static const struct ZydisPredefinedTokenDECO_AAAA_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_AAAA = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'a', 'a', 'a', 'a', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_AAAA = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_AAAA;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_BADC, 7, " {badc}");
static const struct ZydisPredefinedTokenDECO_BADC_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_BADC = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'b', 'a', 'd', 'c', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_BADC = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_BADC;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_BBBB, 7, " {bbbb}");
static const struct ZydisPredefinedTokenDECO_BBBB_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_BBBB = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'b', 'b', 'b', 'b', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_BBBB = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_BBBB;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_BEGIN, 2, " {");
static const struct ZydisPredefinedTokenDECO_BEGIN_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[8];
} TOK_DATA_DECO_BEGIN = { 8, 6, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 0, '{', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_BEGIN = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_BEGIN;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_CCCC, 7, " {cccc}");
static const struct ZydisPredefinedTokenDECO_CCCC_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_CCCC = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'c', 'c', 'c', 'c', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_CCCC = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_CCCC;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_CDAB, 7, " {cdab}");
static const struct ZydisPredefinedTokenDECO_CDAB_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_CDAB = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'c', 'd', 'a', 'b', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_CDAB = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_CDAB;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DACB, 7, " {dacb}");
static const struct ZydisPredefinedTokenDECO_DACB_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_DACB = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'd', 'a', 'c', 'b', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DACB = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DACB;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DDDD, 7, " {dddd}");
static const struct ZydisPredefinedTokenDECO_DDDD_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_DDDD = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'd', 'd', 'd', 'd', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DDDD = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DDDD;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_0, 7, " {dfv=}");
static const struct ZydisPredefinedTokenDECO_DFV_0_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[19];
} TOK_DATA_DECO_DFV_0 = { 19, 17, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 5, 'd', 'f', 'v', '=', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_0 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_0;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_1, 9, " {dfv=cf}");
static const struct ZydisPredefinedTokenDECO_DFV_1_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_DFV_1 = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'd', 'f', 'v', '=', 'c', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_1 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_1;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_2, 9, " {dfv=zf}");
static const struct ZydisPredefinedTokenDECO_DFV_2_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_DFV_2 = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'd', 'f', 'v', '=', 'z', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_2 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_2;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_3, 13, " {dfv=cf, zf}");
static const struct ZydisPredefinedTokenDECO_DFV_3_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[25];
} TOK_DATA_DECO_DFV_3 = { 25, 23, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 11, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 'z', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_3 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_3;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_4, 9, " {dfv=sf}");
static const struct ZydisPredefinedTokenDECO_DFV_4_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_DFV_4 = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'd', 'f', 'v', '=', 's', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_4 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_4;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_5, 13, " {dfv=cf, sf}");
static const struct ZydisPredefinedTokenDECO_DFV_5_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[25];
} TOK_DATA_DECO_DFV_5 = { 25, 23, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 11, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 's', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_5 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_5;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_6, 13, " {dfv=zf, sf}");
static const struct ZydisPredefinedTokenDECO_DFV_6_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[25];
} TOK_DATA_DECO_DFV_6 = { 25, 23, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 11, 'd', 'f', 'v', '=', 'z', 'f', ',', ' ', 's', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_6 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_6;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_7, 17, " {dfv=cf, zf, sf}");
static const struct ZydisPredefinedTokenDECO_DFV_7_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[29];
} TOK_DATA_DECO_DFV_7 = { 29, 27, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 15, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 'z', 'f', ',', ' ', 's', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_7 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_7;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_8, 9, " {dfv=of}");
static const struct ZydisPredefinedTokenDECO_DFV_8_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_DFV_8 = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'd', 'f', 'v', '=', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_8 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_8;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_9, 13, " {dfv=cf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_9_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[25];
} TOK_DATA_DECO_DFV_9 = { 25, 23, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 11, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_9 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_9;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_A, 13, " {dfv=zf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_A_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[25];
} TOK_DATA_DECO_DFV_A = { 25, 23, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 11, 'd', 'f', 'v', '=', 'z', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_A = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_A;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_B, 17, " {dfv=cf, zf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_B_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[29];
} TOK_DATA_DECO_DFV_B = { 29, 27, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 15, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 'z', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_B = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_B;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_C, 13, " {dfv=sf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_C_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[25];
} TOK_DATA_DECO_DFV_C = { 25, 23, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 11, 'd', 'f', 'v', '=', 's', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_C = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_C;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_D, 17, " {dfv=cf, sf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_D_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[29];
} TOK_DATA_DECO_DFV_D = { 29, 27, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 15, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 's', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_D = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_D;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_E, 17, " {dfv=zf, sf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_E_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[29];
} TOK_DATA_DECO_DFV_E = { 29, 27, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 15, 'd', 'f', 'v', '=', 'z', 'f', ',', ' ', 's', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_E = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_E;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_DFV_F, 21, " {dfv=cf, zf, sf, of}");
static const struct ZydisPredefinedTokenDECO_DFV_F_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[33];
} TOK_DATA_DECO_DFV_F = { 33, 31, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 19, 'd', 'f', 'v', '=', 'c', 'f', ',', ' ', 'z', 'f', ',', ' ', 's', 'f', ',', ' ', 'o', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_DFV_F = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_DFV_F;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_EH, 5, " {eh}");
static const struct ZydisPredefinedTokenDECO_EH_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_DECO_EH = { 17, 15, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 3, 'e', 'h', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_EH = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_EH;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_END, 1, "}");
static const struct ZydisPredefinedTokenDECO_END_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_DECO_END = { 4, 2, { ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_END = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_END;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_FLOAT16, 10, " {float16}");
static const struct ZydisPredefinedTokenDECO_FLOAT16_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[22];
} TOK_DATA_DECO_FLOAT16 = { 22, 20, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 8, 'f', 'l', 'o', 'a', 't', '1', '6', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_FLOAT16 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_FLOAT16;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_NF, 5, "{nf} ");
static const struct ZydisPredefinedTokenDECO_NF_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_DECO_NF = { 17, 15, { ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 3, 'n', 'f', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 2, '}', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_NF = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_NF;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RD, 5, " {rd}");
static const struct ZydisPredefinedTokenDECO_RD_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_DECO_RD = { 17, 15, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 3, 'r', 'd', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RD = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RD;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RD_SAE, 9, " {rd-sae}");
static const struct ZydisPredefinedTokenDECO_RD_SAE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_RD_SAE = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'r', 'd', '-', 's', 'a', 'e', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RD_SAE = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RD_SAE;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RN, 5, " {rn}");
static const struct ZydisPredefinedTokenDECO_RN_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_DECO_RN = { 17, 15, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 3, 'r', 'n', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RN = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RN;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RN_SAE, 9, " {rn-sae}");
static const struct ZydisPredefinedTokenDECO_RN_SAE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_RN_SAE = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'r', 'n', '-', 's', 'a', 'e', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RN_SAE = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RN_SAE;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RU, 5, " {ru}");
static const struct ZydisPredefinedTokenDECO_RU_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_DECO_RU = { 17, 15, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 3, 'r', 'u', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RU = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RU;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RU_SAE, 9, " {ru-sae}");
static const struct ZydisPredefinedTokenDECO_RU_SAE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_RU_SAE = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'r', 'u', '-', 's', 'a', 'e', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RU_SAE = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RU_SAE;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RZ, 5, " {rz}");
static const struct ZydisPredefinedTokenDECO_RZ_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_DECO_RZ = { 17, 15, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 3, 'r', 'z', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RZ = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RZ;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_RZ_SAE, 9, " {rz-sae}");
static const struct ZydisPredefinedTokenDECO_RZ_SAE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_RZ_SAE = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'r', 'z', '-', 's', 'a', 'e', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_RZ_SAE = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_RZ_SAE;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_SAE, 6, " {sae}");
static const struct ZydisPredefinedTokenDECO_SAE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[18];
} TOK_DATA_DECO_SAE = { 18, 16, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 4, 's', 'a', 'e', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_SAE = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_SAE;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_SINT8, 8, " {sint8}");
static const struct ZydisPredefinedTokenDECO_SINT8_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_SINT8 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, 's', 'i', 'n', 't', '8', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_SINT8 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_SINT8;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_SINT16, 9, " {sint16}");
static const struct ZydisPredefinedTokenDECO_SINT16_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_SINT16 = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 's', 'i', 'n', 't', '1', '6', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_SINT16 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_SINT16;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_UINT8, 8, " {uint8}");
static const struct ZydisPredefinedTokenDECO_UINT8_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[20];
} TOK_DATA_DECO_UINT8 = { 20, 18, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 6, 'u', 'i', 'n', 't', '8', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_UINT8 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_UINT8;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_UINT16, 9, " {uint16}");
static const struct ZydisPredefinedTokenDECO_UINT16_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[21];
} TOK_DATA_DECO_UINT16 = { 21, 19, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 7, 'u', 'i', 'n', 't', '1', '6', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_UINT16 = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_UINT16;

ZYDIS_DEFINE_SHORTSTRING_DATA(DECO_ZERO, 4, " {z}");
static const struct ZydisPredefinedTokenDECO_ZERO_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[16];
} TOK_DATA_DECO_ZERO = { 16, 14, { ZYDIS_TOKEN_WHITESPACE, 2, ' ', '\0', ZYDIS_TOKEN_PARENTHESIS_OPEN, 2, '{', '\0', ZYDIS_TOKEN_DECORATOR, 2, 'z', '\0', ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, '}', '\0' } };
static const ZydisPredefinedToken* const TOK_DECO_ZERO = (const ZydisPredefinedToken* const)&TOK_DATA_DECO_ZERO;

ZYDIS_DEFINE_SHORTSTRING_DATA(DELIM_MEMORY, 1, ",");
static const struct ZydisPredefinedTokenDELIM_MEMORY_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_DELIM_MEMORY = { 4, 2, { ZYDIS_TOKEN_DELIMITER, 0, ',', '\0' } };
static const ZydisPredefinedToken* const TOK_DELIM_MEMORY = (const ZydisPredefinedToken* const)&TOK_DATA_DELIM_MEMORY;

ZYDIS_DEFINE_SHORTSTRING_DATA(DELIM_MNEMONIC, 1, " ");
static const struct ZydisPredefinedTokenDELIM_MNEMONIC_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_DELIM_MNEMONIC = { 4, 2, { ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_DELIM_MNEMONIC = (const ZydisPredefinedToken* const)&TOK_DATA_DELIM_MNEMONIC;

ZYDIS_DEFINE_SHORTSTRING_DATA(DELIM_OPERAND, 2, ", ");
static const struct ZydisPredefinedTokenDELIM_OPERAND_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[8];
} TOK_DATA_DELIM_OPERAND = { 8, 6, { ZYDIS_TOKEN_DELIMITER, 2, ',', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_DELIM_OPERAND = (const ZydisPredefinedToken* const)&TOK_DATA_DELIM_OPERAND;

ZYDIS_DEFINE_SHORTSTRING_DATA(DELIM_SEGMENT, 1, ":");
static const struct ZydisPredefinedTokenDELIM_SEGMENT_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_DELIM_SEGMENT = { 4, 2, { ZYDIS_TOKEN_DELIMITER, 0, ':', '\0' } };
static const ZydisPredefinedToken* const TOK_DELIM_SEGMENT = (const ZydisPredefinedToken* const)&TOK_DATA_DELIM_SEGMENT;

ZYDIS_DEFINE_SHORTSTRING_DATA(FAR, 4, " far");
ZYDIS_DEFINE_SHORTSTRING_DATA(FAR_ATT, 1, "l");
ZYDIS_DEFINE_SHORTSTRING_DATA(IMMEDIATE, 1, "$");
static const struct ZydisPredefinedTokenIMMEDIATE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_IMMEDIATE = { 4, 2, { ZYDIS_TOKEN_IMMEDIATE, 0, '$', '\0' } };
static const ZydisPredefinedToken* const TOK_IMMEDIATE = (const ZydisPredefinedToken* const)&TOK_DATA_IMMEDIATE;

ZYDIS_DEFINE_SHORTSTRING_DATA(INVALID_MNEMONIC, 7, "invalid");
static const struct ZydisPredefinedTokenINVALID_MNEMONIC_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[10];
} TOK_DATA_INVALID_MNEMONIC = { 10, 2, { ZYDIS_TOKEN_MNEMONIC, 0, 'i', 'n', 'v', 'a', 'l', 'i', 'd', '\0' } };
static const ZydisPredefinedToken* const TOK_INVALID_MNEMONIC = (const ZydisPredefinedToken* const)&TOK_DATA_INVALID_MNEMONIC;

ZYDIS_DEFINE_SHORTSTRING_DATA(INVALID_REG, 7, "invalid");
static const struct ZydisPredefinedTokenINVALID_REG_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[10];
} TOK_DATA_INVALID_REG = { 10, 2, { ZYDIS_TOKEN_REGISTER, 0, 'i', 'n', 'v', 'a', 'l', 'i', 'd', '\0' } };
static const ZydisPredefinedToken* const TOK_INVALID_REG = (const ZydisPredefinedToken* const)&TOK_DATA_INVALID_REG;

ZYDIS_DEFINE_SHORTSTRING_DATA(MEMORY_BEGIN_ATT, 1, "(");
static const struct ZydisPredefinedTokenMEMORY_BEGIN_ATT_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_MEMORY_BEGIN_ATT = { 4, 2, { ZYDIS_TOKEN_PARENTHESIS_OPEN, 0, '(', '\0' } };
static const ZydisPredefinedToken* const TOK_MEMORY_BEGIN_ATT = (const ZydisPredefinedToken* const)&TOK_DATA_MEMORY_BEGIN_ATT;

ZYDIS_DEFINE_SHORTSTRING_DATA(MEMORY_BEGIN_INTEL, 1, "[");
static const struct ZydisPredefinedTokenMEMORY_BEGIN_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_MEMORY_BEGIN_INTEL = { 4, 2, { ZYDIS_TOKEN_PARENTHESIS_OPEN, 0, '[', '\0' } };
static const ZydisPredefinedToken* const TOK_MEMORY_BEGIN_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_MEMORY_BEGIN_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(MEMORY_END_ATT, 1, ")");
static const struct ZydisPredefinedTokenMEMORY_END_ATT_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_MEMORY_END_ATT = { 4, 2, { ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, ')', '\0' } };
static const ZydisPredefinedToken* const TOK_MEMORY_END_ATT = (const ZydisPredefinedToken* const)&TOK_DATA_MEMORY_END_ATT;

ZYDIS_DEFINE_SHORTSTRING_DATA(MEMORY_END_INTEL, 1, "]");
static const struct ZydisPredefinedTokenMEMORY_END_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_MEMORY_END_INTEL = { 4, 2, { ZYDIS_TOKEN_PARENTHESIS_CLOSE, 0, ']', '\0' } };
static const ZydisPredefinedToken* const TOK_MEMORY_END_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_MEMORY_END_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(MUL, 1, "*");
static const struct ZydisPredefinedTokenMUL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_MUL = { 4, 2, { ZYDIS_TOKEN_DELIMITER, 0, '*', '\0' } };
static const ZydisPredefinedToken* const TOK_MUL = (const ZydisPredefinedToken* const)&TOK_DATA_MUL;

ZYDIS_DEFINE_SHORTSTRING_DATA(NEAR, 5, " near");
ZYDIS_DEFINE_SHORTSTRING_DATA(NF, 2, "nf");
ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_BND, 4, "bnd ");
static const struct ZydisPredefinedTokenPREF_BND_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[10];
} TOK_DATA_PREF_BND = { 10, 8, { ZYDIS_TOKEN_PREFIX, 4, 'b', 'n', 'd', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_BND = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_BND;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_LOCK, 5, "lock ");
static const struct ZydisPredefinedTokenPREF_LOCK_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[11];
} TOK_DATA_PREF_LOCK = { 11, 9, { ZYDIS_TOKEN_PREFIX, 5, 'l', 'o', 'c', 'k', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_LOCK = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_LOCK;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REP, 4, "rep ");
static const struct ZydisPredefinedTokenPREF_REP_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[10];
} TOK_DATA_PREF_REP = { 10, 8, { ZYDIS_TOKEN_PREFIX, 4, 'r', 'e', 'p', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_REP = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_REP;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REPE, 5, "repe ");
static const struct ZydisPredefinedTokenPREF_REPE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[11];
} TOK_DATA_PREF_REPE = { 11, 9, { ZYDIS_TOKEN_PREFIX, 5, 'r', 'e', 'p', 'e', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_REPE = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_REPE;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REPNE, 6, "repne ");
static const struct ZydisPredefinedTokenPREF_REPNE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[12];
} TOK_DATA_PREF_REPNE = { 12, 10, { ZYDIS_TOKEN_PREFIX, 6, 'r', 'e', 'p', 'n', 'e', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_REPNE = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_REPNE;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_4A, 7, "rex.wx ");
static const struct ZydisPredefinedTokenPREF_REX_4A_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[13];
} TOK_DATA_PREF_REX_4A = { 13, 11, { ZYDIS_TOKEN_PREFIX, 7, 'r', 'e', 'x', '.', 'w', 'x', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_4B, 8, "rex.wxb ");
static const struct ZydisPredefinedTokenPREF_REX_4B_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[14];
} TOK_DATA_PREF_REX_4B = { 14, 12, { ZYDIS_TOKEN_PREFIX, 8, 'r', 'e', 'x', '.', 'w', 'x', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_4C, 7, "rex.wr ");
static const struct ZydisPredefinedTokenPREF_REX_4C_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[13];
} TOK_DATA_PREF_REX_4C = { 13, 11, { ZYDIS_TOKEN_PREFIX, 7, 'r', 'e', 'x', '.', 'w', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_4D, 8, "rex.wrb ");
static const struct ZydisPredefinedTokenPREF_REX_4D_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[14];
} TOK_DATA_PREF_REX_4D = { 14, 12, { ZYDIS_TOKEN_PREFIX, 8, 'r', 'e', 'x', '.', 'w', 'r', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_4E, 8, "rex.wrx ");
static const struct ZydisPredefinedTokenPREF_REX_4E_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[14];
} TOK_DATA_PREF_REX_4E = { 14, 12, { ZYDIS_TOKEN_PREFIX, 8, 'r', 'e', 'x', '.', 'w', 'r', 'x', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_4F, 9, "rex.wrxb ");
static const struct ZydisPredefinedTokenPREF_REX_4F_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[15];
} TOK_DATA_PREF_REX_4F = { 15, 13, { ZYDIS_TOKEN_PREFIX, 9, 'r', 'e', 'x', '.', 'w', 'r', 'x', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_40, 4, "rex ");
static const struct ZydisPredefinedTokenPREF_REX_40_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[10];
} TOK_DATA_PREF_REX_40 = { 10, 8, { ZYDIS_TOKEN_PREFIX, 4, 'r', 'e', 'x', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_41, 6, "rex.b ");
static const struct ZydisPredefinedTokenPREF_REX_41_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[12];
} TOK_DATA_PREF_REX_41 = { 12, 10, { ZYDIS_TOKEN_PREFIX, 6, 'r', 'e', 'x', '.', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_42, 6, "rex.x ");
static const struct ZydisPredefinedTokenPREF_REX_42_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[12];
} TOK_DATA_PREF_REX_42 = { 12, 10, { ZYDIS_TOKEN_PREFIX, 6, 'r', 'e', 'x', '.', 'x', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_43, 7, "rex.xb ");
static const struct ZydisPredefinedTokenPREF_REX_43_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[13];
} TOK_DATA_PREF_REX_43 = { 13, 11, { ZYDIS_TOKEN_PREFIX, 7, 'r', 'e', 'x', '.', 'x', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_44, 6, "rex.r ");
static const struct ZydisPredefinedTokenPREF_REX_44_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[12];
} TOK_DATA_PREF_REX_44 = { 12, 10, { ZYDIS_TOKEN_PREFIX, 6, 'r', 'e', 'x', '.', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_45, 7, "rex.rb ");
static const struct ZydisPredefinedTokenPREF_REX_45_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[13];
} TOK_DATA_PREF_REX_45 = { 13, 11, { ZYDIS_TOKEN_PREFIX, 7, 'r', 'e', 'x', '.', 'r', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_46, 7, "rex.rx ");
static const struct ZydisPredefinedTokenPREF_REX_46_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[13];
} TOK_DATA_PREF_REX_46 = { 13, 11, { ZYDIS_TOKEN_PREFIX, 7, 'r', 'e', 'x', '.', 'r', 'x', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_47, 8, "rex.rxb ");
static const struct ZydisPredefinedTokenPREF_REX_47_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[14];
} TOK_DATA_PREF_REX_47 = { 14, 12, { ZYDIS_TOKEN_PREFIX, 8, 'r', 'e', 'x', '.', 'r', 'x', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_48, 6, "rex.w ");
static const struct ZydisPredefinedTokenPREF_REX_48_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[12];
} TOK_DATA_PREF_REX_48 = { 12, 10, { ZYDIS_TOKEN_PREFIX, 6, 'r', 'e', 'x', '.', 'w', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_REX_49, 7, "rex.wb ");
static const struct ZydisPredefinedTokenPREF_REX_49_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[13];
} TOK_DATA_PREF_REX_49 = { 13, 11, { ZYDIS_TOKEN_PREFIX, 7, 'r', 'e', 'x', '.', 'w', 'b', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_SEG_CS, 3, "cs ");
static const struct ZydisPredefinedTokenPREF_SEG_CS_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[9];
} TOK_DATA_PREF_SEG_CS = { 9, 7, { ZYDIS_TOKEN_PREFIX, 3, 'c', 's', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_SEG_CS = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_SEG_CS;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_SEG_DS, 3, "ds ");
static const struct ZydisPredefinedTokenPREF_SEG_DS_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[9];
} TOK_DATA_PREF_SEG_DS = { 9, 7, { ZYDIS_TOKEN_PREFIX, 3, 'd', 's', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_SEG_DS = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_SEG_DS;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_SEG_ES, 3, "es ");
static const struct ZydisPredefinedTokenPREF_SEG_ES_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[9];
} TOK_DATA_PREF_SEG_ES = { 9, 7, { ZYDIS_TOKEN_PREFIX, 3, 'e', 's', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_SEG_ES = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_SEG_ES;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_SEG_FS, 3, "fs ");
static const struct ZydisPredefinedTokenPREF_SEG_FS_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[9];
} TOK_DATA_PREF_SEG_FS = { 9, 7, { ZYDIS_TOKEN_PREFIX, 3, 'f', 's', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_SEG_FS = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_SEG_FS;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_SEG_GS, 3, "gs ");
static const struct ZydisPredefinedTokenPREF_SEG_GS_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[9];
} TOK_DATA_PREF_SEG_GS = { 9, 7, { ZYDIS_TOKEN_PREFIX, 3, 'g', 's', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_SEG_GS = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_SEG_GS;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_SEG_SS, 3, "ss ");
static const struct ZydisPredefinedTokenPREF_SEG_SS_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[9];
} TOK_DATA_PREF_SEG_SS = { 9, 7, { ZYDIS_TOKEN_PREFIX, 3, 's', 's', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_SEG_SS = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_SEG_SS;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_XACQUIRE, 9, "xacquire ");
static const struct ZydisPredefinedTokenPREF_XACQUIRE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[15];
} TOK_DATA_PREF_XACQUIRE = { 15, 13, { ZYDIS_TOKEN_PREFIX, 9, 'x', 'a', 'c', 'q', 'u', 'i', 'r', 'e', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_XACQUIRE = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_XACQUIRE;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_XRELEASE, 9, "xrelease ");
static const struct ZydisPredefinedTokenPREF_XRELEASE_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[15];
} TOK_DATA_PREF_XRELEASE = { 15, 13, { ZYDIS_TOKEN_PREFIX, 9, 'x', 'r', 'e', 'l', 'e', 'a', 's', 'e', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_XRELEASE = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_XRELEASE;

ZYDIS_DEFINE_SHORTSTRING_DATA(PREF_NOTRACK, 8, "notrack ");
static const struct ZydisPredefinedTokenPREF_NOTRACK_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[14];
} TOK_DATA_PREF_NOTRACK = { 14, 12, { ZYDIS_TOKEN_PREFIX, 8, 'n', 'o', 't', 'r', 'a', 'c', 'k', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_PREF_NOTRACK = (const ZydisPredefinedToken* const)&TOK_DATA_PREF_NOTRACK;

ZYDIS_DEFINE_SHORTSTRING_DATA(REGISTER, 1, "%");
static const struct ZydisPredefinedTokenREGISTER_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_REGISTER = { 4, 2, { ZYDIS_TOKEN_REGISTER, 0, '%', '\0' } };
static const ZydisPredefinedToken* const TOK_REGISTER = (const ZydisPredefinedToken* const)&TOK_DATA_REGISTER;

ZYDIS_DEFINE_SHORTSTRING_DATA(SHORT, 6, " short");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_8_ATT, 1, "b");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_8_INTEL, 9, "byte ptr ");
static const struct ZydisPredefinedTokenSIZE_8_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[15];
} TOK_DATA_SIZE_8_INTEL = { 15, 13, { ZYDIS_TOKEN_TYPECAST, 9, 'b', 'y', 't', 'e', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_8_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_8_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_16_ATT, 1, "w");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_16_INTEL, 9, "word ptr ");
static const struct ZydisPredefinedTokenSIZE_16_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[15];
} TOK_DATA_SIZE_16_INTEL = { 15, 13, { ZYDIS_TOKEN_TYPECAST, 9, 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_16_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_16_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_16_MASM_BCST, 10, "word bcst ");
static const struct ZydisPredefinedTokenSIZE_16_MASM_BCST_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[16];
} TOK_DATA_SIZE_16_MASM_BCST = { 16, 14, { ZYDIS_TOKEN_TYPECAST, 10, 'w', 'o', 'r', 'd', ' ', 'b', 'c', 's', 't', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_16_MASM_BCST = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_16_MASM_BCST;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_32_ATT, 1, "l");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_32_INTEL, 10, "dword ptr ");
static const struct ZydisPredefinedTokenSIZE_32_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[16];
} TOK_DATA_SIZE_32_INTEL = { 16, 14, { ZYDIS_TOKEN_TYPECAST, 10, 'd', 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_32_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_32_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_32_MASM_BCST, 11, "dword bcst ");
static const struct ZydisPredefinedTokenSIZE_32_MASM_BCST_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_SIZE_32_MASM_BCST = { 17, 15, { ZYDIS_TOKEN_TYPECAST, 11, 'd', 'w', 'o', 'r', 'd', ' ', 'b', 'c', 's', 't', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_32_MASM_BCST = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_32_MASM_BCST;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_48, 10, "fword ptr ");
static const struct ZydisPredefinedTokenSIZE_48_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[16];
} TOK_DATA_SIZE_48 = { 16, 14, { ZYDIS_TOKEN_TYPECAST, 10, 'f', 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_48 = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_48;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_64_ATT, 1, "q");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_64_INTEL, 10, "qword ptr ");
static const struct ZydisPredefinedTokenSIZE_64_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[16];
} TOK_DATA_SIZE_64_INTEL = { 16, 14, { ZYDIS_TOKEN_TYPECAST, 10, 'q', 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_64_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_64_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_64_MASM_BCST, 11, "qword bcst ");
static const struct ZydisPredefinedTokenSIZE_64_MASM_BCST_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[17];
} TOK_DATA_SIZE_64_MASM_BCST = { 17, 15, { ZYDIS_TOKEN_TYPECAST, 11, 'q', 'w', 'o', 'r', 'd', ' ', 'b', 'c', 's', 't', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_64_MASM_BCST = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_64_MASM_BCST;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_80, 10, "tbyte ptr ");
static const struct ZydisPredefinedTokenSIZE_80_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[16];
} TOK_DATA_SIZE_80 = { 16, 14, { ZYDIS_TOKEN_TYPECAST, 10, 't', 'b', 'y', 't', 'e', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_80 = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_80;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_128_ATT, 1, "x");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_128_INTEL, 12, "xmmword ptr ");
static const struct ZydisPredefinedTokenSIZE_128_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[18];
} TOK_DATA_SIZE_128_INTEL = { 18, 16, { ZYDIS_TOKEN_TYPECAST, 12, 'x', 'm', 'm', 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_128_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_128_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_256_ATT, 1, "y");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_256_INTEL, 12, "ymmword ptr ");
static const struct ZydisPredefinedTokenSIZE_256_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[18];
} TOK_DATA_SIZE_256_INTEL = { 18, 16, { ZYDIS_TOKEN_TYPECAST, 12, 'y', 'm', 'm', 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_256_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_256_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_512_ATT, 1, "z");
ZYDIS_DEFINE_SHORTSTRING_DATA(SIZE_512_INTEL, 12, "zmmword ptr ");
static const struct ZydisPredefinedTokenSIZE_512_INTEL_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[18];
} TOK_DATA_SIZE_512_INTEL = { 18, 16, { ZYDIS_TOKEN_TYPECAST, 12, 'z', 'm', 'm', 'w', 'o', 'r', 'd', ' ', 'p', 't', 'r', '\0', ZYDIS_TOKEN_WHITESPACE, 0, ' ', '\0' } };
static const ZydisPredefinedToken* const TOK_SIZE_512_INTEL = (const ZydisPredefinedToken* const)&TOK_DATA_SIZE_512_INTEL;

ZYDIS_DEFINE_SHORTSTRING_DATA(SUB, 1, "-");
static const struct ZydisPredefinedTokenSUB_
{
  ZyanU8 size;
  ZyanU8 next;
  ZyanU8 data[4];
} TOK_DATA_SUB = { 4, 2, { ZYDIS_TOKEN_DELIMITER, 0, '-', '\0' } };
static const ZydisPredefinedToken* const TOK_SUB = (const ZydisPredefinedToken* const)&TOK_DATA_SUB;

ZYDIS_DEFINE_SHORTSTRING_DATA(WHITESPACE, 1, " ");
#pragma pack(pop)
