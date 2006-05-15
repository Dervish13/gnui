//
// "$Id$"
//
// Non-path routines from draw.h that are used by the standard boxtypes
// and thus are always linked into an fltk program.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#include <config.h>
#include <fltk/draw.h>
#include <fltk/x.h>
#include <fltk/math.h>
using namespace fltk;

#if USE_QUARTZ
namespace fltk {
  extern float quartz_line_width_;
}
#endif

/** \defgroup rectangle Simple Drawing
    \ingroup drawing

    These functions bypass the path construction mechanism to draw
    some common shapes more quickly with calls to Xlib or GDI32.  Only
    the x,y coordinates are transformed and in most cases they are
    rounded to the nearest integer.

  \{
*/

/*! Fill the rectangle with the current color. */
void fltk::fillrect(int x, int y, int w, int h) {
  if (w <= 0 || h <= 0) return;
  transform(x,y);
#if USE_CAIRO
  cairo_rectangle(cc,x,y,w,h);
  cairo_fill(cc);
#elif USE_X11
  XFillRectangle(xdisplay, xwindow, gc, x, y, w, h);
#elif defined(_WIN32)
  RECT rect;
  rect.left = x; rect.top = y;  
  rect.right = x+w; rect.bottom = y+h;
  SetBkColor(dc, current_xpixel);
  ExtTextOut(dc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
#elif USE_QUARTZ
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, false);
  CGRect rect = CGRectMake(x, y, w-1, h-1);
  CGContextFillRect(quartz_gc, rect);
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, true);
#else
# error
#endif
}

/*! 
  Draw a line \e inside this bounding box (currently correct only for
  0-thickness lines).
*/
void fltk::strokerect(int x, int y, int w, int h) {
  if (w <= 0 || h <= 0) return;
  transform(x,y);
#if USE_CAIRO
  cairo_rectangle(cc,x+.5,y+.5,w-1,h-1);
  cairo_stroke(cc);
#elif USE_X11
  XDrawRectangle(xdisplay, xwindow, gc, x, y, w-1, h-1);
#elif defined(_WIN32)
  setpen();
  MoveToEx(dc, x, y, 0L); 
  LineTo(dc, x+w-1, y);
  LineTo(dc, x+w-1, y+h-1);
  LineTo(dc, x, y+h-1);
  LineTo(dc, x, y);
#elif USE_QUARTZ
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, false);
  CGRect rect = CGRectMake(x, y, w-1, h-1);
  CGContextStrokeRect(quartz_gc, rect);
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, true);
#else
# error
#endif
}

/*! Draw a straight line between the two points. */
void fltk::drawline(int x, int y, int x1, int y1) {
  transform(x,y);
  transform(x1,y1);
#if USE_CAIRO
  cairo_move_to(cc,x+.5,y+.5);
  cairo_line_to(cc,x1+.5,y1+.5);
  cairo_stroke(cc);
#elif USE_X11
  XDrawLine(xdisplay, xwindow, gc, x, y, x1, y1);
#elif defined(_WIN32)
  setpen();
  MoveToEx(dc, x, y, 0L); 
  LineTo(dc, x1, y1);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  // fltk is supposed to act like there is a 1-pixel pen.
  SetPixel(dc, x1, y1, current_xpixel);
#elif USE_QUARTZ
  if (( x==x1 || y==y1 ) && quartz_line_width_==1.0f )  
    CGContextSetShouldAntialias(quartz_gc, false);
  CGContextMoveToPoint(quartz_gc, x, y);
  CGContextAddLineToPoint(quartz_gc, x1, y1);
  CGContextStrokePath(quartz_gc);
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, true);
#else
# error
#endif
}

/*! Draw a straight line between the two points. */
void fltk::drawline(float X, float Y, float X1, float Y1) {
  transform(X,Y); int x = int(floorf(X)+.5); int y = int(floorf(Y)+.5);
  transform(X1,Y1);int x1 = int(floorf(X1)+.5); int y1 = int(floorf(Y1)+.5);
#if USE_CAIRO
  cairo_move_to(cc,X+.5,Y+.5);
  cairo_line_to(cc,X1+.5,Y1+.5);
  cairo_stroke(cc);
#elif USE_X11
  XDrawLine(xdisplay, xwindow, gc, x, y, x1, y1);
#elif defined(_WIN32)
  setpen();
  MoveToEx(dc, x, y, 0L); 
  LineTo(dc, x1, y1);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  // fltk is supposed to act like there is a 1-pixel pen.
#elif USE_QUARTZ
  if (( x==x1 || y==y1 ) && quartz_line_width_==1.0f )  
    CGContextSetShouldAntialias(quartz_gc, false);
  CGContextMoveToPoint(quartz_gc, x, y);
  CGContextAddLineToPoint(quartz_gc, x1, y1);
  CGContextStrokePath(quartz_gc);
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, true);
#else
# error
#endif
}

/*! Draw a dot at the given point. */
void fltk::drawpoint(int x, int y) {
  transform(x,y);
#if USE_CAIRO
  cairo_move_to(cc,x,y);
  cairo_line_to(cc,x,y);
  cairo_stroke(cc);
#elif USE_X11
  XDrawPoint(xdisplay, xwindow, gc, x, y);
#elif defined(_WIN32)
  SetPixel(dc, x, y, current_xpixel);
#elif USE_QUARTZ
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, false);
  CGContextMoveToPoint(quartz_gc, x, y);
  CGContextAddLineToPoint(quartz_gc, x, y);
  CGContextStrokePath(quartz_gc);
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, true);
#else
# error
#endif
}

/*! Draw a dot at the given point. */
void fltk::drawpoint(float X, float Y) {
  transform(X,Y); int x = int(floorf(X)); int y = int(floorf(Y));
#if USE_CAIRO
  cairo_move_to(cc,X,Y);
  cairo_line_to(cc,X,Y);
  cairo_stroke(cc);
#elif USE_X11
  XDrawPoint(xdisplay, xwindow, gc, x, y);
#elif defined(_WIN32)
  SetPixel(dc, x, y, current_xpixel);
#elif USE_QUARTZ
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, false);
  CGContextMoveToPoint(quartz_gc, x, y);
  CGContextAddLineToPoint(quartz_gc, x, y);
  CGContextStrokePath(quartz_gc);
  if (quartz_line_width_==1.0f) CGContextSetShouldAntialias(quartz_gc, true);
#else
# error
#endif
}

/** \} */

//
// End of "$Id$".
//