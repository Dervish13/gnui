// "$Id:"
//
// Stuff to build menus in the Fast Light toolkit Interface Designer (gnuid)
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
// Please report all bugs and problems on the following page:
//
//     http://www.gnui.org/str.php

#ifndef gnui_gnuid_menus_h
#define gnui_gnuid_menus_h

#include "FluidType.h"

namespace gnui {
    class MenuBar;
    class ItemGroup;
    class Item;
    class xpmImage;
};

gnui::MenuBar* build_hierarchy(gnui::MenuBar* menubar);
void fill_in_New_Menu(gnui::ItemGroup* menu);
gnui::Item* gnuidMenuItem(FluidType& wt,int n=-1);

const int MAX_HISTORY = 10; //!< maximum number of items in menu File
extern char absolute_history[MAX_HISTORY][1024];
extern char relative_history[MAX_HISTORY][1024];

extern gnui::Item *history_item[10],*undo_item[2],
    *iwidget_bin,*itooltip,*isource_view,*istatusbar, *ishow_overlay;
extern gnui::ItemGroup *newMenu;
extern gnui::MenuBar* Main_Menu;

#define DECL_MENUCBV(n) void n(Widget *, void *)
#define DECL_MENUCBL(n) void n(Widget *, long)
#define DECL_MENUCBV2(n,type) void n(type *, void *)
#define DECL_MENUCBL2(n,type) void n(type *, long)
#define IMPL_MENUCB(n) void n(Widget *, void *) {}

#endif
//
// End of "$Id"
//

