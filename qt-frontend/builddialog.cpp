/*
     This file is part of Automatic Isolated User Sandbox builder.
     Automatic Isolated User Sandbox builder is free software: you can redistribute it and/or modify 
     it under the terms of the GNU General Public License as published by 
     the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

     Automatic Isolated User Sandbox builder is distributed in the hope that it will be useful, 
     but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
     See the GNU General Public License for more details.

     You should have received a copy of the GNU General Public License along with 
     Automatic Isolated User Sandbox builder. 
     If not, see <https://www.gnu.org/licenses/>. */
#include "builddialog.h"
#include "ui_builddialog.h"
#include <QDebug>
#include <QtGlobal>

BuildDialog::BuildDialog(QWidget *parent,QMap<QString,QString>*args) :
    QDialog(parent),
    ui(new Ui::BuildDialog)
{
    ui->setupUi(this);
    assert(args);
    #define opt(option) QString(" --")+option.key()+QString(" \"")+option.value()+"\""
    QString exec = QString("/usr/bin/python3 ./build-package.py");
    for(QMap<QString,QString>::ConstIterator i = args->constBegin();i!= args->constEnd();++i)
    {
        exec.append((const QString)opt(i));
    }
    qDebug()<<"\nResulting line:\n"<<exec;
    proc = new QProcess(this);
    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    proc->startCommand(exec);
    #else
    proc->start(exec);
    #endif
    QObject::connect(proc, &QProcess::readyReadStandardError, [this]() {
            QString s = this->proc->readAllStandardError();
            qDebug()<<s;
            this->updateText(s);
        });
    QObject::connect(proc, &QProcess::readyReadStandardOutput, [this]() {
            QString s = this->proc->readAllStandardOutput();
            qDebug()<<s;
            this->updateText(s);
        });
   // proc->waitForFinished();
    //QString s = proc->readAllStandardError();
    //this->ui->plainTextEdit->setPlainText(s);
}

BuildDialog::~BuildDialog()
{
    delete ui;
}
void BuildDialog::updateText(QString text)
{
    this->ui->plainTextEdit->setPlainText(this->ui->plainTextEdit->toPlainText()+text);
}
void BuildDialog::on_closeButton_clicked()
{
    if(proc->state()!=QProcess::NotRunning)proc->terminate();
    this->close();
}
