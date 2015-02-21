#pragma once
/*
 * Copyright (C) 2014 Achim Turan, Achim.Turan@o2online.de
 * https://github.com/AchimTuran/asplib
 *
 * This file is part of asplib (Achim's Signal Processing LIBrary)
 *
 * asplib (Achim's Signal Processing LIBrary) is free software:
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * asplib (Achim's Signal Processing LIBrary) is distributed
 * in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with asplib (Achim's Signal Processing LIBrary).
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */



// this module implements basic biquad filters 
// for more details see: http://en.wikipedia.org/wiki/Digital_biquad_filter

#include "../constants_typedefs/asplib_constants.h"
#include "../constants_typedefs/asplib_typedefs.h"

namespace asplib
{
template<typename T>
class IBaseBiQuad
{
public:
    // use this constructor to create a biquad filter with coefficients
    IBaseBiQuad(uint Quantity, float SampleFrequency)
    {
        m_parameters = NULL;
            
        if(Quantity == 0)
        {
            // ToDo: throw error!
        }
        m_maxBiQuads = Quantity;

        if(SampleFrequency <= 0.0f)
        {
            // ToDo: throw error!
        }
        m_sampleFrequency = SampleFrequency;
    }

    virtual ~IBaseBiQuad() {}

    virtual ASPLIB_ERR updateCoefficients(ASPLIB_BIQUAD_COEFFICIENTS *Coefficients, float D0) = 0;
    virtual ASPLIB_ERR updateCoefficients(ASPLIB_BIQUAD_COEFFICIENTS *Coefficients, float D0, uint BiQuadIdx) = 0;

    // calculate one output sample with the following difference equation
    // y[k] = d0*x[k] + a0*x[k] + a1*x[k-1] + a2*x[k-2] - (b1*y[k-1] + b2*y[k-2])
    virtual float calcSample(float In) = 0;
    virtual ASPLIB_ERR calcSamples(float *In, float *Out, uint N) = 0;

    // Set all past values (x[k-1], x[k-2], y[k-1] and y[k-2]) to zero.
    virtual void resetState() = 0;

    //--- helper functions ---
    // get BiQuad quantity
    uint getMaxBiquads()
    {
        return m_maxBiQuads;
    }

    float getSampleFrequency()
    {
        return m_sampleFrequency;
    }

protected:
    T *m_parameters;    // array structure for one BiQuad
                        // [0]=d0,      [1]=a0*c0,  [2]=a1*c0,    [3]=a2*c0
                        // [4]=-b1*c0,  [5]=-b2*c0, [6]=0,        [7]=0
                        // [8]=x[k-1],  [9]=x[k-2], [10]=y[k-1],  [11]=y[k-2]

private:
    uint m_maxBiQuads;  // maximum BiQuad quantity
    float m_sampleFrequency;
};
}