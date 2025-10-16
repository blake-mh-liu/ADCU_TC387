/**
 * \file Ifx_SvmF32.c
 * \brief Space vector PWM.
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
#include <math.h>
#include "Ifx_SvmF32.h"
#include "Ifx_ClarkeF32.h"
//------------------------------------------------------------------------------

/** \brief Look up table for Sqrt(3)/pi*SIN((k-1)*pi/3) and Sqrt(3)/pi*Cos((k-1)*pi/3),
 * where k=0..6 */
float32 Ifx_g_SvmF32_SinCosVector[14];

/**
 * \brief Initialize lookup-table needed for Space Vector Modulation
 */
void Ifx_SvmF32_init(void)
{
    sint32 k;

    /* generate vector table for Ifx_SvmF32 */
    for (k = 1; k <= 6; k++)
    {
        Ifx_g_SvmF32_SinCosVector[((k - 1) * 2)]     = (sqrtf(3) / IFX_PI) * sinf(((k - 1) * IFX_PI) / 3);
        Ifx_g_SvmF32_SinCosVector[((k - 1) * 2) + 1] = (sqrtf(3) / IFX_PI) * cosf(((k - 1) * IFX_PI) / 3);
    }

    /* Assign the constant value to fix the compiler warning */
    Ifx_g_SvmF32_SinCosVector[12] = 0.0f;        /* (sqrtf(3) / IFX_PI) * sinf(((1 - 1) * IFX_PI) / 3) */
    Ifx_g_SvmF32_SinCosVector[13] = 0.55132902f; /* (sqrtf(3) / IFX_PI) * cosf(((1 - 1) * IFX_PI) / 3) */
}


/** \brief Space Vector Modulation.
 *
 * This function returns the "on time" in ticks corresponding to the input vector m for the 3 output channels.
 * The produced voltage is \f$ V = 2 . m . \frac{V_{dc}}{\pi} \f$
 *
 * Note that in Continuous mode (voltage vector inside hexagon):
 * \f$ V_{max} = \frac{V_{dc}}{sqrt(3)} \f$
 *
 * Thus: \f$ m_{max} = \frac{pi}{2 . sqrt(3)} = 0.906 \f$
 *
 * \param m Specifies the modulation index as a vector. The limit between the continuous and discontinuous mode is defined as follow:
 *  - Continuous mode: \f$ 0 \le \left | m \right | \le 0.906 \f$
 *  - Saturation mode: \f$ 0.906 \ll  \left | m \right | \f$
 *
 * \param period Specifies the PWM period value in ticks.
 * \param channels This parameter is filled in by the function with the corresponding "on time" for the 3 output channels. The unit is ticks.
 *
 * \return none
 */
void Ifx_SvmF32_do(cfloat32 m, Ifx_TimerValue period, Ifx_TimerValue* channels)
{
    uint8              Sector;
    float32            x;
    Ifx_SignedTimerVal Tk, Tk1;
    Ifx_TimerValue     Ts, Tm, Tb;
    Ifx_SignedTimerVal halfPeriod;

    // determination of the sector
    x = m.imag * IFX_ONE_OVER_SQRT_THREE;

    if (m.imag > 0)
    {     // m.imag>0
        if (m.real > 0)
        { // Quadrant 1
            if (x < m.real)
            {
                Sector = 0;
            }
            else
            {
                Sector = 1;
            }
        }
        else
        {   // Quadrant 2
            if (x < -m.real)
            {
                Sector = 2;
            }
            else
            {
                Sector = 1;
            }
        }
    }
    else
    {     // m.imag<0
        if (m.real < 0)
        { // Quadrant 3
            if (x < m.real)
            {
                Sector = 4;
            }
            else
            {
                Sector = 3;
            }
        }
        else
        {   // Quadrant 4
            if (x < -m.real)
            {
                Sector = 4;
            }
            else
            {
                Sector = 5;
            }
        }
    }

    // Sector range is the Sector number minus 1 (from 0 to 5)
    // Calcul of Tk and Tk+1, k is the sector number
    // Tk=      sin(k)*m.Re     -   Cos(k)*m.Im
    // Tk+1=    Cos(k-1)*m.Im   -   Sin(k-1)*m.Re
    Tk  = (Ifx_SignedTimerVal)(((Ifx_g_SvmF32_SinCosVector[((Sector + 1) * 2) + 0] * m.real) - (Ifx_g_SvmF32_SinCosVector[((Sector + 1) * 2) + 1] * m.imag)) * period);
    Tk1 = (Ifx_SignedTimerVal)(((Ifx_g_SvmF32_SinCosVector[((Sector) * 2) + 1] * m.imag) - (Ifx_g_SvmF32_SinCosVector[((Sector) * 2) + 0] * m.real)) * period);

    if ((Sector & 0x1) != 0)
    {
        Ifx_SignedTimerVal temp;
        temp = Tk;
        Tk   = Tk1;
        Tk1  = temp;
    }

    halfPeriod = period >> 1;
    Ts         = __saturateX((halfPeriod - Tk) - Tk1, 0, period);
    Tm         = __saturateX((halfPeriod - Tk) + Tk1, 0, period);
    Tb         = __saturateX((halfPeriod + Tk) + Tk1, 0, period);

    switch (Sector)
    {
    case 0:
        channels[0] = Tb;
        channels[1] = Tm;
        channels[2] = Ts;
        break;
    case 1:
        channels[0] = Tm;
        channels[1] = Tb;
        channels[2] = Ts;
        break;
    case 2:
        channels[0] = Ts;
        channels[1] = Tb;
        channels[2] = Tm;
        break;
    case 3:
        channels[0] = Ts;
        channels[1] = Tm;
        channels[2] = Tb;
        break;
    case 4:
        channels[0] = Tm;
        channels[1] = Ts;
        channels[2] = Tb;
        break;
    case 5:
        channels[0] = Tb;
        channels[1] = Ts;
        channels[2] = Tm;
        break;
    default:
        break;
    }
}


