// "$Id:"
//
// Subclasses of FluidType for each type of Widget in GNUI.
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

// This file needs to be split up into important subclasses that are
// used by multiple files. Many of these subclasses are only used by
// the gnuid_menus file and should just be imbedded in there.

#ifndef gnui_widget_type_h
#define gnui_widget_type_h

#include <gnui/Box.h>
#include <gnui/TabGroup.h>
#include <gnui/WizardGroup.h>
#include <gnui/PopupMenu.h>
#include <gnui/Choice.h>
#include <gnui/MenuBar.h>
#include <gnui/InputBrowser.h>
#include <gnui/FileBrowser.h>
#include <gnui/Divider.h>
#include <gnui/InvisibleBox.h>
#include <gnui/Button.h>
#include <gnui/ReturnButton.h>
#include <gnui/RepeatButton.h>
#include <gnui/LightButton.h>
#include <gnui/CheckButton.h>
#include <gnui/RadioButton.h>
#include <gnui/Clock.h>
#include <gnui/Adjuster.h>
#include <gnui/Dial.h>
#include <gnui/ThumbWheel.h>
#include <gnui/TextDisplay.h>
#include <gnui/TextEditor.h>
#include <gnui/FileInput.h>
#include <gnui/ProgressBar.h>
#include <gnui/Scrollbar.h>
#include <gnui/Output.h>
#include <gnui/ValueInput.h>
#include <gnui/ValueOutput.h>
#include <gnui/ValueSlider.h>
#include <gnui/BarGroup.h>
#include <gnui/StatusBarGroup.h>
#include <gnui/HelpView.h>
#include <gnui/Item.h>
#include "GroupType.h"

class InvisibleBoxType : public WidgetType {
 public:
  virtual const char *type_name() const {return "gnui::InvisibleBox";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::InvisibleBox(x,y,w,h,0);}
  WidgetType *_make() {return new InvisibleBoxType();}
  int pixmapID() { return 5; }
};

extern const Enumeration buttontype_menu[];
class ButtonType : public WidgetType {
  const Enumeration *subtypes() const {return buttontype_menu;}
 public:
  virtual const char *type_name() const {return "gnui::Button";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Button(x,y,w,h,"button");}
  WidgetType *_make() {return new ButtonType();}
  int is_button() const {return 1;}
  int pixmapID() { return 2; }
};

class ReturnButtonType : public ButtonType {
 public:
  virtual const char *type_name() const {return "gnui::ReturnButton";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::ReturnButton(x,y,w,h,0);}
  WidgetType *_make() {return new ReturnButtonType();}
  int pixmapID() { return 23; }
};

class RepeatButtonType : public WidgetType {
 public:
  virtual const char *type_name() const {return "gnui::RepeatButton";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::RepeatButton(x,y,w,h,0);}
  WidgetType *_make() {return new RepeatButtonType();}
  int pixmapID() { return 25; }
};

class CheckButtonType : public ButtonType {
 public:
  virtual const char *type_name() const {return "gnui::CheckButton";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::CheckButton(x,y,w,h,"button");}
  WidgetType *_make() {return new CheckButtonType();}
  int pixmapID() { return 3; }
};

class LightButtonType : public ButtonType {
 public:
  virtual const char *type_name() const {return "gnui::LightButton";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::LightButton(x,y,w,h,"button");}
  WidgetType *_make() {return new LightButtonType();}
  int pixmapID() { return 24; }
};

class RadioButtonType : public ButtonType {
 public:
  virtual const char *type_name() const {return "gnui::RadioButton";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::RadioButton(x,y,w,h,"button");}
  WidgetType *_make() {return new RadioButtonType();}
  int pixmapID() { return  4; }
};

extern const Enumeration input_type_menu[] ;

class InputType : public WidgetType {
  int is_input() const {return 1;}
  const Enumeration *subtypes() const {return input_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::Input";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::Input *o = new gnui::Input(x,y,w,h,"input:");
    o->value("Text Input");
    return o;
  }
  WidgetType *_make() {return new InputType();}
  int pixmapID() { return  14; }
};

class PackType : public GroupType {
  //const Enumeration *subtypes() const {return pack_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::PackedGroup";}
  WidgetType *_make() {return new PackType();}
  int pixmapID() { return  22; }
};

