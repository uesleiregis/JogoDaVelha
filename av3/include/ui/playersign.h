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

#ifndef PLAYERSIGN_H
#define PLAYERSIGN_H

#include <QList>
#include <QPair>
#include <QColor>
#include <QPixmap>

class PlayerSign;

class PlayerSignRegistrator {
    public:
        typedef PlayerSign *(*PlayerSignConstructor)();
        typedef QList< QPair<int, PlayerSignConstructor> > SignsList;

        PlayerSignRegistrator(PlayerSignConstructor);

        static void inc(int i, int n = 1) {
            sm_allSigns[i].first += n;
        };
        static void dec(int i) {
            inc(i, -1);
        };
        static SignsList& list() {
            return sm_allSigns;
        };

        static bool hasOverloadSign();

        static void resetSignsOwners();

    private:
        static SignsList sm_allSigns;
};

class PlayerSign {
    public:
        PlayerSign() { } ;
        virtual ~PlayerSign() { } ;

        virtual QPixmap signPixmap(const QWidget*, QPoint, int);

        static PlayerSign* createSign() {
            return new PlayerSign;
        };

        virtual bool isPainted() const {
            return false;
        };
};

class PaintedPlayerSign : public PlayerSign {
    public:
        PaintedPlayerSign() { };
        PaintedPlayerSign(const QColor&);
        PaintedPlayerSign(const PaintedPlayerSign&);
        virtual ~PaintedPlayerSign() { } ;

        PaintedPlayerSign& operator= (const PaintedPlayerSign&);

        QColor& color() {
            return m_color;
        };
        const QColor& color() const {
            return m_color;
        };
        void setColor(const QColor& col) {
            m_color = col;
        };

        virtual QPixmap signPixmap(const QWidget*, QPoint, int);

        virtual bool isPainted() const {
            return true;
        };

        static PlayerSign* createSign() {
            return new PaintedPlayerSign;
        };

    private:
        QColor m_color;
};

class CirclePlayerSign : public PaintedPlayerSign {
    public:
        CirclePlayerSign() { };
        CirclePlayerSign(const QColor&);
        CirclePlayerSign(const CirclePlayerSign&);
        virtual ~CirclePlayerSign() { } ;

        CirclePlayerSign& operator= (const CirclePlayerSign&);

        virtual QPixmap signPixmap(const QWidget*, QPoint, int);

        static PlayerSign* createSign() {
            return new CirclePlayerSign;
        };

    private:
        static PlayerSignRegistrator sm_register;
};

class CrossPlayerSign : public PaintedPlayerSign {
    public:
        CrossPlayerSign() { };
        CrossPlayerSign(const QColor&);
        CrossPlayerSign(const CrossPlayerSign&);
        virtual ~CrossPlayerSign() { } ;

        CrossPlayerSign& operator= (const CrossPlayerSign&);

        virtual QPixmap signPixmap(const QWidget*, QPoint, int);

        static PlayerSign* createSign() {
            return new CrossPlayerSign;
        };

    private:
        static PlayerSignRegistrator sm_register;
};

class TrinaglePlayerSign : public PaintedPlayerSign {
    public:
        TrinaglePlayerSign() { };
        TrinaglePlayerSign(const QColor&);
        TrinaglePlayerSign(const TrinaglePlayerSign&);
        virtual ~TrinaglePlayerSign() { } ;

        TrinaglePlayerSign& operator= (const TrinaglePlayerSign&);

        virtual QPixmap signPixmap(const QWidget*, QPoint, int);

        static PlayerSign* createSign() {
            return new TrinaglePlayerSign;
        };

    private:
        static PlayerSignRegistrator sm_register;
};

class SquarePlayerSign : public PaintedPlayerSign {
    public:
        SquarePlayerSign() { };
        SquarePlayerSign(const QColor&);
        SquarePlayerSign(const SquarePlayerSign&);
        virtual ~SquarePlayerSign() { } ;

        SquarePlayerSign& operator= (const SquarePlayerSign&);

        virtual QPixmap signPixmap(const QWidget*, QPoint, int);

        static PlayerSign* createSign() {
            return new SquarePlayerSign;
        };

    private:
        static PlayerSignRegistrator sm_register;
};

#endif
