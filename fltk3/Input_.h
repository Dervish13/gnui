//
// "$Id: Input_.h 8068 2010-12-20 07:48:59Z greg.ercolano $"
//
// Input base class header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
//     http://www.fltk.org/str.php
//

/* \file
 fltk3::Input_ widget . */

#ifndef Fltk3_Input__H
#define Fltk3_Input__H

#include "Widget.h"


class Fl_Input_;


namespace fltk3 {
  
  const uchar NORMAL_INPUT	= 0;
  const uchar FLOAT_INPUT	= 1;
  const uchar INT_INPUT		= 2;
  const uchar HIDDEN_INPUT	= 3;
  const uchar MULTILINE_INPUT	= 4;
  const uchar SECRET_INPUT	= 5;
  const uchar INPUT_TYPE	= 7;
  const uchar INPUT_READONLY	= 8;
  const uchar NORMAL_OUTPUT	= (fltk3::NORMAL_INPUT | fltk3::INPUT_READONLY);
  const uchar MULTILINE_OUTPUT	= (fltk3::MULTILINE_INPUT | fltk3::INPUT_READONLY);
  const uchar INPUT_WRAP	= 16;
  const uchar MULTILINE_INPUT_WRAP = (fltk3::MULTILINE_INPUT | fltk3::INPUT_WRAP);
  const uchar MULTILINE_OUTPUT_WRAP = (fltk3::MULTILINE_INPUT | fltk3::INPUT_READONLY | fltk3::INPUT_WRAP);
  
  /**
   This class provides a low-overhead text input field.
   
   This is a virtual base class below fltk3::Input. It has all
   the same interfaces, but lacks the handle() and
   draw() method. You may want to subclass it if you are
   one of those people who likes to change how the editing keys
   work. It may also be useful for adding scrollbars
   to the input field.
   
   This can act like any of the subclasses of fltk3::Input, by
   setting type() to one of the following values:
   
   \code
   #define fltk3::NORMAL_INPUT	   0
   #define fltk3::FLOAT_INPUT	   1
   #define fltk3::INT_INPUT		   2
   #define fltk3::MULTILINE_INPUT	   4
   #define fltk3::SECRET_INPUT	   5
   #define fltk3::INPUT_TYPE		   7
   #define fltk3::INPUT_READONLY	   8
   #define fltk3::NORMAL_OUTPUT	   (fltk3::NORMAL_INPUT | fltk3::INPUT_READONLY)
   #define fltk3::MULTILINE_OUTPUT	   (fltk3::MULTILINE_INPUT | fltk3::INPUT_READONLY)
   #define fltk3::INPUT_WRAP		   16
   #define fltk3::MULTILINE_INPUT_WRAP  (fltk3::MULTILINE_INPUT | fltk3::INPUT_WRAP)
   #define fltk3::MULTILINE_OUTPUT_WRAP (fltk3::MULTILINE_INPUT | fltk3::INPUT_READONLY | fltk3::INPUT_WRAP)
   \endcode
   
   All variables that represent an index into a text buffer are byte-oriented,
   not character oriented. Since UTF-8 characters can be up to six bytes long,
   simply incrementing such an index will not reliably advance to the next character
   in the text buffer.
   
   Indices and pointers into the text buffer should always point at a 7 bit ASCII
   character or the beginning of a UTF-8 character sequence. Behavior for false
   UTF-8 sequences and pointers into the middle of a sequence are undefined.
   
   \see fltk3::TextDisplay, fltk3::TextEditor for more powerful text handling widgets
   
   \internal
   When porting this widget from ASCII to UTF-8, previously legal pointers into
   the text of this widget can become illegal by pointing into the middle of
   a UTF-8 sequence. This is not a big problem for fltk3::Input_ because all code
   in this module is quite tolerant. It could be problematic though when deriving
   from this class because no feedback for illegal pointers is given. Additionally,
   a careless "copy" call can put partial UTF-8 sequences into the clipboard.
   
   None of these issues should be disastrous. Nevertheless, we should
   discuss how FLTK should handle false UTF-8 sequences and pointers.
   */
  class FLTK3_EXPORT Input_ : public fltk3::Widget {
   
    friend class ::Fl_Input_;
 