class TabsType : public GroupType {
 public:
  virtual const char *type_name() const {return "gnui::TabGroup";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::TabGroup *g = new gnui::TabGroup(x,y,w,h); g->resizable(0);
    gnui::Group::current(0); return g;}
  WidgetType *_make() {return new TabsType();}
  FluidType* click_test(int,int);
  void add_child(FluidType*, FluidType*);
  void remove_child(FluidType*);
  // live mode functionalities
  gnui::Widget* enter_live_mode(int top);
  int pixmapID() { return 13; }
};

class WizardGroupType : public GroupType {
 public:
  virtual const char *type_name() const {return "gnui::WizardGroup";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::WizardGroup(x,y,w,h);}
  WidgetType *_make() {return new WizardGroupType();}
  // live mode functionalities
  int pixmapID() { return 21; }
};

extern const Enumeration scroll_type_menu[];

class ScrollType : public GroupType {
  const Enumeration *subtypes() const {return scroll_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::ScrollGroup";}
  WidgetType *_make() {return new ScrollType();}
  int pixmapID() { return 19; }
};

class TileType : public GroupType {
 public:
  virtual const char *type_name() const {return "gnui::TiledGroup";}
  WidgetType *_make() {return new TileType();}
  int pixmapID() { return 20; }
};

class MenuType : public GroupType {
 public:
  int is_group() const {return 0;}
  MenuType() : GroupType() {}
  ~MenuType() {}
  FluidType* click_test(int x, int y);
  int pixmapID() { return -1; }
};

extern const Enumeration button_type_menu[];

class PopupMenuType : public MenuType {
  const Enumeration *subtypes() const {return button_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::PopupMenu";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::PopupMenu(x,y,w,h,"menu");}
  WidgetType *_make() {return new PopupMenuType();}
  int pixmapID() { return 26; }
};

extern const Enumeration input_browser_type_menu[];

class InputBrowserType : public MenuType {
  int is_input_browser() const {return 1;}
  const Enumeration *subtypes() const {return input_browser_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::InputBrowser";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::InputBrowser(x,y,w,h);
  }
  WidgetType *_make() {return new InputBrowserType();}
  int pixmapID() { return 15; }
};

extern const Enumeration browser_type_menu[];

class FileBrowserType : public WidgetType {
  const Enumeration *subtypes() const {return browser_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::FileBrowser";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::FileBrowser(x,y,w,h);
  }
  WidgetType *_make() {return new FileBrowserType();}
  int pixmapID() { return 33; }
};

class MenuBarType : public MenuType {
 public:
  virtual const char *type_name() const {return "gnui::MenuBar";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::MenuBar(x,y,w,h);}
  WidgetType *_make() {return new MenuBarType();}
  int pixmapID() { return 17; }
};

extern const Enumeration item_type_menu[];
class ItemType : public WidgetType {
 public:
  const Enumeration* subtypes() const {return item_type_menu;}
  const char* type_name() const {return "gnui::Item";}
  int is_menu_item() const {return 1;}
  int is_button() const {return 1;} // this gets shortcut to work
  gnui::Widget* widget(int x,int y,int w,int h);
  WidgetType *_make() {return new ItemType();}
  int pixmapID() { return 16; }
};

class DividerType : public WidgetType {
 public:
  const Enumeration* subtypes() const {return 0;}
  const char* type_name() const {return "gnui::Divider";}
  int is_menu_item() const {return 1;}
  gnui::Widget* widget(int x,int y,int w,int h) { return new gnui::Divider; }
  WidgetType *_make() {return new DividerType();}
  int pixmapID() { return 16; }
};

class SubmenuType : public GroupType {
 public:
  const Enumeration* subtypes() const {return 0;}
  const char* type_name() const {return "gnui::ItemGroup";}
  int is_menu_item() const {return 1;}
  gnui::Widget* widget(int x,int y,int w,int h);
  WidgetType *_make() {return new SubmenuType();}
  int pixmapID() { return 18; }
};

class ChoiceType : public MenuType {
 public:
  virtual const char *type_name() const {return "gnui::Choice";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Choice(x,y,w,h,"choice:");
  }
  WidgetType *_make() {return new ChoiceType();}
  int pixmapID() { return 15; }
};

class BrowserType : public MenuType {
  const Enumeration *subtypes() const {return browser_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::Browser";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Browser(x,y,w,h);
  }
  WidgetType *_make() {return new BrowserType();}
  int pixmapID() { return 31; }
};

class ClockType : public WidgetType {
 public:
  virtual const char *type_name() const {return "gnui::Clock";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Clock(x,y,w,h);}
  WidgetType *_make() {return new ClockType();}
  int pixmapID() { return 34; }
};

class AdjusterType : public WidgetType {
  int is_valuator() const {return 1;}
 public:
  virtual const char *type_name() const {return "gnui::Adjuster";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Adjuster(x,y,w,h);}
  WidgetType *_make() {return new AdjusterType();}
  int pixmapID() { return 40; }
};

extern const Enumeration dial_type_menu[];

class DialType : public WidgetType {
  const Enumeration *subtypes() const {return dial_type_menu;}
  int is_valuator() const {return 1;}
 public:
  virtual const char *type_name() const {return "gnui::Dial";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Dial(x,y,w,h);}
  WidgetType *_make() {return new DialType();}
  int pixmapID() { return 42; }
};

class ThumbWheelType : public WidgetType {
  int is_valuator() const {return 1;}
 public:
  virtual const char *type_name() const {return "gnui::ThumbWheel";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::ThumbWheel(x,y,w,h);
  }
  WidgetType *_make() {return new ThumbWheelType();}
  int pixmapID() { return 43; }
};

class TextDisplayType : public WidgetType {
  int textstuff(int w, gnui::Font* f, int& s, gnui::Color c);
 public:
  virtual void ideal_size(int &w, int &h) {
    gnui::TextDisplay *myo = (gnui::TextDisplay *)o;
    gnui::setfont(myo->textfont(), myo->textsize());
    h -= o->box()->dh();
    w -= o->box()->dw();
    int ww = (int) gnui::getwidth("m");
    w = ((w + ww - 1) / ww) * ww + o->box()->dw();
    h = (int) (((h + gnui::getascent() - 1) / gnui::getascent() ) * gnui::getascent() +
               o->box()->dh());
    if (h < 30) h = 30;
    if (w < 50) w = 50;
  }
  virtual const char *type_name() const {return "gnui::TextDisplay";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::TextDisplay *myo = new gnui::TextDisplay(x,y,w,h);
    myo->box(gnui::DOWN_BOX);
    return myo;
  }
  WidgetType *_make() {return new TextDisplayType();}
  int pixmapID() { return 28; }
};

class TextEditorType : public WidgetType {
  int textstuff(int w, gnui::Font* f, int& s, gnui::Color c);
 public:
  virtual void ideal_size(int &w, int &h) {
    gnui::TextEditor *myo = (gnui::TextEditor *)o;
    gnui::setfont(myo->textfont(), myo->textsize());
    h -= o->box()->dh();
    w -= o->box()->dw();
    int ww = (int)gnui::getwidth("m");
    w = ((w + ww - 1) / ww) * ww + o->box()->dw();
    h = (int) (((h + gnui::getascent() - 1) / gnui::getascent()) * gnui::getascent() +
               o->box()->dh());
    if (h < 30) h = 30;
    if (w < 50) w = 50;
  }
  virtual const char *type_name() const {return "gnui::TextEditor";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::TextEditor *myo = new gnui::TextEditor(x,y,w,h);
    return myo;
  }
  WidgetType *_make() {return new TextEditorType();}
  int pixmapID() { return 29; }
};

class FileInputType: public WidgetType {
  gnui::Item *subtypes() {return 0;}
  int textstuff(int w,gnui::Font* f, int& s, gnui::Color c);
 public:
  virtual void ideal_size(int &w, int &h) {
    gnui::FileInput *myo = (gnui::FileInput *)o;
    gnui::setfont(myo->textfont(), myo->textsize());
    h = (int) (gnui::getdescent() + myo->textsize() + 4);
    w -= o->box()->dw();
    int ww = (int)gnui::getwidth("m",1);
    w = ((w + ww - 1) / ww) * ww + o->box()->dw();
    if (h < 20) h = 20;
    if (w < 50) w = 50;
  }
  virtual const char *type_name() const {return "gnui::FileInput";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::FileInput *myo = new gnui::FileInput(x,y,w,h,"file:");
    myo->value("/now/is/the/time/for/a/filename.ext");
    return myo;
  }
  WidgetType *_make() {      return new FileInputType();  }
  int pixmapID() { return 30; }
};

class HelpViewType : public WidgetType {
 public:
  void ideal_size(int &w, int &h) {
    gnui::HelpView *myo = (gnui::HelpView *)o;
    gnui::setfont(myo->textfont(), (float) myo->textsize());
    h -= o->box()->dh();
    w -= o->box()->dw();
    int ww = (int) gnui::getwidth("m");
    w = ((w + ww - 1) / ww) * ww + o->box()->dw();
    h = (int) (((h + gnui::getascent() - 1) / gnui::getascent() ) * gnui::getascent() +
               o->box()->dh());
    if (h < 30) h = 30;
    if (w < 50) w = 50;
  }
  const char *type_name() const {return "gnui::HelpView";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::HelpView *myo = new gnui::HelpView(x,y,w,h);
    myo->value("<HTML><BODY><H1>HelpView Widget</H1>"
               "<P>This is a HelpView widget.</P></BODY></HTML>");
    return myo;}
  WidgetType *_make() {return new HelpViewType();}
  int pixmapID() { return 35; }
};

class ProgressBarType : public WidgetType {
 public:
  virtual const char *type_name() const { return "gnui::ProgressBar"; }
  gnui::Widget* widget(int x, int y, int w, int h) {
    return new gnui::ProgressBar(x, y, w, h);
  }
  WidgetType *_make() { return new ProgressBarType(); }
  int pixmapID() { return 36; }
};

extern const Enumeration slider_type_menu[];

class SliderType : public WidgetType {
  const Enumeration *subtypes() const {return slider_type_menu;}
  int is_valuator() const {return 2;}
 public:
  virtual const char *type_name() const {return "gnui::Slider";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Slider(x,y,w,h);
  }
  WidgetType *_make() {return new SliderType();}
  int pixmapID() { return 37; }
};

class ScrollbarType : public SliderType {
  const Enumeration *subtypes() const {return 0;}
 public:
  virtual const char *type_name() const {return "gnui::Scrollbar";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::Scrollbar(x,y,w,h);
  }
  WidgetType *_make() {return new ScrollbarType();}
  int pixmapID() { return 19; }
};

extern const Enumeration output_type_menu[];
class OutputType : public InputType {
  const Enumeration *subtypes() const {return output_type_menu;}
 public:
  virtual const char *type_name() const {return "gnui::Output";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    gnui::Output *o = new gnui::Output(x,y,w,h,"output:");
    o->value("Text Output");
    return o;
  }
  WidgetType *_make() {return new OutputType();}
};

class ValueInputType : public WidgetType {
 public:
  virtual const char *type_name() const {return "gnui::ValueInput";}
  int is_valuator() const {return 1;}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::ValueInput(x,y,w,h,"value:");
  }
  WidgetType *_make() {return new ValueInputType();}
  int pixmapID() { return 44; }
};

class ValueOutputType : public WidgetType {
 public:
  virtual const char *type_name() const {return "gnui::ValueOutput";}
  int is_valuator() const {return 1;}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::ValueOutput(x,y,w,h,"value:");
  }
  WidgetType *_make() {return new ValueOutputType();}
  int pixmapID() { return 45; }
};

class ValueSliderType : public SliderType {
 public:
  virtual const char *type_name() const {return "gnui::ValueSlider";}
  gnui::Widget* widget(int x,int y,int w,int h) {
    return new gnui::ValueSlider(x,y,w,h);
  }
  WidgetType *_make() {return new ValueSliderType();}
  int pixmapID() { return 39; }
};

class BarGroupType : public WidgetType {
 public:
  virtual const char *type_name() const { return "gnui::BarGroup"; }
  gnui::Widget* widget(int x, int y, int w, int h) {
    return new gnui::BarGroup(x, y, w, h);
  }
  WidgetType *_make() { return new BarGroupType(); }
  int pixmapID() { return 17; }
};

class StatusBarGroupType : public WidgetType {
 public:
  virtual const char *type_name() const { return "gnui::StatusBarGroup"; }
  gnui::Widget* widget(int x, int y, int w, int h) {
    return new gnui::StatusBarGroup(x, y, w, h);
  }
  WidgetType *_make() { return new StatusBarGroupType(); }
  int pixmapID() { return 5; } // no nice bitmap yet use the WidgetType one
};

#endif
// End of "$Id"
