/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013-2018 Martin Zuther (http://www.mzuther.de/)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Thank you for using free software!

---------------------------------------------------------------------------- */

#pragma once

#include "FrutHeader.h"


class GainStage
{
public:
    enum Parameters  // public namespace!
    {
        FET = 0,
        Optical,
        NumberOfGainStages,
    };

    // Destructor.
    virtual ~GainStage() {};

    virtual void reset(double dCurrentGainReduction) = 0;
    virtual double processGainReduction(double dGainReductionNew, double dGainReductionIdeal) = 0;

protected:
    GainStage(int nSampleRate)
    {
        ignoreUnused(nSampleRate);
    };
};