/** \brief Return the reference voltage.
 *
 * The reference voltage is \f$ V_{ref} = m . V_{dc} \frac{2}{\pi} \f$
 *
 * \param m Specifies the modulation index as a vector.
 * \param vdc Specifies the DC link voltage. The unit is arbitrary, the same unit will be returned by the function
 *
 * \return return the reference voltage as vector. The unit is the same as the voltageDc parameter
 */
cfloat32 Ifx_SvmF32_getVoltages(cfloat32 m, float32 vdc)
{
    cfloat32 Vref;
    float32  Factor = vdc * IFX_TWO_OVER_PI;
    Vref.real = m.real * Factor;
    Vref.imag = m.imag * Factor;
    return Vref;
}


/** \brief Return the reference voltage.
 *
 * The reference voltage is \f$ V_{ref} = m . V_{dc} \frac{2}{\pi} \f$
 *
 * \param m Specifies the modulation index.
 * \param vdc Specifies the DC link voltage. The unit is arbitrary, the same unit will be returned by the function
 *
 * \return return the reference voltage. The unit is the same as the voltageDc parameter
 */
float32 Ifx_SvmF32_getVoltage(float32 m, float32 vdc)
{
    float32 Vref;
    float32 Factor = vdc * IFX_TWO_OVER_PI;
    Vref = m * Factor;
    return Vref;
}


/** \brief Return the modulation index
 *
 * The reference voltage is \f$ V_{ref} = m . V_{dc} \frac{2}{\pi} \f$
 *
 * \param v Specifies the voltage as a vector.
 * \param vdc Specifies the DC link voltage, the same unit as v.
 *
 * \return the modulation index
 */
cfloat32 Ifx_SvmF32_getModIndex(cfloat32 v, float32 vdc)
{
    cfloat32 m;
    float32  Factor = vdc * IFX_TWO_OVER_PI;
    m.real = v.real / Factor;
    m.imag = v.imag / Factor;
    return m;
}


/** \brief Calculate the phase voltages from the given timer values
 * \return Alpha-Beta phase voltages in Volts */
cfloat32 Ifx_SvmF32_revertToVoltages(const Ifx_TimerValue* timerValues, float32 vdc, Ifx_TimerValue period)
{
    float32 lineToGround[3];
    float32 lineToLine[3];
    float32 lineToNeutral[3];

    lineToGround[0]  = (float32)timerValues[0] * vdc / period;
    lineToGround[1]  = (float32)timerValues[1] * vdc / period;
    lineToGround[2]  = (float32)timerValues[2] * vdc / period;

    lineToLine[0]    = lineToGround[0] - lineToGround[1];
    lineToLine[1]    = lineToGround[1] - lineToGround[2];
    lineToLine[2]    = lineToGround[2] - lineToGround[0];

    lineToNeutral[0] = (lineToLine[0] - lineToLine[2]) / 3;
    lineToNeutral[1] = (lineToLine[1] - lineToLine[0]) / 3;
    lineToNeutral[2] = (lineToLine[2] - lineToLine[1]) / 3;

    /* forward transform */
    return Ifx_ClarkeF32(lineToNeutral);
}
