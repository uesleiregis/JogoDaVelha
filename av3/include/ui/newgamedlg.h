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

#ifndef NEWGAMEDLG_H
#define NEWGAMEDLG_H

#include "main.h"

#include <QHash>
#include <QList>
#include <QVector>
#include <QWizard>

class Game;
class PlayerCreatorBase;

class QLabel;
class QSpinBox;
class QLineEdit;
class QComboBox;
class QWizardPage;
class QVBoxLayout;
class QScrollArea;


class NewPlayerWidget : public QWidget {
    Q_OBJECT

    public:
        NewPlayerWidget(QWidget* = NULL);
        ~NewPlayerWidget() { };

        PlayerCreatorBase *creator() {
            return m_actualCreator;
        };
        const PlayerCreatorBase *creator() const {
            return m_actualCreator;
        };

    public slots:
        void setActualCreator(int);

    private:

        QComboBox *m_playerCreators;

        PlayerCreatorBase *m_actualCreator;


        QVBoxLayout *m_mainLayout;
};

class NewGameDialog : public QWizard {
    Q_OBJECT

    public:

        NewGameDialog(QWidget* = NULL);


        ~NewGameDialog();


        bool validateCurrentPage();

    public slots:

        void createNewGame();


        void addInitialPage();
        void addPlayersPage();


        void fillPlayersPage(int);

    signals:
        void newGameCreated(Game*);

    private:

        QSpinBox *m_playersCount;
        QSpinBox *m_signsCountToWin;
        QSpinBox *m_boardSize;
        QLineEdit *m_timeLimit;

        QWizardPage *m_playersPage;
        QScrollArea *m_scrollArea;
        QWidget *m_scrollWidget;
        QVector<NewPlayerWidget*> m_newPlayerWidgets;
};

#endif
