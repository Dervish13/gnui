// "$Id$"
//
// Copyright 1998-2005 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

#ifndef fltk_draw_h
#define fltk_draw_h

#include "Flags.h" // for alignment values
#include "Color.h"
#include "Rectangle.h"
#include "PixelType.h"

namespace fltk {

struct Font;
class Style;

class FL_API GSave {
  void* data[4]; // hopefully big enough for everybody...
 public:
  GSave();
  ~GSave();
};

/*! \addtogroup transformation
  \{ */
FL_API void push_matrix();
FL_API void pop_matrix();
FL_API void scale(float x, float y);
FL_API void scale(float x);
FL_API void translate(float x, float y);
FL_API void translate(int x, int y);
FL_API void rotate(float d);
FL_API void concat(float, float, float, float, float, float);
FL_API void load_identity();

// get and use transformed positions:
FL_API void transform(float& x, float& y);
FL_API void transform_distance(float& x, float& y);
FL_API void transform(int& x, int& y);
FL_API void transform(Rectangle&);

/*! \} */

/*! \addtogroup clipping
  \{ */
FL_API void push_clip(const Rectangle&);
FL_API void clipout(const Rectangle&);
FL_API void pop_clip();
FL_API void push_no_clip();
FL_API bool not_clipped(const Rectangle&);
FL_API int intersect_with_clip(Rectangle&);
/*! \} */

/*! \addtogroup color
  \{ */
FL_API void setcolor(Color);
extern FL_API Color current_color_;
inline Color getcolor() {return current_color_;}
extern FL_API Color current_bgcolor_;
inline void setbgcolor(Color c) {current_bgcolor_ = c;}
inline Color getbgcolor() {return current_bgcolor_;}

extern const Style* drawstyle_;
void FL_API drawstyle(const Style* s, Flags);
inline const Style* drawstyle() {return drawstyle_;}

extern Flags drawflags_;
inline void setdrawflags(Flags f) {drawflags_ = f;}
inline Flags drawflags() {return drawflags_;}
inline Flags drawflags(Flags f) {return drawflags_ & f;}

// line type:
FL_API void line_style(int, int width=0, char* dashes=0);
enum {
  SOLID	= 0,
  DASH	= 1,
  DOT	= 2,
  DASHDOT	= 3,
  DASHDOTDOT	= 4,

  CAP_FLAT	= 0x100,
  CAP_ROUND	= 0x200,
  CAP_SQUARE	= 0x300,

  JOIN_MITER	= 0x1000,
  JOIN_ROUND	= 0x2000,
  JOIN_BEVEL	= 0x3000
};
/*! \} */

/*! \addtogroup path
  \{ */
FL_API void newpath();
FL_API void addvertex(float x, float y);
FL_API void addvertex(int x, int y);
FL_API void addvertices(int n, const float v[][2]);
FL_API void addvertices(int n, const int v[][2]);
FL_API void addvertices_transformed(int n, const float v[][2]);
FL_API void addcurve(float,float, float,float, float,float, float,float);
FL_API void addarc(float x,float y,float w,float h, float a1, float a2);
FL_API void addpie(const Rectangle& r, float a, float a2);
FL_API void addchord(const Rectangle& r,float a,float a2);
FL_API void closepath();

FL_API void drawpoints();
FL_API void strokepath();
FL_API void fillpath();
FL_API void fillstrokepath(Color);
/*! \} */

/*! \addtogroup rectangle
  \{ */
FL_API void fillrect(const Rectangle&);
FL_API void strokerect(const Rectangle&);
FL_API void drawpoint(int x, int y);
FL_API void drawpoint(float x, float y);
FL_API void drawline(int x0, int y0, int x1, int y1);
FL_API void drawline(float x0, float y0, float x1, float y1);
/*! \} */

/*! \addtogroup font
  \{ */
FL_API void setfont(Font*, float size);
FL_API void setfont(const char*, float size);
FL_API void setfont(const char*, int attributes, float size);

// change the encoding used to draw bytes (depreciated)
extern FL_API const char* encoding_;
inline const char* get_encoding() {return encoding_;}
FL_API void set_encoding(const char*);

// information you can get about the current font+size+encoding:
extern FL_API Font* current_font_;
extern FL_API float current_size_; // should be 2x2 transformation matrix
inline Font* getfont() {return current_font_;}
inline float getsize() {return current_size_;}

// measure things in the current font:
FL_API float getwidth(const char*);
FL_API float getwidth(const char*, int length);
FL_API float getascent();
FL_API float getdescent();

// draw using current font:
FL_API void drawtext_transformed(const char*, int n, float x, float y);
FL_API void drawtext(const char*, float x, float y);
FL_API void drawtext(const char*, int length, float x, float y);

// the label text formatter:
FL_API void measure(const char*, int& w, int& h, Flags = 0);
FL_API void measure(const char*, int length, int& w, int& h, Flags);
FL_API void drawtext(const char*, const Rectangle&, Flags);
FL_API void drawtext(const char*, int length, const Rectangle&, Flags);
// set where \t characters go in label text formatter:
extern FL_API const int* column_widths_;
inline const int* column_widths() {return column_widths_;}
inline void column_widths(const int* i) {column_widths_ = i;}
// see also Symbol.h for @-sign commands
/*! \} */

/*! \addtogroup images
  \{ */
FL_API void drawimage(const uchar*, PixelType, const Rectangle&);
FL_API void drawimage(const uchar*, PixelType, const Rectangle&, int delta);
FL_API void drawimage(const uchar*, PixelType, const Rectangle&, int delta, int ldelta);

typedef const uchar* (*DrawImageCallback)(void* data, int x, int y, int w, uchar* buffer);
FL_API void drawimage(DrawImageCallback, void*, PixelType, const Rectangle&);
FL_API void drawimage(DrawImageCallback, void*, PixelType, const Rectangle&, int delta);

FL_API uchar *readimage(uchar *p, PixelType, const Rectangle&);
FL_API uchar *readimage(uchar *p, PixelType, const Rectangle&, int delta);
FL_API uchar *readimage(uchar *p, PixelType, const Rectangle&, int delta, int ldelta);
/*! \} */

// depreciated:
FL_API int draw_xpm(const char*const* data, int x, int y, Color=GRAY75);
FL_API int measure_xpm(const char*const* data, int &w, int &h);
FL_API void set_mask_bitmap(uchar **ppBitmap);
FL_API void scrollrect(const Rectangle&, int dx, int dy,
		       void (*draw_area)(void*, const Rectangle&), void*);
FL_API void overlay_rect(int,int,int,int);
FL_API void overlay_clear();
//FL_API int draw_symbol(const char* label, int x,int y,int w,int h, Color);

}

#endif

//
// End of "$Id$".
//