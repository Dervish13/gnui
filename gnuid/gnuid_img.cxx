//
// "$Id"
//
// gnuid_img merge all the gnuid xpm into one table
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

#include <pixmaps/gnuid/lock.xpm>
#include <pixmaps/gnuid/flWindow.xpm>
#include <pixmaps/gnuid/flButton.xpm>
#include <pixmaps/gnuid/flCheckButton.xpm>
#include <pixmaps/gnuid/flRoundButton.xpm>
#include <pixmaps/gnuid/flBox.xpm>
#include <pixmaps/gnuid/flGroup.xpm>
#include <pixmaps/gnuid/flFunction.xpm>
#include <pixmaps/gnuid/flCode.xpm>
#include <pixmaps/gnuid/flCodeBlock.xpm>
#include <pixmaps/gnuid/flComment.xpm>
#include <pixmaps/gnuid/flDeclaration.xpm>
#include <pixmaps/gnuid/flDeclarationBlock.xpm>
#include <pixmaps/gnuid/flClass.xpm>
#include <pixmaps/gnuid/flNamespace.xpm>
#include <pixmaps/gnuid/flTabs.xpm>
#include <pixmaps/gnuid/flInput.xpm>
#include <pixmaps/gnuid/flChoice.xpm>
#include <pixmaps/gnuid/flMenuitem.xpm>
#include <pixmaps/gnuid/flMenubar.xpm>
#include <pixmaps/gnuid/flSubmenu.xpm>
#include <pixmaps/gnuid/flScroll.xpm>
#include <pixmaps/gnuid/flTile.xpm>
#include <pixmaps/gnuid/flWizard.xpm>
#include <pixmaps/gnuid/flPack.xpm>
#include <pixmaps/gnuid/flReturnButton.xpm>
#include <pixmaps/gnuid/flLightButton.xpm>
#include <pixmaps/gnuid/flRepeatButton.xpm>
#include <pixmaps/gnuid/flMenuButton.xpm>
#include <pixmaps/gnuid/flOutput.xpm>
#include <pixmaps/gnuid/flTextDisplay.xpm>
#include <pixmaps/gnuid/flTextEdit.xpm>
#include <pixmaps/gnuid/flFileInput.xpm>
#include <pixmaps/gnuid/flBrowser.xpm>
#include <pixmaps/gnuid/flCheckBrowser.xpm>
#include <pixmaps/gnuid/flFileBrowser.xpm>
#include <pixmaps/gnuid/flClock.xpm>
#include <pixmaps/gnuid/flHelp.xpm>
#include <pixmaps/gnuid/flProgress.xpm>
#include <pixmaps/gnuid/flSlider.xpm>
#include <pixmaps/gnuid/flScrollBar.xpm>
#include <pixmaps/gnuid/flValueSlider.xpm>
#include <pixmaps/gnuid/flAdjuster.xpm>
#include <pixmaps/gnuid/flCounter.xpm>
#include <pixmaps/gnuid/flDial.xpm>
#include <pixmaps/gnuid/flRoller.xpm>
#include <pixmaps/gnuid/flValueInput.xpm>
#include <pixmaps/gnuid/flValueOutput.xpm>
#include <pixmaps/gnuid/flSpinner.xpm>
#include <pixmaps/gnuid/flWidgetClass.xpm>
//#include <pixmaps/file_small.xpm>
//#include <pixmaps/folder_save.xpm>
#include <pixmaps/file_small2.xpm>
#include <pixmaps/folder_small.xpm>
#include <pixmaps/book.xpm>
#include <pixmaps/recycle.xpm>

#include "gnuid_img.h"
#include <gnui/xpmImage.h>

using namespace gnui;

xpmImage	open_pixmap(folder_small);
xpmImage	new_pixmap(file_small2);
xpmImage	write_pixmap(book);
xpmImage	save_pixmap(book);
xpmImage	saveas_pixmap(book);
xpmImage	merge_pixmap(recycle_xpm);
xpmImage	exit_pixmap(recycle_xpm);

