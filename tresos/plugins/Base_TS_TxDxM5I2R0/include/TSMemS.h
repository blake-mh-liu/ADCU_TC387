#ifndef TS_MEMS_H
#define TS_MEMS_H

/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \version 5.2.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <Std_Types.h>

/*==================[macros]=================================================*/

/* !LINKSTO Base.Properties.OverrideMemSetS,1 */
/* prevent double definition of macro for memory set function only if not overridden */
#if ((defined TS_MemSetS) && (TS_MEMSETS_CUSTOM_OVERRIDE == STD_OFF))
#error TS_MemSetS is already defined
/* check for definition of macro for memory set function only if overridden */
#elif ((!defined TS_MemSetS) && (TS_MEMSETS_CUSTOM_OVERRIDE == STD_ON))
#error Configuration parameter CustomOverride_MemSetS is set but macro TS_MemSetS is not defined
#endif

/* !LINKSTO Base.Properties.OverrideMemCmpS,1 */
/* prevent double definition of macro for memory compare function only if not overridden */
#if ((defined TS_MemCmpS) && (TS_MEMCMPS_CUSTOM_OVERRIDE == STD_OFF))
#error TS_MemCmpS is already defined
/* check for definition of macro for memory compare function only if overridden */
#elif ((!defined TS_MemCmpS) && (TS_MEMCMPS_CUSTOM_OVERRIDE == STD_ON))
#error Configuration parameter CustomOverride_MemCmpS is set but macro TS_MemCmpS is not defined
#endif

/* !LINKSTO Base.Properties.OverrideMemBZeroS,1 */
/* prevent double definition of macro for memory zeroing function only if not overridden */
#if ((defined TS_MemBZeroS) && (TS_MEMBZEROS_CUSTOM_OVERRIDE == STD_OFF))
#error TS_MemBZeroS is already defined
/* check for definition of macro for memory zeroing function only if overridden */
#elif ((!defined TS_MemBZeroS) && (TS_MEMBZEROS_CUSTOM_OVERRIDE == STD_ON))
#error Configuration parameter CustomOverride_MemBZeroS is set but macro TS_MemBZeroS is not defined
#endif

#if (TS_MEMSETS_CUSTOM_OVERRIDE == STD_OFF)
#if (CPU_TYPE == CPU_TYPE_64)

/** \brief This macro maps to the CPU specific macro for setting memory bytes, for 64bit CPU to TS_MemSetS64() */
#define TS_MemSetS(dst,val,len) (TS_MemSetS64((dst),(val),(len)))

#elif (CPU_TYPE == CPU_TYPE_32)

/** \brief This macro maps to the CPU specific macro for setting memory bytes, for 32bit CPU to TS_MemSetS32() */
#define TS_MemSetS(dst,val,len) (TS_MemSetS32((dst),(val),(len)))

#elif (CPU_TYPE == CPU_TYPE_16)

/** \brief This macro maps to the CPU specific macro for setting memory bytes, for 16bit CPU to TS_MemSetS16() */
#define TS_MemSetS(dst,val,len) (TS_MemSetS16((dst),(val),(len)))

#elif (CPU_TYPE == CPU_TYPE_8)

/** \brief This macro maps to the CPU specific macro for setting memory bytes, for 8bit CPU to TS_MemSetS8() */
#define TS_MemSetS(dst,val,len) (TS_MemSetS8((dst),(val),(len)))

#endif /* CPU_TYPE */
#endif /* TS_MEMSETS_CUSTOM_OVERRIDE == STD_OFF */

#if (TS_MEMCMPS_CUSTOM_OVERRIDE == STD_OFF)
#if (CPU_TYPE == CPU_TYPE_64)

/** \brief This macro maps to the CPU specific macro for comparing memory bytes, for 64bit CPU to TS_MemCmpS64() */
#define TS_MemCmpS(a,b,n) (TS_MemCmpS64((a),(b),(n)))

#elif (CPU_TYPE == CPU_TYPE_32)

/** \brief This macro maps to the CPU specific macro for comparing memory bytes, for 32bit CPU to TS_MemCmpS32() */
#define TS_MemCmpS(a,b,n) (TS_MemCmpS32((a),(b),(n)))

#elif (CPU_TYPE == CPU_TYPE_16)

/** \brief This macro maps to the CPU specific macro for comparing memory bytes, for 16bit CPU to TS_MemCmpS16() */
#define TS_MemCmpS(a,b,n) (TS_MemCmpS16((a),(b),(n)))

#elif (CPU_TYPE == CPU_TYPE_8)

/** \brief This macro maps to the CPU specific macro for comparing memory bytes, for 8bit CPU to TS_MemCmpS8() */
#define TS_MemCmpS(a,b,n) (TS_MemCmpS8((a),(b),(n)))

#endif /* CPU_TYPE */
#endif /* TS_MEMCMPS_CUSTOM_OVERRIDE == STD_OFF */

#if (TS_MEMBZEROS_CUSTOM_OVERRIDE == STD_OFF)
#if (CPU_TYPE == CPU_TYPE_64)

/** \brief This macro maps to the CPU specific macro for filling memory bytes with zero, for 64bit CPU to TS_MemBZeroS64() */
#define TS_MemBZeroS(dst, len) (TS_MemBZeroS64((dst), (len)))

