#ifndef FILEBASEDMENUMODEL_H
#define FILEBASEDMENUMODEL_H
/*
 *  Copyright(C) 2008 Neuros Technology International LLC. 
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
 * FileBasedMenuModel implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-02-20 nerochiaro
 *
 */
#include <QWidget>
#include <QAbstractItemView>
#include <QList>

#include "nmenuitem.h"

class FileBasedMenuModel : public QAbstractListModel
{
public:

	enum FileBasedMenuItemRoles
	{
		CommandRole = Qt::UserRole,
		IconRole,
		LeftIconRole,
		RightIconRole,
		FgColorRole,
		HLineRole,
		SubmenuRole,
		CaptionRole
	};

	explicit FileBasedMenuModel (QWidget *parent);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;

	bool loadFromFile(const QString &menuFilePath);
	const QString & getMenuPath();
	int getIndexOfCommand(QString command);
	const QString & getMenuTitle();

private:
	QString menuPath;
	QString menuTitle;
	QList<NMenuItem> listEntries;
};

#endif 
