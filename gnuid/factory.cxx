//
// "$Id$"
//
// Widget factory code for the Fast Light Tool Kit (GNUI).
//
// Type classes for most of the gnui widgets.  Most of the work
// is done by code in WidgetType.C.  Also a factory instance
// of each of these type classes.
//
// This file also contains the "new" menu, which has a pointer
// to a factory instance for every class (both the ones defined
// here and ones in other files)
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
//
#include <gnui/run.h>
#include <gnui/Group.h>
#include <gnui/MenuBuild.h>
#include <gnui/MenuBar.h>
#include <gnui/string.h>

#include <string.h>
#include <stdio.h>

#include "Enumeration.h"
#include "Widget_Types.h"
#include "Fluid_Plugins.h"
#include "gnuid_menus.h"
#include "undo.h"

using namespace gnui;

////////////////////////////////////////////////////////////////
const Enumeration buttontype_menu[] = {
  {"Normal", 0,		(void*)0},
  {"Toggle", "TOGGLE",	(void*)gnui::Button::TOGGLE},
  {"Radio",  "RADIO",	(void*)gnui::Button::RADIO},
  {0}};

const Enumeration input_type_menu[] = {
  {"Normal",	0,	(void*)Input::NORMAL},
  {"Numeric",	0,	(void*)6,			"gnui::NumericInput"},
  {"Float",	0,	(void*)1,			"gnui::FloatInput"},
  {"Int",	0,	(void*)2,			"gnui::IntInput"},
  {"Secret",	0,	(void*)Input::SECRET,		"gnui::SecretInput"},
  {"Multiline",	0,	(void*)Input::MULTILINE,	"gnui::MultiLineInput"},
  {"Wordwrap",	0,	(void*)Input::WORDWRAP,		"gnui::WordwrapInput"},
  {0}};

const Enumeration dial_type_menu[] = {
  {"Dot", 	0,	(void*)Dial::NORMAL},
  {"Line",	"LINE",	(void*)Dial::LINE},
  {"Fill",	"FILL",	(void*)Dial::FILL},
  {0}};

const Enumeration slider_type_menu[] = {
  {"Linear No ticks",	"LINEAR",	(void*)(gnui::Slider::LINEAR)},
  {"Linear Top/left ticks","TICK_ABOVE",(void*)(gnui::Slider::TICK_ABOVE)},
  {"Linear Bottom/right ticks","TICK_BELOW",(void*)(gnui::Slider::TICK_BELOW)},
  {"Linear Both ticks","TICK_BOTH", (void*)(gnui::Slider::TICK_BOTH)},

  {"Log No ticks",	"LOG",	(void*)(gnui::Slider::LOG)},
  {"Log Top/left ticks","LOG|gnui::Slider::TICK_ABOVE",(void*)(gnui::Slider::LOG|gnui::Slider::TICK_ABOVE)},
  {"Log Bottom/right ticks","LOG|gnui::Slider::TICK_BELOW",(void*)(gnui::Slider::LOG|gnui::Slider::TICK_BELOW)},
  {"Log Both ticks","LOG|gnui::Slider::TICK_BOTH", (void*)(gnui::Slider::LOG|gnui::Slider::TICK_BOTH)},
  {0}};

const Enumeration output_type_menu[] = {
  {"Normal",	0,	(void*)gnui::Output::NORMAL},
  {"Multiline",	0,	(void*)gnui::Output::MULTILINE, "gnui::MultiLineOutput"},
  {"Wordwrap",	0,	(void*)gnui::Output::WORDWRAP, "gnui::WordwrapOutput"},
  {0}};

////////////////////////////////////////////////////////////////
int TextEditorType::textstuff(int w, gnui::Font* f, int& s, gnui::Color c) {
    gnui::TextEditor *myo = (gnui::TextEditor*)(w==4 ? ((WidgetType*)factory)->o : o);
    switch (w) {
    case 4:
    case 0: f = myo->textfont(); s = (int) myo->textsize(); c = myo->textcolor(); break;
    case 1: myo->textfont(f); break;
    case 2: myo->textsize((float)s); break;
    case 3: myo->textcolor(c); break;
    }
    return 1;
}