    /** \internal Storage for the text field. */
    const char* value_;
    
    /** \internal Buffer memory for expanded text. \see expand() */
    char* buffer;
    
    /** \internal Size of text in bytes in the \p value_ field. */
    int size_;
    
    /** \internal \todo Please document me! */
    int bufsize;
    
    /** \internal Position of the cursor in the document. */
    int position_;
    
    /** \internal Position of the other end of the selected text. If \p position_ equals 
     \p mark_, no text is selected */
    int mark_;
    
    /** \internal Behavior of Tab key in multiline input widget. 
     If enabled (default) Tab causes focus nav, otherwise Tab is inserted 
     as a character. */
    int tab_nav_;
    
    /** \internal Offset to text origin within widget bounds */
    int xscroll_, yscroll_;
    
    /** \internal Minimal update pointer. Display requires redraw from here to the end
     of the buffer. */
    int mu_p;
    
    /** \internal Maximum size of buffer. \todo Is this really needed? */
    int maximum_size_;
    
    /** \internal Shortcut key that will fetch focus for this widget. */
    int shortcut_;
    
    /** \internal This is set if no text but only the cursor needs updating. */
    uchar erase_cursor_only;
    
    /** \internal The font used for the entire text. */
    fltk3::Font textfont_;
    
    /** \internal Height of the font used for the entire text. */
    fltk3::Fontsize textsize_;
    
    /** \internal color of the entire text */
    fltk3::Color textcolor_;
    
    /** \internal color of the text cursor */
    fltk3::Color cursor_color_;
    
    /** \internal Horizontal cursor position in pixels while moving up or down. */
    static double up_down_pos;
    
    /** \internal Flag to remember last cursor move. */
    static int was_up_down;
    
    /* Convert a given text segment into the text that will be rendered on screen. */
    const char* expand(const char*, char*) const;
    
    /* Calculates the width in pixels of part of a text buffer. */
    double expandpos(const char*, const char*, const char*, int*) const;
    
    /* Mark a range of characters for update. */
    void minimal_update(int, int);
    
    /* Mark a range of characters for update. */
    void minimal_update(int p);
    
    /* Copy the value from a possibly static entry into the internal buffer. */
    void put_in_buffer(int newsize);
    
    /* Set the current font and font size. */
    void setfont() const;
    
  protected:
    
    /* Find the start of a word. */
    int word_start(int i) const;
    
    /* Find the end of a word. */
    int word_end(int i) const;
    
    /* Find the start of a line. */
    int line_start(int i) const;
    
    /* Find the end of a line. */
    int line_end(int i) const;
    
    /* Draw the text in the passed bounding box. */
    void drawtext(int, int, int, int);
    
    /* Move the cursor to the column given by up_down_pos. */
    int up_down_position(int, int keepmark=0);
    
    /* Handle mouse clicks and mouse moves. */
    void handle_mouse(int, int, int, int, int keepmark=0);
    
    /* Handle all kinds of text field related events. */
    int handletext(int e, int, int, int, int);
    
    /* Check the when() field and do a callback if indicated. */
    void maybe_do_callback();
    
    /** \internal Horizontal offset of text to left edge of widget. */
    int xscroll() const {return xscroll_;}
    
    /** \internal Vertical offset of text to top edge of widget. */
    int yscroll() const {return yscroll_;}
    void yscroll(int y) { yscroll_ = y; damage(fltk3::DAMAGE_EXPOSE);}
    
    /* Return the number of lines displayed on a single page.  */
    int linesPerPage();
    
  public:
    
    /* Change the size of the widget. */
    void resize(int, int, int, int);
    
    /* Constructor */
    Input_(int, int, int, int, const char* = 0);
    
    /* Destructor */
    ~Input_();
    
    /* Changes the widget text. */
    int value(const char*);
    
    /* Changes the widget text. */
    int value(const char*, int);
    
    /* Changes the widget text. */
    int static_value(const char*);
    
    /* Changes the widget text. */
    int static_value(const char*, int);
    
    /**
     Returns the text displayed in the widget.
     
     This function returns the current value, which is a pointer
     to the internal buffer and is valid only until the next event is
     handled.
     
     \return pointer to an internal buffer - do not free() this    
     \see fltk3::Input_::value(const char*)
     */
    const char* value() const {return value_;}
    
