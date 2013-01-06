/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose compressor with a touch of lemon

   Copyright (c) 2013 Martin Zuther (http://www.mzuther.de/)

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

#ifndef __SLIDER_STEPPED_H__
#define __SLIDER_STEPPED_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "plugin_parameters_squeezer.h"
#include "wrapped_parameter_stepped.h"


//==============================================================================
/**
*/
class SliderStepped : public Slider
{
public:
    SliderStepped(const String& componentName, int nWidth, SqueezerPluginParameters* parameters, int parameter_index);
    ~SliderStepped();

    void setSliderColour(const Colour& colour);

    double getValueFromText(const String& strText);
    String getTextFromValue(double fValue);
private:
    JUCE_LEAK_DETECTOR(SliderStepped);


    SqueezerPluginParameters* pPluginParameters;
    int nParameterIndex;
};


#endif  // __SLIDER_STEPPED_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End:
