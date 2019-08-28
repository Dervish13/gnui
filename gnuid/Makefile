#
# "$Id$"
#
# GNUID makefile for the Fast Light Tool Kit (GNUI).
#
# Copyright 1998-2003 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to the following page:
#
#    http://www.gnui.org/str.php
#

#
# Include common definitions...
#

include ../makeinclude


#
# Files for this directory...
#

CPPFILES = \
	CodeEditor.cxx \
	Enumeration.cxx \
	FluidType.cxx \
	Fluid_Image.cxx \
	Fluid_Plugins.cxx \
	FunctionType.cxx \
	GroupType.cxx \
	MenuType.cxx \
	WidgetClassType.cxx \
	WidgetType.cxx \
	WindowType.cxx \
	about_panel.cxx \
	align_widget.cxx \
	alignment_panel.cxx \
	code.cxx \
	coding_style.cxx \
	coding_style_func.cxx \
	factory.cxx \
	file.cxx \
	function_panel.cxx \
	gnuid.cxx \
	gnuid_img.cxx \
	gnuid_menus.cxx \
	template_panel.cxx \
	undo.cxx \
	widget_panel.cxx

CFILES	=

OBJECTS = $(CPPFILES:.cxx=.o) $(CFILES:.cxx=.o)
TARGETS	= gnuid$(EXEEXT)

#CXXFLAGS+=-g
#
# Make everything...
#

all:		$(TARGETS)


#
# Clean old files...
#

clean:
	$(RM) *.bck
	$(RM) *.o
	$(RM) core*
	$(RM) $(TARGETS)


#
# Make dependencies, excluding standard include directories...
#

depend:
	$(MAKEDEPEND) -I.. $(CPPFILES) $(CFILES) > makedepend


#
# Include automatically generated dependencies...
#

makedepend:
	touch makedepend
include makedepend


#
# Build shared GNUID...
#

gnuid$(EXEEXT): $(OBJECTS) ../lib/$(DSOPREFIX)gnui$(DSOSUFFIX) \
		../lib/$(DSOPREFIX)gnui_images$(DSOSUFFIX)
	echo Linking $@...
	echo $(LOCAL_IMAGELIBS)
	$(CXX) -L../lib $(CXXFLAGS) -o $@ $(OBJECTS) $(LINKSHARED) $(IMAGELIBS) $(LIBS) $(LDLIBS)
	$(POSTBUILD) $@ ../gnui/mac.r


#
# Install everything...
#

install:
	echo "Installing GNUID in $(bindir)..."
	-$(MKDIR) $(DESTDIR)$(bindir)
	$(CP) gnuid$(EXEEXT) $(DESTDIR)$(bindir)/gnuid$(EXEEXT)
	$(STRIP) $(DESTDIR)$(bindir)/gnuid$(EXEEXT)
	$(DESTDIR)$(bindir)/gnui-config --post $(DESTDIR)$(bindir)/gnuid$(EXEEXT)
	$(CHMOD) 755 $(DESTDIR)$(bindir)/gnuid$(EXEEXT)


uninstall:
	$(RM) $(bindir)/gnuid


#
# Note: The rebuild target can only be used if you have the original .fl
#       files.  This is normally only used by the GNUI maintainers...
#

rebuild:
	./gnuid$(EXEEXT) -c about_panel.fl
	./gnuid$(EXEEXT) -c alignment_panel.fl
	./gnuid$(EXEEXT) -c function_panel.fl
	./gnuid$(EXEEXT) -c widget_panel.fl
	./gnuid$(EXEEXT) -c coding_style.fl


#
# End of "$Id$".
#
