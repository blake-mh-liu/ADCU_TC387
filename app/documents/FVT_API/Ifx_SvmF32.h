/**
 * \file Ifx_SvmF32.h
 * \brief Space vector PWM.
 * \ingroup library_sysse_hwindependant_emotor_svm
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
 */
/** \defgroup library_sysse_hwindependant_emotor_svm Space Vector Modulation
 * \ingroup library_sysse_hwindependant_emotor
 * The B6 inverter model consists of two sets of three active switches
 * (IGBT or MOSFET). One set of three switches (\f$T_u\f$, \f$T_v\f$, \f$T_w\f$)
 * is placed as high-side switches and the other set
 * (\f$T_u^*\f$, \f$T_v^*\f$, \f$T_w^*\f$) is placed as low-side switches.
 * In order to generate sine wave at any phase leg, for example the U-phase,
 * the corresponding high- and low-side switches (\f$T_u\f$ and \f$T_u^*\f$) are
 * switched rapidly by means of pulses with varying duty cycles over small periods.
 *
 * \fig{5,B6 inverter model showing [Tu Tv Tw] state = [1 0 0], library_sysse_hwindependant_emotor_svm_f5,SrvSw.SysSe.EMotor.Svm[Inverter].svg}
 *
 * \section vectors Active and Null Vectors
 * Space Vector Modulation uses the vector representation of the individual leg.
 * Because the low-side switches are complementary to the high-side ones, only
 * high-side states are considered.
 *
 * A shown in \figlink{5, library_sysse_hwindependant_emotor_svm_f5}, if the
 * \f$[T_u, T_v, T_w]\f$ state is \f$[100] = [on,off,off]\f$, the state of
 * \f$[T_u^*, T_v^*, T_w^*]\f$ is \f$[off,on,on]\f$, the voltages at the
 * inverter output legs are \f$V_u=\frac{1}{2}.V_{dc}\f$, \f$V_v=-\frac{1}{2}.V_{dc}\f$ and  \f$V_w=-\frac{1}{2}.V_{dc}\f$.
 * By taking the \ref library_sysse_hwindependant_emotor_clarke "complex Clarke transformation" as in
 * \eqlink{3,library_sysse_hwindependant_emotor_clarke_eq3} to the U, V and W voltages, we obtain
 *  the voltage vector: \f$\overrightarrow{V_{[100]}}=\frac{2}{3}.V_{dc}.e^{j0}\f$.
 * In total there are eight states. Six of them are active vectors which
 * generates real voltage. The remaining two states, state \f$[000]\f$ and
 * \f$[111]\f$, are "null" voltage because no voltage is generated. The six
 * active vectors are shown in \figlink{6,library_sysse_hwindependant_emotor_svm_f6}.
 * We can assign index k = 1..6 to those active vectors and write them as:
 *
 * \f$V_k=\frac{2}{3}.V_{dc}.e^{(j.(k-1).\frac{\pi}{3})}\f$ \eq{7,library_sysse_hwindependant_emotor_park_eq7}
 *
 * In addition the sector numbers 1 until 6 are marking the areas which lie
 * between two active vectors.
 *
 * \fig{6,Active voltage vectors,library_sysse_hwindependant_emotor_svm_f6,SrvSw.SysSe.EMotor.Svm[Sectors-2].png}
 *
 * \section generation Arbitrary Vector Generation
 * Arbitrary vector voltage \f$\overrightarrow{V_R}\f$ can be constructed from two
 * vectors \f$\overrightarrow{V_k}\f$ and \f$\overrightarrow{V_{k+1}}\f$ by:
 * - Using PWM with switching period \f$T_s\f$
 * - Allocating time \f$T_k,  T_{k+1}\f$ for vector \f$\overrightarrow{V_k}, \overrightarrow{V_{k+1}}\f$
 * - Remaining time for null vector \f$\overrightarrow{V_0}\f$ and \f$\overrightarrow{V_7}\f$.
 *
 * Thus, the average of \f$\overrightarrow{V_R}\f$ over half of the switching period
 * is described by \eqlink{8,library_sysse_hwindependant_emotor_park_eq8}:
 *
 * \f$\int_{0}^{\frac{1}{2}T_s}\overrightarrow{V_R}\mathrm{d}t = \int_{0}^{\frac{1}{2}T_0}\overrightarrow{V_0}\mathrm{d}t + \int_{\frac{1}{2}T_0}^{\frac{1}{2}T_0+T_k}\overrightarrow{V_k}\mathrm{d}t + \int_{\frac{1}{2}T_0+T_k}^{\frac{1}{2}T_0+T_k+T_{k+1}}\overrightarrow{V_{k+1}}\mathrm{d}t  + \int_{\frac{1}{2}T_0+T_k+T_{k+1}}^{\frac{1}{2}T_s}\overrightarrow{V_7}\mathrm{d}t\f$   \eq{8,library_sysse_hwindependant_emotor_park_eq8}
 *
 * By definition:
 * \f$T_0+T_k+T_{k+1}=\frac{1}{2}.T_s\f$    \eq{9,library_sysse_hwindependant_emotor_park_eq9}
 *
 *
 * \todo Add figure 7
 *
 * \fig{7,Arbitrary vector VR generation,library_sysse_hwindependant_emotor_svm_f7,notFound.png}
 *
 * Because the \f$\overrightarrow{V_0}\f$ and \f$\overrightarrow{V_7}\f$ are null vectors,
 * and assumed that the average value of \f$\overrightarrow{V_R}\f$ is the same as
 * \f$\overrightarrow{V_R}\f$ itself, then:
 *
 * \f$\frac{1}{2}.T_s.\overrightarrow{V_R}=T_k.\overrightarrow{V_k}+T_{k+1}.\overrightarrow{V_{k+1}}\f$ \eq{10,library_sysse_hwindependant_emotor_park_eq10}
 *
 *
 * \eqlink{10,library_sysse_hwindependant_emotor_park_eq10} can be expanded with the complex
 * form of \f$\overrightarrow{V_k}\f$ and \f$\overrightarrow{V_{k+1}}\f$:
 *
 * \f$\frac{1}{2}.T_s.\overrightarrow{V_R}=\frac{2}{3}.V_{dc}.(T_k.e^{j.(k-1).\frac{\pi}{3}}+T_{k+1}.e^{j.k.\frac{\pi}{3}})\f$  \eq{11,library_sysse_hwindependant_emotor_park_eq11}
 *
 * or in vector form:
 *
 * \f$\frac{1}{2}.T_s.\begin{bmatrix}V_\alpha\\V_\beta\end{bmatrix}=\frac{2}{3}.V_{dc}.\begin{bmatrix}cos((k-1).\frac{\pi}{3})&cos(k.\frac{\pi}{3})\\sin((k-1).\frac{\pi}{3})&sin(k.\frac{\pi}{3})\end{bmatrix}\begin{bmatrix}T_k\\T_{k+1}\end{bmatrix}\f$  \eq{12,library_sysse_hwindependant_emotor_park_eq12}
 *
 *
 * Finally, the vector time \f$T_k, T_{k+1}\f$ can be solved as:
 *
 * \f$\begin{bmatrix}T_k\\T_{k+1}\end{bmatrix}=\frac{\sqrt{3}}{2}.\frac{T_s}{V_{dc}}.\begin{bmatrix}sin(k.\frac{\pi}{3})&-cos(k.\frac{\pi}{3})\\-sin((k-1).\frac{\pi}{3})&cos((k-1)\frac{\pi}{3}\end{bmatrix}\begin{bmatrix}V_\alpha\\V_\beta\end{bmatrix}\f$   \eq{13,library_sysse_hwindependant_emotor_park_eq13}
 *
 * \section modulation Modulation index
 * Modulation index vector in this SVM scheme is defined as:
 *
 * \f$\overrightarrow{m}=\frac{\pi}{2}.\frac{\overrightarrow{V_R}}{V_{dc}}=\begin{bmatrix}m_\alpha\\m_\beta\end{bmatrix}\f$ \eq{14,library_sysse_hwindependant_emotor_park_eq14}
 *
 * Therefore, using modulation index notation \eqlink{13,library_sysse_hwindependant_emotor_park_eq13}
 * can be written as:
 *
 * \f$\begin{bmatrix}T_k\\T_{k+1}\end{bmatrix}=\frac{\sqrt{3}}{\pi}.T_s. \begin{bmatrix}sin(k.\frac{\pi}{3})&-cos(k.\frac{\pi}{3})\\-sin((k-1).\frac{\pi}{3})&cos((k-1).\frac{\pi}{3})\end{bmatrix}\begin{bmatrix}m_\alpha\\m_\beta\end{bmatrix}\f$  \eq{15,library_sysse_hwindependant_emotor_park_eq15}
 *
 * \section continuous Continuous Operation
 * For the continuous operation of sine wave generation where amplitude of the
 * generated sine wave can be made constant over time, the vector voltage
 * \f$\overrightarrow{V_R}=\overrightarrow{V_\alpha\beta}\f$ must lie within the circle
 * inside the hexagon as shown in
 * \figlink{8,library_sysse_hwindependant_emotor_svm_f8}, which means:
 *
 * \f$\begin{vmatrix}\overrightarrow{V_R}\end{vmatrix}=\frac{\sqrt{3}}{2}.\begin{vmatrix}\overrightarrow{V_k}\end{vmatrix}\f$   \eq{16,library_sysse_hwindependant_emotor_park_eq16}
 *
 * Substituting \f$\overrightarrow{V_k}\f$ with \eqlink{6,library_sysse_hwindependant_emotor_park_eq6},
 * we obtain:
 *
 * \f$\begin{vmatrix}\overrightarrow{V_R}\end{vmatrix}=\frac{V_{dc}}{\sqrt{3}}\f$   \eq{17,library_sysse_hwindependant_emotor_park_eq17}
 *
 * Combining with \eqlink{14,library_sysse_hwindependant_emotor_park_eq14}, we also obtain:
 *
 * \f$\begin{vmatrix}\overrightarrow{m}\end{vmatrix}=\frac{\pi}{2.\sqrt{3}}\f$  \eq{18,library_sysse_hwindependant_emotor_park_eq18}
 *
 *
 * \fig{8,Diagram for Space Vector Modulation,library_sysse_hwindependant_emotor_svm_f8,SrvSw.SysSe.EMotor.Svm[Sectors-1].png}
 *
 * As an example, a vector \f$\overrightarrow{V_R}\f$ which lies in sector 1 is
 * constructed by vector \f$\overrightarrow{V_1}\f$ and \f$\overrightarrow{V_2}\f$. The
 * timing diagram is shown in \figlink{9,library_sysse_hwindependant_emotor_svm_f9}.
 *
 * \fig{9,Timing diagram for voltage vector in sector 1,library_sysse_hwindependant_emotor_svm_f9,SrvSw.SysSe.EMotor.Svm[Pwm].svg}
 *
 * We can calculate the ON time of PWM signals for the phase U, V, and W,
 * denoted \f$T_u\f$, \f$T_v\f$, and \f$T_w\f$. respectively. For
 * voltage vector in sector 1:
 *
 * \f$\begin{bmatrix}T_u\\T_v\\T_w\end{bmatrix}=\begin{bmatrix}2.(T_k+T_{k+1})+T_0\\2.T_{k+1}+T_0\\T_0\end{bmatrix}\f$  \eq{19,library_sysse_hwindependant_emotor_park_eq19}
 *
 * With similar way, we can calculate the ON time of the PWM signals
 * for other sectors.
 *
 * \section Phase potentials
 * The space vector algorithm produces the following phase potentials:
 *
 *
 * \f$
 * \begin{array}{lcl}
 * V_u(\omega.t) & = &
 * \begin{cases}
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_R} \right | \cos(\omega.t-\frac{\pi}{3})
 * , & \mbox{if } 0 \le \omega.t \ll \frac{\pi}{3} \\
 *
 * \frac{3}{2} \left | \overrightarrow{V_R} \right | \cos(\omega.t)
 * , & \mbox{if } \frac{\pi}{3} \ll \omega.t \le \frac{2.\pi}{3} \\
 *
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_R} \right | \cos(\omega.t+\frac{\pi}{3})
 * , & \mbox{if } \frac{2.\pi}{3} \ll \omega.t \le \pi \\
 *
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_R} \right | \cos(\omega.t-\frac{\pi}{3})
 * , & \mbox{if } \pi \le \omega.t \ll \frac{4.\pi}{3} \\
 *
 * \frac{3}{2} \left | \overrightarrow{V_R} \right | \cos(\omega.t)
 * , & \mbox{if } \frac{4.\pi}{3} \ll \omega.t \le \frac{5.\pi}{3} \\
 *
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_R} \right | \cos(\omega.t+\frac{\pi}{3})
 * , & \mbox{if } \frac{5.\pi}{3} \ll \omega.t \le 2.\pi
 *
 * \end{cases}
 * \\
 * V_v(\omega.t) & = & V_u(\omega.t - \frac{2.\pi}{3}) \\
 * V_w(\omega.t) & = & V_u(\omega.t + \frac{2.\pi}{3})
 *
 * \end{array}
 *
 * \f$
 *
 * And the following line to line voltages:
 *
 * \f$
 * \begin{array}{lcl}
 * V_{uv}(\omega.t) & = & \sqrt{3} \left | \overrightarrow{V_R} \sin(\omega.t+\frac{\pi}{3}) \right | \\
 * V_{vw}(\omega.t) & = & V_{uv}(\omega.t - \frac{2.\pi}{3}) \\
 * V_{wa}(\omega.t) & = & V_{uv}(\omega.t + \frac{2.\pi}{3})
 *
 * \end{array}
 *
 * \f$
 *
 */