#elif (CPU_TYPE == CPU_TYPE_32)

/** \brief This macro maps to the CPU specific macro for filling memory bytes with zero, for 32bit CPU to TS_MemBZeroS32() */
#define TS_MemBZeroS(dst, len) (TS_MemBZeroS32((dst), (len)))

#elif (CPU_TYPE == CPU_TYPE_16)

/** \brief This macro maps to the CPU specific macro for filling memory bytes with zero, for 16bit CPU to TS_MemBZeroS16() */
#define TS_MemBZeroS(dst, len) (TS_MemBZeroS16((dst), (len)))

#elif (CPU_TYPE == CPU_TYPE_8)

/** \brief This macro maps to the CPU specific macro for filling memory bytes with zero, for 8bit CPU to TS_MemBZeroS8() */
#define TS_MemBZeroS(dst, len) (TS_MemBZeroS8((dst), (len)))

#endif /* CPU_TYPE */
#endif /* TS_MEMBZEROS_CUSTOM_OVERRIDE == STD_OFF */

/*==================[external function definitions]==========================*/

#define BASE_START_SEC_CODE
#include <Base_MemMap.h>

#if (CPU_TYPE == CPU_TYPE_64)

/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         (64-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS64
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         (64-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS64
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         (64-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address
 * \pre The pointer \p b points to a valid address
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS64
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);

#elif (CPU_TYPE == CPU_TYPE_32)

/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         (32-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS32
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         (32-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS32
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         (32-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address
 * \pre The pointer \p b points to a valid address
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS32
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);

#elif (CPU_TYPE == CPU_TYPE_16)

/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         (16-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS16
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         (16-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS16
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         (16-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address
 * \pre The pointer \p b points to a valid address
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS16
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);

#elif (CPU_TYPE == CPU_TYPE_8)

/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         (8-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS8
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         (8-bit version)
 *
 * \pre The pointer \p dst points to a valid address
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS8
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         (8-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address
 * \pre The pointer \p b points to a valid address
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS8
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);

#endif /* CPU_TYPE */

#if (defined HAS_64BIT_TYPES)
/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         without alignment checks (64-bit version)
 *
 * \pre The pointer \p dst points to a valid address and is 64-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS64_NoCheck
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         without alignment checks (64-bit version)
 *
 * \pre The pointer \p dst points to a valid address and is 64-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS64_NoCheck
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         without alignment checks (64-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address and is 64-bit aligned
 * \pre The pointer \p b points to a valid address and is 64-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS64_NoCheck
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);
#endif /* if (defined HAS_64BIT_TYPES) */

/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         without alignment checks (32-bit version)
 *
 * \pre The pointer \p dst points to a valid address and is 32-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS32_NoCheck
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         (32-bit version)
 *
 * \pre The pointer \p dst points to a valid address and is 32-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS32_NoCheck
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         without alignment checks (32-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address and is 32-bit aligned
 * \pre The pointer \p b points to a valid address and is 32-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS32_NoCheck
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);

/** \brief Assigns \p len copies of value \p val to destination \p dst
 *         without alignment checks (16-bit version)
 *
 * \pre The pointer \p dst points to a valid address and is 16-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] dst Pointer to assign the value to
 * \param[in] val Value to be assigned
 * \param[in] len Amount of copies to assign
 */
extern FUNC(void, BASE_CODE) TS_MemSetS16_NoCheck
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const uint8 val,
  const usize len
);

/** \brief Fills \p len bytes with zero at destination \p dst
 *         without alignment checks (16-bit version)
 *
 * \pre The pointer \p dst points to a valid address and is 16-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] dst Pointer to the destination to fill
 * \param[in] len Amount of bytes to fill
 */
extern FUNC(void, BASE_CODE) TS_MemBZeroS16_NoCheck
(
  CONSTP2VAR(void, AUTOMATIC, BASE_APPL_DATA) dst,
  const usize len
);

/** \brief Compares \p n bytes of memory at locations \p a and \p b
 *         without alignment checks (16-bit version)
 *
 * This function compares a memory block of length \p len located
 * at address \p a to a memory block located at address \p b.
 *
 * \pre The pointer \p a points to a valid address and is 16-bit aligned
 * \pre The pointer \p b points to a valid address and is 16-bit aligned
 *
 * \note The function does not perform alignment checks
 *
 * \param[in] a Pointer to the first memory block to compare
 * \param[in] b Pointer to the second memory block to compare
 * \param[in] len Amount of bytes to compare
 *
 * \return Comparison status
 * \retval E_OK Both memory blocks compare equal
 * \retval E_NOT_OK The memory blocks are not equal
 */
extern FUNC(Std_ReturnType, BASE_CODE) TS_MemCmpS16_NoCheck
(
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) a,
  CONSTP2CONST(void, AUTOMATIC, BASE_APPL_DATA) b,
  const usize len
);

#define BASE_STOP_SEC_CODE
#include <Base_MemMap.h>

/*==================[internal function definitions]==========================*/

#endif /* ifndef TS_MEMS_H */
/*==================[end of file]============================================*/
