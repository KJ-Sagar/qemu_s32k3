/*==================================================================================================
*   Project              : RTD AUTOSAR 4.9
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.9.0
*   Autosar Revision     : ASR_REL_4_9_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 7.0.1
*   Build Version        : S32K3_RTD_7_0_1_D2602_ASR_REL_4_9_REV_0000_20260206
*
*   Copyright 2020 - 2026 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms. By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms. If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file    Port_Cfg.c
*
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Port.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief        Parameters that shall be published within the Port driver header file and also in the
*               module's description file
* @details      The integration of incompatible files shall be avoided.
*
*/
#define PORT_VENDOR_ID_CFG_C                       43
#define PORT_AR_RELEASE_MAJOR_VERSION_CFG_C        4
#define PORT_AR_RELEASE_MINOR_VERSION_CFG_C        9
#define PORT_AR_RELEASE_REVISION_VERSION_CFG_C     0
#define PORT_SW_MAJOR_VERSION_CFG_C                7
#define PORT_SW_MINOR_VERSION_CFG_C                0
#define PORT_SW_PATCH_VERSION_CFG_C                1

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
/* Check if Port_Cfg.c and Port.h are of the same Autosar version */
#if (PORT_VENDOR_ID_CFG_C != PORT_VENDOR_ID)
    #error "Port_Cfg.c and Port.h have different vendor ids"
#endif
/* Check if Port_Cfg.c and Port.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.c and Port.h are different"
#endif
/* Check if Port_Cfg.c and Port.h are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_CFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_CFG_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_Cfg.c and Port.h are different"
#endif

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/
#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)

#define PORT_START_SEC_CONST_16
#include "Port_MemMap.h"

/**
* @brief Array of elements storing indexes in Port_<SIUL2 Instance>_aInMuxSettings table where IN settings for each pad reside on SIUL2 instance
*/
static const uint16 Port_SIUL2_0_au16InMuxSettingsIndex[324] = 
{
    /* Index to address the input settings for pad 0*/
    (uint16)1,
    /* Index to address the input settings for pad 1*/
    (uint16)8,
    /* Index to address the input settings for pad 2*/
    (uint16)13,
    /* Index to address the input settings for pad 3*/
    (uint16)20,
    /* Index to address the input settings for pad 4*/
    (uint16)27,
    /* Index to address the input settings for pad 5*/
    (uint16)30,
    /* Index to address the input settings for pad 6*/
    (uint16)31,
    /* Index to address the input settings for pad 7*/
    (uint16)40,
    /* Index to address the input settings for pad 8*/
    (uint16)46,
    /* Index to address the input settings for pad 9*/
    (uint16)52,
    /* Index to address the input settings for pad 10*/
    (uint16)58,
    /* Index to address the input settings for pad 11*/
    (uint16)61,
    /* Index to address the input settings for pad 12*/
    (uint16)67,
    /* Index to address the input settings for pad 13*/
    (uint16)74,
    /* Index to address the input settings for pad 14*/
    (uint16)80,
    /* Index to address the input settings for pad 15*/
    (uint16)86,
    /* Index to address the input settings for pad 16*/
    (uint16)93,
    /* Index to address the input settings for pad 17*/
    (uint16)101,
    /* Index to address the input settings for pad 18*/
    (uint16)105,
    /* Index to address the input settings for pad 19*/
    (uint16)112,
    /* Index to address the input settings for pad 20*/
    (uint16)118,
    /* Index to address the input settings for pad 21*/
    (uint16)123,
    /* Index to address the input settings for pad 22*/
    (uint16)130,
    /* Index to address the input settings for pad 23*/
    (uint16)134,
    /* Index to address the input settings for pad 24*/
    (uint16)136,
    /* Index to address the input settings for pad 25*/
    (uint16)138,
    /* Index to address the input settings for pad 26*/
    (uint16)142,
    /* Index to address the input settings for pad 27*/
    (uint16)148,
    /* Index to address the input settings for pad 28*/
    (uint16)153,
    /* Index to address the input settings for pad 29*/
    (uint16)159,
    /* Index to address the input settings for pad 30*/
    (uint16)165,
    /* Index to address the input settings for pad 31*/
    (uint16)171,
    /* Index to address the input settings for pad 32*/
    (uint16)178,
    /* Index to address the input settings for pad 33*/
    (uint16)186,
    /* Index to address the input settings for pad 34*/
    (uint16)193,
    /* Index to address the input settings for pad 35*/
    (uint16)201,
    /* Index to address the input settings for pad 36*/
    (uint16)211,
    /* Index to address the input settings for pad 37*/
    (uint16)218,
    /* Index to address the input settings for pad 38*/
    (uint16)0,
    /* Index to address the input settings for pad 39*/
    (uint16)0,
    /* Index to address the input settings for pad 40*/
    (uint16)224,
    /* Index to address the input settings for pad 41*/
    (uint16)230,
    /* Index to address the input settings for pad 42*/
    (uint16)236,
    /* Index to address the input settings for pad 43*/
    (uint16)241,
    /* Index to address the input settings for pad 44*/
    (uint16)247,
    /* Index to address the input settings for pad 45*/
    (uint16)253,
    /* Index to address the input settings for pad 46*/
    (uint16)260,
    /* Index to address the input settings for pad 47*/
    (uint16)265,
    /* Index to address the input settings for pad 48*/
    (uint16)270,
    /* Index to address the input settings for pad 49*/
    (uint16)276,
    /* Index to address the input settings for pad 50*/
    (uint16)283,
    /* Index to address the input settings for pad 51*/
    (uint16)289,
    /* Index to address the input settings for pad 52*/
    (uint16)296,
    /* Index to address the input settings for pad 53*/
    (uint16)301,
    /* Index to address the input settings for pad 54*/
    (uint16)306,
    /* Index to address the input settings for pad 55*/
    (uint16)315,
    /* Index to address the input settings for pad 56*/
    (uint16)325,
    /* Index to address the input settings for pad 57*/
    (uint16)332,
    /* Index to address the input settings for pad 58*/
    (uint16)340,
    /* Index to address the input settings for pad 59*/
    (uint16)346,
    /* Index to address the input settings for pad 60*/
    (uint16)353,
    /* Index to address the input settings for pad 61*/
    (uint16)360,
    /* Index to address the input settings for pad 62*/
    (uint16)367,
    /* Index to address the input settings for pad 63*/
    (uint16)368,
    /* Index to address the input settings for pad 64*/
    (uint16)371,
    /* Index to address the input settings for pad 65*/
    (uint16)378,
    /* Index to address the input settings for pad 66*/
    (uint16)388,
    /* Index to address the input settings for pad 67*/
    (uint16)398,
    /* Index to address the input settings for pad 68*/
    (uint16)402,
    /* Index to address the input settings for pad 69*/
    (uint16)406,
    /* Index to address the input settings for pad 70*/
    (uint16)411,
    /* Index to address the input settings for pad 71*/
    (uint16)419,
    /* Index to address the input settings for pad 72*/
    (uint16)426,
    /* Index to address the input settings for pad 73*/
    (uint16)433,
    /* Index to address the input settings for pad 74*/
    (uint16)440,
    /* Index to address the input settings for pad 75*/
    (uint16)448,
    /* Index to address the input settings for pad 76*/
    (uint16)456,
    /* Index to address the input settings for pad 77*/
    (uint16)463,
    /* Index to address the input settings for pad 78*/
    (uint16)469,
    /* Index to address the input settings for pad 79*/
    (uint16)481,
    /* Index to address the input settings for pad 80*/
    (uint16)493,
    /* Index to address the input settings for pad 81*/
    (uint16)504,
    /* Index to address the input settings for pad 82*/
    (uint16)510,
    /* Index to address the input settings for pad 83*/
    (uint16)516,
    /* Index to address the input settings for pad 84*/
    (uint16)522,
    /* Index to address the input settings for pad 85*/
    (uint16)527,
    /* Index to address the input settings for pad 86*/
    (uint16)531,
    /* Index to address the input settings for pad 87*/
    (uint16)532,
    /* Index to address the input settings for pad 88*/
    (uint16)535,
    /* Index to address the input settings for pad 89*/
    (uint16)540,
    /* Index to address the input settings for pad 90*/
    (uint16)547,
    /* Index to address the input settings for pad 91*/
    (uint16)555,
    /* Index to address the input settings for pad 92*/
    (uint16)562,
    /* Index to address the input settings for pad 93*/
    (uint16)568,
    /* Index to address the input settings for pad 94*/
    (uint16)577,
    /* Index to address the input settings for pad 95*/
    (uint16)582,
    /* Index to address the input settings for pad 96*/
    (uint16)587,
    /* Index to address the input settings for pad 97*/
    (uint16)593,
    /* Index to address the input settings for pad 98*/
    (uint16)599,
    /* Index to address the input settings for pad 99*/
    (uint16)607,
    /* Index to address the input settings for pad 100*/
    (uint16)614,
    /* Index to address the input settings for pad 101*/
    (uint16)618,
    /* Index to address the input settings for pad 102*/
    (uint16)629,
    /* Index to address the input settings for pad 103*/
    (uint16)640,
    /* Index to address the input settings for pad 104*/
    (uint16)648,
    /* Index to address the input settings for pad 105*/
    (uint16)658,
    /* Index to address the input settings for pad 106*/
    (uint16)667,
    /* Index to address the input settings for pad 107*/
    (uint16)675,
    /* Index to address the input settings for pad 108*/
    (uint16)684,
    /* Index to address the input settings for pad 109*/
    (uint16)692,
    /* Index to address the input settings for pad 110*/
    (uint16)700,
    /* Index to address the input settings for pad 111*/
    (uint16)710,
    /* Index to address the input settings for pad 112*/
    (uint16)722,
    /* Index to address the input settings for pad 113*/
    (uint16)727,
    /* Index to address the input settings for pad 114*/
    (uint16)735,
    /* Index to address the input settings for pad 115*/
    (uint16)737,
    /* Index to address the input settings for pad 116*/
    (uint16)740,
    /* Index to address the input settings for pad 117*/
    (uint16)746,
    /* Index to address the input settings for pad 118*/
    (uint16)750,
    /* Index to address the input settings for pad 119*/
    (uint16)754,
    /* Index to address the input settings for pad 120*/
    (uint16)758,
    /* Index to address the input settings for pad 121*/
    (uint16)762,
    /* Index to address the input settings for pad 122*/
    (uint16)763,
    /* Index to address the input settings for pad 123*/
    (uint16)769,
    /* Index to address the input settings for pad 124*/
    (uint16)774,
    /* Index to address the input settings for pad 125*/
    (uint16)778,
    /* Index to address the input settings for pad 126*/
    (uint16)782,
    /* Index to address the input settings for pad 127*/
    (uint16)784,
    /* Index to address the input settings for pad 128*/
    (uint16)788,
    /* Index to address the input settings for pad 129*/
    (uint16)792,
    /* Index to address the input settings for pad 130*/
    (uint16)796,
    /* Index to address the input settings for pad 131*/
    (uint16)803,
    /* Index to address the input settings for pad 132*/
    (uint16)812,
    /* Index to address the input settings for pad 133*/
    (uint16)819,
    /* Index to address the input settings for pad 134*/
    (uint16)825,
    /* Index to address the input settings for pad 135*/
    (uint16)830,
    /* Index to address the input settings for pad 136*/
    (uint16)834,
    /* Index to address the input settings for pad 137*/
    (uint16)841,
    /* Index to address the input settings for pad 138*/
    (uint16)850,
    /* Index to address the input settings for pad 139*/
    (uint16)856,
    /* Index to address the input settings for pad 140*/
    (uint16)862,
    /* Index to address the input settings for pad 141*/
    (uint16)0,
    /* Index to address the input settings for pad 142*/
    (uint16)869,
    /* Index to address the input settings for pad 143*/
    (uint16)876,
    /* Index to address the input settings for pad 144*/
    (uint16)883,
    /* Index to address the input settings for pad 145*/
    (uint16)889,
    /* Index to address the input settings for pad 146*/
    (uint16)891,
    /* Index to address the input settings for pad 147*/
    (uint16)893,
    /* Index to address the input settings for pad 148*/
    (uint16)894,
    /* Index to address the input settings for pad 149*/
    (uint16)895,
    /* Index to address the input settings for pad 150*/
    (uint16)898,
    /* Index to address the input settings for pad 151*/
    (uint16)901,
    /* Index to address the input settings for pad 152*/
    (uint16)904,
    /* Index to address the input settings for pad 153*/
    (uint16)910,
    /* Index to address the input settings for pad 154*/
    (uint16)914,
    /* Index to address the input settings for pad 155*/
    (uint16)916,
    /* Index to address the input settings for pad 156*/
    (uint16)918,
    /* Index to address the input settings for pad 157*/
    (uint16)919,
    /* Index to address the input settings for pad 158*/
    (uint16)921,
    /* Index to address the input settings for pad 159*/
    (uint16)922,
    /* Index to address the input settings for pad 160*/
    (uint16)924,
    /* Index to address the input settings for pad 161*/
    (uint16)928,
    /* Index to address the input settings for pad 162*/
    (uint16)932,
    /* Index to address the input settings for pad 163*/
    (uint16)936,
    /* Index to address the input settings for pad 164*/
    (uint16)940,
    /* Index to address the input settings for pad 165*/
    (uint16)944,
    /* Index to address the input settings for pad 166*/
    (uint16)947,
    /* Index to address the input settings for pad 167*/
    (uint16)949,
    /* Index to address the input settings for pad 168*/
    (uint16)954,
    /* Index to address the input settings for pad 169*/
    (uint16)958,
    /* Index to address the input settings for pad 170*/
    (uint16)960,
    /* Index to address the input settings for pad 171*/
    (uint16)962,
    /* Index to address the input settings for pad 172*/
    (uint16)965,
    /* Index to address the input settings for pad 173*/
    (uint16)969,
    /* Index to address the input settings for pad 174*/
    (uint16)973,
    /* Index to address the input settings for pad 175*/
    (uint16)977,
    /* Index to address the input settings for pad 176*/
    (uint16)982,
    /* Index to address the input settings for pad 177*/
    (uint16)986,
    /* Index to address the input settings for pad 178*/
    (uint16)989,
    /* Index to address the input settings for pad 179*/
    (uint16)993,
    /* Index to address the input settings for pad 180*/
    (uint16)997,
    /* Index to address the input settings for pad 181*/
    (uint16)1003,
    /* Index to address the input settings for pad 182*/
    (uint16)1010,
    /* Index to address the input settings for pad 183*/
    (uint16)1013,
    /* Index to address the input settings for pad 184*/
    (uint16)1017,
    /* Index to address the input settings for pad 185*/
    (uint16)1019,
    /* Index to address the input settings for pad 186*/
    (uint16)1023,
    /* Index to address the input settings for pad 187*/
    (uint16)1027,
    /* Index to address the input settings for pad 188*/
    (uint16)1030,
    /* Index to address the input settings for pad 189*/
    (uint16)1035,
    /* Index to address the input settings for pad 190*/
    (uint16)1038,
    /* Index to address the input settings for pad 191*/
    (uint16)1040,
    /* Index to address the input settings for pad 192*/
    (uint16)1042,
    /* Index to address the input settings for pad 193*/
    (uint16)1045,
    /* Index to address the input settings for pad 194*/
    (uint16)1048,
    /* Index to address the input settings for pad 195*/
    (uint16)1051,
    /* Index to address the input settings for pad 196*/
    (uint16)1054,
    /* Index to address the input settings for pad 197*/
    (uint16)1057,
    /* Index to address the input settings for pad 198*/
    (uint16)1060,
    /* Index to address the input settings for pad 199*/
    (uint16)1063,
    /* Index to address the input settings for pad 200*/
    (uint16)1066,
    /* Index to address the input settings for pad 201*/
    (uint16)1070,
    /* Index to address the input settings for pad 202*/
    (uint16)1075,
    /* Index to address the input settings for pad 203*/
    (uint16)1078,
    /* Index to address the input settings for pad 204*/
    (uint16)1081,
    /* Index to address the input settings for pad 205*/
    (uint16)1084,
    /* Index to address the input settings for pad 206*/
    (uint16)1088,
    /* Index to address the input settings for pad 207*/
    (uint16)1093,
    /* Index to address the input settings for pad 208*/
    (uint16)1096,
    /* Index to address the input settings for pad 209*/
    (uint16)1098,
    /* Index to address the input settings for pad 210*/
    (uint16)1100,
    /* Index to address the input settings for pad 211*/
    (uint16)1102,
    /* Index to address the input settings for pad 212*/
    (uint16)1104,
    /* Index to address the input settings for pad 213*/
    (uint16)1106,
    /* Index to address the input settings for pad 214*/
    (uint16)1109,
    /* Index to address the input settings for pad 215*/
    (uint16)1111,
    /* Index to address the input settings for pad 216*/
    (uint16)1115,
    /* Index to address the input settings for pad 217*/
    (uint16)1119,
    /* Index to address the input settings for pad 218*/
    (uint16)1123,
    /* Index to address the input settings for pad 219*/
    (uint16)1125,
    /* Index to address the input settings for pad 220*/
    (uint16)1128,
    /* Index to address the input settings for pad 221*/
    (uint16)1130,
    /* Index to address the input settings for pad 222*/
    (uint16)1134,
    /* Index to address the input settings for pad 223*/
    (uint16)1138,
    /* Index to address the input settings for pad 224*/
    (uint16)1142,
    /* Index to address the input settings for pad 225*/
    (uint16)1147,
    /* Index to address the input settings for pad 226*/
    (uint16)1153,
    /* Index to address the input settings for pad 227*/
    (uint16)1157,
    /* Index to address the input settings for pad 228*/
    (uint16)1162,
    /* Index to address the input settings for pad 229*/
    (uint16)1166,
    /* Index to address the input settings for pad 230*/
    (uint16)1170,
    /* Index to address the input settings for pad 231*/
    (uint16)1174,
    /* Index to address the input settings for pad 232*/
    (uint16)1179,
    /* Index to address the input settings for pad 233*/
    (uint16)1183,
    /* Index to address the input settings for pad 234*/
    (uint16)1186,
    /* Index to address the input settings for pad 235*/
    (uint16)1189,
    /* Index to address the input settings for pad 236*/
    (uint16)1192,
    /* Index to address the input settings for pad 237*/
    (uint16)1194,
    /* Index to address the input settings for pad 238*/
    (uint16)1195,
    /* Index to address the input settings for pad 239*/
    (uint16)1197,
    /* Index to address the input settings for pad 240*/
    (uint16)1198,
    /* Index to address the input settings for pad 241*/
    (uint16)1200,
    /* Index to address the input settings for pad 242*/
    (uint16)1202,
    /* Index to address the input settings for pad 243*/
    (uint16)1204,
    /* Index to address the input settings for pad 244*/
    (uint16)1206,
    /* Index to address the input settings for pad 245*/
    (uint16)1208,
    /* Index to address the input settings for pad 246*/
    (uint16)1209,
    /* Index to address the input settings for pad 247*/
    (uint16)0,
    /* Index to address the input settings for pad 248*/
    (uint16)1210,
    /* Index to address the input settings for pad 249*/
    (uint16)1212,
    /* Index to address the input settings for pad 250*/
    (uint16)1214,
    /* Index to address the input settings for pad 251*/
    (uint16)1217,
    /* Index to address the input settings for pad 252*/
    (uint16)1219,
    /* Index to address the input settings for pad 253*/
    (uint16)1221,
    /* Index to address the input settings for pad 254*/
    (uint16)1222,
    /* Index to address the input settings for pad 255*/
    (uint16)1223,
    /* Index to address the input settings for pad 256*/
    (uint16)1224,
    /* Index to address the input settings for pad 257*/
    (uint16)1226,
    /* Index to address the input settings for pad 258*/
    (uint16)1229,
    /* Index to address the input settings for pad 259*/
    (uint16)1231,
    /* Index to address the input settings for pad 260*/
    (uint16)1234,
    /* Index to address the input settings for pad 261*/
    (uint16)1238,
    /* Index to address the input settings for pad 262*/
    (uint16)1241,
    /* Index to address the input settings for pad 263*/
    (uint16)1244,
    /* Index to address the input settings for pad 264*/
    (uint16)1247,
    /* Index to address the input settings for pad 265*/
    (uint16)0,
    /* Index to address the input settings for pad 266*/
    (uint16)1248,
    /* Index to address the input settings for pad 267*/
    (uint16)0,
    /* Index to address the input settings for pad 268*/
    (uint16)1250,
    /* Index to address the input settings for pad 269*/
    (uint16)1252,
    /* Index to address the input settings for pad 270*/
    (uint16)1254,
    /* Index to address the input settings for pad 271*/
    (uint16)1255,
    /* Index to address the input settings for pad 272*/
    (uint16)1257,
    /* Index to address the input settings for pad 273*/
    (uint16)1259,
    /* Index to address the input settings for pad 274*/
    (uint16)1261,
    /* Index to address the input settings for pad 275*/
    (uint16)1263,
    /* Index to address the input settings for pad 276*/
    (uint16)1265,
    /* Index to address the input settings for pad 277*/
    (uint16)1267,
    /* Index to address the input settings for pad 278*/
    (uint16)1269,
    /* Index to address the input settings for pad 279*/
    (uint16)1270,
    /* Index to address the input settings for pad 280*/
    (uint16)1272,
    /* Index to address the input settings for pad 281*/
    (uint16)1275,
    /* Index to address the input settings for pad 282*/
    (uint16)1278,
    /* Index to address the input settings for pad 283*/
    (uint16)1281,
    /* Index to address the input settings for pad 284*/
    (uint16)1283,
    /* Index to address the input settings for pad 285*/
    (uint16)1284,
    /* Index to address the input settings for pad 286*/
    (uint16)1285,
    /* Index to address the input settings for pad 287*/
    (uint16)1286,
    /* Index to address the input settings for pad 288*/
    (uint16)1287,
    /* Index to address the input settings for pad 289*/
    (uint16)1288,
    /* Index to address the input settings for pad 290*/
    (uint16)1291,
    /* Index to address the input settings for pad 291*/
    (uint16)1293,
    /* Index to address the input settings for pad 292*/
    (uint16)1295,
    /* Index to address the input settings for pad 293*/
    (uint16)1298,
    /* Index to address the input settings for pad 294*/
    (uint16)1301,
    /* Index to address the input settings for pad 295*/
    (uint16)1303,
    /* Index to address the input settings for pad 296*/
    (uint16)1305,
    /* Index to address the input settings for pad 297*/
    (uint16)1306,
    /* Index to address the input settings for pad 298*/
    (uint16)1307,
    /* Index to address the input settings for pad 299*/
    (uint16)1309,
    /* Index to address the input settings for pad 300*/
    (uint16)1310,
    /* Index to address the input settings for pad 301*/
    (uint16)1313,
    /* Index to address the input settings for pad 302*/
    (uint16)1316,
    /* Index to address the input settings for pad 303*/
    (uint16)1319,
    /* Index to address the input settings for pad 304*/
    (uint16)1322,
    /* Index to address the input settings for pad 305*/
    (uint16)1324,
    /* Index to address the input settings for pad 306*/
    (uint16)1326,
    /* Index to address the input settings for pad 307*/
    (uint16)1327,
    /* Index to address the input settings for pad 308*/
    (uint16)1329,
    /* Index to address the input settings for pad 309*/
    (uint16)1330,
    /* Index to address the input settings for pad 310*/
    (uint16)1332,
    /* Index to address the input settings for pad 311*/
    (uint16)1333,
    /* Index to address the input settings for pad 312*/
    (uint16)1335,
    /* Index to address the input settings for pad 313*/
    (uint16)1338,
    /* Index to address the input settings for pad 314*/
    (uint16)1340,
    /* Index to address the input settings for pad 315*/
    (uint16)1343,
    /* Index to address the input settings for pad 316*/
    (uint16)1346,
    /* Index to address the input settings for pad 317*/
    (uint16)1347,
    /* Index to address the input settings for pad 318*/
    (uint16)1349,
    /* Index to address the input settings for pad 319*/
    (uint16)1351,
    /* Index to address the input settings for pad 320*/
    (uint16)1352,
    /* Index to address the input settings for pad 321*/
    (uint16)1355,
    /* Index to address the input settings for pad 322*/
    (uint16)1358,
    /* Index to address the input settings for pad 323*/
    (uint16)1361
};

#define PORT_STOP_SEC_CONST_16
#include "Port_MemMap.h"

#define PORT_START_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

/**
* @brief Array of bits storing availability of PortPinModes for MSCRs on SIUL2 instance
*/
static const Port_PinModeAvailabilityArrayType Port_SIUL2_0_au16PinModeAvailability =
{
    /*  Mode PORT_GPIO_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_GPIO |
        SIUL2_0_PORT1_GPIO |
        SIUL2_0_PORT2_GPIO |
        SIUL2_0_PORT3_GPIO |
        SIUL2_0_PORT4_GPIO |
        SIUL2_0_PORT5_GPIO |
        SIUL2_0_PORT6_GPIO |
        SIUL2_0_PORT7_GPIO |
        SIUL2_0_PORT8_GPIO |
        SIUL2_0_PORT9_GPIO |
        SIUL2_0_PORT10_GPIO |
        SIUL2_0_PORT11_GPIO |
        SIUL2_0_PORT12_GPIO |
        SIUL2_0_PORT13_GPIO |
        SIUL2_0_PORT14_GPIO |
        SIUL2_0_PORT15_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_GPIO |
        SIUL2_0_PORT17_GPIO |
        SIUL2_0_PORT18_GPIO |
        SIUL2_0_PORT19_GPIO |
        SIUL2_0_PORT20_GPIO |
        SIUL2_0_PORT21_GPIO |
        SIUL2_0_PORT22_GPIO |
        SIUL2_0_PORT23_GPIO |
        SIUL2_0_PORT24_GPIO |
        SIUL2_0_PORT25_GPIO |
        SIUL2_0_PORT26_GPIO |
        SIUL2_0_PORT27_GPIO |
        SIUL2_0_PORT28_GPIO |
        SIUL2_0_PORT29_GPIO |
        SIUL2_0_PORT30_GPIO |
        SIUL2_0_PORT31_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_GPIO |
        SIUL2_0_PORT33_GPIO |
        SIUL2_0_PORT34_GPIO |
        SIUL2_0_PORT35_GPIO |
        SIUL2_0_PORT36_GPIO |
        SIUL2_0_PORT37_GPIO |
        SIUL2_0_PORT40_GPIO |
        SIUL2_0_PORT41_GPIO |
        SIUL2_0_PORT42_GPIO |
        SIUL2_0_PORT43_GPIO |
        SIUL2_0_PORT44_GPIO |
        SIUL2_0_PORT45_GPIO |
        SIUL2_0_PORT46_GPIO |
        SIUL2_0_PORT47_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_GPIO |
        SIUL2_0_PORT49_GPIO |
        SIUL2_0_PORT50_GPIO |
        SIUL2_0_PORT51_GPIO |
        SIUL2_0_PORT52_GPIO |
        SIUL2_0_PORT53_GPIO |
        SIUL2_0_PORT54_GPIO |
        SIUL2_0_PORT55_GPIO |
        SIUL2_0_PORT56_GPIO |
        SIUL2_0_PORT57_GPIO |
        SIUL2_0_PORT58_GPIO |
        SIUL2_0_PORT59_GPIO |
        SIUL2_0_PORT60_GPIO |
        SIUL2_0_PORT61_GPIO |
        SIUL2_0_PORT62_GPIO |
        SIUL2_0_PORT63_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GPIO |
        SIUL2_0_PORT65_GPIO |
        SIUL2_0_PORT66_GPIO |
        SIUL2_0_PORT67_GPIO |
        SIUL2_0_PORT68_GPIO |
        SIUL2_0_PORT69_GPIO |
        SIUL2_0_PORT70_GPIO |
        SIUL2_0_PORT71_GPIO |
        SIUL2_0_PORT72_GPIO |
        SIUL2_0_PORT73_GPIO |
        SIUL2_0_PORT74_GPIO |
        SIUL2_0_PORT75_GPIO |
        SIUL2_0_PORT76_GPIO |
        SIUL2_0_PORT77_GPIO |
        SIUL2_0_PORT78_GPIO |
        SIUL2_0_PORT79_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_GPIO |
        SIUL2_0_PORT81_GPIO |
        SIUL2_0_PORT82_GPIO |
        SIUL2_0_PORT83_GPIO |
        SIUL2_0_PORT84_GPIO |
        SIUL2_0_PORT85_GPIO |
        SIUL2_0_PORT86_GPIO |
        SIUL2_0_PORT87_GPIO |
        SIUL2_0_PORT88_GPIO |
        SIUL2_0_PORT89_GPIO |
        SIUL2_0_PORT90_GPIO |
        SIUL2_0_PORT91_GPIO |
        SIUL2_0_PORT92_GPIO |
        SIUL2_0_PORT93_GPIO |
        SIUL2_0_PORT94_GPIO |
        SIUL2_0_PORT95_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_GPIO |
        SIUL2_0_PORT97_GPIO |
        SIUL2_0_PORT98_GPIO |
        SIUL2_0_PORT99_GPIO |
        SIUL2_0_PORT100_GPIO |
        SIUL2_0_PORT101_GPIO |
        SIUL2_0_PORT102_GPIO |
        SIUL2_0_PORT103_GPIO |
        SIUL2_0_PORT104_GPIO |
        SIUL2_0_PORT105_GPIO |
        SIUL2_0_PORT106_GPIO |
        SIUL2_0_PORT107_GPIO |
        SIUL2_0_PORT108_GPIO |
        SIUL2_0_PORT109_GPIO |
        SIUL2_0_PORT110_GPIO |
        SIUL2_0_PORT111_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_GPIO |
        SIUL2_0_PORT113_GPIO |
        SIUL2_0_PORT114_GPIO |
        SIUL2_0_PORT115_GPIO |
        SIUL2_0_PORT116_GPIO |
        SIUL2_0_PORT117_GPIO |
        SIUL2_0_PORT118_GPIO |
        SIUL2_0_PORT119_GPIO |
        SIUL2_0_PORT120_GPIO |
        SIUL2_0_PORT121_GPIO |
        SIUL2_0_PORT122_GPIO |
        SIUL2_0_PORT123_GPIO |
        SIUL2_0_PORT124_GPIO |
        SIUL2_0_PORT125_GPIO |
        SIUL2_0_PORT126_GPIO |
        SIUL2_0_PORT127_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_GPIO |
        SIUL2_0_PORT129_GPIO |
        SIUL2_0_PORT130_GPIO |
        SIUL2_0_PORT131_GPIO |
        SIUL2_0_PORT132_GPIO |
        SIUL2_0_PORT133_GPIO |
        SIUL2_0_PORT134_GPIO |
        SIUL2_0_PORT135_GPIO |
        SIUL2_0_PORT136_GPIO |
        SIUL2_0_PORT137_GPIO |
        SIUL2_0_PORT138_GPIO |
        SIUL2_0_PORT139_GPIO |
        SIUL2_0_PORT140_GPIO |
        SIUL2_0_PORT142_GPIO |
        SIUL2_0_PORT143_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_GPIO |
        SIUL2_0_PORT145_GPIO |
        SIUL2_0_PORT146_GPIO |
        SIUL2_0_PORT147_GPIO |
        SIUL2_0_PORT148_GPIO |
        SIUL2_0_PORT149_GPIO |
        SIUL2_0_PORT150_GPIO |
        SIUL2_0_PORT151_GPIO |
        SIUL2_0_PORT152_GPIO |
        SIUL2_0_PORT153_GPIO |
        SIUL2_0_PORT154_GPIO |
        SIUL2_0_PORT155_GPIO |
        SIUL2_0_PORT156_GPIO |
        SIUL2_0_PORT157_GPIO |
        SIUL2_0_PORT158_GPIO |
        SIUL2_0_PORT159_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_GPIO |
        SIUL2_0_PORT161_GPIO |
        SIUL2_0_PORT162_GPIO |
        SIUL2_0_PORT163_GPIO |
        SIUL2_0_PORT164_GPIO |
        SIUL2_0_PORT165_GPIO |
        SIUL2_0_PORT166_GPIO |
        SIUL2_0_PORT167_GPIO |
        SIUL2_0_PORT168_GPIO |
        SIUL2_0_PORT169_GPIO |
        SIUL2_0_PORT170_GPIO |
        SIUL2_0_PORT171_GPIO |
        SIUL2_0_PORT172_GPIO |
        SIUL2_0_PORT173_GPIO |
        SIUL2_0_PORT174_GPIO |
        SIUL2_0_PORT175_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_GPIO |
        SIUL2_0_PORT177_GPIO |
        SIUL2_0_PORT178_GPIO |
        SIUL2_0_PORT179_GPIO |
        SIUL2_0_PORT180_GPIO |
        SIUL2_0_PORT181_GPIO |
        SIUL2_0_PORT182_GPIO |
        SIUL2_0_PORT183_GPIO |
        SIUL2_0_PORT184_GPIO |
        SIUL2_0_PORT185_GPIO |
        SIUL2_0_PORT186_GPIO |
        SIUL2_0_PORT187_GPIO |
        SIUL2_0_PORT188_GPIO |
        SIUL2_0_PORT189_GPIO |
        SIUL2_0_PORT190_GPIO |
        SIUL2_0_PORT191_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_GPIO |
        SIUL2_0_PORT193_GPIO |
        SIUL2_0_PORT194_GPIO |
        SIUL2_0_PORT195_GPIO |
        SIUL2_0_PORT196_GPIO |
        SIUL2_0_PORT197_GPIO |
        SIUL2_0_PORT198_GPIO |
        SIUL2_0_PORT199_GPIO |
        SIUL2_0_PORT200_GPIO |
        SIUL2_0_PORT201_GPIO |
        SIUL2_0_PORT202_GPIO |
        SIUL2_0_PORT203_GPIO |
        SIUL2_0_PORT204_GPIO |
        SIUL2_0_PORT205_GPIO |
        SIUL2_0_PORT206_GPIO |
        SIUL2_0_PORT207_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_GPIO |
        SIUL2_0_PORT209_GPIO |
        SIUL2_0_PORT210_GPIO |
        SIUL2_0_PORT211_GPIO |
        SIUL2_0_PORT212_GPIO |
        SIUL2_0_PORT213_GPIO |
        SIUL2_0_PORT214_GPIO |
        SIUL2_0_PORT215_GPIO |
        SIUL2_0_PORT216_GPIO |
        SIUL2_0_PORT217_GPIO |
        SIUL2_0_PORT218_GPIO |
        SIUL2_0_PORT219_GPIO |
        SIUL2_0_PORT220_GPIO |
        SIUL2_0_PORT221_GPIO |
        SIUL2_0_PORT222_GPIO |
        SIUL2_0_PORT223_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_GPIO |
        SIUL2_0_PORT225_GPIO |
        SIUL2_0_PORT226_GPIO |
        SIUL2_0_PORT227_GPIO |
        SIUL2_0_PORT228_GPIO |
        SIUL2_0_PORT229_GPIO |
        SIUL2_0_PORT230_GPIO |
        SIUL2_0_PORT231_GPIO |
        SIUL2_0_PORT232_GPIO |
        SIUL2_0_PORT233_GPIO |
        SIUL2_0_PORT234_GPIO |
        SIUL2_0_PORT235_GPIO |
        SIUL2_0_PORT236_GPIO |
        SIUL2_0_PORT237_GPIO |
        SIUL2_0_PORT238_GPIO |
        SIUL2_0_PORT239_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT240_GPIO |
        SIUL2_0_PORT241_GPIO |
        SIUL2_0_PORT242_GPIO |
        SIUL2_0_PORT243_GPIO |
        SIUL2_0_PORT244_GPIO |
        SIUL2_0_PORT245_GPIO |
        SIUL2_0_PORT246_GPIO |
        SIUL2_0_PORT247_GPIO |
        SIUL2_0_PORT248_GPIO |
        SIUL2_0_PORT249_GPIO |
        SIUL2_0_PORT250_GPIO |
        SIUL2_0_PORT251_GPIO |
        SIUL2_0_PORT252_GPIO |
        SIUL2_0_PORT253_GPIO |
        SIUL2_0_PORT254_GPIO |
        SIUL2_0_PORT255_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_GPIO |
        SIUL2_0_PORT257_GPIO |
        SIUL2_0_PORT258_GPIO |
        SIUL2_0_PORT259_GPIO |
        SIUL2_0_PORT260_GPIO |
        SIUL2_0_PORT261_GPIO |
        SIUL2_0_PORT262_GPIO |
        SIUL2_0_PORT263_GPIO |
        SIUL2_0_PORT264_GPIO |
        SIUL2_0_PORT265_GPIO |
        SIUL2_0_PORT266_GPIO |
        SIUL2_0_PORT267_GPIO |
        SIUL2_0_PORT268_GPIO |
        SIUL2_0_PORT269_GPIO |
        SIUL2_0_PORT270_GPIO |
        SIUL2_0_PORT271_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_GPIO |
        SIUL2_0_PORT273_GPIO |
        SIUL2_0_PORT274_GPIO |
        SIUL2_0_PORT275_GPIO |
        SIUL2_0_PORT276_GPIO |
        SIUL2_0_PORT277_GPIO |
        SIUL2_0_PORT278_GPIO |
        SIUL2_0_PORT279_GPIO |
        SIUL2_0_PORT280_GPIO |
        SIUL2_0_PORT281_GPIO |
        SIUL2_0_PORT282_GPIO |
        SIUL2_0_PORT283_GPIO |
        SIUL2_0_PORT284_GPIO |
        SIUL2_0_PORT285_GPIO |
        SIUL2_0_PORT286_GPIO |
        SIUL2_0_PORT287_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT288_GPIO |
        SIUL2_0_PORT289_GPIO |
        SIUL2_0_PORT290_GPIO |
        SIUL2_0_PORT291_GPIO |
        SIUL2_0_PORT292_GPIO |
        SIUL2_0_PORT293_GPIO |
        SIUL2_0_PORT294_GPIO |
        SIUL2_0_PORT295_GPIO |
        SIUL2_0_PORT296_GPIO |
        SIUL2_0_PORT297_GPIO |
        SIUL2_0_PORT298_GPIO |
        SIUL2_0_PORT299_GPIO |
        SIUL2_0_PORT300_GPIO |
        SIUL2_0_PORT301_GPIO |
        SIUL2_0_PORT302_GPIO |
        SIUL2_0_PORT303_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_GPIO |
        SIUL2_0_PORT305_GPIO |
        SIUL2_0_PORT306_GPIO |
        SIUL2_0_PORT307_GPIO |
        SIUL2_0_PORT308_GPIO |
        SIUL2_0_PORT309_GPIO |
        SIUL2_0_PORT310_GPIO |
        SIUL2_0_PORT311_GPIO |
        SIUL2_0_PORT312_GPIO |
        SIUL2_0_PORT313_GPIO |
        SIUL2_0_PORT314_GPIO |
        SIUL2_0_PORT315_GPIO |
        SIUL2_0_PORT316_GPIO |
        SIUL2_0_PORT317_GPIO |
        SIUL2_0_PORT318_GPIO |
        SIUL2_0_PORT319_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_GPIO |
        SIUL2_0_PORT321_GPIO |
        SIUL2_0_PORT322_GPIO |
        SIUL2_0_PORT323_GPIO */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_ALT1_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPSPI4_LPSPI4_PCS2_OUT |
        SIUL2_0_PORT1_LPSPI4_LPSPI4_PCS1_OUT |
        SIUL2_0_PORT2_FCCU_FCCU_ERR0_OUT |
        SIUL2_0_PORT3_FCCU_FCCU_ERR1_OUT |
        SIUL2_0_PORT7_LPUART3_LPUART3_TX_OUT |
        SIUL2_0_PORT11_CAN1_CAN1_TX_OUT |
        SIUL2_0_PORT12_LPSPI1_LPSPI1_PCS5_OUT |
        SIUL2_0_PORT13_LPSPI1_LPSPI1_PCS4_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI4_LPSPI4_PCS3_OUT |
        SIUL2_0_PORT21_LPSPI2_LPSPI2_PCS2_OUT |
        SIUL2_0_PORT23_CAN1_CAN1_TX_OUT |
        SIUL2_0_PORT27_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT31_GMAC0_GMAC0_PPS0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPI2C0_LPI2C0_SDAS_OUT |
        SIUL2_0_PORT33_LPI2C0_LPI2C0_SCLS_OUT |
        SIUL2_0_PORT34_ADC1_ADC1_MA_0_OUT |
        SIUL2_0_PORT35_LPUART9_LPUART9_TX_OUT |
        SIUL2_0_PORT36_GMAC0_GMAC0_MII_RMII_TXD_1_OUT |
        SIUL2_0_PORT37_GMAC0_GMAC0_MII_RMII_TXD_0_OUT |
        SIUL2_0_PORT40_LPSPI4_LPSPI4_PCS0_OUT |
        SIUL2_0_PORT41_LPSPI4_LPSPI4_SOUT_OUT |
        SIUL2_0_PORT42_LPSPI4_LPSPI4_SCK_OUT |
        SIUL2_0_PORT43_LPSPI4_LPSPI4_SIN_OUT |
        SIUL2_0_PORT44_LPSPI3_LPSPI3_PCS3_OUT |
        SIUL2_0_PORT45_LPSPI3_LPSPI3_PCS2_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT50_LPUART13_LPUART13_TX_OUT |
        SIUL2_0_PORT51_GMAC0_GMAC0_PPS0_OUT |
        SIUL2_0_PORT52_LPUART14_LPUART14_TX_OUT |
        SIUL2_0_PORT54_CAN1_CAN1_TX_OUT |
        SIUL2_0_PORT55_ADC1_ADC1_MA_0_OUT |
        SIUL2_0_PORT56_ADC1_ADC1_MA_1_OUT |
        SIUL2_0_PORT57_LPUART15_LPUART15_TX_OUT |
        SIUL2_0_PORT59_LPUART5_LPUART5_TX_OUT |
        SIUL2_0_PORT60_ADC1_ADC1_MA_2_OUT |
        SIUL2_0_PORT61_LPUART6_LPUART6_TX_OUT |
        SIUL2_0_PORT63_EMIOS_0_EMIOS_0_CH_19_Y_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_CAN3_CAN3_TX_OUT |
        SIUL2_0_PORT66_GMAC0_GMAC0_MII_RMII_TXD_1_OUT |
        SIUL2_0_PORT70_LPI2C1_LPI2C1_SDA_OUT |
        SIUL2_0_PORT71_FXIO_FXIO_D10_OUT |
        SIUL2_0_PORT72_LPI2C0_LPI2C0_SCL_OUT |
        SIUL2_0_PORT73_LPI2C0_LPI2C0_SDA_OUT |
        SIUL2_0_PORT74_EMIOS_0_EMIOS_0_CH_6_G_OUT |
        SIUL2_0_PORT76_ADC1_ADC1_MA_2_OUT |
        SIUL2_0_PORT77_LPUART10_LPUART10_TX_OUT |
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_OUT |
        SIUL2_0_PORT79_CAN2_CAN2_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPSPI3_LPSPI3_SIN_OUT |
        SIUL2_0_PORT81_LPSPI3_LPSPI3_SCK_OUT |
        SIUL2_0_PORT82_GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_OUT |
        SIUL2_0_PORT83_LPUART7_LPUART7_TX_OUT |
        SIUL2_0_PORT85_GMAC0_GMAC0_PPS1_OUT |
        SIUL2_0_PORT86_EMIOS_0_EMIOS_0_CH_8_X_OUT |
        SIUL2_0_PORT88_LPUART12_LPUART12_TX_OUT |
        SIUL2_0_PORT90_LPUART13_LPUART13_TX_OUT |
        SIUL2_0_PORT91_CAN5_CAN5_TX_OUT |
        SIUL2_0_PORT92_CAN3_CAN3_TX_OUT |
        SIUL2_0_PORT94_CAN4_CAN4_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT97_LPUART5_LPUART5_TX_OUT |
        SIUL2_0_PORT98_LCU0_LCU0_OUT1_OUT |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_TXD2_OUT |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_TXD3_OUT |
        SIUL2_0_PORT103_GMAC0_GMAC0_MII_RMII_TXD_0_OUT |
        SIUL2_0_PORT104_LPSPI3_LPSPI3_SOUT_OUT |
        SIUL2_0_PORT106_GMAC0_GMAC0_MII_TXD3_OUT |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_TXD2_OUT |
        SIUL2_0_PORT108_GMAC0_GMAC0_MII_RMII_TX_CLK_OUT |
        SIUL2_0_PORT109_LPSPI5_LPSPI5_SIN_OUT |
        SIUL2_0_PORT110_LPSPI5_LPSPI5_SCK_OUT |
        SIUL2_0_PORT111_FXIO_FXIO_D6_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT113_LPSPI5_LPSPI5_PCS0_OUT |
        SIUL2_0_PORT114_CAN2_CAN2_TX_OUT |
        SIUL2_0_PORT122_LPUART14_LPUART14_TX_OUT |
        SIUL2_0_PORT124_LPUART15_LPUART15_TX_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT131_CAN4_CAN4_TX_OUT |
        SIUL2_0_PORT132_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT136_LPSPI3_LPSPI3_PCS1_OUT |
        SIUL2_0_PORT137_LPSPI5_LPSPI5_SOUT_OUT |
        SIUL2_0_PORT139_LPUART4_LPUART4_TX_OUT |
        SIUL2_0_PORT142_EMIOS_0_EMIOS_0_CH_19_Y_OUT |
        SIUL2_0_PORT143_FCCU_FCCU_ERR0_OUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_FCCU_FCCU_ERR1_OUT |
        SIUL2_0_PORT156_CAN3_CAN3_TX_OUT |
        SIUL2_0_PORT158_CAN4_CAN4_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_LPUART5_LPUART5_TX_OUT |
        SIUL2_0_PORT162_LPUART6_LPUART6_TX_OUT |
        SIUL2_0_PORT164_CAN5_CAN5_TX_OUT |
        SIUL2_0_PORT167_LPSPI2_LPSPI2_PCS0_OUT |
        SIUL2_0_PORT172_LPUART10_LPUART10_TX_OUT |
        SIUL2_0_PORT174_CAN1_CAN1_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_LPUART12_LPUART12_TX_OUT |
        SIUL2_0_PORT178_LPUART7_LPUART7_TX_OUT |
        SIUL2_0_PORT180_LPUART8_LPUART8_TX_OUT |
        SIUL2_0_PORT183_LPUART9_LPUART9_TX_OUT |
        SIUL2_0_PORT185_CAN2_CAN2_TX_OUT |
        SIUL2_0_PORT187_LPUART11_LPUART11_TX_OUT |
        SIUL2_0_PORT189_CAN3_CAN3_TX_OUT |
        SIUL2_0_PORT191_ADC1_ADC1_MA_2_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_LPUART13_LPUART13_TX_OUT |
        SIUL2_0_PORT194_LPUART14_LPUART14_TX_OUT |
        SIUL2_0_PORT196_LPUART15_LPUART15_TX_OUT |
        SIUL2_0_PORT200_CAN4_CAN4_TX_OUT |
        SIUL2_0_PORT202_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT203_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT205_CAN5_CAN5_TX_OUT |
        SIUL2_0_PORT206_LPSPI2_LPSPI2_PCS0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT216_LPUART12_LPUART12_TX_OUT |
        SIUL2_0_PORT220_LPSPI5_LPSPI5_PCS0_OUT |
        SIUL2_0_PORT221_LPSPI5_LPSPI5_SIN_OUT |
        SIUL2_0_PORT222_LPSPI5_LPSPI5_SOUT_OUT |
        SIUL2_0_PORT223_LPSPI5_LPSPI5_SCK_OUT */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_CAN6_CAN6_TX_OUT |
        SIUL2_0_PORT226_CAN7_CAN7_TX_OUT |
        SIUL2_0_PORT228_LPUART4_LPUART4_TX_OUT |
        SIUL2_0_PORT230_LPUART8_LPUART8_TX_OUT |
        SIUL2_0_PORT232_LPUART10_LPUART10_TX_OUT |
        SIUL2_0_PORT234_LPUART11_LPUART11_TX_OUT |
        SIUL2_0_PORT237_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT238_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT239_FXIO_FXIO_D2_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT240_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT241_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT242_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT243_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT244_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT245_LCU0_LCU0_OUT0_OUT |
        SIUL2_0_PORT246_LCU0_LCU0_OUT1_OUT |
        SIUL2_0_PORT247_LCU0_LCU0_OUT2_OUT |
        SIUL2_0_PORT248_LCU0_LCU0_OUT3_OUT |
        SIUL2_0_PORT249_EMIOS_0_EMIOS_0_CH_1_G_OUT |
        SIUL2_0_PORT250_EMIOS_0_EMIOS_0_CH_2_G_OUT |
        SIUL2_0_PORT251_EMIOS_0_EMIOS_0_CH_3_G_OUT |
        SIUL2_0_PORT252_EMIOS_0_EMIOS_0_CH_4_G_OUT |
        SIUL2_0_PORT253_EMIOS_0_EMIOS_0_CH_5_G_OUT |
        SIUL2_0_PORT254_EMIOS_0_EMIOS_0_CH_6_G_OUT |
        SIUL2_0_PORT255_EMIOS_0_EMIOS_0_CH_7_G_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT257_FXIO_FXIO_D9_OUT |
        SIUL2_0_PORT258_FXIO_FXIO_D10_OUT |
        SIUL2_0_PORT259_FXIO_FXIO_D11_OUT |
        SIUL2_0_PORT260_FXIO_FXIO_D12_OUT |
        SIUL2_0_PORT261_FXIO_FXIO_D13_OUT |
        SIUL2_0_PORT262_FXIO_FXIO_D14_OUT |
        SIUL2_0_PORT263_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT264_LCU0_LCU0_OUT4_OUT |
        SIUL2_0_PORT265_LCU0_LCU0_OUT5_OUT |
        SIUL2_0_PORT266_LCU0_LCU0_OUT6_OUT |
        SIUL2_0_PORT267_LCU0_LCU0_OUT7_OUT |
        SIUL2_0_PORT268_EMIOS_0_EMIOS_0_CH_13_H_OUT |
        SIUL2_0_PORT269_EMIOS_0_EMIOS_0_CH_8_X_OUT |
        SIUL2_0_PORT270_EMIOS_0_EMIOS_0_CH_9_H_OUT |
        SIUL2_0_PORT271_EMIOS_0_EMIOS_0_CH_10_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_EMIOS_0_EMIOS_0_CH_11_H_OUT |
        SIUL2_0_PORT273_EMIOS_0_EMIOS_0_CH_12_H_OUT |
        SIUL2_0_PORT274_EMIOS_0_EMIOS_0_CH_14_H_OUT |
        SIUL2_0_PORT275_EMIOS_0_EMIOS_0_CH_15_H_OUT |
        SIUL2_0_PORT276_EMIOS_0_EMIOS_0_CH_16_X_OUT |
        SIUL2_0_PORT277_EMIOS_0_EMIOS_0_CH_17_Y_OUT |
        SIUL2_0_PORT278_EMIOS_0_EMIOS_0_CH_18_Y_OUT |
        SIUL2_0_PORT279_EMIOS_0_EMIOS_0_CH_19_Y_OUT |
        SIUL2_0_PORT280_EMIOS_0_EMIOS_0_CH_20_Y_OUT |
        SIUL2_0_PORT281_EMIOS_0_EMIOS_0_CH_21_Y_OUT |
        SIUL2_0_PORT282_EMIOS_0_EMIOS_0_CH_22_X_OUT |
        SIUL2_0_PORT283_EMIOS_0_EMIOS_0_CH_23_X_OUT |
        SIUL2_0_PORT284_TRGMUX_TRGMUX_OUT4_OUT |
        SIUL2_0_PORT285_TRGMUX_TRGMUX_OUT5_OUT |
        SIUL2_0_PORT286_TRGMUX_TRGMUX_OUT6_OUT |
        SIUL2_0_PORT287_TRGMUX_TRGMUX_OUT7_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT288_FXIO_FXIO_D16_OUT |
        SIUL2_0_PORT289_FXIO_FXIO_D17_OUT |
        SIUL2_0_PORT290_FXIO_FXIO_D18_OUT |
        SIUL2_0_PORT291_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT292_FXIO_FXIO_D20_OUT |
        SIUL2_0_PORT293_FXIO_FXIO_D21_OUT |
        SIUL2_0_PORT294_FXIO_FXIO_D22_OUT |
        SIUL2_0_PORT295_FXIO_FXIO_D23_OUT |
        SIUL2_0_PORT296_LCU0_LCU0_OUT8_OUT |
        SIUL2_0_PORT297_LCU0_LCU0_OUT9_OUT |
        SIUL2_0_PORT298_LCU0_LCU0_OUT10_OUT |
        SIUL2_0_PORT299_LCU0_LCU0_OUT11_OUT |
        SIUL2_0_PORT300_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT301_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT302_EMIOS_1_EMIOS_1_CH_2_H_OUT |
        SIUL2_0_PORT303_EMIOS_1_EMIOS_1_CH_3_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT305_EMIOS_1_EMIOS_1_CH_6_H_OUT |
        SIUL2_0_PORT306_EMIOS_1_EMIOS_1_CH_7_H_OUT |
        SIUL2_0_PORT307_EMIOS_1_EMIOS_1_CH_8_X_OUT |
        SIUL2_0_PORT308_EMIOS_1_EMIOS_1_CH_9_H_OUT |
        SIUL2_0_PORT309_EMIOS_1_EMIOS_1_CH_10_H_OUT |
        SIUL2_0_PORT310_EMIOS_1_EMIOS_1_CH_11_H_OUT |
        SIUL2_0_PORT311_EMIOS_1_EMIOS_1_CH_12_H_OUT |
        SIUL2_0_PORT312_EMIOS_1_EMIOS_1_CH_13_H_OUT |
        SIUL2_0_PORT313_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT314_EMIOS_1_EMIOS_1_CH_14_H_OUT |
        SIUL2_0_PORT315_EMIOS_1_EMIOS_1_CH_15_H_OUT |
        SIUL2_0_PORT316_TRGMUX_TRGMUX_OUT8_OUT |
        SIUL2_0_PORT317_TRGMUX_TRGMUX_OUT9_OUT |
        SIUL2_0_PORT318_TRGMUX_TRGMUX_OUT10_OUT |
        SIUL2_0_PORT319_TRGMUX_TRGMUX_OUT11_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_FXIO_FXIO_D24_OUT |
        SIUL2_0_PORT321_FXIO_FXIO_D25_OUT |
        SIUL2_0_PORT322_FXIO_FXIO_D26_OUT |
        SIUL2_0_PORT323_FXIO_FXIO_D27_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_ALT2_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_EMIOS_0_EMIOS_0_CH_17_Y_OUT |
        SIUL2_0_PORT1_EMIOS_0_EMIOS_0_CH_9_H_OUT |
        SIUL2_0_PORT2_EMIOS_1_EMIOS_1_CH_19_Y_OUT |
        SIUL2_0_PORT3_EMIOS_1_EMIOS_1_CH_20_Y_OUT |
        SIUL2_0_PORT7_LPSPI0_LPSPI0_PCS1_OUT |
        SIUL2_0_PORT8_EMIOS_1_EMIOS_1_CH_12_H_OUT |
        SIUL2_0_PORT9_LPUART2_LPUART2_TX_OUT |
        SIUL2_0_PORT10_EMIOS_0_EMIOS_0_CH_12_H_OUT |
        SIUL2_0_PORT11_EMIOS_0_EMIOS_0_CH_13_H_OUT |
        SIUL2_0_PORT12_EMIOS_0_EMIOS_0_CH_14_H_OUT |
        SIUL2_0_PORT13_EMIOS_0_EMIOS_0_CH_15_H_OUT |
        SIUL2_0_PORT14_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT15_EMIOS_0_EMIOS_0_CH_10_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_EMIOS_0_EMIOS_0_CH_11_H_OUT |
        SIUL2_0_PORT17_EMIOS_0_EMIOS_0_CH_6_G_OUT |
        SIUL2_0_PORT18_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT19_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT20_EMIOS_1_EMIOS_1_CH_2_H_OUT |
        SIUL2_0_PORT21_EMIOS_1_EMIOS_1_CH_3_H_OUT |
        SIUL2_0_PORT22_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT23_EMIOS_1_EMIOS_1_CH_6_H_OUT |
        SIUL2_0_PORT26_EMIOS_1_EMIOS_1_CH_9_H_OUT |
        SIUL2_0_PORT27_EMIOS_1_EMIOS_1_CH_10_H_OUT |
        SIUL2_0_PORT28_EMIOS_1_EMIOS_1_CH_11_H_OUT |
        SIUL2_0_PORT29_EMIOS_1_EMIOS_1_CH_12_H_OUT |
        SIUL2_0_PORT30_EMIOS_1_EMIOS_1_CH_13_H_OUT |
        SIUL2_0_PORT31_EMIOS_1_EMIOS_1_CH_14_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_FXIO_FXIO_D14_OUT |
        SIUL2_0_PORT33_LPUART0_LPUART0_TX_OUT |
        SIUL2_0_PORT34_EMIOS_0_EMIOS_0_CH_8_X_OUT |
        SIUL2_0_PORT35_EMIOS_0_EMIOS_0_CH_9_H_OUT |
        SIUL2_0_PORT36_EMIOS_0_EMIOS_0_CH_4_G_OUT |
        SIUL2_0_PORT37_EMIOS_0_EMIOS_0_CH_5_G_OUT |
        SIUL2_0_PORT40_EMIOS_1_EMIOS_1_CH_15_H_OUT |
        SIUL2_0_PORT41_EMIOS_1_EMIOS_1_CH_16_X_OUT |
        SIUL2_0_PORT42_EMIOS_1_EMIOS_1_CH_17_Y_OUT |
        SIUL2_0_PORT43_EMIOS_1_EMIOS_1_CH_18_Y_OUT |
        SIUL2_0_PORT44_EMIOS_0_EMIOS_0_CH_0_X_OUT |
        SIUL2_0_PORT45_EMIOS_0_EMIOS_0_CH_1_G_OUT |
        SIUL2_0_PORT46_EMIOS_0_EMIOS_0_CH_2_G_OUT |
        SIUL2_0_PORT47_EMIOS_0_EMIOS_0_CH_3_G_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_EMIOS_0_EMIOS_0_CH_4_G_OUT |
        SIUL2_0_PORT49_EMIOS_0_EMIOS_0_CH_5_G_OUT |
        SIUL2_0_PORT50_EMIOS_1_EMIOS_1_CH_15_H_OUT |
        SIUL2_0_PORT51_EMIOS_1_EMIOS_1_CH_15_H_OUT |
        SIUL2_0_PORT52_EMIOS_1_EMIOS_1_CH_16_X_OUT |
        SIUL2_0_PORT53_EMIOS_1_EMIOS_1_CH_17_Y_OUT |
        SIUL2_0_PORT54_EMIOS_1_EMIOS_1_CH_18_Y_OUT |
        SIUL2_0_PORT55_EMIOS_1_EMIOS_1_CH_19_Y_OUT |
        SIUL2_0_PORT56_EMIOS_1_EMIOS_1_CH_20_Y_OUT |
        SIUL2_0_PORT57_EMIOS_1_EMIOS_1_CH_21_Y_OUT |
        SIUL2_0_PORT58_EMIOS_1_EMIOS_1_CH_22_X_OUT |
        SIUL2_0_PORT59_EMIOS_1_EMIOS_1_CH_23_X_OUT |
        SIUL2_0_PORT60_GMAC0_GMAC0_MII_RGMII_TXD2_OUT |
        SIUL2_0_PORT61_GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_EMIOS_0_EMIOS_0_CH_0_X_OUT |
        SIUL2_0_PORT65_EMIOS_0_EMIOS_0_CH_1_G_OUT |
        SIUL2_0_PORT66_EMIOS_0_EMIOS_0_CH_2_G_OUT |
        SIUL2_0_PORT67_EMIOS_0_EMIOS_0_CH_3_G_OUT |
        SIUL2_0_PORT68_EMIOS_0_EMIOS_0_CH_8_X_OUT |
        SIUL2_0_PORT69_EMIOS_0_EMIOS_0_CH_16_X_OUT |
        SIUL2_0_PORT70_FXIO_FXIO_D11_OUT |
        SIUL2_0_PORT71_LPUART1_LPUART1_TX_OUT |
        SIUL2_0_PORT73_LPUART1_LPUART1_TX_OUT |
        SIUL2_0_PORT74_LPUART11_LPUART11_TX_OUT |
        SIUL2_0_PORT75_LPUART0_LPUART0_DTR_B_OUT |
        SIUL2_0_PORT76_EMIOS_1_EMIOS_1_CH_2_H_OUT |
        SIUL2_0_PORT77_EMIOS_1_EMIOS_1_CH_3_H_OUT |
        SIUL2_0_PORT78_EMIOS_0_EMIOS_0_CH_10_H_OUT |
        SIUL2_0_PORT79_EMIOS_0_EMIOS_0_CH_11_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_EMIOS_1_EMIOS_1_CH_9_H_OUT |
        SIUL2_0_PORT82_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT88_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT89_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT90_EMIOS_1_EMIOS_1_CH_3_H_OUT |
        SIUL2_0_PORT91_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT92_EMIOS_1_EMIOS_1_CH_7_H_OUT |
        SIUL2_0_PORT93_EMIOS_1_EMIOS_1_CH_10_H_OUT |
        SIUL2_0_PORT94_EMIOS_1_EMIOS_1_CH_12_H_OUT |
        SIUL2_0_PORT95_EMIOS_1_EMIOS_1_CH_14_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_EMIOS_0_EMIOS_0_CH_2_G_OUT |
        SIUL2_0_PORT97_EMIOS_0_EMIOS_0_CH_3_G_OUT |
        SIUL2_0_PORT98_EMIOS_1_EMIOS_1_CH_21_Y_OUT |
        SIUL2_0_PORT99_EMIOS_1_EMIOS_1_CH_22_X_OUT |
        SIUL2_0_PORT100_EMIOS_1_EMIOS_1_CH_23_X_OUT |
        SIUL2_0_PORT101_EMIOS_0_EMIOS_0_CH_19_Y_OUT |
        SIUL2_0_PORT102_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT103_LPUART2_LPUART2_TX_OUT |
        SIUL2_0_PORT104_LPI2C1_LPI2C1_SDA_OUT |
        SIUL2_0_PORT105_LPI2C1_LPI2C1_SCL_OUT |
        SIUL2_0_PORT106_EMIOS_0_EMIOS_0_CH_16_X_OUT |
        SIUL2_0_PORT107_EMIOS_0_EMIOS_0_CH_17_Y_OUT |
        SIUL2_0_PORT108_EMIOS_0_EMIOS_0_CH_18_Y_OUT |
        SIUL2_0_PORT109_EMIOS_0_EMIOS_0_CH_20_Y_OUT |
        SIUL2_0_PORT110_EMIOS_0_EMIOS_0_CH_21_Y_OUT |
        SIUL2_0_PORT111_EMIOS_0_EMIOS_0_CH_0_X_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_EMIOS_0_EMIOS_0_CH_1_G_OUT |
        SIUL2_0_PORT113_EMIOS_0_EMIOS_0_CH_18_Y_OUT |
        SIUL2_0_PORT114_EMIOS_1_EMIOS_1_CH_15_H_OUT |
        SIUL2_0_PORT115_EMIOS_1_EMIOS_1_CH_16_X_OUT |
        SIUL2_0_PORT116_EMIOS_1_EMIOS_1_CH_17_Y_OUT |
        SIUL2_0_PORT117_EMIOS_1_EMIOS_1_CH_18_Y_OUT |
        SIUL2_0_PORT118_EMIOS_1_EMIOS_1_CH_19_Y_OUT |
        SIUL2_0_PORT119_EMIOS_1_EMIOS_1_CH_20_Y_OUT |
        SIUL2_0_PORT120_EMIOS_1_EMIOS_1_CH_21_Y_OUT |
        SIUL2_0_PORT121_EMIOS_1_EMIOS_1_CH_22_X_OUT |
        SIUL2_0_PORT122_EMIOS_1_EMIOS_1_CH_23_X_OUT |
        SIUL2_0_PORT127_LPSPI5_LPSPI5_SCK_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_LPSPI0_LPSPI0_SIN_OUT |
        SIUL2_0_PORT129_LPSPI0_LPSPI0_SCK_OUT |
        SIUL2_0_PORT130_LPSPI0_LPSPI0_SOUT_OUT |
        SIUL2_0_PORT131_SAI1_SAI1_D0_OUT |
        SIUL2_0_PORT132_LPSPI1_LPSPI1_PCS1_OUT |
        SIUL2_0_PORT134_LPSPI0_LPSPI0_PCS2_OUT |
        SIUL2_0_PORT135_EMIOS_0_EMIOS_0_CH_7_G_OUT |
        SIUL2_0_PORT136_EMIOS_0_EMIOS_0_CH_6_G_OUT |
        SIUL2_0_PORT137_EMIOS_0_EMIOS_0_CH_7_G_OUT |
        SIUL2_0_PORT138_LPSPI3_LPSPI3_SIN_OUT |
        SIUL2_0_PORT139_LPSPI2_LPSPI2_PCS0_OUT |
        SIUL2_0_PORT140_CAN5_CAN5_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPUART3_LPUART3_TX_OUT |
        SIUL2_0_PORT147_EMIOS_0_EMIOS_0_CH_22_X_OUT |
        SIUL2_0_PORT148_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT149_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT150_EMIOS_1_EMIOS_1_CH_2_H_OUT |
        SIUL2_0_PORT151_EMIOS_1_EMIOS_1_CH_3_H_OUT |
        SIUL2_0_PORT152_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT153_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT154_EMIOS_1_EMIOS_1_CH_6_H_OUT |
        SIUL2_0_PORT155_EMIOS_1_EMIOS_1_CH_7_H_OUT |
        SIUL2_0_PORT158_CMP1_CMP1_OUT_OUT |
        SIUL2_0_PORT159_CMP1_CMP1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_EMIOS_2_EMIOS_2_CH_0_X_OUT |
        SIUL2_0_PORT161_EMIOS_2_EMIOS_2_CH_1_H_OUT |
        SIUL2_0_PORT162_EMIOS_2_EMIOS_2_CH_2_H_OUT |
        SIUL2_0_PORT163_EMIOS_2_EMIOS_2_CH_3_H_OUT |
        SIUL2_0_PORT164_EMIOS_2_EMIOS_2_CH_4_H_OUT |
        SIUL2_0_PORT165_EMIOS_2_EMIOS_2_CH_5_H_OUT |
        SIUL2_0_PORT166_EMIOS_2_EMIOS_2_CH_6_H_OUT |
        SIUL2_0_PORT167_EMIOS_2_EMIOS_2_CH_7_H_OUT |
        SIUL2_0_PORT168_EMIOS_2_EMIOS_2_CH_8_X_OUT |
        SIUL2_0_PORT169_EMIOS_2_EMIOS_2_CH_9_H_OUT |
        SIUL2_0_PORT170_EMIOS_2_EMIOS_2_CH_10_H_OUT |
        SIUL2_0_PORT171_EMIOS_2_EMIOS_2_CH_11_H_OUT |
        SIUL2_0_PORT172_EMIOS_2_EMIOS_2_CH_12_H_OUT |
        SIUL2_0_PORT173_EMIOS_2_EMIOS_2_CH_13_H_OUT |
        SIUL2_0_PORT174_EMIOS_2_EMIOS_2_CH_14_H_OUT |
        SIUL2_0_PORT175_EMIOS_2_EMIOS_2_CH_15_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_EMIOS_2_EMIOS_2_CH_16_X_OUT |
        SIUL2_0_PORT177_EMIOS_2_EMIOS_2_CH_17_Y_OUT |
        SIUL2_0_PORT178_EMIOS_2_EMIOS_2_CH_18_Y_OUT |
        SIUL2_0_PORT179_EMIOS_2_EMIOS_2_CH_19_Y_OUT |
        SIUL2_0_PORT180_EMIOS_2_EMIOS_2_CH_20_Y_OUT |
        SIUL2_0_PORT181_EMIOS_2_EMIOS_2_CH_21_Y_OUT |
        SIUL2_0_PORT182_EMIOS_2_EMIOS_2_CH_22_X_OUT |
        SIUL2_0_PORT183_EMIOS_2_EMIOS_2_CH_23_X_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT198_FXIO_FXIO_D10_OUT |
        SIUL2_0_PORT199_FXIO_FXIO_D11_OUT |
        SIUL2_0_PORT200_FXIO_FXIO_D12_OUT |
        SIUL2_0_PORT201_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT205_FXIO_FXIO_D13_OUT |
        SIUL2_0_PORT206_LPSPI2_LPSPI2_PCS2_OUT |
        SIUL2_0_PORT207_FXIO_FXIO_D14_OUT */
        (uint16)( SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_EMIOS_2_EMIOS_2_CH_16_X_OUT |
        SIUL2_0_PORT209_EMIOS_2_EMIOS_2_CH_17_Y_OUT |
        SIUL2_0_PORT210_EMIOS_2_EMIOS_2_CH_18_Y_OUT |
        SIUL2_0_PORT211_EMIOS_2_EMIOS_2_CH_19_Y_OUT |
        SIUL2_0_PORT212_EMIOS_2_EMIOS_2_CH_20_Y_OUT |
        SIUL2_0_PORT213_EMIOS_2_EMIOS_2_CH_21_Y_OUT |
        SIUL2_0_PORT214_EMIOS_2_EMIOS_2_CH_22_X_OUT |
        SIUL2_0_PORT215_EMIOS_2_EMIOS_2_CH_23_X_OUT |
        SIUL2_0_PORT216_LPSPI5_LPSPI5_PCS2_OUT |
        SIUL2_0_PORT217_LPSPI5_LPSPI5_SOUT_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_LPUART0_LPUART0_TX_OUT |
        SIUL2_0_PORT226_LPUART3_LPUART3_TX_OUT |
        SIUL2_0_PORT232_LPUART2_LPUART2_TX_OUT |
        SIUL2_0_PORT237_CAN8_CAN8_TX_OUT |
        SIUL2_0_PORT239_CAN11_CAN11_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT241_LPUART14_LPUART14_TX_OUT |
        SIUL2_0_PORT243_LPUART15_LPUART15_TX_OUT |
        SIUL2_0_PORT245_EMIOS_2_EMIOS_2_CH_17_Y_OUT |
        SIUL2_0_PORT246_EMIOS_2_EMIOS_2_CH_18_Y_OUT |
        SIUL2_0_PORT248_EMIOS_0_EMIOS_0_CH_0_X_OUT |
        SIUL2_0_PORT249_CAN11_CAN11_TX_OUT |
        SIUL2_0_PORT251_CAN8_CAN8_TX_OUT |
        SIUL2_0_PORT252_TRGMUX_TRGMUX_OUT0_OUT |
        SIUL2_0_PORT253_TRGMUX_TRGMUX_OUT1_OUT |
        SIUL2_0_PORT254_TRGMUX_TRGMUX_OUT2_OUT |
        SIUL2_0_PORT255_TRGMUX_TRGMUX_OUT3_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_CAN9_CAN9_TX_OUT |
        SIUL2_0_PORT258_LPUART13_LPUART13_TX_OUT |
        SIUL2_0_PORT260_LPUART14_LPUART14_TX_OUT |
        SIUL2_0_PORT264_TRGMUX_TRGMUX_OUT12_OUT |
        SIUL2_0_PORT265_TRGMUX_TRGMUX_OUT13_OUT |
        SIUL2_0_PORT266_TRGMUX_TRGMUX_OUT14_OUT |
        SIUL2_0_PORT267_TRGMUX_TRGMUX_OUT15_OUT |
        SIUL2_0_PORT268_LPUART9_LPUART9_TX_OUT |
        SIUL2_0_PORT270_CAN8_CAN8_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_CAN11_CAN11_TX_OUT |
        SIUL2_0_PORT274_CAN9_CAN9_TX_OUT |
        SIUL2_0_PORT276_CAN7_CAN7_TX_OUT |
        SIUL2_0_PORT279_CAN10_CAN10_TX_OUT |
        SIUL2_0_PORT281_LPUART9_LPUART9_TX_OUT |
        SIUL2_0_PORT284_EMIOS_2_EMIOS_2_CH_9_H_OUT |
        SIUL2_0_PORT285_EMIOS_2_EMIOS_2_CH_10_H_OUT |
        SIUL2_0_PORT286_EMIOS_2_EMIOS_2_CH_11_H_OUT |
        SIUL2_0_PORT287_EMIOS_2_EMIOS_2_CH_12_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT289_EMIOS_2_EMIOS_2_CH_19_Y_OUT |
        SIUL2_0_PORT290_EMIOS_2_EMIOS_2_CH_20_Y_OUT |
        SIUL2_0_PORT291_EMIOS_2_EMIOS_2_CH_21_Y_OUT |
        SIUL2_0_PORT292_EMIOS_2_EMIOS_2_CH_22_X_OUT |
        SIUL2_0_PORT293_EMIOS_2_EMIOS_2_CH_23_X_OUT |
        SIUL2_0_PORT294_EMIOS_2_EMIOS_2_CH_13_H_OUT |
        SIUL2_0_PORT295_EMIOS_2_EMIOS_2_CH_14_H_OUT |
        SIUL2_0_PORT296_EMIOS_2_EMIOS_2_CH_15_H_OUT |
        SIUL2_0_PORT297_EMIOS_2_EMIOS_2_CH_16_X_OUT |
        SIUL2_0_PORT298_CAN9_CAN9_TX_OUT |
        SIUL2_0_PORT300_CAN8_CAN8_TX_OUT |
        SIUL2_0_PORT302_CAN9_CAN9_TX_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_CAN10_CAN10_TX_OUT |
        SIUL2_0_PORT306_CAN11_CAN11_TX_OUT |
        SIUL2_0_PORT308_CAN6_CAN6_TX_OUT |
        SIUL2_0_PORT311_CAN9_CAN9_TX_OUT |
        SIUL2_0_PORT314_CAN10_CAN10_TX_OUT |
        SIUL2_0_PORT316_EMIOS_1_EMIOS_1_CH_16_X_OUT |
        SIUL2_0_PORT317_EMIOS_1_EMIOS_1_CH_17_Y_OUT |
        SIUL2_0_PORT318_EMIOS_1_EMIOS_1_CH_18_Y_OUT |
        SIUL2_0_PORT319_EMIOS_1_EMIOS_1_CH_19_Y_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_EMIOS_1_EMIOS_1_CH_20_Y_OUT |
        SIUL2_0_PORT321_EMIOS_1_EMIOS_1_CH_21_Y_OUT |
        SIUL2_0_PORT322_EMIOS_1_EMIOS_1_CH_22_X_OUT |
        SIUL2_0_PORT323_EMIOS_1_EMIOS_1_CH_23_X_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_ALT3_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LCU0_LCU0_OUT4_OUT |
        SIUL2_0_PORT1_LPUART0_LPUART0_RTS_OUT |
        SIUL2_0_PORT3_LPSPI1_LPSPI1_SCK_OUT |
        SIUL2_0_PORT4_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT6_LPSPI1_LPSPI1_PCS1_OUT |
        SIUL2_0_PORT7_EMIOS_1_EMIOS_1_CH_11_H_OUT |
        SIUL2_0_PORT8_LPSPI2_LPSPI2_SOUT_OUT |
        SIUL2_0_PORT9_LPSPI2_LPSPI2_PCS0_OUT |
        SIUL2_0_PORT11_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT12_SYSTEM_CLKOUT_STANDBY_OUT |
        SIUL2_0_PORT14_LPSPI1_LPSPI1_PCS3_OUT |
        SIUL2_0_PORT15_LPSPI0_LPSPI0_PCS3_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI1_LPSPI1_PCS2_OUT |
        SIUL2_0_PORT18_LPUART1_LPUART1_TX_OUT |
        SIUL2_0_PORT21_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT22_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT23_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT26_LPSPI1_LPSPI1_PCS0_OUT |
        SIUL2_0_PORT27_GMAC0_GMAC0_PPS1_OUT |
        SIUL2_0_PORT28_LPSPI1_LPSPI1_SCK_OUT |
        SIUL2_0_PORT29_GMAC0_GMAC0_PPS2_OUT |
        SIUL2_0_PORT30_LPSPI1_LPSPI1_SOUT_OUT |
        SIUL2_0_PORT31_FXIO_FXIO_D0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT33_LPSPI0_LPSPI0_SOUT_OUT |
        SIUL2_0_PORT34_LPSPI2_LPSPI2_SIN_OUT |
        SIUL2_0_PORT35_LPSPI2_LPSPI2_SOUT_OUT |
        SIUL2_0_PORT36_LPSPI0_LPSPI0_SOUT_OUT |
        SIUL2_0_PORT37_LPSPI0_LPSPI0_PCS1_OUT |
        SIUL2_0_PORT42_LPUART0_LPUART0_DTR_B_OUT |
        SIUL2_0_PORT45_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT46_LPSPI1_LPSPI1_SCK_OUT |
        SIUL2_0_PORT47_LPSPI1_LPSPI1_SIN_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_LPSPI1_LPSPI1_SOUT_OUT |
        SIUL2_0_PORT49_LPSPI1_LPSPI1_PCS3_OUT |
        SIUL2_0_PORT50_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT51_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT52_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT53_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT54_LPSPI3_LPSPI3_PCS1_OUT |
        SIUL2_0_PORT55_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT56_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT57_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT58_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT59_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT60_FXIO_FXIO_D9_OUT |
        SIUL2_0_PORT61_FXIO_FXIO_D10_OUT |
        SIUL2_0_PORT62_FXIO_FXIO_D11_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT66_LPSPI3_LPSPI3_PCS2_OUT |
        SIUL2_0_PORT67_CAN0_CAN0_TX_OUT |
        SIUL2_0_PORT70_LPSPI1_LPSPI1_PCS1_OUT |
        SIUL2_0_PORT71_LPI2C1_LPI2C1_SCL_OUT |
        SIUL2_0_PORT72_CAN1_CAN1_TX_OUT |
        SIUL2_0_PORT73_LPUART0_LPUART0_RTS_OUT |
        SIUL2_0_PORT74_CAN5_CAN5_TX_OUT |
        SIUL2_0_PORT75_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT76_EMIOS_0_EMIOS_0_CH_22_X_OUT |
        SIUL2_0_PORT77_EMIOS_0_EMIOS_0_CH_23_X_OUT |
        SIUL2_0_PORT78_LPSPI2_LPSPI2_PCS0_OUT |
        SIUL2_0_PORT79_LPSPI2_LPSPI2_SCK_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_EMIOS_2_EMIOS_2_CH_9_H_OUT |
        SIUL2_0_PORT81_CAN2_CAN2_TX_OUT |
        SIUL2_0_PORT82_FXIO_FXIO_D12_OUT |
        SIUL2_0_PORT83_FXIO_FXIO_D13_OUT |
        SIUL2_0_PORT84_FXIO_FXIO_D14_OUT |
        SIUL2_0_PORT85_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT87_FXIO_FXIO_D16_OUT |
        SIUL2_0_PORT88_FXIO_FXIO_D17_OUT |
        SIUL2_0_PORT89_FXIO_FXIO_D18_OUT |
        SIUL2_0_PORT90_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT91_FXIO_FXIO_D20_OUT |
        SIUL2_0_PORT92_FXIO_FXIO_D21_OUT |
        SIUL2_0_PORT93_FXIO_FXIO_D22_OUT |
        SIUL2_0_PORT94_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT95_FXIO_FXIO_D1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_LPSPI3_LPSPI3_SOUT_OUT |
        SIUL2_0_PORT97_LPSPI3_LPSPI3_SCK_OUT |
        SIUL2_0_PORT98_LPSPI1_LPSPI1_SOUT_OUT |
        SIUL2_0_PORT99_LPSPI1_LPSPI1_PCS0_OUT |
        SIUL2_0_PORT100_LPSPI1_LPSPI1_PCS1_OUT |
        SIUL2_0_PORT101_EMIOS_0_EMIOS_0_CH_2_G_OUT |
        SIUL2_0_PORT102_EMIOS_1_EMIOS_1_CH_12_H_OUT |
        SIUL2_0_PORT103_LPSPI3_LPSPI3_PCS3_OUT |
        SIUL2_0_PORT105_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT106_EMIOS_1_EMIOS_1_CH_10_H_OUT |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_RMII_TX_EN_OUT |
        SIUL2_0_PORT108_LPUART2_LPUART2_RTS_OUT |
        SIUL2_0_PORT109_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT110_LPUART1_LPUART1_TX_OUT |
        SIUL2_0_PORT111_EMIOS_1_EMIOS_1_CH_14_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_GMAC0_GMAC0_MII_RMII_RGMII_MDIO_OUT |
        SIUL2_0_PORT113_GMAC0_GMAC0_MII_RMII_RGMII_MDC_OUT |
        SIUL2_0_PORT114_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT115_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT116_FXIO_FXIO_D25_OUT |
        SIUL2_0_PORT117_FXIO_FXIO_D26_OUT |
        SIUL2_0_PORT118_FXIO_FXIO_D27_OUT |
        SIUL2_0_PORT119_FXIO_FXIO_D28_OUT |
        SIUL2_0_PORT120_FXIO_FXIO_D29_OUT |
        SIUL2_0_PORT122_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT127_FXIO_FXIO_D6_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT129_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT130_EMIOS_0_EMIOS_0_CH_3_G_OUT |
        SIUL2_0_PORT131_EMIOS_0_EMIOS_0_CH_19_Y_OUT |
        SIUL2_0_PORT132_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT133_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT134_LPUART1_LPUART1_RTS_OUT |
        SIUL2_0_PORT136_LPSPI5_LPSPI5_PCS1_OUT |
        SIUL2_0_PORT137_EMIOS_1_EMIOS_1_CH_13_H_OUT |
        SIUL2_0_PORT138_LPSPI2_LPSPI2_PCS1_OUT |
        SIUL2_0_PORT139_EMIOS_0_EMIOS_0_CH_1_G_OUT |
        SIUL2_0_PORT140_LPUART2_LPUART2_TX_OUT |
        SIUL2_0_PORT143_LPSPI2_LPSPI2_SCK_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPSPI2_LPSPI2_SIN_OUT |
        SIUL2_0_PORT145_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT146_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT152_CAN2_CAN2_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_LPSPI2_LPSPI2_SCK_OUT |
        SIUL2_0_PORT161_LPSPI2_LPSPI2_SIN_OUT |
        SIUL2_0_PORT162_LPSPI2_LPSPI2_SOUT_OUT |
        SIUL2_0_PORT163_LPSPI2_LPSPI2_PCS0_OUT |
        SIUL2_0_PORT164_LPSPI2_LPSPI2_SOUT_OUT |
        SIUL2_0_PORT167_LPI2C1_LPI2C1_SCL_OUT |
        SIUL2_0_PORT168_LPI2C1_LPI2C1_SDA_OUT |
        SIUL2_0_PORT169_ADC0_ADC0_MA_0_OUT |
        SIUL2_0_PORT170_ADC0_ADC0_MA_1_OUT |
        SIUL2_0_PORT171_ADC0_ADC0_MA_2_OUT |
        SIUL2_0_PORT172_ADC0_ADC0_MA_0_OUT |
        SIUL2_0_PORT173_ADC0_ADC0_MA_1_OUT |
        SIUL2_0_PORT174_CMP0_CMP0_OUT_OUT |
        SIUL2_0_PORT175_CMP0_CMP0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT177_EMIOS_1_EMIOS_1_CH_1_H_OUT |
        SIUL2_0_PORT178_EMIOS_1_EMIOS_1_CH_2_H_OUT |
        SIUL2_0_PORT179_EMIOS_1_EMIOS_1_CH_3_H_OUT |
        SIUL2_0_PORT180_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT181_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT182_EMIOS_1_EMIOS_1_CH_6_H_OUT |
        SIUL2_0_PORT183_EMIOS_1_EMIOS_1_CH_7_H_OUT |
        SIUL2_0_PORT184_EMIOS_1_EMIOS_1_CH_8_X_OUT |
        SIUL2_0_PORT185_EMIOS_1_EMIOS_1_CH_9_H_OUT |
        SIUL2_0_PORT186_EMIOS_1_EMIOS_1_CH_10_H_OUT |
        SIUL2_0_PORT187_EMIOS_1_EMIOS_1_CH_11_H_OUT |
        SIUL2_0_PORT188_EMIOS_1_EMIOS_1_CH_12_H_OUT |
        SIUL2_0_PORT189_EMIOS_1_EMIOS_1_CH_13_H_OUT |
        SIUL2_0_PORT190_EMIOS_1_EMIOS_1_CH_14_H_OUT |
        SIUL2_0_PORT191_EMIOS_1_EMIOS_1_CH_15_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_EMIOS_1_EMIOS_1_CH_16_X_OUT |
        SIUL2_0_PORT193_EMIOS_1_EMIOS_1_CH_17_Y_OUT |
        SIUL2_0_PORT194_EMIOS_1_EMIOS_1_CH_18_Y_OUT |
        SIUL2_0_PORT195_EMIOS_1_EMIOS_1_CH_19_Y_OUT |
        SIUL2_0_PORT196_EMIOS_1_EMIOS_1_CH_20_Y_OUT |
        SIUL2_0_PORT197_EMIOS_1_EMIOS_1_CH_21_Y_OUT |
        SIUL2_0_PORT198_EMIOS_1_EMIOS_1_CH_22_X_OUT |
        SIUL2_0_PORT199_EMIOS_1_EMIOS_1_CH_23_X_OUT |
        SIUL2_0_PORT200_LPSPI5_LPSPI5_PCS3_OUT |
        SIUL2_0_PORT201_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT205_LPSPI5_LPSPI5_PCS2_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT209_FXIO_FXIO_D16_OUT |
        SIUL2_0_PORT210_FXIO_FXIO_D17_OUT |
        SIUL2_0_PORT211_FXIO_FXIO_D18_OUT |
        SIUL2_0_PORT212_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT213_FXIO_FXIO_D20_OUT |
        SIUL2_0_PORT214_FXIO_FXIO_D21_OUT |
        SIUL2_0_PORT215_FXIO_FXIO_D22_OUT |
        SIUL2_0_PORT216_FXIO_FXIO_D23_OUT |
        SIUL2_0_PORT217_FXIO_FXIO_D24_OUT |
        SIUL2_0_PORT218_FXIO_FXIO_D25_OUT |
        SIUL2_0_PORT219_FXIO_FXIO_D26_OUT |
        SIUL2_0_PORT221_FXIO_FXIO_D29_OUT |
        SIUL2_0_PORT222_FXIO_FXIO_D30_OUT |
        SIUL2_0_PORT223_FXIO_FXIO_D31_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_FXIO_FXIO_D16_OUT |
        SIUL2_0_PORT225_FXIO_FXIO_D17_OUT |
        SIUL2_0_PORT226_FXIO_FXIO_D18_OUT |
        SIUL2_0_PORT227_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT228_FXIO_FXIO_D20_OUT |
        SIUL2_0_PORT229_FXIO_FXIO_D21_OUT |
        SIUL2_0_PORT230_FXIO_FXIO_D22_OUT |
        SIUL2_0_PORT231_FXIO_FXIO_D23_OUT |
        SIUL2_0_PORT232_FXIO_FXIO_D24_OUT |
        SIUL2_0_PORT233_FXIO_FXIO_D25_OUT |
        SIUL2_0_PORT234_FXIO_FXIO_D26_OUT |
        SIUL2_0_PORT235_FXIO_FXIO_D27_OUT |
        SIUL2_0_PORT236_FXIO_FXIO_D28_OUT |
        SIUL2_0_PORT237_LCU1_LCU1_OUT2_OUT |
        SIUL2_0_PORT238_LCU1_LCU1_OUT3_OUT |
        SIUL2_0_PORT239_LCU1_LCU1_OUT4_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT240_LCU1_LCU1_OUT5_OUT |
        SIUL2_0_PORT241_LCU1_LCU1_OUT6_OUT |
        SIUL2_0_PORT242_LCU1_LCU1_OUT7_OUT |
        SIUL2_0_PORT243_LCU1_LCU1_OUT8_OUT |
        SIUL2_0_PORT244_LCU1_LCU1_OUT9_OUT |
        SIUL2_0_PORT249_LCU1_LCU1_OUT10_OUT |
        SIUL2_0_PORT250_LCU1_LCU1_OUT11_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_EMIOS_2_EMIOS_2_CH_0_X_OUT |
        SIUL2_0_PORT257_EMIOS_2_EMIOS_2_CH_1_H_OUT |
        SIUL2_0_PORT259_EMIOS_2_EMIOS_2_CH_3_H_OUT |
        SIUL2_0_PORT260_EMIOS_2_EMIOS_2_CH_5_H_OUT |
        SIUL2_0_PORT262_EMIOS_2_EMIOS_2_CH_7_H_OUT |
        SIUL2_0_PORT263_EMIOS_2_EMIOS_2_CH_8_X_OUT |
        SIUL2_0_PORT264_EMIOS_2_EMIOS_2_CH_6_H_OUT |
        SIUL2_0_PORT265_CAN10_CAN10_TX_OUT |
        SIUL2_0_PORT266_EMIOS_2_EMIOS_2_CH_4_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_LPSPI1_LPSPI1_PCS0_OUT |
        SIUL2_0_PORT274_LPSPI1_LPSPI1_SOUT_OUT |
        SIUL2_0_PORT276_LPSPI1_LPSPI1_SIN_OUT |
        SIUL2_0_PORT279_LPSPI1_LPSPI1_SCK_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT288_CAN10_CAN10_TX_OUT |
        SIUL2_0_PORT292_LPUART13_LPUART13_TX_OUT |
        SIUL2_0_PORT298_EMIOS_2_EMIOS_2_CH_2_H_OUT |
        SIUL2_0_PORT300_FXIO_FXIO_D28_OUT |
        SIUL2_0_PORT301_FXIO_FXIO_D29_OUT |
        SIUL2_0_PORT302_FXIO_FXIO_D30_OUT |
        SIUL2_0_PORT303_FXIO_FXIO_D31_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_LPSPI3_LPSPI3_PCS0_OUT |
        SIUL2_0_PORT311_LPSPI4_LPSPI4_SIN_OUT |
        SIUL2_0_PORT314_LCU1_LCU1_OUT0_OUT |
        SIUL2_0_PORT315_LCU1_LCU1_OUT1_OUT |
        SIUL2_0_PORT317_CAN8_CAN8_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_CAN11_CAN11_TX_OUT |
        SIUL2_0_PORT322_LPUART15_LPUART15_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U)
                )
    }
    ,
    /*  Mode PORT_ALT4_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT1_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT3_LCU0_LCU0_OUT2_OUT |
        SIUL2_0_PORT4_CMP0_CMP0_OUT_OUT |
        SIUL2_0_PORT6_EMIOS_1_EMIOS_1_CH_13_H_OUT |
        SIUL2_0_PORT7_CAN0_CAN0_TX_OUT |
        SIUL2_0_PORT8_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT9_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT10_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT11_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT14_EMIOS_2_EMIOS_2_CH_18_Y_OUT |
        SIUL2_0_PORT15_LPSPI2_LPSPI2_PCS3_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI0_LPSPI0_PCS4_OUT |
        SIUL2_0_PORT17_LPUART4_LPUART4_TX_OUT |
        SIUL2_0_PORT18_LPSPI1_LPSPI1_SOUT_OUT |
        SIUL2_0_PORT19_LPSPI1_LPSPI1_SCK_OUT |
        SIUL2_0_PORT20_LPSPI1_LPSPI1_SIN_OUT |
        SIUL2_0_PORT21_LPSPI1_LPSPI1_PCS0_OUT |
        SIUL2_0_PORT22_LPSPI1_LPSPI1_PCS1_OUT |
        SIUL2_0_PORT26_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT27_LPUART0_LPUART0_TX_OUT |
        SIUL2_0_PORT29_LPUART2_LPUART2_TX_OUT |
        SIUL2_0_PORT30_LPSPI0_LPSPI0_SOUT_OUT |
        SIUL2_0_PORT31_LPSPI0_LPSPI0_PCS1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_EMIOS_0_EMIOS_0_CH_3_G_OUT |
        SIUL2_0_PORT33_EMIOS_0_EMIOS_0_CH_7_G_OUT |
        SIUL2_0_PORT35_ADC0_ADC0_MA_0_OUT |
        SIUL2_0_PORT37_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT46_LCU0_LCU0_OUT7_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_LPUART4_LPUART4_TX_OUT |
        SIUL2_0_PORT49_EMIOS_1_EMIOS_1_CH_7_H_OUT |
        SIUL2_0_PORT50_LPSPI1_LPSPI1_PCS1_OUT |
        SIUL2_0_PORT51_GMAC0_GMAC0_MII_RMII_TX_EN_OUT |
        SIUL2_0_PORT54_EMIOS_2_EMIOS_2_CH_18_Y_OUT |
        SIUL2_0_PORT55_EMIOS_2_EMIOS_2_CH_19_Y_OUT |
        SIUL2_0_PORT56_EMIOS_2_EMIOS_2_CH_20_Y_OUT |
        SIUL2_0_PORT57_EMIOS_2_EMIOS_2_CH_21_Y_OUT |
        SIUL2_0_PORT58_EMIOS_2_EMIOS_2_CH_22_X_OUT |
        SIUL2_0_PORT59_EMIOS_2_EMIOS_2_CH_23_X_OUT |
        SIUL2_0_PORT60_EMIOS_2_EMIOS_2_CH_10_H_OUT |
        SIUL2_0_PORT61_EMIOS_2_EMIOS_2_CH_11_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT65_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT66_LPSPI0_LPSPI0_PCS2_OUT |
        SIUL2_0_PORT67_LPUART0_LPUART0_TX_OUT |
        SIUL2_0_PORT68_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT69_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT70_LCU0_LCU0_OUT7_OUT |
        SIUL2_0_PORT71_LCU0_LCU0_OUT6_OUT |
        SIUL2_0_PORT72_EMIOS_1_EMIOS_1_CH_9_H_OUT |
        SIUL2_0_PORT73_EMIOS_1_EMIOS_1_CH_8_X_OUT |
        SIUL2_0_PORT74_LPSPI2_LPSPI2_PCS1_OUT |
        SIUL2_0_PORT75_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT76_LPSPI2_LPSPI2_PCS1_OUT |
        SIUL2_0_PORT77_ADC1_ADC1_MA_1_OUT |
        SIUL2_0_PORT78_ADC0_ADC0_MA_1_OUT |
        SIUL2_0_PORT79_ADC0_ADC0_MA_2_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPI2C1_LPI2C1_SDAS_OUT |
        SIUL2_0_PORT81_LPI2C1_LPI2C1_SCLS_OUT |
        SIUL2_0_PORT82_EMIOS_2_EMIOS_2_CH_12_H_OUT |
        SIUL2_0_PORT83_EMIOS_2_EMIOS_2_CH_13_H_OUT |
        SIUL2_0_PORT84_EMIOS_2_EMIOS_2_CH_14_H_OUT |
        SIUL2_0_PORT85_EMIOS_2_EMIOS_2_CH_15_H_OUT |
        SIUL2_0_PORT88_EMIOS_2_EMIOS_2_CH_0_X_OUT |
        SIUL2_0_PORT89_EMIOS_2_EMIOS_2_CH_1_H_OUT |
        SIUL2_0_PORT90_EMIOS_2_EMIOS_2_CH_2_H_OUT |
        SIUL2_0_PORT91_EMIOS_2_EMIOS_2_CH_3_H_OUT |
        SIUL2_0_PORT92_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT93_EMIOS_2_EMIOS_2_CH_4_H_OUT |
        SIUL2_0_PORT94_EMIOS_2_EMIOS_2_CH_5_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_EMIOS_0_EMIOS_0_CH_16_X_OUT |
        SIUL2_0_PORT97_EMIOS_0_EMIOS_0_CH_17_Y_OUT |
        SIUL2_0_PORT98_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT99_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT101_GMAC1_GMAC1_MII_RMII_RX_DV_RGMII_RXCTL_OUT |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_RMII_TX_CLK_OUT |
        SIUL2_0_PORT103_LPSPI0_LPSPI0_PCS3_OUT |
        SIUL2_0_PORT105_LPUART6_LPUART6_TX_OUT |
        SIUL2_0_PORT106_TRACE_TRACE_ETM_D3_OUT |
        SIUL2_0_PORT107_TRACE_TRACE_ETM_D2_OUT |
        SIUL2_0_PORT108_TRACE_TRACE_ETM_D1_OUT |
        SIUL2_0_PORT109_LPI2C0_LPI2C0_SDA_OUT |
        SIUL2_0_PORT110_LPI2C0_LPI2C0_SCL_OUT |
        SIUL2_0_PORT111_LPSPI0_LPSPI0_SCK_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPSPI0_LPSPI0_SIN_OUT |
        SIUL2_0_PORT116_EMIOS_2_EMIOS_2_CH_0_X_OUT |
        SIUL2_0_PORT117_EMIOS_2_EMIOS_2_CH_8_X_OUT |
        SIUL2_0_PORT118_EMIOS_2_EMIOS_2_CH_22_X_OUT |
        SIUL2_0_PORT119_EMIOS_2_EMIOS_2_CH_23_X_OUT |
        SIUL2_0_PORT122_EMIOS_2_EMIOS_2_CH_7_H_OUT |
        SIUL2_0_PORT123_EMIOS_2_EMIOS_2_CH_9_H_OUT |
        SIUL2_0_PORT124_EMIOS_2_EMIOS_2_CH_0_X_OUT |
        SIUL2_0_PORT125_EMIOS_2_EMIOS_2_CH_8_X_OUT |
        SIUL2_0_PORT126_EMIOS_2_EMIOS_2_CH_16_X_OUT |
        SIUL2_0_PORT127_EMIOS_2_EMIOS_2_CH_22_X_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT130_EMIOS_1_EMIOS_1_CH_8_X_OUT |
        SIUL2_0_PORT131_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT132_EMIOS_0_EMIOS_0_CH_18_Y_OUT |
        SIUL2_0_PORT133_EMIOS_0_EMIOS_0_CH_19_Y_OUT |
        SIUL2_0_PORT134_EMIOS_1_EMIOS_1_CH_14_H_OUT |
        SIUL2_0_PORT136_FXIO_FXIO_D12_OUT |
        SIUL2_0_PORT137_CAN3_CAN3_TX_OUT |
        SIUL2_0_PORT138_EMIOS_0_EMIOS_0_CH_20_Y_OUT |
        SIUL2_0_PORT139_EMIOS_0_EMIOS_0_CH_21_Y_OUT |
        SIUL2_0_PORT140_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT142_LPUART5_LPUART5_TX_OUT |
        SIUL2_0_PORT143_EMIOS_0_EMIOS_0_CH_22_X_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_EMIOS_0_EMIOS_0_CH_23_X_OUT |
        SIUL2_0_PORT145_EMIOS_2_EMIOS_2_CH_23_X_OUT |
        SIUL2_0_PORT146_EMIOS_2_EMIOS_2_CH_17_Y_OUT |
        SIUL2_0_PORT149_EMIOS_2_EMIOS_2_CH_19_Y_OUT |
        SIUL2_0_PORT150_EMIOS_2_EMIOS_2_CH_20_Y_OUT |
        SIUL2_0_PORT151_EMIOS_2_EMIOS_2_CH_21_Y_OUT |
        SIUL2_0_PORT152_EMIOS_2_EMIOS_2_CH_4_H_OUT |
        SIUL2_0_PORT153_EMIOS_2_EMIOS_2_CH_5_H_OUT |
        SIUL2_0_PORT154_EMIOS_2_EMIOS_2_CH_6_H_OUT |
        SIUL2_0_PORT158_LPSPI0_LPSPI0_SOUT_OUT |
        SIUL2_0_PORT159_LPSPI0_LPSPI0_PCS0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT164_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT167_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT168_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT172_LPSPI3_LPSPI3_SIN_OUT |
        SIUL2_0_PORT173_LPSPI3_LPSPI3_SCK_OUT |
        SIUL2_0_PORT174_FCCU_FCCU_ERR0_OUT |
        SIUL2_0_PORT175_LPSPI3_LPSPI3_SOUT_OUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_ADC1_ADC1_MA_0_OUT |
        SIUL2_0_PORT177_ADC1_ADC1_MA_1_OUT |
        SIUL2_0_PORT178_ADC1_ADC1_MA_2_OUT |
        SIUL2_0_PORT179_ADC0_ADC0_MA_2_OUT |
        SIUL2_0_PORT180_LPI2C0_LPI2C0_SCL_OUT |
        SIUL2_0_PORT181_LPI2C0_LPI2C0_SDA_OUT |
        SIUL2_0_PORT188_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT189_ADC1_ADC1_MA_0_OUT |
        SIUL2_0_PORT190_ADC1_ADC1_MA_1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT196_CMP2_CMP2_OUT_OUT |
        SIUL2_0_PORT197_CMP2_CMP2_OUT |
        SIUL2_0_PORT201_LPUART2_LPUART2_TX_OUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT215_EMIOS_0_EMIOS_0_CH_0_X_OUT |
        SIUL2_0_PORT216_EMIOS_0_EMIOS_0_CH_1_G_OUT |
        SIUL2_0_PORT217_EMIOS_0_EMIOS_0_CH_2_G_OUT |
        SIUL2_0_PORT218_EMIOS_0_EMIOS_0_CH_3_G_OUT |
        SIUL2_0_PORT219_EMIOS_0_EMIOS_0_CH_4_G_OUT |
        SIUL2_0_PORT220_EMIOS_0_EMIOS_0_CH_5_G_OUT |
        SIUL2_0_PORT221_EMIOS_0_EMIOS_0_CH_6_G_OUT |
        SIUL2_0_PORT222_EMIOS_0_EMIOS_0_CH_7_G_OUT |
        SIUL2_0_PORT223_EMIOS_0_EMIOS_0_CH_8_X_OUT */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_EMIOS_0_EMIOS_0_CH_9_H_OUT |
        SIUL2_0_PORT225_EMIOS_0_EMIOS_0_CH_10_H_OUT |
        SIUL2_0_PORT226_EMIOS_0_EMIOS_0_CH_11_H_OUT |
        SIUL2_0_PORT227_EMIOS_0_EMIOS_0_CH_12_H_OUT |
        SIUL2_0_PORT228_EMIOS_0_EMIOS_0_CH_13_H_OUT |
        SIUL2_0_PORT229_EMIOS_0_EMIOS_0_CH_14_H_OUT |
        SIUL2_0_PORT230_EMIOS_0_EMIOS_0_CH_15_H_OUT |
        SIUL2_0_PORT231_EMIOS_0_EMIOS_0_CH_16_X_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303
        SIUL2_0_PORT298_LPSPI3_LPSPI3_SCK_OUT |
        SIUL2_0_PORT300_LPSPI3_LPSPI3_SIN_OUT |
        SIUL2_0_PORT302_LPSPI3_LPSPI3_SOUT_OUT */
        (uint16)( SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT314_LPSPI4_LPSPI4_SOUT_OUT |
        SIUL2_0_PORT317_LPSPI4_LPSPI4_SCK_OUT */
        (uint16)( SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_LPSPI4_LPSPI4_PCS0_OUT */
        (uint16)( SHL_PAD_U32(0U)
                )
    }
    ,
    /*  Mode PORT_ALT5_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT1_LCU0_LCU0_OUT5_OUT |
        SIUL2_0_PORT2_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT3_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT6_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT7_LPUART1_LPUART1_RTS_OUT |
        SIUL2_0_PORT11_CMP0_CMP0_OUT |
        SIUL2_0_PORT12_FXIO_FXIO_D9_OUT |
        SIUL2_0_PORT13_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT15_LPUART1_LPUART1_DTR_B_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPUART6_LPUART6_TX_OUT |
        SIUL2_0_PORT18_EMIOS_1_EMIOS_1_CH_16_X_OUT |
        SIUL2_0_PORT26_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT27_CAN0_CAN0_TX_OUT |
        SIUL2_0_PORT29_LPSPI1_LPSPI1_SIN_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LCU1_LCU1_OUT5_OUT |
        SIUL2_0_PORT33_CAN0_CAN0_TX_OUT |
        SIUL2_0_PORT34_LCU1_LCU1_OUT3_OUT |
        SIUL2_0_PORT35_CAN4_CAN4_TX_OUT |
        SIUL2_0_PORT36_GMAC0_GMAC0_MII_RMII_RGMII_MDIO_OUT |
        SIUL2_0_PORT37_SYSTEM_CLKOUT_RUN_OUT |
        SIUL2_0_PORT40_LCU0_LCU0_OUT11_OUT |
        SIUL2_0_PORT42_LPUART9_LPUART9_TX_OUT |
        SIUL2_0_PORT43_LCU0_LCU0_OUT8_OUT |
        SIUL2_0_PORT45_LCU0_LCU0_OUT3_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT50_EMIOS_2_EMIOS_2_CH_14_H_OUT |
        SIUL2_0_PORT51_EMIOS_2_EMIOS_2_CH_15_H_OUT |
        SIUL2_0_PORT52_EMIOS_2_EMIOS_2_CH_16_X_OUT |
        SIUL2_0_PORT53_EMIOS_2_EMIOS_2_CH_17_Y_OUT |
        SIUL2_0_PORT54_LPUART1_LPUART1_TX_OUT |
        SIUL2_0_PORT57_LPSPI2_LPSPI2_PCS0_OUT |
        SIUL2_0_PORT59_LPSPI2_LPSPI2_SOUT_OUT |
        SIUL2_0_PORT60_LPSPI2_LPSPI2_SIN_OUT |
        SIUL2_0_PORT61_LPSPI2_LPSPI2_SCK_OUT |
        SIUL2_0_PORT62_HSE_HSE_TAMPER_LOOP_OUT0_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT66_GMAC0_GMAC0_MII_RMII_TXD_0_OUT |
        SIUL2_0_PORT69_CMP2_CMP2_OUT |
        SIUL2_0_PORT70_EMIOS_1_EMIOS_1_CH_6_H_OUT |
        SIUL2_0_PORT71_EMIOS_1_EMIOS_1_CH_7_H_OUT |
        SIUL2_0_PORT72_LCU1_LCU1_OUT7_OUT |
        SIUL2_0_PORT73_LCU1_LCU1_OUT6_OUT |
        SIUL2_0_PORT74_LPSPI4_LPSPI4_PCS0_OUT |
        SIUL2_0_PORT75_LPSPI4_LPSPI4_SOUT_OUT |
        SIUL2_0_PORT76_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT77_FXIO_FXIO_D16_OUT |
        SIUL2_0_PORT78_EMIOS_1_EMIOS_1_CH_4_H_OUT |
        SIUL2_0_PORT79_LPUART2_LPUART2_TX_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_OUT |
        SIUL2_0_PORT81_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_OUT |
        SIUL2_0_PORT82_GMAC0_GMAC0_MII_RMII_RGMII_TXD_1_OUT |
        SIUL2_0_PORT83_LPSPI2_LPSPI2_PCS1_OUT |
        SIUL2_0_PORT84_ADC1_ADC1_MA_2_OUT |
        SIUL2_0_PORT85_ADC1_ADC1_MA_1_OUT |
        SIUL2_0_PORT88_CAN7_CAN7_TX_OUT |
        SIUL2_0_PORT89_LPSPI4_LPSPI4_PCS1_OUT |
        SIUL2_0_PORT91_ADC1_ADC1_MA_0_OUT |
        SIUL2_0_PORT92_LPI2C1_LPI2C1_SCL_OUT |
        SIUL2_0_PORT93_LPI2C1_LPI2C1_SDA_OUT |
        SIUL2_0_PORT95_EMIOS_2_EMIOS_2_CH_6_H_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT98_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT99_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT100_LCU0_LCU0_OUT6_OUT |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_TXD3_OUT |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_TXD2_OUT |
        SIUL2_0_PORT103_GMAC0_GMAC0_MII_RMII_TXD_1_OUT |
        SIUL2_0_PORT104_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT106_LPSPI0_LPSPI0_SIN_OUT |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_RMII_TX_CLK_OUT |
        SIUL2_0_PORT108_GMAC0_GMAC0_MII_RMII_TX_EN_OUT |
        SIUL2_0_PORT109_GMAC0_GMAC0_PPS1_OUT |
        SIUL2_0_PORT110_GMAC0_GMAC0_PPS0_OUT |
        SIUL2_0_PORT111_GMAC0_GMAC0_PPS2_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_EMIOS_1_EMIOS_1_CH_15_H_OUT |
        SIUL2_0_PORT113_LPSPI3_LPSPI3_PCS0_OUT |
        SIUL2_0_PORT116_LPSPI1_LPSPI1_PCS2_OUT |
        SIUL2_0_PORT117_LCU0_LCU0_OUT4_OUT |
        SIUL2_0_PORT119_HSE_HSE_TAMPER_LOOP_OUT0_OUT |
        SIUL2_0_PORT122_FXIO_FXIO_D30_OUT |
        SIUL2_0_PORT123_FXIO_FXIO_D31_OUT |
        SIUL2_0_PORT124_LCU0_LCU0_OUT2_OUT |
        SIUL2_0_PORT125_LCU0_LCU0_OUT3_OUT |
        SIUL2_0_PORT126_LCU0_LCU0_OUT8_OUT |
        SIUL2_0_PORT127_LCU0_LCU0_OUT9_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT131_LPUART2_LPUART2_RTS_OUT |
        SIUL2_0_PORT132_LPUART12_LPUART12_TX_OUT |
        SIUL2_0_PORT134_LPUART10_LPUART10_TX_OUT |
        SIUL2_0_PORT136_GMAC0_GMAC0_MII_RMII_RGMII_MDC_OUT |
        SIUL2_0_PORT137_GMAC0_GMAC0_PPS3_OUT |
        SIUL2_0_PORT138_SYSTEM_CLKOUT_STANDBY_OUT |
        SIUL2_0_PORT140_GMAC0_GMAC0_PPS3_OUT |
        SIUL2_0_PORT143_CMP1_CMP1_OUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPUART1_LPUART1_RTS_OUT |
        SIUL2_0_PORT152_FXIO_FXIO_D5_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT174_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT175_FCCU_FCCU_ERR1_OUT */
        (uint16)( SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_LPSPI3_LPSPI3_PCS0_OUT |
        SIUL2_0_PORT178_LPSPI3_LPSPI3_PCS1_OUT |
        SIUL2_0_PORT179_LPSPI3_LPSPI3_PCS2_OUT |
        SIUL2_0_PORT180_LPSPI3_LPSPI3_PCS3_OUT |
        SIUL2_0_PORT181_LPSPI1_LPSPI1_PCS0_OUT |
        SIUL2_0_PORT183_LPSPI3_LPSPI3_PCS3_OUT |
        SIUL2_0_PORT185_LPSPI2_LPSPI2_PCS2_OUT |
        SIUL2_0_PORT186_LPSPI2_LPSPI2_PCS3_OUT |
        SIUL2_0_PORT188_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT189_LPSPI3_LPSPI3_PCS1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT207_EMIOS_2_EMIOS_2_CH_15_H_OUT */
        (uint16)( SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239
        SIUL2_0_PORT224_LPSPI2_LPSPI2_PCS2_OUT |
        SIUL2_0_PORT225_LPSPI2_LPSPI2_PCS3_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT6_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPSPI0_LPSPI0_PCS7_OUT |
        SIUL2_0_PORT1_LPSPI0_LPSPI0_PCS6_OUT |
        SIUL2_0_PORT2_LCU0_LCU0_OUT3_OUT |
        SIUL2_0_PORT3_LPUART0_LPUART0_TX_OUT |
        SIUL2_0_PORT6_LPSPI3_LPSPI3_PCS1_OUT |
        SIUL2_0_PORT7_FXIO_FXIO_D9_OUT |
        SIUL2_0_PORT8_EMIOS_2_EMIOS_2_CH_7_H_OUT |
        SIUL2_0_PORT9_LPSPI3_LPSPI3_PCS0_OUT |
        SIUL2_0_PORT11_LPSPI1_LPSPI1_PCS0_OUT |
        SIUL2_0_PORT12_EMIOS_1_EMIOS_1_CH_2_H_OUT |
        SIUL2_0_PORT13_EMIOS_1_EMIOS_1_CH_3_H_OUT |
        SIUL2_0_PORT14_FXIO_FXIO_D14_OUT |
        SIUL2_0_PORT15_LPSPI5_LPSPI5_PCS0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT17_LPSPI3_LPSPI3_SOUT_OUT |
        SIUL2_0_PORT18_EMIOS_2_EMIOS_2_CH_0_X_OUT |
        SIUL2_0_PORT19_EMIOS_2_EMIOS_2_CH_1_H_OUT |
        SIUL2_0_PORT20_EMIOS_2_EMIOS_2_CH_2_H_OUT |
        SIUL2_0_PORT21_EMIOS_2_EMIOS_2_CH_3_H_OUT |
        SIUL2_0_PORT26_EMIOS_2_EMIOS_2_CH_9_H_OUT |
        SIUL2_0_PORT27_EMIOS_2_EMIOS_2_CH_10_H_OUT |
        SIUL2_0_PORT28_EMIOS_2_EMIOS_2_CH_11_H_OUT |
        SIUL2_0_PORT29_EMIOS_2_EMIOS_2_CH_12_H_OUT |
        SIUL2_0_PORT30_EMIOS_2_EMIOS_2_CH_13_H_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_EMIOS_1_EMIOS_1_CH_6_H_OUT |
        SIUL2_0_PORT33_EMIOS_1_EMIOS_1_CH_5_H_OUT |
        SIUL2_0_PORT34_SAI0_SAI0_D0_OUT |
        SIUL2_0_PORT35_LCU1_LCU1_OUT2_OUT |
        SIUL2_0_PORT36_EMIOS_1_EMIOS_1_CH_10_H_OUT |
        SIUL2_0_PORT37_EMIOS_1_EMIOS_1_CH_11_H_OUT |
        SIUL2_0_PORT40_LPSPI0_LPSPI0_PCS5_OUT |
        SIUL2_0_PORT41_LCU0_LCU0_OUT10_OUT |
        SIUL2_0_PORT42_LCU0_LCU0_OUT9_OUT |
        SIUL2_0_PORT44_LCU0_LCU0_OUT2_OUT |
        SIUL2_0_PORT45_LPUART8_LPUART8_TX_OUT |
        SIUL2_0_PORT47_LPUART7_LPUART7_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT49_LPSPI3_LPSPI3_PCS0_OUT |
        SIUL2_0_PORT54_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT57_GMAC0_GMAC0_RGMII_TXCTL_OUT |
        SIUL2_0_PORT59_SAI0_SAI0_D0_OUT |
        SIUL2_0_PORT60_LCU1_LCU1_OUT11_OUT |
        SIUL2_0_PORT61_LCU1_LCU1_OUT10_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_EMIOS_0_EMIOS_0_CH_14_H_OUT |
        SIUL2_0_PORT65_EMIOS_0_EMIOS_0_CH_15_H_OUT |
        SIUL2_0_PORT66_TRACE_TRACE_ETM_CLKOUT_OUT |
        SIUL2_0_PORT67_QUADSPI_QUADSPI_PCSFA_OUT |
        SIUL2_0_PORT70_LPSPI0_LPSPI0_PCS1_OUT |
        SIUL2_0_PORT71_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT72_LPSPI0_LPSPI0_SCK_OUT |
        SIUL2_0_PORT73_LPSPI0_LPSPI0_SIN_OUT |
        SIUL2_0_PORT74_LCU1_LCU1_OUT11_OUT |
        SIUL2_0_PORT75_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT76_LCU1_LCU1_OUT9_OUT |
        SIUL2_0_PORT77_LCU1_LCU1_OUT8_OUT |
        SIUL2_0_PORT78_LCU1_LCU1_OUT1_OUT |
        SIUL2_0_PORT79_LCU1_LCU1_OUT0_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT81_FXIO_FXIO_D14_OUT |
        SIUL2_0_PORT82_LCU1_LCU1_OUT7_OUT |
        SIUL2_0_PORT83_LCU1_LCU1_OUT6_OUT |
        SIUL2_0_PORT84_LCU1_LCU1_OUT5_OUT |
        SIUL2_0_PORT85_LCU1_LCU1_OUT4_OUT |
        SIUL2_0_PORT87_LCU1_LCU1_OUT0_OUT |
        SIUL2_0_PORT88_LCU1_LCU1_OUT1_OUT |
        SIUL2_0_PORT89_LCU1_LCU1_OUT2_OUT |
        SIUL2_0_PORT90_LCU1_LCU1_OUT9_OUT |
        SIUL2_0_PORT91_LCU1_LCU1_OUT3_OUT |
        SIUL2_0_PORT92_LCU1_LCU1_OUT8_OUT |
        SIUL2_0_PORT95_LPUART1_LPUART1_DTR_B_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_FXIO_FXIO_D0_OUT |
        SIUL2_0_PORT97_FXIO_FXIO_D1_OUT |
        SIUL2_0_PORT98_LPUART3_LPUART3_TX_OUT |
        SIUL2_0_PORT99_LCU0_LCU0_OUT0_OUT |
        SIUL2_0_PORT101_FXIO_FXIO_D15_OUT |
        SIUL2_0_PORT102_FXIO_FXIO_D13_OUT |
        SIUL2_0_PORT103_TRACE_TRACE_ETM_D0_OUT |
        SIUL2_0_PORT104_EMIOS_0_EMIOS_0_CH_12_H_OUT |
        SIUL2_0_PORT105_EMIOS_0_EMIOS_0_CH_13_H_OUT |
        SIUL2_0_PORT106_SYSTEM_CLKOUT_RUN_OUT |
        SIUL2_0_PORT107_LPSPI0_LPSPI0_SCK_OUT |
        SIUL2_0_PORT108_LPSPI0_LPSPI0_SOUT_OUT |
        SIUL2_0_PORT109_SAI1_SAI1_D0_OUT |
        SIUL2_0_PORT110_CMP0_CMP0_OUT |
        SIUL2_0_PORT111_SAI1_SAI1_SYNC_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPUART2_LPUART2_RTS_OUT |
        SIUL2_0_PORT113_FXIO_FXIO_D9_OUT |
        SIUL2_0_PORT116_LPSPI3_LPSPI3_SIN_OUT |
        SIUL2_0_PORT118_LCU0_LCU0_OUT5_OUT |
        SIUL2_0_PORT119_LCU0_LCU0_OUT10_OUT |
        SIUL2_0_PORT120_LCU0_LCU0_OUT11_OUT |
        SIUL2_0_PORT122_LPSPI5_LPSPI5_SCK_OUT |
        SIUL2_0_PORT123_LPSPI5_LPSPI5_SOUT_OUT |
        SIUL2_0_PORT124_LPSPI5_LPSPI5_SIN_OUT |
        SIUL2_0_PORT125_LPSPI5_LPSPI5_PCS2_OUT |
        SIUL2_0_PORT126_LPSPI5_LPSPI5_PCS3_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT129_LPUART7_LPUART7_TX_OUT |
        SIUL2_0_PORT130_FXIO_FXIO_D13_OUT |
        SIUL2_0_PORT131_GMAC0_GMAC0_PPS0_OUT |
        SIUL2_0_PORT132_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT133_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT134_FXIO_FXIO_D12_OUT |
        SIUL2_0_PORT135_LPSPI3_LPSPI3_SCK_OUT |
        SIUL2_0_PORT136_SAI1_SAI1_BCLK_OUT |
        SIUL2_0_PORT137_GMAC0_GMAC0_MII_RMII_TX_EN_OUT |
        SIUL2_0_PORT138_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT139_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT140_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT142_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT143_FXIO_FXIO_D2_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT149_LPSPI4_LPSPI4_SIN_OUT |
        SIUL2_0_PORT150_LPSPI4_LPSPI4_SCK_OUT |
        SIUL2_0_PORT151_LPSPI4_LPSPI4_PCS0_OUT |
        SIUL2_0_PORT152_LPSPI4_LPSPI4_PCS1_OUT |
        SIUL2_0_PORT153_LPSPI4_LPSPI4_SOUT_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191
        SIUL2_0_PORT179_HSE_HSE_TAMPER_LOOP_OUT0_OUT |
        SIUL2_0_PORT180_CAN0_CAN0_TX_OUT |
        SIUL2_0_PORT182_LPSPI4_LPSPI4_PCS2_OUT |
        SIUL2_0_PORT185_LPSPI4_LPSPI4_PCS0_OUT |
        SIUL2_0_PORT186_LPSPI4_LPSPI4_PCS1_OUT |
        SIUL2_0_PORT187_LPSPI4_LPSPI4_PCS2_OUT |
        SIUL2_0_PORT188_LPSPI4_LPSPI4_PCS3_OUT |
        SIUL2_0_PORT191_FXIO_FXIO_D9_OUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT204_LPSPI4_LPSPI4_PCS3_OUT */
        (uint16)( SHL_PAD_U32(12U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT212_CAN6_CAN6_TX_OUT |
        SIUL2_0_PORT218_CAN7_CAN7_TX_OUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT7_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_TRGMUX_TRGMUX_OUT3_OUT |
        SIUL2_0_PORT1_TRGMUX_TRGMUX_OUT0_OUT |
        SIUL2_0_PORT2_LPSPI5_LPSPI5_SIN_OUT |
        SIUL2_0_PORT3_LPSPI5_LPSPI5_SCK_OUT |
        SIUL2_0_PORT4_JTAG_JTAG_TMSSWD_DIO_OUT |
        SIUL2_0_PORT5_SYSTEM_RESET_B_IN |
        SIUL2_0_PORT5_SYSTEM_RESET_B_OUT |
        SIUL2_0_PORT9_CMP2_CMP2_OUT_OUT |
        SIUL2_0_PORT10_JTAG_TRACENOETM_JTAG_TDO_TRACENOETM_SWO_OUT |
        SIUL2_0_PORT11_LPSPI2_LPSPI2_SCK_OUT |
        SIUL2_0_PORT12_CMP1_CMP1_OUT_OUT |
        SIUL2_0_PORT13_LPUART11_LPUART11_TX_OUT |
        SIUL2_0_PORT14_LPSPI5_LPSPI5_PCS1_OUT |
        SIUL2_0_PORT15_FXIO_FXIO_D31_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_FXIO_FXIO_D30_OUT |
        SIUL2_0_PORT17_FXIO_FXIO_D19_OUT |
        SIUL2_0_PORT26_GMAC0_GMAC0_PPS0_OUT |
        SIUL2_0_PORT30_GMAC1_GMAC1_MII_RMII_RGMII_MDC_OUT |
        SIUL2_0_PORT31_TRGMUX_TRGMUX_OUT8_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_HSE_HSE_TAMPER_LOOP_OUT0_OUT |
        SIUL2_0_PORT33_LCU1_LCU1_OUT4_OUT |
        SIUL2_0_PORT34_FXIO_FXIO_D18_OUT |
        SIUL2_0_PORT35_FXIO_FXIO_D17_OUT |
        SIUL2_0_PORT36_SAI0_SAI0_D1_OUT |
        SIUL2_0_PORT37_GMAC0_GMAC0_MII_RMII_RGMII_MDC_OUT |
        SIUL2_0_PORT40_FXIO_FXIO_D29_OUT |
        SIUL2_0_PORT41_FXIO_FXIO_D28_OUT |
        SIUL2_0_PORT42_FXIO_FXIO_D27_OUT |
        SIUL2_0_PORT43_FXIO_FXIO_D26_OUT |
        SIUL2_0_PORT44_FXIO_FXIO_D25_OUT |
        SIUL2_0_PORT45_FXIO_FXIO_D24_OUT |
        SIUL2_0_PORT46_FXIO_FXIO_D23_OUT |
        SIUL2_0_PORT47_FXIO_FXIO_D22_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_FXIO_FXIO_D21_OUT |
        SIUL2_0_PORT49_FXIO_FXIO_D20_OUT |
        SIUL2_0_PORT50_TRGMUX_TRGMUX_OUT9_OUT |
        SIUL2_0_PORT51_TRGMUX_TRGMUX_OUT10_OUT |
        SIUL2_0_PORT52_TRGMUX_TRGMUX_OUT11_OUT |
        SIUL2_0_PORT53_TRGMUX_TRGMUX_OUT12_OUT |
        SIUL2_0_PORT54_TRGMUX_TRGMUX_OUT13_OUT |
        SIUL2_0_PORT55_TRGMUX_TRGMUX_OUT14_OUT |
        SIUL2_0_PORT60_GMAC0_GMAC0_PPS3_OUT |
        SIUL2_0_PORT61_SAI0_SAI0_D1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC0_GMAC0_MII_RMII_TX_CLK_OUT |
        SIUL2_0_PORT65_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_OUT |
        SIUL2_0_PORT66_QUADSPI_QUADSPI_IOFA3_OUT |
        SIUL2_0_PORT67_GMAC1_GMAC1_MII_RMII_TX_EN_OUT |
        SIUL2_0_PORT70_ADC0_ADC0_MA_2_OUT |
        SIUL2_0_PORT71_CAN2_CAN2_TX_OUT |
        SIUL2_0_PORT72_FXIO_FXIO_D12_OUT |
        SIUL2_0_PORT73_FXIO_FXIO_D13_OUT |
        SIUL2_0_PORT74_EMIOS_1_EMIOS_1_CH_0_X_OUT |
        SIUL2_0_PORT75_LCU1_LCU1_OUT10_OUT |
        SIUL2_0_PORT76_SAI0_SAI0_BCLK_OUT |
        SIUL2_0_PORT77_SAI0_SAI0_SYNC_OUT |
        SIUL2_0_PORT78_FXIO_FXIO_D16_OUT |
        SIUL2_0_PORT79_LPI2C1_LPI2C1_SCL_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPI2C1_LPI2C1_SDA_OUT |
        SIUL2_0_PORT81_FXIO_FXIO_D2_OUT |
        SIUL2_0_PORT82_SAI0_SAI0_D2_OUT |
        SIUL2_0_PORT83_SAI0_SAI0_D3_OUT |
        SIUL2_0_PORT84_GMAC0_GMAC0_PPS0_OUT |
        SIUL2_0_PORT85_CAN6_CAN6_TX_OUT |
        SIUL2_0_PORT88_TRGMUX_TRGMUX_OUT15_OUT |
        SIUL2_0_PORT90_LPSPI4_LPSPI4_SIN_OUT |
        SIUL2_0_PORT91_LPSPI4_LPSPI4_SCK_OUT |
        SIUL2_0_PORT93_FXIO_FXIO_D3_OUT |
        SIUL2_0_PORT94_FXIO_FXIO_D23_OUT |
        SIUL2_0_PORT95_FXIO_FXIO_D24_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_TRGMUX_TRGMUX_OUT1_OUT |
        SIUL2_0_PORT97_TRGMUX_TRGMUX_OUT2_OUT |
        SIUL2_0_PORT98_LPSPI5_LPSPI5_SOUT_OUT |
        SIUL2_0_PORT100_LPSPI5_LPSPI5_PCS0_OUT |
        SIUL2_0_PORT101_LPSPI0_LPSPI0_PCS1_OUT |
        SIUL2_0_PORT102_LPSPI0_LPSPI0_PCS0_OUT |
        SIUL2_0_PORT103_QUADSPI_QUADSPI_IOFA1_OUT |
        SIUL2_0_PORT104_FXIO_FXIO_D11_OUT |
        SIUL2_0_PORT105_FXIO_FXIO_D10_OUT |
        SIUL2_0_PORT106_QUADSPI_QUADSPI_SCKFA_OUT |
        SIUL2_0_PORT107_QUADSPI_QUADSPI_IOFA0_OUT |
        SIUL2_0_PORT108_QUADSPI_QUADSPI_IOFA2_OUT |
        SIUL2_0_PORT110_SYSTEM_CLKOUT_RUN_OUT |
        SIUL2_0_PORT111_FXIO_FXIO_D10_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPUART8_LPUART8_TX_OUT |
        SIUL2_0_PORT113_GMAC0_GMAC0_PPS2_OUT |
        SIUL2_0_PORT122_LCU0_LCU0_OUT0_OUT |
        SIUL2_0_PORT123_LCU0_LCU0_OUT1_OUT |
        SIUL2_0_PORT124_CAN6_CAN6_TX_OUT |
        SIUL2_0_PORT126_CAN7_CAN7_TX_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT130_ADC0_ADC0_MA_0_OUT |
        SIUL2_0_PORT131_CMP0_CMP0_OUT_OUT |
        SIUL2_0_PORT134_ADC0_ADC0_MA_1_OUT |
        SIUL2_0_PORT135_FXIO_FXIO_D11_OUT |
        SIUL2_0_PORT136_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT137_FXIO_FXIO_D11_OUT |
        SIUL2_0_PORT138_TRGMUX_TRGMUX_OUT4_OUT |
        SIUL2_0_PORT139_TRGMUX_TRGMUX_OUT5_OUT |
        SIUL2_0_PORT140_FXIO_FXIO_D7_OUT |
        SIUL2_0_PORT142_GMAC0_GMAC0_PPS1_OUT |
        SIUL2_0_PORT143_TRGMUX_TRGMUX_OUT6_OUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_TRGMUX_TRGMUX_OUT7_OUT |
        SIUL2_0_PORT152_FXIO_FXIO_D11_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191
        SIUL2_0_PORT180_FXIO_FXIO_D4_OUT |
        SIUL2_0_PORT181_FXIO_FXIO_D5_OUT |
        SIUL2_0_PORT185_FXIO_FXIO_D6_OUT |
        SIUL2_0_PORT188_TRACE_TRACE_ETM_D5_OUT |
        SIUL2_0_PORT189_FXIO_FXIO_D8_OUT |
        SIUL2_0_PORT191_TRACE_TRACE_ETM_D3_OUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT198_TRACE_TRACE_ETM_CLKOUT_OUT |
        SIUL2_0_PORT199_TRACE_TRACE_ETM_D0_OUT |
        SIUL2_0_PORT207_TRACE_TRACE_ETM_D1_OUT */
        (uint16)( SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_TRACE_TRACE_ETM_D2_OUT |
        SIUL2_0_PORT209_TRACE_TRACE_ETM_D4_OUT |
        SIUL2_0_PORT210_TRACE_TRACE_ETM_D6_OUT |
        SIUL2_0_PORT211_TRACE_TRACE_ETM_D7_OUT |
        SIUL2_0_PORT212_TRACE_TRACE_ETM_D8_OUT |
        SIUL2_0_PORT213_TRACE_TRACE_ETM_D9_OUT |
        SIUL2_0_PORT214_TRACE_TRACE_ETM_D10_OUT |
        SIUL2_0_PORT215_TRACE_TRACE_ETM_D11_OUT |
        SIUL2_0_PORT216_TRACE_TRACE_ETM_D12_OUT |
        SIUL2_0_PORT217_TRACE_TRACE_ETM_D13_OUT |
        SIUL2_0_PORT218_TRACE_TRACE_ETM_D14_OUT |
        SIUL2_0_PORT219_TRACE_TRACE_ETM_D15_OUT |
        SIUL2_0_PORT220_TRACE_TRACE_ETM_D0_OUT |
        SIUL2_0_PORT221_TRACE_TRACE_ETM_D1_OUT |
        SIUL2_0_PORT222_TRACE_TRACE_ETM_D2_OUT |
        SIUL2_0_PORT223_TRACE_TRACE_ETM_D3_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_TRACE_TRACE_ETM_D4_OUT |
        SIUL2_0_PORT225_TRACE_TRACE_ETM_D5_OUT |
        SIUL2_0_PORT226_TRACE_TRACE_ETM_D6_OUT |
        SIUL2_0_PORT227_TRACE_TRACE_ETM_D7_OUT |
        SIUL2_0_PORT228_TRACE_TRACE_ETM_CLKOUT_OUT |
        SIUL2_0_PORT229_TRACE_TRACE_ETM_D8_OUT |
        SIUL2_0_PORT230_TRACE_TRACE_ETM_D9_OUT |
        SIUL2_0_PORT231_TRACE_TRACE_ETM_D10_OUT |
        SIUL2_0_PORT232_TRACE_TRACE_ETM_D11_OUT |
        SIUL2_0_PORT233_TRACE_TRACE_ETM_D12_OUT |
        SIUL2_0_PORT234_TRACE_TRACE_ETM_D13_OUT |
        SIUL2_0_PORT235_TRACE_TRACE_ETM_D14_OUT |
        SIUL2_0_PORT236_TRACE_TRACE_ETM_D15_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT8_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31
        SIUL2_0_PORT28_GMAC1_GMAC1_MII_RMII_RGMII_MDC_OUT |
        SIUL2_0_PORT29_GMAC1_GMAC1_MII_RMII_RGMII_MDIO_OUT |
        SIUL2_0_PORT31_GMAC1_GMAC1_PPS0_OUT */
        (uint16)( SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC0_GMAC0_MII_RGMII_TXD3_OUT |
        SIUL2_0_PORT47_PGO_EXTWAKE_OUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT51_GMAC1_GMAC1_MII_RMII_RGMII_MDIO_OUT |
        SIUL2_0_PORT52_GMAC1_GMAC1_PPS2_OUT |
        SIUL2_0_PORT54_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_OUT |
        SIUL2_0_PORT55_GMAC0_GMAC0_MII_RGMII_RXD2_OUT |
        SIUL2_0_PORT60_GMAC0_GMAC0_MII_RGMII_TXD3_OUT |
        SIUL2_0_PORT61_GMAC0_GMAC0_MII_RMII_RGMII_TXD_1_OUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC1_GMAC1_MII_RGMII_TXD2_OUT |
        SIUL2_0_PORT65_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_OUT |
        SIUL2_0_PORT66_GMAC1_GMAC1_MII_RGMII_RXD3_OUT |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_OUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT81_GMAC1_GMAC1_MII_RMII_RGMII_TXD_1_OUT |
        SIUL2_0_PORT82_GMAC0_GMAC0_MII_RGMII_TXD2_OUT |
        SIUL2_0_PORT83_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_OUT |
        SIUL2_0_PORT91_LPUART13_LPUART13_TX_OUT |
        SIUL2_0_PORT92_LPUART0_LPUART0_TX_OUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT103_GMAC1_GMAC1_MII_RGMII_RXD2_OUT |
        SIUL2_0_PORT104_GMAC1_GMAC1_MII_RMII_RGMII_TXD_0_OUT |
        SIUL2_0_PORT105_GMAC1_GMAC1_MII_RGMII_TXD3_OUT |
        SIUL2_0_PORT106_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_OUT |
        SIUL2_0_PORT107_GMAC1_GMAC1_RGMII_TXCTL_OUT |
        SIUL2_0_PORT108_GMAC1_GMAC1_MII_RMII_RGMII_RXD_1_OUT */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143
        SIUL2_0_PORT131_GMAC1_GMAC1_PPS3_OUT |
        SIUL2_0_PORT142_GMAC1_GMAC1_PPS1_OUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT152_LPSPI2_LPSPI2_SIN_OUT |
        SIUL2_0_PORT155_EMIOS_0_EMIOS_0_CH_10_H_OUT |
        SIUL2_0_PORT156_EMIOS_0_EMIOS_0_CH_11_H_OUT |
        SIUL2_0_PORT157_EMIOS_0_EMIOS_0_CH_12_H_OUT */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207
        SIUL2_0_PORT200_EMIOS_0_EMIOS_0_CH_13_H_OUT |
        SIUL2_0_PORT202_EMIOS_0_EMIOS_0_CH_14_H_OUT |
        SIUL2_0_PORT203_EMIOS_0_EMIOS_0_CH_15_H_OUT |
        SIUL2_0_PORT204_EMIOS_0_EMIOS_0_CH_16_X_OUT |
        SIUL2_0_PORT205_EMIOS_0_EMIOS_0_CH_17_Y_OUT |
        SIUL2_0_PORT206_EMIOS_0_EMIOS_0_CH_18_Y_OUT */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT215_LPSPI5_LPSPI5_PCS0_OUT */
        (uint16)( SHL_PAD_U32(7U)
                ),
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT9_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_OUT */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT61_GMAC0_GMAC0_MII_RGMII_TXD2_OUT */
        (uint16)( SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95
        SIUL2_0_PORT83_GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_OUT */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT10_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_OUT */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT11_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79
        SIUL2_0_PORT64_TRACE_TRACE_ETM_D0_OUT */
        (uint16)( SHL_PAD_U32(0U)
                ),
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT101_SAI0_SAI0_D3_OUT */
        (uint16)( SHL_PAD_U32(5U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT12_FUNC_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT8_PGO_EXTWAKE_OUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79
        SIUL2_0_PORT65_TRACE_TRACE_ETM_CLKOUT_OUT */
        (uint16)( SHL_PAD_U32(1U)
                ),
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT104_TRACE_TRACE_ETM_D2_OUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT13_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95
        SIUL2_0_PORT81_TRACE_TRACE_ETM_D3_OUT */
        (uint16)( SHL_PAD_U32(1U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT102_SAI0_SAI0_D2_OUT */
        (uint16)( SHL_PAD_U32(6U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT14_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT102_GMAC1_GMAC1_MII_RMII_RGMII_RXD_0_OUT */
        (uint16)( SHL_PAD_U32(6U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ALT15_FUNC_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63
        SIUL2_0_PORT56_GMAC0_GMAC0_MII_RGMII_RXD3_OUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT105_TRACE_TRACE_ETM_D1_OUT */
        (uint16)( SHL_PAD_U32(9U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ANALOG_INPUT_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_ADC0_ADC0_S8_IN |
        SIUL2_0_PORT1_ADC0_ADC0_S9_IN |
        SIUL2_0_PORT2_ADC1_ADC1_X_0_IN |
        SIUL2_0_PORT3_ADC1_ADC1_S17_IN |
        SIUL2_0_PORT4_ADC1_ADC1_S15_IN |
        SIUL2_0_PORT6_ADC0_ADC0_S18_IN |
        SIUL2_0_PORT7_ADC0_ADC0_S11_IN |
        SIUL2_0_PORT8_ADC0_ADC0_P2_IN |
        SIUL2_0_PORT9_ADC0_ADC0_P7_IN |
        SIUL2_0_PORT11_ADC1_ADC1_S10_IN |
        SIUL2_0_PORT12_ADC1_ADC1_P0_IN |
        SIUL2_0_PORT13_ADC1_ADC1_P1_IN |
        SIUL2_0_PORT14_ADC1_ADC1_P4_IN |
        SIUL2_0_PORT15_ADC1_ADC1_P7_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_ADC1_ADC1_S13_IN |
        SIUL2_0_PORT17_ADC2_ADC2_S19_IN |
        SIUL2_0_PORT18_ADC2_ADC2_P0_IN |
        SIUL2_0_PORT19_ADC2_ADC2_P1_IN |
        SIUL2_0_PORT20_ADC2_ADC2_P2_IN |
        SIUL2_0_PORT21_ADC2_ADC2_S12_IN |
        SIUL2_0_PORT23_ADC1_ADC1_S19_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_ADC1_ADC1_S14_IN |
        SIUL2_0_PORT32_ADC0_ADC0_S14_IN |
        SIUL2_0_PORT33_ADC1_ADC1_S15_IN |
        SIUL2_0_PORT33_ADC0_ADC0_S15_IN |
        SIUL2_0_PORT40_ADC0_ADC0_X_0_IN |
        SIUL2_0_PORT41_ADC0_ADC0_X_1_IN |
        SIUL2_0_PORT42_ADC0_ADC0_X_2_IN |
        SIUL2_0_PORT43_ADC0_ADC0_X_3_IN |
        SIUL2_0_PORT44_ADC1_ADC1_X_1_IN |
        SIUL2_0_PORT45_ADC0_ADC0_S8_IN |
        SIUL2_0_PORT45_ADC1_ADC1_S8_IN |
        SIUL2_0_PORT45_ADC2_ADC2_S8_IN |
        SIUL2_0_PORT46_ADC0_ADC0_S9_IN |
        SIUL2_0_PORT46_ADC1_ADC1_S9_IN |
        SIUL2_0_PORT46_ADC2_ADC2_S9_IN |
        SIUL2_0_PORT47_ADC1_ADC1_S11_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_ADC1_ADC1_S12_IN |
        SIUL2_0_PORT49_ADC1_ADC1_X_2_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT69_ADC1_ADC1_S14_IN |
        SIUL2_0_PORT70_ADC1_ADC1_S18_IN |
        SIUL2_0_PORT71_ADC1_ADC1_S16_IN |
        SIUL2_0_PORT72_ADC0_ADC0_S12_IN |
        SIUL2_0_PORT73_ADC0_ADC0_S13_IN |
        SIUL2_0_PORT74_ADC1_ADC1_X_3_IN |
        SIUL2_0_PORT75_ADC0_ADC0_S17_IN */
        (uint16)( SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT87_ADC2_ADC2_S23_IN |
        SIUL2_0_PORT88_ADC2_ADC2_S22_IN |
        SIUL2_0_PORT89_ADC0_ADC0_S20_IN |
        SIUL2_0_PORT90_ADC0_ADC0_S21_IN |
        SIUL2_0_PORT95_ADC2_ADC2_S21_IN */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_ADC0_ADC0_P1_IN |
        SIUL2_0_PORT97_ADC0_ADC0_P0_IN |
        SIUL2_0_PORT98_ADC0_ADC0_S16_IN |
        SIUL2_0_PORT99_ADC0_ADC0_S10_IN |
        SIUL2_0_PORT100_ADC0_ADC0_S19_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT116_ADC0_ADC0_S22_IN |
        SIUL2_0_PORT117_ADC0_ADC0_S23_IN |
        SIUL2_0_PORT118_ADC2_ADC2_S18_IN |
        SIUL2_0_PORT119_ADC2_ADC2_S17_IN |
        SIUL2_0_PORT120_ADC1_ADC1_S20_IN |
        SIUL2_0_PORT122_ADC2_ADC2_S16_IN |
        SIUL2_0_PORT123_ADC1_ADC1_S21_IN |
        SIUL2_0_PORT124_ADC1_ADC1_S22_IN |
        SIUL2_0_PORT125_ADC1_ADC1_S23_IN |
        SIUL2_0_PORT126_ADC2_ADC2_S15_IN |
        SIUL2_0_PORT127_ADC2_ADC2_S14_IN */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_ADC1_ADC1_P2_IN |
        SIUL2_0_PORT129_ADC1_ADC1_P3_IN |
        SIUL2_0_PORT130_ADC1_ADC1_P5_IN |
        SIUL2_0_PORT132_ADC2_ADC2_S9_IN |
        SIUL2_0_PORT133_ADC2_ADC2_S8_IN |
        SIUL2_0_PORT134_ADC1_ADC1_P6_IN |
        SIUL2_0_PORT135_ADC2_ADC2_S20_IN |
        SIUL2_0_PORT138_ADC0_ADC0_P5_IN |
        SIUL2_0_PORT139_ADC0_ADC0_P6_IN |
        SIUL2_0_PORT143_ADC0_ADC0_P3_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_ADC0_ADC0_P4_IN |
        SIUL2_0_PORT145_ADC2_ADC2_S10_IN |
        SIUL2_0_PORT145_ADC1_ADC1_S22_IN |
        SIUL2_0_PORT146_ADC2_ADC2_S11_IN |
        SIUL2_0_PORT146_ADC1_ADC1_S23_IN |
        SIUL2_0_PORT149_ADC2_ADC2_P3_IN |
        SIUL2_0_PORT150_ADC2_ADC2_P4_IN |
        SIUL2_0_PORT151_ADC2_ADC2_P5_IN |
        SIUL2_0_PORT152_ADC2_ADC2_S13_IN |
        SIUL2_0_PORT153_ADC2_ADC2_P7_IN |
        SIUL2_0_PORT154_ADC2_ADC2_P6_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ONLY_OUTPUT_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31
        SIUL2_0_PORT24_OSC32K_OSC32K_XTAL_OUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_ONLY_INPUT_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_CMP1_CMP1_IN0_IN |
        SIUL2_0_PORT1_CMP1_CMP1_IN1_IN |
        SIUL2_0_PORT1_WKPU_WKPU_5_IN |
        SIUL2_0_PORT2_WKPU_WKPU_0_IN |
        SIUL2_0_PORT2_CMP1_CMP1_IN2_IN |
        SIUL2_0_PORT6_WKPU_WKPU_15_IN |
        SIUL2_0_PORT8_WKPU_WKPU_23_IN |
        SIUL2_0_PORT9_WKPU_WKPU_21_IN |
        SIUL2_0_PORT13_WKPU_WKPU_4_IN |
        SIUL2_0_PORT15_WKPU_WKPU_20_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_WKPU_WKPU_31_IN |
        SIUL2_0_PORT20_WKPU_WKPU_59_IN |
        SIUL2_0_PORT25_OSC32K_OSC32K_EXTAL_IN |
        SIUL2_0_PORT25_WKPU_WKPU_34_IN |
        SIUL2_0_PORT26_WKPU_WKPU_35_IN |
        SIUL2_0_PORT30_WKPU_WKPU_37_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_WKPU_WKPU_7_IN |
        SIUL2_0_PORT34_WKPU_WKPU_8_IN |
        SIUL2_0_PORT40_CMP2_CMP2_IN3_IN |
        SIUL2_0_PORT40_WKPU_WKPU_25_IN |
        SIUL2_0_PORT41_CMP2_CMP2_IN2_IN |
        SIUL2_0_PORT41_WKPU_WKPU_17_IN |
        SIUL2_0_PORT42_CMP2_CMP2_IN1_IN |
        SIUL2_0_PORT43_CMP2_CMP2_IN0_IN |
        SIUL2_0_PORT43_WKPU_WKPU_16_IN |
        SIUL2_0_PORT44_WKPU_WKPU_12_IN |
        SIUL2_0_PORT45_WKPU_WKPU_11_IN |
        SIUL2_0_PORT47_WKPU_WKPU_33_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_WKPU_WKPU_13_IN |
        SIUL2_0_PORT49_WKPU_WKPU_14_IN |
        SIUL2_0_PORT51_WKPU_WKPU_38_IN |
        SIUL2_0_PORT53_WKPU_WKPU_39_IN |
        SIUL2_0_PORT55_WKPU_WKPU_40_IN |
        SIUL2_0_PORT58_WKPU_WKPU_41_IN |
        SIUL2_0_PORT60_WKPU_WKPU_42_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT66_CMP0_CMP0_IN2_IN |
        SIUL2_0_PORT67_CMP0_CMP0_IN4_IN |
        SIUL2_0_PORT68_CMP1_CMP1_IN3_IN |
        SIUL2_0_PORT70_WKPU_WKPU_3_IN |
        SIUL2_0_PORT71_WKPU_WKPU_2_IN |
        SIUL2_0_PORT73_WKPU_WKPU_10_IN |
        SIUL2_0_PORT75_WKPU_WKPU_18_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT82_WKPU_WKPU_36_IN |
        SIUL2_0_PORT84_WKPU_WKPU_43_IN |
        SIUL2_0_PORT87_WKPU_WKPU_44_IN |
        SIUL2_0_PORT88_WKPU_WKPU_46_IN |
        SIUL2_0_PORT89_WKPU_WKPU_45_IN |
        SIUL2_0_PORT90_WKPU_WKPU_48_IN |
        SIUL2_0_PORT93_WKPU_WKPU_47_IN |
        SIUL2_0_PORT95_WKPU_WKPU_49_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_WKPU_WKPU_6_IN |
        SIUL2_0_PORT98_WKPU_WKPU_9_IN |
        SIUL2_0_PORT99_SYSTEM_NMI_B_IN |
        SIUL2_0_PORT99_WKPU_WKPU_1_IN |
        SIUL2_0_PORT100_WKPU_WKPU_22_IN |
        SIUL2_0_PORT102_CMP0_CMP0_IN7_IN |
        SIUL2_0_PORT103_CMP0_CMP0_IN6_IN |
        SIUL2_0_PORT109_WKPU_WKPU_24_IN |
        SIUL2_0_PORT111_CMP0_CMP0_IN1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_CMP0_CMP0_IN5_IN |
        SIUL2_0_PORT116_WKPU_WKPU_54_IN |
        SIUL2_0_PORT119_WKPU_WKPU_50_IN |
        SIUL2_0_PORT123_WKPU_WKPU_51_IN |
        SIUL2_0_PORT125_WKPU_WKPU_52_IN |
        SIUL2_0_PORT127_WKPU_WKPU_53_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_WKPU_WKPU_26_IN |
        SIUL2_0_PORT130_WKPU_WKPU_27_IN |
        SIUL2_0_PORT133_WKPU_WKPU_32_IN |
        SIUL2_0_PORT134_WKPU_WKPU_29_IN |
        SIUL2_0_PORT136_CMP0_CMP0_IN3_IN |
        SIUL2_0_PORT137_CMP0_CMP0_IN0_IN |
        SIUL2_0_PORT139_WKPU_WKPU_28_IN |
        SIUL2_0_PORT142_WKPU_WKPU_30_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_WKPU_WKPU_19_IN |
        SIUL2_0_PORT146_WKPU_WKPU_55_IN |
        SIUL2_0_PORT149_WKPU_WKPU_56_IN |
        SIUL2_0_PORT151_WKPU_WKPU_57_IN |
        SIUL2_0_PORT153_WKPU_WKPU_58_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223
        SIUL2_0_PORT217_WKPU_WKPU_45_IN */
        (uint16)( SHL_PAD_U32(9U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT225_WKPU_WKPU_0_IN |
        SIUL2_0_PORT227_WKPU_WKPU_15_IN |
        SIUL2_0_PORT229_WKPU_WKPU_14_IN |
        SIUL2_0_PORT231_WKPU_WKPU_8_IN |
        SIUL2_0_PORT233_WKPU_WKPU_27_IN |
        SIUL2_0_PORT235_WKPU_WKPU_18_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT1_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_SIUL_EIRQ_0_IN |
        SIUL2_0_PORT1_SIUL_EIRQ_1_IN |
        SIUL2_0_PORT2_SIUL_EIRQ_2_IN |
        SIUL2_0_PORT3_SIUL_EIRQ_3_IN |
        SIUL2_0_PORT4_SIUL_EIRQ_4_IN |
        SIUL2_0_PORT5_SIUL_EIRQ_5_IN |
        SIUL2_0_PORT6_CAN0_CAN0_RX_IN |
        SIUL2_0_PORT7_SIUL_EIRQ_7_IN |
        SIUL2_0_PORT8_SIUL_EIRQ_16_IN |
        SIUL2_0_PORT9_SIUL_EIRQ_17_IN |
        SIUL2_0_PORT10_SIUL_EIRQ_18_IN |
        SIUL2_0_PORT11_SIUL_EIRQ_19_IN |
        SIUL2_0_PORT12_CAN1_CAN1_RX_IN |
        SIUL2_0_PORT13_SIUL_EIRQ_21_IN |
        SIUL2_0_PORT14_SIUL_EIRQ_22_IN |
        SIUL2_0_PORT15_SIUL_EIRQ_23_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_SIUL_EIRQ_4_IN |
        SIUL2_0_PORT17_EMIOS_0_EMIOS_0_CH_6_G_IN |
        SIUL2_0_PORT18_SIUL_EIRQ_0_IN |
        SIUL2_0_PORT19_SIUL_EIRQ_1_IN |
        SIUL2_0_PORT20_SIUL_EIRQ_2_IN |
        SIUL2_0_PORT21_SIUL_EIRQ_3_IN |
        SIUL2_0_PORT22_CAN1_CAN1_RX_IN |
        SIUL2_0_PORT23_EMIOS_1_EMIOS_1_CH_6_H_IN |
        SIUL2_0_PORT24_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT25_SIUL_EIRQ_5_IN |
        SIUL2_0_PORT26_EMIOS_1_EMIOS_1_CH_9_H_IN |
        SIUL2_0_PORT27_EMIOS_1_EMIOS_1_CH_10_H_IN |
        SIUL2_0_PORT28_CAN0_CAN0_RX_IN |
        SIUL2_0_PORT29_EMIOS_1_EMIOS_1_CH_12_H_IN |
        SIUL2_0_PORT30_SIUL_EIRQ_7_IN |
        SIUL2_0_PORT31_EMIOS_1_EMIOS_1_CH_14_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_CAN0_CAN0_RX_IN |
        SIUL2_0_PORT33_SIUL_EIRQ_9_IN |
        SIUL2_0_PORT34_CAN4_CAN4_RX_IN |
        SIUL2_0_PORT35_SIUL_EIRQ_11_IN |
        SIUL2_0_PORT36_SIUL_EIRQ_12_IN |
        SIUL2_0_PORT37_SIUL_EIRQ_13_IN |
        SIUL2_0_PORT40_SIUL_EIRQ_14_IN |
        SIUL2_0_PORT41_SIUL_EIRQ_15_IN |
        SIUL2_0_PORT42_SIUL_EIRQ_24_IN |
        SIUL2_0_PORT43_SIUL_EIRQ_25_IN |
        SIUL2_0_PORT44_SIUL_EIRQ_26_IN |
        SIUL2_0_PORT45_SIUL_EIRQ_27_IN |
        SIUL2_0_PORT46_SIUL_EIRQ_28_IN |
        SIUL2_0_PORT47_SIUL_EIRQ_29_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_SIUL_EIRQ_30_IN |
        SIUL2_0_PORT49_SIUL_EIRQ_31_IN |
        SIUL2_0_PORT50_EMIOS_1_EMIOS_1_CH_15_H_IN |
        SIUL2_0_PORT51_EMIOS_1_EMIOS_1_CH_15_H_IN |
        SIUL2_0_PORT52_EMIOS_1_EMIOS_1_CH_16_X_IN |
        SIUL2_0_PORT53_SIUL_EIRQ_8_IN |
        SIUL2_0_PORT54_SIUL_EIRQ_9_IN |
        SIUL2_0_PORT55_CAN1_CAN1_RX_IN |
        SIUL2_0_PORT56_SIUL_EIRQ_11_IN |
        SIUL2_0_PORT57_SIUL_EIRQ_12_IN |
        SIUL2_0_PORT58_SIUL_EIRQ_13_IN |
        SIUL2_0_PORT59_EMIOS_1_EMIOS_1_CH_23_X_IN |
        SIUL2_0_PORT60_SIUL_EIRQ_14_IN |
        SIUL2_0_PORT61_CAN4_CAN4_RX_IN |
        SIUL2_0_PORT62_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT63_SIUL_EIRQ_15_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_SIUL_EIRQ_0_IN |
        SIUL2_0_PORT65_CAN3_CAN3_RX_IN |
        SIUL2_0_PORT66_CAN0_CAN0_RX_IN |
        SIUL2_0_PORT67_SIUL_EIRQ_3_IN |
        SIUL2_0_PORT68_SIUL_EIRQ_4_IN |
        SIUL2_0_PORT69_SIUL_EIRQ_5_IN |
        SIUL2_0_PORT70_CAN2_CAN2_RX_IN |
        SIUL2_0_PORT71_SIUL_EIRQ_7_IN |
        SIUL2_0_PORT72_SIUL_EIRQ_16_IN |
        SIUL2_0_PORT73_CAN1_CAN1_RX_IN |
        SIUL2_0_PORT74_SIUL_EIRQ_18_IN |
        SIUL2_0_PORT75_CAN5_CAN5_RX_IN |
        SIUL2_0_PORT76_SIUL_EIRQ_20_IN |
        SIUL2_0_PORT77_SIUL_EIRQ_21_IN |
        SIUL2_0_PORT78_CAN2_CAN2_RX_IN |
        SIUL2_0_PORT79_SIUL_EIRQ_23_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_CAN2_CAN2_RX_IN |
        SIUL2_0_PORT81_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT82_EMIOS_2_EMIOS_2_CH_12_H_IN |
        SIUL2_0_PORT83_EMIOS_2_EMIOS_2_CH_13_H_IN |
        SIUL2_0_PORT84_SIUL_EIRQ_16_IN |
        SIUL2_0_PORT85_SIUL_EIRQ_17_IN |
        SIUL2_0_PORT86_EMIOS_0_EMIOS_0_CH_8_X_IN |
        SIUL2_0_PORT87_SIUL_EIRQ_18_IN |
        SIUL2_0_PORT88_SIUL_EIRQ_19_IN |
        SIUL2_0_PORT89_SIUL_EIRQ_20_IN |
        SIUL2_0_PORT90_CAN5_CAN5_RX_IN |
        SIUL2_0_PORT91_SIUL_EIRQ_22_IN |
        SIUL2_0_PORT92_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT93_CAN3_CAN3_RX_IN |
        SIUL2_0_PORT94_EMIOS_1_EMIOS_1_CH_12_H_IN |
        SIUL2_0_PORT95_CAN4_CAN4_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_SIUL_EIRQ_8_IN |
        SIUL2_0_PORT97_SIUL_EIRQ_9_IN |
        SIUL2_0_PORT98_SIUL_EIRQ_10_IN |
        SIUL2_0_PORT99_SIUL_EIRQ_11_IN |
        SIUL2_0_PORT100_SIUL_EIRQ_12_IN |
        SIUL2_0_PORT101_SIUL_EIRQ_13_IN |
        SIUL2_0_PORT102_SIUL_EIRQ_14_IN |
        SIUL2_0_PORT103_SIUL_EIRQ_15_IN |
        SIUL2_0_PORT104_SIUL_EIRQ_24_IN |
        SIUL2_0_PORT105_SIUL_EIRQ_25_IN |
        SIUL2_0_PORT106_SIUL_EIRQ_26_IN |
        SIUL2_0_PORT107_SIUL_EIRQ_27_IN |
        SIUL2_0_PORT108_SIUL_EIRQ_28_IN |
        SIUL2_0_PORT109_SIUL_EIRQ_29_IN |
        SIUL2_0_PORT110_SIUL_EIRQ_30_IN |
        SIUL2_0_PORT111_CAN3_CAN3_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_EMIOS_0_EMIOS_0_CH_1_G_IN |
        SIUL2_0_PORT113_CAN5_CAN5_RX_IN |
        SIUL2_0_PORT114_EMIOS_1_EMIOS_1_CH_15_H_IN |
        SIUL2_0_PORT115_CAN2_CAN2_RX_IN |
        SIUL2_0_PORT116_SIUL_EIRQ_25_IN |
        SIUL2_0_PORT117_SIUL_EIRQ_26_IN |
        SIUL2_0_PORT118_SIUL_EIRQ_27_IN |
        SIUL2_0_PORT119_SIUL_EIRQ_28_IN |
        SIUL2_0_PORT120_SIUL_EIRQ_29_IN |
        SIUL2_0_PORT121_EMIOS_1_EMIOS_1_CH_22_X_IN |
        SIUL2_0_PORT122_EMIOS_1_EMIOS_1_CH_23_X_IN |
        SIUL2_0_PORT123_SIUL_EIRQ_30_IN |
        SIUL2_0_PORT124_SIUL_EIRQ_31_IN |
        SIUL2_0_PORT125_EMIOS_2_EMIOS_2_CH_8_X_IN |
        SIUL2_0_PORT126_EMIOS_2_EMIOS_2_CH_16_X_IN |
        SIUL2_0_PORT127_EMIOS_2_EMIOS_2_CH_22_X_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_SIUL_EIRQ_0_IN |
        SIUL2_0_PORT129_SIUL_EIRQ_1_IN |
        SIUL2_0_PORT130_SIUL_EIRQ_2_IN |
        SIUL2_0_PORT131_SIUL_EIRQ_3_IN |
        SIUL2_0_PORT132_SIUL_EIRQ_4_IN |
        SIUL2_0_PORT133_SIUL_EIRQ_5_IN |
        SIUL2_0_PORT134_SIUL_EIRQ_6_IN |
        SIUL2_0_PORT135_EMIOS_0_EMIOS_0_CH_7_G_IN |
        SIUL2_0_PORT136_SIUL_EIRQ_7_IN |
        SIUL2_0_PORT137_SIUL_EIRQ_8_IN |
        SIUL2_0_PORT138_SIUL_EIRQ_9_IN |
        SIUL2_0_PORT139_SIUL_EIRQ_10_IN |
        SIUL2_0_PORT140_SIUL_EIRQ_11_IN |
        SIUL2_0_PORT142_CAN4_CAN4_RX_IN |
        SIUL2_0_PORT143_SIUL_EIRQ_14_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_SIUL_EIRQ_15_IN |
        SIUL2_0_PORT145_EMIOS_2_EMIOS_2_CH_23_X_IN |
        SIUL2_0_PORT146_EMIOS_2_EMIOS_2_CH_17_Y_IN |
        SIUL2_0_PORT147_EMIOS_0_EMIOS_0_CH_22_X_IN |
        SIUL2_0_PORT148_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT149_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT150_EMIOS_1_EMIOS_1_CH_2_H_IN |
        SIUL2_0_PORT151_EMIOS_1_EMIOS_1_CH_3_H_IN |
        SIUL2_0_PORT152_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT153_CAN2_CAN2_RX_IN |
        SIUL2_0_PORT154_EMIOS_1_EMIOS_1_CH_6_H_IN |
        SIUL2_0_PORT155_EMIOS_0_EMIOS_0_CH_10_H_IN |
        SIUL2_0_PORT156_EMIOS_0_EMIOS_0_CH_11_H_IN |
        SIUL2_0_PORT157_CAN3_CAN3_RX_IN |
        SIUL2_0_PORT158_LPSPI0_LPSPI0_SOUT_IN |
        SIUL2_0_PORT159_CAN4_CAN4_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_SIUL_EIRQ_0_IN |
        SIUL2_0_PORT161_SIUL_EIRQ_1_IN |
        SIUL2_0_PORT162_SIUL_EIRQ_2_IN |
        SIUL2_0_PORT163_SIUL_EIRQ_3_IN |
        SIUL2_0_PORT164_SIUL_EIRQ_4_IN |
        SIUL2_0_PORT165_CAN5_CAN5_RX_IN |
        SIUL2_0_PORT166_SIUL_EIRQ_6_IN |
        SIUL2_0_PORT167_SIUL_EIRQ_7_IN |
        SIUL2_0_PORT168_SIUL_EIRQ_16_IN |
        SIUL2_0_PORT169_SIUL_EIRQ_17_IN |
        SIUL2_0_PORT170_SIUL_EIRQ_18_IN |
        SIUL2_0_PORT171_SIUL_EIRQ_19_IN |
        SIUL2_0_PORT172_SIUL_EIRQ_20_IN |
        SIUL2_0_PORT173_SIUL_EIRQ_21_IN |
        SIUL2_0_PORT174_SIUL_EIRQ_22_IN |
        SIUL2_0_PORT175_CAN1_CAN1_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT177_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT178_EMIOS_1_EMIOS_1_CH_2_H_IN |
        SIUL2_0_PORT179_EMIOS_1_EMIOS_1_CH_3_H_IN |
        SIUL2_0_PORT180_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT181_CAN0_CAN0_RX_IN |
        SIUL2_0_PORT182_EMIOS_1_EMIOS_1_CH_6_H_IN |
        SIUL2_0_PORT183_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT184_EMIOS_1_EMIOS_1_CH_8_X_IN |
        SIUL2_0_PORT185_EMIOS_1_EMIOS_1_CH_9_H_IN |
        SIUL2_0_PORT186_CAN2_CAN2_RX_IN |
        SIUL2_0_PORT187_EMIOS_1_EMIOS_1_CH_11_H_IN |
        SIUL2_0_PORT188_EMIOS_1_EMIOS_1_CH_12_H_IN |
        SIUL2_0_PORT189_EMIOS_1_EMIOS_1_CH_13_H_IN |
        SIUL2_0_PORT190_CAN3_CAN3_RX_IN |
        SIUL2_0_PORT191_EMIOS_1_EMIOS_1_CH_15_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_SIUL_EIRQ_8_IN |
        SIUL2_0_PORT193_SIUL_EIRQ_9_IN |
        SIUL2_0_PORT194_SIUL_EIRQ_10_IN |
        SIUL2_0_PORT195_SIUL_EIRQ_11_IN |
        SIUL2_0_PORT196_SIUL_EIRQ_12_IN |
        SIUL2_0_PORT197_SIUL_EIRQ_13_IN |
        SIUL2_0_PORT198_SIUL_EIRQ_14_IN |
        SIUL2_0_PORT199_SIUL_EIRQ_15_IN |
        SIUL2_0_PORT200_SIUL_EIRQ_24_IN |
        SIUL2_0_PORT201_CAN4_CAN4_RX_IN |
        SIUL2_0_PORT202_SIUL_EIRQ_26_IN |
        SIUL2_0_PORT203_SIUL_EIRQ_27_IN |
        SIUL2_0_PORT204_SIUL_EIRQ_28_IN |
        SIUL2_0_PORT205_SIUL_EIRQ_29_IN |
        SIUL2_0_PORT206_CAN5_CAN5_RX_IN |
        SIUL2_0_PORT207_SIUL_EIRQ_31_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_EMIOS_2_EMIOS_2_CH_16_X_IN |
        SIUL2_0_PORT209_EMIOS_2_EMIOS_2_CH_17_Y_IN |
        SIUL2_0_PORT210_EMIOS_2_EMIOS_2_CH_18_Y_IN |
        SIUL2_0_PORT211_EMIOS_2_EMIOS_2_CH_19_Y_IN |
        SIUL2_0_PORT212_EMIOS_2_EMIOS_2_CH_20_Y_IN |
        SIUL2_0_PORT213_EMIOS_2_EMIOS_2_CH_21_Y_IN |
        SIUL2_0_PORT214_EMIOS_2_EMIOS_2_CH_22_X_IN |
        SIUL2_0_PORT215_EMIOS_0_EMIOS_0_CH_0_X_IN |
        SIUL2_0_PORT216_EMIOS_0_EMIOS_0_CH_1_G_IN |
        SIUL2_0_PORT217_EMIOS_0_EMIOS_0_CH_2_G_IN |
        SIUL2_0_PORT218_EMIOS_0_EMIOS_0_CH_3_G_IN |
        SIUL2_0_PORT219_EMIOS_0_EMIOS_0_CH_4_G_IN |
        SIUL2_0_PORT220_EMIOS_0_EMIOS_0_CH_5_G_IN |
        SIUL2_0_PORT221_SIUL_EIRQ_29_IN |
        SIUL2_0_PORT222_SIUL_EIRQ_30_IN |
        SIUL2_0_PORT223_SIUL_EIRQ_31_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_SIUL_EIRQ_16_IN |
        SIUL2_0_PORT225_SIUL_EIRQ_17_IN |
        SIUL2_0_PORT226_SIUL_EIRQ_18_IN |
        SIUL2_0_PORT227_SIUL_EIRQ_19_IN |
        SIUL2_0_PORT228_SIUL_EIRQ_20_IN |
        SIUL2_0_PORT229_SIUL_EIRQ_21_IN |
        SIUL2_0_PORT230_SIUL_EIRQ_22_IN |
        SIUL2_0_PORT231_SIUL_EIRQ_23_IN |
        SIUL2_0_PORT232_SIUL_EIRQ_24_IN |
        SIUL2_0_PORT233_SIUL_EIRQ_25_IN |
        SIUL2_0_PORT234_SIUL_EIRQ_26_IN |
        SIUL2_0_PORT235_SIUL_EIRQ_27_IN |
        SIUL2_0_PORT236_SIUL_EIRQ_28_IN |
        SIUL2_0_PORT237_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT238_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT239_FXIO_FXIO_D2_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT240_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT241_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT242_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT243_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT244_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT245_EMIOS_2_EMIOS_2_CH_17_Y_IN |
        SIUL2_0_PORT246_EMIOS_2_EMIOS_2_CH_18_Y_IN |
        SIUL2_0_PORT248_EMIOS_0_EMIOS_0_CH_0_X_IN |
        SIUL2_0_PORT249_EMIOS_0_EMIOS_0_CH_1_G_IN |
        SIUL2_0_PORT250_EMIOS_0_EMIOS_0_CH_2_G_IN |
        SIUL2_0_PORT251_EMIOS_0_EMIOS_0_CH_3_G_IN |
        SIUL2_0_PORT252_EMIOS_0_EMIOS_0_CH_4_G_IN |
        SIUL2_0_PORT253_EMIOS_0_EMIOS_0_CH_5_G_IN |
        SIUL2_0_PORT254_EMIOS_0_EMIOS_0_CH_6_G_IN |
        SIUL2_0_PORT255_EMIOS_0_EMIOS_0_CH_7_G_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_EMIOS_2_EMIOS_2_CH_0_X_IN |
        SIUL2_0_PORT257_EMIOS_2_EMIOS_2_CH_1_H_IN |
        SIUL2_0_PORT258_FXIO_FXIO_D10_IN |
        SIUL2_0_PORT259_EMIOS_2_EMIOS_2_CH_3_H_IN |
        SIUL2_0_PORT260_EMIOS_2_EMIOS_2_CH_5_H_IN |
        SIUL2_0_PORT261_FXIO_FXIO_D13_IN |
        SIUL2_0_PORT262_EMIOS_2_EMIOS_2_CH_7_H_IN |
        SIUL2_0_PORT263_EMIOS_2_EMIOS_2_CH_8_X_IN |
        SIUL2_0_PORT264_EMIOS_2_EMIOS_2_CH_6_H_IN |
        SIUL2_0_PORT266_EMIOS_2_EMIOS_2_CH_4_H_IN |
        SIUL2_0_PORT268_EMIOS_0_EMIOS_0_CH_13_H_IN |
        SIUL2_0_PORT269_EMIOS_0_EMIOS_0_CH_8_X_IN |
        SIUL2_0_PORT270_EMIOS_0_EMIOS_0_CH_9_H_IN |
        SIUL2_0_PORT271_EMIOS_0_EMIOS_0_CH_10_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_EMIOS_0_EMIOS_0_CH_11_H_IN |
        SIUL2_0_PORT273_EMIOS_0_EMIOS_0_CH_12_H_IN |
        SIUL2_0_PORT274_EMIOS_0_EMIOS_0_CH_14_H_IN |
        SIUL2_0_PORT275_EMIOS_0_EMIOS_0_CH_15_H_IN |
        SIUL2_0_PORT276_EMIOS_0_EMIOS_0_CH_16_X_IN |
        SIUL2_0_PORT277_EMIOS_0_EMIOS_0_CH_17_Y_IN |
        SIUL2_0_PORT278_EMIOS_0_EMIOS_0_CH_18_Y_IN |
        SIUL2_0_PORT279_EMIOS_0_EMIOS_0_CH_19_Y_IN |
        SIUL2_0_PORT280_EMIOS_0_EMIOS_0_CH_20_Y_IN |
        SIUL2_0_PORT281_EMIOS_0_EMIOS_0_CH_21_Y_IN |
        SIUL2_0_PORT282_EMIOS_0_EMIOS_0_CH_22_X_IN |
        SIUL2_0_PORT283_EMIOS_0_EMIOS_0_CH_23_X_IN |
        SIUL2_0_PORT284_EMIOS_2_EMIOS_2_CH_9_H_IN |
        SIUL2_0_PORT285_EMIOS_2_EMIOS_2_CH_10_H_IN |
        SIUL2_0_PORT286_EMIOS_2_EMIOS_2_CH_11_H_IN |
        SIUL2_0_PORT287_EMIOS_2_EMIOS_2_CH_12_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT288_FXIO_FXIO_D16_IN |
        SIUL2_0_PORT289_EMIOS_2_EMIOS_2_CH_19_Y_IN |
        SIUL2_0_PORT290_EMIOS_2_EMIOS_2_CH_20_Y_IN |
        SIUL2_0_PORT291_EMIOS_2_EMIOS_2_CH_21_Y_IN |
        SIUL2_0_PORT292_EMIOS_2_EMIOS_2_CH_22_X_IN |
        SIUL2_0_PORT293_EMIOS_2_EMIOS_2_CH_23_X_IN |
        SIUL2_0_PORT294_EMIOS_2_EMIOS_2_CH_13_H_IN |
        SIUL2_0_PORT295_EMIOS_2_EMIOS_2_CH_14_H_IN |
        SIUL2_0_PORT296_EMIOS_2_EMIOS_2_CH_15_H_IN |
        SIUL2_0_PORT297_EMIOS_2_EMIOS_2_CH_16_X_IN |
        SIUL2_0_PORT298_EMIOS_2_EMIOS_2_CH_2_H_IN |
        SIUL2_0_PORT299_CAN9_CAN9_RX_IN |
        SIUL2_0_PORT300_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT301_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT302_EMIOS_1_EMIOS_1_CH_2_H_IN |
        SIUL2_0_PORT303_EMIOS_1_EMIOS_1_CH_3_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT305_EMIOS_1_EMIOS_1_CH_6_H_IN |
        SIUL2_0_PORT306_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT307_EMIOS_1_EMIOS_1_CH_8_X_IN |
        SIUL2_0_PORT308_EMIOS_1_EMIOS_1_CH_9_H_IN |
        SIUL2_0_PORT309_EMIOS_1_EMIOS_1_CH_10_H_IN |
        SIUL2_0_PORT310_EMIOS_1_EMIOS_1_CH_11_H_IN |
        SIUL2_0_PORT311_EMIOS_1_EMIOS_1_CH_12_H_IN |
        SIUL2_0_PORT312_EMIOS_1_EMIOS_1_CH_13_H_IN |
        SIUL2_0_PORT313_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT314_EMIOS_1_EMIOS_1_CH_14_H_IN |
        SIUL2_0_PORT315_EMIOS_1_EMIOS_1_CH_15_H_IN |
        SIUL2_0_PORT316_EMIOS_1_EMIOS_1_CH_16_X_IN |
        SIUL2_0_PORT317_EMIOS_1_EMIOS_1_CH_17_Y_IN |
        SIUL2_0_PORT318_EMIOS_1_EMIOS_1_CH_18_Y_IN |
        SIUL2_0_PORT319_EMIOS_1_EMIOS_1_CH_19_Y_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_EMIOS_1_EMIOS_1_CH_20_Y_IN |
        SIUL2_0_PORT321_EMIOS_1_EMIOS_1_CH_21_Y_IN |
        SIUL2_0_PORT322_EMIOS_1_EMIOS_1_CH_22_X_IN |
        SIUL2_0_PORT323_EMIOS_1_EMIOS_1_CH_23_X_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_INPUT2_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_EMIOS_0_EMIOS_0_CH_17_Y_IN |
        SIUL2_0_PORT1_EMIOS_0_EMIOS_0_CH_9_H_IN |
        SIUL2_0_PORT2_EMIOS_1_EMIOS_1_CH_19_Y_IN |
        SIUL2_0_PORT3_EMIOS_1_EMIOS_1_CH_20_Y_IN |
        SIUL2_0_PORT4_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT6_SIUL_EIRQ_6_IN |
        SIUL2_0_PORT7_EMIOS_1_EMIOS_1_CH_11_H_IN |
        SIUL2_0_PORT8_EMIOS_1_EMIOS_1_CH_12_H_IN |
        SIUL2_0_PORT9_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT10_EMIOS_0_EMIOS_0_CH_12_H_IN |
        SIUL2_0_PORT11_EMIOS_0_EMIOS_0_CH_13_H_IN |
        SIUL2_0_PORT12_SIUL_EIRQ_20_IN |
        SIUL2_0_PORT13_EMIOS_0_EMIOS_0_CH_15_H_IN |
        SIUL2_0_PORT14_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT15_EMIOS_0_EMIOS_0_CH_10_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_EMIOS_0_EMIOS_0_CH_11_H_IN |
        SIUL2_0_PORT17_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT18_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT19_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT20_EMIOS_1_EMIOS_1_CH_2_H_IN |
        SIUL2_0_PORT21_EMIOS_1_EMIOS_1_CH_3_H_IN |
        SIUL2_0_PORT22_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT23_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT24_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT25_EMIOS_1_EMIOS_1_CH_8_X_IN |
        SIUL2_0_PORT26_EMIOS_2_EMIOS_2_CH_9_H_IN |
        SIUL2_0_PORT27_EMIOS_2_EMIOS_2_CH_10_H_IN |
        SIUL2_0_PORT28_SIUL_EIRQ_6_IN |
        SIUL2_0_PORT29_EMIOS_2_EMIOS_2_CH_12_H_IN |
        SIUL2_0_PORT30_EMIOS_1_EMIOS_1_CH_13_H_IN |
        SIUL2_0_PORT31_GMAC0_GMAC0_PPS0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_SIUL_EIRQ_8_IN |
        SIUL2_0_PORT33_EMIOS_0_EMIOS_0_CH_7_G_IN |
        SIUL2_0_PORT34_SIUL_EIRQ_10_IN |
        SIUL2_0_PORT35_EMIOS_0_EMIOS_0_CH_9_H_IN |
        SIUL2_0_PORT36_EMIOS_0_EMIOS_0_CH_4_G_IN |
        SIUL2_0_PORT37_EMIOS_0_EMIOS_0_CH_5_G_IN |
        SIUL2_0_PORT40_EMIOS_1_EMIOS_1_CH_15_H_IN |
        SIUL2_0_PORT41_EMIOS_1_EMIOS_1_CH_16_X_IN |
        SIUL2_0_PORT42_EMIOS_1_EMIOS_1_CH_17_Y_IN |
        SIUL2_0_PORT43_EMIOS_1_EMIOS_1_CH_18_Y_IN |
        SIUL2_0_PORT44_EMIOS_0_EMIOS_0_CH_0_X_IN |
        SIUL2_0_PORT45_EMIOS_0_EMIOS_0_CH_1_G_IN |
        SIUL2_0_PORT46_EMIOS_0_EMIOS_0_CH_2_G_IN |
        SIUL2_0_PORT47_EMIOS_0_EMIOS_0_CH_3_G_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_EMIOS_0_EMIOS_0_CH_4_G_IN |
        SIUL2_0_PORT49_EMIOS_0_EMIOS_0_CH_5_G_IN |
        SIUL2_0_PORT50_EMIOS_2_EMIOS_2_CH_14_H_IN |
        SIUL2_0_PORT51_EMIOS_2_EMIOS_2_CH_15_H_IN |
        SIUL2_0_PORT52_EMIOS_2_EMIOS_2_CH_16_X_IN |
        SIUL2_0_PORT53_EMIOS_1_EMIOS_1_CH_17_Y_IN |
        SIUL2_0_PORT54_EMIOS_1_EMIOS_1_CH_18_Y_IN |
        SIUL2_0_PORT55_SIUL_EIRQ_10_IN |
        SIUL2_0_PORT56_EMIOS_1_EMIOS_1_CH_20_Y_IN |
        SIUL2_0_PORT57_EMIOS_1_EMIOS_1_CH_21_Y_IN |
        SIUL2_0_PORT58_EMIOS_1_EMIOS_1_CH_22_X_IN |
        SIUL2_0_PORT59_EMIOS_2_EMIOS_2_CH_23_X_IN |
        SIUL2_0_PORT60_EMIOS_2_EMIOS_2_CH_10_H_IN |
        SIUL2_0_PORT61_EMIOS_2_EMIOS_2_CH_11_H_IN |
        SIUL2_0_PORT63_EMIOS_0_EMIOS_0_CH_19_Y_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_EMIOS_0_EMIOS_0_CH_0_X_IN |
        SIUL2_0_PORT65_SIUL_EIRQ_1_IN |
        SIUL2_0_PORT66_SIUL_EIRQ_2_IN |
        SIUL2_0_PORT67_EMIOS_0_EMIOS_0_CH_3_G_IN |
        SIUL2_0_PORT68_EMIOS_0_EMIOS_0_CH_8_X_IN |
        SIUL2_0_PORT69_EMIOS_0_EMIOS_0_CH_16_X_IN |
        SIUL2_0_PORT70_SIUL_EIRQ_6_IN |
        SIUL2_0_PORT71_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT72_EMIOS_1_EMIOS_1_CH_9_H_IN |
        SIUL2_0_PORT73_SIUL_EIRQ_17_IN |
        SIUL2_0_PORT74_EMIOS_0_EMIOS_0_CH_6_G_IN |
        SIUL2_0_PORT75_SIUL_EIRQ_19_IN |
        SIUL2_0_PORT76_EMIOS_0_EMIOS_0_CH_22_X_IN |
        SIUL2_0_PORT77_EMIOS_0_EMIOS_0_CH_23_X_IN |
        SIUL2_0_PORT78_SIUL_EIRQ_22_IN |
        SIUL2_0_PORT79_EMIOS_0_EMIOS_0_CH_11_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_EMIOS_1_EMIOS_1_CH_9_H_IN |
        SIUL2_0_PORT81_FXIO_FXIO_D14_IN |
        SIUL2_0_PORT82_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT83_FXIO_FXIO_D13_IN |
        SIUL2_0_PORT84_EMIOS_2_EMIOS_2_CH_14_H_IN |
        SIUL2_0_PORT85_EMIOS_2_EMIOS_2_CH_15_H_IN |
        SIUL2_0_PORT87_FXIO_FXIO_D16_IN |
        SIUL2_0_PORT88_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT89_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT90_SIUL_EIRQ_21_IN |
        SIUL2_0_PORT91_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT92_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT93_SIUL_EIRQ_23_IN |
        SIUL2_0_PORT94_EMIOS_2_EMIOS_2_CH_5_H_IN |
        SIUL2_0_PORT95_EMIOS_1_EMIOS_1_CH_14_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_EMIOS_0_EMIOS_0_CH_2_G_IN |
        SIUL2_0_PORT97_EMIOS_0_EMIOS_0_CH_3_G_IN |
        SIUL2_0_PORT98_EMIOS_1_EMIOS_1_CH_21_Y_IN |
        SIUL2_0_PORT99_EMIOS_1_EMIOS_1_CH_22_X_IN |
        SIUL2_0_PORT100_EMIOS_1_EMIOS_1_CH_23_X_IN |
        SIUL2_0_PORT101_EMIOS_0_EMIOS_0_CH_2_G_IN |
        SIUL2_0_PORT102_EMIOS_1_EMIOS_1_CH_12_H_IN |
        SIUL2_0_PORT103_LPSPI0_LPSPI0_PCS3_IN |
        SIUL2_0_PORT104_EMIOS_0_EMIOS_0_CH_12_H_IN |
        SIUL2_0_PORT105_EMIOS_0_EMIOS_0_CH_13_H_IN |
        SIUL2_0_PORT106_EMIOS_0_EMIOS_0_CH_16_X_IN |
        SIUL2_0_PORT107_EMIOS_0_EMIOS_0_CH_17_Y_IN |
        SIUL2_0_PORT108_EMIOS_0_EMIOS_0_CH_18_Y_IN |
        SIUL2_0_PORT109_EMIOS_0_EMIOS_0_CH_20_Y_IN |
        SIUL2_0_PORT110_EMIOS_0_EMIOS_0_CH_21_Y_IN |
        SIUL2_0_PORT111_SIUL_EIRQ_31_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_EMIOS_1_EMIOS_1_CH_15_H_IN |
        SIUL2_0_PORT113_SIUL_EIRQ_24_IN |
        SIUL2_0_PORT114_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT115_EMIOS_1_EMIOS_1_CH_16_X_IN |
        SIUL2_0_PORT116_EMIOS_1_EMIOS_1_CH_17_Y_IN |
        SIUL2_0_PORT117_EMIOS_1_EMIOS_1_CH_18_Y_IN |
        SIUL2_0_PORT118_EMIOS_1_EMIOS_1_CH_19_Y_IN |
        SIUL2_0_PORT119_EMIOS_1_EMIOS_1_CH_20_Y_IN |
        SIUL2_0_PORT120_EMIOS_1_EMIOS_1_CH_21_Y_IN |
        SIUL2_0_PORT122_EMIOS_2_EMIOS_2_CH_7_H_IN |
        SIUL2_0_PORT123_EMIOS_2_EMIOS_2_CH_9_H_IN |
        SIUL2_0_PORT124_EMIOS_2_EMIOS_2_CH_0_X_IN |
        SIUL2_0_PORT125_LPUART15_LPUART15_RX_IN |
        SIUL2_0_PORT126_LPSPI5_LPSPI5_PCS3_IN |
        SIUL2_0_PORT127_FXIO_FXIO_D6_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT129_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT130_EMIOS_0_EMIOS_0_CH_3_G_IN |
        SIUL2_0_PORT131_EMIOS_0_EMIOS_0_CH_19_Y_IN |
        SIUL2_0_PORT132_EMIOS_0_EMIOS_0_CH_18_Y_IN |
        SIUL2_0_PORT133_EMIOS_0_EMIOS_0_CH_19_Y_IN |
        SIUL2_0_PORT134_EMIOS_1_EMIOS_1_CH_14_H_IN |
        SIUL2_0_PORT135_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT136_EMIOS_0_EMIOS_0_CH_6_G_IN |
        SIUL2_0_PORT137_EMIOS_0_EMIOS_0_CH_7_G_IN |
        SIUL2_0_PORT138_EMIOS_0_EMIOS_0_CH_20_Y_IN |
        SIUL2_0_PORT139_EMIOS_0_EMIOS_0_CH_1_G_IN |
        SIUL2_0_PORT140_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT142_SIUL_EIRQ_13_IN |
        SIUL2_0_PORT143_EMIOS_0_EMIOS_0_CH_22_X_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_EMIOS_0_EMIOS_0_CH_23_X_IN |
        SIUL2_0_PORT145_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT146_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT149_EMIOS_2_EMIOS_2_CH_19_Y_IN |
        SIUL2_0_PORT150_EMIOS_2_EMIOS_2_CH_20_Y_IN |
        SIUL2_0_PORT151_EMIOS_2_EMIOS_2_CH_21_Y_IN |
        SIUL2_0_PORT152_EMIOS_2_EMIOS_2_CH_4_H_IN |
        SIUL2_0_PORT153_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT154_EMIOS_2_EMIOS_2_CH_6_H_IN |
        SIUL2_0_PORT155_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT157_EMIOS_0_EMIOS_0_CH_12_H_IN |
        SIUL2_0_PORT159_LPSPI0_LPSPI0_PCS0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_EMIOS_2_EMIOS_2_CH_0_X_IN |
        SIUL2_0_PORT161_EMIOS_2_EMIOS_2_CH_1_H_IN |
        SIUL2_0_PORT162_EMIOS_2_EMIOS_2_CH_2_H_IN |
        SIUL2_0_PORT163_EMIOS_2_EMIOS_2_CH_3_H_IN |
        SIUL2_0_PORT164_EMIOS_2_EMIOS_2_CH_4_H_IN |
        SIUL2_0_PORT165_SIUL_EIRQ_5_IN |
        SIUL2_0_PORT166_EMIOS_2_EMIOS_2_CH_6_H_IN |
        SIUL2_0_PORT167_EMIOS_2_EMIOS_2_CH_7_H_IN |
        SIUL2_0_PORT168_EMIOS_2_EMIOS_2_CH_8_X_IN |
        SIUL2_0_PORT169_EMIOS_2_EMIOS_2_CH_9_H_IN |
        SIUL2_0_PORT170_EMIOS_2_EMIOS_2_CH_10_H_IN |
        SIUL2_0_PORT171_EMIOS_2_EMIOS_2_CH_11_H_IN |
        SIUL2_0_PORT172_EMIOS_2_EMIOS_2_CH_12_H_IN |
        SIUL2_0_PORT173_EMIOS_2_EMIOS_2_CH_13_H_IN |
        SIUL2_0_PORT174_EMIOS_2_EMIOS_2_CH_14_H_IN |
        SIUL2_0_PORT175_SIUL_EIRQ_23_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_EMIOS_2_EMIOS_2_CH_16_X_IN |
        SIUL2_0_PORT177_EMIOS_2_EMIOS_2_CH_17_Y_IN |
        SIUL2_0_PORT178_EMIOS_2_EMIOS_2_CH_18_Y_IN |
        SIUL2_0_PORT179_EMIOS_2_EMIOS_2_CH_19_Y_IN |
        SIUL2_0_PORT180_EMIOS_2_EMIOS_2_CH_20_Y_IN |
        SIUL2_0_PORT181_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT182_EMIOS_2_EMIOS_2_CH_22_X_IN |
        SIUL2_0_PORT183_EMIOS_2_EMIOS_2_CH_23_X_IN |
        SIUL2_0_PORT184_LPUART9_LPUART9_RX_IN |
        SIUL2_0_PORT185_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT186_EMIOS_1_EMIOS_1_CH_10_H_IN |
        SIUL2_0_PORT187_LPSPI4_LPSPI4_PCS2_IN |
        SIUL2_0_PORT188_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT189_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT190_EMIOS_1_EMIOS_1_CH_14_H_IN |
        SIUL2_0_PORT191_FXIO_FXIO_D9_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_EMIOS_1_EMIOS_1_CH_16_X_IN |
        SIUL2_0_PORT193_EMIOS_1_EMIOS_1_CH_17_Y_IN |
        SIUL2_0_PORT194_EMIOS_1_EMIOS_1_CH_18_Y_IN |
        SIUL2_0_PORT195_EMIOS_1_EMIOS_1_CH_19_Y_IN |
        SIUL2_0_PORT196_EMIOS_1_EMIOS_1_CH_20_Y_IN |
        SIUL2_0_PORT197_EMIOS_1_EMIOS_1_CH_21_Y_IN |
        SIUL2_0_PORT198_EMIOS_1_EMIOS_1_CH_22_X_IN |
        SIUL2_0_PORT199_EMIOS_1_EMIOS_1_CH_23_X_IN |
        SIUL2_0_PORT200_EMIOS_0_EMIOS_0_CH_13_H_IN |
        SIUL2_0_PORT201_SIUL_EIRQ_25_IN |
        SIUL2_0_PORT202_EMIOS_0_EMIOS_0_CH_14_H_IN |
        SIUL2_0_PORT203_EMIOS_0_EMIOS_0_CH_15_H_IN |
        SIUL2_0_PORT204_EMIOS_0_EMIOS_0_CH_16_X_IN |
        SIUL2_0_PORT205_EMIOS_0_EMIOS_0_CH_17_Y_IN |
        SIUL2_0_PORT206_SIUL_EIRQ_30_IN |
        SIUL2_0_PORT207_EMIOS_2_EMIOS_2_CH_15_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT209_FXIO_FXIO_D16_IN |
        SIUL2_0_PORT210_FXIO_FXIO_D17_IN |
        SIUL2_0_PORT211_FXIO_FXIO_D18_IN |
        SIUL2_0_PORT212_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT213_FXIO_FXIO_D20_IN |
        SIUL2_0_PORT214_FXIO_FXIO_D21_IN |
        SIUL2_0_PORT215_EMIOS_2_EMIOS_2_CH_23_X_IN |
        SIUL2_0_PORT216_FXIO_FXIO_D23_IN |
        SIUL2_0_PORT217_FXIO_FXIO_D24_IN |
        SIUL2_0_PORT218_FXIO_FXIO_D25_IN |
        SIUL2_0_PORT219_FXIO_FXIO_D26_IN |
        SIUL2_0_PORT220_LPSPI5_LPSPI5_PCS0_IN |
        SIUL2_0_PORT221_EMIOS_0_EMIOS_0_CH_6_G_IN |
        SIUL2_0_PORT222_EMIOS_0_EMIOS_0_CH_7_G_IN |
        SIUL2_0_PORT223_EMIOS_0_EMIOS_0_CH_8_X_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_EMIOS_0_EMIOS_0_CH_9_H_IN |
        SIUL2_0_PORT225_EMIOS_0_EMIOS_0_CH_10_H_IN |
        SIUL2_0_PORT226_EMIOS_0_EMIOS_0_CH_11_H_IN |
        SIUL2_0_PORT227_EMIOS_0_EMIOS_0_CH_12_H_IN |
        SIUL2_0_PORT228_EMIOS_0_EMIOS_0_CH_13_H_IN |
        SIUL2_0_PORT229_EMIOS_0_EMIOS_0_CH_14_H_IN |
        SIUL2_0_PORT230_EMIOS_0_EMIOS_0_CH_15_H_IN |
        SIUL2_0_PORT231_EMIOS_0_EMIOS_0_CH_16_X_IN |
        SIUL2_0_PORT232_FXIO_FXIO_D24_IN |
        SIUL2_0_PORT233_FXIO_FXIO_D25_IN |
        SIUL2_0_PORT234_FXIO_FXIO_D26_IN |
        SIUL2_0_PORT235_FXIO_FXIO_D27_IN |
        SIUL2_0_PORT236_FXIO_FXIO_D28_IN |
        SIUL2_0_PORT238_CAN8_CAN8_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT240_CAN11_CAN11_RX_IN |
        SIUL2_0_PORT241_LPUART14_LPUART14_TX_IN |
        SIUL2_0_PORT242_LPUART14_LPUART14_RX_IN |
        SIUL2_0_PORT243_LPUART15_LPUART15_TX_IN |
        SIUL2_0_PORT244_LPUART15_LPUART15_RX_IN |
        SIUL2_0_PORT248_TRGMUX_TRGMUX_IN0_IN |
        SIUL2_0_PORT249_TRGMUX_TRGMUX_IN1_IN |
        SIUL2_0_PORT250_TRGMUX_TRGMUX_IN2_IN |
        SIUL2_0_PORT251_TRGMUX_TRGMUX_IN3_IN |
        SIUL2_0_PORT252_CAN8_CAN8_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT257_FXIO_FXIO_D9_IN |
        SIUL2_0_PORT258_LPUART13_LPUART13_TX_IN |
        SIUL2_0_PORT259_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT260_FXIO_FXIO_D12_IN |
        SIUL2_0_PORT261_LPUART14_LPUART14_RX_IN |
        SIUL2_0_PORT262_FXIO_FXIO_D14_IN |
        SIUL2_0_PORT263_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT266_CAN10_CAN10_RX_IN |
        SIUL2_0_PORT268_LPUART9_LPUART9_TX_IN |
        SIUL2_0_PORT269_LPUART9_LPUART9_RX_IN |
        SIUL2_0_PORT271_CAN8_CAN8_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_LPSPI1_LPSPI1_PCS0_IN |
        SIUL2_0_PORT273_CAN11_CAN11_RX_IN |
        SIUL2_0_PORT274_LPSPI1_LPSPI1_SOUT_IN |
        SIUL2_0_PORT275_CAN9_CAN9_RX_IN |
        SIUL2_0_PORT276_LPSPI1_LPSPI1_SIN_IN |
        SIUL2_0_PORT277_CAN7_CAN7_RX_IN |
        SIUL2_0_PORT279_LPSPI1_LPSPI1_SCK_IN |
        SIUL2_0_PORT280_TRGMUX_TRGMUX_IN4_IN |
        SIUL2_0_PORT281_TRGMUX_TRGMUX_IN5_IN |
        SIUL2_0_PORT282_LPUART9_LPUART9_RX_IN |
        SIUL2_0_PORT283_TRGMUX_TRGMUX_IN7_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT289_FXIO_FXIO_D17_IN |
        SIUL2_0_PORT290_FXIO_FXIO_D18_IN |
        SIUL2_0_PORT291_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT292_FXIO_FXIO_D20_IN |
        SIUL2_0_PORT293_FXIO_FXIO_D21_IN |
        SIUL2_0_PORT294_FXIO_FXIO_D22_IN |
        SIUL2_0_PORT295_FXIO_FXIO_D23_IN |
        SIUL2_0_PORT298_LPSPI3_LPSPI3_SCK_IN |
        SIUL2_0_PORT300_FXIO_FXIO_D28_IN |
        SIUL2_0_PORT301_FXIO_FXIO_D29_IN |
        SIUL2_0_PORT302_FXIO_FXIO_D30_IN |
        SIUL2_0_PORT303_FXIO_FXIO_D31_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_LPSPI3_LPSPI3_PCS0_IN |
        SIUL2_0_PORT305_CAN10_CAN10_RX_IN |
        SIUL2_0_PORT307_CAN11_CAN11_RX_IN |
        SIUL2_0_PORT309_CAN6_CAN6_RX_IN |
        SIUL2_0_PORT311_LPSPI4_LPSPI4_SIN_IN |
        SIUL2_0_PORT312_TRGMUX_TRGMUX_IN8_IN |
        SIUL2_0_PORT313_TRGMUX_TRGMUX_IN9_IN |
        SIUL2_0_PORT314_LPSPI4_LPSPI4_SOUT_IN |
        SIUL2_0_PORT315_TRGMUX_TRGMUX_IN11_IN |
        SIUL2_0_PORT317_LPSPI4_LPSPI4_SCK_IN |
        SIUL2_0_PORT318_CAN8_CAN8_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_FXIO_FXIO_D24_IN |
        SIUL2_0_PORT321_FXIO_FXIO_D25_IN |
        SIUL2_0_PORT322_FXIO_FXIO_D26_IN |
        SIUL2_0_PORT323_FXIO_FXIO_D27_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_INPUT3_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT1_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT2_FCCU_FCCU_ERR_IN0_IN |
        SIUL2_0_PORT3_FCCU_FCCU_ERR_IN1_IN |
        SIUL2_0_PORT4_JTAG_JTAG_TMSSWD_DIO_IN |
        SIUL2_0_PORT6_EMIOS_1_EMIOS_1_CH_13_H_IN |
        SIUL2_0_PORT7_FXIO_FXIO_D9_IN |
        SIUL2_0_PORT8_EMIOS_2_EMIOS_2_CH_7_H_IN |
        SIUL2_0_PORT9_LPSPI2_LPSPI2_PCS0_IN |
        SIUL2_0_PORT10_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT11_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT12_EMIOS_0_EMIOS_0_CH_14_H_IN |
        SIUL2_0_PORT13_EMIOS_1_EMIOS_1_CH_3_H_IN |
        SIUL2_0_PORT14_EMIOS_2_EMIOS_2_CH_18_Y_IN |
        SIUL2_0_PORT15_FXIO_FXIO_D31_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_FXIO_FXIO_D30_IN |
        SIUL2_0_PORT17_LPSPI3_LPSPI3_SOUT_IN |
        SIUL2_0_PORT18_EMIOS_1_EMIOS_1_CH_16_X_IN |
        SIUL2_0_PORT19_EMIOS_2_EMIOS_2_CH_1_H_IN |
        SIUL2_0_PORT20_EMIOS_2_EMIOS_2_CH_2_H_IN |
        SIUL2_0_PORT21_EMIOS_2_EMIOS_2_CH_3_H_IN |
        SIUL2_0_PORT22_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT25_EMIOS_2_EMIOS_2_CH_8_X_IN |
        SIUL2_0_PORT26_GMAC0_GMAC0_PPS0_IN |
        SIUL2_0_PORT27_GMAC0_GMAC0_PPS1_IN |
        SIUL2_0_PORT28_EMIOS_1_EMIOS_1_CH_11_H_IN |
        SIUL2_0_PORT29_GMAC0_GMAC0_PPS2_IN |
        SIUL2_0_PORT30_EMIOS_2_EMIOS_2_CH_13_H_IN |
        SIUL2_0_PORT31_FXIO_FXIO_D0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_EMIOS_0_EMIOS_0_CH_3_G_IN |
        SIUL2_0_PORT33_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT34_EMIOS_0_EMIOS_0_CH_8_X_IN |
        SIUL2_0_PORT35_FXIO_FXIO_D17_IN |
        SIUL2_0_PORT36_EMIOS_1_EMIOS_1_CH_10_H_IN |
        SIUL2_0_PORT37_EMIOS_1_EMIOS_1_CH_11_H_IN |
        SIUL2_0_PORT40_FXIO_FXIO_D29_IN |
        SIUL2_0_PORT41_FXIO_FXIO_D28_IN |
        SIUL2_0_PORT42_FXIO_FXIO_D27_IN |
        SIUL2_0_PORT43_FXIO_FXIO_D26_IN |
        SIUL2_0_PORT44_FXIO_FXIO_D25_IN |
        SIUL2_0_PORT45_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT46_FXIO_FXIO_D23_IN |
        SIUL2_0_PORT47_FXIO_FXIO_D22_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_FXIO_FXIO_D21_IN |
        SIUL2_0_PORT49_EMIOS_1_EMIOS_1_CH_7_H_IN |
        SIUL2_0_PORT50_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT51_GMAC0_GMAC0_PPS0_IN |
        SIUL2_0_PORT52_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT53_EMIOS_2_EMIOS_2_CH_17_Y_IN |
        SIUL2_0_PORT54_EMIOS_2_EMIOS_2_CH_18_Y_IN |
        SIUL2_0_PORT55_EMIOS_1_EMIOS_1_CH_19_Y_IN |
        SIUL2_0_PORT56_EMIOS_2_EMIOS_2_CH_20_Y_IN |
        SIUL2_0_PORT57_EMIOS_2_EMIOS_2_CH_21_Y_IN |
        SIUL2_0_PORT58_EMIOS_2_EMIOS_2_CH_22_X_IN |
        SIUL2_0_PORT59_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT60_GMAC0_GMAC0_PPS3_IN |
        SIUL2_0_PORT61_FXIO_FXIO_D10_IN |
        SIUL2_0_PORT63_HSE_HSE_TAMPER_EXTIN0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_EMIOS_0_EMIOS_0_CH_14_H_IN |
        SIUL2_0_PORT65_EMIOS_0_EMIOS_0_CH_1_G_IN |
        SIUL2_0_PORT66_EMIOS_0_EMIOS_0_CH_2_G_IN |
        SIUL2_0_PORT67_LPUART0_LPUART0_TX_IN |
        SIUL2_0_PORT68_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT69_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT70_EMIOS_1_EMIOS_1_CH_6_H_IN |
        SIUL2_0_PORT71_FXIO_FXIO_D10_IN |
        SIUL2_0_PORT72_FXIO_FXIO_D12_IN |
        SIUL2_0_PORT73_EMIOS_1_EMIOS_1_CH_8_X_IN |
        SIUL2_0_PORT74_EMIOS_1_EMIOS_1_CH_0_X_IN |
        SIUL2_0_PORT75_EMIOS_1_EMIOS_1_CH_1_H_IN |
        SIUL2_0_PORT76_EMIOS_1_EMIOS_1_CH_2_H_IN |
        SIUL2_0_PORT77_EMIOS_1_EMIOS_1_CH_3_H_IN |
        SIUL2_0_PORT78_EMIOS_0_EMIOS_0_CH_10_H_IN |
        SIUL2_0_PORT79_LPI2C1_LPI2C1_SCL_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_EMIOS_2_EMIOS_2_CH_9_H_IN |
        SIUL2_0_PORT81_LPI2C1_LPI2C1_SCLS_IN |
        SIUL2_0_PORT82_FXIO_FXIO_D12_IN |
        SIUL2_0_PORT83_LPSPI2_LPSPI2_PCS1_IN |
        SIUL2_0_PORT84_GMAC0_GMAC0_PPS0_IN |
        SIUL2_0_PORT85_GMAC0_GMAC0_PPS1_IN |
        SIUL2_0_PORT87_CAN6_CAN6_RX_IN |
        SIUL2_0_PORT88_EMIOS_2_EMIOS_2_CH_0_X_IN |
        SIUL2_0_PORT89_EMIOS_2_EMIOS_2_CH_1_H_IN |
        SIUL2_0_PORT90_EMIOS_1_EMIOS_1_CH_3_H_IN |
        SIUL2_0_PORT91_EMIOS_2_EMIOS_2_CH_3_H_IN |
        SIUL2_0_PORT92_FXIO_FXIO_D21_IN |
        SIUL2_0_PORT93_EMIOS_1_EMIOS_1_CH_10_H_IN |
        SIUL2_0_PORT94_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT95_EMIOS_2_EMIOS_2_CH_6_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_EMIOS_0_EMIOS_0_CH_16_X_IN |
        SIUL2_0_PORT97_EMIOS_0_EMIOS_0_CH_17_Y_IN |
        SIUL2_0_PORT98_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT99_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT100_LPSPI1_LPSPI1_PCS1_IN |
        SIUL2_0_PORT101_EMIOS_0_EMIOS_0_CH_19_Y_IN |
        SIUL2_0_PORT102_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT103_LPSPI3_LPSPI3_PCS3_IN |
        SIUL2_0_PORT104_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT105_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT106_EMIOS_1_EMIOS_1_CH_10_H_IN |
        SIUL2_0_PORT107_LPSPI0_LPSPI0_SCK_IN |
        SIUL2_0_PORT108_LPI2C1_LPI2C1_HREQ_IN |
        SIUL2_0_PORT109_GMAC0_GMAC0_PPS1_IN |
        SIUL2_0_PORT110_GMAC0_GMAC0_PPS0_IN |
        SIUL2_0_PORT111_EMIOS_0_EMIOS_0_CH_0_X_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPSPI0_LPSPI0_SIN_IN |
        SIUL2_0_PORT113_EMIOS_0_EMIOS_0_CH_18_Y_IN |
        SIUL2_0_PORT115_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT116_EMIOS_2_EMIOS_2_CH_0_X_IN |
        SIUL2_0_PORT117_EMIOS_2_EMIOS_2_CH_8_X_IN |
        SIUL2_0_PORT118_EMIOS_2_EMIOS_2_CH_22_X_IN |
        SIUL2_0_PORT119_EMIOS_2_EMIOS_2_CH_23_X_IN |
        SIUL2_0_PORT120_FXIO_FXIO_D29_IN |
        SIUL2_0_PORT122_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT123_FXIO_FXIO_D31_IN |
        SIUL2_0_PORT124_LPSPI5_LPSPI5_SIN_IN |
        SIUL2_0_PORT125_LPSPI5_LPSPI5_PCS2_IN |
        SIUL2_0_PORT127_LPSPI5_LPSPI5_SCK_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_LPUART7_LPUART7_RX_IN |
        SIUL2_0_PORT129_LPSPI0_LPSPI0_SCK_IN |
        SIUL2_0_PORT130_EMIOS_1_EMIOS_1_CH_8_X_IN |
        SIUL2_0_PORT131_GMAC0_GMAC0_PPS0_IN |
        SIUL2_0_PORT132_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT133_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT134_FXIO_FXIO_D12_IN |
        SIUL2_0_PORT135_LPUART4_LPUART4_RX_IN |
        SIUL2_0_PORT136_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT137_EMIOS_1_EMIOS_1_CH_13_H_IN |
        SIUL2_0_PORT138_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT139_EMIOS_0_EMIOS_0_CH_21_Y_IN |
        SIUL2_0_PORT140_GMAC0_GMAC0_PPS3_IN |
        SIUL2_0_PORT142_EMIOS_0_EMIOS_0_CH_19_Y_IN |
        SIUL2_0_PORT143_FCCU_FCCU_ERR_IN0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_FCCU_FCCU_ERR_IN1_IN |
        SIUL2_0_PORT149_LPSPI4_LPSPI4_SIN_IN |
        SIUL2_0_PORT150_LPSPI4_LPSPI4_SCK_IN |
        SIUL2_0_PORT151_LPSPI4_LPSPI4_PCS0_IN |
        SIUL2_0_PORT152_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT153_EMIOS_2_EMIOS_2_CH_5_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_LPSPI2_LPSPI2_SCK_IN |
        SIUL2_0_PORT161_LPUART5_LPUART5_RX_IN |
        SIUL2_0_PORT162_LPSPI2_LPSPI2_SOUT_IN |
        SIUL2_0_PORT163_LPUART6_LPUART6_RX_IN |
        SIUL2_0_PORT164_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT165_EMIOS_2_EMIOS_2_CH_5_H_IN |
        SIUL2_0_PORT167_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT168_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT171_HSE_HSE_TAMPER_EXTIN0_IN |
        SIUL2_0_PORT172_LPSPI3_LPSPI3_SIN_IN |
        SIUL2_0_PORT173_LPUART10_LPUART10_RX_IN |
        SIUL2_0_PORT174_FCCU_FCCU_ERR_IN0_IN |
        SIUL2_0_PORT175_EMIOS_2_EMIOS_2_CH_15_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_LPSPI3_LPSPI3_PCS0_IN |
        SIUL2_0_PORT177_LPUART12_LPUART12_RX_IN |
        SIUL2_0_PORT178_LPSPI3_LPSPI3_PCS1_IN |
        SIUL2_0_PORT179_LPUART7_LPUART7_RX_IN |
        SIUL2_0_PORT180_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT181_EMIOS_2_EMIOS_2_CH_21_Y_IN |
        SIUL2_0_PORT182_LPSPI4_LPSPI4_PCS2_IN |
        SIUL2_0_PORT183_LPSPI3_LPSPI3_PCS3_IN |
        SIUL2_0_PORT185_LPSPI2_LPSPI2_PCS2_IN |
        SIUL2_0_PORT186_LPSPI2_LPSPI2_PCS3_IN |
        SIUL2_0_PORT187_LPUART11_LPUART11_TX_IN |
        SIUL2_0_PORT188_LPUART11_LPUART11_RX_IN |
        SIUL2_0_PORT189_LPSPI3_LPSPI3_PCS1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_LPUART13_LPUART13_TX_IN |
        SIUL2_0_PORT193_LPUART13_LPUART13_RX_IN |
        SIUL2_0_PORT194_LPUART14_LPUART14_TX_IN |
        SIUL2_0_PORT195_LPUART14_LPUART14_RX_IN |
        SIUL2_0_PORT196_LPUART15_LPUART15_TX_IN |
        SIUL2_0_PORT197_LPUART15_LPUART15_RX_IN |
        SIUL2_0_PORT198_FXIO_FXIO_D10_IN |
        SIUL2_0_PORT199_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT200_FXIO_FXIO_D12_IN |
        SIUL2_0_PORT201_EMIOS_1_EMIOS_1_CH_5_H_IN |
        SIUL2_0_PORT202_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT203_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT204_LPSPI4_LPSPI4_PCS3_IN |
        SIUL2_0_PORT205_FXIO_FXIO_D13_IN |
        SIUL2_0_PORT206_EMIOS_0_EMIOS_0_CH_18_Y_IN |
        SIUL2_0_PORT207_FXIO_FXIO_D14_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT213_CAN6_CAN6_RX_IN |
        SIUL2_0_PORT215_FXIO_FXIO_D22_IN |
        SIUL2_0_PORT216_LPSPI5_LPSPI5_PCS2_IN |
        SIUL2_0_PORT217_LPUART12_LPUART12_RX_IN |
        SIUL2_0_PORT219_CAN7_CAN7_RX_IN |
        SIUL2_0_PORT221_FXIO_FXIO_D29_IN |
        SIUL2_0_PORT222_FXIO_FXIO_D30_IN |
        SIUL2_0_PORT223_FXIO_FXIO_D31_IN */
        (uint16)( SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_FXIO_FXIO_D16_IN |
        SIUL2_0_PORT225_FXIO_FXIO_D17_IN |
        SIUL2_0_PORT226_FXIO_FXIO_D18_IN |
        SIUL2_0_PORT227_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT228_FXIO_FXIO_D20_IN |
        SIUL2_0_PORT229_FXIO_FXIO_D21_IN |
        SIUL2_0_PORT230_FXIO_FXIO_D22_IN |
        SIUL2_0_PORT231_FXIO_FXIO_D23_IN |
        SIUL2_0_PORT232_LPUART2_LPUART2_TX_IN |
        SIUL2_0_PORT233_LPUART10_LPUART10_RX_IN |
        SIUL2_0_PORT234_LPUART11_LPUART11_TX_IN |
        SIUL2_0_PORT235_LPUART11_LPUART11_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT250_CAN11_CAN11_RX_IN */
        (uint16)( SHL_PAD_U32(10U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT257_CAN9_CAN9_RX_IN |
        SIUL2_0_PORT259_LPUART13_LPUART13_RX_IN |
        SIUL2_0_PORT260_TRGMUX_TRGMUX_IN12_IN |
        SIUL2_0_PORT261_TRGMUX_TRGMUX_IN13_IN |
        SIUL2_0_PORT262_TRGMUX_TRGMUX_IN14_IN |
        SIUL2_0_PORT263_TRGMUX_TRGMUX_IN15_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT280_CAN10_CAN10_RX_IN |
        SIUL2_0_PORT281_LPUART9_LPUART9_TX_IN |
        SIUL2_0_PORT282_TRGMUX_TRGMUX_IN6_IN */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT289_CAN10_CAN10_RX_IN |
        SIUL2_0_PORT292_LPUART13_LPUART13_TX_IN |
        SIUL2_0_PORT293_LPUART13_LPUART13_RX_IN |
        SIUL2_0_PORT300_LPSPI3_LPSPI3_SIN_IN |
        SIUL2_0_PORT301_CAN8_CAN8_RX_IN |
        SIUL2_0_PORT302_LPSPI3_LPSPI3_SOUT_IN |
        SIUL2_0_PORT303_CAN9_CAN9_RX_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT312_CAN9_CAN9_RX_IN |
        SIUL2_0_PORT314_TRGMUX_TRGMUX_IN10_IN |
        SIUL2_0_PORT315_CAN10_CAN10_RX_IN */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_LPSPI4_LPSPI4_PCS0_IN |
        SIUL2_0_PORT321_CAN11_CAN11_RX_IN |
        SIUL2_0_PORT322_LPUART15_LPUART15_TX_IN |
        SIUL2_0_PORT323_LPUART15_LPUART15_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_INPUT4_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT1_LPSPI0_LPSPI0_PCS6_IN |
        SIUL2_0_PORT2_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT3_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT6_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT7_LPSPI0_LPSPI0_PCS1_IN |
        SIUL2_0_PORT8_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT9_LPSPI3_LPSPI3_PCS0_IN |
        SIUL2_0_PORT11_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT12_EMIOS_1_EMIOS_1_CH_2_H_IN |
        SIUL2_0_PORT13_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT14_FXIO_FXIO_D14_IN |
        SIUL2_0_PORT15_LPUART6_LPUART6_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI0_LPSPI0_PCS4_IN |
        SIUL2_0_PORT17_LPUART4_LPUART4_TX_IN |
        SIUL2_0_PORT18_EMIOS_2_EMIOS_2_CH_0_X_IN |
        SIUL2_0_PORT19_LPUART1_LPUART1_RX_IN |
        SIUL2_0_PORT20_LPSPI1_LPSPI1_SIN_IN |
        SIUL2_0_PORT21_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT22_LPSPI1_LPSPI1_PCS1_IN |
        SIUL2_0_PORT25_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT26_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT27_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT28_EMIOS_2_EMIOS_2_CH_11_H_IN |
        SIUL2_0_PORT29_LPSPI1_LPSPI1_SIN_IN |
        SIUL2_0_PORT30_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT31_LPSPI0_LPSPI0_PCS1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_EMIOS_1_EMIOS_1_CH_6_H_IN |
        SIUL2_0_PORT33_LPI2C0_LPI2C0_SCLS_IN |
        SIUL2_0_PORT34_FXIO_FXIO_D18_IN |
        SIUL2_0_PORT35_LPSPI2_LPSPI2_SOUT_IN |
        SIUL2_0_PORT36_LPSPI0_LPSPI0_SOUT_IN |
        SIUL2_0_PORT37_LPSPI0_LPSPI0_PCS0_IN |
        SIUL2_0_PORT40_LPSPI0_LPSPI0_PCS5_IN |
        SIUL2_0_PORT41_LPUART9_LPUART9_RX_IN |
        SIUL2_0_PORT42_LPSPI4_LPSPI4_SCK_IN |
        SIUL2_0_PORT43_LPI2C0_LPI2C0_HREQ_IN |
        SIUL2_0_PORT44_LPUART8_LPUART8_RX_IN |
        SIUL2_0_PORT45_FXIO_FXIO_D24_IN |
        SIUL2_0_PORT46_LPUART7_LPUART7_RX_IN |
        SIUL2_0_PORT47_LPSPI1_LPSPI1_SIN_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_LPSPI1_LPSPI1_SOUT_IN |
        SIUL2_0_PORT49_FXIO_FXIO_D20_IN |
        SIUL2_0_PORT50_LPSPI1_LPSPI1_PCS1_IN |
        SIUL2_0_PORT51_FXIO_FXIO_D2_IN |
        SIUL2_0_PORT52_LPUART14_LPUART14_TX_IN |
        SIUL2_0_PORT53_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT54_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT55_EMIOS_2_EMIOS_2_CH_19_Y_IN |
        SIUL2_0_PORT56_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT57_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT58_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT59_LPSPI2_LPSPI2_SOUT_IN |
        SIUL2_0_PORT60_FXIO_FXIO_D9_IN |
        SIUL2_0_PORT61_LPSPI2_LPSPI2_SCK_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC0_GMAC0_MII_RMII_RXD_0_IN |
        SIUL2_0_PORT65_EMIOS_0_EMIOS_0_CH_15_H_IN |
        SIUL2_0_PORT66_LPUART0_LPUART0_RX_IN |
        SIUL2_0_PORT67_GMAC1_GMAC1_MII_RMII_TX_EN_IN |
        SIUL2_0_PORT68_JTAG_JTAG_TCKSWD_CLK_IN |
        SIUL2_0_PORT69_JTAG_JTAG_TDI_IN |
        SIUL2_0_PORT70_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT71_LPI2C0_LPI2C0_HREQ_IN |
        SIUL2_0_PORT72_LPUART1_LPUART1_RX_IN |
        SIUL2_0_PORT73_FXIO_FXIO_D13_IN |
        SIUL2_0_PORT74_LPSPI2_LPSPI2_PCS1_IN |
        SIUL2_0_PORT75_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT76_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT77_FXIO_FXIO_D16_IN |
        SIUL2_0_PORT78_EMIOS_1_EMIOS_1_CH_4_H_IN |
        SIUL2_0_PORT79_LPSPI2_LPSPI2_SCK_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT81_LPSPI3_LPSPI3_SCK_IN |
        SIUL2_0_PORT82_LPUART6_LPUART6_RX_IN |
        SIUL2_0_PORT83_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_IN |
        SIUL2_0_PORT84_FXIO_FXIO_D14_IN |
        SIUL2_0_PORT85_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT88_FXIO_FXIO_D17_IN |
        SIUL2_0_PORT89_FXIO_FXIO_D18_IN |
        SIUL2_0_PORT90_EMIOS_2_EMIOS_2_CH_2_H_IN |
        SIUL2_0_PORT91_FXIO_FXIO_D20_IN |
        SIUL2_0_PORT92_LPI2C1_LPI2C1_SCL_IN |
        SIUL2_0_PORT93_EMIOS_2_EMIOS_2_CH_4_H_IN |
        SIUL2_0_PORT94_FXIO_FXIO_D23_IN |
        SIUL2_0_PORT95_FXIO_FXIO_D1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_FXIO_FXIO_D0_IN |
        SIUL2_0_PORT97_FXIO_FXIO_D1_IN |
        SIUL2_0_PORT98_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT99_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT100_LPSPI5_LPSPI5_PCS0_IN |
        SIUL2_0_PORT101_FXIO_FXIO_D15_IN |
        SIUL2_0_PORT102_FXIO_FXIO_D13_IN |
        SIUL2_0_PORT103_GMAC0_GMAC0_MII_RMII_TXD_0_IN |
        SIUL2_0_PORT104_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT105_FXIO_FXIO_D10_IN |
        SIUL2_0_PORT106_LPSPI0_LPSPI0_SIN_IN |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_RMII_TX_CLK_IN |
        SIUL2_0_PORT108_LPSPI0_LPSPI0_SOUT_IN |
        SIUL2_0_PORT109_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT110_LPI2C0_LPI2C0_SCL_IN |
        SIUL2_0_PORT111_EMIOS_1_EMIOS_1_CH_14_H_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_GMAC0_GMAC0_MII_RMII_RGMII_MDIO_IN |
        SIUL2_0_PORT113_GMAC0_GMAC0_PPS2_IN |
        SIUL2_0_PORT116_FXIO_FXIO_D25_IN |
        SIUL2_0_PORT117_FXIO_FXIO_D26_IN |
        SIUL2_0_PORT118_FXIO_FXIO_D27_IN |
        SIUL2_0_PORT119_FXIO_FXIO_D28_IN |
        SIUL2_0_PORT120_HSE_HSE_TAMPER_EXTIN0_IN |
        SIUL2_0_PORT122_FXIO_FXIO_D30_IN |
        SIUL2_0_PORT123_LPUART14_LPUART14_RX_IN |
        SIUL2_0_PORT124_LPUART15_LPUART15_TX_IN |
        SIUL2_0_PORT125_CAN6_CAN6_RX_IN |
        SIUL2_0_PORT127_CAN7_CAN7_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_LPSPI0_LPSPI0_SIN_IN |
        SIUL2_0_PORT129_LPUART7_LPUART7_TX_IN |
        SIUL2_0_PORT130_FXIO_FXIO_D13_IN |
        SIUL2_0_PORT131_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT132_FXIO_FXIO_D6_IN |
        SIUL2_0_PORT133_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT134_LPSPI0_LPSPI0_PCS2_IN |
        SIUL2_0_PORT135_LPSPI3_LPSPI3_SCK_IN |
        SIUL2_0_PORT136_FXIO_FXIO_D12_IN |
        SIUL2_0_PORT137_GMAC0_GMAC0_PPS3_IN |
        SIUL2_0_PORT138_LPUART4_LPUART4_RX_IN |
        SIUL2_0_PORT139_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT140_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT142_GMAC0_GMAC0_PPS1_IN |
        SIUL2_0_PORT143_FXIO_FXIO_D2_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT152_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT153_LPSPI4_LPSPI4_SOUT_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_LPUART5_LPUART5_TX_IN |
        SIUL2_0_PORT161_LPSPI2_LPSPI2_SIN_IN |
        SIUL2_0_PORT162_LPUART6_LPUART6_TX_IN |
        SIUL2_0_PORT163_LPSPI2_LPSPI2_PCS0_IN |
        SIUL2_0_PORT164_LPSPI2_LPSPI2_SOUT_IN |
        SIUL2_0_PORT167_LPI2C1_LPI2C1_SCL_IN |
        SIUL2_0_PORT168_LPI2C1_LPI2C1_SDA_IN |
        SIUL2_0_PORT172_LPUART10_LPUART10_TX_IN |
        SIUL2_0_PORT173_LPSPI3_LPSPI3_SCK_IN |
        SIUL2_0_PORT174_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT175_FCCU_FCCU_ERR_IN1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_LPUART12_LPUART12_TX_IN |
        SIUL2_0_PORT178_LPUART7_LPUART7_TX_IN |
        SIUL2_0_PORT179_LPSPI3_LPSPI3_PCS2_IN |
        SIUL2_0_PORT180_LPI2C0_LPI2C0_SCL_IN |
        SIUL2_0_PORT181_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT183_LPUART9_LPUART9_TX_IN |
        SIUL2_0_PORT185_LPSPI4_LPSPI4_PCS0_IN |
        SIUL2_0_PORT186_LPSPI4_LPSPI4_PCS1_IN |
        SIUL2_0_PORT188_LPSPI0_LPSPI0_PCS0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT200_LPSPI5_LPSPI5_PCS3_IN |
        SIUL2_0_PORT201_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT205_LPSPI5_LPSPI5_PCS2_IN |
        SIUL2_0_PORT206_LPSPI2_LPSPI2_PCS0_IN */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT215_LPSPI5_LPSPI5_PCS0_IN |
        SIUL2_0_PORT216_LPUART12_LPUART12_TX_IN |
        SIUL2_0_PORT217_LPSPI5_LPSPI5_SOUT_IN |
        SIUL2_0_PORT221_LPSPI5_LPSPI5_SIN_IN |
        SIUL2_0_PORT222_LPSPI5_LPSPI5_SOUT_IN |
        SIUL2_0_PORT223_LPSPI5_LPSPI5_SCK_IN */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_LPSPI2_LPSPI2_PCS2_IN |
        SIUL2_0_PORT225_LPUART0_LPUART0_RX_IN |
        SIUL2_0_PORT226_LPUART3_LPUART3_TX_IN |
        SIUL2_0_PORT227_LPUART3_LPUART3_RX_IN |
        SIUL2_0_PORT228_LPUART4_LPUART4_TX_IN |
        SIUL2_0_PORT229_LPUART4_LPUART4_RX_IN |
        SIUL2_0_PORT230_LPUART8_LPUART8_TX_IN |
        SIUL2_0_PORT231_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT232_LPUART10_LPUART10_TX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271
        SIUL2_0_PORT260_LPUART14_LPUART14_TX_IN */
        (uint16)( SHL_PAD_U32(4U)
                ),
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT5_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPSPI0_LPSPI0_PCS7_IN |
        SIUL2_0_PORT1_LPSPI4_LPSPI4_PCS1_IN |
        SIUL2_0_PORT2_LPUART0_LPUART0_RX_IN |
        SIUL2_0_PORT3_LPSPI1_LPSPI1_SCK_IN |
        SIUL2_0_PORT6_LPUART3_LPUART3_RX_IN |
        SIUL2_0_PORT7_LPUART3_LPUART3_TX_IN |
        SIUL2_0_PORT8_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT9_LPUART2_LPUART2_TX_IN |
        SIUL2_0_PORT11_LPSPI1_LPSPI1_PCS0_IN |
        SIUL2_0_PORT12_FXIO_FXIO_D9_IN |
        SIUL2_0_PORT13_LPSPI1_LPSPI1_PCS4_IN |
        SIUL2_0_PORT14_LPSPI1_LPSPI1_PCS3_IN |
        SIUL2_0_PORT15_LPSPI0_LPSPI0_PCS3_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI1_LPSPI1_PCS2_IN |
        SIUL2_0_PORT18_LPSPI1_LPSPI1_SOUT_IN |
        SIUL2_0_PORT19_LPSPI1_LPSPI1_SCK_IN |
        SIUL2_0_PORT20_TRGMUX_TRGMUX_IN14_IN |
        SIUL2_0_PORT21_LPSPI1_LPSPI1_PCS0_IN |
        SIUL2_0_PORT26_LPSPI0_LPSPI0_PCS0_IN |
        SIUL2_0_PORT27_LPUART0_LPUART0_TX_IN |
        SIUL2_0_PORT28_LPUART0_LPUART0_RX_IN |
        SIUL2_0_PORT29_LPUART2_LPUART2_TX_IN |
        SIUL2_0_PORT30_LPSPI0_LPSPI0_SOUT_IN |
        SIUL2_0_PORT31_SAI0_SAI0_MCLK_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_FXIO_FXIO_D14_IN |
        SIUL2_0_PORT33_LPSPI0_LPSPI0_SOUT_IN |
        SIUL2_0_PORT34_LPUART9_LPUART9_RX_IN |
        SIUL2_0_PORT35_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_IN |
        SIUL2_0_PORT36_GMAC0_GMAC0_MII_RMII_RGMII_MDIO_IN |
        SIUL2_0_PORT37_LPSPI0_LPSPI0_PCS1_IN |
        SIUL2_0_PORT40_LPSPI4_LPSPI4_PCS0_IN |
        SIUL2_0_PORT41_LPSPI4_LPSPI4_SOUT_IN |
        SIUL2_0_PORT42_LPUART9_LPUART9_TX_IN |
        SIUL2_0_PORT43_LPSPI4_LPSPI4_SIN_IN |
        SIUL2_0_PORT44_LPSPI3_LPSPI3_PCS3_IN |
        SIUL2_0_PORT45_LPSPI3_LPSPI3_PCS2_IN |
        SIUL2_0_PORT46_LPSPI1_LPSPI1_SCK_IN |
        SIUL2_0_PORT47_LPUART7_LPUART7_TX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_LPUART4_LPUART4_TX_IN |
        SIUL2_0_PORT49_LPUART4_LPUART4_RX_IN |
        SIUL2_0_PORT50_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN |
        SIUL2_0_PORT51_LPUART13_LPUART13_RX_IN |
        SIUL2_0_PORT52_GMAC1_GMAC1_PPS2_IN |
        SIUL2_0_PORT53_LPUART14_LPUART14_RX_IN |
        SIUL2_0_PORT54_LPSPI3_LPSPI3_PCS1_IN |
        SIUL2_0_PORT55_FXIO_FXIO_D4_IN |
        SIUL2_0_PORT56_GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_IN |
        SIUL2_0_PORT57_LPSPI2_LPSPI2_PCS0_IN |
        SIUL2_0_PORT58_LPUART15_LPUART15_RX_IN |
        SIUL2_0_PORT59_SAI0_SAI0_D0_IN |
        SIUL2_0_PORT60_LPUART5_LPUART5_RX_IN |
        SIUL2_0_PORT61_GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC0_GMAC0_MII_RMII_RXD_1_IN |
        SIUL2_0_PORT65_FXIO_FXIO_D5_IN |
        SIUL2_0_PORT66_LPSPI0_LPSPI0_PCS2_IN |
        SIUL2_0_PORT69_LPI2C1_LPI2C1_HREQ_IN |
        SIUL2_0_PORT70_LPUART1_LPUART1_RX_IN |
        SIUL2_0_PORT71_LPI2C1_LPI2C1_SCL_IN |
        SIUL2_0_PORT72_LPI2C0_LPI2C0_SCL_IN |
        SIUL2_0_PORT73_LPI2C0_LPI2C0_SDA_IN |
        SIUL2_0_PORT74_LPSPI4_LPSPI4_PCS0_IN |
        SIUL2_0_PORT75_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT76_LPUART10_LPUART10_RX_IN |
        SIUL2_0_PORT77_SAI0_SAI0_SYNC_IN |
        SIUL2_0_PORT78_FXIO_FXIO_D16_IN |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_CRS_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT81_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN |
        SIUL2_0_PORT82_GMAC0_GMAC0_MII_RMII_RGMII_TXD_1_IN |
        SIUL2_0_PORT83_SAI0_SAI0_D3_IN |
        SIUL2_0_PORT84_LPUART7_LPUART7_RX_IN |
        SIUL2_0_PORT88_LPUART12_LPUART12_TX_IN |
        SIUL2_0_PORT89_LPUART12_LPUART12_RX_IN |
        SIUL2_0_PORT90_FXIO_FXIO_D19_IN |
        SIUL2_0_PORT91_LPUART13_LPUART13_RX_IN |
        SIUL2_0_PORT92_LPUART0_LPUART0_TX_IN |
        SIUL2_0_PORT93_FXIO_FXIO_D3_IN |
        SIUL2_0_PORT94_LPUART1_LPUART1_DSR_B_IN |
        SIUL2_0_PORT95_FXIO_FXIO_D24_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_LPUART5_LPUART5_RX_IN |
        SIUL2_0_PORT97_LPSPI3_LPSPI3_SCK_IN |
        SIUL2_0_PORT98_LPSPI1_LPSPI1_SOUT_IN |
        SIUL2_0_PORT99_LPUART3_LPUART3_RX_IN |
        SIUL2_0_PORT101_LPSPI0_LPSPI0_PCS1_IN |
        SIUL2_0_PORT102_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT103_GMAC0_GMAC0_MII_RMII_TXD_1_IN |
        SIUL2_0_PORT104_LPUART6_LPUART6_RX_IN |
        SIUL2_0_PORT105_LPI2C1_LPI2C1_SCL_IN |
        SIUL2_0_PORT106_GMAC0_GMAC0_MII_RX_CLK_IN |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_RMII_TX_EN_IN |
        SIUL2_0_PORT108_GMAC0_GMAC0_MII_RMII_TX_CLK_IN |
        SIUL2_0_PORT109_LPUART1_LPUART1_RX_IN |
        SIUL2_0_PORT110_LPSPI5_LPSPI5_SCK_IN |
        SIUL2_0_PORT111_GMAC0_GMAC0_PPS2_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPUART8_LPUART8_TX_IN |
        SIUL2_0_PORT113_FXIO_FXIO_D9_IN |
        SIUL2_0_PORT116_LPSPI1_LPSPI1_PCS2_IN |
        SIUL2_0_PORT122_LPSPI5_LPSPI5_SCK_IN |
        SIUL2_0_PORT123_LPSPI5_LPSPI5_SOUT_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT130_LPUART10_LPUART10_RX_IN |
        SIUL2_0_PORT131_LPUART5_LPUART5_RX_IN |
        SIUL2_0_PORT132_LPSPI0_LPSPI0_PCS0_IN |
        SIUL2_0_PORT133_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT134_LPUART10_LPUART10_TX_IN |
        SIUL2_0_PORT136_LPSPI3_LPSPI3_PCS1_IN |
        SIUL2_0_PORT137_FXIO_FXIO_D11_IN |
        SIUL2_0_PORT138_LPSPI2_LPSPI2_PCS1_IN |
        SIUL2_0_PORT139_LPSPI2_LPSPI2_PCS0_IN |
        SIUL2_0_PORT140_FXIO_FXIO_D8_IN |
        SIUL2_0_PORT142_FXIO_FXIO_D7_IN |
        SIUL2_0_PORT143_LPUART3_LPUART3_RX_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPSPI2_LPSPI2_SIN_IN |
        SIUL2_0_PORT152_LPSPI2_LPSPI2_SIN_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT167_LPSPI2_LPSPI2_PCS0_IN |
        SIUL2_0_PORT175_LPSPI3_LPSPI3_SOUT_IN */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT180_LPSPI3_LPSPI3_PCS3_IN |
        SIUL2_0_PORT181_LPUART8_LPUART8_RX_IN |
        SIUL2_0_PORT188_LPSPI4_LPSPI4_PCS3_IN */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT201_LPUART2_LPUART2_TX_IN |
        SIUL2_0_PORT206_LPSPI2_LPSPI2_PCS2_IN */
        (uint16)( SHL_PAD_U32(9U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239
        SIUL2_0_PORT224_LPUART0_LPUART0_TX_IN |
        SIUL2_0_PORT225_LPSPI2_LPSPI2_PCS3_IN |
        SIUL2_0_PORT227_CAN7_CAN7_RX_IN |
        SIUL2_0_PORT231_LPUART8_LPUART8_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT6_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPSPI4_LPSPI4_PCS2_IN |
        SIUL2_0_PORT2_LPSPI1_LPSPI1_SIN_IN |
        SIUL2_0_PORT3_LPSPI5_LPSPI5_SCK_IN |
        SIUL2_0_PORT6_LPSPI1_LPSPI1_PCS1_IN |
        SIUL2_0_PORT7_LPUART0_LPUART0_DCD_B_IN |
        SIUL2_0_PORT8_LPSPI2_LPSPI2_SOUT_IN |
        SIUL2_0_PORT9_PGI_PGOOD_IN |
        SIUL2_0_PORT11_LPSPI2_LPSPI2_SCK_IN |
        SIUL2_0_PORT12_LPUART11_LPUART11_RX_IN |
        SIUL2_0_PORT13_LPUART11_LPUART11_TX_IN |
        SIUL2_0_PORT14_LPSPI5_LPSPI5_PCS1_IN |
        SIUL2_0_PORT15_LPSPI2_LPSPI2_PCS3_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI4_LPSPI4_PCS3_IN |
        SIUL2_0_PORT18_TRGMUX_TRGMUX_IN12_IN |
        SIUL2_0_PORT19_TRGMUX_TRGMUX_IN13_IN |
        SIUL2_0_PORT21_LPSPI2_LPSPI2_PCS2_IN |
        SIUL2_0_PORT26_LPSPI1_LPSPI1_PCS0_IN |
        SIUL2_0_PORT28_LPSPI1_LPSPI1_SCK_IN |
        SIUL2_0_PORT29_GMAC1_GMAC1_MII_RMII_RGMII_MDIO_IN |
        SIUL2_0_PORT30_LPSPI1_LPSPI1_SOUT_IN |
        SIUL2_0_PORT31_GMAC1_GMAC1_PPS0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPUART0_LPUART0_RX_IN |
        SIUL2_0_PORT33_HSE_HSE_TAMPER_EXTIN0_IN |
        SIUL2_0_PORT34_LPSPI2_LPSPI2_SIN_IN |
        SIUL2_0_PORT35_GMAC0_GMAC0_MII_RGMII_TXD3_IN |
        SIUL2_0_PORT36_SAI0_SAI0_D1_IN |
        SIUL2_0_PORT37_TRGMUX_TRGMUX_IN0_IN |
        SIUL2_0_PORT40_LPUART1_LPUART1_DCD_B_IN |
        SIUL2_0_PORT41_LPUART1_LPUART1_RIN_B_IN |
        SIUL2_0_PORT43_LPUART0_LPUART0_DSR_B_IN |
        SIUL2_0_PORT44_LPUART0_LPUART0_DCD_B_IN |
        SIUL2_0_PORT45_LPUART0_LPUART0_RIN_B_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_PGI_PGOOD_IN |
        SIUL2_0_PORT49_LPSPI1_LPSPI1_PCS3_IN |
        SIUL2_0_PORT50_LPUART13_LPUART13_TX_IN |
        SIUL2_0_PORT51_GMAC0_GMAC0_MII_RMII_TX_EN_IN |
        SIUL2_0_PORT54_GMAC0_GMAC0_MII_CRS_IN |
        SIUL2_0_PORT55_LPUART1_LPUART1_RX_IN |
        SIUL2_0_PORT56_GMAC0_GMAC0_MII_RGMII_RXD2_IN |
        SIUL2_0_PORT57_GMAC0_GMAC0_MII_COL_IN |
        SIUL2_0_PORT58_GMAC0_GMAC0_MII_RX_CLK_IN |
        SIUL2_0_PORT59_LPUART5_LPUART5_TX_IN |
        SIUL2_0_PORT60_LPSPI2_LPSPI2_SIN_IN |
        SIUL2_0_PORT61_SAI0_SAI0_D1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC0_GMAC0_MII_RMII_TX_CLK_IN |
        SIUL2_0_PORT65_GMAC0_GMAC0_MII_RMII_RXD_0_IN |
        SIUL2_0_PORT66_LPSPI3_LPSPI3_PCS2_IN |
        SIUL2_0_PORT70_LPI2C1_LPI2C1_SDA_IN |
        SIUL2_0_PORT71_LPSPI0_LPSPI0_PCS0_IN |
        SIUL2_0_PORT72_LPSPI0_LPSPI0_SCK_IN |
        SIUL2_0_PORT73_LPSPI0_LPSPI0_SIN_IN |
        SIUL2_0_PORT74_TRGMUX_TRGMUX_IN11_IN |
        SIUL2_0_PORT75_LPUART11_LPUART11_RX_IN |
        SIUL2_0_PORT76_LPSPI2_LPSPI2_PCS1_IN |
        SIUL2_0_PORT77_LPUART10_LPUART10_TX_IN |
        SIUL2_0_PORT78_LPSPI2_LPSPI2_PCS0_IN |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPI2C1_LPI2C1_SDA_IN |
        SIUL2_0_PORT81_GMAC1_GMAC1_MII_RMII_RGMII_TXD_1_IN |
        SIUL2_0_PORT82_SAI0_SAI0_D2_IN |
        SIUL2_0_PORT83_LPUART7_LPUART7_TX_IN |
        SIUL2_0_PORT89_LPSPI4_LPSPI4_PCS1_IN |
        SIUL2_0_PORT90_LPUART13_LPUART13_RX_IN |
        SIUL2_0_PORT91_LPSPI4_LPSPI4_SCK_IN |
        SIUL2_0_PORT92_LPUART1_LPUART1_RIN_B_IN |
        SIUL2_0_PORT93_FXIO_FXIO_D22_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_LPSPI3_LPSPI3_SOUT_IN |
        SIUL2_0_PORT97_LPUART5_LPUART5_TX_IN |
        SIUL2_0_PORT98_LPSPI5_LPSPI5_SOUT_IN |
        SIUL2_0_PORT99_LPSPI1_LPSPI1_PCS0_IN |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_RX_CLK_IN |
        SIUL2_0_PORT102_LPSPI0_LPSPI0_PCS0_IN |
        SIUL2_0_PORT103_QUADSPI_QUADSPI_IOFA1_IN |
        SIUL2_0_PORT104_LPI2C1_LPI2C1_SDA_IN |
        SIUL2_0_PORT105_GMAC0_GMAC0_MII_RMII_RXD_0_IN |
        SIUL2_0_PORT106_GMAC0_GMAC0_MII_TXD3_IN |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_TXD2_IN |
        SIUL2_0_PORT108_GMAC0_GMAC0_MII_RMII_TX_EN_IN |
        SIUL2_0_PORT109_LPI2C0_LPI2C0_SDA_IN |
        SIUL2_0_PORT110_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN |
        SIUL2_0_PORT111_FXIO_FXIO_D6_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT113_LPUART2_LPUART2_RX_IN |
        SIUL2_0_PORT116_LPSPI3_LPSPI3_SIN_IN |
        SIUL2_0_PORT122_LPUART14_LPUART14_TX_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT130_LPSPI0_LPSPI0_SOUT_IN |
        SIUL2_0_PORT131_SAI1_SAI1_D0_IN |
        SIUL2_0_PORT132_LPSPI1_LPSPI1_PCS1_IN |
        SIUL2_0_PORT133_LPUART12_LPUART12_RX_IN |
        SIUL2_0_PORT136_LPSPI5_LPSPI5_PCS1_IN |
        SIUL2_0_PORT137_LPSPI5_LPSPI5_SOUT_IN |
        SIUL2_0_PORT138_LPSPI3_LPSPI3_SIN_IN |
        SIUL2_0_PORT139_LPUART4_LPUART4_TX_IN |
        SIUL2_0_PORT140_SAI1_SAI1_MCLK_IN |
        SIUL2_0_PORT142_LPUART5_LPUART5_TX_IN |
        SIUL2_0_PORT143_LPSPI2_LPSPI2_SCK_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPUART3_LPUART3_TX_IN |
        SIUL2_0_PORT152_LPSPI4_LPSPI4_PCS1_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191
        SIUL2_0_PORT180_LPUART8_LPUART8_TX_IN |
        SIUL2_0_PORT181_LPI2C0_LPI2C0_SDA_IN */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U)
                ),
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239
        SIUL2_0_PORT225_CAN6_CAN6_RX_IN */
        (uint16)( SHL_PAD_U32(1U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT7_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPUART0_LPUART0_CTS_IN |
        SIUL2_0_PORT2_LPSPI5_LPSPI5_SIN_IN |
        SIUL2_0_PORT3_LPUART0_LPUART0_TX_IN |
        SIUL2_0_PORT6_LPSPI3_LPSPI3_PCS1_IN |
        SIUL2_0_PORT12_LPSPI1_LPSPI1_PCS5_IN |
        SIUL2_0_PORT15_LPSPI5_LPSPI5_PCS0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPUART6_LPUART6_TX_IN |
        SIUL2_0_PORT18_LPUART1_LPUART1_TX_IN |
        SIUL2_0_PORT21_TRGMUX_TRGMUX_IN15_IN |
        SIUL2_0_PORT31_GMAC1_GMAC1_MII_CRS_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPI2C0_LPI2C0_SDAS_IN |
        SIUL2_0_PORT33_LPUART0_LPUART0_TX_IN |
        SIUL2_0_PORT34_SAI0_SAI0_D0_IN |
        SIUL2_0_PORT35_SAI0_SAI0_MCLK_IN |
        SIUL2_0_PORT36_TRGMUX_TRGMUX_IN1_IN |
        SIUL2_0_PORT45_LPUART8_LPUART8_TX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT49_LPSPI3_LPSPI3_PCS0_IN |
        SIUL2_0_PORT51_GMAC1_GMAC1_MII_RMII_RGMII_MDIO_IN |
        SIUL2_0_PORT54_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN |
        SIUL2_0_PORT55_GMAC0_GMAC0_MII_COL_IN |
        SIUL2_0_PORT56_GMAC0_GMAC0_MII_RGMII_RXD3_IN |
        SIUL2_0_PORT57_LPUART15_LPUART15_TX_IN |
        SIUL2_0_PORT59_GMAC1_GMAC1_MII_RMII_RX_ER_IN |
        SIUL2_0_PORT60_GMAC0_GMAC0_MII_RGMII_TXD2_IN |
        SIUL2_0_PORT61_LPUART6_LPUART6_TX_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC1_GMAC1_MII_RGMII_TXD2_IN |
        SIUL2_0_PORT65_GMAC0_GMAC0_MII_RMII_RXD_1_IN |
        SIUL2_0_PORT66_GMAC0_GMAC0_MII_RMII_TXD_0_IN |
        SIUL2_0_PORT70_LPSPI0_LPSPI0_PCS1_IN |
        SIUL2_0_PORT71_LPUART1_LPUART1_TX_IN |
        SIUL2_0_PORT72_LPUART0_LPUART0_CTS_IN |
        SIUL2_0_PORT73_LPUART1_LPUART1_TX_IN |
        SIUL2_0_PORT74_LPUART0_LPUART0_DSR_B_IN |
        SIUL2_0_PORT75_LPSPI4_LPSPI4_SOUT_IN |
        SIUL2_0_PORT76_SAI0_SAI0_BCLK_IN |
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_COL_IN |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPI2C1_LPI2C1_SDAS_IN |
        SIUL2_0_PORT89_CAN7_CAN7_RX_IN |
        SIUL2_0_PORT90_LPSPI4_LPSPI4_SIN_IN |
        SIUL2_0_PORT91_LPUART13_LPUART13_TX_IN |
        SIUL2_0_PORT93_LPUART0_LPUART0_RX_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT98_TRGMUX_TRGMUX_IN5_IN |
        SIUL2_0_PORT99_TRGMUX_TRGMUX_IN4_IN |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_TXD2_IN |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_RMII_TX_CLK_IN |
        SIUL2_0_PORT103_LPUART2_LPUART2_TX_IN |
        SIUL2_0_PORT104_LPSPI3_LPSPI3_SOUT_IN |
        SIUL2_0_PORT105_GMAC0_GMAC0_MII_RXD2_IN |
        SIUL2_0_PORT106_QUADSPI_QUADSPI_SCKFA_IN |
        SIUL2_0_PORT107_QUADSPI_QUADSPI_IOFA0_IN |
        SIUL2_0_PORT108_QUADSPI_QUADSPI_IOFA2_IN |
        SIUL2_0_PORT109_LPSPI5_LPSPI5_SIN_IN |
        SIUL2_0_PORT110_SAI0_SAI0_MCLK_IN |
        SIUL2_0_PORT111_FXIO_FXIO_D10_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT113_LPSPI3_LPSPI3_PCS0_IN */
        (uint16)( SHL_PAD_U32(1U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT130_LPUART1_LPUART1_CTS_IN |
        SIUL2_0_PORT131_TRGMUX_TRGMUX_IN6_IN |
        SIUL2_0_PORT132_LPUART12_LPUART12_TX_IN |
        SIUL2_0_PORT136_SAI1_SAI1_BCLK_IN |
        SIUL2_0_PORT137_GMAC0_GMAC0_MII_RMII_TX_EN_IN |
        SIUL2_0_PORT140_LPUART2_LPUART2_TX_IN |
        SIUL2_0_PORT142_GMAC1_GMAC1_PPS1_IN |
        SIUL2_0_PORT143_LPUART1_LPUART1_CTS_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191
        SIUL2_0_PORT181_LPSPI1_LPSPI1_PCS0_IN */
        (uint16)( SHL_PAD_U32(5U)
                ),
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT8_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT6_LPUART1_LPUART1_CTS_IN */
        (uint16)( SHL_PAD_U32(6U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPUART1_LPUART1_DSR_B_IN */
        (uint16)( SHL_PAD_U32(0U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPSPI0_LPSPI0_PCS0_IN |
        SIUL2_0_PORT34_TRGMUX_TRGMUX_IN3_IN |
        SIUL2_0_PORT35_TRGMUX_TRGMUX_IN2_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT54_GMAC0_GMAC0_MII_RGMII_RX_CLK_IN |
        SIUL2_0_PORT55_GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_IN |
        SIUL2_0_PORT57_GMAC0_GMAC0_RGMII_TXCTL_IN */
        (uint16)( SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT65_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_IN |
        SIUL2_0_PORT66_GMAC0_GMAC0_MII_RMII_TXD_1_IN |
        SIUL2_0_PORT70_LPSPI1_LPSPI1_PCS1_IN |
        SIUL2_0_PORT74_LPUART11_LPUART11_TX_IN |
        SIUL2_0_PORT75_TRGMUX_TRGMUX_IN10_IN |
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_RMII_RX_ER_IN |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPSPI3_LPSPI3_SIN_IN |
        SIUL2_0_PORT90_LPUART13_LPUART13_TX_IN |
        SIUL2_0_PORT93_LPI2C1_LPI2C1_SDA_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT98_LPUART3_LPUART3_TX_IN |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_TXD3_IN |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_TXD2_IN |
        SIUL2_0_PORT103_GMAC1_GMAC1_MII_RGMII_RXD2_IN |
        SIUL2_0_PORT104_GMAC0_GMAC0_MII_RMII_RXD_1_IN |
        SIUL2_0_PORT105_LPUART6_LPUART6_TX_IN |
        SIUL2_0_PORT106_GMAC1_GMAC1_MII_RGMII_RX_CLK_IN |
        SIUL2_0_PORT107_LPUART2_LPUART2_CTS_IN |
        SIUL2_0_PORT108_GMAC1_GMAC1_MII_RMII_RGMII_RXD_1_IN |
        SIUL2_0_PORT109_SAI1_SAI1_D0_IN |
        SIUL2_0_PORT110_SAI1_SAI1_MCLK_IN |
        SIUL2_0_PORT111_LPUART8_LPUART8_RX_IN */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT113_LPSPI5_LPSPI5_PCS0_IN */
        (uint16)( SHL_PAD_U32(1U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT131_GMAC1_GMAC1_PPS3_IN |
        SIUL2_0_PORT137_SAI0_SAI0_MCLK_IN */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT9_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT6_LPUART0_LPUART0_RIN_B_IN */
        (uint16)( SHL_PAD_U32(6U)
                ),
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47
        SIUL2_0_PORT35_LPUART9_LPUART9_TX_IN */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT54_LPUART1_LPUART1_TX_IN |
        SIUL2_0_PORT55_GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_IN */
        (uint16)( SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT65_GMAC0_GMAC0_MII_RX_CLK_IN |
        SIUL2_0_PORT66_QUADSPI_QUADSPI_IOFA3_IN |
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_IN |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RXD2_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN |
        SIUL2_0_PORT93_LPUART1_LPUART1_DCD_B_IN */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT101_SAI0_SAI0_D3_IN |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_TXD3_IN |
        SIUL2_0_PORT104_GMAC0_GMAC0_MII_RXD3_IN |
        SIUL2_0_PORT105_GMAC1_GMAC1_MII_RGMII_TXD3_IN |
        SIUL2_0_PORT107_GMAC1_GMAC1_RGMII_TXCTL_IN |
        SIUL2_0_PORT110_LPUART1_LPUART1_TX_IN |
        SIUL2_0_PORT111_LPSPI0_LPSPI0_SCK_IN */
        (uint16)( SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143
        SIUL2_0_PORT131_GMAC1_GMAC1_MII_COL_IN |
        SIUL2_0_PORT137_LPUART2_LPUART2_CTS_IN */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT10_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_IN */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT55_GMAC0_GMAC0_MII_RGMII_RXD2_IN */
        (uint16)( SHL_PAD_U32(7U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT65_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_IN |
        SIUL2_0_PORT66_GMAC1_GMAC1_MII_RGMII_RXD3_IN |
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_RGMII_RXD2_IN |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RGMII_RXD3_IN */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_GMAC0_GMAC0_MII_RMII_RX_ER_IN */
        (uint16)( SHL_PAD_U32(0U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT101_TRGMUX_TRGMUX_IN7_IN |
        SIUL2_0_PORT102_SAI0_SAI0_D2_IN |
        SIUL2_0_PORT104_GMAC1_GMAC1_MII_RMII_RGMII_TXD_0_IN |
        SIUL2_0_PORT110_GMAC1_GMAC1_MII_COL_IN |
        SIUL2_0_PORT111_SAI1_SAI1_SYNC_IN */
        (uint16)( SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT11_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_RGMII_RXD3_IN |
        SIUL2_0_PORT79_TRGMUX_TRGMUX_IN8_IN */
        (uint16)( SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_GMAC0_GMAC0_MII_RGMII_RX_CLK_IN */
        (uint16)( SHL_PAD_U32(0U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT101_GMAC1_GMAC1_MII_RMII_RX_DV_RGMII_RXCTL_IN |
        SIUL2_0_PORT102_GMAC1_GMAC1_MII_RMII_RGMII_RXD_0_IN |
        SIUL2_0_PORT111_LPUART2_LPUART2_CTS_IN */
        (uint16)( SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT12_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79
        SIUL2_0_PORT78_TRGMUX_TRGMUX_IN9_IN |
        SIUL2_0_PORT79_LPUART2_LPUART2_TX_IN */
        (uint16)( SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT111_GMAC1_GMAC1_MII_CRS_IN */
        (uint16)( SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT13_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT14_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INPUT15_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT1_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPSPI4_LPSPI4_PCS2_INOUT |
        SIUL2_0_PORT1_LPSPI4_LPSPI4_PCS1_INOUT |
        SIUL2_0_PORT7_LPUART3_LPUART3_TX_INOUT |
        SIUL2_0_PORT12_LPSPI1_LPSPI1_PCS5_INOUT |
        SIUL2_0_PORT13_LPSPI1_LPSPI1_PCS4_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI4_LPSPI4_PCS3_INOUT |
        SIUL2_0_PORT21_LPSPI2_LPSPI2_PCS2_INOUT |
        SIUL2_0_PORT27_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT31_GMAC0_GMAC0_PPS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPI2C0_LPI2C0_SDAS_INOUT |
        SIUL2_0_PORT33_LPI2C0_LPI2C0_SCLS_INOUT |
        SIUL2_0_PORT35_LPUART9_LPUART9_TX_INOUT |
        SIUL2_0_PORT40_LPSPI4_LPSPI4_PCS0_INOUT |
        SIUL2_0_PORT41_LPSPI4_LPSPI4_SOUT_INOUT |
        SIUL2_0_PORT42_LPSPI4_LPSPI4_SCK_INOUT |
        SIUL2_0_PORT43_LPSPI4_LPSPI4_SIN_INOUT |
        SIUL2_0_PORT44_LPSPI3_LPSPI3_PCS3_INOUT |
        SIUL2_0_PORT45_LPSPI3_LPSPI3_PCS2_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT50_LPUART13_LPUART13_TX_INOUT |
        SIUL2_0_PORT51_GMAC0_GMAC0_PPS0_INOUT |
        SIUL2_0_PORT52_LPUART14_LPUART14_TX_INOUT |
        SIUL2_0_PORT57_LPUART15_LPUART15_TX_INOUT |
        SIUL2_0_PORT59_LPUART5_LPUART5_TX_INOUT |
        SIUL2_0_PORT61_LPUART6_LPUART6_TX_INOUT |
        SIUL2_0_PORT63_EMIOS_0_EMIOS_0_CH_19_Y_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT66_GMAC0_GMAC0_MII_RMII_TXD_1_INOUT |
        SIUL2_0_PORT70_LPI2C1_LPI2C1_SDA_INOUT |
        SIUL2_0_PORT71_FXIO_FXIO_D10_INOUT |
        SIUL2_0_PORT72_LPI2C0_LPI2C0_SCL_INOUT |
        SIUL2_0_PORT73_LPI2C0_LPI2C0_SDA_INOUT |
        SIUL2_0_PORT74_EMIOS_0_EMIOS_0_CH_6_G_INOUT |
        SIUL2_0_PORT77_LPUART10_LPUART10_TX_INOUT |
        SIUL2_0_PORT78_GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPSPI3_LPSPI3_SIN_INOUT |
        SIUL2_0_PORT81_LPSPI3_LPSPI3_SCK_INOUT |
        SIUL2_0_PORT83_LPUART7_LPUART7_TX_INOUT |
        SIUL2_0_PORT85_GMAC0_GMAC0_PPS1_INOUT |
        SIUL2_0_PORT86_EMIOS_0_EMIOS_0_CH_8_X_INOUT |
        SIUL2_0_PORT88_LPUART12_LPUART12_TX_INOUT |
        SIUL2_0_PORT90_LPUART13_LPUART13_TX_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT97_LPUART5_LPUART5_TX_INOUT |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_TXD2_INOUT |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_TXD3_INOUT |
        SIUL2_0_PORT103_GMAC0_GMAC0_MII_RMII_TXD_0_INOUT |
        SIUL2_0_PORT104_LPSPI3_LPSPI3_SOUT_INOUT |
        SIUL2_0_PORT106_GMAC0_GMAC0_MII_TXD3_INOUT |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_TXD2_INOUT |
        SIUL2_0_PORT108_GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT |
        SIUL2_0_PORT109_LPSPI5_LPSPI5_SIN_INOUT |
        SIUL2_0_PORT110_LPSPI5_LPSPI5_SCK_INOUT |
        SIUL2_0_PORT111_FXIO_FXIO_D6_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT113_LPSPI5_LPSPI5_PCS0_INOUT |
        SIUL2_0_PORT122_LPUART14_LPUART14_TX_INOUT |
        SIUL2_0_PORT124_LPUART15_LPUART15_TX_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT132_LPSPI0_LPSPI0_PCS0_INOUT |
        SIUL2_0_PORT136_LPSPI3_LPSPI3_PCS1_INOUT |
        SIUL2_0_PORT137_LPSPI5_LPSPI5_SOUT_INOUT |
        SIUL2_0_PORT139_LPUART4_LPUART4_TX_INOUT |
        SIUL2_0_PORT142_EMIOS_0_EMIOS_0_CH_19_Y_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175
        SIUL2_0_PORT160_LPUART5_LPUART5_TX_INOUT |
        SIUL2_0_PORT162_LPUART6_LPUART6_TX_INOUT |
        SIUL2_0_PORT167_LPSPI2_LPSPI2_PCS0_INOUT |
        SIUL2_0_PORT172_LPUART10_LPUART10_TX_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_LPUART12_LPUART12_TX_INOUT |
        SIUL2_0_PORT178_LPUART7_LPUART7_TX_INOUT |
        SIUL2_0_PORT180_LPUART8_LPUART8_TX_INOUT |
        SIUL2_0_PORT183_LPUART9_LPUART9_TX_INOUT |
        SIUL2_0_PORT187_LPUART11_LPUART11_TX_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_LPUART13_LPUART13_TX_INOUT |
        SIUL2_0_PORT194_LPUART14_LPUART14_TX_INOUT |
        SIUL2_0_PORT196_LPUART15_LPUART15_TX_INOUT |
        SIUL2_0_PORT202_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT203_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT206_LPSPI2_LPSPI2_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT216_LPUART12_LPUART12_TX_INOUT |
        SIUL2_0_PORT220_LPSPI5_LPSPI5_PCS0_INOUT |
        SIUL2_0_PORT221_LPSPI5_LPSPI5_SIN_INOUT |
        SIUL2_0_PORT222_LPSPI5_LPSPI5_SOUT_INOUT |
        SIUL2_0_PORT223_LPSPI5_LPSPI5_SCK_INOUT */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT228_LPUART4_LPUART4_TX_INOUT |
        SIUL2_0_PORT230_LPUART8_LPUART8_TX_INOUT |
        SIUL2_0_PORT232_LPUART10_LPUART10_TX_INOUT |
        SIUL2_0_PORT234_LPUART11_LPUART11_TX_INOUT |
        SIUL2_0_PORT237_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT238_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT239_FXIO_FXIO_D2_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT240_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT241_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT242_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT243_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT244_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT249_EMIOS_0_EMIOS_0_CH_1_G_INOUT |
        SIUL2_0_PORT250_EMIOS_0_EMIOS_0_CH_2_G_INOUT |
        SIUL2_0_PORT251_EMIOS_0_EMIOS_0_CH_3_G_INOUT |
        SIUL2_0_PORT252_EMIOS_0_EMIOS_0_CH_4_G_INOUT |
        SIUL2_0_PORT253_EMIOS_0_EMIOS_0_CH_5_G_INOUT |
        SIUL2_0_PORT254_EMIOS_0_EMIOS_0_CH_6_G_INOUT |
        SIUL2_0_PORT255_EMIOS_0_EMIOS_0_CH_7_G_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT256_FXIO_FXIO_D8_INOUT |
        SIUL2_0_PORT257_FXIO_FXIO_D9_INOUT |
        SIUL2_0_PORT258_FXIO_FXIO_D10_INOUT |
        SIUL2_0_PORT259_FXIO_FXIO_D11_INOUT |
        SIUL2_0_PORT260_FXIO_FXIO_D12_INOUT |
        SIUL2_0_PORT261_FXIO_FXIO_D13_INOUT |
        SIUL2_0_PORT262_FXIO_FXIO_D14_INOUT |
        SIUL2_0_PORT263_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT268_EMIOS_0_EMIOS_0_CH_13_H_INOUT |
        SIUL2_0_PORT269_EMIOS_0_EMIOS_0_CH_8_X_INOUT |
        SIUL2_0_PORT270_EMIOS_0_EMIOS_0_CH_9_H_INOUT |
        SIUL2_0_PORT271_EMIOS_0_EMIOS_0_CH_10_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_EMIOS_0_EMIOS_0_CH_11_H_INOUT |
        SIUL2_0_PORT273_EMIOS_0_EMIOS_0_CH_12_H_INOUT |
        SIUL2_0_PORT274_EMIOS_0_EMIOS_0_CH_14_H_INOUT |
        SIUL2_0_PORT275_EMIOS_0_EMIOS_0_CH_15_H_INOUT |
        SIUL2_0_PORT276_EMIOS_0_EMIOS_0_CH_16_X_INOUT |
        SIUL2_0_PORT277_EMIOS_0_EMIOS_0_CH_17_Y_INOUT |
        SIUL2_0_PORT278_EMIOS_0_EMIOS_0_CH_18_Y_INOUT |
        SIUL2_0_PORT279_EMIOS_0_EMIOS_0_CH_19_Y_INOUT |
        SIUL2_0_PORT280_EMIOS_0_EMIOS_0_CH_20_Y_INOUT |
        SIUL2_0_PORT281_EMIOS_0_EMIOS_0_CH_21_Y_INOUT |
        SIUL2_0_PORT282_EMIOS_0_EMIOS_0_CH_22_X_INOUT |
        SIUL2_0_PORT283_EMIOS_0_EMIOS_0_CH_23_X_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT288_FXIO_FXIO_D16_INOUT |
        SIUL2_0_PORT289_FXIO_FXIO_D17_INOUT |
        SIUL2_0_PORT290_FXIO_FXIO_D18_INOUT |
        SIUL2_0_PORT291_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT292_FXIO_FXIO_D20_INOUT |
        SIUL2_0_PORT293_FXIO_FXIO_D21_INOUT |
        SIUL2_0_PORT294_FXIO_FXIO_D22_INOUT |
        SIUL2_0_PORT295_FXIO_FXIO_D23_INOUT |
        SIUL2_0_PORT300_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT301_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT302_EMIOS_1_EMIOS_1_CH_2_H_INOUT |
        SIUL2_0_PORT303_EMIOS_1_EMIOS_1_CH_3_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT305_EMIOS_1_EMIOS_1_CH_6_H_INOUT |
        SIUL2_0_PORT306_EMIOS_1_EMIOS_1_CH_7_H_INOUT |
        SIUL2_0_PORT307_EMIOS_1_EMIOS_1_CH_8_X_INOUT |
        SIUL2_0_PORT308_EMIOS_1_EMIOS_1_CH_9_H_INOUT |
        SIUL2_0_PORT309_EMIOS_1_EMIOS_1_CH_10_H_INOUT |
        SIUL2_0_PORT310_EMIOS_1_EMIOS_1_CH_11_H_INOUT |
        SIUL2_0_PORT311_EMIOS_1_EMIOS_1_CH_12_H_INOUT |
        SIUL2_0_PORT312_EMIOS_1_EMIOS_1_CH_13_H_INOUT |
        SIUL2_0_PORT313_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT314_EMIOS_1_EMIOS_1_CH_14_H_INOUT |
        SIUL2_0_PORT315_EMIOS_1_EMIOS_1_CH_15_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_FXIO_FXIO_D24_INOUT |
        SIUL2_0_PORT321_FXIO_FXIO_D25_INOUT |
        SIUL2_0_PORT322_FXIO_FXIO_D26_INOUT |
        SIUL2_0_PORT323_FXIO_FXIO_D27_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_INOUT2_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_EMIOS_0_EMIOS_0_CH_17_Y_INOUT |
        SIUL2_0_PORT1_EMIOS_0_EMIOS_0_CH_9_H_INOUT |
        SIUL2_0_PORT2_EMIOS_1_EMIOS_1_CH_19_Y_INOUT |
        SIUL2_0_PORT3_EMIOS_1_EMIOS_1_CH_20_Y_INOUT |
        SIUL2_0_PORT7_LPSPI0_LPSPI0_PCS1_INOUT |
        SIUL2_0_PORT8_EMIOS_1_EMIOS_1_CH_12_H_INOUT |
        SIUL2_0_PORT9_LPUART2_LPUART2_TX_INOUT |
        SIUL2_0_PORT10_EMIOS_0_EMIOS_0_CH_12_H_INOUT |
        SIUL2_0_PORT11_EMIOS_0_EMIOS_0_CH_13_H_INOUT |
        SIUL2_0_PORT12_EMIOS_0_EMIOS_0_CH_14_H_INOUT |
        SIUL2_0_PORT13_EMIOS_0_EMIOS_0_CH_15_H_INOUT |
        SIUL2_0_PORT14_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT15_EMIOS_0_EMIOS_0_CH_10_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_EMIOS_0_EMIOS_0_CH_11_H_INOUT |
        SIUL2_0_PORT17_EMIOS_0_EMIOS_0_CH_6_G_INOUT |
        SIUL2_0_PORT18_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT19_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT20_EMIOS_1_EMIOS_1_CH_2_H_INOUT |
        SIUL2_0_PORT21_EMIOS_1_EMIOS_1_CH_3_H_INOUT |
        SIUL2_0_PORT22_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT23_EMIOS_1_EMIOS_1_CH_6_H_INOUT |
        SIUL2_0_PORT26_EMIOS_1_EMIOS_1_CH_9_H_INOUT |
        SIUL2_0_PORT27_EMIOS_1_EMIOS_1_CH_10_H_INOUT |
        SIUL2_0_PORT28_EMIOS_1_EMIOS_1_CH_11_H_INOUT |
        SIUL2_0_PORT29_EMIOS_1_EMIOS_1_CH_12_H_INOUT |
        SIUL2_0_PORT30_EMIOS_1_EMIOS_1_CH_13_H_INOUT |
        SIUL2_0_PORT31_EMIOS_1_EMIOS_1_CH_14_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_FXIO_FXIO_D14_INOUT |
        SIUL2_0_PORT33_LPUART0_LPUART0_TX_INOUT |
        SIUL2_0_PORT34_EMIOS_0_EMIOS_0_CH_8_X_INOUT |
        SIUL2_0_PORT35_EMIOS_0_EMIOS_0_CH_9_H_INOUT |
        SIUL2_0_PORT36_EMIOS_0_EMIOS_0_CH_4_G_INOUT |
        SIUL2_0_PORT37_EMIOS_0_EMIOS_0_CH_5_G_INOUT |
        SIUL2_0_PORT40_EMIOS_1_EMIOS_1_CH_15_H_INOUT |
        SIUL2_0_PORT41_EMIOS_1_EMIOS_1_CH_16_X_INOUT |
        SIUL2_0_PORT42_EMIOS_1_EMIOS_1_CH_17_Y_INOUT |
        SIUL2_0_PORT43_EMIOS_1_EMIOS_1_CH_18_Y_INOUT |
        SIUL2_0_PORT44_EMIOS_0_EMIOS_0_CH_0_X_INOUT |
        SIUL2_0_PORT45_EMIOS_0_EMIOS_0_CH_1_G_INOUT |
        SIUL2_0_PORT46_EMIOS_0_EMIOS_0_CH_2_G_INOUT |
        SIUL2_0_PORT47_EMIOS_0_EMIOS_0_CH_3_G_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_EMIOS_0_EMIOS_0_CH_4_G_INOUT |
        SIUL2_0_PORT49_EMIOS_0_EMIOS_0_CH_5_G_INOUT |
        SIUL2_0_PORT50_EMIOS_1_EMIOS_1_CH_15_H_INOUT |
        SIUL2_0_PORT51_EMIOS_1_EMIOS_1_CH_15_H_INOUT |
        SIUL2_0_PORT52_EMIOS_1_EMIOS_1_CH_16_X_INOUT |
        SIUL2_0_PORT53_EMIOS_1_EMIOS_1_CH_17_Y_INOUT |
        SIUL2_0_PORT54_EMIOS_1_EMIOS_1_CH_18_Y_INOUT |
        SIUL2_0_PORT55_EMIOS_1_EMIOS_1_CH_19_Y_INOUT |
        SIUL2_0_PORT56_EMIOS_1_EMIOS_1_CH_20_Y_INOUT |
        SIUL2_0_PORT57_EMIOS_1_EMIOS_1_CH_21_Y_INOUT |
        SIUL2_0_PORT58_EMIOS_1_EMIOS_1_CH_22_X_INOUT |
        SIUL2_0_PORT59_EMIOS_1_EMIOS_1_CH_23_X_INOUT |
        SIUL2_0_PORT60_GMAC0_GMAC0_MII_RGMII_TXD2_INOUT |
        SIUL2_0_PORT61_GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_EMIOS_0_EMIOS_0_CH_0_X_INOUT |
        SIUL2_0_PORT65_EMIOS_0_EMIOS_0_CH_1_G_INOUT |
        SIUL2_0_PORT66_EMIOS_0_EMIOS_0_CH_2_G_INOUT |
        SIUL2_0_PORT67_EMIOS_0_EMIOS_0_CH_3_G_INOUT |
        SIUL2_0_PORT68_EMIOS_0_EMIOS_0_CH_8_X_INOUT |
        SIUL2_0_PORT69_EMIOS_0_EMIOS_0_CH_16_X_INOUT |
        SIUL2_0_PORT70_FXIO_FXIO_D11_INOUT |
        SIUL2_0_PORT71_LPUART1_LPUART1_TX_INOUT |
        SIUL2_0_PORT73_LPUART1_LPUART1_TX_INOUT |
        SIUL2_0_PORT74_LPUART11_LPUART11_TX_INOUT |
        SIUL2_0_PORT76_EMIOS_1_EMIOS_1_CH_2_H_INOUT |
        SIUL2_0_PORT77_EMIOS_1_EMIOS_1_CH_3_H_INOUT |
        SIUL2_0_PORT78_EMIOS_0_EMIOS_0_CH_10_H_INOUT |
        SIUL2_0_PORT79_EMIOS_0_EMIOS_0_CH_11_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_EMIOS_1_EMIOS_1_CH_9_H_INOUT |
        SIUL2_0_PORT82_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT88_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT89_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT90_EMIOS_1_EMIOS_1_CH_3_H_INOUT |
        SIUL2_0_PORT91_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT92_EMIOS_1_EMIOS_1_CH_7_H_INOUT |
        SIUL2_0_PORT93_EMIOS_1_EMIOS_1_CH_10_H_INOUT |
        SIUL2_0_PORT94_EMIOS_1_EMIOS_1_CH_12_H_INOUT |
        SIUL2_0_PORT95_EMIOS_1_EMIOS_1_CH_14_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_EMIOS_0_EMIOS_0_CH_2_G_INOUT |
        SIUL2_0_PORT97_EMIOS_0_EMIOS_0_CH_3_G_INOUT |
        SIUL2_0_PORT98_EMIOS_1_EMIOS_1_CH_21_Y_INOUT |
        SIUL2_0_PORT99_EMIOS_1_EMIOS_1_CH_22_X_INOUT |
        SIUL2_0_PORT100_EMIOS_1_EMIOS_1_CH_23_X_INOUT |
        SIUL2_0_PORT101_EMIOS_0_EMIOS_0_CH_19_Y_INOUT |
        SIUL2_0_PORT102_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT103_LPUART2_LPUART2_TX_INOUT |
        SIUL2_0_PORT104_LPI2C1_LPI2C1_SDA_INOUT |
        SIUL2_0_PORT105_LPI2C1_LPI2C1_SCL_INOUT |
        SIUL2_0_PORT106_EMIOS_0_EMIOS_0_CH_16_X_INOUT |
        SIUL2_0_PORT107_EMIOS_0_EMIOS_0_CH_17_Y_INOUT |
        SIUL2_0_PORT108_EMIOS_0_EMIOS_0_CH_18_Y_INOUT |
        SIUL2_0_PORT109_EMIOS_0_EMIOS_0_CH_20_Y_INOUT |
        SIUL2_0_PORT110_EMIOS_0_EMIOS_0_CH_21_Y_INOUT |
        SIUL2_0_PORT111_EMIOS_0_EMIOS_0_CH_0_X_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_EMIOS_0_EMIOS_0_CH_1_G_INOUT |
        SIUL2_0_PORT113_EMIOS_0_EMIOS_0_CH_18_Y_INOUT |
        SIUL2_0_PORT114_EMIOS_1_EMIOS_1_CH_15_H_INOUT |
        SIUL2_0_PORT115_EMIOS_1_EMIOS_1_CH_16_X_INOUT |
        SIUL2_0_PORT116_EMIOS_1_EMIOS_1_CH_17_Y_INOUT |
        SIUL2_0_PORT117_EMIOS_1_EMIOS_1_CH_18_Y_INOUT |
        SIUL2_0_PORT118_EMIOS_1_EMIOS_1_CH_19_Y_INOUT |
        SIUL2_0_PORT119_EMIOS_1_EMIOS_1_CH_20_Y_INOUT |
        SIUL2_0_PORT120_EMIOS_1_EMIOS_1_CH_21_Y_INOUT |
        SIUL2_0_PORT121_EMIOS_1_EMIOS_1_CH_22_X_INOUT |
        SIUL2_0_PORT122_EMIOS_1_EMIOS_1_CH_23_X_INOUT |
        SIUL2_0_PORT127_LPSPI5_LPSPI5_SCK_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_LPSPI0_LPSPI0_SIN_INOUT |
        SIUL2_0_PORT129_LPSPI0_LPSPI0_SCK_INOUT |
        SIUL2_0_PORT130_LPSPI0_LPSPI0_SOUT_INOUT |
        SIUL2_0_PORT131_SAI1_SAI1_D0_INOUT |
        SIUL2_0_PORT132_LPSPI1_LPSPI1_PCS1_INOUT |
        SIUL2_0_PORT134_LPSPI0_LPSPI0_PCS2_INOUT |
        SIUL2_0_PORT135_EMIOS_0_EMIOS_0_CH_7_G_INOUT |
        SIUL2_0_PORT136_EMIOS_0_EMIOS_0_CH_6_G_INOUT |
        SIUL2_0_PORT137_EMIOS_0_EMIOS_0_CH_7_G_INOUT |
        SIUL2_0_PORT138_LPSPI3_LPSPI3_SIN_INOUT |
        SIUL2_0_PORT139_LPSPI2_LPSPI2_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPUART3_LPUART3_TX_INOUT |
        SIUL2_0_PORT147_EMIOS_0_EMIOS_0_CH_22_X_INOUT |
        SIUL2_0_PORT148_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT149_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT150_EMIOS_1_EMIOS_1_CH_2_H_INOUT |
        SIUL2_0_PORT151_EMIOS_1_EMIOS_1_CH_3_H_INOUT |
        SIUL2_0_PORT152_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT153_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT154_EMIOS_1_EMIOS_1_CH_6_H_INOUT |
        SIUL2_0_PORT155_EMIOS_1_EMIOS_1_CH_7_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_EMIOS_2_EMIOS_2_CH_0_X_INOUT |
        SIUL2_0_PORT161_EMIOS_2_EMIOS_2_CH_1_H_INOUT |
        SIUL2_0_PORT162_EMIOS_2_EMIOS_2_CH_2_H_INOUT |
        SIUL2_0_PORT163_EMIOS_2_EMIOS_2_CH_3_H_INOUT |
        SIUL2_0_PORT164_EMIOS_2_EMIOS_2_CH_4_H_INOUT |
        SIUL2_0_PORT165_EMIOS_2_EMIOS_2_CH_5_H_INOUT |
        SIUL2_0_PORT166_EMIOS_2_EMIOS_2_CH_6_H_INOUT |
        SIUL2_0_PORT167_EMIOS_2_EMIOS_2_CH_7_H_INOUT |
        SIUL2_0_PORT168_EMIOS_2_EMIOS_2_CH_8_X_INOUT |
        SIUL2_0_PORT169_EMIOS_2_EMIOS_2_CH_9_H_INOUT |
        SIUL2_0_PORT170_EMIOS_2_EMIOS_2_CH_10_H_INOUT |
        SIUL2_0_PORT171_EMIOS_2_EMIOS_2_CH_11_H_INOUT |
        SIUL2_0_PORT172_EMIOS_2_EMIOS_2_CH_12_H_INOUT |
        SIUL2_0_PORT173_EMIOS_2_EMIOS_2_CH_13_H_INOUT |
        SIUL2_0_PORT174_EMIOS_2_EMIOS_2_CH_14_H_INOUT |
        SIUL2_0_PORT175_EMIOS_2_EMIOS_2_CH_15_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_EMIOS_2_EMIOS_2_CH_16_X_INOUT |
        SIUL2_0_PORT177_EMIOS_2_EMIOS_2_CH_17_Y_INOUT |
        SIUL2_0_PORT178_EMIOS_2_EMIOS_2_CH_18_Y_INOUT |
        SIUL2_0_PORT179_EMIOS_2_EMIOS_2_CH_19_Y_INOUT |
        SIUL2_0_PORT180_EMIOS_2_EMIOS_2_CH_20_Y_INOUT |
        SIUL2_0_PORT181_EMIOS_2_EMIOS_2_CH_21_Y_INOUT |
        SIUL2_0_PORT182_EMIOS_2_EMIOS_2_CH_22_X_INOUT |
        SIUL2_0_PORT183_EMIOS_2_EMIOS_2_CH_23_X_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT198_FXIO_FXIO_D10_INOUT |
        SIUL2_0_PORT199_FXIO_FXIO_D11_INOUT |
        SIUL2_0_PORT200_FXIO_FXIO_D12_INOUT |
        SIUL2_0_PORT201_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT205_FXIO_FXIO_D13_INOUT |
        SIUL2_0_PORT206_LPSPI2_LPSPI2_PCS2_INOUT |
        SIUL2_0_PORT207_FXIO_FXIO_D14_INOUT */
        (uint16)( SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_EMIOS_2_EMIOS_2_CH_16_X_INOUT |
        SIUL2_0_PORT209_EMIOS_2_EMIOS_2_CH_17_Y_INOUT |
        SIUL2_0_PORT210_EMIOS_2_EMIOS_2_CH_18_Y_INOUT |
        SIUL2_0_PORT211_EMIOS_2_EMIOS_2_CH_19_Y_INOUT |
        SIUL2_0_PORT212_EMIOS_2_EMIOS_2_CH_20_Y_INOUT |
        SIUL2_0_PORT213_EMIOS_2_EMIOS_2_CH_21_Y_INOUT |
        SIUL2_0_PORT214_EMIOS_2_EMIOS_2_CH_22_X_INOUT |
        SIUL2_0_PORT215_EMIOS_2_EMIOS_2_CH_23_X_INOUT |
        SIUL2_0_PORT216_LPSPI5_LPSPI5_PCS2_INOUT |
        SIUL2_0_PORT217_LPSPI5_LPSPI5_SOUT_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_LPUART0_LPUART0_TX_INOUT |
        SIUL2_0_PORT226_LPUART3_LPUART3_TX_INOUT |
        SIUL2_0_PORT232_LPUART2_LPUART2_TX_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 240 - 255
        SIUL2_0_PORT241_LPUART14_LPUART14_TX_INOUT |
        SIUL2_0_PORT243_LPUART15_LPUART15_TX_INOUT |
        SIUL2_0_PORT245_EMIOS_2_EMIOS_2_CH_17_Y_INOUT |
        SIUL2_0_PORT246_EMIOS_2_EMIOS_2_CH_18_Y_INOUT |
        SIUL2_0_PORT248_EMIOS_0_EMIOS_0_CH_0_X_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 256 - 271
        SIUL2_0_PORT258_LPUART13_LPUART13_TX_INOUT |
        SIUL2_0_PORT260_LPUART14_LPUART14_TX_INOUT |
        SIUL2_0_PORT268_LPUART9_LPUART9_TX_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT281_LPUART9_LPUART9_TX_INOUT |
        SIUL2_0_PORT284_EMIOS_2_EMIOS_2_CH_9_H_INOUT |
        SIUL2_0_PORT285_EMIOS_2_EMIOS_2_CH_10_H_INOUT |
        SIUL2_0_PORT286_EMIOS_2_EMIOS_2_CH_11_H_INOUT |
        SIUL2_0_PORT287_EMIOS_2_EMIOS_2_CH_12_H_INOUT */
        (uint16)( SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT289_EMIOS_2_EMIOS_2_CH_19_Y_INOUT |
        SIUL2_0_PORT290_EMIOS_2_EMIOS_2_CH_20_Y_INOUT |
        SIUL2_0_PORT291_EMIOS_2_EMIOS_2_CH_21_Y_INOUT |
        SIUL2_0_PORT292_EMIOS_2_EMIOS_2_CH_22_X_INOUT |
        SIUL2_0_PORT293_EMIOS_2_EMIOS_2_CH_23_X_INOUT |
        SIUL2_0_PORT294_EMIOS_2_EMIOS_2_CH_13_H_INOUT |
        SIUL2_0_PORT295_EMIOS_2_EMIOS_2_CH_14_H_INOUT |
        SIUL2_0_PORT296_EMIOS_2_EMIOS_2_CH_15_H_INOUT |
        SIUL2_0_PORT297_EMIOS_2_EMIOS_2_CH_16_X_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT316_EMIOS_1_EMIOS_1_CH_16_X_INOUT |
        SIUL2_0_PORT317_EMIOS_1_EMIOS_1_CH_17_Y_INOUT |
        SIUL2_0_PORT318_EMIOS_1_EMIOS_1_CH_18_Y_INOUT |
        SIUL2_0_PORT319_EMIOS_1_EMIOS_1_CH_19_Y_INOUT */
        (uint16)( SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_EMIOS_1_EMIOS_1_CH_20_Y_INOUT |
        SIUL2_0_PORT321_EMIOS_1_EMIOS_1_CH_21_Y_INOUT |
        SIUL2_0_PORT322_EMIOS_1_EMIOS_1_CH_22_X_INOUT |
        SIUL2_0_PORT323_EMIOS_1_EMIOS_1_CH_23_X_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U)
                )
    }
    ,
    /*  Mode PORT_INOUT3_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT3_LPSPI1_LPSPI1_SCK_INOUT |
        SIUL2_0_PORT4_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT6_LPSPI1_LPSPI1_PCS1_INOUT |
        SIUL2_0_PORT7_EMIOS_1_EMIOS_1_CH_11_H_INOUT |
        SIUL2_0_PORT8_LPSPI2_LPSPI2_SOUT_INOUT |
        SIUL2_0_PORT9_LPSPI2_LPSPI2_PCS0_INOUT |
        SIUL2_0_PORT11_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT14_LPSPI1_LPSPI1_PCS3_INOUT |
        SIUL2_0_PORT15_LPSPI0_LPSPI0_PCS3_INOUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI1_LPSPI1_PCS2_INOUT |
        SIUL2_0_PORT18_LPUART1_LPUART1_TX_INOUT |
        SIUL2_0_PORT21_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT22_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT23_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT26_LPSPI1_LPSPI1_PCS0_INOUT |
        SIUL2_0_PORT27_GMAC0_GMAC0_PPS1_INOUT |
        SIUL2_0_PORT28_LPSPI1_LPSPI1_SCK_INOUT |
        SIUL2_0_PORT29_GMAC0_GMAC0_PPS2_INOUT |
        SIUL2_0_PORT30_LPSPI1_LPSPI1_SOUT_INOUT |
        SIUL2_0_PORT31_FXIO_FXIO_D0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_LPSPI0_LPSPI0_PCS0_INOUT |
        SIUL2_0_PORT33_LPSPI0_LPSPI0_SOUT_INOUT |
        SIUL2_0_PORT34_LPSPI2_LPSPI2_SIN_INOUT |
        SIUL2_0_PORT35_LPSPI2_LPSPI2_SOUT_INOUT |
        SIUL2_0_PORT36_LPSPI0_LPSPI0_SOUT_INOUT |
        SIUL2_0_PORT37_LPSPI0_LPSPI0_PCS1_INOUT |
        SIUL2_0_PORT45_FXIO_FXIO_D8_INOUT |
        SIUL2_0_PORT46_LPSPI1_LPSPI1_SCK_INOUT |
        SIUL2_0_PORT47_LPSPI1_LPSPI1_SIN_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_LPSPI1_LPSPI1_SOUT_INOUT |
        SIUL2_0_PORT49_LPSPI1_LPSPI1_PCS3_INOUT |
        SIUL2_0_PORT50_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT51_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT52_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT53_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT54_LPSPI3_LPSPI3_PCS1_INOUT |
        SIUL2_0_PORT55_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT56_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT57_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT58_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT59_FXIO_FXIO_D8_INOUT |
        SIUL2_0_PORT60_FXIO_FXIO_D9_INOUT |
        SIUL2_0_PORT61_FXIO_FXIO_D10_INOUT |
        SIUL2_0_PORT62_FXIO_FXIO_D11_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT66_LPSPI3_LPSPI3_PCS2_INOUT |
        SIUL2_0_PORT70_LPSPI1_LPSPI1_PCS1_INOUT |
        SIUL2_0_PORT71_LPI2C1_LPI2C1_SCL_INOUT |
        SIUL2_0_PORT75_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT76_EMIOS_0_EMIOS_0_CH_22_X_INOUT |
        SIUL2_0_PORT77_EMIOS_0_EMIOS_0_CH_23_X_INOUT |
        SIUL2_0_PORT78_LPSPI2_LPSPI2_PCS0_INOUT |
        SIUL2_0_PORT79_LPSPI2_LPSPI2_SCK_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_EMIOS_2_EMIOS_2_CH_9_H_INOUT |
        SIUL2_0_PORT82_FXIO_FXIO_D12_INOUT |
        SIUL2_0_PORT83_FXIO_FXIO_D13_INOUT |
        SIUL2_0_PORT84_FXIO_FXIO_D14_INOUT |
        SIUL2_0_PORT85_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT87_FXIO_FXIO_D16_INOUT |
        SIUL2_0_PORT88_FXIO_FXIO_D17_INOUT |
        SIUL2_0_PORT89_FXIO_FXIO_D18_INOUT |
        SIUL2_0_PORT90_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT91_FXIO_FXIO_D20_INOUT |
        SIUL2_0_PORT92_FXIO_FXIO_D21_INOUT |
        SIUL2_0_PORT93_FXIO_FXIO_D22_INOUT |
        SIUL2_0_PORT94_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT95_FXIO_FXIO_D1_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_LPSPI3_LPSPI3_SOUT_INOUT |
        SIUL2_0_PORT97_LPSPI3_LPSPI3_SCK_INOUT |
        SIUL2_0_PORT98_LPSPI1_LPSPI1_SOUT_INOUT |
        SIUL2_0_PORT99_LPSPI1_LPSPI1_PCS0_INOUT |
        SIUL2_0_PORT100_LPSPI1_LPSPI1_PCS1_INOUT |
        SIUL2_0_PORT101_EMIOS_0_EMIOS_0_CH_2_G_INOUT |
        SIUL2_0_PORT102_EMIOS_1_EMIOS_1_CH_12_H_INOUT |
        SIUL2_0_PORT103_LPSPI3_LPSPI3_PCS3_INOUT |
        SIUL2_0_PORT105_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT106_EMIOS_1_EMIOS_1_CH_10_H_INOUT |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_RMII_TX_EN_INOUT |
        SIUL2_0_PORT109_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT110_LPUART1_LPUART1_TX_INOUT |
        SIUL2_0_PORT111_EMIOS_1_EMIOS_1_CH_14_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_GMAC0_GMAC0_MII_RMII_RGMII_MDIO_INOUT |
        SIUL2_0_PORT114_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT115_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT116_FXIO_FXIO_D25_INOUT |
        SIUL2_0_PORT117_FXIO_FXIO_D26_INOUT |
        SIUL2_0_PORT118_FXIO_FXIO_D27_INOUT |
        SIUL2_0_PORT119_FXIO_FXIO_D28_INOUT |
        SIUL2_0_PORT120_FXIO_FXIO_D29_INOUT |
        SIUL2_0_PORT122_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT127_FXIO_FXIO_D6_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT128_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT129_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT130_EMIOS_0_EMIOS_0_CH_3_G_INOUT |
        SIUL2_0_PORT131_EMIOS_0_EMIOS_0_CH_19_Y_INOUT |
        SIUL2_0_PORT132_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT133_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT136_LPSPI5_LPSPI5_PCS1_INOUT |
        SIUL2_0_PORT137_EMIOS_1_EMIOS_1_CH_13_H_INOUT |
        SIUL2_0_PORT138_LPSPI2_LPSPI2_PCS1_INOUT |
        SIUL2_0_PORT139_EMIOS_0_EMIOS_0_CH_1_G_INOUT |
        SIUL2_0_PORT140_LPUART2_LPUART2_TX_INOUT |
        SIUL2_0_PORT143_LPSPI2_LPSPI2_SCK_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_LPSPI2_LPSPI2_SIN_INOUT |
        SIUL2_0_PORT145_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT146_FXIO_FXIO_D4_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT160_LPSPI2_LPSPI2_SCK_INOUT |
        SIUL2_0_PORT161_LPSPI2_LPSPI2_SIN_INOUT |
        SIUL2_0_PORT162_LPSPI2_LPSPI2_SOUT_INOUT |
        SIUL2_0_PORT163_LPSPI2_LPSPI2_PCS0_INOUT |
        SIUL2_0_PORT164_LPSPI2_LPSPI2_SOUT_INOUT |
        SIUL2_0_PORT167_LPI2C1_LPI2C1_SCL_INOUT |
        SIUL2_0_PORT168_LPI2C1_LPI2C1_SDA_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT177_EMIOS_1_EMIOS_1_CH_1_H_INOUT |
        SIUL2_0_PORT178_EMIOS_1_EMIOS_1_CH_2_H_INOUT |
        SIUL2_0_PORT179_EMIOS_1_EMIOS_1_CH_3_H_INOUT |
        SIUL2_0_PORT180_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT181_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT182_EMIOS_1_EMIOS_1_CH_6_H_INOUT |
        SIUL2_0_PORT183_EMIOS_1_EMIOS_1_CH_7_H_INOUT |
        SIUL2_0_PORT184_EMIOS_1_EMIOS_1_CH_8_X_INOUT |
        SIUL2_0_PORT185_EMIOS_1_EMIOS_1_CH_9_H_INOUT |
        SIUL2_0_PORT186_EMIOS_1_EMIOS_1_CH_10_H_INOUT |
        SIUL2_0_PORT187_EMIOS_1_EMIOS_1_CH_11_H_INOUT |
        SIUL2_0_PORT188_EMIOS_1_EMIOS_1_CH_12_H_INOUT |
        SIUL2_0_PORT189_EMIOS_1_EMIOS_1_CH_13_H_INOUT |
        SIUL2_0_PORT190_EMIOS_1_EMIOS_1_CH_14_H_INOUT |
        SIUL2_0_PORT191_EMIOS_1_EMIOS_1_CH_15_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT192_EMIOS_1_EMIOS_1_CH_16_X_INOUT |
        SIUL2_0_PORT193_EMIOS_1_EMIOS_1_CH_17_Y_INOUT |
        SIUL2_0_PORT194_EMIOS_1_EMIOS_1_CH_18_Y_INOUT |
        SIUL2_0_PORT195_EMIOS_1_EMIOS_1_CH_19_Y_INOUT |
        SIUL2_0_PORT196_EMIOS_1_EMIOS_1_CH_20_Y_INOUT |
        SIUL2_0_PORT197_EMIOS_1_EMIOS_1_CH_21_Y_INOUT |
        SIUL2_0_PORT198_EMIOS_1_EMIOS_1_CH_22_X_INOUT |
        SIUL2_0_PORT199_EMIOS_1_EMIOS_1_CH_23_X_INOUT |
        SIUL2_0_PORT200_LPSPI5_LPSPI5_PCS3_INOUT |
        SIUL2_0_PORT201_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT205_LPSPI5_LPSPI5_PCS2_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT208_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT209_FXIO_FXIO_D16_INOUT |
        SIUL2_0_PORT210_FXIO_FXIO_D17_INOUT |
        SIUL2_0_PORT211_FXIO_FXIO_D18_INOUT |
        SIUL2_0_PORT212_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT213_FXIO_FXIO_D20_INOUT |
        SIUL2_0_PORT214_FXIO_FXIO_D21_INOUT |
        SIUL2_0_PORT215_FXIO_FXIO_D22_INOUT |
        SIUL2_0_PORT216_FXIO_FXIO_D23_INOUT |
        SIUL2_0_PORT217_FXIO_FXIO_D24_INOUT |
        SIUL2_0_PORT218_FXIO_FXIO_D25_INOUT |
        SIUL2_0_PORT219_FXIO_FXIO_D26_INOUT |
        SIUL2_0_PORT221_FXIO_FXIO_D29_INOUT |
        SIUL2_0_PORT222_FXIO_FXIO_D30_INOUT |
        SIUL2_0_PORT223_FXIO_FXIO_D31_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_FXIO_FXIO_D16_INOUT |
        SIUL2_0_PORT225_FXIO_FXIO_D17_INOUT |
        SIUL2_0_PORT226_FXIO_FXIO_D18_INOUT |
        SIUL2_0_PORT227_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT228_FXIO_FXIO_D20_INOUT |
        SIUL2_0_PORT229_FXIO_FXIO_D21_INOUT |
        SIUL2_0_PORT230_FXIO_FXIO_D22_INOUT |
        SIUL2_0_PORT231_FXIO_FXIO_D23_INOUT |
        SIUL2_0_PORT232_FXIO_FXIO_D24_INOUT |
        SIUL2_0_PORT233_FXIO_FXIO_D25_INOUT |
        SIUL2_0_PORT234_FXIO_FXIO_D26_INOUT |
        SIUL2_0_PORT235_FXIO_FXIO_D27_INOUT |
        SIUL2_0_PORT236_FXIO_FXIO_D28_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271
        SIUL2_0_PORT256_EMIOS_2_EMIOS_2_CH_0_X_INOUT |
        SIUL2_0_PORT257_EMIOS_2_EMIOS_2_CH_1_H_INOUT |
        SIUL2_0_PORT259_EMIOS_2_EMIOS_2_CH_3_H_INOUT |
        SIUL2_0_PORT260_EMIOS_2_EMIOS_2_CH_5_H_INOUT |
        SIUL2_0_PORT262_EMIOS_2_EMIOS_2_CH_7_H_INOUT |
        SIUL2_0_PORT263_EMIOS_2_EMIOS_2_CH_8_X_INOUT |
        SIUL2_0_PORT264_EMIOS_2_EMIOS_2_CH_6_H_INOUT |
        SIUL2_0_PORT266_EMIOS_2_EMIOS_2_CH_4_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 272 - 287
        SIUL2_0_PORT272_LPSPI1_LPSPI1_PCS0_INOUT |
        SIUL2_0_PORT274_LPSPI1_LPSPI1_SOUT_INOUT |
        SIUL2_0_PORT276_LPSPI1_LPSPI1_SIN_INOUT |
        SIUL2_0_PORT279_LPSPI1_LPSPI1_SCK_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 288 - 303
        SIUL2_0_PORT292_LPUART13_LPUART13_TX_INOUT |
        SIUL2_0_PORT298_EMIOS_2_EMIOS_2_CH_2_H_INOUT |
        SIUL2_0_PORT300_FXIO_FXIO_D28_INOUT |
        SIUL2_0_PORT301_FXIO_FXIO_D29_INOUT |
        SIUL2_0_PORT302_FXIO_FXIO_D30_INOUT |
        SIUL2_0_PORT303_FXIO_FXIO_D31_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT304_LPSPI3_LPSPI3_PCS0_INOUT |
        SIUL2_0_PORT311_LPSPI4_LPSPI4_SIN_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT322_LPUART15_LPUART15_TX_INOUT */
        (uint16)( SHL_PAD_U32(2U)
                )
    }
    ,
    /*  Mode PORT_INOUT4_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT1_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT6_EMIOS_1_EMIOS_1_CH_13_H_INOUT |
        SIUL2_0_PORT8_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT9_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT10_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT11_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT14_EMIOS_2_EMIOS_2_CH_18_Y_INOUT |
        SIUL2_0_PORT15_LPSPI2_LPSPI2_PCS3_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPSPI0_LPSPI0_PCS4_INOUT |
        SIUL2_0_PORT17_LPUART4_LPUART4_TX_INOUT |
        SIUL2_0_PORT18_LPSPI1_LPSPI1_SOUT_INOUT |
        SIUL2_0_PORT19_LPSPI1_LPSPI1_SCK_INOUT |
        SIUL2_0_PORT20_LPSPI1_LPSPI1_SIN_INOUT |
        SIUL2_0_PORT21_LPSPI1_LPSPI1_PCS0_INOUT |
        SIUL2_0_PORT22_LPSPI1_LPSPI1_PCS1_INOUT |
        SIUL2_0_PORT26_LPSPI0_LPSPI0_PCS0_INOUT |
        SIUL2_0_PORT27_LPUART0_LPUART0_TX_INOUT |
        SIUL2_0_PORT29_LPUART2_LPUART2_TX_INOUT |
        SIUL2_0_PORT30_LPSPI0_LPSPI0_SOUT_INOUT |
        SIUL2_0_PORT31_LPSPI0_LPSPI0_PCS1_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_EMIOS_0_EMIOS_0_CH_3_G_INOUT |
        SIUL2_0_PORT33_EMIOS_0_EMIOS_0_CH_7_G_INOUT |
        SIUL2_0_PORT37_LPSPI0_LPSPI0_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(5U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_LPUART4_LPUART4_TX_INOUT |
        SIUL2_0_PORT49_EMIOS_1_EMIOS_1_CH_7_H_INOUT |
        SIUL2_0_PORT50_LPSPI1_LPSPI1_PCS1_INOUT |
        SIUL2_0_PORT51_GMAC0_GMAC0_MII_RMII_TX_EN_INOUT |
        SIUL2_0_PORT54_EMIOS_2_EMIOS_2_CH_18_Y_INOUT |
        SIUL2_0_PORT55_EMIOS_2_EMIOS_2_CH_19_Y_INOUT |
        SIUL2_0_PORT56_EMIOS_2_EMIOS_2_CH_20_Y_INOUT |
        SIUL2_0_PORT57_EMIOS_2_EMIOS_2_CH_21_Y_INOUT |
        SIUL2_0_PORT58_EMIOS_2_EMIOS_2_CH_22_X_INOUT |
        SIUL2_0_PORT59_EMIOS_2_EMIOS_2_CH_23_X_INOUT |
        SIUL2_0_PORT60_EMIOS_2_EMIOS_2_CH_10_H_INOUT |
        SIUL2_0_PORT61_EMIOS_2_EMIOS_2_CH_11_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT65_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT66_LPSPI0_LPSPI0_PCS2_INOUT |
        SIUL2_0_PORT67_LPUART0_LPUART0_TX_INOUT |
        SIUL2_0_PORT68_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT69_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT72_EMIOS_1_EMIOS_1_CH_9_H_INOUT |
        SIUL2_0_PORT73_EMIOS_1_EMIOS_1_CH_8_X_INOUT |
        SIUL2_0_PORT74_LPSPI2_LPSPI2_PCS1_INOUT |
        SIUL2_0_PORT75_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT76_LPSPI2_LPSPI2_PCS1_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPI2C1_LPI2C1_SDAS_INOUT |
        SIUL2_0_PORT81_LPI2C1_LPI2C1_SCLS_INOUT |
        SIUL2_0_PORT82_EMIOS_2_EMIOS_2_CH_12_H_INOUT |
        SIUL2_0_PORT83_EMIOS_2_EMIOS_2_CH_13_H_INOUT |
        SIUL2_0_PORT84_EMIOS_2_EMIOS_2_CH_14_H_INOUT |
        SIUL2_0_PORT85_EMIOS_2_EMIOS_2_CH_15_H_INOUT |
        SIUL2_0_PORT88_EMIOS_2_EMIOS_2_CH_0_X_INOUT |
        SIUL2_0_PORT89_EMIOS_2_EMIOS_2_CH_1_H_INOUT |
        SIUL2_0_PORT90_EMIOS_2_EMIOS_2_CH_2_H_INOUT |
        SIUL2_0_PORT91_EMIOS_2_EMIOS_2_CH_3_H_INOUT |
        SIUL2_0_PORT92_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT93_EMIOS_2_EMIOS_2_CH_4_H_INOUT |
        SIUL2_0_PORT94_EMIOS_2_EMIOS_2_CH_5_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_EMIOS_0_EMIOS_0_CH_16_X_INOUT |
        SIUL2_0_PORT97_EMIOS_0_EMIOS_0_CH_17_Y_INOUT |
        SIUL2_0_PORT98_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT99_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT101_GMAC1_GMAC1_MII_RMII_RX_DV_RGMII_RXCTL_INOUT |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT |
        SIUL2_0_PORT103_LPSPI0_LPSPI0_PCS3_INOUT |
        SIUL2_0_PORT105_LPUART6_LPUART6_TX_INOUT |
        SIUL2_0_PORT109_LPI2C0_LPI2C0_SDA_INOUT |
        SIUL2_0_PORT110_LPI2C0_LPI2C0_SCL_INOUT |
        SIUL2_0_PORT111_LPSPI0_LPSPI0_SCK_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPSPI0_LPSPI0_SIN_INOUT |
        SIUL2_0_PORT116_EMIOS_2_EMIOS_2_CH_0_X_INOUT |
        SIUL2_0_PORT117_EMIOS_2_EMIOS_2_CH_8_X_INOUT |
        SIUL2_0_PORT118_EMIOS_2_EMIOS_2_CH_22_X_INOUT |
        SIUL2_0_PORT119_EMIOS_2_EMIOS_2_CH_23_X_INOUT |
        SIUL2_0_PORT122_EMIOS_2_EMIOS_2_CH_7_H_INOUT |
        SIUL2_0_PORT123_EMIOS_2_EMIOS_2_CH_9_H_INOUT |
        SIUL2_0_PORT124_EMIOS_2_EMIOS_2_CH_0_X_INOUT |
        SIUL2_0_PORT125_EMIOS_2_EMIOS_2_CH_8_X_INOUT |
        SIUL2_0_PORT126_EMIOS_2_EMIOS_2_CH_16_X_INOUT |
        SIUL2_0_PORT127_EMIOS_2_EMIOS_2_CH_22_X_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT130_EMIOS_1_EMIOS_1_CH_8_X_INOUT |
        SIUL2_0_PORT131_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT132_EMIOS_0_EMIOS_0_CH_18_Y_INOUT |
        SIUL2_0_PORT133_EMIOS_0_EMIOS_0_CH_19_Y_INOUT |
        SIUL2_0_PORT134_EMIOS_1_EMIOS_1_CH_14_H_INOUT |
        SIUL2_0_PORT136_FXIO_FXIO_D12_INOUT |
        SIUL2_0_PORT138_EMIOS_0_EMIOS_0_CH_20_Y_INOUT |
        SIUL2_0_PORT139_EMIOS_0_EMIOS_0_CH_21_Y_INOUT |
        SIUL2_0_PORT140_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT142_LPUART5_LPUART5_TX_INOUT |
        SIUL2_0_PORT143_EMIOS_0_EMIOS_0_CH_22_X_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_EMIOS_0_EMIOS_0_CH_23_X_INOUT |
        SIUL2_0_PORT145_EMIOS_2_EMIOS_2_CH_23_X_INOUT |
        SIUL2_0_PORT146_EMIOS_2_EMIOS_2_CH_17_Y_INOUT |
        SIUL2_0_PORT149_EMIOS_2_EMIOS_2_CH_19_Y_INOUT |
        SIUL2_0_PORT150_EMIOS_2_EMIOS_2_CH_20_Y_INOUT |
        SIUL2_0_PORT151_EMIOS_2_EMIOS_2_CH_21_Y_INOUT |
        SIUL2_0_PORT152_EMIOS_2_EMIOS_2_CH_4_H_INOUT |
        SIUL2_0_PORT153_EMIOS_2_EMIOS_2_CH_5_H_INOUT |
        SIUL2_0_PORT154_EMIOS_2_EMIOS_2_CH_6_H_INOUT |
        SIUL2_0_PORT158_LPSPI0_LPSPI0_SOUT_INOUT |
        SIUL2_0_PORT159_LPSPI0_LPSPI0_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT164_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT167_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT168_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT172_LPSPI3_LPSPI3_SIN_INOUT |
        SIUL2_0_PORT173_LPSPI3_LPSPI3_SCK_INOUT |
        SIUL2_0_PORT175_LPSPI3_LPSPI3_SOUT_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT180_LPI2C0_LPI2C0_SCL_INOUT |
        SIUL2_0_PORT181_LPI2C0_LPI2C0_SDA_INOUT |
        SIUL2_0_PORT188_FXIO_FXIO_D7_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT201_LPUART2_LPUART2_TX_INOUT */
        (uint16)( SHL_PAD_U32(9U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT215_EMIOS_0_EMIOS_0_CH_0_X_INOUT |
        SIUL2_0_PORT216_EMIOS_0_EMIOS_0_CH_1_G_INOUT |
        SIUL2_0_PORT217_EMIOS_0_EMIOS_0_CH_2_G_INOUT |
        SIUL2_0_PORT218_EMIOS_0_EMIOS_0_CH_3_G_INOUT |
        SIUL2_0_PORT219_EMIOS_0_EMIOS_0_CH_4_G_INOUT |
        SIUL2_0_PORT220_EMIOS_0_EMIOS_0_CH_5_G_INOUT |
        SIUL2_0_PORT221_EMIOS_0_EMIOS_0_CH_6_G_INOUT |
        SIUL2_0_PORT222_EMIOS_0_EMIOS_0_CH_7_G_INOUT |
        SIUL2_0_PORT223_EMIOS_0_EMIOS_0_CH_8_X_INOUT */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 224 - 239
        SIUL2_0_PORT224_EMIOS_0_EMIOS_0_CH_9_H_INOUT |
        SIUL2_0_PORT225_EMIOS_0_EMIOS_0_CH_10_H_INOUT |
        SIUL2_0_PORT226_EMIOS_0_EMIOS_0_CH_11_H_INOUT |
        SIUL2_0_PORT227_EMIOS_0_EMIOS_0_CH_12_H_INOUT |
        SIUL2_0_PORT228_EMIOS_0_EMIOS_0_CH_13_H_INOUT |
        SIUL2_0_PORT229_EMIOS_0_EMIOS_0_CH_14_H_INOUT |
        SIUL2_0_PORT230_EMIOS_0_EMIOS_0_CH_15_H_INOUT |
        SIUL2_0_PORT231_EMIOS_0_EMIOS_0_CH_16_X_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303
        SIUL2_0_PORT298_LPSPI3_LPSPI3_SCK_INOUT |
        SIUL2_0_PORT300_LPSPI3_LPSPI3_SIN_INOUT |
        SIUL2_0_PORT302_LPSPI3_LPSPI3_SOUT_INOUT */
        (uint16)( SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 304 - 319
        SIUL2_0_PORT314_LPSPI4_LPSPI4_SOUT_INOUT |
        SIUL2_0_PORT317_LPSPI4_LPSPI4_SCK_INOUT */
        (uint16)( SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 320 - 335
        SIUL2_0_PORT320_LPSPI4_LPSPI4_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(0U)
                )
    }
    ,
    /*  Mode PORT_INOUT5_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT2_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT3_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT6_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT12_FXIO_FXIO_D9_INOUT |
        SIUL2_0_PORT13_FXIO_FXIO_D8_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_LPUART6_LPUART6_TX_INOUT |
        SIUL2_0_PORT18_EMIOS_1_EMIOS_1_CH_16_X_INOUT |
        SIUL2_0_PORT26_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT29_LPSPI1_LPSPI1_SIN_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT36_GMAC0_GMAC0_MII_RMII_RGMII_MDIO_INOUT |
        SIUL2_0_PORT42_LPUART9_LPUART9_TX_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT50_EMIOS_2_EMIOS_2_CH_14_H_INOUT |
        SIUL2_0_PORT51_EMIOS_2_EMIOS_2_CH_15_H_INOUT |
        SIUL2_0_PORT52_EMIOS_2_EMIOS_2_CH_16_X_INOUT |
        SIUL2_0_PORT53_EMIOS_2_EMIOS_2_CH_17_Y_INOUT |
        SIUL2_0_PORT54_LPUART1_LPUART1_TX_INOUT |
        SIUL2_0_PORT57_LPSPI2_LPSPI2_PCS0_INOUT |
        SIUL2_0_PORT59_LPSPI2_LPSPI2_SOUT_INOUT |
        SIUL2_0_PORT60_LPSPI2_LPSPI2_SIN_INOUT |
        SIUL2_0_PORT61_LPSPI2_LPSPI2_SCK_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT66_GMAC0_GMAC0_MII_RMII_TXD_0_INOUT |
        SIUL2_0_PORT70_EMIOS_1_EMIOS_1_CH_6_H_INOUT |
        SIUL2_0_PORT71_EMIOS_1_EMIOS_1_CH_7_H_INOUT |
        SIUL2_0_PORT74_LPSPI4_LPSPI4_PCS0_INOUT |
        SIUL2_0_PORT75_LPSPI4_LPSPI4_SOUT_INOUT |
        SIUL2_0_PORT76_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT77_FXIO_FXIO_D16_INOUT |
        SIUL2_0_PORT78_EMIOS_1_EMIOS_1_CH_4_H_INOUT |
        SIUL2_0_PORT79_LPUART2_LPUART2_TX_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_INOUT |
        SIUL2_0_PORT81_GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_INOUT |
        SIUL2_0_PORT82_GMAC0_GMAC0_MII_RMII_RGMII_TXD_1_INOUT |
        SIUL2_0_PORT83_LPSPI2_LPSPI2_PCS1_INOUT |
        SIUL2_0_PORT89_LPSPI4_LPSPI4_PCS1_INOUT |
        SIUL2_0_PORT92_LPI2C1_LPI2C1_SCL_INOUT |
        SIUL2_0_PORT93_LPI2C1_LPI2C1_SDA_INOUT |
        SIUL2_0_PORT95_EMIOS_2_EMIOS_2_CH_6_H_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT98_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT99_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT101_GMAC0_GMAC0_MII_TXD3_INOUT |
        SIUL2_0_PORT102_GMAC0_GMAC0_MII_TXD2_INOUT |
        SIUL2_0_PORT103_GMAC0_GMAC0_MII_RMII_TXD_1_INOUT |
        SIUL2_0_PORT104_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT106_LPSPI0_LPSPI0_SIN_INOUT |
        SIUL2_0_PORT107_GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT |
        SIUL2_0_PORT108_GMAC0_GMAC0_MII_RMII_TX_EN_INOUT |
        SIUL2_0_PORT109_GMAC0_GMAC0_PPS1_INOUT |
        SIUL2_0_PORT110_GMAC0_GMAC0_PPS0_INOUT |
        SIUL2_0_PORT111_GMAC0_GMAC0_PPS2_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_EMIOS_1_EMIOS_1_CH_15_H_INOUT |
        SIUL2_0_PORT113_LPSPI3_LPSPI3_PCS0_INOUT |
        SIUL2_0_PORT116_LPSPI1_LPSPI1_PCS2_INOUT |
        SIUL2_0_PORT122_FXIO_FXIO_D30_INOUT |
        SIUL2_0_PORT123_FXIO_FXIO_D31_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT132_LPUART12_LPUART12_TX_INOUT |
        SIUL2_0_PORT134_LPUART10_LPUART10_TX_INOUT |
        SIUL2_0_PORT137_GMAC0_GMAC0_PPS3_INOUT |
        SIUL2_0_PORT140_GMAC0_GMAC0_PPS3_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT152_FXIO_FXIO_D5_INOUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175
        SIUL2_0_PORT174_FXIO_FXIO_D3_INOUT */
        (uint16)( SHL_PAD_U32(14U)
                ),
        /* Pads 176 - 191
        SIUL2_0_PORT176_LPSPI3_LPSPI3_PCS0_INOUT |
        SIUL2_0_PORT178_LPSPI3_LPSPI3_PCS1_INOUT |
        SIUL2_0_PORT179_LPSPI3_LPSPI3_PCS2_INOUT |
        SIUL2_0_PORT180_LPSPI3_LPSPI3_PCS3_INOUT |
        SIUL2_0_PORT181_LPSPI1_LPSPI1_PCS0_INOUT |
        SIUL2_0_PORT183_LPSPI3_LPSPI3_PCS3_INOUT |
        SIUL2_0_PORT185_LPSPI2_LPSPI2_PCS2_INOUT |
        SIUL2_0_PORT186_LPSPI2_LPSPI2_PCS3_INOUT |
        SIUL2_0_PORT188_LPSPI0_LPSPI0_PCS0_INOUT |
        SIUL2_0_PORT189_LPSPI3_LPSPI3_PCS1_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT207_EMIOS_2_EMIOS_2_CH_15_H_INOUT */
        (uint16)( SHL_PAD_U32(15U)
                ),
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239
        SIUL2_0_PORT224_LPSPI2_LPSPI2_PCS2_INOUT |
        SIUL2_0_PORT225_LPSPI2_LPSPI2_PCS3_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U)
                ),
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT6_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT0_LPSPI0_LPSPI0_PCS7_INOUT |
        SIUL2_0_PORT1_LPSPI0_LPSPI0_PCS6_INOUT |
        SIUL2_0_PORT3_LPUART0_LPUART0_TX_INOUT |
        SIUL2_0_PORT6_LPSPI3_LPSPI3_PCS1_INOUT |
        SIUL2_0_PORT7_FXIO_FXIO_D9_INOUT |
        SIUL2_0_PORT8_EMIOS_2_EMIOS_2_CH_7_H_INOUT |
        SIUL2_0_PORT9_LPSPI3_LPSPI3_PCS0_INOUT |
        SIUL2_0_PORT11_LPSPI1_LPSPI1_PCS0_INOUT |
        SIUL2_0_PORT12_EMIOS_1_EMIOS_1_CH_2_H_INOUT |
        SIUL2_0_PORT13_EMIOS_1_EMIOS_1_CH_3_H_INOUT |
        SIUL2_0_PORT14_FXIO_FXIO_D14_INOUT |
        SIUL2_0_PORT15_LPSPI5_LPSPI5_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT17_LPSPI3_LPSPI3_SOUT_INOUT |
        SIUL2_0_PORT18_EMIOS_2_EMIOS_2_CH_0_X_INOUT |
        SIUL2_0_PORT19_EMIOS_2_EMIOS_2_CH_1_H_INOUT |
        SIUL2_0_PORT20_EMIOS_2_EMIOS_2_CH_2_H_INOUT |
        SIUL2_0_PORT21_EMIOS_2_EMIOS_2_CH_3_H_INOUT |
        SIUL2_0_PORT26_EMIOS_2_EMIOS_2_CH_9_H_INOUT |
        SIUL2_0_PORT27_EMIOS_2_EMIOS_2_CH_10_H_INOUT |
        SIUL2_0_PORT28_EMIOS_2_EMIOS_2_CH_11_H_INOUT |
        SIUL2_0_PORT29_EMIOS_2_EMIOS_2_CH_12_H_INOUT |
        SIUL2_0_PORT30_EMIOS_2_EMIOS_2_CH_13_H_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT32_EMIOS_1_EMIOS_1_CH_6_H_INOUT |
        SIUL2_0_PORT33_EMIOS_1_EMIOS_1_CH_5_H_INOUT |
        SIUL2_0_PORT34_SAI0_SAI0_D0_INOUT |
        SIUL2_0_PORT36_EMIOS_1_EMIOS_1_CH_10_H_INOUT |
        SIUL2_0_PORT37_EMIOS_1_EMIOS_1_CH_11_H_INOUT |
        SIUL2_0_PORT40_LPSPI0_LPSPI0_PCS5_INOUT |
        SIUL2_0_PORT45_LPUART8_LPUART8_TX_INOUT |
        SIUL2_0_PORT47_LPUART7_LPUART7_TX_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT49_LPSPI3_LPSPI3_PCS0_INOUT |
        SIUL2_0_PORT54_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT57_GMAC0_GMAC0_RGMII_TXCTL_INOUT |
        SIUL2_0_PORT59_SAI0_SAI0_D0_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_EMIOS_0_EMIOS_0_CH_14_H_INOUT |
        SIUL2_0_PORT65_EMIOS_0_EMIOS_0_CH_15_H_INOUT |
        SIUL2_0_PORT70_LPSPI0_LPSPI0_PCS1_INOUT |
        SIUL2_0_PORT71_LPSPI0_LPSPI0_PCS0_INOUT |
        SIUL2_0_PORT72_LPSPI0_LPSPI0_SCK_INOUT |
        SIUL2_0_PORT73_LPSPI0_LPSPI0_SIN_INOUT |
        SIUL2_0_PORT75_FXIO_FXIO_D19_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT81_FXIO_FXIO_D14_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT96_FXIO_FXIO_D0_INOUT |
        SIUL2_0_PORT97_FXIO_FXIO_D1_INOUT |
        SIUL2_0_PORT98_LPUART3_LPUART3_TX_INOUT |
        SIUL2_0_PORT101_FXIO_FXIO_D15_INOUT |
        SIUL2_0_PORT102_FXIO_FXIO_D13_INOUT |
        SIUL2_0_PORT104_EMIOS_0_EMIOS_0_CH_12_H_INOUT |
        SIUL2_0_PORT105_EMIOS_0_EMIOS_0_CH_13_H_INOUT |
        SIUL2_0_PORT107_LPSPI0_LPSPI0_SCK_INOUT |
        SIUL2_0_PORT108_LPSPI0_LPSPI0_SOUT_INOUT |
        SIUL2_0_PORT109_SAI1_SAI1_D0_INOUT |
        SIUL2_0_PORT111_SAI1_SAI1_SYNC_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT113_FXIO_FXIO_D9_INOUT |
        SIUL2_0_PORT116_LPSPI3_LPSPI3_SIN_INOUT |
        SIUL2_0_PORT122_LPSPI5_LPSPI5_SCK_INOUT |
        SIUL2_0_PORT123_LPSPI5_LPSPI5_SOUT_INOUT |
        SIUL2_0_PORT124_LPSPI5_LPSPI5_SIN_INOUT |
        SIUL2_0_PORT125_LPSPI5_LPSPI5_PCS2_INOUT |
        SIUL2_0_PORT126_LPSPI5_LPSPI5_PCS3_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT129_LPUART7_LPUART7_TX_INOUT |
        SIUL2_0_PORT130_FXIO_FXIO_D13_INOUT |
        SIUL2_0_PORT131_GMAC0_GMAC0_PPS0_INOUT |
        SIUL2_0_PORT132_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT133_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT134_FXIO_FXIO_D12_INOUT |
        SIUL2_0_PORT135_LPSPI3_LPSPI3_SCK_INOUT |
        SIUL2_0_PORT136_SAI1_SAI1_BCLK_INOUT |
        SIUL2_0_PORT137_GMAC0_GMAC0_MII_RMII_TX_EN_INOUT |
        SIUL2_0_PORT138_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT139_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT140_FXIO_FXIO_D8_INOUT |
        SIUL2_0_PORT142_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT143_FXIO_FXIO_D2_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT144_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT149_LPSPI4_LPSPI4_SIN_INOUT |
        SIUL2_0_PORT150_LPSPI4_LPSPI4_SCK_INOUT |
        SIUL2_0_PORT151_LPSPI4_LPSPI4_PCS0_INOUT |
        SIUL2_0_PORT152_LPSPI4_LPSPI4_PCS1_INOUT |
        SIUL2_0_PORT153_LPSPI4_LPSPI4_SOUT_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191
        SIUL2_0_PORT182_LPSPI4_LPSPI4_PCS2_INOUT |
        SIUL2_0_PORT185_LPSPI4_LPSPI4_PCS0_INOUT |
        SIUL2_0_PORT186_LPSPI4_LPSPI4_PCS1_INOUT |
        SIUL2_0_PORT187_LPSPI4_LPSPI4_PCS2_INOUT |
        SIUL2_0_PORT188_LPSPI4_LPSPI4_PCS3_INOUT |
        SIUL2_0_PORT191_FXIO_FXIO_D9_INOUT */
        (uint16)( SHL_PAD_U32(6U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 192 - 207
        SIUL2_0_PORT204_LPSPI4_LPSPI4_PCS3_INOUT */
        (uint16)( SHL_PAD_U32(12U)
                ),
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT7_MODE: */
    {
        /* Pads 0 - 15
        SIUL2_0_PORT2_LPSPI5_LPSPI5_SIN_INOUT |
        SIUL2_0_PORT3_LPSPI5_LPSPI5_SCK_INOUT |
        SIUL2_0_PORT4_JTAG_JTAG_TMSSWD_DIO_INOUT |
        SIUL2_0_PORT5_SYSTEM_RESET_B_INOUT |
        SIUL2_0_PORT11_LPSPI2_LPSPI2_SCK_INOUT |
        SIUL2_0_PORT13_LPUART11_LPUART11_TX_INOUT |
        SIUL2_0_PORT14_LPSPI5_LPSPI5_PCS1_INOUT |
        SIUL2_0_PORT15_FXIO_FXIO_D31_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 16 - 31
        SIUL2_0_PORT16_FXIO_FXIO_D30_INOUT |
        SIUL2_0_PORT17_FXIO_FXIO_D19_INOUT |
        SIUL2_0_PORT26_GMAC0_GMAC0_PPS0_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(10U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT34_FXIO_FXIO_D18_INOUT |
        SIUL2_0_PORT35_FXIO_FXIO_D17_INOUT |
        SIUL2_0_PORT36_SAI0_SAI0_D1_INOUT |
        SIUL2_0_PORT40_FXIO_FXIO_D29_INOUT |
        SIUL2_0_PORT41_FXIO_FXIO_D28_INOUT |
        SIUL2_0_PORT42_FXIO_FXIO_D27_INOUT |
        SIUL2_0_PORT43_FXIO_FXIO_D26_INOUT |
        SIUL2_0_PORT44_FXIO_FXIO_D25_INOUT |
        SIUL2_0_PORT45_FXIO_FXIO_D24_INOUT |
        SIUL2_0_PORT46_FXIO_FXIO_D23_INOUT |
        SIUL2_0_PORT47_FXIO_FXIO_D22_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT48_FXIO_FXIO_D21_INOUT |
        SIUL2_0_PORT49_FXIO_FXIO_D20_INOUT |
        SIUL2_0_PORT60_GMAC0_GMAC0_PPS3_INOUT |
        SIUL2_0_PORT61_SAI0_SAI0_D1_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT |
        SIUL2_0_PORT65_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_INOUT |
        SIUL2_0_PORT66_QUADSPI_QUADSPI_IOFA3_INOUT |
        SIUL2_0_PORT67_GMAC1_GMAC1_MII_RMII_TX_EN_INOUT |
        SIUL2_0_PORT72_FXIO_FXIO_D12_INOUT |
        SIUL2_0_PORT73_FXIO_FXIO_D13_INOUT |
        SIUL2_0_PORT74_EMIOS_1_EMIOS_1_CH_0_X_INOUT |
        SIUL2_0_PORT76_SAI0_SAI0_BCLK_INOUT |
        SIUL2_0_PORT77_SAI0_SAI0_SYNC_INOUT |
        SIUL2_0_PORT78_FXIO_FXIO_D16_INOUT |
        SIUL2_0_PORT79_LPI2C1_LPI2C1_SCL_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT80_LPI2C1_LPI2C1_SDA_INOUT |
        SIUL2_0_PORT81_FXIO_FXIO_D2_INOUT |
        SIUL2_0_PORT82_SAI0_SAI0_D2_INOUT |
        SIUL2_0_PORT83_SAI0_SAI0_D3_INOUT |
        SIUL2_0_PORT84_GMAC0_GMAC0_PPS0_INOUT |
        SIUL2_0_PORT90_LPSPI4_LPSPI4_SIN_INOUT |
        SIUL2_0_PORT91_LPSPI4_LPSPI4_SCK_INOUT |
        SIUL2_0_PORT93_FXIO_FXIO_D3_INOUT |
        SIUL2_0_PORT94_FXIO_FXIO_D23_INOUT |
        SIUL2_0_PORT95_FXIO_FXIO_D24_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT98_LPSPI5_LPSPI5_SOUT_INOUT |
        SIUL2_0_PORT100_LPSPI5_LPSPI5_PCS0_INOUT |
        SIUL2_0_PORT101_LPSPI0_LPSPI0_PCS1_INOUT |
        SIUL2_0_PORT102_LPSPI0_LPSPI0_PCS0_INOUT |
        SIUL2_0_PORT103_QUADSPI_QUADSPI_IOFA1_INOUT |
        SIUL2_0_PORT104_FXIO_FXIO_D11_INOUT |
        SIUL2_0_PORT105_FXIO_FXIO_D10_INOUT |
        SIUL2_0_PORT106_QUADSPI_QUADSPI_SCKFA_INOUT |
        SIUL2_0_PORT107_QUADSPI_QUADSPI_IOFA0_INOUT |
        SIUL2_0_PORT108_QUADSPI_QUADSPI_IOFA2_INOUT |
        SIUL2_0_PORT111_FXIO_FXIO_D10_INOUT */
        (uint16)( SHL_PAD_U32(2U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(6U) |
                  SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 112 - 127
        SIUL2_0_PORT112_LPUART8_LPUART8_TX_INOUT |
        SIUL2_0_PORT113_GMAC0_GMAC0_PPS2_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U)
                ),
        /* Pads 128 - 143
        SIUL2_0_PORT135_FXIO_FXIO_D11_INOUT |
        SIUL2_0_PORT136_FXIO_FXIO_D8_INOUT |
        SIUL2_0_PORT137_FXIO_FXIO_D11_INOUT |
        SIUL2_0_PORT140_FXIO_FXIO_D7_INOUT |
        SIUL2_0_PORT142_GMAC0_GMAC0_PPS1_INOUT */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT152_FXIO_FXIO_D11_INOUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191
        SIUL2_0_PORT180_FXIO_FXIO_D4_INOUT |
        SIUL2_0_PORT181_FXIO_FXIO_D5_INOUT |
        SIUL2_0_PORT185_FXIO_FXIO_D6_INOUT |
        SIUL2_0_PORT189_FXIO_FXIO_D8_INOUT */
        (uint16)( SHL_PAD_U32(4U) |
                  SHL_PAD_U32(5U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT8_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31
        SIUL2_0_PORT29_GMAC1_GMAC1_MII_RMII_RGMII_MDIO_INOUT |
        SIUL2_0_PORT31_GMAC1_GMAC1_PPS0_INOUT */
        (uint16)( SHL_PAD_U32(13U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC0_GMAC0_MII_RGMII_TXD3_INOUT */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63
        SIUL2_0_PORT51_GMAC1_GMAC1_MII_RMII_RGMII_MDIO_INOUT |
        SIUL2_0_PORT52_GMAC1_GMAC1_PPS2_INOUT |
        SIUL2_0_PORT55_GMAC0_GMAC0_MII_RGMII_RXD2_INOUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(4U) |
                  SHL_PAD_U32(7U)
                ),
        /* Pads 64 - 79
        SIUL2_0_PORT64_GMAC1_GMAC1_MII_RGMII_TXD2_INOUT |
        SIUL2_0_PORT65_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_INOUT |
        SIUL2_0_PORT66_GMAC1_GMAC1_MII_RGMII_RXD3_INOUT |
        SIUL2_0_PORT79_GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_INOUT */
        (uint16)( SHL_PAD_U32(0U) |
                  SHL_PAD_U32(1U) |
                  SHL_PAD_U32(2U) |
                  SHL_PAD_U32(15U)
                ),
        /* Pads 80 - 95
        SIUL2_0_PORT81_GMAC1_GMAC1_MII_RMII_RGMII_TXD_1_INOUT |
        SIUL2_0_PORT83_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_INOUT |
        SIUL2_0_PORT91_LPUART13_LPUART13_TX_INOUT |
        SIUL2_0_PORT92_LPUART0_LPUART0_TX_INOUT */
        (uint16)( SHL_PAD_U32(1U) |
                  SHL_PAD_U32(3U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 96 - 111
        SIUL2_0_PORT103_GMAC1_GMAC1_MII_RGMII_RXD2_INOUT |
        SIUL2_0_PORT104_GMAC1_GMAC1_MII_RMII_RGMII_TXD_0_INOUT |
        SIUL2_0_PORT105_GMAC1_GMAC1_MII_RGMII_TXD3_INOUT |
        SIUL2_0_PORT107_GMAC1_GMAC1_RGMII_TXCTL_INOUT |
        SIUL2_0_PORT108_GMAC1_GMAC1_MII_RMII_RGMII_RXD_1_INOUT */
        (uint16)( SHL_PAD_U32(7U) |
                  SHL_PAD_U32(8U) |
                  SHL_PAD_U32(9U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143
        SIUL2_0_PORT131_GMAC1_GMAC1_PPS3_INOUT |
        SIUL2_0_PORT142_GMAC1_GMAC1_PPS1_INOUT */
        (uint16)( SHL_PAD_U32(3U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 144 - 159
        SIUL2_0_PORT152_LPSPI2_LPSPI2_SIN_INOUT |
        SIUL2_0_PORT155_EMIOS_0_EMIOS_0_CH_10_H_INOUT |
        SIUL2_0_PORT156_EMIOS_0_EMIOS_0_CH_11_H_INOUT |
        SIUL2_0_PORT157_EMIOS_0_EMIOS_0_CH_12_H_INOUT */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U)
                ),
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207
        SIUL2_0_PORT200_EMIOS_0_EMIOS_0_CH_13_H_INOUT |
        SIUL2_0_PORT202_EMIOS_0_EMIOS_0_CH_14_H_INOUT |
        SIUL2_0_PORT203_EMIOS_0_EMIOS_0_CH_15_H_INOUT |
        SIUL2_0_PORT204_EMIOS_0_EMIOS_0_CH_16_X_INOUT |
        SIUL2_0_PORT205_EMIOS_0_EMIOS_0_CH_17_Y_INOUT |
        SIUL2_0_PORT206_EMIOS_0_EMIOS_0_CH_18_Y_INOUT */
        (uint16)( SHL_PAD_U32(8U) |
                  SHL_PAD_U32(10U) |
                  SHL_PAD_U32(11U) |
                  SHL_PAD_U32(12U) |
                  SHL_PAD_U32(13U) |
                  SHL_PAD_U32(14U)
                ),
        /* Pads 208 - 223
        SIUL2_0_PORT215_LPSPI5_LPSPI5_PCS0_INOUT */
        (uint16)( SHL_PAD_U32(7U)
                ),
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT9_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_INOUT */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT10_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47
        SIUL2_0_PORT35_GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_INOUT */
        (uint16)( SHL_PAD_U32(3U)
                ),
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT11_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT101_SAI0_SAI0_D3_INOUT */
        (uint16)( SHL_PAD_U32(5U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT12_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT13_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT102_SAI0_SAI0_D2_INOUT */
        (uint16)( SHL_PAD_U32(6U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT14_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63 */
        (uint16)0x0000,
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111
        SIUL2_0_PORT102_GMAC1_GMAC1_MII_RMII_RGMII_RXD_0_INOUT */
        (uint16)( SHL_PAD_U32(6U)
                ),
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
    ,
    /*  Mode PORT_INOUT15_MODE: */
    {
        /* Pads 0 - 15 */
        (uint16)0x0000,
        /* Pads 16 - 31 */
        (uint16)0x0000,
        /* Pads 32 - 47 */
        (uint16)0x0000,
        /* Pads 48 - 63
        SIUL2_0_PORT56_GMAC0_GMAC0_MII_RGMII_RXD3_INOUT */
        (uint16)( SHL_PAD_U32(8U)
                ),
        /* Pads 64 - 79 */
        (uint16)0x0000,
        /* Pads 80 - 95 */
        (uint16)0x0000,
        /* Pads 96 - 111 */
        (uint16)0x0000,
        /* Pads 112 - 127 */
        (uint16)0x0000,
        /* Pads 128 - 143 */
        (uint16)0x0000,
        /* Pads 144 - 159 */
        (uint16)0x0000,
        /* Pads 160 - 175 */
        (uint16)0x0000,
        /* Pads 176 - 191 */
        (uint16)0x0000,
        /* Pads 192 - 207 */
        (uint16)0x0000,
        /* Pads 208 - 223 */
        (uint16)0x0000,
        /* Pads 224 - 239 */
        (uint16)0x0000,
        /* Pads 240 - 255 */
        (uint16)0x0000,
        /* Pads 256 - 271 */
        (uint16)0x0000,
        /* Pads 272 - 287 */
        (uint16)0x0000,
        /* Pads 288 - 303 */
        (uint16)0x0000,
        /* Pads 304 - 319 */
        (uint16)0x0000,
        /* Pads 320 - 335 */
        (uint16)0x0000
    }
};

/**
* @brief Array of elements storing information about IN functionalities on the SIUL2 instance
*/
static const Port_InMuxSettingType Port_SIUL2_0_aInMuxSettings[] =
{
    /* INMUX settings for pad not available: */
    { NO_INPUTMUX_U16, 0U, 0U},
    /* INMUX settings for pad PORT0:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_0_IN input func */
    {16U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_17_Y_IN input func */
    {65U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 3U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 2U, 0U},
    /* LPSPI0_LPSPI0_PCS7_IN input func */
    {228U, 1U, 0U},
    /* LPSPI4_LPSPI4_PCS2_IN input func */
    {257U, 1U, 0U},
    /* LPUART0_LPUART0_CTS_IN input func */
    {360U, 1U, 0U},
    /* INMUX settings for pad PORT1:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_1_IN input func */
    {17U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_9_H_IN input func */
    {57U, 1U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS6_IN input func */
    {227U, 1U, 0U},
    /* LPSPI4_LPSPI4_PCS1_IN input func */
    {256U, 1U, 0U},
    /* INMUX settings for pad PORT2:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_2_IN input func */
    {18U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_19_Y_IN input func */
    {99U, 4U, 0U},
    /* FCCU_FCCU_ERR_IN0_IN input func */
    {148U, 1U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 3U, 0U},
    /* LPUART0_LPUART0_RX_IN input func */
    {187U, 1U, 0U},
    /* LPSPI1_LPSPI1_SIN_IN input func */
    {239U, 2U, 0U},
    /* LPSPI5_LPSPI5_SIN_IN input func */
    {267U, 2U, 0U},
    /* INMUX settings for pad PORT3:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_3_IN input func */
    {19U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_20_Y_IN input func */
    {100U, 4U, 0U},
    /* FCCU_FCCU_ERR_IN1_IN input func */
    {149U, 1U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 3U, 0U},
    /* LPSPI1_LPSPI1_SCK_IN input func */
    {238U, 1U, 0U},
    /* LPSPI5_LPSPI5_SCK_IN input func */
    {266U, 2U, 0U},
    /* LPUART0_LPUART0_TX_IN input func */
    {363U, 1U, 0U},
    /* INMUX settings for pad PORT4:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_4_IN input func */
    {20U, 1U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 8U, 0U},
    /* JTAG_JTAG_TMSSWD_DIO_IN input func */
    {186U, 0U, 0U},
    /* INMUX settings for pad PORT5:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_5_IN input func */
    {21U, 1U, 0U},
    /* INMUX settings for pad PORT6:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN0_CAN0_RX_IN input func */
    {0U, 2U, 0U},
    /* SIUL_EIRQ_6_IN input func */
    {22U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_13_H_IN input func */
    {93U, 1U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 4U, 0U},
    /* LPUART3_LPUART3_RX_IN input func */
    {190U, 2U, 0U},
    /* LPSPI1_LPSPI1_PCS1_IN input func */
    {233U, 1U, 0U},
    /* LPSPI3_LPSPI3_PCS1_IN input func */
    {249U, 5U, 0U},
    /* LPUART1_LPUART1_CTS_IN input func */
    {361U, 2U, 0U},
    /* LPUART0_LPUART0_RIN_B_IN input func */
    {375U, 1U, 0U},
    /* INMUX settings for pad PORT7:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_7_IN input func */
    {23U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_11_H_IN input func */
    {91U, 1U, 0U},
    /* FXIO_FXIO_D9_IN input func */
    {161U, 3U, 0U},
    /* LPSPI0_LPSPI0_PCS1_IN input func */
    {222U, 3U, 0U},
    /* LPUART3_LPUART3_TX_IN input func */
    {366U, 1U, 0U},
    /* LPUART0_LPUART0_DCD_B_IN input func */
    {374U, 1U, 0U},
    /* INMUX settings for pad PORT8:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_16_IN input func */
    {32U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_12_H_IN input func */
    {92U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_7_H_IN input func */
    {119U, 3U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 2U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 3U, 0U},
    /* LPSPI2_LPSPI2_SOUT_IN input func */
    {247U, 1U, 0U},
    /* INMUX settings for pad PORT9:    {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_17_IN input func */
    {33U, 1U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 2U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 1U, 0U},
    /* LPSPI3_LPSPI3_PCS0_IN input func */
    {248U, 3U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 1U, 0U},
    /* PGI_PGOOD_IN input func */
    {440U, 1U, 0U},
    /* INMUX settings for pad PORT10:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_18_IN input func */
    {34U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_12_H_IN input func */
    {60U, 2U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 2U, 0U},
    /* INMUX settings for pad PORT11:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_19_IN input func */
    {35U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_13_H_IN input func */
    {61U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 3U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 2U, 0U},
    /* LPSPI1_LPSPI1_PCS0_IN input func */
    {232U, 2U, 0U},
    /* LPSPI2_LPSPI2_SCK_IN input func */
    {245U, 5U, 0U},
    /* INMUX settings for pad PORT12:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN1_CAN1_RX_IN input func */
    {1U, 2U, 0U},
    /* SIUL_EIRQ_20_IN input func */
    {36U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_14_H_IN input func */
    {62U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_2_H_IN input func */
    {82U, 4U, 0U},
    /* FXIO_FXIO_D9_IN input func */
    {161U, 4U, 0U},
    /* LPUART11_LPUART11_RX_IN input func */
    {198U, 2U, 0U},
    /* LPSPI1_LPSPI1_PCS5_IN input func */
    {237U, 1U, 0U},
    /* INMUX settings for pad PORT13:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_21_IN input func */
    {37U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_15_H_IN input func */
    {63U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 4U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 4U, 0U},
    /* LPSPI1_LPSPI1_PCS4_IN input func */
    {236U, 1U, 0U},
    /* LPUART11_LPUART11_TX_IN input func */
    {412U, 1U, 0U},
    /* INMUX settings for pad PORT14:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_22_IN input func */
    {38U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 7U, 0U},
    /* EMIOS_2_EMIOS_2_CH_18_Y_IN input func */
    {130U, 4U, 0U},
    /* FXIO_FXIO_D14_IN input func */
    {166U, 4U, 0U},
    /* LPSPI1_LPSPI1_PCS3_IN input func */
    {235U, 2U, 0U},
    /* LPSPI5_LPSPI5_PCS1_IN input func */
    {263U, 2U, 0U},
    /* INMUX settings for pad PORT15:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_23_IN input func */
    {39U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_10_H_IN input func */
    {58U, 2U, 0U},
    /* FXIO_FXIO_D31_IN input func */
    {183U, 1U, 0U},
    /* LPUART6_LPUART6_RX_IN input func */
    {193U, 2U, 0U},
    /* LPSPI0_LPSPI0_PCS3_IN input func */
    {224U, 1U, 0U},
    /* LPSPI2_LPSPI2_PCS3_IN input func */
    {244U, 1U, 0U},
    /* LPSPI5_LPSPI5_PCS0_IN input func */
    {262U, 3U, 0U},
    /* INMUX settings for pad PORT16:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_4_IN input func */
    {20U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_11_H_IN input func */
    {59U, 2U, 0U},
    /* FXIO_FXIO_D30_IN input func */
    {182U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS4_IN input func */
    {225U, 1U, 0U},
    /* LPSPI1_LPSPI1_PCS2_IN input func */
    {234U, 2U, 0U},
    /* LPSPI4_LPSPI4_PCS3_IN input func */
    {258U, 1U, 0U},
    /* LPUART6_LPUART6_TX_IN input func */
    {369U, 1U, 0U},
    /* LPUART1_LPUART1_DSR_B_IN input func */
    {378U, 1U, 0U},
    /* INMUX settings for pad PORT17:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_6_G_IN input func */
    {54U, 2U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 1U, 0U},
    /* LPSPI3_LPSPI3_SOUT_IN input func */
    {254U, 2U, 0U},
    /* LPUART4_LPUART4_TX_IN input func */
    {367U, 1U, 0U},
    /* INMUX settings for pad PORT18:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_0_IN input func */
    {16U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_16_X_IN input func */
    {96U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_0_X_IN input func */
    {112U, 2U, 0U},
    /* LPSPI1_LPSPI1_SOUT_IN input func */
    {240U, 4U, 0U},
    /* TRGMUX_TRGMUX_IN12_IN input func */
    {356U, 1U, 0U},
    /* LPUART1_LPUART1_TX_IN input func */
    {364U, 4U, 0U},
    /* INMUX settings for pad PORT19:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_1_IN input func */
    {17U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_1_H_IN input func */
    {113U, 2U, 0U},
    /* LPUART1_LPUART1_RX_IN input func */
    {188U, 5U, 0U},
    /* LPSPI1_LPSPI1_SCK_IN input func */
    {238U, 3U, 0U},
    /* TRGMUX_TRGMUX_IN13_IN input func */
    {357U, 1U, 0U},
    /* INMUX settings for pad PORT20:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_2_IN input func */
    {18U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_2_H_IN input func */
    {82U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_2_H_IN input func */
    {114U, 2U, 0U},
    /* LPSPI1_LPSPI1_SIN_IN input func */
    {239U, 3U, 0U},
    /* TRGMUX_TRGMUX_IN14_IN input func */
    {358U, 1U, 0U},
    /* INMUX settings for pad PORT21:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_3_IN input func */
    {19U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_3_H_IN input func */
    {115U, 2U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 3U, 0U},
    /* LPSPI1_LPSPI1_PCS0_IN input func */
    {232U, 3U, 0U},
    /* LPSPI2_LPSPI2_PCS2_IN input func */
    {243U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN15_IN input func */
    {359U, 1U, 0U},
    /* INMUX settings for pad PORT22:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN1_CAN1_RX_IN input func */
    {1U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 1U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 3U, 0U},
    /* LPSPI1_LPSPI1_PCS1_IN input func */
    {233U, 3U, 0U},
    /* INMUX settings for pad PORT23:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_IN input func */
    {86U, 2U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 3U, 0U},
    /* INMUX settings for pad PORT24:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 2U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 3U, 0U},
    /* INMUX settings for pad PORT25:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_5_IN input func */
    {21U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_8_X_IN input func */
    {88U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_8_X_IN input func */
    {120U, 2U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 6U, 0U},
    /* INMUX settings for pad PORT26:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_9_H_IN input func */
    {89U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_9_H_IN input func */
    {121U, 2U, 0U},
    /* GMAC0_GMAC0_PPS0_IN input func */
    {144U, 3U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 7U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 3U, 0U},
    /* LPSPI1_LPSPI1_PCS0_IN input func */
    {232U, 5U, 0U},
    /* INMUX settings for pad PORT27:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_10_H_IN input func */
    {90U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_10_H_IN input func */
    {122U, 2U, 0U},
    /* GMAC0_GMAC0_PPS1_IN input func */
    {145U, 3U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 9U, 0U},
    /* LPUART0_LPUART0_TX_IN input func */
    {363U, 4U, 0U},
    /* INMUX settings for pad PORT28:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN0_CAN0_RX_IN input func */
    {0U, 4U, 0U},
    /* SIUL_EIRQ_6_IN input func */
    {22U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_11_H_IN input func */
    {91U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_11_H_IN input func */
    {123U, 2U, 0U},
    /* LPUART0_LPUART0_RX_IN input func */
    {187U, 4U, 0U},
    /* LPSPI1_LPSPI1_SCK_IN input func */
    {238U, 4U, 0U},
    /* INMUX settings for pad PORT29:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_IN input func */
    {92U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_12_H_IN input func */
    {124U, 1U, 0U},
    /* GMAC0_GMAC0_PPS2_IN input func */
    {146U, 3U, 0U},
    /* LPSPI1_LPSPI1_SIN_IN input func */
    {239U, 4U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 5U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_MDIO_IN input func */
    {454U, 1U, 0U},
    /* INMUX settings for pad PORT30:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_7_IN input func */
    {23U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_13_H_IN input func */
    {93U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_13_H_IN input func */
    {125U, 2U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 4U, 0U},
    /* LPSPI0_LPSPI0_SOUT_IN input func */
    {231U, 4U, 0U},
    /* LPSPI1_LPSPI1_SOUT_IN input func */
    {240U, 5U, 0U},
    /* INMUX settings for pad PORT31:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_14_H_IN input func */
    {94U, 2U, 0U},
    /* GMAC0_GMAC0_PPS0_IN input func */
    {144U, 5U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 6U, 0U},
    /* LPSPI0_LPSPI0_PCS1_IN input func */
    {222U, 2U, 0U},
    /* SAI0_SAI0_MCLK_IN input func */
    {320U, 3U, 0U},
    /* GMAC1_GMAC1_PPS0_IN input func */
    {457U, 1U, 0U},
    /* GMAC1_GMAC1_MII_CRS_IN input func */
    {461U, 2U, 0U},
    /* INMUX settings for pad PORT32:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN0_CAN0_RX_IN input func */
    {0U, 3U, 0U},
    /* SIUL_EIRQ_8_IN input func */
    {24U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_6_H_IN input func */
    {86U, 1U, 0U},
    /* FXIO_FXIO_D14_IN input func */
    {166U, 3U, 0U},
    /* LPUART0_LPUART0_RX_IN input func */
    {187U, 2U, 0U},
    /* LPI2C0_LPI2C0_SDAS_IN input func */
    {215U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 1U, 0U},
    /* INMUX settings for pad PORT33:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_9_IN input func */
    {25U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_7_G_IN input func */
    {55U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 1U, 0U},
    /* LPI2C0_LPI2C0_SCLS_IN input func */
    {213U, 1U, 0U},
    /* LPSPI0_LPSPI0_SOUT_IN input func */
    {231U, 3U, 0U},
    /* HSE_HSE_TAMPER_EXTIN0_IN input func */
    {343U, 1U, 0U},
    /* LPUART0_LPUART0_TX_IN input func */
    {363U, 2U, 0U},
    /* INMUX settings for pad PORT34:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN4_CAN4_RX_IN input func */
    {4U, 2U, 0U},
    /* SIUL_EIRQ_10_IN input func */
    {26U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_8_X_IN input func */
    {56U, 1U, 0U},
    /* FXIO_FXIO_D18_IN input func */
    {170U, 1U, 0U},
    /* LPUART9_LPUART9_RX_IN input func */
    {196U, 2U, 0U},
    /* LPSPI2_LPSPI2_SIN_IN input func */
    {246U, 2U, 0U},
    /* SAI0_SAI0_D0_IN input func */
    {316U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN3_IN input func */
    {347U, 1U, 0U},
    /* INMUX settings for pad PORT35:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_11_IN input func */
    {27U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_9_H_IN input func */
    {57U, 2U, 0U},
    /* FXIO_FXIO_D17_IN input func */
    {169U, 1U, 0U},
    /* LPSPI2_LPSPI2_SOUT_IN input func */
    {247U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_IN input func */
    {296U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_TXD3_IN input func */
    {304U, 4U, 0U},
    /* SAI0_SAI0_MCLK_IN input func */
    {320U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN2_IN input func */
    {346U, 1U, 0U},
    /* LPUART9_LPUART9_TX_IN input func */
    {410U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_IN input func */
    {463U, 2U, 0U},
    /* INMUX settings for pad PORT36:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_12_IN input func */
    {28U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_4_G_IN input func */
    {52U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_10_H_IN input func */
    {90U, 6U, 0U},
    /* LPSPI0_LPSPI0_SOUT_IN input func */
    {231U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_MDIO_IN input func */
    {291U, 1U, 0U},
    /* SAI0_SAI0_D1_IN input func */
    {317U, 2U, 0U},
    /* TRGMUX_TRGMUX_IN1_IN input func */
    {345U, 1U, 0U},
    /* INMUX settings for pad PORT37:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_13_IN input func */
    {29U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_5_G_IN input func */
    {53U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_11_H_IN input func */
    {91U, 5U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 2U, 0U},
    /* LPSPI0_LPSPI0_PCS1_IN input func */
    {222U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN0_IN input func */
    {344U, 1U, 0U},
    /* INMUX settings for pad PORT40:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_14_IN input func */
    {30U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 6U, 0U},
    /* FXIO_FXIO_D29_IN input func */
    {181U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS5_IN input func */
    {226U, 1U, 0U},
    /* LPSPI4_LPSPI4_PCS0_IN input func */
    {255U, 2U, 0U},
    /* LPUART1_LPUART1_DCD_B_IN input func */
    {377U, 1U, 0U},
    /* INMUX settings for pad PORT41:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_15_IN input func */
    {31U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_16_X_IN input func */
    {96U, 5U, 0U},
    /* FXIO_FXIO_D28_IN input func */
    {180U, 1U, 0U},
    /* LPUART9_LPUART9_RX_IN input func */
    {196U, 1U, 0U},
    /* LPSPI4_LPSPI4_SOUT_IN input func */
    {261U, 2U, 0U},
    /* LPUART1_LPUART1_RIN_B_IN input func */
    {376U, 1U, 0U},
    /* INMUX settings for pad PORT42:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_24_IN input func */
    {40U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_17_Y_IN input func */
    {97U, 4U, 0U},
    /* FXIO_FXIO_D27_IN input func */
    {179U, 1U, 0U},
    /* LPSPI4_LPSPI4_SCK_IN input func */
    {259U, 2U, 0U},
    /* LPUART9_LPUART9_TX_IN input func */
    {410U, 2U, 0U},
    /* INMUX settings for pad PORT43:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_25_IN input func */
    {41U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_18_Y_IN input func */
    {98U, 4U, 0U},
    /* FXIO_FXIO_D26_IN input func */
    {178U, 1U, 0U},
    /* LPI2C0_LPI2C0_HREQ_IN input func */
    {211U, 1U, 0U},
    /* LPSPI4_LPSPI4_SIN_IN input func */
    {260U, 2U, 0U},
    /* LPUART0_LPUART0_DSR_B_IN input func */
    {373U, 2U, 0U},
    /* INMUX settings for pad PORT44:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_26_IN input func */
    {42U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_0_X_IN input func */
    {48U, 1U, 0U},
    /* FXIO_FXIO_D25_IN input func */
    {177U, 1U, 0U},
    /* LPUART8_LPUART8_RX_IN input func */
    {195U, 1U, 0U},
    /* LPSPI3_LPSPI3_PCS3_IN input func */
    {251U, 1U, 0U},
    /* LPUART0_LPUART0_DCD_B_IN input func */
    {374U, 2U, 0U},
    /* INMUX settings for pad PORT45:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_27_IN input func */
    {43U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_1_G_IN input func */
    {49U, 2U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 3U, 0U},
    /* FXIO_FXIO_D24_IN input func */
    {176U, 1U, 0U},
    /* LPSPI3_LPSPI3_PCS2_IN input func */
    {250U, 1U, 0U},
    /* LPUART0_LPUART0_RIN_B_IN input func */
    {375U, 2U, 0U},
    /* LPUART8_LPUART8_TX_IN input func */
    {409U, 1U, 0U},
    /* INMUX settings for pad PORT46:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_28_IN input func */
    {44U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_2_G_IN input func */
    {50U, 3U, 0U},
    /* FXIO_FXIO_D23_IN input func */
    {175U, 1U, 0U},
    /* LPUART7_LPUART7_RX_IN input func */
    {194U, 1U, 0U},
    /* LPSPI1_LPSPI1_SCK_IN input func */
    {238U, 2U, 0U},
    /* INMUX settings for pad PORT47:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_29_IN input func */
    {45U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 1U, 0U},
    /* FXIO_FXIO_D22_IN input func */
    {174U, 1U, 0U},
    /* LPSPI1_LPSPI1_SIN_IN input func */
    {239U, 1U, 0U},
    /* LPUART7_LPUART7_TX_IN input func */
    {370U, 1U, 0U},
    /* INMUX settings for pad PORT48:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_30_IN input func */
    {46U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_4_G_IN input func */
    {52U, 2U, 0U},
    /* FXIO_FXIO_D21_IN input func */
    {173U, 1U, 0U},
    /* LPSPI1_LPSPI1_SOUT_IN input func */
    {240U, 2U, 0U},
    /* LPUART4_LPUART4_TX_IN input func */
    {367U, 2U, 0U},
    /* PGI_PGOOD_IN input func */
    {440U, 2U, 0U},
    /* INMUX settings for pad PORT49:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_31_IN input func */
    {47U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_5_G_IN input func */
    {53U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 7U, 0U},
    /* FXIO_FXIO_D20_IN input func */
    {172U, 1U, 0U},
    /* LPUART4_LPUART4_RX_IN input func */
    {191U, 3U, 0U},
    /* LPSPI1_LPSPI1_PCS3_IN input func */
    {235U, 1U, 0U},
    /* LPSPI3_LPSPI3_PCS0_IN input func */
    {248U, 2U, 0U},
    /* INMUX settings for pad PORT50:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_14_H_IN input func */
    {126U, 2U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 6U, 0U},
    /* LPSPI1_LPSPI1_PCS1_IN input func */
    {233U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {292U, 4U, 0U},
    /* LPUART13_LPUART13_TX_IN input func */
    {414U, 1U, 0U},
    /* INMUX settings for pad PORT51:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_15_H_IN input func */
    {127U, 3U, 0U},
    /* GMAC0_GMAC0_PPS0_IN input func */
    {144U, 4U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 5U, 0U},
    /* LPUART13_LPUART13_RX_IN input func */
    {200U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_EN_IN input func */
    {297U, 4U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_MDIO_IN input func */
    {454U, 2U, 0U},
    /* INMUX settings for pad PORT52:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_16_X_IN input func */
    {96U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_16_X_IN input func */
    {128U, 2U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 5U, 0U},
    /* LPUART14_LPUART14_TX_IN input func */
    {415U, 1U, 0U},
    /* GMAC1_GMAC1_PPS2_IN input func */
    {458U, 1U, 0U},
    /* INMUX settings for pad PORT53:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_8_IN input func */
    {24U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_17_Y_IN input func */
    {97U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_17_Y_IN input func */
    {129U, 2U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 5U, 0U},
    /* LPUART14_LPUART14_RX_IN input func */
    {201U, 1U, 0U},
    /* INMUX settings for pad PORT54:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_9_IN input func */
    {25U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_18_Y_IN input func */
    {98U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_18_Y_IN input func */
    {130U, 2U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 5U, 0U},
    /* LPSPI3_LPSPI3_PCS1_IN input func */
    {249U, 4U, 0U},
    /* GMAC0_GMAC0_MII_CRS_IN input func */
    {290U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {292U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RX_CLK_IN input func */
    {300U, 7U, 0U},
    /* LPUART1_LPUART1_TX_IN input func */
    {364U, 5U, 0U},
    /* INMUX settings for pad PORT55:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN1_CAN1_RX_IN input func */
    {1U, 4U, 0U},
    /* SIUL_EIRQ_10_IN input func */
    {26U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_19_Y_IN input func */
    {99U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_19_Y_IN input func */
    {131U, 2U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 6U, 0U},
    /* LPUART1_LPUART1_RX_IN input func */
    {188U, 4U, 0U},
    /* GMAC0_GMAC0_MII_COL_IN input func */
    {289U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_IN input func */
    {294U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_IN input func */
    {295U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RXD2_IN input func */
    {301U, 5U, 0U},
    /* INMUX settings for pad PORT56:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_11_IN input func */
    {27U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_20_Y_IN input func */
    {100U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_20_Y_IN input func */
    {132U, 2U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 6U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_IN input func */
    {295U, 4U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RXD2_IN input func */
    {301U, 4U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RXD3_IN input func */
    {302U, 3U, 0U},
    /* INMUX settings for pad PORT57:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_12_IN input func */
    {28U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_21_Y_IN input func */
    {101U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_21_Y_IN input func */
    {133U, 2U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 5U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 4U, 0U},
    /* GMAC0_GMAC0_MII_COL_IN input func */
    {289U, 3U, 0U},
    /* LPUART15_LPUART15_TX_IN input func */
    {416U, 1U, 0U},
    /* GMAC0_GMAC0_RGMII_TXCTL_IN input func */
    {469U, 1U, 0U},
    /* INMUX settings for pad PORT58:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_13_IN input func */
    {29U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_22_X_IN input func */
    {102U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_22_X_IN input func */
    {134U, 2U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 6U, 0U},
    /* LPUART15_LPUART15_RX_IN input func */
    {202U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RX_CLK_IN input func */
    {300U, 5U, 0U},
    /* INMUX settings for pad PORT59:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_23_X_IN input func */
    {103U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_23_X_IN input func */
    {135U, 2U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 2U, 0U},
    /* LPSPI2_LPSPI2_SOUT_IN input func */
    {247U, 3U, 0U},
    /* SAI0_SAI0_D0_IN input func */
    {316U, 2U, 0U},
    /* LPUART5_LPUART5_TX_IN input func */
    {368U, 3U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RX_ER_IN input func */
    {460U, 1U, 0U},
    /* INMUX settings for pad PORT60:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_14_IN input func */
    {30U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_10_H_IN input func */
    {122U, 3U, 0U},
    /* GMAC0_GMAC0_PPS3_IN input func */
    {147U, 2U, 0U},
    /* FXIO_FXIO_D9_IN input func */
    {161U, 2U, 0U},
    /* LPUART5_LPUART5_RX_IN input func */
    {192U, 4U, 0U},
    /* LPSPI2_LPSPI2_SIN_IN input func */
    {246U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_TXD2_IN input func */
    {303U, 4U, 0U},
    /* INMUX settings for pad PORT61:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN4_CAN4_RX_IN input func */
    {4U, 6U, 0U},
    /* EMIOS_2_EMIOS_2_CH_11_H_IN input func */
    {123U, 3U, 0U},
    /* FXIO_FXIO_D10_IN input func */
    {162U, 2U, 0U},
    /* LPSPI2_LPSPI2_SCK_IN input func */
    {245U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_IN input func */
    {298U, 3U, 0U},
    /* SAI0_SAI0_D1_IN input func */
    {317U, 1U, 0U},
    /* LPUART6_LPUART6_TX_IN input func */
    {369U, 3U, 0U},
    /* INMUX settings for pad PORT62:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D11_IN input func */
    {163U, 2U, 0U},
    /* INMUX settings for pad PORT63:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_15_IN input func */
    {31U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_19_Y_IN input func */
    {67U, 5U, 0U},
    /* HSE_HSE_TAMPER_EXTIN0_IN input func */
    {343U, 3U, 0U},
    /* INMUX settings for pad PORT64:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_0_IN input func */
    {16U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_0_X_IN input func */
    {48U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_14_H_IN input func */
    {62U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RXD_0_IN input func */
    {294U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RXD_1_IN input func */
    {295U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_IN input func */
    {296U, 4U, 0U},
    /* GMAC1_GMAC1_MII_RGMII_TXD2_IN input func */
    {464U, 1U, 0U},
    /* INMUX settings for pad PORT65:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN3_CAN3_RX_IN input func */
    {3U, 2U, 0U},
    /* SIUL_EIRQ_1_IN input func */
    {17U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_1_G_IN input func */
    {49U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_15_H_IN input func */
    {63U, 1U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 7U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RXD_0_IN input func */
    {294U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RXD_1_IN input func */
    {295U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_IN input func */
    {296U, 7U, 0U},
    /* GMAC0_GMAC0_MII_RX_CLK_IN input func */
    {300U, 3U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_IN input func */
    {463U, 1U, 0U},
    /* INMUX settings for pad PORT66:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN0_CAN0_RX_IN input func */
    {0U, 1U, 0U},
    /* SIUL_EIRQ_2_IN input func */
    {18U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_2_G_IN input func */
    {50U, 2U, 0U},
    /* LPUART0_LPUART0_RX_IN input func */
    {187U, 3U, 0U},
    /* LPSPI0_LPSPI0_PCS2_IN input func */
    {223U, 2U, 0U},
    /* LPSPI3_LPSPI3_PCS2_IN input func */
    {250U, 4U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TXD_0_IN input func */
    {298U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TXD_1_IN input func */
    {299U, 2U, 0U},
    /* QUADSPI_QUADSPI_IOFA3_IN input func */
    {308U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RGMII_RXD3_IN input func */
    {451U, 1U, 0U},
    /* INMUX settings for pad PORT67:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_3_IN input func */
    {19U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 3U, 0U},
    /* LPUART0_LPUART0_TX_IN input func */
    {363U, 3U, 0U},
    /* GMAC1_GMAC1_MII_RMII_TX_EN_IN input func */
    {459U, 1U, 0U},
    /* INMUX settings for pad PORT68:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_4_IN input func */
    {20U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_8_X_IN input func */
    {56U, 2U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 8U, 0U},
    /* JTAG_JTAG_TCKSWD_CLK_IN input func */
    {184U, 0U, 0U},
    /* INMUX settings for pad PORT69:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_5_IN input func */
    {21U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_16_X_IN input func */
    {64U, 2U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 7U, 0U},
    /* JTAG_JTAG_TDI_IN input func */
    {185U, 0U, 0U},
    /* LPI2C1_LPI2C1_HREQ_IN input func */
    {216U, 2U, 0U},
    /* INMUX settings for pad PORT70:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN2_CAN2_RX_IN input func */
    {2U, 6U, 0U},
    /* SIUL_EIRQ_6_IN input func */
    {22U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_6_H_IN input func */
    {86U, 4U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 3U, 0U},
    /* LPUART1_LPUART1_RX_IN input func */
    {188U, 1U, 0U},
    /* LPI2C1_LPI2C1_SDA_IN input func */
    {219U, 2U, 0U},
    /* LPSPI0_LPSPI0_PCS1_IN input func */
    {222U, 4U, 0U},
    /* LPSPI1_LPSPI1_PCS1_IN input func */
    {233U, 4U, 0U},
    /* INMUX settings for pad PORT71:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_7_IN input func */
    {23U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 4U, 0U},
    /* FXIO_FXIO_D10_IN input func */
    {162U, 3U, 0U},
    /* LPI2C0_LPI2C0_HREQ_IN input func */
    {211U, 2U, 0U},
    /* LPI2C1_LPI2C1_SCL_IN input func */
    {217U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 6U, 0U},
    /* LPUART1_LPUART1_TX_IN input func */
    {364U, 1U, 0U},
    /* INMUX settings for pad PORT72:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_16_IN input func */
    {32U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_9_H_IN input func */
    {89U, 1U, 0U},
    /* FXIO_FXIO_D12_IN input func */
    {164U, 3U, 0U},
    /* LPUART1_LPUART1_RX_IN input func */
    {188U, 2U, 0U},
    /* LPI2C0_LPI2C0_SCL_IN input func */
    {212U, 1U, 0U},
    /* LPSPI0_LPSPI0_SCK_IN input func */
    {229U, 1U, 0U},
    /* LPUART0_LPUART0_CTS_IN input func */
    {360U, 2U, 0U},
    /* INMUX settings for pad PORT73:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN1_CAN1_RX_IN input func */
    {1U, 1U, 0U},
    /* SIUL_EIRQ_17_IN input func */
    {33U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_8_X_IN input func */
    {88U, 1U, 0U},
    /* FXIO_FXIO_D13_IN input func */
    {165U, 3U, 0U},
    /* LPI2C0_LPI2C0_SDA_IN input func */
    {214U, 1U, 0U},
    /* LPSPI0_LPSPI0_SIN_IN input func */
    {230U, 2U, 0U},
    /* LPUART1_LPUART1_TX_IN input func */
    {364U, 2U, 0U},
    /* INMUX settings for pad PORT74:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_18_IN input func */
    {34U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_6_G_IN input func */
    {54U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 6U, 0U},
    /* LPSPI2_LPSPI2_PCS1_IN input func */
    {242U, 3U, 0U},
    /* LPSPI4_LPSPI4_PCS0_IN input func */
    {255U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN11_IN input func */
    {355U, 1U, 0U},
    /* LPUART0_LPUART0_DSR_B_IN input func */
    {373U, 1U, 0U},
    /* LPUART11_LPUART11_TX_IN input func */
    {412U, 2U, 0U},
    /* INMUX settings for pad PORT75:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN5_CAN5_RX_IN input func */
    {5U, 2U, 0U},
    /* SIUL_EIRQ_19_IN input func */
    {35U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 7U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 3U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 3U, 0U},
    /* LPUART11_LPUART11_RX_IN input func */
    {198U, 1U, 0U},
    /* LPSPI4_LPSPI4_SOUT_IN input func */
    {261U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN10_IN input func */
    {354U, 1U, 0U},
    /* INMUX settings for pad PORT76:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_20_IN input func */
    {36U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_22_X_IN input func */
    {70U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_2_H_IN input func */
    {82U, 1U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 5U, 0U},
    /* LPUART10_LPUART10_RX_IN input func */
    {197U, 2U, 0U},
    /* LPSPI2_LPSPI2_PCS1_IN input func */
    {242U, 4U, 0U},
    /* SAI0_SAI0_BCLK_IN input func */
    {315U, 1U, 0U},
    /* INMUX settings for pad PORT77:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_21_IN input func */
    {37U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_23_X_IN input func */
    {71U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 7U, 0U},
    /* FXIO_FXIO_D16_IN input func */
    {168U, 3U, 0U},
    /* SAI0_SAI0_SYNC_IN input func */
    {321U, 1U, 0U},
    /* LPUART10_LPUART10_TX_IN input func */
    {411U, 1U, 0U},
    /* INMUX settings for pad PORT78:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN2_CAN2_RX_IN input func */
    {2U, 2U, 0U},
    /* SIUL_EIRQ_22_IN input func */
    {38U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_10_H_IN input func */
    {58U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 8U, 0U},
    /* FXIO_FXIO_D16_IN input func */
    {168U, 1U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 2U, 0U},
    /* GMAC0_GMAC0_MII_COL_IN input func */
    {289U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_ER_IN input func */
    {293U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_IN input func */
    {294U, 4U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RXD2_IN input func */
    {301U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RXD3_IN input func */
    {302U, 2U, 0U},
    /* TRGMUX_TRGMUX_IN9_IN input func */
    {353U, 1U, 0U},
    /* INMUX settings for pad PORT79:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_23_IN input func */
    {39U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_11_H_IN input func */
    {59U, 1U, 0U},
    /* LPI2C1_LPI2C1_SCL_IN input func */
    {217U, 6U, 0U},
    /* LPSPI2_LPSPI2_SCK_IN input func */
    {245U, 2U, 0U},
    /* GMAC0_GMAC0_MII_CRS_IN input func */
    {290U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {292U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_IN input func */
    {294U, 6U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_IN input func */
    {295U, 6U, 0U},
    /* GMAC0_GMAC0_MII_RXD2_IN input func */
    {301U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RXD3_IN input func */
    {302U, 4U, 0U},
    /* TRGMUX_TRGMUX_IN8_IN input func */
    {352U, 1U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 2U, 0U},
    /* INMUX settings for pad PORT80:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN2_CAN2_RX_IN input func */
    {2U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_9_H_IN input func */
    {89U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_9_H_IN input func */
    {121U, 4U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 1U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 5U, 0U},
    /* LPI2C1_LPI2C1_SDA_IN input func */
    {219U, 5U, 0U},
    /* LPI2C1_LPI2C1_SDAS_IN input func */
    {220U, 1U, 0U},
    /* LPSPI3_LPSPI3_SIN_IN input func */
    {253U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {292U, 6U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_ER_IN input func */
    {293U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RGMII_RX_CLK_IN input func */
    {300U, 6U, 0U},
    /* INMUX settings for pad PORT81:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D2_IN input func */
    {154U, 10U, 0U},
    /* FXIO_FXIO_D14_IN input func */
    {166U, 1U, 0U},
    /* LPI2C1_LPI2C1_SCLS_IN input func */
    {218U, 2U, 0U},
    /* LPSPI3_LPSPI3_SCK_IN input func */
    {252U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {292U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_TXD_1_IN input func */
    {467U, 1U, 0U},
    /* INMUX settings for pad PORT82:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_12_H_IN input func */
    {124U, 3U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 9U, 0U},
    /* FXIO_FXIO_D12_IN input func */
    {164U, 2U, 0U},
    /* LPUART6_LPUART6_RX_IN input func */
    {193U, 4U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_TXD_1_IN input func */
    {299U, 3U, 0U},
    /* SAI0_SAI0_D2_IN input func */
    {318U, 1U, 0U},
    /* INMUX settings for pad PORT83:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_13_H_IN input func */
    {125U, 3U, 0U},
    /* FXIO_FXIO_D13_IN input func */
    {165U, 2U, 0U},
    /* LPSPI2_LPSPI2_PCS1_IN input func */
    {242U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_IN input func */
    {296U, 6U, 0U},
    /* SAI0_SAI0_D3_IN input func */
    {319U, 1U, 0U},
    /* LPUART7_LPUART7_TX_IN input func */
    {370U, 2U, 0U},
    /* INMUX settings for pad PORT84:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_16_IN input func */
    {32U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_14_H_IN input func */
    {126U, 3U, 0U},
    /* GMAC0_GMAC0_PPS0_IN input func */
    {144U, 6U, 0U},
    /* FXIO_FXIO_D14_IN input func */
    {166U, 2U, 0U},
    /* LPUART7_LPUART7_RX_IN input func */
    {194U, 4U, 0U},
    /* INMUX settings for pad PORT85:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_17_IN input func */
    {33U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_15_H_IN input func */
    {127U, 5U, 0U},
    /* GMAC0_GMAC0_PPS1_IN input func */
    {145U, 4U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 2U, 0U},
    /* INMUX settings for pad PORT86:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_8_X_IN input func */
    {56U, 3U, 0U},
    /* INMUX settings for pad PORT87:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_18_IN input func */
    {34U, 3U, 0U},
    /* FXIO_FXIO_D16_IN input func */
    {168U, 2U, 0U},
    /* CAN6_CAN6_RX_IN input func */
    {417U, 1U, 0U},
    /* INMUX settings for pad PORT88:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_19_IN input func */
    {35U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_0_X_IN input func */
    {112U, 5U, 0U},
    /* FXIO_FXIO_D17_IN input func */
    {169U, 2U, 0U},
    /* LPUART12_LPUART12_TX_IN input func */
    {413U, 1U, 0U},
    /* INMUX settings for pad PORT89:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_20_IN input func */
    {36U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_1_H_IN input func */
    {113U, 3U, 0U},
    /* FXIO_FXIO_D18_IN input func */
    {170U, 2U, 0U},
    /* LPUART12_LPUART12_RX_IN input func */
    {199U, 2U, 0U},
    /* LPSPI4_LPSPI4_PCS1_IN input func */
    {256U, 4U, 0U},
    /* CAN7_CAN7_RX_IN input func */
    {418U, 1U, 0U},
    /* INMUX settings for pad PORT90:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN5_CAN5_RX_IN input func */
    {5U, 5U, 0U},
    /* SIUL_EIRQ_21_IN input func */
    {37U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_2_H_IN input func */
    {114U, 3U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 2U, 0U},
    /* LPUART13_LPUART13_RX_IN input func */
    {200U, 4U, 0U},
    /* LPSPI4_LPSPI4_SIN_IN input func */
    {260U, 1U, 0U},
    /* LPUART13_LPUART13_TX_IN input func */
    {414U, 2U, 0U},
    /* INMUX settings for pad PORT91:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_22_IN input func */
    {38U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_3_H_IN input func */
    {115U, 3U, 0U},
    /* FXIO_FXIO_D20_IN input func */
    {172U, 2U, 0U},
    /* LPUART13_LPUART13_RX_IN input func */
    {200U, 2U, 0U},
    /* LPSPI4_LPSPI4_SCK_IN input func */
    {259U, 1U, 0U},
    /* LPUART13_LPUART13_TX_IN input func */
    {414U, 4U, 0U},
    /* INMUX settings for pad PORT92:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 3U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 7U, 0U},
    /* FXIO_FXIO_D21_IN input func */
    {173U, 2U, 0U},
    /* LPI2C1_LPI2C1_SCL_IN input func */
    {217U, 4U, 0U},
    /* LPUART0_LPUART0_TX_IN input func */
    {363U, 6U, 0U},
    /* LPUART1_LPUART1_RIN_B_IN input func */
    {376U, 2U, 0U},
    /* INMUX settings for pad PORT93:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN3_CAN3_RX_IN input func */
    {3U, 3U, 0U},
    /* SIUL_EIRQ_23_IN input func */
    {39U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_10_H_IN input func */
    {90U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_4_H_IN input func */
    {116U, 2U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 6U, 0U},
    /* FXIO_FXIO_D22_IN input func */
    {174U, 2U, 0U},
    /* LPUART0_LPUART0_RX_IN input func */
    {187U, 6U, 0U},
    /* LPI2C1_LPI2C1_SDA_IN input func */
    {219U, 3U, 0U},
    /* LPUART1_LPUART1_DCD_B_IN input func */
    {377U, 2U, 0U},
    /* INMUX settings for pad PORT94:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_IN input func */
    {92U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_5_H_IN input func */
    {117U, 3U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 4U, 0U},
    /* FXIO_FXIO_D23_IN input func */
    {175U, 2U, 0U},
    /* LPUART1_LPUART1_DSR_B_IN input func */
    {378U, 2U, 0U},
    /* INMUX settings for pad PORT95:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN4_CAN4_RX_IN input func */
    {4U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_14_H_IN input func */
    {94U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_6_H_IN input func */
    {118U, 2U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 4U, 0U},
    /* FXIO_FXIO_D24_IN input func */
    {176U, 2U, 0U},
    /* INMUX settings for pad PORT96:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_8_IN input func */
    {24U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_2_G_IN input func */
    {50U, 1U, 0U},
    /* EMIOS_0_EMIOS_0_CH_16_X_IN input func */
    {64U, 1U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 1U, 0U},
    /* LPUART5_LPUART5_RX_IN input func */
    {192U, 2U, 0U},
    /* LPSPI3_LPSPI3_SOUT_IN input func */
    {254U, 1U, 0U},
    /* INMUX settings for pad PORT97:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_9_IN input func */
    {25U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_17_Y_IN input func */
    {65U, 1U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 1U, 0U},
    /* LPSPI3_LPSPI3_SCK_IN input func */
    {252U, 1U, 0U},
    /* LPUART5_LPUART5_TX_IN input func */
    {368U, 1U, 0U},
    /* INMUX settings for pad PORT98:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_10_IN input func */
    {26U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_21_Y_IN input func */
    {101U, 4U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 1U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 3U, 0U},
    /* LPSPI1_LPSPI1_SOUT_IN input func */
    {240U, 1U, 0U},
    /* LPSPI5_LPSPI5_SOUT_IN input func */
    {268U, 2U, 0U},
    /* TRGMUX_TRGMUX_IN5_IN input func */
    {349U, 1U, 0U},
    /* LPUART3_LPUART3_TX_IN input func */
    {366U, 2U, 0U},
    /* INMUX settings for pad PORT99:   {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_11_IN input func */
    {27U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_22_X_IN input func */
    {102U, 4U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 2U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 3U, 0U},
    /* LPUART3_LPUART3_RX_IN input func */
    {190U, 3U, 0U},
    /* LPSPI1_LPSPI1_PCS0_IN input func */
    {232U, 1U, 0U},
    /* TRGMUX_TRGMUX_IN4_IN input func */
    {348U, 1U, 0U},
    /* INMUX settings for pad PORT100:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_12_IN input func */
    {28U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_23_X_IN input func */
    {103U, 4U, 0U},
    /* LPSPI1_LPSPI1_PCS1_IN input func */
    {233U, 6U, 0U},
    /* LPSPI5_LPSPI5_PCS0_IN input func */
    {262U, 2U, 0U},
    /* INMUX settings for pad PORT101:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_13_IN input func */
    {29U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_2_G_IN input func */
    {50U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_19_Y_IN input func */
    {67U, 2U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 4U, 0U},
    /* LPSPI0_LPSPI0_PCS1_IN input func */
    {222U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RX_CLK_IN input func */
    {300U, 2U, 0U},
    /* GMAC0_GMAC0_MII_TXD2_IN input func */
    {303U, 3U, 0U},
    /* GMAC0_GMAC0_MII_TXD3_IN input func */
    {304U, 1U, 0U},
    /* SAI0_SAI0_D3_IN input func */
    {319U, 2U, 0U},
    /* TRGMUX_TRGMUX_IN7_IN input func */
    {351U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {448U, 1U, 0U},
    /* INMUX settings for pad PORT102:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_14_IN input func */
    {30U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_12_H_IN input func */
    {92U, 5U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 9U, 0U},
    /* FXIO_FXIO_D13_IN input func */
    {165U, 1U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 7U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_IN input func */
    {296U, 2U, 0U},
    /* GMAC0_GMAC0_MII_TXD2_IN input func */
    {303U, 1U, 0U},
    /* GMAC0_GMAC0_MII_TXD3_IN input func */
    {304U, 3U, 0U},
    /* SAI0_SAI0_D2_IN input func */
    {318U, 2U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_RXD_0_IN input func */
    {449U, 1U, 0U},
    /* INMUX settings for pad PORT103:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_15_IN input func */
    {31U, 3U, 0U},
    /* LPSPI0_LPSPI0_PCS3_IN input func */
    {224U, 2U, 0U},
    /* LPSPI3_LPSPI3_PCS3_IN input func */
    {251U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TXD_0_IN input func */
    {298U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TXD_1_IN input func */
    {299U, 1U, 0U},
    /* QUADSPI_QUADSPI_IOFA1_IN input func */
    {306U, 1U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 3U, 0U},
    /* GMAC1_GMAC1_MII_RGMII_RXD2_IN input func */
    {453U, 1U, 0U},
    /* INMUX settings for pad PORT104:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_24_IN input func */
    {40U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_12_H_IN input func */
    {60U, 1U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 5U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 5U, 0U},
    /* LPUART6_LPUART6_RX_IN input func */
    {193U, 1U, 0U},
    /* LPI2C1_LPI2C1_SDA_IN input func */
    {219U, 1U, 0U},
    /* LPSPI3_LPSPI3_SOUT_IN input func */
    {254U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RXD_1_IN input func */
    {295U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RXD3_IN input func */
    {302U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_TXD_0_IN input func */
    {466U, 1U, 0U},
    /* INMUX settings for pad PORT105:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_25_IN input func */
    {41U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_13_H_IN input func */
    {61U, 2U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 5U, 0U},
    /* FXIO_FXIO_D10_IN input func */
    {162U, 4U, 0U},
    /* LPI2C1_LPI2C1_SCL_IN input func */
    {217U, 2U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RXD_0_IN input func */
    {294U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RXD2_IN input func */
    {301U, 1U, 0U},
    /* LPUART6_LPUART6_TX_IN input func */
    {369U, 2U, 0U},
    /* GMAC1_GMAC1_MII_RGMII_TXD3_IN input func */
    {465U, 1U, 0U},
    /* INMUX settings for pad PORT106:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_26_IN input func */
    {42U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_16_X_IN input func */
    {64U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_10_H_IN input func */
    {90U, 2U, 0U},
    /* LPSPI0_LPSPI0_SIN_IN input func */
    {230U, 4U, 0U},
    /* GMAC0_GMAC0_MII_RX_CLK_IN input func */
    {300U, 1U, 0U},
    /* GMAC0_GMAC0_MII_TXD3_IN input func */
    {304U, 2U, 0U},
    /* QUADSPI_QUADSPI_SCKFA_IN input func */
    {309U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RGMII_RX_CLK_IN input func */
    {450U, 1U, 0U},
    /* INMUX settings for pad PORT107:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_27_IN input func */
    {43U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_17_Y_IN input func */
    {65U, 3U, 0U},
    /* LPSPI0_LPSPI0_SCK_IN input func */
    {229U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_IN input func */
    {296U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_EN_IN input func */
    {297U, 2U, 0U},
    /* GMAC0_GMAC0_MII_TXD2_IN input func */
    {303U, 2U, 0U},
    /* QUADSPI_QUADSPI_IOFA0_IN input func */
    {305U, 1U, 0U},
    /* LPUART2_LPUART2_CTS_IN input func */
    {362U, 1U, 0U},
    /* GMAC1_GMAC1_RGMII_TXCTL_IN input func */
    {468U, 1U, 0U},
    /* INMUX settings for pad PORT108:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_28_IN input func */
    {44U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_18_Y_IN input func */
    {66U, 1U, 0U},
    /* LPI2C1_LPI2C1_HREQ_IN input func */
    {216U, 1U, 0U},
    /* LPSPI0_LPSPI0_SOUT_IN input func */
    {231U, 5U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_IN input func */
    {296U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_EN_IN input func */
    {297U, 1U, 0U},
    /* QUADSPI_QUADSPI_IOFA2_IN input func */
    {307U, 1U, 0U},
    /* GMAC1_GMAC1_MII_RMII_RGMII_RXD_1_IN input func */
    {452U, 1U, 0U},
    /* INMUX settings for pad PORT109:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_29_IN input func */
    {45U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_20_Y_IN input func */
    {68U, 1U, 0U},
    /* GMAC0_GMAC0_PPS1_IN input func */
    {145U, 2U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 7U, 0U},
    /* LPUART1_LPUART1_RX_IN input func */
    {188U, 3U, 0U},
    /* LPI2C0_LPI2C0_SDA_IN input func */
    {214U, 2U, 0U},
    /* LPSPI5_LPSPI5_SIN_IN input func */
    {267U, 1U, 0U},
    /* SAI1_SAI1_D0_IN input func */
    {323U, 1U, 0U},
    /* INMUX settings for pad PORT110:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_30_IN input func */
    {46U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_21_Y_IN input func */
    {69U, 1U, 0U},
    /* GMAC0_GMAC0_PPS0_IN input func */
    {144U, 2U, 0U},
    /* LPI2C0_LPI2C0_SCL_IN input func */
    {212U, 2U, 0U},
    /* LPSPI5_LPSPI5_SCK_IN input func */
    {266U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_IN input func */
    {292U, 3U, 0U},
    /* SAI0_SAI0_MCLK_IN input func */
    {320U, 4U, 0U},
    /* SAI1_SAI1_MCLK_IN input func */
    {324U, 1U, 0U},
    /* LPUART1_LPUART1_TX_IN input func */
    {364U, 3U, 0U},
    /* GMAC1_GMAC1_MII_COL_IN input func */
    {462U, 1U, 0U},
    /* INMUX settings for pad PORT111:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN3_CAN3_RX_IN input func */
    {3U, 1U, 0U},
    /* SIUL_EIRQ_31_IN input func */
    {47U, 2U, 0U},
    /* EMIOS_0_EMIOS_0_CH_0_X_IN input func */
    {48U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_14_H_IN input func */
    {94U, 6U, 0U},
    /* GMAC0_GMAC0_PPS2_IN input func */
    {146U, 2U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 7U, 0U},
    /* FXIO_FXIO_D10_IN input func */
    {162U, 1U, 0U},
    /* LPUART8_LPUART8_RX_IN input func */
    {195U, 2U, 0U},
    /* LPSPI0_LPSPI0_SCK_IN input func */
    {229U, 3U, 0U},
    /* SAI1_SAI1_SYNC_IN input func */
    {325U, 1U, 0U},
    /* LPUART2_LPUART2_CTS_IN input func */
    {362U, 2U, 0U},
    /* GMAC1_GMAC1_MII_CRS_IN input func */
    {461U, 1U, 0U},
    /* INMUX settings for pad PORT112:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_1_G_IN input func */
    {49U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 7U, 0U},
    /* LPSPI0_LPSPI0_SIN_IN input func */
    {230U, 3U, 0U},
    /* GMAC0_GMAC0_MII_RMII_RGMII_MDIO_IN input func */
    {291U, 2U, 0U},
    /* LPUART8_LPUART8_TX_IN input func */
    {409U, 2U, 0U},
    /* INMUX settings for pad PORT113:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN5_CAN5_RX_IN input func */
    {5U, 1U, 0U},
    /* SIUL_EIRQ_24_IN input func */
    {40U, 3U, 0U},
    /* EMIOS_0_EMIOS_0_CH_18_Y_IN input func */
    {66U, 3U, 0U},
    /* GMAC0_GMAC0_PPS2_IN input func */
    {146U, 1U, 0U},
    /* FXIO_FXIO_D9_IN input func */
    {161U, 1U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 2U, 0U},
    /* LPSPI3_LPSPI3_PCS0_IN input func */
    {248U, 1U, 0U},
    /* LPSPI5_LPSPI5_PCS0_IN input func */
    {262U, 1U, 0U},
    /* INMUX settings for pad PORT114:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 1U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 4U, 0U},
    /* INMUX settings for pad PORT115:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN2_CAN2_RX_IN input func */
    {2U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_16_X_IN input func */
    {96U, 2U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 4U, 0U},
    /* INMUX settings for pad PORT116:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_25_IN input func */
    {41U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_17_Y_IN input func */
    {97U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_0_X_IN input func */
    {112U, 3U, 0U},
    /* FXIO_FXIO_D25_IN input func */
    {177U, 2U, 0U},
    /* LPSPI1_LPSPI1_PCS2_IN input func */
    {234U, 1U, 0U},
    /* LPSPI3_LPSPI3_SIN_IN input func */
    {253U, 2U, 0U},
    /* INMUX settings for pad PORT117:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_26_IN input func */
    {42U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_18_Y_IN input func */
    {98U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_8_X_IN input func */
    {120U, 3U, 0U},
    /* FXIO_FXIO_D26_IN input func */
    {178U, 2U, 0U},
    /* INMUX settings for pad PORT118:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_27_IN input func */
    {43U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_19_Y_IN input func */
    {99U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_22_X_IN input func */
    {134U, 3U, 0U},
    /* FXIO_FXIO_D27_IN input func */
    {179U, 2U, 0U},
    /* INMUX settings for pad PORT119:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_28_IN input func */
    {44U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_20_Y_IN input func */
    {100U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_23_X_IN input func */
    {135U, 3U, 0U},
    /* FXIO_FXIO_D28_IN input func */
    {180U, 2U, 0U},
    /* INMUX settings for pad PORT120:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_29_IN input func */
    {45U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_21_Y_IN input func */
    {101U, 1U, 0U},
    /* FXIO_FXIO_D29_IN input func */
    {181U, 2U, 0U},
    /* HSE_HSE_TAMPER_EXTIN0_IN input func */
    {343U, 2U, 0U},
    /* INMUX settings for pad PORT121:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_22_X_IN input func */
    {102U, 1U, 0U},
    /* INMUX settings for pad PORT122:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_23_X_IN input func */
    {103U, 1U, 0U},
    /* EMIOS_2_EMIOS_2_CH_7_H_IN input func */
    {119U, 1U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 4U, 0U},
    /* FXIO_FXIO_D30_IN input func */
    {182U, 2U, 0U},
    /* LPSPI5_LPSPI5_SCK_IN input func */
    {266U, 3U, 0U},
    /* LPUART14_LPUART14_TX_IN input func */
    {415U, 2U, 0U},
    /* INMUX settings for pad PORT123:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_30_IN input func */
    {46U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_9_H_IN input func */
    {121U, 3U, 0U},
    /* FXIO_FXIO_D31_IN input func */
    {183U, 2U, 0U},
    /* LPUART14_LPUART14_RX_IN input func */
    {201U, 2U, 0U},
    /* LPSPI5_LPSPI5_SOUT_IN input func */
    {268U, 3U, 0U},
    /* INMUX settings for pad PORT124:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_31_IN input func */
    {47U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_0_X_IN input func */
    {112U, 4U, 0U},
    /* LPSPI5_LPSPI5_SIN_IN input func */
    {267U, 3U, 0U},
    /* LPUART15_LPUART15_TX_IN input func */
    {416U, 2U, 0U},
    /* INMUX settings for pad PORT125:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_8_X_IN input func */
    {120U, 4U, 0U},
    /* LPUART15_LPUART15_RX_IN input func */
    {202U, 2U, 0U},
    /* LPSPI5_LPSPI5_PCS2_IN input func */
    {264U, 1U, 0U},
    /* CAN6_CAN6_RX_IN input func */
    {417U, 2U, 0U},
    /* INMUX settings for pad PORT126:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_16_X_IN input func */
    {128U, 3U, 0U},
    /* LPSPI5_LPSPI5_PCS3_IN input func */
    {265U, 1U, 0U},
    /* INMUX settings for pad PORT127:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_22_X_IN input func */
    {134U, 4U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 4U, 0U},
    /* LPSPI5_LPSPI5_SCK_IN input func */
    {266U, 5U, 0U},
    /* CAN7_CAN7_RX_IN input func */
    {418U, 2U, 0U},
    /* INMUX settings for pad PORT128:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_0_IN input func */
    {16U, 4U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 7U, 0U},
    /* LPUART7_LPUART7_RX_IN input func */
    {194U, 2U, 0U},
    /* LPSPI0_LPSPI0_SIN_IN input func */
    {230U, 1U, 0U},
    /* INMUX settings for pad PORT129:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_1_IN input func */
    {17U, 4U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 8U, 0U},
    /* LPSPI0_LPSPI0_SCK_IN input func */
    {229U, 2U, 0U},
    /* LPUART7_LPUART7_TX_IN input func */
    {370U, 3U, 0U},
    /* INMUX settings for pad PORT130:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_2_IN input func */
    {18U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_8_X_IN input func */
    {88U, 4U, 0U},
    /* FXIO_FXIO_D13_IN input func */
    {165U, 4U, 0U},
    /* LPUART10_LPUART10_RX_IN input func */
    {197U, 1U, 0U},
    /* LPSPI0_LPSPI0_SOUT_IN input func */
    {231U, 1U, 0U},
    /* LPUART1_LPUART1_CTS_IN input func */
    {361U, 1U, 0U},
    /* INMUX settings for pad PORT131:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_3_IN input func */
    {19U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_19_Y_IN input func */
    {67U, 4U, 0U},
    /* GMAC0_GMAC0_PPS0_IN input func */
    {144U, 1U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 6U, 0U},
    /* LPUART5_LPUART5_RX_IN input func */
    {192U, 1U, 0U},
    /* SAI1_SAI1_D0_IN input func */
    {323U, 2U, 0U},
    /* TRGMUX_TRGMUX_IN6_IN input func */
    {350U, 1U, 0U},
    /* GMAC1_GMAC1_PPS3_IN input func */
    {456U, 1U, 0U},
    /* GMAC1_GMAC1_MII_COL_IN input func */
    {462U, 2U, 0U},
    /* INMUX settings for pad PORT132:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_4_IN input func */
    {20U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_18_Y_IN input func */
    {66U, 2U, 0U},
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 4U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 1U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 5U, 0U},
    /* LPSPI1_LPSPI1_PCS1_IN input func */
    {233U, 5U, 0U},
    /* LPUART12_LPUART12_TX_IN input func */
    {413U, 2U, 0U},
    /* INMUX settings for pad PORT133:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_5_IN input func */
    {21U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_19_Y_IN input func */
    {67U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 4U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 1U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 6U, 0U},
    /* LPUART12_LPUART12_RX_IN input func */
    {199U, 1U, 0U},
    /* INMUX settings for pad PORT134:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_6_IN input func */
    {22U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_14_H_IN input func */
    {94U, 5U, 0U},
    /* FXIO_FXIO_D12_IN input func */
    {164U, 4U, 0U},
    /* LPSPI0_LPSPI0_PCS2_IN input func */
    {223U, 1U, 0U},
    /* LPUART10_LPUART10_TX_IN input func */
    {411U, 2U, 0U},
    /* INMUX settings for pad PORT135:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_7_G_IN input func */
    {55U, 2U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 4U, 0U},
    /* LPUART4_LPUART4_RX_IN input func */
    {191U, 4U, 0U},
    /* LPSPI3_LPSPI3_SCK_IN input func */
    {252U, 2U, 0U},
    /* INMUX settings for pad PORT136:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_7_IN input func */
    {23U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_6_G_IN input func */
    {54U, 1U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 5U, 0U},
    /* FXIO_FXIO_D12_IN input func */
    {164U, 1U, 0U},
    /* LPSPI3_LPSPI3_PCS1_IN input func */
    {249U, 1U, 0U},
    /* LPSPI5_LPSPI5_PCS1_IN input func */
    {263U, 1U, 0U},
    /* SAI1_SAI1_BCLK_IN input func */
    {322U, 1U, 0U},
    /* INMUX settings for pad PORT137:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_8_IN input func */
    {24U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_7_G_IN input func */
    {55U, 1U, 0U},
    /* EMIOS_1_EMIOS_1_CH_13_H_IN input func */
    {93U, 5U, 0U},
    /* GMAC0_GMAC0_PPS3_IN input func */
    {147U, 1U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 1U, 0U},
    /* LPSPI5_LPSPI5_SOUT_IN input func */
    {268U, 1U, 0U},
    /* GMAC0_GMAC0_MII_RMII_TX_EN_IN input func */
    {297U, 3U, 0U},
    /* SAI0_SAI0_MCLK_IN input func */
    {320U, 2U, 0U},
    /* LPUART2_LPUART2_CTS_IN input func */
    {362U, 3U, 0U},
    /* INMUX settings for pad PORT138:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_9_IN input func */
    {25U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_20_Y_IN input func */
    {68U, 2U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 2U, 0U},
    /* LPUART4_LPUART4_RX_IN input func */
    {191U, 2U, 0U},
    /* LPSPI2_LPSPI2_PCS1_IN input func */
    {242U, 1U, 0U},
    /* LPSPI3_LPSPI3_SIN_IN input func */
    {253U, 1U, 0U},
    /* INMUX settings for pad PORT139:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_10_IN input func */
    {26U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_1_G_IN input func */
    {49U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_21_Y_IN input func */
    {69U, 2U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 1U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 3U, 0U},
    /* LPUART4_LPUART4_TX_IN input func */
    {367U, 3U, 0U},
    /* INMUX settings for pad PORT140:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_11_IN input func */
    {27U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 5U, 0U},
    /* GMAC0_GMAC0_PPS3_IN input func */
    {147U, 3U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 9U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 1U, 0U},
    /* SAI1_SAI1_MCLK_IN input func */
    {324U, 2U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 4U, 0U},
    /* INMUX settings for pad PORT142:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN4_CAN4_RX_IN input func */
    {4U, 1U, 0U},
    /* SIUL_EIRQ_13_IN input func */
    {29U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_19_Y_IN input func */
    {67U, 3U, 0U},
    /* GMAC0_GMAC0_PPS1_IN input func */
    {145U, 1U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 5U, 0U},
    /* LPUART5_LPUART5_TX_IN input func */
    {368U, 2U, 0U},
    /* GMAC1_GMAC1_PPS1_IN input func */
    {455U, 1U, 0U},
    /* INMUX settings for pad PORT143:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_14_IN input func */
    {30U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_22_X_IN input func */
    {70U, 1U, 0U},
    /* FCCU_FCCU_ERR_IN0_IN input func */
    {148U, 2U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 1U, 0U},
    /* LPUART3_LPUART3_RX_IN input func */
    {190U, 1U, 0U},
    /* LPSPI2_LPSPI2_SCK_IN input func */
    {245U, 1U, 0U},
    /* LPUART1_LPUART1_CTS_IN input func */
    {361U, 3U, 0U},
    /* INMUX settings for pad PORT144:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_15_IN input func */
    {31U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_23_X_IN input func */
    {71U, 2U, 0U},
    /* FCCU_FCCU_ERR_IN1_IN input func */
    {149U, 2U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 2U, 0U},
    /* LPSPI2_LPSPI2_SIN_IN input func */
    {246U, 1U, 0U},
    /* LPUART3_LPUART3_TX_IN input func */
    {366U, 3U, 0U},
    /* INMUX settings for pad PORT145:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_23_X_IN input func */
    {135U, 4U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 4U, 0U},
    /* INMUX settings for pad PORT146:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_17_Y_IN input func */
    {129U, 4U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 4U, 0U},
    /* INMUX settings for pad PORT147:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_22_X_IN input func */
    {70U, 3U, 0U},
    /* INMUX settings for pad PORT148:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 2U, 0U},
    /* INMUX settings for pad PORT149:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_19_Y_IN input func */
    {131U, 4U, 0U},
    /* LPSPI4_LPSPI4_SIN_IN input func */
    {260U, 3U, 0U},
    /* INMUX settings for pad PORT150:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_IN input func */
    {82U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_20_Y_IN input func */
    {132U, 4U, 0U},
    /* LPSPI4_LPSPI4_SCK_IN input func */
    {259U, 3U, 0U},
    /* INMUX settings for pad PORT151:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_21_Y_IN input func */
    {133U, 4U, 0U},
    /* LPSPI4_LPSPI4_PCS0_IN input func */
    {255U, 4U, 0U},
    /* INMUX settings for pad PORT152:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_4_H_IN input func */
    {116U, 3U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 10U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 6U, 0U},
    /* LPSPI2_LPSPI2_SIN_IN input func */
    {246U, 5U, 0U},
    /* LPSPI4_LPSPI4_PCS1_IN input func */
    {256U, 3U, 0U},
    /* INMUX settings for pad PORT153:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN2_CAN2_RX_IN input func */
    {2U, 3U, 0U},
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 2U, 0U},
    /* EMIOS_2_EMIOS_2_CH_5_H_IN input func */
    {117U, 2U, 0U},
    /* LPSPI4_LPSPI4_SOUT_IN input func */
    {261U, 3U, 0U},
    /* INMUX settings for pad PORT154:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_IN input func */
    {86U, 3U, 0U},
    /* EMIOS_2_EMIOS_2_CH_6_H_IN input func */
    {118U, 3U, 0U},
    /* INMUX settings for pad PORT155:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_10_H_IN input func */
    {58U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 1U, 0U},
    /* INMUX settings for pad PORT156:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_11_H_IN input func */
    {59U, 4U, 0U},
    /* INMUX settings for pad PORT157:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN3_CAN3_RX_IN input func */
    {3U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_12_H_IN input func */
    {60U, 4U, 0U},
    /* INMUX settings for pad PORT158:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* LPSPI0_LPSPI0_SOUT_IN input func */
    {231U, 6U, 0U},
    /* INMUX settings for pad PORT159:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN4_CAN4_RX_IN input func */
    {4U, 4U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 8U, 0U},
    /* INMUX settings for pad PORT160:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_0_IN input func */
    {16U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_0_X_IN input func */
    {112U, 1U, 0U},
    /* LPSPI2_LPSPI2_SCK_IN input func */
    {245U, 4U, 0U},
    /* LPUART5_LPUART5_TX_IN input func */
    {368U, 4U, 0U},
    /* INMUX settings for pad PORT161:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_1_IN input func */
    {17U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_1_H_IN input func */
    {113U, 1U, 0U},
    /* LPUART5_LPUART5_RX_IN input func */
    {192U, 3U, 0U},
    /* LPSPI2_LPSPI2_SIN_IN input func */
    {246U, 4U, 0U},
    /* INMUX settings for pad PORT162:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_2_IN input func */
    {18U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_2_H_IN input func */
    {114U, 1U, 0U},
    /* LPSPI2_LPSPI2_SOUT_IN input func */
    {247U, 4U, 0U},
    /* LPUART6_LPUART6_TX_IN input func */
    {369U, 4U, 0U},
    /* INMUX settings for pad PORT163:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_3_IN input func */
    {19U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_3_H_IN input func */
    {115U, 1U, 0U},
    /* LPUART6_LPUART6_RX_IN input func */
    {193U, 3U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 6U, 0U},
    /* INMUX settings for pad PORT164:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_4_IN input func */
    {20U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_4_H_IN input func */
    {116U, 1U, 0U},
    /* FXIO_FXIO_D0_IN input func */
    {152U, 7U, 0U},
    /* LPSPI2_LPSPI2_SOUT_IN input func */
    {247U, 5U, 0U},
    /* INMUX settings for pad PORT165:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN5_CAN5_RX_IN input func */
    {5U, 3U, 0U},
    /* SIUL_EIRQ_5_IN input func */
    {21U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_5_H_IN input func */
    {117U, 1U, 0U},
    /* INMUX settings for pad PORT166:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_6_IN input func */
    {22U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_6_H_IN input func */
    {118U, 1U, 0U},
    /* INMUX settings for pad PORT167:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_7_IN input func */
    {23U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_7_H_IN input func */
    {119U, 2U, 0U},
    /* FXIO_FXIO_D1_IN input func */
    {153U, 8U, 0U},
    /* LPI2C1_LPI2C1_SCL_IN input func */
    {217U, 5U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 8U, 0U},
    /* INMUX settings for pad PORT168:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_16_IN input func */
    {32U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_8_X_IN input func */
    {120U, 1U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 9U, 0U},
    /* LPI2C1_LPI2C1_SDA_IN input func */
    {219U, 4U, 0U},
    /* INMUX settings for pad PORT169:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_17_IN input func */
    {33U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_9_H_IN input func */
    {121U, 1U, 0U},
    /* INMUX settings for pad PORT170:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_18_IN input func */
    {34U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_10_H_IN input func */
    {122U, 1U, 0U},
    /* INMUX settings for pad PORT171:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_19_IN input func */
    {35U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_11_H_IN input func */
    {123U, 1U, 0U},
    /* HSE_HSE_TAMPER_EXTIN0_IN input func */
    {343U, 4U, 0U},
    /* INMUX settings for pad PORT172:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_20_IN input func */
    {36U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_12_H_IN input func */
    {124U, 2U, 0U},
    /* LPSPI3_LPSPI3_SIN_IN input func */
    {253U, 4U, 0U},
    /* LPUART10_LPUART10_TX_IN input func */
    {411U, 3U, 0U},
    /* INMUX settings for pad PORT173:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_21_IN input func */
    {37U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_13_H_IN input func */
    {125U, 1U, 0U},
    /* LPUART10_LPUART10_RX_IN input func */
    {197U, 3U, 0U},
    /* LPSPI3_LPSPI3_SCK_IN input func */
    {252U, 4U, 0U},
    /* INMUX settings for pad PORT174:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_22_IN input func */
    {38U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_14_H_IN input func */
    {126U, 1U, 0U},
    /* FCCU_FCCU_ERR_IN0_IN input func */
    {148U, 3U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 8U, 0U},
    /* INMUX settings for pad PORT175:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN1_CAN1_RX_IN input func */
    {1U, 5U, 0U},
    /* SIUL_EIRQ_23_IN input func */
    {39U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_15_H_IN input func */
    {127U, 1U, 0U},
    /* FCCU_FCCU_ERR_IN1_IN input func */
    {149U, 3U, 0U},
    /* LPSPI3_LPSPI3_SOUT_IN input func */
    {254U, 4U, 0U},
    /* INMUX settings for pad PORT176:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_16_X_IN input func */
    {128U, 4U, 0U},
    /* LPSPI3_LPSPI3_PCS0_IN input func */
    {248U, 4U, 0U},
    /* LPUART12_LPUART12_TX_IN input func */
    {413U, 3U, 0U},
    /* INMUX settings for pad PORT177:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_17_Y_IN input func */
    {129U, 3U, 0U},
    /* LPUART12_LPUART12_RX_IN input func */
    {199U, 3U, 0U},
    /* INMUX settings for pad PORT178:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_IN input func */
    {82U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_18_Y_IN input func */
    {130U, 3U, 0U},
    /* LPSPI3_LPSPI3_PCS1_IN input func */
    {249U, 2U, 0U},
    /* LPUART7_LPUART7_TX_IN input func */
    {370U, 4U, 0U},
    /* INMUX settings for pad PORT179:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_19_Y_IN input func */
    {131U, 3U, 0U},
    /* LPUART7_LPUART7_RX_IN input func */
    {194U, 3U, 0U},
    /* LPSPI3_LPSPI3_PCS2_IN input func */
    {250U, 2U, 0U},
    /* INMUX settings for pad PORT180:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_20_Y_IN input func */
    {132U, 3U, 0U},
    /* FXIO_FXIO_D4_IN input func */
    {156U, 8U, 0U},
    /* LPI2C0_LPI2C0_SCL_IN input func */
    {212U, 3U, 0U},
    /* LPSPI3_LPSPI3_PCS3_IN input func */
    {251U, 2U, 0U},
    /* LPUART8_LPUART8_TX_IN input func */
    {409U, 3U, 0U},
    /* INMUX settings for pad PORT181:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN0_CAN0_RX_IN input func */
    {0U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 6U, 0U},
    /* EMIOS_2_EMIOS_2_CH_21_Y_IN input func */
    {133U, 3U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 11U, 0U},
    /* LPUART8_LPUART8_RX_IN input func */
    {195U, 3U, 0U},
    /* LPI2C0_LPI2C0_SDA_IN input func */
    {214U, 3U, 0U},
    /* LPSPI1_LPSPI1_PCS0_IN input func */
    {232U, 4U, 0U},
    /* INMUX settings for pad PORT182:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_IN input func */
    {86U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_22_X_IN input func */
    {134U, 5U, 0U},
    /* LPSPI4_LPSPI4_PCS2_IN input func */
    {257U, 2U, 0U},
    /* INMUX settings for pad PORT183:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 5U, 0U},
    /* EMIOS_2_EMIOS_2_CH_23_X_IN input func */
    {135U, 5U, 0U},
    /* LPSPI3_LPSPI3_PCS3_IN input func */
    {251U, 3U, 0U},
    /* LPUART9_LPUART9_TX_IN input func */
    {410U, 3U, 0U},
    /* INMUX settings for pad PORT184:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_8_X_IN input func */
    {88U, 3U, 0U},
    /* LPUART9_LPUART9_RX_IN input func */
    {196U, 3U, 0U},
    /* INMUX settings for pad PORT185:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_9_H_IN input func */
    {89U, 3U, 0U},
    /* FXIO_FXIO_D6_IN input func */
    {158U, 10U, 0U},
    /* LPSPI2_LPSPI2_PCS2_IN input func */
    {243U, 3U, 0U},
    /* LPSPI4_LPSPI4_PCS0_IN input func */
    {255U, 3U, 0U},
    /* INMUX settings for pad PORT186:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN2_CAN2_RX_IN input func */
    {2U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_10_H_IN input func */
    {90U, 4U, 0U},
    /* LPSPI2_LPSPI2_PCS3_IN input func */
    {244U, 2U, 0U},
    /* LPSPI4_LPSPI4_PCS1_IN input func */
    {256U, 2U, 0U},
    /* INMUX settings for pad PORT187:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_11_H_IN input func */
    {91U, 3U, 0U},
    /* LPSPI4_LPSPI4_PCS2_IN input func */
    {257U, 3U, 0U},
    /* LPUART11_LPUART11_TX_IN input func */
    {412U, 3U, 0U},
    /* INMUX settings for pad PORT188:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_IN input func */
    {92U, 4U, 0U},
    /* FXIO_FXIO_D7_IN input func */
    {159U, 8U, 0U},
    /* LPUART11_LPUART11_RX_IN input func */
    {198U, 3U, 0U},
    /* LPSPI0_LPSPI0_PCS0_IN input func */
    {221U, 4U, 0U},
    /* LPSPI4_LPSPI4_PCS3_IN input func */
    {258U, 2U, 0U},
    /* INMUX settings for pad PORT189:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_13_H_IN input func */
    {93U, 3U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 6U, 0U},
    /* LPSPI3_LPSPI3_PCS1_IN input func */
    {249U, 3U, 0U},
    /* INMUX settings for pad PORT190:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN3_CAN3_RX_IN input func */
    {3U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_14_H_IN input func */
    {94U, 3U, 0U},
    /* INMUX settings for pad PORT191:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 4U, 0U},
    /* FXIO_FXIO_D9_IN input func */
    {161U, 5U, 0U},
    /* INMUX settings for pad PORT192:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_8_IN input func */
    {24U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_16_X_IN input func */
    {96U, 4U, 0U},
    /* LPUART13_LPUART13_TX_IN input func */
    {414U, 3U, 0U},
    /* INMUX settings for pad PORT193:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_9_IN input func */
    {25U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_17_Y_IN input func */
    {97U, 3U, 0U},
    /* LPUART13_LPUART13_RX_IN input func */
    {200U, 3U, 0U},
    /* INMUX settings for pad PORT194:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_10_IN input func */
    {26U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_18_Y_IN input func */
    {98U, 3U, 0U},
    /* LPUART14_LPUART14_TX_IN input func */
    {415U, 3U, 0U},
    /* INMUX settings for pad PORT195:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_11_IN input func */
    {27U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_19_Y_IN input func */
    {99U, 3U, 0U},
    /* LPUART14_LPUART14_RX_IN input func */
    {201U, 3U, 0U},
    /* INMUX settings for pad PORT196:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_12_IN input func */
    {28U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_20_Y_IN input func */
    {100U, 3U, 0U},
    /* LPUART15_LPUART15_TX_IN input func */
    {416U, 3U, 0U},
    /* INMUX settings for pad PORT197:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_13_IN input func */
    {29U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_21_Y_IN input func */
    {101U, 3U, 0U},
    /* LPUART15_LPUART15_RX_IN input func */
    {202U, 3U, 0U},
    /* INMUX settings for pad PORT198:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_14_IN input func */
    {30U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_22_X_IN input func */
    {102U, 3U, 0U},
    /* FXIO_FXIO_D10_IN input func */
    {162U, 5U, 0U},
    /* INMUX settings for pad PORT199:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_15_IN input func */
    {31U, 5U, 0U},
    /* EMIOS_1_EMIOS_1_CH_23_X_IN input func */
    {103U, 3U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 7U, 0U},
    /* INMUX settings for pad PORT200:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_24_IN input func */
    {40U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_13_H_IN input func */
    {61U, 4U, 0U},
    /* FXIO_FXIO_D12_IN input func */
    {164U, 5U, 0U},
    /* LPSPI5_LPSPI5_PCS3_IN input func */
    {265U, 2U, 0U},
    /* INMUX settings for pad PORT201:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN4_CAN4_RX_IN input func */
    {4U, 5U, 0U},
    /* SIUL_EIRQ_25_IN input func */
    {41U, 4U, 0U},
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 8U, 0U},
    /* FXIO_FXIO_D5_IN input func */
    {157U, 12U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 6U, 0U},
    /* INMUX settings for pad PORT202:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_26_IN input func */
    {42U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_14_H_IN input func */
    {62U, 4U, 0U},
    /* FXIO_FXIO_D2_IN input func */
    {154U, 11U, 0U},
    /* INMUX settings for pad PORT203:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_27_IN input func */
    {43U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_15_H_IN input func */
    {63U, 4U, 0U},
    /* FXIO_FXIO_D3_IN input func */
    {155U, 10U, 0U},
    /* INMUX settings for pad PORT204:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_28_IN input func */
    {44U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_16_X_IN input func */
    {64U, 4U, 0U},
    /* LPSPI4_LPSPI4_PCS3_IN input func */
    {258U, 3U, 0U},
    /* INMUX settings for pad PORT205:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_29_IN input func */
    {45U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_17_Y_IN input func */
    {65U, 4U, 0U},
    /* FXIO_FXIO_D13_IN input func */
    {165U, 5U, 0U},
    /* LPSPI5_LPSPI5_PCS2_IN input func */
    {264U, 2U, 0U},
    /* INMUX settings for pad PORT206:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN5_CAN5_RX_IN input func */
    {5U, 4U, 0U},
    /* SIUL_EIRQ_30_IN input func */
    {46U, 4U, 0U},
    /* EMIOS_0_EMIOS_0_CH_18_Y_IN input func */
    {66U, 4U, 0U},
    /* LPSPI2_LPSPI2_PCS0_IN input func */
    {241U, 7U, 0U},
    /* LPSPI2_LPSPI2_PCS2_IN input func */
    {243U, 4U, 0U},
    /* INMUX settings for pad PORT207:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_31_IN input func */
    {47U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_15_H_IN input func */
    {127U, 4U, 0U},
    /* FXIO_FXIO_D14_IN input func */
    {166U, 5U, 0U},
    /* INMUX settings for pad PORT208:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_16_X_IN input func */
    {128U, 1U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 6U, 0U},
    /* INMUX settings for pad PORT209:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_17_Y_IN input func */
    {129U, 1U, 0U},
    /* FXIO_FXIO_D16_IN input func */
    {168U, 4U, 0U},
    /* INMUX settings for pad PORT210:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_18_Y_IN input func */
    {130U, 1U, 0U},
    /* FXIO_FXIO_D17_IN input func */
    {169U, 3U, 0U},
    /* INMUX settings for pad PORT211:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_19_Y_IN input func */
    {131U, 1U, 0U},
    /* FXIO_FXIO_D18_IN input func */
    {170U, 3U, 0U},
    /* INMUX settings for pad PORT212:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_20_Y_IN input func */
    {132U, 1U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 6U, 0U},
    /* INMUX settings for pad PORT213:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_21_Y_IN input func */
    {133U, 1U, 0U},
    /* FXIO_FXIO_D20_IN input func */
    {172U, 3U, 0U},
    /* CAN6_CAN6_RX_IN input func */
    {417U, 3U, 0U},
    /* INMUX settings for pad PORT214:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_22_X_IN input func */
    {134U, 1U, 0U},
    /* FXIO_FXIO_D21_IN input func */
    {173U, 3U, 0U},
    /* INMUX settings for pad PORT215:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_0_X_IN input func */
    {48U, 4U, 0U},
    /* EMIOS_2_EMIOS_2_CH_23_X_IN input func */
    {135U, 1U, 0U},
    /* FXIO_FXIO_D22_IN input func */
    {174U, 3U, 0U},
    /* LPSPI5_LPSPI5_PCS0_IN input func */
    {262U, 5U, 0U},
    /* INMUX settings for pad PORT216:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_1_G_IN input func */
    {49U, 6U, 0U},
    /* FXIO_FXIO_D23_IN input func */
    {175U, 3U, 0U},
    /* LPSPI5_LPSPI5_PCS2_IN input func */
    {264U, 3U, 0U},
    /* LPUART12_LPUART12_TX_IN input func */
    {413U, 4U, 0U},
    /* INMUX settings for pad PORT217:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_2_G_IN input func */
    {50U, 6U, 0U},
    /* FXIO_FXIO_D24_IN input func */
    {176U, 3U, 0U},
    /* LPUART12_LPUART12_RX_IN input func */
    {199U, 4U, 0U},
    /* LPSPI5_LPSPI5_SOUT_IN input func */
    {268U, 5U, 0U},
    /* INMUX settings for pad PORT218:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 7U, 0U},
    /* FXIO_FXIO_D25_IN input func */
    {177U, 3U, 0U},
    /* INMUX settings for pad PORT219:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_4_G_IN input func */
    {52U, 4U, 0U},
    /* FXIO_FXIO_D26_IN input func */
    {178U, 3U, 0U},
    /* CAN7_CAN7_RX_IN input func */
    {418U, 3U, 0U},
    /* INMUX settings for pad PORT220:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_5_G_IN input func */
    {53U, 4U, 0U},
    /* LPSPI5_LPSPI5_PCS0_IN input func */
    {262U, 4U, 0U},
    /* INMUX settings for pad PORT221:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_29_IN input func */
    {45U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_6_G_IN input func */
    {54U, 5U, 0U},
    /* FXIO_FXIO_D29_IN input func */
    {181U, 3U, 0U},
    /* LPSPI5_LPSPI5_SIN_IN input func */
    {267U, 4U, 0U},
    /* INMUX settings for pad PORT222:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_30_IN input func */
    {46U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_7_G_IN input func */
    {55U, 5U, 0U},
    /* FXIO_FXIO_D30_IN input func */
    {182U, 3U, 0U},
    /* LPSPI5_LPSPI5_SOUT_IN input func */
    {268U, 4U, 0U},
    /* INMUX settings for pad PORT223:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_31_IN input func */
    {47U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_8_X_IN input func */
    {56U, 4U, 0U},
    /* FXIO_FXIO_D31_IN input func */
    {183U, 3U, 0U},
    /* LPSPI5_LPSPI5_SCK_IN input func */
    {266U, 4U, 0U},
    /* INMUX settings for pad PORT224:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_16_IN input func */
    {32U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_9_H_IN input func */
    {57U, 4U, 0U},
    /* FXIO_FXIO_D16_IN input func */
    {168U, 5U, 0U},
    /* LPSPI2_LPSPI2_PCS2_IN input func */
    {243U, 5U, 0U},
    /* LPUART0_LPUART0_TX_IN input func */
    {363U, 5U, 0U},
    /* INMUX settings for pad PORT225:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_17_IN input func */
    {33U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_10_H_IN input func */
    {58U, 5U, 0U},
    /* FXIO_FXIO_D17_IN input func */
    {169U, 4U, 0U},
    /* LPUART0_LPUART0_RX_IN input func */
    {187U, 5U, 0U},
    /* LPSPI2_LPSPI2_PCS3_IN input func */
    {244U, 3U, 0U},
    /* CAN6_CAN6_RX_IN input func */
    {417U, 4U, 0U},
    /* INMUX settings for pad PORT226:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_18_IN input func */
    {34U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_11_H_IN input func */
    {59U, 5U, 0U},
    /* FXIO_FXIO_D18_IN input func */
    {170U, 4U, 0U},
    /* LPUART3_LPUART3_TX_IN input func */
    {366U, 4U, 0U},
    /* INMUX settings for pad PORT227:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_19_IN input func */
    {35U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_12_H_IN input func */
    {60U, 5U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 7U, 0U},
    /* LPUART3_LPUART3_RX_IN input func */
    {190U, 4U, 0U},
    /* CAN7_CAN7_RX_IN input func */
    {418U, 4U, 0U},
    /* INMUX settings for pad PORT228:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_20_IN input func */
    {36U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_13_H_IN input func */
    {61U, 5U, 0U},
    /* FXIO_FXIO_D20_IN input func */
    {172U, 4U, 0U},
    /* LPUART4_LPUART4_TX_IN input func */
    {367U, 4U, 0U},
    /* INMUX settings for pad PORT229:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_21_IN input func */
    {37U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_14_H_IN input func */
    {62U, 5U, 0U},
    /* FXIO_FXIO_D21_IN input func */
    {173U, 4U, 0U},
    /* LPUART4_LPUART4_RX_IN input func */
    {191U, 5U, 0U},
    /* INMUX settings for pad PORT230:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_22_IN input func */
    {38U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_15_H_IN input func */
    {63U, 5U, 0U},
    /* FXIO_FXIO_D22_IN input func */
    {174U, 4U, 0U},
    /* LPUART8_LPUART8_TX_IN input func */
    {409U, 4U, 0U},
    /* INMUX settings for pad PORT231:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_23_IN input func */
    {39U, 5U, 0U},
    /* EMIOS_0_EMIOS_0_CH_16_X_IN input func */
    {64U, 5U, 0U},
    /* FXIO_FXIO_D23_IN input func */
    {175U, 4U, 0U},
    /* LPUART2_LPUART2_RX_IN input func */
    {189U, 7U, 0U},
    /* LPUART8_LPUART8_RX_IN input func */
    {195U, 4U, 0U},
    /* INMUX settings for pad PORT232:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_24_IN input func */
    {40U, 5U, 0U},
    /* FXIO_FXIO_D24_IN input func */
    {176U, 4U, 0U},
    /* LPUART2_LPUART2_TX_IN input func */
    {365U, 7U, 0U},
    /* LPUART10_LPUART10_TX_IN input func */
    {411U, 4U, 0U},
    /* INMUX settings for pad PORT233:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_25_IN input func */
    {41U, 5U, 0U},
    /* FXIO_FXIO_D25_IN input func */
    {177U, 4U, 0U},
    /* LPUART10_LPUART10_RX_IN input func */
    {197U, 4U, 0U},
    /* INMUX settings for pad PORT234:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_26_IN input func */
    {42U, 5U, 0U},
    /* FXIO_FXIO_D26_IN input func */
    {178U, 4U, 0U},
    /* LPUART11_LPUART11_TX_IN input func */
    {412U, 4U, 0U},
    /* INMUX settings for pad PORT235:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_27_IN input func */
    {43U, 5U, 0U},
    /* FXIO_FXIO_D27_IN input func */
    {179U, 3U, 0U},
    /* LPUART11_LPUART11_RX_IN input func */
    {198U, 4U, 0U},
    /* INMUX settings for pad PORT236:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* SIUL_EIRQ_28_IN input func */
    {44U, 5U, 0U},
    /* FXIO_FXIO_D28_IN input func */
    {180U, 3U, 0U},
    /* INMUX settings for pad PORT237:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D0_IN input func */
    {152U, 8U, 0U},
    /* INMUX settings for pad PORT238:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D1_IN input func */
    {153U, 9U, 0U},
    /* CAN8_CAN8_RX_IN input func */
    {470U, 1U, 0U},
    /* INMUX settings for pad PORT239:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D2_IN input func */
    {154U, 12U, 0U},
    /* INMUX settings for pad PORT240:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D3_IN input func */
    {155U, 11U, 0U},
    /* CAN11_CAN11_RX_IN input func */
    {473U, 1U, 0U},
    /* INMUX settings for pad PORT241:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D4_IN input func */
    {156U, 9U, 0U},
    /* LPUART14_LPUART14_TX_IN input func */
    {415U, 4U, 0U},
    /* INMUX settings for pad PORT242:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D5_IN input func */
    {157U, 13U, 0U},
    /* LPUART14_LPUART14_RX_IN input func */
    {201U, 4U, 0U},
    /* INMUX settings for pad PORT243:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D6_IN input func */
    {158U, 11U, 0U},
    /* LPUART15_LPUART15_TX_IN input func */
    {416U, 4U, 0U},
    /* INMUX settings for pad PORT244:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D7_IN input func */
    {159U, 10U, 0U},
    /* LPUART15_LPUART15_RX_IN input func */
    {202U, 4U, 0U},
    /* INMUX settings for pad PORT245:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_17_Y_IN input func */
    {129U, 5U, 0U},
    /* INMUX settings for pad PORT246:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_18_Y_IN input func */
    {130U, 5U, 0U},
    /* INMUX settings for pad PORT248:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_0_X_IN input func */
    {48U, 5U, 0U},
    /* TRGMUX_TRGMUX_IN0_IN input func */
    {344U, 2U, 0U},
    /* INMUX settings for pad PORT249:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_1_G_IN input func */
    {49U, 7U, 0U},
    /* TRGMUX_TRGMUX_IN1_IN input func */
    {345U, 2U, 0U},
    /* INMUX settings for pad PORT250:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_2_G_IN input func */
    {50U, 7U, 0U},
    /* TRGMUX_TRGMUX_IN2_IN input func */
    {346U, 2U, 0U},
    /* CAN11_CAN11_RX_IN input func */
    {473U, 2U, 0U},
    /* INMUX settings for pad PORT251:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_3_G_IN input func */
    {51U, 8U, 0U},
    /* TRGMUX_TRGMUX_IN3_IN input func */
    {347U, 2U, 0U},
    /* INMUX settings for pad PORT252:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_4_G_IN input func */
    {52U, 5U, 0U},
    /* CAN8_CAN8_RX_IN input func */
    {470U, 2U, 0U},
    /* INMUX settings for pad PORT253:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_5_G_IN input func */
    {53U, 5U, 0U},
    /* INMUX settings for pad PORT254:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_6_G_IN input func */
    {54U, 6U, 0U},
    /* INMUX settings for pad PORT255:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_7_G_IN input func */
    {55U, 6U, 0U},
    /* INMUX settings for pad PORT256:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_0_X_IN input func */
    {112U, 6U, 0U},
    /* FXIO_FXIO_D8_IN input func */
    {160U, 7U, 0U},
    /* INMUX settings for pad PORT257:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_1_H_IN input func */
    {113U, 4U, 0U},
    /* FXIO_FXIO_D9_IN input func */
    {161U, 6U, 0U},
    /* CAN9_CAN9_RX_IN input func */
    {471U, 1U, 0U},
    /* INMUX settings for pad PORT258:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D10_IN input func */
    {162U, 6U, 0U},
    /* LPUART13_LPUART13_TX_IN input func */
    {414U, 5U, 0U},
    /* INMUX settings for pad PORT259:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_3_H_IN input func */
    {115U, 4U, 0U},
    /* FXIO_FXIO_D11_IN input func */
    {163U, 8U, 0U},
    /* LPUART13_LPUART13_RX_IN input func */
    {200U, 5U, 0U},
    /* INMUX settings for pad PORT260:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_5_H_IN input func */
    {117U, 4U, 0U},
    /* FXIO_FXIO_D12_IN input func */
    {164U, 6U, 0U},
    /* TRGMUX_TRGMUX_IN12_IN input func */
    {356U, 2U, 0U},
    /* LPUART14_LPUART14_TX_IN input func */
    {415U, 5U, 0U},
    /* INMUX settings for pad PORT261:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D13_IN input func */
    {165U, 6U, 0U},
    /* LPUART14_LPUART14_RX_IN input func */
    {201U, 5U, 0U},
    /* TRGMUX_TRGMUX_IN13_IN input func */
    {357U, 2U, 0U},
    /* INMUX settings for pad PORT262:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_7_H_IN input func */
    {119U, 4U, 0U},
    /* FXIO_FXIO_D14_IN input func */
    {166U, 6U, 0U},
    /* TRGMUX_TRGMUX_IN14_IN input func */
    {358U, 2U, 0U},
    /* INMUX settings for pad PORT263:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_8_X_IN input func */
    {120U, 5U, 0U},
    /* FXIO_FXIO_D15_IN input func */
    {167U, 7U, 0U},
    /* TRGMUX_TRGMUX_IN15_IN input func */
    {359U, 2U, 0U},
    /* INMUX settings for pad PORT264:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_6_H_IN input func */
    {118U, 4U, 0U},
    /* INMUX settings for pad PORT266:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_4_H_IN input func */
    {116U, 4U, 0U},
    /* CAN10_CAN10_RX_IN input func */
    {472U, 1U, 0U},
    /* INMUX settings for pad PORT268:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_13_H_IN input func */
    {61U, 6U, 0U},
    /* LPUART9_LPUART9_TX_IN input func */
    {410U, 4U, 0U},
    /* INMUX settings for pad PORT269:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_8_X_IN input func */
    {56U, 5U, 0U},
    /* LPUART9_LPUART9_RX_IN input func */
    {196U, 4U, 0U},
    /* INMUX settings for pad PORT270:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_9_H_IN input func */
    {57U, 5U, 0U},
    /* INMUX settings for pad PORT271:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_10_H_IN input func */
    {58U, 6U, 0U},
    /* CAN8_CAN8_RX_IN input func */
    {470U, 3U, 0U},
    /* INMUX settings for pad PORT272:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_11_H_IN input func */
    {59U, 6U, 0U},
    /* LPSPI1_LPSPI1_PCS0_IN input func */
    {232U, 6U, 0U},
    /* INMUX settings for pad PORT273:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_12_H_IN input func */
    {60U, 6U, 0U},
    /* CAN11_CAN11_RX_IN input func */
    {473U, 3U, 0U},
    /* INMUX settings for pad PORT274:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_14_H_IN input func */
    {62U, 6U, 0U},
    /* LPSPI1_LPSPI1_SOUT_IN input func */
    {240U, 6U, 0U},
    /* INMUX settings for pad PORT275:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_15_H_IN input func */
    {63U, 6U, 0U},
    /* CAN9_CAN9_RX_IN input func */
    {471U, 2U, 0U},
    /* INMUX settings for pad PORT276:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_16_X_IN input func */
    {64U, 6U, 0U},
    /* LPSPI1_LPSPI1_SIN_IN input func */
    {239U, 5U, 0U},
    /* INMUX settings for pad PORT277:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_17_Y_IN input func */
    {65U, 5U, 0U},
    /* CAN7_CAN7_RX_IN input func */
    {418U, 5U, 0U},
    /* INMUX settings for pad PORT278:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_18_Y_IN input func */
    {66U, 5U, 0U},
    /* INMUX settings for pad PORT279:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_19_Y_IN input func */
    {67U, 6U, 0U},
    /* LPSPI1_LPSPI1_SCK_IN input func */
    {238U, 5U, 0U},
    /* INMUX settings for pad PORT280:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_20_Y_IN input func */
    {68U, 3U, 0U},
    /* TRGMUX_TRGMUX_IN4_IN input func */
    {348U, 2U, 0U},
    /* CAN10_CAN10_RX_IN input func */
    {472U, 2U, 0U},
    /* INMUX settings for pad PORT281:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_21_Y_IN input func */
    {69U, 3U, 0U},
    /* TRGMUX_TRGMUX_IN5_IN input func */
    {349U, 2U, 0U},
    /* LPUART9_LPUART9_TX_IN input func */
    {410U, 5U, 0U},
    /* INMUX settings for pad PORT282:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_22_X_IN input func */
    {70U, 4U, 0U},
    /* LPUART9_LPUART9_RX_IN input func */
    {196U, 5U, 0U},
    /* TRGMUX_TRGMUX_IN6_IN input func */
    {350U, 2U, 0U},
    /* INMUX settings for pad PORT283:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_0_EMIOS_0_CH_23_X_IN input func */
    {71U, 3U, 0U},
    /* TRGMUX_TRGMUX_IN7_IN input func */
    {351U, 2U, 0U},
    /* INMUX settings for pad PORT284:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_9_H_IN input func */
    {121U, 5U, 0U},
    /* INMUX settings for pad PORT285:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_10_H_IN input func */
    {122U, 4U, 0U},
    /* INMUX settings for pad PORT286:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_11_H_IN input func */
    {123U, 4U, 0U},
    /* INMUX settings for pad PORT287:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_12_H_IN input func */
    {124U, 4U, 0U},
    /* INMUX settings for pad PORT288:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* FXIO_FXIO_D16_IN input func */
    {168U, 6U, 0U},
    /* INMUX settings for pad PORT289:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_19_Y_IN input func */
    {131U, 5U, 0U},
    /* FXIO_FXIO_D17_IN input func */
    {169U, 5U, 0U},
    /* CAN10_CAN10_RX_IN input func */
    {472U, 3U, 0U},
    /* INMUX settings for pad PORT290:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_20_Y_IN input func */
    {132U, 5U, 0U},
    /* FXIO_FXIO_D18_IN input func */
    {170U, 5U, 0U},
    /* INMUX settings for pad PORT291:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_21_Y_IN input func */
    {133U, 5U, 0U},
    /* FXIO_FXIO_D19_IN input func */
    {171U, 8U, 0U},
    /* INMUX settings for pad PORT292:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_22_X_IN input func */
    {134U, 6U, 0U},
    /* FXIO_FXIO_D20_IN input func */
    {172U, 5U, 0U},
    /* LPUART13_LPUART13_TX_IN input func */
    {414U, 6U, 0U},
    /* INMUX settings for pad PORT293:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_23_X_IN input func */
    {135U, 6U, 0U},
    /* FXIO_FXIO_D21_IN input func */
    {173U, 5U, 0U},
    /* LPUART13_LPUART13_RX_IN input func */
    {200U, 6U, 0U},
    /* INMUX settings for pad PORT294:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_13_H_IN input func */
    {125U, 4U, 0U},
    /* FXIO_FXIO_D22_IN input func */
    {174U, 5U, 0U},
    /* INMUX settings for pad PORT295:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_14_H_IN input func */
    {126U, 4U, 0U},
    /* FXIO_FXIO_D23_IN input func */
    {175U, 5U, 0U},
    /* INMUX settings for pad PORT296:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_15_H_IN input func */
    {127U, 6U, 0U},
    /* INMUX settings for pad PORT297:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_16_X_IN input func */
    {128U, 5U, 0U},
    /* INMUX settings for pad PORT298:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_2_EMIOS_2_CH_2_H_IN input func */
    {114U, 4U, 0U},
    /* LPSPI3_LPSPI3_SCK_IN input func */
    {252U, 5U, 0U},
    /* INMUX settings for pad PORT299:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* CAN9_CAN9_RX_IN input func */
    {471U, 3U, 0U},
    /* INMUX settings for pad PORT300:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_0_X_IN input func */
    {80U, 7U, 0U},
    /* FXIO_FXIO_D28_IN input func */
    {180U, 4U, 0U},
    /* LPSPI3_LPSPI3_SIN_IN input func */
    {253U, 5U, 0U},
    /* INMUX settings for pad PORT301:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_IN input func */
    {81U, 8U, 0U},
    /* FXIO_FXIO_D29_IN input func */
    {181U, 4U, 0U},
    /* CAN8_CAN8_RX_IN input func */
    {470U, 4U, 0U},
    /* INMUX settings for pad PORT302:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_IN input func */
    {82U, 7U, 0U},
    /* FXIO_FXIO_D30_IN input func */
    {182U, 4U, 0U},
    /* LPSPI3_LPSPI3_SOUT_IN input func */
    {254U, 5U, 0U},
    /* INMUX settings for pad PORT303:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_3_H_IN input func */
    {83U, 8U, 0U},
    /* FXIO_FXIO_D31_IN input func */
    {183U, 4U, 0U},
    /* CAN9_CAN9_RX_IN input func */
    {471U, 4U, 0U},
    /* INMUX settings for pad PORT304:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_5_H_IN input func */
    {85U, 9U, 0U},
    /* LPSPI3_LPSPI3_PCS0_IN input func */
    {248U, 5U, 0U},
    /* INMUX settings for pad PORT305:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_IN input func */
    {86U, 7U, 0U},
    /* CAN10_CAN10_RX_IN input func */
    {472U, 4U, 0U},
    /* INMUX settings for pad PORT306:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_IN input func */
    {87U, 8U, 0U},
    /* INMUX settings for pad PORT307:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_8_X_IN input func */
    {88U, 5U, 0U},
    /* CAN11_CAN11_RX_IN input func */
    {473U, 4U, 0U},
    /* INMUX settings for pad PORT308:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_9_H_IN input func */
    {89U, 6U, 0U},
    /* INMUX settings for pad PORT309:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_10_H_IN input func */
    {90U, 7U, 0U},
    /* CAN6_CAN6_RX_IN input func */
    {417U, 5U, 0U},
    /* INMUX settings for pad PORT310:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_11_H_IN input func */
    {91U, 6U, 0U},
    /* INMUX settings for pad PORT311:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_IN input func */
    {92U, 7U, 0U},
    /* LPSPI4_LPSPI4_SIN_IN input func */
    {260U, 4U, 0U},
    /* INMUX settings for pad PORT312:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_13_H_IN input func */
    {93U, 6U, 0U},
    /* TRGMUX_TRGMUX_IN8_IN input func */
    {352U, 2U, 0U},
    /* CAN9_CAN9_RX_IN input func */
    {471U, 5U, 0U},
    /* INMUX settings for pad PORT313:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_IN input func */
    {84U, 9U, 0U},
    /* TRGMUX_TRGMUX_IN9_IN input func */
    {353U, 2U, 0U},
    /* INMUX settings for pad PORT314:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_14_H_IN input func */
    {94U, 7U, 0U},
    /* LPSPI4_LPSPI4_SOUT_IN input func */
    {261U, 4U, 0U},
    /* TRGMUX_TRGMUX_IN10_IN input func */
    {354U, 2U, 0U},
    /* INMUX settings for pad PORT315:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_IN input func */
    {95U, 8U, 0U},
    /* TRGMUX_TRGMUX_IN11_IN input func */
    {355U, 2U, 0U},
    /* CAN10_CAN10_RX_IN input func */
    {472U, 5U, 0U},
    /* INMUX settings for pad PORT316:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_16_X_IN input func */
    {96U, 6U, 0U},
    /* INMUX settings for pad PORT317:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_17_Y_IN input func */
    {97U, 5U, 0U},
    /* LPSPI4_LPSPI4_SCK_IN input func */
    {259U, 4U, 0U},
    /* INMUX settings for pad PORT318:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_18_Y_IN input func */
    {98U, 5U, 0U},
    /* CAN8_CAN8_RX_IN input func */
    {470U, 5U, 0U},
    /* INMUX settings for pad PORT319:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_19_Y_IN input func */
    {99U, 5U, 0U},
    /* INMUX settings for pad PORT320:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_20_Y_IN input func */
    {100U, 5U, 0U},
    /* FXIO_FXIO_D24_IN input func */
    {176U, 5U, 0U},
    /* LPSPI4_LPSPI4_PCS0_IN input func */
    {255U, 5U, 0U},
    /* INMUX settings for pad PORT321:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_21_Y_IN input func */
    {101U, 5U, 0U},
    /* FXIO_FXIO_D25_IN input func */
    {177U, 5U, 0U},
    /* CAN11_CAN11_RX_IN input func */
    {473U, 5U, 0U},
    /* INMUX settings for pad PORT322:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_22_X_IN input func */
    {102U, 5U, 0U},
    /* FXIO_FXIO_D26_IN input func */
    {178U, 5U, 0U},
    /* LPUART15_LPUART15_TX_IN input func */
    {416U, 5U, 0U},
    /* INMUX settings for pad PORT323:  {IMCR reg, IMCR.SSS Val, IMCR SIUL2 Instance} */
    /* EMIOS_1_EMIOS_1_CH_23_X_IN input func */
    {103U, 5U, 0U},
    /* FXIO_FXIO_D27_IN input func */
    {179U, 4U, 0U},
    /* LPUART15_LPUART15_RX_IN input func */
    {202U, 5U, 0U}
};

/**
* @brief Array of elements storing information about INOUT functionalities on the SIUL2 instance
*/
static const Port_InoutSettingType Port_SIUL2_0_aInoutMuxSettings[PORT_SIUL2_0_INOUT_TABLE_NUM_ENTRIES_U16] =
{
    /* Inout settings for pad PORT0 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_PCS2_INOUT inout functionality */
    {0U, 34U, 257U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_17_Y_INOUT inout functionality */
    {0U, 35U, 65U, 2U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {0U, 37U, 154U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {0U, 38U, 80U, 3U, 0U}, 
    /* LPSPI0_LPSPI0_PCS7_INOUT inout functionality */
    {0U, 39U, 228U, 1U, 0U}, 
    /* Inout settings for pad PORT1 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_PCS1_INOUT inout functionality */
    {1U, 34U, 256U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_9_H_INOUT inout functionality */
    {1U, 35U, 57U, 1U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {1U, 37U, 155U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_PCS6_INOUT inout functionality */
    {1U, 39U, 227U, 1U, 0U}, 
    /* Inout settings for pad PORT2 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_19_Y_INOUT inout functionality */
    {2U, 35U, 99U, 4U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {2U, 38U, 156U, 3U, 0U}, 
    /* LPSPI5_LPSPI5_SIN_INOUT inout functionality */
    {2U, 40U, 267U, 2U, 0U}, 
    /* Inout settings for pad PORT3 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_20_Y_INOUT inout functionality */
    {3U, 35U, 100U, 4U, 0U}, 
    /* LPSPI1_LPSPI1_SCK_INOUT inout functionality */
    {3U, 36U, 238U, 1U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {3U, 38U, 157U, 3U, 0U}, 
    /* LPUART0_LPUART0_TX_INOUT inout functionality */
    {3U, 39U, 363U, 1U, 0U}, 
    /* LPSPI5_LPSPI5_SCK_INOUT inout functionality */
    {3U, 40U, 266U, 2U, 0U}, 
    /* Inout settings for pad PORT4 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {4U, 36U, 158U, 8U, 0U}, 
    /* JTAG_JTAG_TMSSWD_DIO_INOUT inout functionality */
    {4U, 40U, 186U, 0U, 0U}, 
    /* Inout settings for pad PORT5 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* SYSTEM_RESET_B_INOUT inout functionality */
    {5U, 40U, 65535U, 0U, 0U}, 
    /* Inout settings for pad PORT6 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI1_LPSPI1_PCS1_INOUT inout functionality */
    {6U, 36U, 233U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_13_H_INOUT inout functionality */
    {6U, 37U, 93U, 1U, 0U}, 
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {6U, 38U, 171U, 4U, 0U}, 
    /* LPSPI3_LPSPI3_PCS1_INOUT inout functionality */
    {6U, 39U, 249U, 5U, 0U}, 
    /* Inout settings for pad PORT7 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART3_LPUART3_TX_INOUT inout functionality */
    {7U, 34U, 366U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_PCS1_INOUT inout functionality */
    {7U, 35U, 222U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_11_H_INOUT inout functionality */
    {7U, 36U, 91U, 1U, 0U}, 
    /* FXIO_FXIO_D9_INOUT inout functionality */
    {7U, 39U, 161U, 3U, 0U}, 
    /* Inout settings for pad PORT8 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_INOUT inout functionality */
    {8U, 35U, 92U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_SOUT_INOUT inout functionality */
    {8U, 36U, 247U, 1U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {8U, 37U, 158U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_7_H_INOUT inout functionality */
    {8U, 39U, 119U, 3U, 0U}, 
    /* Inout settings for pad PORT9 :   {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {9U, 35U, 365U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {9U, 36U, 241U, 1U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {9U, 37U, 159U, 2U, 0U}, 
    /* LPSPI3_LPSPI3_PCS0_INOUT inout functionality */
    {9U, 39U, 248U, 3U, 0U}, 
    /* Inout settings for pad PORT10 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_12_H_INOUT inout functionality */
    {10U, 35U, 60U, 2U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {10U, 37U, 152U, 2U, 0U}, 
    /* Inout settings for pad PORT11 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_13_H_INOUT inout functionality */
    {11U, 35U, 61U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {11U, 36U, 81U, 3U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {11U, 37U, 153U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_PCS0_INOUT inout functionality */
    {11U, 39U, 232U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_SCK_INOUT inout functionality */
    {11U, 40U, 245U, 5U, 0U}, 
    /* Inout settings for pad PORT12 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI1_LPSPI1_PCS5_INOUT inout functionality */
    {12U, 34U, 237U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_14_H_INOUT inout functionality */
    {12U, 35U, 62U, 1U, 0U}, 
    /* FXIO_FXIO_D9_INOUT inout functionality */
    {12U, 38U, 161U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_2_H_INOUT inout functionality */
    {12U, 39U, 82U, 4U, 0U}, 
    /* Inout settings for pad PORT13 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI1_LPSPI1_PCS4_INOUT inout functionality */
    {13U, 34U, 236U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_15_H_INOUT inout functionality */
    {13U, 35U, 63U, 2U, 0U}, 
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {13U, 38U, 160U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {13U, 39U, 83U, 4U, 0U}, 
    /* LPUART11_LPUART11_TX_INOUT inout functionality */
    {13U, 40U, 412U, 1U, 0U}, 
    /* Inout settings for pad PORT14 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {14U, 35U, 84U, 7U, 0U}, 
    /* LPSPI1_LPSPI1_PCS3_INOUT inout functionality */
    {14U, 36U, 235U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_18_Y_INOUT inout functionality */
    {14U, 37U, 130U, 4U, 0U}, 
    /* FXIO_FXIO_D14_INOUT inout functionality */
    {14U, 39U, 166U, 4U, 0U}, 
    /* LPSPI5_LPSPI5_PCS1_INOUT inout functionality */
    {14U, 40U, 263U, 2U, 0U}, 
    /* Inout settings for pad PORT15 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_10_H_INOUT inout functionality */
    {15U, 35U, 58U, 2U, 0U}, 
    /* LPSPI0_LPSPI0_PCS3_INOUT inout functionality */
    {15U, 36U, 224U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_PCS3_INOUT inout functionality */
    {15U, 37U, 244U, 1U, 0U}, 
    /* LPSPI5_LPSPI5_PCS0_INOUT inout functionality */
    {15U, 39U, 262U, 3U, 0U}, 
    /* FXIO_FXIO_D31_INOUT inout functionality */
    {15U, 40U, 183U, 1U, 0U}, 
    /* Inout settings for pad PORT16 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_PCS3_INOUT inout functionality */
    {16U, 34U, 258U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_11_H_INOUT inout functionality */
    {16U, 35U, 59U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_PCS2_INOUT inout functionality */
    {16U, 36U, 234U, 2U, 0U}, 
    /* LPSPI0_LPSPI0_PCS4_INOUT inout functionality */
    {16U, 37U, 225U, 1U, 0U}, 
    /* LPUART6_LPUART6_TX_INOUT inout functionality */
    {16U, 38U, 369U, 1U, 0U}, 
    /* FXIO_FXIO_D30_INOUT inout functionality */
    {16U, 40U, 182U, 1U, 0U}, 
    /* Inout settings for pad PORT17 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_6_G_INOUT inout functionality */
    {17U, 35U, 54U, 2U, 0U}, 
    /* LPUART4_LPUART4_TX_INOUT inout functionality */
    {17U, 37U, 367U, 1U, 0U}, 
    /* LPSPI3_LPSPI3_SOUT_INOUT inout functionality */
    {17U, 39U, 254U, 2U, 0U}, 
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {17U, 40U, 171U, 1U, 0U}, 
    /* Inout settings for pad PORT18 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {18U, 35U, 80U, 1U, 0U}, 
    /* LPUART1_LPUART1_TX_INOUT inout functionality */
    {18U, 36U, 364U, 4U, 0U}, 
    /* LPSPI1_LPSPI1_SOUT_INOUT inout functionality */
    {18U, 37U, 240U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_16_X_INOUT inout functionality */
    {18U, 38U, 96U, 1U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_0_X_INOUT inout functionality */
    {18U, 39U, 112U, 2U, 0U}, 
    /* Inout settings for pad PORT19 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {19U, 35U, 81U, 1U, 0U}, 
    /* LPSPI1_LPSPI1_SCK_INOUT inout functionality */
    {19U, 37U, 238U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_1_H_INOUT inout functionality */
    {19U, 39U, 113U, 2U, 0U}, 
    /* Inout settings for pad PORT20 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_INOUT inout functionality */
    {20U, 35U, 82U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_SIN_INOUT inout functionality */
    {20U, 37U, 239U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_2_H_INOUT inout functionality */
    {20U, 39U, 114U, 2U, 0U}, 
    /* Inout settings for pad PORT21 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI2_LPSPI2_PCS2_INOUT inout functionality */
    {21U, 34U, 243U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {21U, 35U, 83U, 1U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {21U, 36U, 152U, 3U, 0U}, 
    /* LPSPI1_LPSPI1_PCS0_INOUT inout functionality */
    {21U, 37U, 232U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_3_H_INOUT inout functionality */
    {21U, 39U, 115U, 2U, 0U}, 
    /* Inout settings for pad PORT22 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {22U, 35U, 84U, 1U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {22U, 36U, 153U, 3U, 0U}, 
    /* LPSPI1_LPSPI1_PCS1_INOUT inout functionality */
    {22U, 37U, 233U, 3U, 0U}, 
    /* Inout settings for pad PORT23 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_INOUT inout functionality */
    {23U, 35U, 86U, 2U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {23U, 36U, 154U, 3U, 0U}, 
    /* Inout settings for pad PORT26 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_9_H_INOUT inout functionality */
    {26U, 35U, 89U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_PCS0_INOUT inout functionality */
    {26U, 36U, 232U, 5U, 0U}, 
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {26U, 37U, 221U, 3U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {26U, 38U, 153U, 7U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_9_H_INOUT inout functionality */
    {26U, 39U, 121U, 2U, 0U}, 
    /* GMAC0_GMAC0_PPS0_INOUT inout functionality */
    {26U, 40U, 144U, 3U, 0U}, 
    /* Inout settings for pad PORT27 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {27U, 34U, 157U, 9U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_10_H_INOUT inout functionality */
    {27U, 35U, 90U, 3U, 0U}, 
    /* GMAC0_GMAC0_PPS1_INOUT inout functionality */
    {27U, 36U, 145U, 3U, 0U}, 
    /* LPUART0_LPUART0_TX_INOUT inout functionality */
    {27U, 37U, 363U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_10_H_INOUT inout functionality */
    {27U, 39U, 122U, 2U, 0U}, 
    /* Inout settings for pad PORT28 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_11_H_INOUT inout functionality */
    {28U, 35U, 91U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_SCK_INOUT inout functionality */
    {28U, 36U, 238U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_11_H_INOUT inout functionality */
    {28U, 39U, 123U, 2U, 0U}, 
    /* Inout settings for pad PORT29 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_INOUT inout functionality */
    {29U, 35U, 92U, 3U, 0U}, 
    /* GMAC0_GMAC0_PPS2_INOUT inout functionality */
    {29U, 36U, 146U, 3U, 0U}, 
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {29U, 37U, 365U, 5U, 0U}, 
    /* LPSPI1_LPSPI1_SIN_INOUT inout functionality */
    {29U, 38U, 239U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_12_H_INOUT inout functionality */
    {29U, 39U, 124U, 1U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_MDIO_INOUT inout functionality */
    {29U, 41U, 454U, 1U, 0U}, 
    /* Inout settings for pad PORT30 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_13_H_INOUT inout functionality */
    {30U, 35U, 93U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_SOUT_INOUT inout functionality */
    {30U, 36U, 240U, 5U, 0U}, 
    /* LPSPI0_LPSPI0_SOUT_INOUT inout functionality */
    {30U, 37U, 231U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_13_H_INOUT inout functionality */
    {30U, 39U, 125U, 2U, 0U}, 
    /* Inout settings for pad PORT31 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_PPS0_INOUT inout functionality */
    {31U, 34U, 144U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_14_H_INOUT inout functionality */
    {31U, 35U, 94U, 2U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {31U, 36U, 152U, 6U, 0U}, 
    /* LPSPI0_LPSPI0_PCS1_INOUT inout functionality */
    {31U, 37U, 222U, 2U, 0U}, 
    /* GMAC1_GMAC1_PPS0_INOUT inout functionality */
    {31U, 41U, 457U, 1U, 0U}, 
    /* Inout settings for pad PORT32 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPI2C0_LPI2C0_SDAS_INOUT inout functionality */
    {32U, 34U, 215U, 1U, 0U}, 
    /* FXIO_FXIO_D14_INOUT inout functionality */
    {32U, 35U, 166U, 3U, 0U}, 
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {32U, 36U, 221U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {32U, 37U, 51U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_6_H_INOUT inout functionality */
    {32U, 39U, 86U, 1U, 0U}, 
    /* Inout settings for pad PORT33 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPI2C0_LPI2C0_SCLS_INOUT inout functionality */
    {33U, 34U, 213U, 1U, 0U}, 
    /* LPUART0_LPUART0_TX_INOUT inout functionality */
    {33U, 35U, 363U, 2U, 0U}, 
    /* LPSPI0_LPSPI0_SOUT_INOUT inout functionality */
    {33U, 36U, 231U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_7_G_INOUT inout functionality */
    {33U, 37U, 55U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {33U, 39U, 85U, 1U, 0U}, 
    /* Inout settings for pad PORT34 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_8_X_INOUT inout functionality */
    {34U, 35U, 56U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_SIN_INOUT inout functionality */
    {34U, 36U, 246U, 2U, 0U}, 
    /* SAI0_SAI0_D0_INOUT inout functionality */
    {34U, 39U, 316U, 1U, 0U}, 
    /* FXIO_FXIO_D18_INOUT inout functionality */
    {34U, 40U, 170U, 1U, 0U}, 
    /* Inout settings for pad PORT35 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART9_LPUART9_TX_INOUT inout functionality */
    {35U, 34U, 410U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_9_H_INOUT inout functionality */
    {35U, 35U, 57U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_SOUT_INOUT inout functionality */
    {35U, 36U, 247U, 2U, 0U}, 
    /* FXIO_FXIO_D17_INOUT inout functionality */
    {35U, 40U, 169U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_RGMII_TXD3_INOUT inout functionality */
    {35U, 41U, 304U, 4U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_INOUT inout functionality */
    {35U, 42U, 296U, 5U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_INOUT inout functionality */
    {35U, 43U, 463U, 2U, 0U}, 
    /* Inout settings for pad PORT36 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_4_G_INOUT inout functionality */
    {36U, 35U, 52U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_SOUT_INOUT inout functionality */
    {36U, 36U, 231U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_MDIO_INOUT inout functionality */
    {36U, 38U, 291U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_10_H_INOUT inout functionality */
    {36U, 39U, 90U, 6U, 0U}, 
    /* SAI0_SAI0_D1_INOUT inout functionality */
    {36U, 40U, 317U, 2U, 0U}, 
    /* Inout settings for pad PORT37 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_5_G_INOUT inout functionality */
    {37U, 35U, 53U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_PCS1_INOUT inout functionality */
    {37U, 36U, 222U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {37U, 37U, 221U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_11_H_INOUT inout functionality */
    {37U, 39U, 91U, 5U, 0U}, 
    /* Inout settings for pad PORT40 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_PCS0_INOUT inout functionality */
    {40U, 34U, 255U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {40U, 35U, 95U, 6U, 0U}, 
    /* LPSPI0_LPSPI0_PCS5_INOUT inout functionality */
    {40U, 39U, 226U, 1U, 0U}, 
    /* FXIO_FXIO_D29_INOUT inout functionality */
    {40U, 40U, 181U, 1U, 0U}, 
    /* Inout settings for pad PORT41 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_SOUT_INOUT inout functionality */
    {41U, 34U, 261U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_16_X_INOUT inout functionality */
    {41U, 35U, 96U, 5U, 0U}, 
    /* FXIO_FXIO_D28_INOUT inout functionality */
    {41U, 40U, 180U, 1U, 0U}, 
    /* Inout settings for pad PORT42 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_SCK_INOUT inout functionality */
    {42U, 34U, 259U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_17_Y_INOUT inout functionality */
    {42U, 35U, 97U, 4U, 0U}, 
    /* LPUART9_LPUART9_TX_INOUT inout functionality */
    {42U, 38U, 410U, 2U, 0U}, 
    /* FXIO_FXIO_D27_INOUT inout functionality */
    {42U, 40U, 179U, 1U, 0U}, 
    /* Inout settings for pad PORT43 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_SIN_INOUT inout functionality */
    {43U, 34U, 260U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_18_Y_INOUT inout functionality */
    {43U, 35U, 98U, 4U, 0U}, 
    /* FXIO_FXIO_D26_INOUT inout functionality */
    {43U, 40U, 178U, 1U, 0U}, 
    /* Inout settings for pad PORT44 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_PCS3_INOUT inout functionality */
    {44U, 34U, 251U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_0_X_INOUT inout functionality */
    {44U, 35U, 48U, 1U, 0U}, 
    /* FXIO_FXIO_D25_INOUT inout functionality */
    {44U, 40U, 177U, 1U, 0U}, 
    /* Inout settings for pad PORT45 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_PCS2_INOUT inout functionality */
    {45U, 34U, 250U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_1_G_INOUT inout functionality */
    {45U, 35U, 49U, 2U, 0U}, 
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {45U, 36U, 160U, 3U, 0U}, 
    /* LPUART8_LPUART8_TX_INOUT inout functionality */
    {45U, 39U, 409U, 1U, 0U}, 
    /* FXIO_FXIO_D24_INOUT inout functionality */
    {45U, 40U, 176U, 1U, 0U}, 
    /* Inout settings for pad PORT46 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_2_G_INOUT inout functionality */
    {46U, 35U, 50U, 3U, 0U}, 
    /* LPSPI1_LPSPI1_SCK_INOUT inout functionality */
    {46U, 36U, 238U, 2U, 0U}, 
    /* FXIO_FXIO_D23_INOUT inout functionality */
    {46U, 40U, 175U, 1U, 0U}, 
    /* Inout settings for pad PORT47 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {47U, 35U, 51U, 1U, 0U}, 
    /* LPSPI1_LPSPI1_SIN_INOUT inout functionality */
    {47U, 36U, 239U, 1U, 0U}, 
    /* LPUART7_LPUART7_TX_INOUT inout functionality */
    {47U, 39U, 370U, 1U, 0U}, 
    /* FXIO_FXIO_D22_INOUT inout functionality */
    {47U, 40U, 174U, 1U, 0U}, 
    /* Inout settings for pad PORT48 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_4_G_INOUT inout functionality */
    {48U, 35U, 52U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_SOUT_INOUT inout functionality */
    {48U, 36U, 240U, 2U, 0U}, 
    /* LPUART4_LPUART4_TX_INOUT inout functionality */
    {48U, 37U, 367U, 2U, 0U}, 
    /* FXIO_FXIO_D21_INOUT inout functionality */
    {48U, 40U, 173U, 1U, 0U}, 
    /* Inout settings for pad PORT49 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_5_G_INOUT inout functionality */
    {49U, 35U, 53U, 2U, 0U}, 
    /* LPSPI1_LPSPI1_PCS3_INOUT inout functionality */
    {49U, 36U, 235U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_7_H_INOUT inout functionality */
    {49U, 37U, 87U, 7U, 0U}, 
    /* LPSPI3_LPSPI3_PCS0_INOUT inout functionality */
    {49U, 39U, 248U, 2U, 0U}, 
    /* FXIO_FXIO_D20_INOUT inout functionality */
    {49U, 40U, 172U, 1U, 0U}, 
    /* Inout settings for pad PORT50 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART13_LPUART13_TX_INOUT inout functionality */
    {50U, 34U, 414U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {50U, 35U, 95U, 2U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {50U, 36U, 153U, 6U, 0U}, 
    /* LPSPI1_LPSPI1_PCS1_INOUT inout functionality */
    {50U, 37U, 233U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_14_H_INOUT inout functionality */
    {50U, 38U, 126U, 2U, 0U}, 
    /* Inout settings for pad PORT51 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_PPS0_INOUT inout functionality */
    {51U, 34U, 144U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {51U, 35U, 95U, 3U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {51U, 36U, 154U, 5U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_EN_INOUT inout functionality */
    {51U, 37U, 297U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_15_H_INOUT inout functionality */
    {51U, 38U, 127U, 3U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_MDIO_INOUT inout functionality */
    {51U, 41U, 454U, 2U, 0U}, 
    /* Inout settings for pad PORT52 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART14_LPUART14_TX_INOUT inout functionality */
    {52U, 34U, 415U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_16_X_INOUT inout functionality */
    {52U, 35U, 96U, 3U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {52U, 36U, 155U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_16_X_INOUT inout functionality */
    {52U, 38U, 128U, 2U, 0U}, 
    /* GMAC1_GMAC1_PPS2_INOUT inout functionality */
    {52U, 41U, 458U, 1U, 0U}, 
    /* Inout settings for pad PORT53 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_17_Y_INOUT inout functionality */
    {53U, 35U, 97U, 2U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {53U, 36U, 156U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_17_Y_INOUT inout functionality */
    {53U, 38U, 129U, 2U, 0U}, 
    /* Inout settings for pad PORT54 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_18_Y_INOUT inout functionality */
    {54U, 35U, 98U, 2U, 0U}, 
    /* LPSPI3_LPSPI3_PCS1_INOUT inout functionality */
    {54U, 36U, 249U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_18_Y_INOUT inout functionality */
    {54U, 37U, 130U, 2U, 0U}, 
    /* LPUART1_LPUART1_TX_INOUT inout functionality */
    {54U, 38U, 364U, 5U, 0U}, 
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {54U, 39U, 167U, 5U, 0U}, 
    /* Inout settings for pad PORT55 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_19_Y_INOUT inout functionality */
    {55U, 35U, 99U, 2U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {55U, 36U, 156U, 6U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_19_Y_INOUT inout functionality */
    {55U, 37U, 131U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RGMII_RXD2_INOUT inout functionality */
    {55U, 41U, 301U, 5U, 0U}, 
    /* Inout settings for pad PORT56 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_20_Y_INOUT inout functionality */
    {56U, 35U, 100U, 2U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {56U, 36U, 157U, 6U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_20_Y_INOUT inout functionality */
    {56U, 37U, 132U, 2U, 0U}, 
    /* Inout settings for pad PORT57 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART15_LPUART15_TX_INOUT inout functionality */
    {57U, 34U, 416U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_21_Y_INOUT inout functionality */
    {57U, 35U, 101U, 2U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {57U, 36U, 158U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_21_Y_INOUT inout functionality */
    {57U, 37U, 133U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {57U, 38U, 241U, 4U, 0U}, 
    /* GMAC0_GMAC0_RGMII_TXCTL_INOUT inout functionality */
    {57U, 39U, 469U, 1U, 0U}, 
    /* Inout settings for pad PORT58 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_22_X_INOUT inout functionality */
    {58U, 35U, 102U, 2U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {58U, 36U, 159U, 6U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_22_X_INOUT inout functionality */
    {58U, 37U, 134U, 2U, 0U}, 
    /* Inout settings for pad PORT59 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART5_LPUART5_TX_INOUT inout functionality */
    {59U, 34U, 368U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_23_X_INOUT inout functionality */
    {59U, 35U, 103U, 2U, 0U}, 
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {59U, 36U, 160U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_23_X_INOUT inout functionality */
    {59U, 37U, 135U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_SOUT_INOUT inout functionality */
    {59U, 38U, 247U, 3U, 0U}, 
    /* SAI0_SAI0_D0_INOUT inout functionality */
    {59U, 39U, 316U, 2U, 0U}, 
    /* Inout settings for pad PORT60 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_RGMII_TXD2_INOUT inout functionality */
    {60U, 35U, 303U, 4U, 0U}, 
    /* FXIO_FXIO_D9_INOUT inout functionality */
    {60U, 36U, 161U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_10_H_INOUT inout functionality */
    {60U, 37U, 122U, 3U, 0U}, 
    /* LPSPI2_LPSPI2_SIN_INOUT inout functionality */
    {60U, 38U, 246U, 3U, 0U}, 
    /* GMAC0_GMAC0_PPS3_INOUT inout functionality */
    {60U, 40U, 147U, 2U, 0U}, 
    /* Inout settings for pad PORT61 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART6_LPUART6_TX_INOUT inout functionality */
    {61U, 34U, 369U, 3U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_TXD_0_INOUT inout functionality */
    {61U, 35U, 298U, 3U, 0U}, 
    /* FXIO_FXIO_D10_INOUT inout functionality */
    {61U, 36U, 162U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_11_H_INOUT inout functionality */
    {61U, 37U, 123U, 3U, 0U}, 
    /* LPSPI2_LPSPI2_SCK_INOUT inout functionality */
    {61U, 38U, 245U, 3U, 0U}, 
    /* SAI0_SAI0_D1_INOUT inout functionality */
    {61U, 40U, 317U, 1U, 0U}, 
    /* Inout settings for pad PORT62 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {62U, 36U, 163U, 2U, 0U}, 
    /* Inout settings for pad PORT63 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_19_Y_INOUT inout functionality */
    {63U, 34U, 67U, 5U, 0U}, 
    /* Inout settings for pad PORT64 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_0_X_INOUT inout functionality */
    {64U, 35U, 48U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_14_H_INOUT inout functionality */
    {64U, 39U, 62U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT inout functionality */
    {64U, 40U, 296U, 4U, 0U}, 
    /* GMAC1_GMAC1_MII_RGMII_TXD2_INOUT inout functionality */
    {64U, 41U, 464U, 1U, 0U}, 
    /* Inout settings for pad PORT65 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_1_G_INOUT inout functionality */
    {65U, 35U, 49U, 1U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {65U, 37U, 157U, 7U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_15_H_INOUT inout functionality */
    {65U, 39U, 63U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_INOUT inout functionality */
    {65U, 40U, 296U, 7U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_TX_CLK_INOUT inout functionality */
    {65U, 41U, 463U, 1U, 0U}, 
    /* Inout settings for pad PORT66 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_RMII_TXD_1_INOUT inout functionality */
    {66U, 34U, 299U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_2_G_INOUT inout functionality */
    {66U, 35U, 50U, 2U, 0U}, 
    /* LPSPI3_LPSPI3_PCS2_INOUT inout functionality */
    {66U, 36U, 250U, 4U, 0U}, 
    /* LPSPI0_LPSPI0_PCS2_INOUT inout functionality */
    {66U, 37U, 223U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TXD_0_INOUT inout functionality */
    {66U, 38U, 298U, 1U, 0U}, 
    /* QUADSPI_QUADSPI_IOFA3_INOUT inout functionality */
    {66U, 40U, 308U, 1U, 0U}, 
    /* GMAC1_GMAC1_MII_RGMII_RXD3_INOUT inout functionality */
    {66U, 41U, 451U, 1U, 0U}, 
    /* Inout settings for pad PORT67 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {67U, 35U, 51U, 3U, 0U}, 
    /* LPUART0_LPUART0_TX_INOUT inout functionality */
    {67U, 37U, 363U, 3U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_TX_EN_INOUT inout functionality */
    {67U, 40U, 459U, 1U, 0U}, 
    /* Inout settings for pad PORT68 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_8_X_INOUT inout functionality */
    {68U, 35U, 56U, 2U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {68U, 37U, 157U, 8U, 0U}, 
    /* Inout settings for pad PORT69 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_16_X_INOUT inout functionality */
    {69U, 35U, 64U, 2U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {69U, 37U, 156U, 7U, 0U}, 
    /* Inout settings for pad PORT70 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPI2C1_LPI2C1_SDA_INOUT inout functionality */
    {70U, 34U, 219U, 2U, 0U}, 
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {70U, 35U, 163U, 3U, 0U}, 
    /* LPSPI1_LPSPI1_PCS1_INOUT inout functionality */
    {70U, 36U, 233U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_6_H_INOUT inout functionality */
    {70U, 38U, 86U, 4U, 0U}, 
    /* LPSPI0_LPSPI0_PCS1_INOUT inout functionality */
    {70U, 39U, 222U, 4U, 0U}, 
    /* Inout settings for pad PORT71 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D10_INOUT inout functionality */
    {71U, 34U, 162U, 3U, 0U}, 
    /* LPUART1_LPUART1_TX_INOUT inout functionality */
    {71U, 35U, 364U, 1U, 0U}, 
    /* LPI2C1_LPI2C1_SCL_INOUT inout functionality */
    {71U, 36U, 217U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_7_H_INOUT inout functionality */
    {71U, 38U, 87U, 4U, 0U}, 
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {71U, 39U, 221U, 6U, 0U}, 
    /* Inout settings for pad PORT72 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPI2C0_LPI2C0_SCL_INOUT inout functionality */
    {72U, 34U, 212U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_9_H_INOUT inout functionality */
    {72U, 37U, 89U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_SCK_INOUT inout functionality */
    {72U, 39U, 229U, 1U, 0U}, 
    /* FXIO_FXIO_D12_INOUT inout functionality */
    {72U, 40U, 164U, 3U, 0U}, 
    /* Inout settings for pad PORT73 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPI2C0_LPI2C0_SDA_INOUT inout functionality */
    {73U, 34U, 214U, 1U, 0U}, 
    /* LPUART1_LPUART1_TX_INOUT inout functionality */
    {73U, 35U, 364U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_8_X_INOUT inout functionality */
    {73U, 37U, 88U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_SIN_INOUT inout functionality */
    {73U, 39U, 230U, 2U, 0U}, 
    /* FXIO_FXIO_D13_INOUT inout functionality */
    {73U, 40U, 165U, 3U, 0U}, 
    /* Inout settings for pad PORT74 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_6_G_INOUT inout functionality */
    {74U, 34U, 54U, 4U, 0U}, 
    /* LPUART11_LPUART11_TX_INOUT inout functionality */
    {74U, 35U, 412U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_PCS1_INOUT inout functionality */
    {74U, 37U, 242U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_PCS0_INOUT inout functionality */
    {74U, 38U, 255U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {74U, 40U, 80U, 6U, 0U}, 
    /* Inout settings for pad PORT75 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {75U, 36U, 81U, 7U, 0U}, 
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {75U, 37U, 167U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_SOUT_INOUT inout functionality */
    {75U, 38U, 261U, 1U, 0U}, 
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {75U, 39U, 171U, 3U, 0U}, 
    /* Inout settings for pad PORT76 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_INOUT inout functionality */
    {76U, 35U, 82U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_22_X_INOUT inout functionality */
    {76U, 36U, 70U, 2U, 0U}, 
    /* LPSPI2_LPSPI2_PCS1_INOUT inout functionality */
    {76U, 37U, 242U, 4U, 0U}, 
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {76U, 38U, 171U, 5U, 0U}, 
    /* SAI0_SAI0_BCLK_INOUT inout functionality */
    {76U, 40U, 315U, 1U, 0U}, 
    /* Inout settings for pad PORT77 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART10_LPUART10_TX_INOUT inout functionality */
    {77U, 34U, 411U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {77U, 35U, 83U, 7U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_23_X_INOUT inout functionality */
    {77U, 36U, 71U, 1U, 0U}, 
    /* FXIO_FXIO_D16_INOUT inout functionality */
    {77U, 38U, 168U, 3U, 0U}, 
    /* SAI0_SAI0_SYNC_INOUT inout functionality */
    {77U, 40U, 321U, 1U, 0U}, 
    /* Inout settings for pad PORT78 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_0_INOUT inout functionality */
    {78U, 34U, 294U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_10_H_INOUT inout functionality */
    {78U, 35U, 58U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {78U, 36U, 241U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {78U, 38U, 84U, 8U, 0U}, 
    /* FXIO_FXIO_D16_INOUT inout functionality */
    {78U, 40U, 168U, 1U, 0U}, 
    /* Inout settings for pad PORT79 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_11_H_INOUT inout functionality */
    {79U, 35U, 59U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_SCK_INOUT inout functionality */
    {79U, 36U, 245U, 2U, 0U}, 
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {79U, 38U, 365U, 2U, 0U}, 
    /* LPI2C1_LPI2C1_SCL_INOUT inout functionality */
    {79U, 40U, 217U, 6U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_RXD_1_INOUT inout functionality */
    {79U, 41U, 295U, 6U, 0U}, 
    /* Inout settings for pad PORT80 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_SIN_INOUT inout functionality */
    {80U, 34U, 253U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_9_H_INOUT inout functionality */
    {80U, 35U, 89U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_9_H_INOUT inout functionality */
    {80U, 36U, 121U, 4U, 0U}, 
    /* LPI2C1_LPI2C1_SDAS_INOUT inout functionality */
    {80U, 37U, 220U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_INOUT inout functionality */
    {80U, 38U, 292U, 6U, 0U}, 
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {80U, 39U, 167U, 1U, 0U}, 
    /* LPI2C1_LPI2C1_SDA_INOUT inout functionality */
    {80U, 40U, 219U, 5U, 0U}, 
    /* Inout settings for pad PORT81 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_SCK_INOUT inout functionality */
    {81U, 34U, 252U, 3U, 0U}, 
    /* LPI2C1_LPI2C1_SCLS_INOUT inout functionality */
    {81U, 37U, 218U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RX_DV_RGMII_RXCTL_INOUT inout functionality */
    {81U, 38U, 292U, 1U, 0U}, 
    /* FXIO_FXIO_D14_INOUT inout functionality */
    {81U, 39U, 166U, 1U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {81U, 40U, 154U, 10U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_TXD_1_INOUT inout functionality */
    {81U, 41U, 467U, 1U, 0U}, 
    /* Inout settings for pad PORT82 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {82U, 35U, 158U, 9U, 0U}, 
    /* FXIO_FXIO_D12_INOUT inout functionality */
    {82U, 36U, 164U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_12_H_INOUT inout functionality */
    {82U, 37U, 124U, 3U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_TXD_1_INOUT inout functionality */
    {82U, 38U, 299U, 3U, 0U}, 
    /* SAI0_SAI0_D2_INOUT inout functionality */
    {82U, 40U, 318U, 1U, 0U}, 
    /* Inout settings for pad PORT83 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART7_LPUART7_TX_INOUT inout functionality */
    {83U, 34U, 370U, 2U, 0U}, 
    /* FXIO_FXIO_D13_INOUT inout functionality */
    {83U, 36U, 165U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_13_H_INOUT inout functionality */
    {83U, 37U, 125U, 3U, 0U}, 
    /* LPSPI2_LPSPI2_PCS1_INOUT inout functionality */
    {83U, 38U, 242U, 2U, 0U}, 
    /* SAI0_SAI0_D3_INOUT inout functionality */
    {83U, 40U, 319U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_TX_CLK_INOUT inout functionality */
    {83U, 41U, 296U, 6U, 0U}, 
    /* Inout settings for pad PORT84 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D14_INOUT inout functionality */
    {84U, 36U, 166U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_14_H_INOUT inout functionality */
    {84U, 37U, 126U, 3U, 0U}, 
    /* GMAC0_GMAC0_PPS0_INOUT inout functionality */
    {84U, 40U, 144U, 6U, 0U}, 
    /* Inout settings for pad PORT85 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_PPS1_INOUT inout functionality */
    {85U, 34U, 145U, 4U, 0U}, 
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {85U, 36U, 167U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_15_H_INOUT inout functionality */
    {85U, 37U, 127U, 5U, 0U}, 
    /* Inout settings for pad PORT86 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_8_X_INOUT inout functionality */
    {86U, 34U, 56U, 3U, 0U}, 
    /* Inout settings for pad PORT87 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D16_INOUT inout functionality */
    {87U, 36U, 168U, 2U, 0U}, 
    /* Inout settings for pad PORT88 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART12_LPUART12_TX_INOUT inout functionality */
    {88U, 34U, 413U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {88U, 35U, 80U, 4U, 0U}, 
    /* FXIO_FXIO_D17_INOUT inout functionality */
    {88U, 36U, 169U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_0_X_INOUT inout functionality */
    {88U, 37U, 112U, 5U, 0U}, 
    /* Inout settings for pad PORT89 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {89U, 35U, 81U, 4U, 0U}, 
    /* FXIO_FXIO_D18_INOUT inout functionality */
    {89U, 36U, 170U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_1_H_INOUT inout functionality */
    {89U, 37U, 113U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_PCS1_INOUT inout functionality */
    {89U, 38U, 256U, 4U, 0U}, 
    /* Inout settings for pad PORT90 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART13_LPUART13_TX_INOUT inout functionality */
    {90U, 34U, 414U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {90U, 35U, 83U, 3U, 0U}, 
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {90U, 36U, 171U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_2_H_INOUT inout functionality */
    {90U, 37U, 114U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_SIN_INOUT inout functionality */
    {90U, 40U, 260U, 1U, 0U}, 
    /* Inout settings for pad PORT91 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {91U, 35U, 84U, 2U, 0U}, 
    /* FXIO_FXIO_D20_INOUT inout functionality */
    {91U, 36U, 172U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_3_H_INOUT inout functionality */
    {91U, 37U, 115U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_SCK_INOUT inout functionality */
    {91U, 40U, 259U, 1U, 0U}, 
    /* LPUART13_LPUART13_TX_INOUT inout functionality */
    {91U, 41U, 414U, 4U, 0U}, 
    /* Inout settings for pad PORT92 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_INOUT inout functionality */
    {92U, 35U, 87U, 3U, 0U}, 
    /* FXIO_FXIO_D21_INOUT inout functionality */
    {92U, 36U, 173U, 2U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {92U, 37U, 154U, 7U, 0U}, 
    /* LPI2C1_LPI2C1_SCL_INOUT inout functionality */
    {92U, 38U, 217U, 4U, 0U}, 
    /* LPUART0_LPUART0_TX_INOUT inout functionality */
    {92U, 41U, 363U, 6U, 0U}, 
    /* Inout settings for pad PORT93 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_10_H_INOUT inout functionality */
    {93U, 35U, 90U, 1U, 0U}, 
    /* FXIO_FXIO_D22_INOUT inout functionality */
    {93U, 36U, 174U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_4_H_INOUT inout functionality */
    {93U, 37U, 116U, 2U, 0U}, 
    /* LPI2C1_LPI2C1_SDA_INOUT inout functionality */
    {93U, 38U, 219U, 3U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {93U, 40U, 155U, 6U, 0U}, 
    /* Inout settings for pad PORT94 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_INOUT inout functionality */
    {94U, 35U, 92U, 1U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {94U, 36U, 152U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_5_H_INOUT inout functionality */
    {94U, 37U, 117U, 3U, 0U}, 
    /* FXIO_FXIO_D23_INOUT inout functionality */
    {94U, 40U, 175U, 2U, 0U}, 
    /* Inout settings for pad PORT95 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_14_H_INOUT inout functionality */
    {95U, 35U, 94U, 1U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {95U, 36U, 153U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_6_H_INOUT inout functionality */
    {95U, 38U, 118U, 2U, 0U}, 
    /* FXIO_FXIO_D24_INOUT inout functionality */
    {95U, 40U, 176U, 2U, 0U}, 
    /* Inout settings for pad PORT96 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_2_G_INOUT inout functionality */
    {96U, 35U, 50U, 1U, 0U}, 
    /* LPSPI3_LPSPI3_SOUT_INOUT inout functionality */
    {96U, 36U, 254U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_16_X_INOUT inout functionality */
    {96U, 37U, 64U, 1U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {96U, 39U, 152U, 1U, 0U}, 
    /* Inout settings for pad PORT97 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART5_LPUART5_TX_INOUT inout functionality */
    {97U, 34U, 368U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {97U, 35U, 51U, 2U, 0U}, 
    /* LPSPI3_LPSPI3_SCK_INOUT inout functionality */
    {97U, 36U, 252U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_17_Y_INOUT inout functionality */
    {97U, 37U, 65U, 1U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {97U, 39U, 153U, 1U, 0U}, 
    /* Inout settings for pad PORT98 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_21_Y_INOUT inout functionality */
    {98U, 35U, 101U, 4U, 0U}, 
    /* LPSPI1_LPSPI1_SOUT_INOUT inout functionality */
    {98U, 36U, 240U, 1U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {98U, 37U, 156U, 1U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {98U, 38U, 158U, 3U, 0U}, 
    /* LPUART3_LPUART3_TX_INOUT inout functionality */
    {98U, 39U, 366U, 2U, 0U}, 
    /* LPSPI5_LPSPI5_SOUT_INOUT inout functionality */
    {98U, 40U, 268U, 2U, 0U}, 
    /* Inout settings for pad PORT99 :  {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_22_X_INOUT inout functionality */
    {99U, 35U, 102U, 4U, 0U}, 
    /* LPSPI1_LPSPI1_PCS0_INOUT inout functionality */
    {99U, 36U, 232U, 1U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {99U, 37U, 157U, 2U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {99U, 38U, 159U, 3U, 0U}, 
    /* Inout settings for pad PORT100 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_23_X_INOUT inout functionality */
    {100U, 35U, 103U, 4U, 0U}, 
    /* LPSPI1_LPSPI1_PCS1_INOUT inout functionality */
    {100U, 36U, 233U, 6U, 0U}, 
    /* LPSPI5_LPSPI5_PCS0_INOUT inout functionality */
    {100U, 40U, 262U, 2U, 0U}, 
    /* Inout settings for pad PORT101 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_TXD2_INOUT inout functionality */
    {101U, 34U, 303U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_19_Y_INOUT inout functionality */
    {101U, 35U, 67U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_2_G_INOUT inout functionality */
    {101U, 36U, 50U, 4U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RX_DV_RGMII_RXCTL_INOUT inout functionality */
    {101U, 37U, 448U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_TXD3_INOUT inout functionality */
    {101U, 38U, 304U, 1U, 0U}, 
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {101U, 39U, 167U, 4U, 0U}, 
    /* LPSPI0_LPSPI0_PCS1_INOUT inout functionality */
    {101U, 40U, 222U, 5U, 0U}, 
    /* SAI0_SAI0_D3_INOUT inout functionality */
    {101U, 44U, 319U, 2U, 0U}, 
    /* Inout settings for pad PORT102 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_TXD3_INOUT inout functionality */
    {102U, 34U, 304U, 3U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {102U, 35U, 155U, 9U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_12_H_INOUT inout functionality */
    {102U, 36U, 92U, 5U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT inout functionality */
    {102U, 37U, 296U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_TXD2_INOUT inout functionality */
    {102U, 38U, 303U, 1U, 0U}, 
    /* FXIO_FXIO_D13_INOUT inout functionality */
    {102U, 39U, 165U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {102U, 40U, 221U, 7U, 0U}, 
    /* Inout settings for pad PORT103 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_RMII_TXD_0_INOUT inout functionality */
    {103U, 34U, 298U, 2U, 0U}, 
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {103U, 35U, 365U, 3U, 0U}, 
    /* LPSPI3_LPSPI3_PCS3_INOUT inout functionality */
    {103U, 36U, 251U, 5U, 0U}, 
    /* LPSPI0_LPSPI0_PCS3_INOUT inout functionality */
    {103U, 37U, 224U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TXD_1_INOUT inout functionality */
    {103U, 38U, 299U, 1U, 0U}, 
    /* QUADSPI_QUADSPI_IOFA1_INOUT inout functionality */
    {103U, 40U, 306U, 1U, 0U}, 
    /* GMAC1_GMAC1_MII_RGMII_RXD2_INOUT inout functionality */
    {103U, 41U, 453U, 1U, 0U}, 
    /* Inout settings for pad PORT104 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_SOUT_INOUT inout functionality */
    {104U, 34U, 254U, 3U, 0U}, 
    /* LPI2C1_LPI2C1_SDA_INOUT inout functionality */
    {104U, 35U, 219U, 1U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {104U, 38U, 153U, 5U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_12_H_INOUT inout functionality */
    {104U, 39U, 60U, 1U, 0U}, 
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {104U, 40U, 163U, 5U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_TXD_0_INOUT inout functionality */
    {104U, 41U, 466U, 1U, 0U}, 
    /* Inout settings for pad PORT105 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPI2C1_LPI2C1_SCL_INOUT inout functionality */
    {105U, 35U, 217U, 2U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {105U, 36U, 152U, 5U, 0U}, 
    /* LPUART6_LPUART6_TX_INOUT inout functionality */
    {105U, 37U, 369U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_13_H_INOUT inout functionality */
    {105U, 39U, 61U, 2U, 0U}, 
    /* FXIO_FXIO_D10_INOUT inout functionality */
    {105U, 40U, 162U, 4U, 0U}, 
    /* GMAC1_GMAC1_MII_RGMII_TXD3_INOUT inout functionality */
    {105U, 41U, 465U, 1U, 0U}, 
    /* Inout settings for pad PORT106 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_TXD3_INOUT inout functionality */
    {106U, 34U, 304U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_16_X_INOUT inout functionality */
    {106U, 35U, 64U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_10_H_INOUT inout functionality */
    {106U, 36U, 90U, 2U, 0U}, 
    /* LPSPI0_LPSPI0_SIN_INOUT inout functionality */
    {106U, 38U, 230U, 4U, 0U}, 
    /* QUADSPI_QUADSPI_SCKFA_INOUT inout functionality */
    {106U, 40U, 309U, 1U, 0U}, 
    /* Inout settings for pad PORT107 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_TXD2_INOUT inout functionality */
    {107U, 34U, 303U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_17_Y_INOUT inout functionality */
    {107U, 35U, 65U, 3U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_EN_INOUT inout functionality */
    {107U, 36U, 297U, 2U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT inout functionality */
    {107U, 38U, 296U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_SCK_INOUT inout functionality */
    {107U, 39U, 229U, 5U, 0U}, 
    /* QUADSPI_QUADSPI_IOFA0_INOUT inout functionality */
    {107U, 40U, 305U, 1U, 0U}, 
    /* GMAC1_GMAC1_RGMII_TXCTL_INOUT inout functionality */
    {107U, 41U, 468U, 1U, 0U}, 
    /* Inout settings for pad PORT108 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* GMAC0_GMAC0_MII_RMII_TX_CLK_INOUT inout functionality */
    {108U, 34U, 296U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_18_Y_INOUT inout functionality */
    {108U, 35U, 66U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_EN_INOUT inout functionality */
    {108U, 38U, 297U, 1U, 0U}, 
    /* LPSPI0_LPSPI0_SOUT_INOUT inout functionality */
    {108U, 39U, 231U, 5U, 0U}, 
    /* QUADSPI_QUADSPI_IOFA2_INOUT inout functionality */
    {108U, 40U, 307U, 1U, 0U}, 
    /* GMAC1_GMAC1_MII_RMII_RGMII_RXD_1_INOUT inout functionality */
    {108U, 41U, 452U, 1U, 0U}, 
    /* Inout settings for pad PORT109 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SIN_INOUT inout functionality */
    {109U, 34U, 267U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_20_Y_INOUT inout functionality */
    {109U, 35U, 68U, 1U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {109U, 36U, 159U, 7U, 0U}, 
    /* LPI2C0_LPI2C0_SDA_INOUT inout functionality */
    {109U, 37U, 214U, 2U, 0U}, 
    /* GMAC0_GMAC0_PPS1_INOUT inout functionality */
    {109U, 38U, 145U, 2U, 0U}, 
    /* SAI1_SAI1_D0_INOUT inout functionality */
    {109U, 39U, 323U, 1U, 0U}, 
    /* Inout settings for pad PORT110 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SCK_INOUT inout functionality */
    {110U, 34U, 266U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_21_Y_INOUT inout functionality */
    {110U, 35U, 69U, 1U, 0U}, 
    /* LPUART1_LPUART1_TX_INOUT inout functionality */
    {110U, 36U, 364U, 3U, 0U}, 
    /* LPI2C0_LPI2C0_SCL_INOUT inout functionality */
    {110U, 37U, 212U, 2U, 0U}, 
    /* GMAC0_GMAC0_PPS0_INOUT inout functionality */
    {110U, 38U, 144U, 2U, 0U}, 
    /* Inout settings for pad PORT111 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {111U, 34U, 158U, 7U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_0_X_INOUT inout functionality */
    {111U, 35U, 48U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_14_H_INOUT inout functionality */
    {111U, 36U, 94U, 6U, 0U}, 
    /* LPSPI0_LPSPI0_SCK_INOUT inout functionality */
    {111U, 37U, 229U, 3U, 0U}, 
    /* GMAC0_GMAC0_PPS2_INOUT inout functionality */
    {111U, 38U, 146U, 2U, 0U}, 
    /* SAI1_SAI1_SYNC_INOUT inout functionality */
    {111U, 39U, 325U, 1U, 0U}, 
    /* FXIO_FXIO_D10_INOUT inout functionality */
    {111U, 40U, 162U, 1U, 0U}, 
    /* Inout settings for pad PORT112 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_1_G_INOUT inout functionality */
    {112U, 35U, 49U, 3U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_RGMII_MDIO_INOUT inout functionality */
    {112U, 36U, 291U, 2U, 0U}, 
    /* LPSPI0_LPSPI0_SIN_INOUT inout functionality */
    {112U, 37U, 230U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {112U, 38U, 95U, 7U, 0U}, 
    /* LPUART8_LPUART8_TX_INOUT inout functionality */
    {112U, 40U, 409U, 2U, 0U}, 
    /* Inout settings for pad PORT113 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_PCS0_INOUT inout functionality */
    {113U, 34U, 262U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_18_Y_INOUT inout functionality */
    {113U, 35U, 66U, 3U, 0U}, 
    /* LPSPI3_LPSPI3_PCS0_INOUT inout functionality */
    {113U, 38U, 248U, 1U, 0U}, 
    /* FXIO_FXIO_D9_INOUT inout functionality */
    {113U, 39U, 161U, 1U, 0U}, 
    /* GMAC0_GMAC0_PPS2_INOUT inout functionality */
    {113U, 40U, 146U, 1U, 0U}, 
    /* Inout settings for pad PORT114 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {114U, 35U, 95U, 1U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {114U, 36U, 154U, 4U, 0U}, 
    /* Inout settings for pad PORT115 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_16_X_INOUT inout functionality */
    {115U, 35U, 96U, 2U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {115U, 36U, 155U, 4U, 0U}, 
    /* Inout settings for pad PORT116 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_17_Y_INOUT inout functionality */
    {116U, 35U, 97U, 1U, 0U}, 
    /* FXIO_FXIO_D25_INOUT inout functionality */
    {116U, 36U, 177U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_0_X_INOUT inout functionality */
    {116U, 37U, 112U, 3U, 0U}, 
    /* LPSPI1_LPSPI1_PCS2_INOUT inout functionality */
    {116U, 38U, 234U, 1U, 0U}, 
    /* LPSPI3_LPSPI3_SIN_INOUT inout functionality */
    {116U, 39U, 253U, 2U, 0U}, 
    /* Inout settings for pad PORT117 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_18_Y_INOUT inout functionality */
    {117U, 35U, 98U, 1U, 0U}, 
    /* FXIO_FXIO_D26_INOUT inout functionality */
    {117U, 36U, 178U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_8_X_INOUT inout functionality */
    {117U, 37U, 120U, 3U, 0U}, 
    /* Inout settings for pad PORT118 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_19_Y_INOUT inout functionality */
    {118U, 35U, 99U, 1U, 0U}, 
    /* FXIO_FXIO_D27_INOUT inout functionality */
    {118U, 36U, 179U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_22_X_INOUT inout functionality */
    {118U, 37U, 134U, 3U, 0U}, 
    /* Inout settings for pad PORT119 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_20_Y_INOUT inout functionality */
    {119U, 35U, 100U, 1U, 0U}, 
    /* FXIO_FXIO_D28_INOUT inout functionality */
    {119U, 36U, 180U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_23_X_INOUT inout functionality */
    {119U, 37U, 135U, 3U, 0U}, 
    /* Inout settings for pad PORT120 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_21_Y_INOUT inout functionality */
    {120U, 35U, 101U, 1U, 0U}, 
    /* FXIO_FXIO_D29_INOUT inout functionality */
    {120U, 36U, 181U, 2U, 0U}, 
    /* Inout settings for pad PORT121 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_22_X_INOUT inout functionality */
    {121U, 35U, 102U, 1U, 0U}, 
    /* Inout settings for pad PORT122 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART14_LPUART14_TX_INOUT inout functionality */
    {122U, 34U, 415U, 2U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_23_X_INOUT inout functionality */
    {122U, 35U, 103U, 1U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {122U, 36U, 159U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_7_H_INOUT inout functionality */
    {122U, 37U, 119U, 1U, 0U}, 
    /* FXIO_FXIO_D30_INOUT inout functionality */
    {122U, 38U, 182U, 2U, 0U}, 
    /* LPSPI5_LPSPI5_SCK_INOUT inout functionality */
    {122U, 39U, 266U, 3U, 0U}, 
    /* Inout settings for pad PORT123 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_9_H_INOUT inout functionality */
    {123U, 37U, 121U, 3U, 0U}, 
    /* FXIO_FXIO_D31_INOUT inout functionality */
    {123U, 38U, 183U, 2U, 0U}, 
    /* LPSPI5_LPSPI5_SOUT_INOUT inout functionality */
    {123U, 39U, 268U, 3U, 0U}, 
    /* Inout settings for pad PORT124 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART15_LPUART15_TX_INOUT inout functionality */
    {124U, 34U, 416U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_0_X_INOUT inout functionality */
    {124U, 37U, 112U, 4U, 0U}, 
    /* LPSPI5_LPSPI5_SIN_INOUT inout functionality */
    {124U, 39U, 267U, 3U, 0U}, 
    /* Inout settings for pad PORT125 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_8_X_INOUT inout functionality */
    {125U, 37U, 120U, 4U, 0U}, 
    /* LPSPI5_LPSPI5_PCS2_INOUT inout functionality */
    {125U, 39U, 264U, 1U, 0U}, 
    /* Inout settings for pad PORT126 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_16_X_INOUT inout functionality */
    {126U, 37U, 128U, 3U, 0U}, 
    /* LPSPI5_LPSPI5_PCS3_INOUT inout functionality */
    {126U, 39U, 265U, 1U, 0U}, 
    /* Inout settings for pad PORT127 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SCK_INOUT inout functionality */
    {127U, 35U, 266U, 5U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {127U, 36U, 158U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_22_X_INOUT inout functionality */
    {127U, 37U, 134U, 4U, 0U}, 
    /* Inout settings for pad PORT128 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_SIN_INOUT inout functionality */
    {128U, 35U, 230U, 1U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {128U, 36U, 155U, 7U, 0U}, 
    /* Inout settings for pad PORT129 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_SCK_INOUT inout functionality */
    {129U, 35U, 229U, 2U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {129U, 36U, 154U, 8U, 0U}, 
    /* LPUART7_LPUART7_TX_INOUT inout functionality */
    {129U, 39U, 370U, 3U, 0U}, 
    /* Inout settings for pad PORT130 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_SOUT_INOUT inout functionality */
    {130U, 35U, 231U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {130U, 36U, 51U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_8_X_INOUT inout functionality */
    {130U, 37U, 88U, 4U, 0U}, 
    /* FXIO_FXIO_D13_INOUT inout functionality */
    {130U, 39U, 165U, 4U, 0U}, 
    /* Inout settings for pad PORT131 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* SAI1_SAI1_D0_INOUT inout functionality */
    {131U, 35U, 323U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_19_Y_INOUT inout functionality */
    {131U, 36U, 67U, 4U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {131U, 37U, 158U, 6U, 0U}, 
    /* GMAC0_GMAC0_PPS0_INOUT inout functionality */
    {131U, 39U, 144U, 1U, 0U}, 
    /* GMAC1_GMAC1_PPS3_INOUT inout functionality */
    {131U, 41U, 456U, 1U, 0U}, 
    /* Inout settings for pad PORT132 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {132U, 34U, 221U, 5U, 0U}, 
    /* LPSPI1_LPSPI1_PCS1_INOUT inout functionality */
    {132U, 35U, 233U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {132U, 36U, 84U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_18_Y_INOUT inout functionality */
    {132U, 37U, 66U, 2U, 0U}, 
    /* LPUART12_LPUART12_TX_INOUT inout functionality */
    {132U, 38U, 413U, 2U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {132U, 39U, 158U, 1U, 0U}, 
    /* Inout settings for pad PORT133 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {133U, 36U, 85U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_19_Y_INOUT inout functionality */
    {133U, 37U, 67U, 1U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {133U, 39U, 159U, 1U, 0U}, 
    /* Inout settings for pad PORT134 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_PCS2_INOUT inout functionality */
    {134U, 35U, 223U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_14_H_INOUT inout functionality */
    {134U, 37U, 94U, 5U, 0U}, 
    /* LPUART10_LPUART10_TX_INOUT inout functionality */
    {134U, 38U, 411U, 2U, 0U}, 
    /* FXIO_FXIO_D12_INOUT inout functionality */
    {134U, 39U, 164U, 4U, 0U}, 
    /* Inout settings for pad PORT135 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_7_G_INOUT inout functionality */
    {135U, 35U, 55U, 2U, 0U}, 
    /* LPSPI3_LPSPI3_SCK_INOUT inout functionality */
    {135U, 39U, 252U, 2U, 0U}, 
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {135U, 40U, 163U, 4U, 0U}, 
    /* Inout settings for pad PORT136 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_PCS1_INOUT inout functionality */
    {136U, 34U, 249U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_6_G_INOUT inout functionality */
    {136U, 35U, 54U, 1U, 0U}, 
    /* LPSPI5_LPSPI5_PCS1_INOUT inout functionality */
    {136U, 36U, 263U, 1U, 0U}, 
    /* FXIO_FXIO_D12_INOUT inout functionality */
    {136U, 37U, 164U, 1U, 0U}, 
    /* SAI1_SAI1_BCLK_INOUT inout functionality */
    {136U, 39U, 322U, 1U, 0U}, 
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {136U, 40U, 160U, 5U, 0U}, 
    /* Inout settings for pad PORT137 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SOUT_INOUT inout functionality */
    {137U, 34U, 268U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_7_G_INOUT inout functionality */
    {137U, 35U, 55U, 1U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_13_H_INOUT inout functionality */
    {137U, 36U, 93U, 5U, 0U}, 
    /* GMAC0_GMAC0_PPS3_INOUT inout functionality */
    {137U, 38U, 147U, 1U, 0U}, 
    /* GMAC0_GMAC0_MII_RMII_TX_EN_INOUT inout functionality */
    {137U, 39U, 297U, 3U, 0U}, 
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {137U, 40U, 163U, 1U, 0U}, 
    /* Inout settings for pad PORT138 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI3_LPSPI3_SIN_INOUT inout functionality */
    {138U, 35U, 253U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_PCS1_INOUT inout functionality */
    {138U, 36U, 242U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_20_Y_INOUT inout functionality */
    {138U, 37U, 68U, 2U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {138U, 39U, 156U, 2U, 0U}, 
    /* Inout settings for pad PORT139 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART4_LPUART4_TX_INOUT inout functionality */
    {139U, 34U, 367U, 3U, 0U}, 
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {139U, 35U, 241U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_1_G_INOUT inout functionality */
    {139U, 36U, 49U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_21_Y_INOUT inout functionality */
    {139U, 37U, 69U, 2U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {139U, 39U, 157U, 1U, 0U}, 
    /* Inout settings for pad PORT140 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {140U, 36U, 365U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {140U, 37U, 85U, 5U, 0U}, 
    /* GMAC0_GMAC0_PPS3_INOUT inout functionality */
    {140U, 38U, 147U, 3U, 0U}, 
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {140U, 39U, 160U, 1U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {140U, 40U, 159U, 9U, 0U}, 
    /* Inout settings for pad PORT142 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_19_Y_INOUT inout functionality */
    {142U, 34U, 67U, 3U, 0U}, 
    /* LPUART5_LPUART5_TX_INOUT inout functionality */
    {142U, 37U, 368U, 2U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {142U, 39U, 159U, 5U, 0U}, 
    /* GMAC0_GMAC0_PPS1_INOUT inout functionality */
    {142U, 40U, 145U, 1U, 0U}, 
    /* GMAC1_GMAC1_PPS1_INOUT inout functionality */
    {142U, 41U, 455U, 1U, 0U}, 
    /* Inout settings for pad PORT143 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI2_LPSPI2_SCK_INOUT inout functionality */
    {143U, 36U, 245U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_22_X_INOUT inout functionality */
    {143U, 37U, 70U, 1U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {143U, 39U, 154U, 1U, 0U}, 
    /* Inout settings for pad PORT144 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART3_LPUART3_TX_INOUT inout functionality */
    {144U, 35U, 366U, 3U, 0U}, 
    /* LPSPI2_LPSPI2_SIN_INOUT inout functionality */
    {144U, 36U, 246U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_23_X_INOUT inout functionality */
    {144U, 37U, 71U, 2U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {144U, 39U, 155U, 2U, 0U}, 
    /* Inout settings for pad PORT145 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {145U, 36U, 157U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_23_X_INOUT inout functionality */
    {145U, 37U, 135U, 4U, 0U}, 
    /* Inout settings for pad PORT146 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {146U, 36U, 156U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_17_Y_INOUT inout functionality */
    {146U, 37U, 129U, 4U, 0U}, 
    /* Inout settings for pad PORT147 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_22_X_INOUT inout functionality */
    {147U, 35U, 70U, 3U, 0U}, 
    /* Inout settings for pad PORT148 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {148U, 35U, 80U, 2U, 0U}, 
    /* Inout settings for pad PORT149 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {149U, 35U, 81U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_19_Y_INOUT inout functionality */
    {149U, 37U, 131U, 4U, 0U}, 
    /* LPSPI4_LPSPI4_SIN_INOUT inout functionality */
    {149U, 39U, 260U, 3U, 0U}, 
    /* Inout settings for pad PORT150 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_INOUT inout functionality */
    {150U, 35U, 82U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_20_Y_INOUT inout functionality */
    {150U, 37U, 132U, 4U, 0U}, 
    /* LPSPI4_LPSPI4_SCK_INOUT inout functionality */
    {150U, 39U, 259U, 3U, 0U}, 
    /* Inout settings for pad PORT151 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {151U, 35U, 83U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_21_Y_INOUT inout functionality */
    {151U, 37U, 133U, 4U, 0U}, 
    /* LPSPI4_LPSPI4_PCS0_INOUT inout functionality */
    {151U, 39U, 255U, 4U, 0U}, 
    /* Inout settings for pad PORT152 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {152U, 35U, 84U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_4_H_INOUT inout functionality */
    {152U, 37U, 116U, 3U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {152U, 38U, 157U, 10U, 0U}, 
    /* LPSPI4_LPSPI4_PCS1_INOUT inout functionality */
    {152U, 39U, 256U, 3U, 0U}, 
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {152U, 40U, 163U, 6U, 0U}, 
    /* LPSPI2_LPSPI2_SIN_INOUT inout functionality */
    {152U, 41U, 246U, 5U, 0U}, 
    /* Inout settings for pad PORT153 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {153U, 35U, 85U, 2U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_5_H_INOUT inout functionality */
    {153U, 37U, 117U, 2U, 0U}, 
    /* LPSPI4_LPSPI4_SOUT_INOUT inout functionality */
    {153U, 39U, 261U, 3U, 0U}, 
    /* Inout settings for pad PORT154 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_INOUT inout functionality */
    {154U, 35U, 86U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_6_H_INOUT inout functionality */
    {154U, 37U, 118U, 3U, 0U}, 
    /* Inout settings for pad PORT155 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_INOUT inout functionality */
    {155U, 35U, 87U, 1U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_10_H_INOUT inout functionality */
    {155U, 41U, 58U, 4U, 0U}, 
    /* Inout settings for pad PORT156 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_11_H_INOUT inout functionality */
    {156U, 41U, 59U, 4U, 0U}, 
    /* Inout settings for pad PORT157 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_12_H_INOUT inout functionality */
    {157U, 41U, 60U, 4U, 0U}, 
    /* Inout settings for pad PORT158 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_SOUT_INOUT inout functionality */
    {158U, 37U, 231U, 6U, 0U}, 
    /* Inout settings for pad PORT159 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {159U, 37U, 221U, 8U, 0U}, 
    /* Inout settings for pad PORT160 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART5_LPUART5_TX_INOUT inout functionality */
    {160U, 34U, 368U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_0_X_INOUT inout functionality */
    {160U, 35U, 112U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_SCK_INOUT inout functionality */
    {160U, 36U, 245U, 4U, 0U}, 
    /* Inout settings for pad PORT161 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_1_H_INOUT inout functionality */
    {161U, 35U, 113U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_SIN_INOUT inout functionality */
    {161U, 36U, 246U, 4U, 0U}, 
    /* Inout settings for pad PORT162 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART6_LPUART6_TX_INOUT inout functionality */
    {162U, 34U, 369U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_2_H_INOUT inout functionality */
    {162U, 35U, 114U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_SOUT_INOUT inout functionality */
    {162U, 36U, 247U, 4U, 0U}, 
    /* Inout settings for pad PORT163 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_3_H_INOUT inout functionality */
    {163U, 35U, 115U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {163U, 36U, 241U, 6U, 0U}, 
    /* Inout settings for pad PORT164 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_4_H_INOUT inout functionality */
    {164U, 35U, 116U, 1U, 0U}, 
    /* LPSPI2_LPSPI2_SOUT_INOUT inout functionality */
    {164U, 36U, 247U, 5U, 0U}, 
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {164U, 37U, 152U, 7U, 0U}, 
    /* Inout settings for pad PORT165 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_5_H_INOUT inout functionality */
    {165U, 35U, 117U, 1U, 0U}, 
    /* Inout settings for pad PORT166 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_6_H_INOUT inout functionality */
    {166U, 35U, 118U, 1U, 0U}, 
    /* Inout settings for pad PORT167 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {167U, 34U, 241U, 8U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_7_H_INOUT inout functionality */
    {167U, 35U, 119U, 2U, 0U}, 
    /* LPI2C1_LPI2C1_SCL_INOUT inout functionality */
    {167U, 36U, 217U, 5U, 0U}, 
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {167U, 37U, 153U, 8U, 0U}, 
    /* Inout settings for pad PORT168 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_8_X_INOUT inout functionality */
    {168U, 35U, 120U, 1U, 0U}, 
    /* LPI2C1_LPI2C1_SDA_INOUT inout functionality */
    {168U, 36U, 219U, 4U, 0U}, 
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {168U, 37U, 154U, 9U, 0U}, 
    /* Inout settings for pad PORT169 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_9_H_INOUT inout functionality */
    {169U, 35U, 121U, 1U, 0U}, 
    /* Inout settings for pad PORT170 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_10_H_INOUT inout functionality */
    {170U, 35U, 122U, 1U, 0U}, 
    /* Inout settings for pad PORT171 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_11_H_INOUT inout functionality */
    {171U, 35U, 123U, 1U, 0U}, 
    /* Inout settings for pad PORT172 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART10_LPUART10_TX_INOUT inout functionality */
    {172U, 34U, 411U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_12_H_INOUT inout functionality */
    {172U, 35U, 124U, 2U, 0U}, 
    /* LPSPI3_LPSPI3_SIN_INOUT inout functionality */
    {172U, 37U, 253U, 4U, 0U}, 
    /* Inout settings for pad PORT173 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_13_H_INOUT inout functionality */
    {173U, 35U, 125U, 1U, 0U}, 
    /* LPSPI3_LPSPI3_SCK_INOUT inout functionality */
    {173U, 37U, 252U, 4U, 0U}, 
    /* Inout settings for pad PORT174 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_14_H_INOUT inout functionality */
    {174U, 35U, 126U, 1U, 0U}, 
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {174U, 38U, 155U, 8U, 0U}, 
    /* Inout settings for pad PORT175 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_15_H_INOUT inout functionality */
    {175U, 35U, 127U, 1U, 0U}, 
    /* LPSPI3_LPSPI3_SOUT_INOUT inout functionality */
    {175U, 37U, 254U, 4U, 0U}, 
    /* Inout settings for pad PORT176 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART12_LPUART12_TX_INOUT inout functionality */
    {176U, 34U, 413U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_16_X_INOUT inout functionality */
    {176U, 35U, 128U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {176U, 36U, 80U, 5U, 0U}, 
    /* LPSPI3_LPSPI3_PCS0_INOUT inout functionality */
    {176U, 38U, 248U, 4U, 0U}, 
    /* Inout settings for pad PORT177 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_17_Y_INOUT inout functionality */
    {177U, 35U, 129U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {177U, 36U, 81U, 5U, 0U}, 
    /* Inout settings for pad PORT178 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART7_LPUART7_TX_INOUT inout functionality */
    {178U, 34U, 370U, 4U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_18_Y_INOUT inout functionality */
    {178U, 35U, 130U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_2_H_INOUT inout functionality */
    {178U, 36U, 82U, 5U, 0U}, 
    /* LPSPI3_LPSPI3_PCS1_INOUT inout functionality */
    {178U, 38U, 249U, 2U, 0U}, 
    /* Inout settings for pad PORT179 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_19_Y_INOUT inout functionality */
    {179U, 35U, 131U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {179U, 36U, 83U, 5U, 0U}, 
    /* LPSPI3_LPSPI3_PCS2_INOUT inout functionality */
    {179U, 38U, 250U, 2U, 0U}, 
    /* Inout settings for pad PORT180 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART8_LPUART8_TX_INOUT inout functionality */
    {180U, 34U, 409U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_20_Y_INOUT inout functionality */
    {180U, 35U, 132U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {180U, 36U, 84U, 5U, 0U}, 
    /* LPI2C0_LPI2C0_SCL_INOUT inout functionality */
    {180U, 37U, 212U, 3U, 0U}, 
    /* LPSPI3_LPSPI3_PCS3_INOUT inout functionality */
    {180U, 38U, 251U, 2U, 0U}, 
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {180U, 40U, 156U, 8U, 0U}, 
    /* Inout settings for pad PORT181 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_21_Y_INOUT inout functionality */
    {181U, 35U, 133U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {181U, 36U, 85U, 6U, 0U}, 
    /* LPI2C0_LPI2C0_SDA_INOUT inout functionality */
    {181U, 37U, 214U, 3U, 0U}, 
    /* LPSPI1_LPSPI1_PCS0_INOUT inout functionality */
    {181U, 38U, 232U, 4U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {181U, 40U, 157U, 11U, 0U}, 
    /* Inout settings for pad PORT182 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_22_X_INOUT inout functionality */
    {182U, 35U, 134U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_6_H_INOUT inout functionality */
    {182U, 36U, 86U, 5U, 0U}, 
    /* LPSPI4_LPSPI4_PCS2_INOUT inout functionality */
    {182U, 39U, 257U, 2U, 0U}, 
    /* Inout settings for pad PORT183 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART9_LPUART9_TX_INOUT inout functionality */
    {183U, 34U, 410U, 3U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_23_X_INOUT inout functionality */
    {183U, 35U, 135U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_7_H_INOUT inout functionality */
    {183U, 36U, 87U, 5U, 0U}, 
    /* LPSPI3_LPSPI3_PCS3_INOUT inout functionality */
    {183U, 38U, 251U, 3U, 0U}, 
    /* Inout settings for pad PORT184 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_8_X_INOUT inout functionality */
    {184U, 36U, 88U, 3U, 0U}, 
    /* Inout settings for pad PORT185 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_9_H_INOUT inout functionality */
    {185U, 36U, 89U, 3U, 0U}, 
    /* LPSPI2_LPSPI2_PCS2_INOUT inout functionality */
    {185U, 38U, 243U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_PCS0_INOUT inout functionality */
    {185U, 39U, 255U, 3U, 0U}, 
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {185U, 40U, 158U, 10U, 0U}, 
    /* Inout settings for pad PORT186 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_10_H_INOUT inout functionality */
    {186U, 36U, 90U, 4U, 0U}, 
    /* LPSPI2_LPSPI2_PCS3_INOUT inout functionality */
    {186U, 38U, 244U, 2U, 0U}, 
    /* LPSPI4_LPSPI4_PCS1_INOUT inout functionality */
    {186U, 39U, 256U, 2U, 0U}, 
    /* Inout settings for pad PORT187 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART11_LPUART11_TX_INOUT inout functionality */
    {187U, 34U, 412U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_11_H_INOUT inout functionality */
    {187U, 36U, 91U, 3U, 0U}, 
    /* LPSPI4_LPSPI4_PCS2_INOUT inout functionality */
    {187U, 39U, 257U, 3U, 0U}, 
    /* Inout settings for pad PORT188 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_INOUT inout functionality */
    {188U, 36U, 92U, 4U, 0U}, 
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {188U, 37U, 159U, 8U, 0U}, 
    /* LPSPI0_LPSPI0_PCS0_INOUT inout functionality */
    {188U, 38U, 221U, 4U, 0U}, 
    /* LPSPI4_LPSPI4_PCS3_INOUT inout functionality */
    {188U, 39U, 258U, 2U, 0U}, 
    /* Inout settings for pad PORT189 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_13_H_INOUT inout functionality */
    {189U, 36U, 93U, 3U, 0U}, 
    /* LPSPI3_LPSPI3_PCS1_INOUT inout functionality */
    {189U, 38U, 249U, 3U, 0U}, 
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {189U, 40U, 160U, 6U, 0U}, 
    /* Inout settings for pad PORT190 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_14_H_INOUT inout functionality */
    {190U, 36U, 94U, 3U, 0U}, 
    /* Inout settings for pad PORT191 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {191U, 36U, 95U, 4U, 0U}, 
    /* FXIO_FXIO_D9_INOUT inout functionality */
    {191U, 39U, 161U, 5U, 0U}, 
    /* Inout settings for pad PORT192 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART13_LPUART13_TX_INOUT inout functionality */
    {192U, 34U, 414U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_16_X_INOUT inout functionality */
    {192U, 36U, 96U, 4U, 0U}, 
    /* Inout settings for pad PORT193 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_17_Y_INOUT inout functionality */
    {193U, 36U, 97U, 3U, 0U}, 
    /* Inout settings for pad PORT194 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART14_LPUART14_TX_INOUT inout functionality */
    {194U, 34U, 415U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_18_Y_INOUT inout functionality */
    {194U, 36U, 98U, 3U, 0U}, 
    /* Inout settings for pad PORT195 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_19_Y_INOUT inout functionality */
    {195U, 36U, 99U, 3U, 0U}, 
    /* Inout settings for pad PORT196 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART15_LPUART15_TX_INOUT inout functionality */
    {196U, 34U, 416U, 3U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_20_Y_INOUT inout functionality */
    {196U, 36U, 100U, 3U, 0U}, 
    /* Inout settings for pad PORT197 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_21_Y_INOUT inout functionality */
    {197U, 36U, 101U, 3U, 0U}, 
    /* Inout settings for pad PORT198 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D10_INOUT inout functionality */
    {198U, 35U, 162U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_22_X_INOUT inout functionality */
    {198U, 36U, 102U, 3U, 0U}, 
    /* Inout settings for pad PORT199 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {199U, 35U, 163U, 7U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_23_X_INOUT inout functionality */
    {199U, 36U, 103U, 3U, 0U}, 
    /* Inout settings for pad PORT200 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D12_INOUT inout functionality */
    {200U, 35U, 164U, 5U, 0U}, 
    /* LPSPI5_LPSPI5_PCS3_INOUT inout functionality */
    {200U, 36U, 265U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_13_H_INOUT inout functionality */
    {200U, 41U, 61U, 4U, 0U}, 
    /* Inout settings for pad PORT201 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {201U, 35U, 85U, 8U, 0U}, 
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {201U, 36U, 157U, 12U, 0U}, 
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {201U, 37U, 365U, 6U, 0U}, 
    /* Inout settings for pad PORT202 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {202U, 34U, 154U, 11U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_14_H_INOUT inout functionality */
    {202U, 41U, 62U, 4U, 0U}, 
    /* Inout settings for pad PORT203 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {203U, 34U, 155U, 10U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_15_H_INOUT inout functionality */
    {203U, 41U, 63U, 4U, 0U}, 
    /* Inout settings for pad PORT204 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI4_LPSPI4_PCS3_INOUT inout functionality */
    {204U, 39U, 258U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_16_X_INOUT inout functionality */
    {204U, 41U, 64U, 4U, 0U}, 
    /* Inout settings for pad PORT205 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D13_INOUT inout functionality */
    {205U, 35U, 165U, 5U, 0U}, 
    /* LPSPI5_LPSPI5_PCS2_INOUT inout functionality */
    {205U, 36U, 264U, 2U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_17_Y_INOUT inout functionality */
    {205U, 41U, 65U, 4U, 0U}, 
    /* Inout settings for pad PORT206 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI2_LPSPI2_PCS0_INOUT inout functionality */
    {206U, 34U, 241U, 7U, 0U}, 
    /* LPSPI2_LPSPI2_PCS2_INOUT inout functionality */
    {206U, 35U, 243U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_18_Y_INOUT inout functionality */
    {206U, 41U, 66U, 4U, 0U}, 
    /* Inout settings for pad PORT207 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D14_INOUT inout functionality */
    {207U, 35U, 166U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_15_H_INOUT inout functionality */
    {207U, 38U, 127U, 4U, 0U}, 
    /* Inout settings for pad PORT208 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_16_X_INOUT inout functionality */
    {208U, 35U, 128U, 1U, 0U}, 
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {208U, 36U, 167U, 6U, 0U}, 
    /* Inout settings for pad PORT209 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_17_Y_INOUT inout functionality */
    {209U, 35U, 129U, 1U, 0U}, 
    /* FXIO_FXIO_D16_INOUT inout functionality */
    {209U, 36U, 168U, 4U, 0U}, 
    /* Inout settings for pad PORT210 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_18_Y_INOUT inout functionality */
    {210U, 35U, 130U, 1U, 0U}, 
    /* FXIO_FXIO_D17_INOUT inout functionality */
    {210U, 36U, 169U, 3U, 0U}, 
    /* Inout settings for pad PORT211 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_19_Y_INOUT inout functionality */
    {211U, 35U, 131U, 1U, 0U}, 
    /* FXIO_FXIO_D18_INOUT inout functionality */
    {211U, 36U, 170U, 3U, 0U}, 
    /* Inout settings for pad PORT212 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_20_Y_INOUT inout functionality */
    {212U, 35U, 132U, 1U, 0U}, 
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {212U, 36U, 171U, 6U, 0U}, 
    /* Inout settings for pad PORT213 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_21_Y_INOUT inout functionality */
    {213U, 35U, 133U, 1U, 0U}, 
    /* FXIO_FXIO_D20_INOUT inout functionality */
    {213U, 36U, 172U, 3U, 0U}, 
    /* Inout settings for pad PORT214 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_22_X_INOUT inout functionality */
    {214U, 35U, 134U, 1U, 0U}, 
    /* FXIO_FXIO_D21_INOUT inout functionality */
    {214U, 36U, 173U, 3U, 0U}, 
    /* Inout settings for pad PORT215 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_23_X_INOUT inout functionality */
    {215U, 35U, 135U, 1U, 0U}, 
    /* FXIO_FXIO_D22_INOUT inout functionality */
    {215U, 36U, 174U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_0_X_INOUT inout functionality */
    {215U, 37U, 48U, 4U, 0U}, 
    /* LPSPI5_LPSPI5_PCS0_INOUT inout functionality */
    {215U, 41U, 262U, 5U, 0U}, 
    /* Inout settings for pad PORT216 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART12_LPUART12_TX_INOUT inout functionality */
    {216U, 34U, 413U, 4U, 0U}, 
    /* LPSPI5_LPSPI5_PCS2_INOUT inout functionality */
    {216U, 35U, 264U, 3U, 0U}, 
    /* FXIO_FXIO_D23_INOUT inout functionality */
    {216U, 36U, 175U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_1_G_INOUT inout functionality */
    {216U, 37U, 49U, 6U, 0U}, 
    /* Inout settings for pad PORT217 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SOUT_INOUT inout functionality */
    {217U, 35U, 268U, 5U, 0U}, 
    /* FXIO_FXIO_D24_INOUT inout functionality */
    {217U, 36U, 176U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_2_G_INOUT inout functionality */
    {217U, 37U, 50U, 6U, 0U}, 
    /* Inout settings for pad PORT218 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D25_INOUT inout functionality */
    {218U, 36U, 177U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {218U, 37U, 51U, 7U, 0U}, 
    /* Inout settings for pad PORT219 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D26_INOUT inout functionality */
    {219U, 36U, 178U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_4_G_INOUT inout functionality */
    {219U, 37U, 52U, 4U, 0U}, 
    /* Inout settings for pad PORT220 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_PCS0_INOUT inout functionality */
    {220U, 34U, 262U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_5_G_INOUT inout functionality */
    {220U, 37U, 53U, 4U, 0U}, 
    /* Inout settings for pad PORT221 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SIN_INOUT inout functionality */
    {221U, 34U, 267U, 4U, 0U}, 
    /* FXIO_FXIO_D29_INOUT inout functionality */
    {221U, 36U, 181U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_6_G_INOUT inout functionality */
    {221U, 37U, 54U, 5U, 0U}, 
    /* Inout settings for pad PORT222 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SOUT_INOUT inout functionality */
    {222U, 34U, 268U, 4U, 0U}, 
    /* FXIO_FXIO_D30_INOUT inout functionality */
    {222U, 36U, 182U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_7_G_INOUT inout functionality */
    {222U, 37U, 55U, 5U, 0U}, 
    /* Inout settings for pad PORT223 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPSPI5_LPSPI5_SCK_INOUT inout functionality */
    {223U, 34U, 266U, 4U, 0U}, 
    /* FXIO_FXIO_D31_INOUT inout functionality */
    {223U, 36U, 183U, 3U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_8_X_INOUT inout functionality */
    {223U, 37U, 56U, 4U, 0U}, 
    /* Inout settings for pad PORT224 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART0_LPUART0_TX_INOUT inout functionality */
    {224U, 35U, 363U, 5U, 0U}, 
    /* FXIO_FXIO_D16_INOUT inout functionality */
    {224U, 36U, 168U, 5U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_9_H_INOUT inout functionality */
    {224U, 37U, 57U, 4U, 0U}, 
    /* LPSPI2_LPSPI2_PCS2_INOUT inout functionality */
    {224U, 38U, 243U, 5U, 0U}, 
    /* Inout settings for pad PORT225 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D17_INOUT inout functionality */
    {225U, 36U, 169U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_10_H_INOUT inout functionality */
    {225U, 37U, 58U, 5U, 0U}, 
    /* LPSPI2_LPSPI2_PCS3_INOUT inout functionality */
    {225U, 38U, 244U, 3U, 0U}, 
    /* Inout settings for pad PORT226 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART3_LPUART3_TX_INOUT inout functionality */
    {226U, 35U, 366U, 4U, 0U}, 
    /* FXIO_FXIO_D18_INOUT inout functionality */
    {226U, 36U, 170U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_11_H_INOUT inout functionality */
    {226U, 37U, 59U, 5U, 0U}, 
    /* Inout settings for pad PORT227 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {227U, 36U, 171U, 7U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_12_H_INOUT inout functionality */
    {227U, 37U, 60U, 5U, 0U}, 
    /* Inout settings for pad PORT228 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART4_LPUART4_TX_INOUT inout functionality */
    {228U, 34U, 367U, 4U, 0U}, 
    /* FXIO_FXIO_D20_INOUT inout functionality */
    {228U, 36U, 172U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_13_H_INOUT inout functionality */
    {228U, 37U, 61U, 5U, 0U}, 
    /* Inout settings for pad PORT229 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D21_INOUT inout functionality */
    {229U, 36U, 173U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_14_H_INOUT inout functionality */
    {229U, 37U, 62U, 5U, 0U}, 
    /* Inout settings for pad PORT230 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART8_LPUART8_TX_INOUT inout functionality */
    {230U, 34U, 409U, 4U, 0U}, 
    /* FXIO_FXIO_D22_INOUT inout functionality */
    {230U, 36U, 174U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_15_H_INOUT inout functionality */
    {230U, 37U, 63U, 5U, 0U}, 
    /* Inout settings for pad PORT231 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D23_INOUT inout functionality */
    {231U, 36U, 175U, 4U, 0U}, 
    /* EMIOS_0_EMIOS_0_CH_16_X_INOUT inout functionality */
    {231U, 37U, 64U, 5U, 0U}, 
    /* Inout settings for pad PORT232 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART10_LPUART10_TX_INOUT inout functionality */
    {232U, 34U, 411U, 4U, 0U}, 
    /* LPUART2_LPUART2_TX_INOUT inout functionality */
    {232U, 35U, 365U, 7U, 0U}, 
    /* FXIO_FXIO_D24_INOUT inout functionality */
    {232U, 36U, 176U, 4U, 0U}, 
    /* Inout settings for pad PORT233 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D25_INOUT inout functionality */
    {233U, 36U, 177U, 4U, 0U}, 
    /* Inout settings for pad PORT234 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* LPUART11_LPUART11_TX_INOUT inout functionality */
    {234U, 34U, 412U, 4U, 0U}, 
    /* FXIO_FXIO_D26_INOUT inout functionality */
    {234U, 36U, 178U, 4U, 0U}, 
    /* Inout settings for pad PORT235 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D27_INOUT inout functionality */
    {235U, 36U, 179U, 3U, 0U}, 
    /* Inout settings for pad PORT236 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D28_INOUT inout functionality */
    {236U, 36U, 180U, 3U, 0U}, 
    /* Inout settings for pad PORT237 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D0_INOUT inout functionality */
    {237U, 34U, 152U, 8U, 0U}, 
    /* Inout settings for pad PORT238 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D1_INOUT inout functionality */
    {238U, 34U, 153U, 9U, 0U}, 
    /* Inout settings for pad PORT239 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D2_INOUT inout functionality */
    {239U, 34U, 154U, 12U, 0U}, 
    /* Inout settings for pad PORT240 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D3_INOUT inout functionality */
    {240U, 34U, 155U, 11U, 0U}, 
    /* Inout settings for pad PORT241 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D4_INOUT inout functionality */
    {241U, 34U, 156U, 9U, 0U}, 
    /* LPUART14_LPUART14_TX_INOUT inout functionality */
    {241U, 35U, 415U, 4U, 0U}, 
    /* Inout settings for pad PORT242 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D5_INOUT inout functionality */
    {242U, 34U, 157U, 13U, 0U}, 
    /* Inout settings for pad PORT243 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D6_INOUT inout functionality */
    {243U, 34U, 158U, 11U, 0U}, 
    /* LPUART15_LPUART15_TX_INOUT inout functionality */
    {243U, 35U, 416U, 4U, 0U}, 
    /* Inout settings for pad PORT244 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D7_INOUT inout functionality */
    {244U, 34U, 159U, 10U, 0U}, 
    /* Inout settings for pad PORT245 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_17_Y_INOUT inout functionality */
    {245U, 35U, 129U, 5U, 0U}, 
    /* Inout settings for pad PORT246 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_18_Y_INOUT inout functionality */
    {246U, 35U, 130U, 5U, 0U}, 
    /* Inout settings for pad PORT248 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_0_X_INOUT inout functionality */
    {248U, 35U, 48U, 5U, 0U}, 
    /* Inout settings for pad PORT249 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_1_G_INOUT inout functionality */
    {249U, 34U, 49U, 7U, 0U}, 
    /* Inout settings for pad PORT250 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_2_G_INOUT inout functionality */
    {250U, 34U, 50U, 7U, 0U}, 
    /* Inout settings for pad PORT251 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_3_G_INOUT inout functionality */
    {251U, 34U, 51U, 8U, 0U}, 
    /* Inout settings for pad PORT252 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_4_G_INOUT inout functionality */
    {252U, 34U, 52U, 5U, 0U}, 
    /* Inout settings for pad PORT253 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_5_G_INOUT inout functionality */
    {253U, 34U, 53U, 5U, 0U}, 
    /* Inout settings for pad PORT254 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_6_G_INOUT inout functionality */
    {254U, 34U, 54U, 6U, 0U}, 
    /* Inout settings for pad PORT255 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_7_G_INOUT inout functionality */
    {255U, 34U, 55U, 6U, 0U}, 
    /* Inout settings for pad PORT256 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D8_INOUT inout functionality */
    {256U, 34U, 160U, 7U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_0_X_INOUT inout functionality */
    {256U, 36U, 112U, 6U, 0U}, 
    /* Inout settings for pad PORT257 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D9_INOUT inout functionality */
    {257U, 34U, 161U, 6U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_1_H_INOUT inout functionality */
    {257U, 36U, 113U, 4U, 0U}, 
    /* Inout settings for pad PORT258 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D10_INOUT inout functionality */
    {258U, 34U, 162U, 6U, 0U}, 
    /* LPUART13_LPUART13_TX_INOUT inout functionality */
    {258U, 35U, 414U, 5U, 0U}, 
    /* Inout settings for pad PORT259 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D11_INOUT inout functionality */
    {259U, 34U, 163U, 8U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_3_H_INOUT inout functionality */
    {259U, 36U, 115U, 4U, 0U}, 
    /* Inout settings for pad PORT260 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D12_INOUT inout functionality */
    {260U, 34U, 164U, 6U, 0U}, 
    /* LPUART14_LPUART14_TX_INOUT inout functionality */
    {260U, 35U, 415U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_5_H_INOUT inout functionality */
    {260U, 36U, 117U, 4U, 0U}, 
    /* Inout settings for pad PORT261 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D13_INOUT inout functionality */
    {261U, 34U, 165U, 6U, 0U}, 
    /* Inout settings for pad PORT262 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D14_INOUT inout functionality */
    {262U, 34U, 166U, 6U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_7_H_INOUT inout functionality */
    {262U, 36U, 119U, 4U, 0U}, 
    /* Inout settings for pad PORT263 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D15_INOUT inout functionality */
    {263U, 34U, 167U, 7U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_8_X_INOUT inout functionality */
    {263U, 36U, 120U, 5U, 0U}, 
    /* Inout settings for pad PORT264 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_6_H_INOUT inout functionality */
    {264U, 36U, 118U, 4U, 0U}, 
    /* Inout settings for pad PORT266 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_4_H_INOUT inout functionality */
    {266U, 36U, 116U, 4U, 0U}, 
    /* Inout settings for pad PORT268 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_13_H_INOUT inout functionality */
    {268U, 34U, 61U, 6U, 0U}, 
    /* LPUART9_LPUART9_TX_INOUT inout functionality */
    {268U, 35U, 410U, 4U, 0U}, 
    /* Inout settings for pad PORT269 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_8_X_INOUT inout functionality */
    {269U, 34U, 56U, 5U, 0U}, 
    /* Inout settings for pad PORT270 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_9_H_INOUT inout functionality */
    {270U, 34U, 57U, 5U, 0U}, 
    /* Inout settings for pad PORT271 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_10_H_INOUT inout functionality */
    {271U, 34U, 58U, 6U, 0U}, 
    /* Inout settings for pad PORT272 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_11_H_INOUT inout functionality */
    {272U, 34U, 59U, 6U, 0U}, 
    /* LPSPI1_LPSPI1_PCS0_INOUT inout functionality */
    {272U, 36U, 232U, 6U, 0U}, 
    /* Inout settings for pad PORT273 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_12_H_INOUT inout functionality */
    {273U, 34U, 60U, 6U, 0U}, 
    /* Inout settings for pad PORT274 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_14_H_INOUT inout functionality */
    {274U, 34U, 62U, 6U, 0U}, 
    /* LPSPI1_LPSPI1_SOUT_INOUT inout functionality */
    {274U, 36U, 240U, 6U, 0U}, 
    /* Inout settings for pad PORT275 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_15_H_INOUT inout functionality */
    {275U, 34U, 63U, 6U, 0U}, 
    /* Inout settings for pad PORT276 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_16_X_INOUT inout functionality */
    {276U, 34U, 64U, 6U, 0U}, 
    /* LPSPI1_LPSPI1_SIN_INOUT inout functionality */
    {276U, 36U, 239U, 5U, 0U}, 
    /* Inout settings for pad PORT277 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_17_Y_INOUT inout functionality */
    {277U, 34U, 65U, 5U, 0U}, 
    /* Inout settings for pad PORT278 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_18_Y_INOUT inout functionality */
    {278U, 34U, 66U, 5U, 0U}, 
    /* Inout settings for pad PORT279 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_19_Y_INOUT inout functionality */
    {279U, 34U, 67U, 6U, 0U}, 
    /* LPSPI1_LPSPI1_SCK_INOUT inout functionality */
    {279U, 36U, 238U, 5U, 0U}, 
    /* Inout settings for pad PORT280 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_20_Y_INOUT inout functionality */
    {280U, 34U, 68U, 3U, 0U}, 
    /* Inout settings for pad PORT281 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_21_Y_INOUT inout functionality */
    {281U, 34U, 69U, 3U, 0U}, 
    /* LPUART9_LPUART9_TX_INOUT inout functionality */
    {281U, 35U, 410U, 5U, 0U}, 
    /* Inout settings for pad PORT282 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_22_X_INOUT inout functionality */
    {282U, 34U, 70U, 4U, 0U}, 
    /* Inout settings for pad PORT283 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_0_EMIOS_0_CH_23_X_INOUT inout functionality */
    {283U, 34U, 71U, 3U, 0U}, 
    /* Inout settings for pad PORT284 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_9_H_INOUT inout functionality */
    {284U, 35U, 121U, 5U, 0U}, 
    /* Inout settings for pad PORT285 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_10_H_INOUT inout functionality */
    {285U, 35U, 122U, 4U, 0U}, 
    /* Inout settings for pad PORT286 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_11_H_INOUT inout functionality */
    {286U, 35U, 123U, 4U, 0U}, 
    /* Inout settings for pad PORT287 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_12_H_INOUT inout functionality */
    {287U, 35U, 124U, 4U, 0U}, 
    /* Inout settings for pad PORT288 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D16_INOUT inout functionality */
    {288U, 34U, 168U, 6U, 0U}, 
    /* Inout settings for pad PORT289 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D17_INOUT inout functionality */
    {289U, 34U, 169U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_19_Y_INOUT inout functionality */
    {289U, 35U, 131U, 5U, 0U}, 
    /* Inout settings for pad PORT290 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D18_INOUT inout functionality */
    {290U, 34U, 170U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_20_Y_INOUT inout functionality */
    {290U, 35U, 132U, 5U, 0U}, 
    /* Inout settings for pad PORT291 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D19_INOUT inout functionality */
    {291U, 34U, 171U, 8U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_21_Y_INOUT inout functionality */
    {291U, 35U, 133U, 5U, 0U}, 
    /* Inout settings for pad PORT292 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D20_INOUT inout functionality */
    {292U, 34U, 172U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_22_X_INOUT inout functionality */
    {292U, 35U, 134U, 6U, 0U}, 
    /* LPUART13_LPUART13_TX_INOUT inout functionality */
    {292U, 36U, 414U, 6U, 0U}, 
    /* Inout settings for pad PORT293 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D21_INOUT inout functionality */
    {293U, 34U, 173U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_23_X_INOUT inout functionality */
    {293U, 35U, 135U, 6U, 0U}, 
    /* Inout settings for pad PORT294 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D22_INOUT inout functionality */
    {294U, 34U, 174U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_13_H_INOUT inout functionality */
    {294U, 35U, 125U, 4U, 0U}, 
    /* Inout settings for pad PORT295 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D23_INOUT inout functionality */
    {295U, 34U, 175U, 5U, 0U}, 
    /* EMIOS_2_EMIOS_2_CH_14_H_INOUT inout functionality */
    {295U, 35U, 126U, 4U, 0U}, 
    /* Inout settings for pad PORT296 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_15_H_INOUT inout functionality */
    {296U, 35U, 127U, 6U, 0U}, 
    /* Inout settings for pad PORT297 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_16_X_INOUT inout functionality */
    {297U, 35U, 128U, 5U, 0U}, 
    /* Inout settings for pad PORT298 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_2_EMIOS_2_CH_2_H_INOUT inout functionality */
    {298U, 36U, 114U, 4U, 0U}, 
    /* LPSPI3_LPSPI3_SCK_INOUT inout functionality */
    {298U, 37U, 252U, 5U, 0U}, 
    /* Inout settings for pad PORT300 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_0_X_INOUT inout functionality */
    {300U, 34U, 80U, 7U, 0U}, 
    /* FXIO_FXIO_D28_INOUT inout functionality */
    {300U, 36U, 180U, 4U, 0U}, 
    /* LPSPI3_LPSPI3_SIN_INOUT inout functionality */
    {300U, 37U, 253U, 5U, 0U}, 
    /* Inout settings for pad PORT301 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_1_H_INOUT inout functionality */
    {301U, 34U, 81U, 8U, 0U}, 
    /* FXIO_FXIO_D29_INOUT inout functionality */
    {301U, 36U, 181U, 4U, 0U}, 
    /* Inout settings for pad PORT302 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_2_H_INOUT inout functionality */
    {302U, 34U, 82U, 7U, 0U}, 
    /* FXIO_FXIO_D30_INOUT inout functionality */
    {302U, 36U, 182U, 4U, 0U}, 
    /* LPSPI3_LPSPI3_SOUT_INOUT inout functionality */
    {302U, 37U, 254U, 5U, 0U}, 
    /* Inout settings for pad PORT303 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_3_H_INOUT inout functionality */
    {303U, 34U, 83U, 8U, 0U}, 
    /* FXIO_FXIO_D31_INOUT inout functionality */
    {303U, 36U, 183U, 4U, 0U}, 
    /* Inout settings for pad PORT304 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_5_H_INOUT inout functionality */
    {304U, 34U, 85U, 9U, 0U}, 
    /* LPSPI3_LPSPI3_PCS0_INOUT inout functionality */
    {304U, 36U, 248U, 5U, 0U}, 
    /* Inout settings for pad PORT305 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_6_H_INOUT inout functionality */
    {305U, 34U, 86U, 7U, 0U}, 
    /* Inout settings for pad PORT306 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_7_H_INOUT inout functionality */
    {306U, 34U, 87U, 8U, 0U}, 
    /* Inout settings for pad PORT307 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_8_X_INOUT inout functionality */
    {307U, 34U, 88U, 5U, 0U}, 
    /* Inout settings for pad PORT308 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_9_H_INOUT inout functionality */
    {308U, 34U, 89U, 6U, 0U}, 
    /* Inout settings for pad PORT309 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_10_H_INOUT inout functionality */
    {309U, 34U, 90U, 7U, 0U}, 
    /* Inout settings for pad PORT310 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_11_H_INOUT inout functionality */
    {310U, 34U, 91U, 6U, 0U}, 
    /* Inout settings for pad PORT311 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_12_H_INOUT inout functionality */
    {311U, 34U, 92U, 7U, 0U}, 
    /* LPSPI4_LPSPI4_SIN_INOUT inout functionality */
    {311U, 36U, 260U, 4U, 0U}, 
    /* Inout settings for pad PORT312 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_13_H_INOUT inout functionality */
    {312U, 34U, 93U, 6U, 0U}, 
    /* Inout settings for pad PORT313 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_4_H_INOUT inout functionality */
    {313U, 34U, 84U, 9U, 0U}, 
    /* Inout settings for pad PORT314 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_14_H_INOUT inout functionality */
    {314U, 34U, 94U, 7U, 0U}, 
    /* LPSPI4_LPSPI4_SOUT_INOUT inout functionality */
    {314U, 37U, 261U, 4U, 0U}, 
    /* Inout settings for pad PORT315 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_15_H_INOUT inout functionality */
    {315U, 34U, 95U, 8U, 0U}, 
    /* Inout settings for pad PORT316 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_16_X_INOUT inout functionality */
    {316U, 35U, 96U, 6U, 0U}, 
    /* Inout settings for pad PORT317 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_17_Y_INOUT inout functionality */
    {317U, 35U, 97U, 5U, 0U}, 
    /* LPSPI4_LPSPI4_SCK_INOUT inout functionality */
    {317U, 37U, 259U, 4U, 0U}, 
    /* Inout settings for pad PORT318 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_18_Y_INOUT inout functionality */
    {318U, 35U, 98U, 5U, 0U}, 
    /* Inout settings for pad PORT319 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* EMIOS_1_EMIOS_1_CH_19_Y_INOUT inout functionality */
    {319U, 35U, 99U, 5U, 0U}, 
    /* Inout settings for pad PORT320 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D24_INOUT inout functionality */
    {320U, 34U, 176U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_20_Y_INOUT inout functionality */
    {320U, 35U, 100U, 5U, 0U}, 
    /* LPSPI4_LPSPI4_PCS0_INOUT inout functionality */
    {320U, 37U, 255U, 5U, 0U}, 
    /* Inout settings for pad PORT321 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D25_INOUT inout functionality */
    {321U, 34U, 177U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_21_Y_INOUT inout functionality */
    {321U, 35U, 101U, 5U, 0U}, 
    /* Inout settings for pad PORT322 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D26_INOUT inout functionality */
    {322U, 34U, 178U, 5U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_22_X_INOUT inout functionality */
    {322U, 35U, 102U, 5U, 0U}, 
    /* LPUART15_LPUART15_TX_INOUT inout functionality */
    {322U, 36U, 416U, 5U, 0U}, 
    /* Inout settings for pad PORT323 : {Mscr Id, AltFunc, Imcr Id, Imcr value, Imcr Siul Instance} */
    /* FXIO_FXIO_D27_INOUT inout functionality */
    {323U, 34U, 179U, 4U, 0U}, 
    /* EMIOS_1_EMIOS_1_CH_23_X_INOUT inout functionality */
    {323U, 35U, 103U, 5U, 0U}
};

#define PORT_STOP_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

#endif /* (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/
#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)

#define PORT_START_SEC_CONST_16
#include "Port_MemMap.h"

/**
* @brief Array of values storing the length of tables with INOUT functionality information on each of the SIUL2 instance on the platform
*/
const uint16 Port_au16NumInoutMuxSettings[PORT_NUM_SIUL2_INSTANCES_U8] =
{
    PORT_SIUL2_0_INOUT_TABLE_NUM_ENTRIES_U16
};

#define PORT_STOP_SEC_CONST_16
#include "Port_MemMap.h"

#define PORT_START_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

/**
* @brief Array of pointers to the tables storing information about pin availability on each of the SIUL2 instance on the platform
*/
const Port_PinModeAvailabilityArrayType * const Port_apSiul2InstancePinModeAvailability[PORT_NUM_SIUL2_INSTANCES_U8] =
{
    &Port_SIUL2_0_au16PinModeAvailability
};

/**
* @brief Array of pointers to the tables storing information about IN functionality on each of the SIUL2 instance on the platform
*/
const Port_InMuxSettingType * const Port_apInMuxSettings[PORT_NUM_SIUL2_INSTANCES_U8] =
{
    Port_SIUL2_0_aInMuxSettings
};

#define PORT_STOP_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

#define PORT_START_SEC_CONST_16
#include "Port_MemMap.h"

/**
* @brief Array of pointers to the tables storing information about indexes in the IN functionality tables on each of the SIUL2 instance on the platform
*/
const uint16 *const Port_apInMuxSettingsIndex[PORT_NUM_SIUL2_INSTANCES_U8] =
{
    Port_SIUL2_0_au16InMuxSettingsIndex
};

#define PORT_STOP_SEC_CONST_16
#include "Port_MemMap.h"

#define PORT_START_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

/**
* @brief Array of pointers to the tables storing information about INOUT functionality on each of the SIUL2 instance on the platform
*/
const Port_InoutSettingType * const Port_apInoutMuxSettings[PORT_NUM_SIUL2_INSTANCES_U8] =
{
    Port_SIUL2_0_aInoutMuxSettings
};

#define PORT_STOP_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

#endif /* (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/


/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

/* End of File */