    /* Returns the character at index \p i. */
    fltk3::Char index(int i) const;
    
    /**
     Returns the number of bytes in value(). 
     
     This may be greater than <tt>strlen(value())</tt> if there are 
     \c nul characters in the text.
     
     \return number of bytes in the text
     */
    int size() const {return size_;}
    
    /** Sets the width and height of this widget.
     \param [in] W, H new width and height
     \see fltk3::Widget::size(int, int) */
    void size(int W, int H) { fltk3::Widget::size(W, H); }
    
    /** Gets the maximum length of the input field.  
     \todo It is not clear if this function is actually required */
    int maximum_size() const {return maximum_size_;}
    
    /** Sets the maximum length of the input field. 
     \todo It is not clear if this function is actually required */
    void maximum_size(int m) {maximum_size_ = m;}
    
    /** Gets the position of the text cursor.
     \return the cursor position as an index
     \see position(int, int)
     */
    int position() const {return position_;}
    
    /** Gets the current selection mark. 
     \return index into the text */
    int mark() const {return mark_;}
    
    /* Sets the index for the cursor and mark. */
    int position(int p, int m);
    
    /** Set the cursor position and mark.
     position(n) is the same as <tt>position(n, n)</tt>.
     \param p new index for cursor and mark
     \return 0 if no positions changed
     \see position(int, int), position(), mark(int)
     */
    int position(int p) {return position(p, p);}
    
    /** Sets the current selection mark. 
     mark(n) is the same as <tt>position(position(),n)</tt>.
     \param m new index of the mark 
     \return 0 if the mark did not change
     \see position(), position(int, int) */
    int mark(int m) {return position(position(), m);}
    
    /* Deletes text from b to e and inserts the new string text. */
    int replace(int, int, const char*, int=0);
    
    /**
     Deletes the current selection.
     
     This function deletes the currently selected text
     \e without storing it in the clipboard. To use the clipboard,
     you may call copy() first or copy_cuts() after
     this call.
     
     \return 0 if no data was copied
     */
    int cut() {return replace(position(), mark(), 0);}
    
    /**
     Deletes the next \p n bytes rounded to characters before or after the cursor.
     
     This function deletes the currently selected text
     \e without storing it in the clipboard. To use the clipboard,
     you may call copy() first or copy_cuts() after
     this call.
     
     \param n number of bytes rounded to full characters and clamped to the buffer.
     A negative number will cut characters to the left of the cursor.
     \return 0 if no data was copied
     */
    int cut(int n) {return replace(position(), position()+n, 0);}
    
    /**
     Deletes all characters between index \p a and \p b.
     
     This function deletes the currently selected text
     \e without storing it in the clipboard. To use the clipboard,
     you may call copy() first or copy_cuts() after
     this call.
     
     \param a, b range of bytes rounded to full characters and clamped to the buffer
     \return 0 if no data was copied
     */
    int cut(int a, int b) {return replace(a, b, 0);}
    
    /**
     Inserts text at the cursor position.
     
     This function inserts the string in \p t at the cursor
     position() and moves the new position and mark to
     the end of the inserted text.
     
     \param [in] t text that will be inserted
     \param [in] l length of text, or 0 if the string is terminated by \c nul.
     \return 0 if no text was inserted
     */
    int insert(const char* t, int l=0){return replace(position_, mark_, t, l);}
    
    /* Put the current selection into the clipboard. */
    int copy(int clipboard);
    
    /* Undo previous changes to the text buffer. */
    int undo();
    
    /* Copy the yank buffer to the clipboard. */
    int copy_cuts();
    
    /** Return the shortcut key associated with this widget.
     \return shortcut keystroke
     \see fltk3::Button::shortcut() */
    int shortcut() const {return shortcut_;}
    
    /** 
     Sets the shortcut key associated with this widget.
     Pressing the shortcut key gives text editing focus to this widget.
     \param [in] s new shortcut keystroke 
     \see fltk3::Button::shortcut() 
     */
    void shortcut(int s) {shortcut_ = s;}
    
    /** Gets the font of the text in the input field.
     \return the current fltk3::Font index */
    fltk3::Font textfont() const {return textfont_;}
    
