//
// "$Id$"
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//    http://www.fltk.org/str.php
//

// This is an obsolete class from fltk2 development. All functionality
// has been moved to the base Image class.

#ifndef fltk_rgbImage_h
#define fltk_rgbImage_h

#include "Image.h"

namespace fltk {

class FL_API rgbImage : public Image {
public:
  //bool write_jpeg(const char *filename, int quality=75, int dpi=150);
  rgbImage(const char* name=0) : Image(name) {}
  rgbImage(const uchar* d, PixelType p, int W, int H) :
    Image(d,p,W,H,fltk::depth(p)*W) {}
  rgbImage(const uchar* d, PixelType p, int W, int H, int linedelta) :
    Image(d,p,W,H,linedelta) {}
};

}

#endif

//
// End of "$Id$".
//
