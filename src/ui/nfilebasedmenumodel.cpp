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
 * FileBasedMenuModel implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-02-20 nerochiaro
 * 2) Add utf-8 on caption. --------------------------------2008-03-10 Jchen
 *
 */
#include <QTextCodec>
#include <QFileInfo>
#include "filebasedmenumodel.h"

FileBasedMenuModel::FileBasedMenuModel (QWidget *parent)
: QAbstractListModel(parent)
{
}

int FileBasedMenuModel::rowCount(const QModelIndex &parent) const
{
	if(parent.isValid())
		return 0;

	return listEntries.size();
}

QVariant FileBasedMenuModel::data(const QModelIndex &index, int role) const
{
	if(index.row() < 0 )
		return QVariant();

	if( listEntries.size() == 0 )
		return QVariant();

	if(role == Qt::DisplayRole || CaptionRole )
	{
	    QTextCodec *codec = QTextCodec::codecForName("UTF-8") ;
		return codec->toUnicode(listEntries.at(index.row()).caption( ).toUtf8());
	}

	else if(role == IconRole || LeftIconRole )
		return listEntries.at(index.row()).leftIcon ( );
	else if(role == RightIconRole )
		return listEntries.at(index.row()).rightIcon ( );
	else if(role == FgColorRole)
		return listEntries.at(index.row()).fgColor();
	else if(role == HLineRole)
		return listEntries.at(index.row()).hLine();
	else if(role == CommandRole)
		return listEntries.at(index.row()).command();
	else if(role == SubmenuRole)
		return listEntries.at(index.row()).isSubmenu();
	return QVariant();
}

bool FileBasedMenuModel :: loadFromFile(const QString &menuFilePath)
{
	QFile menuFile(menuFilePath);
	if(!menuFile.open(QFile::ReadOnly))	return false; //TODO: implement some error handling here.

	listEntries.clear();
	menuPath = menuFilePath;

	QTextStream stream(&menuFile);
	stream.setCodec("UTF-8");
	QString line;
	do // Each line is a menu item, fields separated by "|"
	{
		line = stream.readLine();
		QStringList fields = line.split("|", QString::SkipEmptyParts);
		QStringListIterator i(fields);

		QString caption, icon, righticon(":/neux/navright.gif"), type, command, helpid;

		if (fields.size() > 0) 
		{
			if (fields.at(0) == "Menu") 
			{
				for (int i = 1; i < fields.size(); i++) 
				{
					QString field = fields.at(i);
					int pos = field.indexOf("=");
					if (pos != -1) 
					{
						QString name = field.left(pos);
						if (name == "Title") menuTitle = field.mid(pos+1);
					}
				}
				continue;
			}
		}

		while(i.hasNext()) // Each field is Name=Value
		{
			QString field = i.next();
			int pos = field.indexOf("=");
			if(pos != -1)
			{
				QString name = field.left(pos);
				// Save the value only for the recognized fields
				if(name == "Name") caption = field.mid(pos+1);
				else if(name == "Icon")	icon = field.mid(pos+1);
				else if(name == "RightIcon")	righticon = field.mid(pos+1);
				else if(name == "Type")	type = field.mid(pos+1);
				else if(name == "Command") command = field.mid(pos+1);
				else if(name == "HelpId") helpid = field.mid(pos+1);
			}
		}

		// Create a menu item if at least the caption was found.
		if(!caption.isEmpty())
		{
			if (type == "MenuOpt")
			{
				QFileInfo f(command);
				if (f.exists()) listEntries << NMenuItem(caption, icon, righticon, true, command, helpid.isEmpty()?0:helpid.toInt());
			}
			else listEntries << NMenuItem(caption, icon, righticon, (type == "Menu"), command, helpid.isEmpty()?0:helpid.toInt());
		}

	} while(!line.isNull());

	return true;
}

const QString & FileBasedMenuModel::getMenuPath()
{
	return menuPath;
}

const QString & FileBasedMenuModel::getMenuTitle()
{
	return menuTitle;
}

int FileBasedMenuModel::getIndexOfCommand(QString command)
{
	for(int i = 0; i<listEntries.count(); i++)
		if(listEntries.at(i).command() == command)
			return i;
	return -1;
}


