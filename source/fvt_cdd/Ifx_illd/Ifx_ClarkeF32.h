/**
 * \file Ifx_ClarkeF32.h
 * \brief Clarke transformation.
 * \ingroup library_sysse_hwindependant_emotor_clarke
 *
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
 * \defgroup library_sysse_hwindependant_emotor_clarke Clarke Transformation
 * \ingroup library_sysse_hwindependant_emotor
 *
 * The Clarke transformation converts the signals in the three-phase domain
 * into two-phase domain. In matrix form, this transformation is written as:
 *
 * \f$\begin{bmatrix}x_\alpha \\ x_\beta\end{bmatrix}=\frac{2}{3}.\begin{bmatrix}1&-\frac{1}{2}&-\frac{1}{2} \\ 0&\frac{\sqrt{3}}{2}&-\frac{\sqrt{3}}{2}\end{bmatrix}\begin{bmatrix}x_u \\ x_v \\ x_w\end{bmatrix}\f$	\eq{1,library_sysse_hwindependant_emotor_clarke_eq1}
 *
 * The inverse of the transformation is written as:
 *
 * \f$\begin{bmatrix}x_u \\ x_v \\ x_w\end{bmatrix}=\begin{bmatrix}1&0 \\ -\frac{1}{2}&\sqrt{\frac{3}{2}} \\ -\frac{1}{2}&-\sqrt{\frac{3}{2}}\end{bmatrix}\begin{bmatrix}x_\alpha \\ x_\beta\end{bmatrix}\f$	\eq{2,library_sysse_hwindependant_emotor_clarke_eq2}
 *
 * In complex variables, the forward transformation is written as:
 *
 * \f$\overrightarrow{x_{\alpha\beta}}=x_\alpha+j.x_\beta=\frac{2}{3}.(x_u.\overrightarrow{a}^0+x_v.\overrightarrow{a}^1+x_w\overrightarrow{a}^2 )\f$,        \f$\overrightarrow{a}=e^{j.\frac{2\pi}{3}}\f$	\eq{3,library_sysse_hwindependant_emotor_clarke_eq3}
 *
 *
 * If the x variable is phase currents with star-connection, then Kirchoff's
 * law applies, i.e. \f$i_u+i_v+i_w=0\f$. In this case, \eqlink{2,library_sysse_hwindependant_emotor_clarke_eq2} can be simplified as:
 *
 * \f$i_\alpha=i_u\f$
 *
 * \f$i_\beta=\frac{i_w-i_v}{\sqrt{3}}=\frac{i_u+2.i_v}{\sqrt{3}}\f$	\eq{4,library_sysse_hwindependant_emotor_clarke_eq4}
 *
 * \image html "SrvSw.SysSe.EMotor.Clarke[Transforms].png" "Clarke transform"
 *
 *
 */

#if !defined(IFX_CLARKEF32_H)
#define IFX_CLARKEF32_H
//------------------------------------------------------------------------------
#include "IFX_Cf32.h"
//------------------------------------------------------------------------------

cfloat32 Ifx_ClarkeF32(const float32* Currents);
#endif