#if !defined(IFX_SVMF32_H)
#define IFX_SVMF32_H
//------------------------------------------------------------------------------
#include "SysSe/Math/IFX_Cf32.h"
//------------------------------------------------------------------------------
#define IFX_SVMF32_MAX_AMPLITUDE (IFX_ONE_OVER_SQRT_THREE / IFX_TWO_OVER_PI)
//------------------------------------------------------------------------------
/** \addtogroup library_sysse_hwindependant_emotor_svm
 * \{ */
IFX_EXTERN void     Ifx_SvmF32_init(void);
IFX_EXTERN void     Ifx_SvmF32_do(cfloat32 m, Ifx_TimerValue period, Ifx_TimerValue* timerValues);
IFX_EXTERN float32  Ifx_SvmF32_getVoltage(float32 m, float32 vdc);
IFX_EXTERN cfloat32 Ifx_SvmF32_getVoltages(cfloat32 m, float32 vdc);
IFX_EXTERN cfloat32 Ifx_SvmF32_getModIndex(cfloat32 v, float32 vdc);

IFX_EXTERN cfloat32 Ifx_SvmF32_revertToVoltages(const Ifx_TimerValue* timerValues, float32 vdc, Ifx_TimerValue period);
/** \} */
//------------------------------------------------------------------------------

IFX_INLINE float32 getModIndex(float32 voltage, float32 vdc)
{
    float32 factor = __maxf(vdc, 1e-7) * IFX_TWO_OVER_PI;
    return voltage / factor;
}


#endif
