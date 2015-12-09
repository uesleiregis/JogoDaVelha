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

#ifndef GAME_H
#define GAME_H

#include "main.h"

#include <QList>
#include <QTime>
#include <QPoint>
#include <QObject>
#include <QVector>

class Player;
class PlayBoard;
class MainWindow;

class Game : public QObject {
    Q_OBJECT

    public:
        class Square {
            public:
                Square() : m_player(NULL), m_isWinning(false) { };
                Square(Player *pl) : m_player(pl), m_isWinning(false) { };
                Square(const Square& from) : m_player(from.m_player), m_isWinning(false) { };

                Square& operator= (Player *pl) {
                    m_player = pl;
                    return *this;
                };
                Square& operator= (const Square& from) {
                    if(this != &from) {
                        m_player = from.m_player;
                        m_isWinning = from.m_isWinning;
                    }
                    return *this;
                };

                operator Player* () {
                    return m_player;
                };
                operator const Player* () const {
                    return m_player;
                };

                Player *operator-> () {
                    return m_player;
                };
                const Player *operator-> () const {
                    return m_player;
                };

                bool isWinning() const {
                    return m_isWinning;
                };
                void setWinning(bool v = true) {
                    m_isWinning = v;
                };

            private:
                Player *m_player;
                bool m_isWinning;
        };

        Game(int = DEFAULT_BOARD_SIZE, int = DEFAULT_TIME_LIMIT, int = DEFAULT_WIN_STONES,
             const QVector<Player*>& = QVector<Player*>(), QObject* = NULL);

        ~Game();

        Player *incActualPlayer();
        Player *actualPlayer() const;
        void setActualPlayerIndex(int i) {
            m_actualPlayerIndex = i;
        };

        QVector<Player*>& players() {
            return m_players;
        };
        const QVector<Player*>& players() const {
            return m_players;
        };
        void setPlayers(const QVector<Player*>&);
        void unsetPlayers();

        QVector< QVector<Square> >& squareBoard() {
            return m_squareBoard;
        };
        const QVector< QVector<Square> >& squareBoard() const {
            return m_squareBoard;
        };
        Square& square(int x, int y) {
            return m_squareBoard[y][x];
        };
        const Square& square(int x, int y) const {
            return m_squareBoard[y][x];
        };
        int squareBoardSize() const {
            return m_squareCount;
        };
        void setSquareBoardSize(int);

        int winStonesCount() const {
            return m_toWin;
        };
        void setWinStonesCount(int c) {
            m_toWin = c;
        };

        bool isRunning() const {
            return m_isRunning;
        };

        bool isPaused() const {
            return m_isPaused;
        };


        void timerEvent(QTimerEvent*);

    public slots:
        void fillSquare(int, int, Player*);
        void testWinner(int, int, Player*);
        void processActualPlayer(int, int);

        void startGame(const QVector<Player*>&);
        void startGame();
        void pauseGame(bool = true);
        void unpauseGame() {
            pauseGame(false);
        };
        void stopGame();
        void resetGame();

        void resetTimer(int = -1);
        void stopTimer();

    signals:
        void squareBoardUpdated(int = WHOLE, int = WHOLE, Player* = NULL);

        void playerChanged(Player*);

        void gameStarted(Player*);

        void gameEnded(Player* = NULL);

        void gamePaused(bool = true);
        void gameUnpaused();

        void playerProcessStarted();
        void playerProcessEnded();

        void timerUpdated(int);

    private:        
        QVector<Player*> m_players;

        int m_actualPlayerIndex;

        QVector< QVector<Square> > m_squareBoard;

        bool m_isRunning;

        bool m_isPaused;

        int m_squareCount;

        int m_timeLimit;

        int m_actuTimeLimit;

        int m_timerID;

        QTime m_lastTime;

        int m_toWin;
};

#endif
