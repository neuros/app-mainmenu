#ifndef NMENUITEM_H
#define NMENUITEM_H
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
 * NMenuItem implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-11-27 SZ
 *
 */
#include <QString>
#include <QColor>

class NMenuItem
{
public:
	NMenuItem(const QString &caption,const QString &lefticon,
			  const QString &righticon,bool isSubmenu = false, const QString &command = QString(""),
			  const int helpid = 0); 

	NMenuItem(const QString &caption,const QString &lefticon,
			   const QString &righticon,bool hLine, const QColor &color); 

	void setCaption(const QString &caption);
	void setLeftIcon ( const QString &lefticon ) ;
	void setRightIcon ( const QString &righticon);
	void setIsSubmenu ( bool flag );
	void setCommand ( const QString &command );
	void setFgColor(const QColor &color);
	void setHLine(bool flag);
	void setHelpId(int id);

	const QString caption( ) const;
	const QString leftIcon ( ) const;
	const QString rightIcon ( ) const;
	bool isSubmenu ( ) const;
	const QString command ( ) const;
	const QColor fgColor() const;
	bool hLine() const;
	int helpId() const;

private:
	QString Caption;
	QString Icon;
	QString RightIcon;
	bool SubMenu;
	QString Command;
	QColor Color;
	bool HLine;
	int HelpId;
};

#endif
