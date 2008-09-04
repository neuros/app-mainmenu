
TEMPLATE = app
TARGET = ../../build/main-menu
DEPENDPATH += .
INCLUDEPATH += .
RESOURCES += ../../resources/graphics/main-menu.qrc

menu.path = $$(INSTALL_MOD_PATH)/etc
menu.files = ../../resources/menu

target.path = $$(INSTALL_MOD_PATH)/usr/local/bin

INSTALLS += target menu

FORMS +=../forms/mainmenu.ui

# These are all the QT application headers. that are for THIS APPLICATION ONLY.
# External headers such as xmms or nmsd use the INCLUDEPATH

HEADERS += mainmenu.h  \
		nmenuitem.h \
		filebasedmenumodel.h
	   

# These are all the QT application source files. that are for THIS APPLICATION ONLY.

SOURCES += mainmenu.cpp \
		filebasedmenumodel.cpp \
		nmenuitem.cpp \
		main.cpp 


TRANSLATIONS+= ../../translations/main-menu_zh.ts \
		../../translations/main-menu_cn.ts \
		../../translations/main-menu_fr.ts \
		../../translations/main-menu_de.ts \
		../../translations/main-menu_es.ts \
		../../translations/main-menu_it.ts \
		../../translations/main-menu_pt.ts \
		../../translations/main-menu_nl.ts \
		../../translations/main-menu_pl.ts \
		../../translations/main-menu_ru.ts \
		../../translations/main-menu_sv.ts



QMAKE_CLEAN += ../../build/* ./Makefile
