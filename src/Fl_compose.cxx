//
// "$Id: Fl_compose.cxx,v 1.22 2004/06/24 07:05:17 spitzak Exp $"
//
// Copyright 1998-2003 by Bill Spitzak and others.
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
#include <fltk/events.h>
#include <stdio.h>
using namespace fltk;

// Before searching anything the following conversions are made:
// '"', ';' -> ":"     "/" -> "|"    "=",'_' -> "-"

// This table starts at character 0xA0 (non-breaking space)
// The characters may be typed in either order after the compose key.
// If the second character is a space then only the first character
// needs to be typed.
// I changed these slightly from fltk 1.0 to match X compose
// sequences in cases when my version did not use the same characters
// as the X sequence. Comments show the original versions.

static const char compose_pairs[] = {
  "  "	// nbsp
  "! "	// inverted !
  "c|"	// cent		 (was "% ")
  "l-"	// pound	 (was "# ")
  "xo"	// currency	 (was "$ ")
  "y-"	// yen
  "| "	// broken bar
  "s "	// section	 (was "& ", X uses "so")
  ": "	// dieresis
  "c "	// copyright	 (X uses "co")
  "a "	// superscript a (X uses "a-")
  "<<"	// <<
  "-,"	// not sign	 (was "~ ")
  "- "	// hyphen
  "r "	// registered	 (X uses "ro")
  "--"	// macron	 (was "_ ", X uses "-^")
  "0 "	// superscript 0 (degree, was "* ", X uses "0^")
  "+-"	// plusminus
  "2 "	// superscript 2 (X uses "2^")
  "3 "	// superscript 3 (X uses "3^")
  "' "	// acute
  "u "	// mu
  "p "	// paragraph
  ". "	// centered dot
  ", "	// cedilla
  "1 "	// superscript 1 (X uses "1^")
  "o "	// superscript o (X uses "o-")
  ">>"	// >>
  "14"	// 1/4
  "12"	// 1/2
  "34"	// 3/4
  "? "	// inverted ?
  "`A"
  "'A"
  "^A"
  "~A"
  ":A"
  "*A"
  "AE"
  ",C"
  "`E"
  "'E"
  "^E"
  ":E"
  "`I"
  "'I"
  "^I"
  ":I"
  "-D"
  "~N"
  "`O"
  "'O"
  "^O"
  "~O"
  ":O"
  "x "	// multiply
  "O|"
  "`U"
  "'U"
  "^U"
  ":U"
  "'Y"
  "TH"
  "ss"
  "`a"
  "'a"
  "^a"
  "~a"
  ":a"
  "*a"
  "ae"
  ",c"
  "`e"
  "'e"
  "^e"
  ":e"
  "`i"
  "'i"
  "^i"
  ":i"
  "-d"
  "~n"
  "`o"
  "'o"
  "^o"
  "~o"
  ":o"
  "-:"	// divide
  "o|"
  "`u"
  "'u"
  "^u"
  ":u"
  "'y"
  "th"
  ":y"
};

#if USE_X11 // X only
extern int fl_actual_keysym;
// X dead-key lookup table.  This turns a dead-key keysym into the
// first of two characters for one of the compose sequences.  These
// keysyms start at 0xFE50.
// Win32 handles the dead keys before fltk can see them.  This is
// unfortunate, because you don't get the preview effect.
static const char dead_keys[] = {
  '`',	// XK_dead_grave
  '\'',	// XK_dead_acute
  '^',	// XK_dead_circumflex
  '~',	// XK_dead_tilde
  '_',	// XK_dead_macron
  0,	// XK_dead_breve
  '.',	// XK_dead_abovedot
  ':',	// XK_dead_diaeresis
  '*',	// XK_dead_abovering
  0,	// XK_dead_doubleacute
  'v',	// XK_dead_caron
  ','	// XK_dead_cedilla
//   0,	// XK_dead_ogonek
//   0,	// XK_dead_iota
//   0,	// XK_dead_voiced_sound
//   0,	// XK_dead_semivoiced_sound
//   0	// XK_dead_belowdot
};
#endif

