/* -----------------------------------------------------------------------------

    Copyright (c) 2006 Simon Brown                          si@sjbrown.co.uk

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   -------------------------------------------------------------------------- */

/*! @file

    @brief This program tests the error for 1 and 2-colour DXT compression.

    This tests the effectiveness of the DXT compression algorithm for all
    possible 1 and 2-colour blocks of pixels.
*/

#include <squish/squish.h>
#include <sstream>
#include <cmath>
#include <cfloat>
#include <cstdlib>

#include "libsquish_test_common.h"

using namespace squish;

struct ErrorStats
{
    double min, max, avg;

    ErrorStats(double min, double max, double avg) :
        min(min),
        max(max),
        avg(avg)
    {}

    bool operator==(const ErrorStats& other) const
    {
        return this->min == other.min &&
               this->max == other.max &&
               this->avg == other.avg;
    }
};

inline std::string toString(const ErrorStats& es)
{
    std::ostringstream ss;
    ss.precision(100);
    ss << "{\n";
    ss << "    min = " << es.min << "\n";
    ss << "    max = " << es.max << "\n";
    ss << "    avg = " << es.avg << "\n";
    ss << "}\n";

    return ss.str();
}

double GetColourError( u8 const* a, u8 const* b )
{
    double error = 0.0;
    for( int i = 0; i < 16; ++i )
    {
        for( int j = 0; j < 3; ++j )
        {
            int index = 4*i + j;
            int diff = ( int )a[index] - ( int )b[index];
            error += ( double )( diff*diff );
        }
    }
    return error / 16.0;
}

ErrorStats TestOneColour( int flags )
{
    u8 input[4*16];
    u8 output[4*16];
    u8 block[16];

    double avg = 0.0, min = DBL_MAX, max = -DBL_MAX;
    int counter = 0;

    // test all single-channel colours
    for( int i = 0; i < 16*4; ++i )
        input[i] = ( ( i % 4 ) == 3 ) ? 255 : 0;
    for( int channel = 0; channel < 3; ++channel )
    {
        for( int value = 0; value < 255; ++value )
        {
            // set the channnel value
            for( int i = 0; i < 16; ++i )
                input[4*i + channel] = ( u8 )value;

            // compress and decompress
            Compress( input, block, flags );
            Decompress( output, block, flags );

            // test the results
            double rm = GetColourError( input, output );
            double rms = std::sqrt( rm );

            // accumulate stats
            if (rms < min) min = rms;
            if (rms > max) max = rms;
            avg += rm;
            ++counter;
        }

        // reset the channel value
        for( int i = 0; i < 16; ++i )
            input[4*i + channel] = 0;
    }

    // finish stats
    avg = std::sqrt( avg/counter );
    return ErrorStats(min, max, avg);
}

ErrorStats TestOneColourRandom( int flags )
{
    u8 input[4*16];
    u8 output[4*16];
    u8 block[16];

    double avg = 0.0, min = DBL_MAX, max = -DBL_MAX;
    int counter = 0;

    // test all single-channel colours
    for( int test = 0; test < 1000; ++test )
    {
        // set a constant random colour
        for( int channel = 0; channel < 3; ++channel )
        {
            u8 value = ( u8 )( rand() & 0xff );
            for( int i = 0; i < 16; ++i )
                input[4*i + channel] = value;
        }
        for( int i = 0; i < 16; ++i )
            input[4*i + 3] = 255;

        // compress and decompress
        Compress( input, block, flags );
        Decompress( output, block, flags );

        // test the results
        double rm = GetColourError( input, output );
        double rms = std::sqrt( rm );

        // accumulate stats
        if (rms < min) min = rms;
        if (rms > max) max = rms;
        avg += rm;
        ++counter;
    }

    // finish stats
    avg = std::sqrt( avg/counter );
    return ErrorStats(min, max, avg);
}

ErrorStats TestTwoColour( int flags )
{
    u8 input[4*16];
    u8 output[4*16];
    u8 block[16];

    double avg = 0.0, min = DBL_MAX, max = -DBL_MAX;
    int counter = 0;

    // test all single-channel colours
    for( int i = 0; i < 16*4; ++i )
        input[i] = ( ( i % 4 ) == 3 ) ? 255 : 0;
    for( int channel = 0; channel < 3; ++channel )
    {
        for( int value1 = 0; value1 < 255; ++value1 )
        {
            for( int value2 = value1 + 1; value2 < 255; ++value2 )
            {
                // set the channnel value
                for( int i = 0; i < 16; ++i )
                    input[4*i + channel] = ( u8 )( ( i < 8 ) ? value1 : value2 );

                // compress and decompress
                Compress( input, block, flags );
                Decompress( output, block, flags );

                // test the results
                double rm = GetColourError( input, output );
                double rms = std::sqrt( rm );

                // accumulate stats
                if (rms < min) min = rms;
                if (rms > max) max = rms;
                avg += rm;
                ++counter;
            }
        }

        // reset the channel value
        for( int i = 0; i < 16; ++i )
            input[4*i + channel] = 0;
    }

    // finish stats
    avg = std::sqrt( avg/counter );
    return ErrorStats(min, max, avg);
}

int main()
{
    LS_START("tst_color_error");

    // Re-seed
    srand(time(NULL));

    LS_VERIFY(TestOneColourRandom( kDxt1 | kColourRangeFit).max == 1.732050807568877193176604123436845839023590087890625);
    LS_COMPARE(TestOneColour( kDxt1 ),
               ErrorStats(0, 1, 0.478286702652959527792830840553506277501583099365234375));
    LS_COMPARE(TestTwoColour( kDxt1 ),
               ErrorStats(0, 4.527692569068708650092958123423159122467041015625, 1.50027016248562716782544157467782497406005859375));

    LS_END();
}