int TextDisplayType::textstuff(int w, gnui::Font* f, int& s, gnui::Color c) {
  gnui::TextDisplay *myo = (gnui::TextDisplay*)(w==4 ? ((WidgetType*)factory)->o : o);
  switch (w) {
    case 4:
    case 0: f = myo->textfont(); s = (int) myo->textsize(); c = myo->textcolor(); break;
    case 1: myo->textfont(f); break;
    case 2: myo->textsize((float)s); break;
    case 3: myo->textcolor(c); break;
  }
  return 1;
}

int FileInputType::textstuff(int w, gnui::Font* f, int& s, gnui::Color c) {
    gnui::FileInput *myo = (gnui::FileInput*)(w==4 ? ((WidgetType*)factory)->o : o);
  switch (w) {
    case 4:
    case 0: f = myo->textfont(); s = (int) myo->textsize(); c = myo->textcolor(); break;
    case 1: myo->textfont(f); break;
    case 2: myo->textsize((float)s); break;
    case 3: myo->textcolor(c); break;
  }
  return 1;
}

////////////////////////////////////////////////////////////////

extern void select(FluidType *,int);

using namespace gnui;


//////////////////////////////////////////////////////////////////////

int reading_file;

// Recursive function for searching submenus:
static FluidType *FluidType_make(const char *tn, gnui::ItemGroup * menu) {
  FluidType *r = 0;
  gnui::Item * m=0;
  char menuName[128];
  int n;

  reading_file = 1; // makes labels be null

  if (!tn || strlen(tn)==0) 
      return 0;

  for (n = menu->children(); n--;) {
    gnui::Widget* w = menu->child(n);
    if (w->label() && w->is_group() && tn && *tn) {
	snprintf(menuName,sizeof(menuName),"%s/%s",w->label(),tn);
	m = (gnui::Item *) menu->find(menuName);
	if (m)  break;
      }
  }
  if (m && m->user_data())
    r = ((FluidType*)(m->user_data()))->make();

  reading_file = 0; // makes labels be null

  return r;
}

static struct {const char* oldname; const char* newname;} ntable[] = {
  {"submenu",		"gnui::ItemGroup"},
  {"menuitem",		"gnui::Item"},
  {"GNUI_Counter",	"gnui::ValueInput"},
  {"GNUI_Spinner",	"gnui::ValueInput"},
  {"GNUI_Tabs",		"gnui::TabGroup"},
  {"GNUI_Return_Button",	"gnui::ReturnButton"},
  {"gnui::EnterButton",	"gnui::ReturnButton"},
  {"GNUI_Menu_Button",	"gnui::PopupMenu"},
  {"GNUI_Box",		"gnui::InvisibleBox"},
  {"GNUI_Boxtype",	"gnui::InvisibleBoxType"},
  {"GNUI_Round_Button",	"gnui::RadioButton"},
  {"GNUI_Pack",		"gnui::PackedGroup"},
  {"GNUI_Tabs",		"gnui::TabGroup"},
  {"GNUI_Scroll",		"gnui::ScrollGroup"},
  {"GNUI_Bar",		"gnui::BarGroup"},
  {"GNUI_Roller",		"gnui::ThumbWheel"},
  {"GNUI_File_Browser",	"gnui::FileBrowser"},
  {"GNUI_Text_Display",	"gnui::TextDisplay"},
  {"GNUI_Text_Editor",	"gnui::TextEditor"},
  {"GNUI_Tile",		"gnui::TiledGroup"}
};

// Create a new type by name.
FluidType* FluidType::make(const char *tn) {
  // Translate gnui1.0 names into gnui.0 ones:
  const char* p = 0;
  // First try any of our direct translations:
  for (unsigned n = 0; n < sizeof(ntable)/sizeof(*ntable); n++) {
    if (!strcasecmp(ntable[n].oldname, tn)) {p = ntable[n].newname; break;}
  }
  char buffer[128];
  // Now try cooking old names into new ones:
  if (!p && !strncmp(tn, "GNUI_", 3)) {
    p = buffer;
    strcpy(buffer, "gnui::");
    char* q = buffer+6;
    for (const char* r = tn+3; *r; r++) if (*r != '_') *q++ = *r;
    *q = 0;
  } else if (!p) {
    p = tn;
  }
  // Now search the "new" menu for them
  return ::FluidType_make(p, newMenu);
}

////////////////////////////////////////////////////////////////

// Since I have included all the .h files, do this table here:

// This table is only used for back compatability with XForms fdesign files,
// there should be no need to add to it in future versions of gnuid.

