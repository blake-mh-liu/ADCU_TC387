#ifndef CPL_ARLECOMMON_H
#define CPL_ARLECOMMON_H

/* --------{ EB Automotive C Source File }-------- */

/*==================[macros]================================================*/

/* Control Byte Elements */
/** \brief Bit mask to find the repetition counter within the control byte
 **/
#define  CPL_ARLE_CNTR       0x3FU    /*    63U */
/** \brief Bit mask to find the pattern type within the control byte
 **/
#define  CPL_ARLE_TYPE       0xC0U    /*   192U */

/* Pattern Types */
/** \brief Type that identifies an uncompressed section
 **/
#define  CPL_ARLE_TYPE_UNCOMP   0x00U    /*     0U */
/** \brief Type that identifies a 'byte' repetition pattern
 **/
#define  CPL_ARLE_TYPE_BYTE     0x40U    /*    64U */
/** \brief Type that identifies a 'word' repetition pattern
 **/
#define  CPL_ARLE_TYPE_WORD     0x80U    /*   128U */
/** \brief Type that identifies a 'long' repetition pattern
 **/
#define  CPL_ARLE_TYPE_LONG     0xC0U    /*   192U */
/** \brief Type that is used as initial value - not used by ARLE
 **/
#define  CPL_ARLE_TYPE_NONE     0xFFU    /*   255U */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /* CPL_ARLECOMMON_H */
