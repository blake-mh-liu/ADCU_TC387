/**
 * \file Ifx_ClarkeF32.c
 * \brief Clarke transformation.
 *
 *
 * \version disabled
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

//------------------------------------------------------------------------------
#include "Ifx_ClarkeF32.h"
//------------------------------------------------------------------------------
/** \brief Clarke transformation.
 *
 * This function converts the current from the three phases system \f$ (a, b, c) \f$ to the two phases system \f$ (\alpha, \beta) \f$.
 * \image html "SrvSw.SysSe.EMotor.Clarke[Transforms].png"
 *
 * \param Currents Specifies the stator currents in the three phases system (U, V, W).
 *
 * \return Returns the stator current in two phases system :
 * \f$
 *  \begin{bmatrix}
 *  i_{s\alpha} \\
 *  i_{s\beta}
 *  \end{bmatrix}
 *  =
 *  \begin{bmatrix}
 *  i_a \\
 *  \frac{1}{\sqrt{3}}*(i_b-i_c)
 *  \end{bmatrix}
 * \f$.
 * \ingroup library_sysse_hwindependant_emotor_clarke
 */
cfloat32 Ifx_ClarkeF32(const float32* Currents)
{
    cfloat32 Result;
    Result.real = Currents[0];
    Result.imag = IFX_ONE_OVER_SQRT_THREE * (Currents[1] - Currents[2]);
    return Result;
}