int fltk::compose_state;

/*!

  Use of this function is very simple. Any text editing widget should
  call this for each fltk::KEY event.

  If true is returned, then it has modified the fltk::event_text() and
  fltk::event_length() to a set of bytes to insert (it may be of zero
  length!). It will also set the \a del parameter to the number of bytes
  to the left of the cursor to delete, this is used to delete the
  results of the previous call to fltk::compose(). Compose may consume
  the key, which is indicated by returning true, but both the length
  and del are set to zero.

  Compose returns false if it thinks the key is a function key that
  the widget should handle itself, and not an attempt by the user to
  insert text.

  Though the current implementation returns immediately, future
  versions may take quite awhile, as they may pop up a window or do
  other user-interface things to allow international characters to be
  selected.
*/
bool fltk::compose(int& del) {

  del = 0;
  char ascii = e_text[0];
  if      (ascii == '"' || ascii == ';') ascii = ':';
  else if (ascii == '/') ascii = '|';
  else if (ascii == '_' || ascii == '=') ascii = '-';

  static int plen;

  if (e_length > 1) return true; // probably indicates InputMethod was used

  if (compose_state == 1) { // after the compose key

    plen = e_length;

    // see if it is either character of any pair:
    for (const char *p = compose_pairs; *p; p += 2) 
      if (p[0] == ascii || p[1] == ascii) {
	compose_state = ascii;
	// prefer the single-character versions:
	if (p[1] == ' ') {
	  int code = (p-compose_pairs)/2+0xA0;
	  // convert code to utf8:
	  e_text[0] = 0xc0 | code>>6;
	  e_text[1] = 0x80 | (code & 0x3f);
	  e_text[2] = 0;
	  plen = e_length = 2;
	  return true;
	}
      }
    if (compose_state != 1) return true;

    // The right-hand ctrl and any letter "quotes" the control character:
    if (e_length && event_key()<128) {
      compose_state = 0;
      return true;
    }

  } else if (compose_state) { // second character of compose

    char c1 = char(compose_state); // retrieve first character
    // now search for the pair in either order:
    for (const char *p = compose_pairs; *p; p += 2) {
      if (p[0] == ascii && p[1] == c1 || p[1] == ascii && p[0] == c1) {
	int code = (p-compose_pairs)/2+0xA0;
	// convert code to utf8:
	e_text[0] = 0xc0 | code>>6;
	e_text[1] = 0x80 | (code & 0x3f);
	e_text[2] = 0;
	e_length = 2;
	del = plen; // delete the old character and insert new one
	compose_state = 0;
	return true;
      }
    }

  }

#if USE_X11
  int i = fl_actual_keysym;
  // See if they typed a dead key.  This gets it into the same state as
  // typing prefix+accent:
  if (i >= 0xfe50 && i <= 0xfe5b) {
    compose_state = dead_keys[i-0xfe50];
    return true;
  }
#else
  int i = e_keysym;
#endif

  // Alt+letters are reserved for shortcuts.  But alt+foreign letters
  // has to be allowed, because some key layouts require alt to be held
  // down in order to type them...
  if ((e_state & (ALT|META)) && !(ascii & 128)) return false;

  // See if they type the compose prefix key:
  if (i == RightCtrlKey || i == 0xff20/* Multi-Key */) {
    compose_state = 1;
    return true;
  }

  // Only insert non-control characters:
  if (e_length && (ascii & ~31 && ascii != 127)) {
    compose_state = 0;
    return true;
  }

  return false;
}

/*! \fn void fltk::compose_reset()
  If the user moves the cursor, be sure to call
  fltk::compose_reset(). The next call to fltk::compose() will start
  out in an initial state. In particular it will not set "del" to
  non-zero. This call is very fast so it is ok to call it many times
  and in many places.
*/

// end of Fl_compose.cxx