struct symbol {const char *name; int value;};

static symbol table[] = {
  {"BLACK",	gnui::BLACK},
  {"RED",	gnui::RED},
  {"GREEN",	gnui::GREEN},
  {"YELLOW",	gnui::YELLOW},
  {"BLUE",	gnui::BLUE},
  {"MAGENTA",	gnui::MAGENTA},
  {"CYAN",	gnui::CYAN},
  {"WHITE",	gnui::WHITE},

  {"LCOL",		gnui::BLACK},
  {"COL1",		gnui::GRAY75},
  {"MCOL",		51},
  {"LEFT_BCOL",		55},
  {"TOP_BCOL",		53},
  {"BOTTOM_BCOL",	45},
  {"RIGHT_BCOL",	39},
  {"INACTIVE",		gnui::GRAY66},
  {"INACTIVE_COL",	gnui::GRAY66},
  {"FREE_COL1",		16},
  {"FREE_COL2",		17},
  {"FREE_COL3",		18},
  {"FREE_COL4",		19},
  {"FREE_COL5",		20},
  {"FREE_COL6",		21},
  {"FREE_COL7",		22},
  {"FREE_COL8",		23},
  {"FREE_COL9",		24},
  {"FREE_COL10",	25},
  {"FREE_COL11",	26},
  {"FREE_COL12",	27},
  {"FREE_COL13",	28},
  {"FREE_COL14",	29},
  {"FREE_COL15",	30},
  {"FREE_COL16",	31},
  {"TOMATO",		131},
  {"INDIANRED",		164},
  {"SLATEBLUE",		195},
  {"DARKGOLD",		84},
  {"PALEGREEN",		157},
  {"ORCHID",		203},
  {"DARKCYAN",		189},
  {"DARKTOMATO",	113},
  {"WHEAT",		174},

  {"ALIGN_CENTER",	gnui::ALIGN_CENTER},
  {"ALIGN_TOP",		gnui::ALIGN_TOP},
  {"ALIGN_BOTTOM",	gnui::ALIGN_BOTTOM},
  {"ALIGN_LEFT",	gnui::ALIGN_LEFT},
  {"ALIGN_RIGHT",	gnui::ALIGN_RIGHT},
  {"ALIGN_INSIDE",	gnui::ALIGN_INSIDE},
  {"ALIGN_TOP_LEFT",	 gnui::ALIGN_TOP | gnui::ALIGN_LEFT},
  {"ALIGN_TOP_RIGHT",	 gnui::ALIGN_TOP | gnui::ALIGN_RIGHT},
  {"ALIGN_BOTTOM_LEFT",	 gnui::ALIGN_BOTTOM | gnui::ALIGN_LEFT},
  {"ALIGN_BOTTOM_RIGHT", gnui::ALIGN_BOTTOM | gnui::ALIGN_RIGHT},
  {"ALIGN_CENTER|GNUI_ALIGN_INSIDE",	gnui::ALIGN_CENTER|gnui::ALIGN_INSIDE},
  {"ALIGN_TOP|GNUI_ALIGN_INSIDE",		gnui::ALIGN_TOP|gnui::ALIGN_INSIDE},
  {"ALIGN_BOTTOM|GNUI_ALIGN_INSIDE",	gnui::ALIGN_BOTTOM|gnui::ALIGN_INSIDE},
  {"ALIGN_LEFT|GNUI_ALIGN_INSIDE",	gnui::ALIGN_LEFT|gnui::ALIGN_INSIDE},
  {"ALIGN_RIGHT|GNUI_ALIGN_INSIDE",	gnui::ALIGN_RIGHT|gnui::ALIGN_INSIDE},
  {"ALIGN_INSIDE|GNUI_ALIGN_INSIDE",	gnui::ALIGN_INSIDE|gnui::ALIGN_INSIDE},
  {"ALIGN_TOP_LEFT|GNUI_ALIGN_INSIDE",	gnui::ALIGN_TOP|gnui::ALIGN_LEFT|gnui::ALIGN_INSIDE},
  {"ALIGN_TOP_RIGHT|GNUI_ALIGN_INSIDE",	gnui::ALIGN_TOP|gnui::ALIGN_RIGHT|gnui::ALIGN_INSIDE},
  {"ALIGN_BOTTOM_LEFT|GNUI_ALIGN_INSIDE",	gnui::ALIGN_BOTTOM|gnui::ALIGN_LEFT|gnui::ALIGN_INSIDE},
  {"ALIGN_BOTTOM_RIGHT|GNUI_ALIGN_INSIDE",gnui::ALIGN_BOTTOM|gnui::ALIGN_RIGHT|gnui::ALIGN_INSIDE},

  {"ALIGN_LEFT_TOP",	 gnui::ALIGN_TOP | gnui::ALIGN_LEFT},
  {"ALIGN_RIGHT_TOP",	 gnui::ALIGN_TOP | gnui::ALIGN_RIGHT},
  {"ALIGN_LEFT_BOTTOM",	 gnui::ALIGN_BOTTOM | gnui::ALIGN_LEFT},
  {"ALIGN_RIGHT_BOTTOM", gnui::ALIGN_BOTTOM | gnui::ALIGN_RIGHT},
  {"INVALID_STYLE",	 255},
  {"NORMAL_STYLE",	 0},
  {"BOLD_STYLE",	 1},
  {"ITALIC_STYLE",	 2},
  {"BOLDITALIC_STYLE",	 3},
  {"FIXED_STYLE",	 4},
  {"FIXEDBOLD_STYLE",	 5},
  {"FIXEDITALIC_STYLE",	 6},
  {"FIXEDBOLDITALIC_STYLE",  7},
  {"TIMES_STYLE",	 8},
  {"TIMESBOLD_STYLE",	 9},
  {"TIMESITALIC_STYLE",	 10},
  {"TIMESBOLDITALIC_STYLE",  11},
//   {"SHADOW_STYLE",	0x100
//   {"ENGRAVED_STYLE",	0x200
//   {"EMBOSSED_STYLE",	0x300
  {"TINY_SIZE",		8},
  {"SMALL_SIZE",	11},
  {"NORMAL_SIZE",	12},
  {"MEDIUM_SIZE",	18},
  {"LARGE_SIZE",	24},
  {"HUGE_SIZE",		32},
  {"DEFAULT_SIZE",	12},
  {"TINY_FONT",		8},
  {"SMALL_FONT",	11},
  {"NORMAL_FONT",	12},
  {"MEDIUM_FONT",	18},
  {"LARGE_FONT",	24},
  {"HUGE_FONT",		32},
  {"NORMAL_FONT1",	11},
  {"NORMAL_FONT2",	12},
  {"DEFAULT_FONT",	11},
  {"RETURN_END_CHANGED",0},
  {"RETURN_CHANGED",	1},
  {"RETURN_END",	2},
  {"RETURN_ALWAYS",	3},
  {"PUSH_BUTTON",	gnui::Button::TOGGLE},
  {"RADIO_BUTTON",	gnui::Button::RADIO},
  {"HIDDEN_BUTTON",	gnui::Button::HIDDEN},
  {"SELECT_BROWSER",	gnui::Browser::NORMAL},
  {"HOLD_BROWSER",	gnui::Browser::NORMAL},
  {"MULTI_BROWSER",	gnui::Browser::MULTI},
  //  {"SIMPLE_COUNTER",	gnui::Counter::SIMPLE},
  {"LINE_DIAL",		gnui::Dial::LINE},
  {"FILL_DIAL",		gnui::Dial::FILL},
  {"VERT_SLIDER",	gnui::Slider::LINEAR},
  {"HOR_SLIDER",	gnui::Slider::LINEAR},
  {"VERT_FILL_SLIDER",	gnui::Slider::LINEAR},
  {"HOR_FILL_SLIDER",	gnui::Slider::LINEAR},
  {"VERT_NICE_SLIDER",	gnui::Slider::LINEAR},
  {"HOR_NICE_SLIDER",	gnui::Slider::LINEAR},
};

#include <stdlib.h>

int lookup_fdesign(const char *name, int &v, int numberok) {
  if (name[0]=='F' && name[1]=='L' && name[2]=='_') name += 3;
  for (int i=0; i < int(sizeof(table)/sizeof(*table)); i++)
    if (!strcasecmp(name,table[i].name)) {v = table[i].value; return 1;}
  if (numberok) {
    char* p;
    v = strtol(name, &p, 0);
    if (!*p && p > name) return 1;
  }
  return 0;
}

//
// End of "$Id$".
//
