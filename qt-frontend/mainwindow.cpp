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
#include "mainwindow.h"
#include "builddialog.h"
#include "ui_mainwindow.h"
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList cats;
    cats<<QString( "admin")
    <<QString("cli-mono")
    <<QString("comm")
    <<QString("database")
    <<QString( "debian-installer")
    <<QString("debug")
    <<QString("devel")
    <<QString("doc")
    <<QString("editors")
    <<QString("education")
    <<QString("embedded")
    <<QString("fonts")
    <<QString("games")
    <<QString("gnome")
    <<QString("gnu-r")
    <<QString("gnustep")
    <<QString("golang")
    <<QString("graphics")
    <<QString("hamradio")
    <<QString("haskell")
    <<QString("httpd")
    <<QString("interpreters")
    <<QString("introspection")
    <<QString("java")
    <<QString("javascript")
    <<QString("kde")
    <<QString("kernel")
    <<QString("libdevel")
    <<QString("libs")
    <<QString("lisp")
    <<QString("localization")
    <<QString("mail")
    <<QString("math")
    <<QString("metapackages")
    <<QString("misc")
    <<QString("net")
    <<QString("news")
    <<QString("ocaml")
    <<QString("oldlibs")
    <<QString("otherosfs")
    <<QString("perl")
    <<QString("php")
    <<QString("python")
    <<QString("ruby")
    <<QString("rust")
    <<QString("science")
    <<QString("shells")
    <<QString("sound")
    <<QString("tasks")
    <<QString("tex")
    <<QString("text")
    <<QString("utils")
    <<QString("vcs")
    <<QString("video")
    <<QString("virtual")
    <<QString("web")
    <<QString("x11")
    <<QString( "xfce")
    <<QString( "zope");
    ui->catSelection->addItems(cats);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buildButton_clicked()
{
   QMap <QString,QString>args;
   args["name"] = ui->pkgName->text();
   args["user"] = ui->userName->text();
   args["polkit-vendor"] = ui->pkVendor->text();
   args["maintainer"] = ui->maintainer->text();
   args["maintainer-email"] = ui->maintainerEmail->text();
   args["provides"] = ui->provides->text();
   args["section"] = ui->catSelection->currentText();
   args["homepage"] = ui->homepage->text();
   args["pkdomain"] = ui->pkDomain->text();
   args["exe"] = ui->exeName->text();
   args["desktop-name"] = ui->desktopName->text();
   args["icon"] = ui->iconName->text();
   args["extra-deps"] = ui->extraDeps->text();
   BuildDialog * form = new BuildDialog(this,&args);
   form->show();
}

