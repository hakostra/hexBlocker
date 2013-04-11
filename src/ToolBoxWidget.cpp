/*
Copyright 2012, 2013
Author Nicolas Edh,
Nicolas.Edh@gmail.com,
or user "nsf" at cfd-online.com

License
    This file is part of hexBlocker.

    hexBlocker is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    hexBlocker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with hexBlocker.  If not, see <http://www.gnu.org/licenses/>.

    The license is included in the file COPYING.
*/

#include "ToolBoxWidget.h"
#include "ui_ToolBoxWidget.h"
#include "CreateBlockWidget.h"
#include "MoveVerticesWidget.h"
#include "SetBCsWidget.h"
#include "EdgePropsWidget.h"
#include <QWidget>

ToolBoxWidget::ToolBoxWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ToolBoxWidget)
{
    ui->setupUi(this);

    emptyPage = new QWidget; //index 0
    this-ui->stackedWidget->addWidget(emptyPage);
    createBlockW = new CreateBlockWidget; //index 1
    this->ui->stackedWidget->addWidget(createBlockW);
    moveVerticesW = new MoveVerticesWidget; //index 2
    this->ui->stackedWidget->addWidget(moveVerticesW);
    setBCsW = new SetBCsWidget; //index 3
    this->ui->stackedWidget->addWidget(setBCsW);
    edgePropsW = new EdgePropsWidget; //index 4
    this->ui->stackedWidget->addWidget(edgePropsW);
    this->ui->stackedWidget->setCurrentIndex(1);

    connect(createBlockW,SIGNAL(cancel()),this,SLOT(slotCancel()));
    connect(setBCsW,SIGNAL(done()),this,SLOT(slotCancel()));
    connect(moveVerticesW,SIGNAL(setStatusText(QString)),this,SLOT(slotSetStatusText(QString)));
    connect(moveVerticesW,SIGNAL(moveDone()),this,SLOT(slotCancel()));
    connect(createBlockW,SIGNAL(setStatusText(QString)),this,SLOT(slotSetStatusText(QString)));
    connect(setBCsW,SIGNAL(setStatusText(QString)),this,SLOT(slotSetStatusText(QString)));
    connect(edgePropsW,SIGNAL(cancel()),this,SLOT(slotCancel()));
    connect(edgePropsW,SIGNAL(setStatusText(QString)),this,SLOT(slotSetStatusText(QString)));

}

ToolBoxWidget::~ToolBoxWidget()
{
    delete ui;
}

void ToolBoxWidget::setCurrentIndex(int ind)
{
    this->ui->stackedWidget->setCurrentIndex(ind);
}

void ToolBoxWidget::setHexBlockerPointer(HexBlocker *hexBker)
{
    this->hexBlocker=hexBker;
    setBCsW->hexBlocker=hexBlocker;
    createBlockW->hexBlocker=hexBlocker;
    moveVerticesW->hexBlocker=hexBlocker;
    edgePropsW->hexBlocker=hexBlocker;
}

void ToolBoxWidget::slotCancel()
{
    this->ui->stackedWidget->setCurrentIndex(0);
    emit cancel();
}

void ToolBoxWidget::slotSetStatusText(QString text)
{
    emit setStatusText(text);
}
