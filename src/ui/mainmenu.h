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
 * MainMenu class definition
 *
 * REVISION:
 * 
 *
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QProcess>
#include <QMenu>
#include <QKeyEvent>
#include <QEvent>
#include <QSettings>

#include "ui_mainmenu.h"

#include "filebasedmenumodel.h"

class MainMenu : public QWidget,private Ui::MainMenu
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = 0);
       	~MainMenu();

private:
	void setupConnections();
	void keyPressEvent(QKeyEvent *);

	FileBasedMenuModel *model;
	QMenu *contextMenu;

	//settings
	QSettings settings;

private slots:
	void changeIconLabel(int index);
	void runMenuCommand(const QString &command);

	// Menu Action Items
	void onRebootAction();

};

#endif

