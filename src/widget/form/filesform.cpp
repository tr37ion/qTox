/*
    This file is part of qTox, a Qt-based graphical interface for Tox.

    This program is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the COPYING file for more details.
*/

#include "filesform.h"
#include "ui_mainwindow.h"
#include "src/widget/widget.h"
#include <QFileInfo>
#include <QUrl>
#include <QDebug>
#include <QPainter>
#include <QIcon>
#include <QDateTime>
#include <QPixmap>

#define STATUS       0
#define FILENAME     1
#define SENDER       2
#define ETA          3
#define DATESTARTED  4
#define DATEENDED    5

FilesForm::FilesForm()
    : QObject()
{
    head = new QWidget();
    main = new QTableWidget();
    QStringList columns;
    columns << tr("Status") << tr("Filename")
            << tr("Sender") << tr("ETA")
            << tr("Date started") << tr("Date ended");
    main->setColumnCount(columns.size());
    main->setEnabled(true);
    main->setHorizontalHeaderLabels(columns);
    main->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    main->setAlternatingRowColors(true);
    ///TODO this must be fixed later
    main->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    QFont bold;
    bold.setBold(true);
    headLabel.setText(tr("Transfered Files", "Headline of the window"));
    headLabel.setFont(bold);
    head->setLayout(&headLayout);
    headLayout.addWidget(&headLabel);
}

void FilesForm::show(Ui::MainWindow& ui)
{
    ui.mainContent->layout()->addWidget(main);
    ui.mainHead->layout()->addWidget(head);
    head->show();
    main->show();
}

void FilesForm::onFileDownloadComplete(const QString& path)
{
    int rowCount = main->rowCount();
    main->insertRow(rowCount);
    main->setItem(rowCount, STATUS, new QTableWidgetItem(QIcon(":/ui/fileTransferWidget/fileDone.svg"), QString(""), 0));
    main->setItem(rowCount, FILENAME, new QTableWidgetItem(path));
    main->setItem(rowCount, SENDER, new QTableWidgetItem("Zetok"));
    main->setItem(rowCount, ETA, new QTableWidgetItem("4m 20s"));
    main->setItem(rowCount, DATESTARTED, new QTableWidgetItem("23:36"));
    main->setItem(rowCount, DATEENDED, new QTableWidgetItem("23:37"));
    
//    main->setItem(0, STATUS, new QTableWidgetItem(QIcon(":/ui/fileTransferWidget/fileDone.svg"), QString(""), 0));
//    main->setItem(1, STATUS, new QTableWidgetItem(QIcon(":/ui/chatArea/scrollBarUpArrow.svg"), QString(""), 0));
//    main->setItem(2, STATUS, new QTableWidgetItem(QIcon(":/ui/chatArea/scrollBarDownArrow.svg"), QString(""), 0));
//    main->setItem(3, STATUS, new QTableWidgetItem(QIcon(":/ui/chatArea/error.svg"), QString(""), 0));
    
}

void FilesForm::onFileUploadComplete(const QString& path)
{
    int rowCount = main->rowCount();
    main->insertRow(rowCount);
    main->setItem(rowCount, STATUS, new QTableWidgetItem(QIcon(":/ui/fileTransferWidget/fileDone.svg"), QString(""), 0));
    main->setItem(rowCount, FILENAME, new QTableWidgetItem(path));
    main->setItem(rowCount, SENDER, new QTableWidgetItem("Zetok"));
    main->setItem(rowCount, ETA, new QTableWidgetItem("4m 20s"));
    main->setItem(rowCount, DATESTARTED, new QTableWidgetItem("23:36"));
    main->setItem(rowCount, DATEENDED, new QTableWidgetItem(QDateTime::currentDateTime().toString()));
}

// sadly, the ToxFile struct in core only has the file name, not the file path...
// so currently, these doesn't work as intended (though for now, downloads might work
// whenever they're not saved anywhere custom, thanks to the hack)
// I could do some digging around, but for now I'm tired and others already 
// might know it without me needing to dig, so...
void FilesForm::onFileActivated(QListWidgetItem* item)
{
    ListWidgetItem* tmp = dynamic_cast<ListWidgetItem*> (item);

    Widget::confirmExecutableOpen(QFileInfo(tmp->path));
}

FilesForm::~FilesForm()
{
    head->deleteLater();
}
