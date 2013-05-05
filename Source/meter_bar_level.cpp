/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

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

#include "meter_bar_level.h"

MeterBarLevel::MeterBarLevel(const String& componentName, int pos_x, int pos_y, int width, int number_of_bars, int segment_height, float crest_factor)
{
    setName(componentName);

    // this component does not have any transparent areas (increases
    // performance on redrawing)
    setOpaque(true);

    // add overload marker
    nNumberOfBars = number_of_bars + 1;
    nSegmentHeight = segment_height;
    fCrestFactor = crest_factor;

    nPosX = pos_x;
    nPosY = pos_y;
    nWidth = width;
    nHeight = (nNumberOfBars + 1) * nSegmentHeight + 1;

    fAverageLevel = -70.01f;
    fPeakLevel = -70.01f;
    fPeakLevelPeak = -70.01f;
    fMaximumLevel = -70.01f;

    MeterArray = new MeterSegment*[nNumberOfBars];

    float fRange = 2.0f;
    int nThreshold = 10 * int(fCrestFactor - fRange);
    int nColor = -1;

    for (int n = 0; n < nNumberOfBars; n++)
    {
        if (n == 0)
        {
            nColor = 0;
            nThreshold += 20;
        }
        else if (nThreshold >= 160)
        {
            nColor = 0;
        }
        else if (nThreshold >= 100)
        {
            nColor = 1;
        }
        else
        {
            nColor = 2;
        }

        MeterArray[n] = new MeterSegment("MeterSegment #" + String(n) + " (" + componentName + ")", nThreshold * 0.1f, fRange, true, nColor);
        addAndMakeVisible(MeterArray[n]);

        nThreshold -= 20;
    }
}


MeterBarLevel::~MeterBarLevel()
{
    for (int n = 0; n < nNumberOfBars; n++)
    {
        removeChildComponent(MeterArray[n]);

        delete MeterArray[n];
        MeterArray[n] = NULL;
    }

    delete [] MeterArray;
    MeterArray = NULL;

    deleteAllChildren();
}


void MeterBarLevel::visibilityChanged()
{
    setBounds(nPosX, nPosY, nWidth, nHeight);

    int x = 0;
    int y = 0;

    for (int n = 0; n < nNumberOfBars; n++)
    {
        if (n == 0)
        {
            MeterArray[n]->setBounds(x, y, nWidth, 2 * nSegmentHeight - 1);
            y += 2 * nSegmentHeight;
        }
        else
        {
            MeterArray[n]->setBounds(x, y, nWidth, nSegmentHeight + 1);
            y += nSegmentHeight;
        }
    }
}


void MeterBarLevel::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}


void MeterBarLevel::resized()
{
}


void MeterBarLevel::setLevel(float fPeakLevelNew, float fAverageLevelNew, float fPeakLevelPeakNew, float fMaximumLevelNew)
{
    if ((fPeakLevelNew != fPeakLevel) || (fAverageLevelNew != fAverageLevel) || (fPeakLevelPeakNew != fPeakLevelPeak))
    {
        fPeakLevel = fPeakLevelNew;
        fAverageLevel = fAverageLevelNew;
        fPeakLevelPeak = fPeakLevelPeakNew;

        for (int n = 1; n < nNumberOfBars; n++)
        {
            MeterArray[n]->setLevels(fPeakLevel, fAverageLevel, fPeakLevelPeak, -9999.9f);
        }
    }

    if (fMaximumLevelNew != fMaximumLevel)
    {
        fMaximumLevel = fMaximumLevelNew;

        if (fMaximumLevel >= fCrestFactor)
        {
            MeterArray[0]->setLevels(fCrestFactor + 0.01f, -9999.9f, fCrestFactor + 0.01f, -9999.9f);
        }
        else
        {
            MeterArray[0]->setLevels(-9999.9f, -9999.9f, -9999.9f, -9999.9f);
        }
    }
}


// Local Variables:
// ispell-local-dictionary: "british"
// End:
