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
 * main-menu implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-11-08 EY
 * 2) Add multi language support. ------------------------- 2008-02-22 JChen
 *
 */
#include <QFont>
#include <QFileInfo>
#include <QPixmapCache>
#include <QProcess>
#include <QTextStream>
#include <QtDebug>
#include <QModelIndex>
#include "mainmenu.h"

#define ROOTMENU_PREFIX        "/etc/menu/Root"
#define ROOTMENU_POSTFIX	".menu"

MainMenu::MainMenu(QWidget *parent) 
{
	QString menuFile ;

	menuFile = ROOTMENU_PREFIX ;
	menuFile.append(ROOTMENU_POSTFIX) ;

	setupUi(this); 

	model = new FileBasedMenuModel(this);
	model->loadFromFile(menuFile);
	logoLabel->setVisible(true);
	titleLabel->setVisible(false);

	listView->setModel(model);
	listView->setFocus();
	listView->setCurrentIndex(model->index(0,0));

	setupConnections();

	contextMenu = new QMenu(this);
	QFont myfont = font();
	myfont.setPointSize(20);
	contextMenu->setFont(myfont);

	QAction *rebootAction = new QAction(tr("System Reboot"),this);
	connect(rebootAction,SIGNAL(triggered()),this,SLOT(onRebootAction()));
	contextMenu->addAction(rebootAction);
}

MainMenu::~MainMenu()
{
	if(model)
		delete model;
	if(contextMenu)
		delete contextMenu;
}

void MainMenu::setupConnections()
{
	connect(listView,SIGNAL(currentItemMoved(int)),this,SLOT(changeIconLabel(int)));
}

void MainMenu::changeIconLabel(int row)
{
    QModelIndex index = model->index( row , 0, QModelIndex());

    QPixmap pixmap;
    QString imageName = model->data(index, FileBasedMenuModel::IconRole).toString();
    if (!QPixmapCache :: find(imageName , pixmap))
    {
        pixmap = QPixmap(imageName).scaled(menuiconLabel->size());
        QPixmapCache::insert (imageName, pixmap);
    }
    menuiconLabel->setPixmap(pixmap);
}

void MainMenu::keyPressEvent(QKeyEvent *e)
{
	QString command;
	bool subMenu;

	if(e->isAutoRepeat())
	{
		if(e->key() != Qt::Key_Up && e->key() != Qt::Key_Down &&
		   e->key() != Qt::Key_PageUp && e->key() != Qt::Key_PageDown && e->key() != Qt::Key_HomePage)
		{
			return;
		}
	}

	switch(e->key())
	{
		case Qt::Key_Right:
		case Qt::Key_Enter:
		case Qt::Key_Return:
			command = model->data(model->index(listView->currentIndex().row(), 0), FileBasedMenuModel::CommandRole).toString();
			subMenu = model->data(model->index(listView->currentIndex().row(), 0), FileBasedMenuModel::SubmenuRole).toBool();

			runMenuCommand(command);
			break;
		case Qt::Key_HomePage:
			break;
		case Qt::Key_MediaRecord:
			break;
		case Qt::Key_Menu:
			contextMenu->show();
			break;
		case Qt::Key_Help:
			break;
		case Qt::Key_F12:
			break;
		case Qt::Key_Escape:
		case Qt::Key_Left:
			break;
		default:
		        break;
	}

}

void MainMenu::runMenuCommand(const QString &command)
{
	qDebug() << "Running Menu Command:" << command;
	QProcess *process = new QProcess;
	process->start(command);
	process->waitForFinished();
}

// When language changes simply bring down the application. NWM will restart

void MainMenu::onRebootAction()
{
	QProcess process;
	process.start("reboot");
	
}
