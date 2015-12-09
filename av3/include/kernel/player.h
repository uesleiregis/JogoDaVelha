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

#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"

#include <QObject>
#include <QWidget>
#include <QString>

class Player;
class PlayerSign;

class QWidget;

class Player : public QObject {
    Q_OBJECT

    public:
        Player(PlayerSign*, QString = QString("NoName"), QObject* = NULL);
        virtual ~Player();

        int id() const {
            return m_id;
        };
        PlayerSign *sign() const {
            return m_sign;
        };

        QString& name() {
            return m_name;
        };
        const QString& name() const {
            return m_name;
        };
        void setName(const QString& name) {
            m_name = name;
        };

        virtual bool isComputer() const {
            return false;
        };

        virtual bool isNetwork() const {
            return false;
        };

        bool isOrdinary() const {
            return !isComputer() && !isNetwork();
        };

    public slots:
        virtual void processMove(int = -1, int = -1);
        virtual void updateBoard(int, int, Player*);

    signals:
        void moving(int, int, Player*);

    private:
        int m_id;

        static int sm_idGenerator;

        PlayerSign *m_sign;

        QString m_name;
};

#endif