static xpmImage	lock_pixmap(lock_xpm);
static xpmImage	window_pixmap(flWindow_xpm);
static xpmImage	button_pixmap(flButton_xpm);
static xpmImage	checkbutton_pixmap(flCheckButton_xpm);
static xpmImage	roundbutton_pixmap(flRoundButton_xpm);
static xpmImage	box_pixmap(flBox_xpm);
static xpmImage	group_pixmap(flGroup_xpm);
static xpmImage	function_pixmap(flFunction_xpm);
static xpmImage	code_pixmap(flCode_xpm);
static xpmImage	codeblock_pixmap(flCodeBlock_xpm);
static xpmImage	comment_pixmap(flComment_xpm);
static xpmImage	declaration_pixmap(flDeclaration_xpm);
static xpmImage	declarationblock_pixmap(flDeclarationBlock_xpm);
static xpmImage	class_pixmap(flClass_xpm);
static xpmImage	namespace_pixmap(flNamespace_xpm);
static xpmImage	tabs_pixmap(flTabs_xpm);
static xpmImage	input_pixmap(flInput_xpm);
static xpmImage	choice_pixmap(flChoice_xpm);
static xpmImage	menuitem_pixmap(flMenuitem_xpm);
static xpmImage	menubar_pixmap(flMenubar_xpm);
static xpmImage	submenu_pixmap(flSubmenu_xpm);
static xpmImage	scroll_pixmap(flScroll_xpm);
static xpmImage	tile_pixmap(flTile_xpm);
static xpmImage	wizard_pixmap(flWizard_xpm);
static xpmImage	pack_pixmap(flPack_xpm);
static xpmImage	returnbutton_pixmap(flReturnButton_xpm);
static xpmImage	lightbutton_pixmap(flLightButton_xpm);
static xpmImage	repeatbutton_pixmap(flRepeatButton_xpm);
static xpmImage	menubutton_pixmap(flMenuButton_xpm);
static xpmImage	output_pixmap(flOutput_xpm);
static xpmImage	textdisplay_pixmap(flTextDisplay_xpm);
static xpmImage	textedit_pixmap(flTextEdit_xpm);
static xpmImage	fileinput_pixmap(flFileInput_xpm);
static xpmImage	browser_pixmap(flBrowser_xpm);
static xpmImage	checkbrowser_pixmap(flCheckBrowser_xpm);
static xpmImage	filebrowser_pixmap(flFileBrowser_xpm);
static xpmImage	clock_pixmap(flClock_xpm);
static xpmImage	help_pixmap(flHelp_xpm);
static xpmImage	progress_pixmap(flProgress_xpm);
static xpmImage	slider_pixmap(flSlider_xpm);
static xpmImage	scrollbar_pixmap(flScrollBar_xpm);
static xpmImage	valueslider_pixmap(flValueSlider_xpm);
static xpmImage	adjuster_pixmap(flAdjuster_xpm);
static xpmImage	counter_pixmap(flCounter_xpm);
static xpmImage	dial_pixmap(flDial_xpm);
static xpmImage	roller_pixmap(flRoller_xpm);
static xpmImage	valueinput_pixmap(flValueInput_xpm);
static xpmImage	valueoutput_pixmap(flValueOutput_xpm);
static xpmImage	spinner_pixmap(flSpinner_xpm);
static xpmImage	widgetclass_pixmap(flWidgetClass_xpm);

xpmImage * gnuid_pixmap[] = { 
 0, &window_pixmap, &button_pixmap, &checkbutton_pixmap, &roundbutton_pixmap, /* 0..4 */
 &box_pixmap, &group_pixmap, &function_pixmap, &code_pixmap, &codeblock_pixmap, &declaration_pixmap, /* 5..10 */ 
 &declarationblock_pixmap, &class_pixmap, &tabs_pixmap, &input_pixmap, &choice_pixmap,               /* 11..15 */
 &menuitem_pixmap, &menubar_pixmap, &submenu_pixmap, &scroll_pixmap, &tile_pixmap, &wizard_pixmap,   /* 16..21 */
 &pack_pixmap, &returnbutton_pixmap, &lightbutton_pixmap, &repeatbutton_pixmap, &menubutton_pixmap,  /* 22..26 */
 &output_pixmap, &textdisplay_pixmap, &textedit_pixmap, &fileinput_pixmap, &browser_pixmap,          /* 27..32 */
 &checkbrowser_pixmap, &filebrowser_pixmap, &clock_pixmap, &help_pixmap, &progress_pixmap,	     /* 33..36 */
 &slider_pixmap, &scrollbar_pixmap, &valueslider_pixmap, &adjuster_pixmap, &counter_pixmap,          /* 37..41 */
 &dial_pixmap, &roller_pixmap, &valueinput_pixmap, &valueoutput_pixmap, &comment_pixmap,             /* 42..46 */
 &spinner_pixmap, &widgetclass_pixmap,&namespace_pixmap /* 47..49 */ 
};

// End of "$Id"
