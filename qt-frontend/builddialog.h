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
#ifndef BUILDDIALOG_H
#define BUILDDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QTimer>

namespace Ui {
class BuildDialog;
}

class BuildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildDialog(QWidget *parent = nullptr,QMap<QString,QString>*args = NULL);
    ~BuildDialog();

private slots:
    void on_closeButton_clicked();
    void updateText(QString text);

private:
    Ui::BuildDialog *ui;
    QProcess *proc;
};

#endif // BUILDDIALOG_H
