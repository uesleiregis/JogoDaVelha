/*!
*   This program is free software; you can redistribute it and/or
*   modify it under the terms of the GNU General Public License as
*   published by the Free Software Foundation; either version 3 of the
*   License, or (at your option) any later version.

*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*   General Public License for more details:
*   http://www.gnu.org/licenses/gpl.txt
*/

#ifndef PLAYERCREATOR_H
#define PLAYERCREATOR_H

#include "main.h"

#include <QList>
#include <QWidget>

class Player;
class PlayerSign;
class PlayerCreatorBase;

class QLineEdit;
class QComboBox;
class QPushButton;
class QColorDialog;


class PlayerCreatorRegistrator {
    public:
        typedef PlayerCreatorBase *(*PlayerCreatorConstructor)();
        typedef QList< QPair<QString, PlayerCreatorConstructor> > PlayerCreatorsList;

        PlayerCreatorRegistrator(const QString&, PlayerCreatorConstructor);

        static PlayerCreatorsList& list() {
            return sm_allCreators;
        };

    private:
        static PlayerCreatorsList sm_allCreators;
};

class PlayerCreatorBase : public QWidget {
    Q_OBJECT

    public:
        PlayerCreatorBase(QWidget *pa = NULL) : QWidget(pa) { };
        virtual ~PlayerCreatorBase() { };

        static PlayerCreatorBase* createCreator() {
            return NULL;
        };

        virtual Player* createPlayer() = 0;
};

class PlayerCreator : public PlayerCreatorBase {
    Q_OBJECT

    public:
        PlayerCreator(QWidget* = NULL);
        virtual ~PlayerCreator();

        static PlayerCreatorBase* createCreator() {
            return new PlayerCreator;
        };

        virtual Player* createPlayer();

        const QColor& color() const {
            return m_color;
        };

    public slots:
        void startColorDialog();

        void changeColorButton(QColor);

        void refreshSignTypes();

        void incDecSings(int);

        void setColor(QColor c) {
            m_color = c;
        };

    private:
        QLineEdit *m_nameEdit;

        QComboBox *m_signType;

        QPushButton *m_colorButton;

        QColor m_color;

        int m_actuIndex;

        static PlayerCreatorRegistrator sm_register;
};

#endif
