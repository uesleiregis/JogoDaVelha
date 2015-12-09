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

#ifndef PLAYBOARD_H
#define PLAYBOARD_H

#include "main.h"

#include <QTimer>
#include <QWidget>

class Game;
class Player;


class PlayBoard : public QWidget {
    Q_OBJECT

    public:


        PlayBoard(Game* = NULL, QWidget* = NULL);


        virtual ~PlayBoard() { };


        QPoint squareCoords(int, int);
        QPoint arrayCoords(int, int);


        void mouseReleaseEvent(QMouseEvent*);

        void resizeEvent(QResizeEvent*);

        void paintEvent(QPaintEvent*);

        Game *game() {
            return m_game;
        };
        const Game *game() const {
            return m_game;
        };

        bool isClickEnabled() const {
            return m_clickEnabled;
        };

        bool isRunning() const {
            return m_isRunning;
        };

    public slots:
        void enableClick(bool v = true) {
            m_clickEnabled = v;
        };
        void disableClick() {
            enableClick(false);
        };

        void startBoard();
        void stopBoard();

        void repaint(int, int);

        void setGame(Game*);
        void unsetGame();

    signals:
        void squareClicked(int, int);

    private:
        Game *m_game;

        bool m_clickEnabled;

        bool m_isRunning;

        int m_sideSize;

        int m_fromLeft;
        int m_fromTop;
};

#endif
