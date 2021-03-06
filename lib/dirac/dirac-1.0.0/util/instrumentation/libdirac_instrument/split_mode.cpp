/* ***** BEGIN LICENSE BLOCK *****
*
* $Id: split_mode.cpp,v 1.8 2008/06/19 10:39:59 tjdwave Exp $ $Name: Dirac_1_0_0 $
*
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License
* Version 1.1 (the "License"); you may not use this file except in compliance
* with the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
* the specific language governing rights and limitations under the License.
*
* The Original Code is BBC Research and Development code.
*
* The Initial Developer of the Original Code is the British Broadcasting
* Corporation.
* Portions created by the Initial Developer are Copyright (C) 2004.
* All Rights Reserved.
*
* Contributor(s): Chris Bowley (Original Author)
*
* Alternatively, the contents of this file may be used under the terms of
* the GNU General Public License Version 2 (the "GPL"), or the GNU Lesser
* Public License Version 2.1 (the "LGPL"), in which case the provisions of
* the GPL or the LGPL are applicable instead of those above. If you wish to
* allow use of your version of this file only under the terms of the either
* the GPL or LGPL and not to allow others to use your version of this file
* under the MPL, indicate your decision by deleting the provisions above
* and replace them with the notice and other provisions required by the GPL
* or LGPL. If you do not delete the provisions above, a recipient may use
* your version of this file under the terms of any one of the MPL, the GPL
* or the LGPL.
* ***** END LICENSE BLOCK ***** */

#include <util/instrumentation/libdirac_instrument/split_mode.h>
using namespace dirac_instr;
using namespace dirac;

// constructor
DrawSplitMode::DrawSplitMode(Picture & picture, DrawPictureMotionParams & draw_params, const TwoDArray<int> & mode)
:
    DrawOverlay(picture, draw_params),
    m_mode(mode)
{}

// destructor
DrawSplitMode::~DrawSplitMode()
{}

// colours a motion vector block according to split mode
void DrawSplitMode::DrawBlock(int j, int i)
{
    int power = 0, U = 0, V = 0;
    // get split level
    if (m_mode[int(j/4)][int(i/4)] == 0)
        power=0;
    else if (m_mode[int(j/4)][int(i/4)] == 1)
        power=100;
    else if (m_mode[int(j/4)][int(i/4)] == 2)
        power=200;

    GetPowerUV(power, U, V);
    DrawMvBlockUV(j, i, U, V);

}

// displays colours representing splitting mode
void DrawSplitMode::DrawLegend()
{
    // blank background
    for (int ypx=m_draw_params.PicY()-49; ypx<m_draw_params.PicY(); ++ypx)
    {
        for (int xpx=7; xpx>=0; --xpx)
            m_picture.Data(Y_COMP)[ypx][xpx]=0; // grey
    }

    int U=0, V=0;

    GetPowerUV(200, U, V); // mode 2
    DrawBlockUV((m_draw_params.PicY()/m_draw_params.ChromaFactorY())-1-(48/m_draw_params.ChromaFactorY())+1, 0, U, V);
    DrawBlockUV((m_draw_params.PicY()/m_draw_params.ChromaFactorY())-1-(40/m_draw_params.ChromaFactorY())+1, 0, U, V);
    
    GetPowerUV(100, U, V); // mode 1
    DrawBlockUV((m_draw_params.PicY()/m_draw_params.ChromaFactorY())-1-(32/m_draw_params.ChromaFactorY())+1, 0, U, V);
    DrawBlockUV((m_draw_params.PicY()/m_draw_params.ChromaFactorY())-1-(24/m_draw_params.ChromaFactorY())+1, 0, U, V);
    
    GetPowerUV(0, U, V); // mode 0
    DrawBlockUV((m_draw_params.PicY()/m_draw_params.ChromaFactorY())-1-(16/m_draw_params.ChromaFactorY())+1, 0, U, V);
    DrawBlockUV((m_draw_params.PicY()/m_draw_params.ChromaFactorY())-1-(8/m_draw_params.ChromaFactorY())+1, 0, U, V);

    // black horizontal lines
    for (int xpx=15; xpx>=0; --xpx)
    {
        m_picture.Data(Y_COMP)[m_draw_params.PicY()-49][xpx]=-128;
        m_picture.Data(Y_COMP)[m_draw_params.PicY()-33][xpx]=-128;
        m_picture.Data(Y_COMP)[m_draw_params.PicY()-17][xpx]=-128;
    }

    // draw '2 1 0' label
    DrawCharacter(m_symbols.Number2(), m_draw_params.PicY()-48, 8);
    DrawCharacter(m_symbols.Number1(), m_draw_params.PicY()-32, 8);
    DrawCharacter(m_symbols.Number0(), m_draw_params.PicY()-16, 8);
}