    /** Sets the font of the text in the input field.
     The text font defaults to \c fltk3::HELVETICA.
     \param [in] s the new text font */
    void textfont(fltk3::Font s) {textfont_ = s;}
    
    /** Gets the size of the text in the input field.
     \return the text height in pixels */
    fltk3::Fontsize textsize() const {return textsize_;}
    
    /** Sets the size of the text in the input field.
     The text height defaults to \c fltk3::NORMAL_SIZE.
     \param [in] s the new font height in pixel units */
    void textsize(fltk3::Fontsize s) {textsize_ = s;}
    
    /** Gets the color of the text in the input field.
     \return the text color
     \see textcolor(fltk3::Color) */
    fltk3::Color textcolor() const {return textcolor_;}
    
    /** Sets the color of the text in the input field.
     The text color defaults to \c fltk3::FOREGROUND_COLOR.
     \param [in] n new text color
     \see textcolor() */
    void textcolor(fltk3::Color n) {textcolor_ = n;}
    
    /** Gets the color of the cursor.  
     \return the current cursor color */
    fltk3::Color cursor_color() const {return cursor_color_;}
    
    /** Sets the color of the cursor.  
     The default color for the cursor is \c fltk3::BLACK.
     \param [in] n the new cursor color */
    void cursor_color(fltk3::Color n) {cursor_color_ = n;}
    
    /** Gets the input field type. 
     \return the current input type */
    int input_type() const {return type() & fltk3::INPUT_TYPE; }
    
    /** Sets the input field type. 
     A redraw() is required to reformat the input field.
     \param [in] t new input type */
    void input_type(int t) { type((uchar)(t | readonly())); }
    
    /** Gets the read-only state of the input field.  
     \return non-zero if this widget is read-only */
    int readonly() const { return type() & fltk3::INPUT_READONLY; }
    
    /** Sets the read-only state of the input field.  
     \param [in] b if \p b is 0, the text in this widget can be edited by the user */
    void readonly(int b) { if (b) type((uchar)(type() | fltk3::INPUT_READONLY));
      else type((uchar)(type() & ~fltk3::INPUT_READONLY)); }
    
    /**
     Gets  the word wrapping state of the input field. 
     Word wrap is only functional with multi-line input fields.
     */
    int wrap() const { return type() & fltk3::INPUT_WRAP; }
    
    /**
     Sets the word wrapping state of the input field. 
     Word wrap is only functional with multi-line input fields.
     */
    void wrap(int b) { if (b) type((uchar)(type() | fltk3::INPUT_WRAP));
      else type((uchar)(type() & ~fltk3::INPUT_WRAP)); }
    
    /**
     Sets whether the Tab key does focus navigation, 
     or inserts tab characters into fltk3::MultilineInput.
     
     By default this flag is enabled to provide the 'normal' behavior 
     most users expect; Tab navigates focus to the next widget. 
     To inserting an actual Tab character, users can use Ctrl-I
     or copy/paste.
     
     Disabling this flag gives the old FLTK behavior where Tab
     inserts a tab character into the text field, in which case
     only the mouse can be used to navigate to the next field.
     
     History: This flag was provided for backwards support of FLTK's old 1.1.x
     behavior where Tab inserts a tab character instead of navigating 
     focus to the next widget. This behavior was unique to fltk3::MultilineInput. 
     With the advent of fltk3::TextEditor, this old behavior has been deprecated.
     
     \param [in] val If \p val is 1, Tab advances focus (default).<BR>
     If \p val is 0, Tab inserts a tab character (old FLTK behavior).
     */
    void tab_nav(int val) {
      tab_nav_ = val;
    }
    
    /**
     Gets whether the Tab key causes focus navigation in multiline input fields or not.
     
     If enabled (default), hitting Tab causes focus navigation to the next widget.
     
     If disabled, hitting Tab inserts a tab character into the text field.
     \returns 1 if Tab advances focus (default), 0 if Tab inserts tab characters.
     \see tab_nav(int)
     */
    int tab_nav() const {
      return tab_nav_;
    }
  };
  
}

#endif 

//
// End of "$Id: Input_.h 8068 2010-12-20 07:48:59Z greg.ercolano $".
//
