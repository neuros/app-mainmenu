/*
 *  Copyright(C) 2007 Neuros Technology International LLC. 
 *               <www.neurostechnology.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *  
 *
 *  This program is distributed in the hope that, in addition to its 
 *  original purpose to support Neuros hardware, it will be useful 
 *  otherwise, but WITHOUT ANY WARRANTY; without even the implied 
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ****************************************************************************
 *
 * MenuItemModel implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-11-27 SZ
 *
 */
#include "nmenuitem.h"

NMenuItem :: NMenuItem(const QString &caption,const QString &lefticon,
					   const QString &righticon,bool isSubmenu , const QString &command,
					   const int helpid )
: Caption (caption), Icon(lefticon) , RightIcon(righticon) , SubMenu(isSubmenu), 
Command(command), HelpId(helpid)
{
	HLine = false;
	Color = QColor();
};

NMenuItem::NMenuItem(const QString &caption,const QString &lefticon,
			   const QString &righticon,bool hLine, const QColor &color)
 : Caption(caption), Icon(lefticon), RightIcon(righticon)
{
	HLine = hLine;
	Color = color;
}

void NMenuItem::setFgColor(const QColor &color)
{
	Color = color;
}

void NMenuItem::setHLine(bool flag)
{
	HLine = flag;
}

void NMenuItem :: setCaption ( const QString &caption )
{
	Caption = caption;
}

void NMenuItem :: setLeftIcon ( const QString &lefticon )
{
	Icon = lefticon;
}

void NMenuItem :: setRightIcon ( const QString &righticon)
{
	RightIcon = righticon;
}

void NMenuItem :: setIsSubmenu ( bool flag )
{
	SubMenu = flag;
}

void NMenuItem :: setCommand ( const QString &command )
{
	Command = command;
}

void NMenuItem :: setHelpId ( const int id )
{
	HelpId = id;
}

const QString NMenuItem :: caption( ) const
{ 
	return Caption;
}

const QString NMenuItem :: leftIcon ( ) const 
{
	return Icon;
}

const QString NMenuItem :: rightIcon ( ) const
{
	return RightIcon;
}

bool NMenuItem :: isSubmenu ( ) const
{
	return SubMenu;
}

const QString NMenuItem :: command ( ) const
{
	return Command;
}

const QColor NMenuItem::fgColor() const
{
	return Color;
}

bool NMenuItem::hLine() const
{
	return HLine;
}

int NMenuItem::helpId() const
{
	return HelpId;
}
