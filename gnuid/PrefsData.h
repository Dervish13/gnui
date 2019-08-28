// "$Id:"
//
// Preferences database for the Fast Light toolkit Interface Designer (gnuid)
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
//    http://www.gnui.org/str.php

#ifndef _gnui_PrefsData_h
#define _gnui_PrefsData_h
#include <gnui/Preferences.h>
#include <gnui/Color.h>
#include <gnui/string.h>

// Properties are not implemented in C++ so here's so macros defining them
// Note: a gnuid property is persistent,
#define GnuidProperty(type, p, name) \
public:	    type p() const {return p##_;} \
	    type * p##Ptr() {return &p##_;} \
            void p(const type v) {p##_=v; if(autosave_) set(name, p##_);} \
private:    type p##_

#define GnuidPropVect(type, size, p, name) \
public:	    const type* p() const {return p##_;} \
            void p(const type* v) {memcpy(p##_,v,size);if(autosave_) set(name, p##_);} \
private:    type p##_[size];

#define GnuidPropertyGroup(group, type, p, name) \
public:	    type p() const {return p##_;} \
	    type * p##Ptr() {return &p##_;} \
            void p(const type v) {p##_=v; if(autosave_) {gnui::Preferences g(this, group); g.set(name, p##_);}} \
private:    type p##_

#define GnuidPropVectGroup(type, size, p, name) \
public:	    const type* p() const {return p##_;} \
    void p(const type* v) {memcpy(p##_,v,size); if(autosave_) {gnui::Preferences g(this, group); g.set(name, p##_);}} \
private:    type p##_[size];

/** \class PrefsData
  Gnuid unified preferences data structure
  This class permit to unify all often used persistent
  gnuid data. It features the notion of 'property' which is
  not only an attribute, but has members and the 'set' part is persistent
  so that
  it makes not necessary to reload all the time the same data from the prefs
  as every 'set' is written automatically to the prefs file
  So not performance gain occurs now (it was quite acceptable before),
  it also greatly simplifies the design.
  All important persistant gnuid data should be declared here.
*/
class PrefsData : public gnui::Preferences {
    // 1. define your persistent property here
    GnuidProperty(int, gridx,"gridx");
    GnuidProperty(int, gridy,"gridy");
    GnuidProperty(int, snap,"snap");
    GnuidProperty(int, show_tooltip,"show_tooltips");
    GnuidProperty(int, open_previous_file,"open_previous_file");
    GnuidProperty(int, prev_window_pos,"prev_window_pos");
    GnuidProperty(int, show_completion_dialogs,"show_completion_dialogs");
    GnuidProperty(int, recent_files,"recent_files");
    GnuidPropVect(char, 1024, shell_command,"shell_command");
    GnuidProperty(int, shell_writecode,"shell_writecode");
    GnuidProperty(int, shell_writemsgs,"shell_writemsgs");
    GnuidProperty(int, shell_savegnui,"shell_savegnui");
    GnuidProperty(int, show_statusbar,"show_statusbar");
    GnuidProperty(int, show_splash,"show_splash");

    GnuidPropertyGroup("sourceview", int, sv_autorefresh,"autorefresh");
    GnuidPropertyGroup("sourceview", int, sv_autoposition,"autoposition");
    GnuidPropertyGroup("sourceview", int, sv_tab,"tab");

    GnuidPropertyGroup("tabs", int, tabcolor,"tabcolor");
    GnuidPropertyGroup("tabs", int, tabcolor1,"tabcolor1");
    GnuidPropertyGroup("tabs", int, tabcolor2,"tabcolor2");
    GnuidPropertyGroup("tabs", int, tabcolor3,"tabcolor3");

    // 2. initialize your persistent property here
    void get_all_properties() {
      get("gridx",gridx_, 5);
      get("gridy",gridy_, 5);
      get("snap",snap_, 3);
      get("show_tooltip",show_tooltip_, 1);
      get("open_previous_file", open_previous_file_, 0);
      get("prev_window_pos", prev_window_pos_, 1);
      get("show_completion_dialogs", show_completion_dialogs_, 1);
      get("recent_files", recent_files_, 5);
      get("shell_command", shell_command_, "", sizeof(shell_command_));
      get("shell_writecode", shell_writecode_, 1);
      get("shell_writemsgs", shell_writemsgs_, 0);
      get("shell_savegnui", shell_savegnui_, 1);
      get("show_statusbar", show_statusbar_, 1);
      get("show_splash",show_splash_,1);

      gnui::Preferences s(this, "sourceview");
      s.get("autorefresh",sv_autorefresh_,1);
      s.get("autoposition",sv_autoposition_,1);
      s.get("tab",sv_tab_,0);

      gnui::Preferences g(this,"tabs");
      g.get("tabcolor",tabcolor_, 1);
      g.get("tabcolor1",tabcolor1_, 0x14aef700);
      g.get("tabcolor2",tabcolor2_, 0xd4b38d00);
      g.get("tabcolor3",tabcolor3_, 0x93d49c00);

    }

    bool    autosave_;

private:
    void init() {autosave_=true; get_all_properties();}

public:
    PrefsData( Root root, const char *vendor, const char *application ):
	Preferences(root, vendor, application) {init();}
    //!avoid saving in the prefs when writing (for per-file prefs purpose)
    void autosave(bool a) {autosave_=a;}
};

extern PrefsData prefs; // GNUID preferences

#endif

//
// End of "$Id"
//
