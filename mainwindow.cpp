#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QDebug"
#include "lexer2.h"
#include "parser2.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "QDir"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::on_actionGuardar_triggered()
{
    if (curFile.isEmpty()){
     return   on_actionGuardar_triggered();
    }else{
       return saveFile();
    }
}

bool MainWindow::on_actionGuardar_Como_triggered()
{
    QString fileName =  QFileDialog :: getSaveFileName(
                this,
                "TextEditor - Save as",
                "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller_parser",
                "Text Files (*.txt):: All File (*.*) ");

    if(!fileName.isEmpty()){
        curFile = fileName;
       return saveFile();
    }
    return false;
}

bool MainWindow::saveFile()
{
    QFile file(curFile);
    if(file.open(QFile::WriteOnly)){
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
        return true;
    }else{
        QMessageBox::warning(
                    this,
                    "TexEditor",
                    tr("cannot write file %1. \nError: %2")
                    .arg(curFile)
                    .arg(file.errorString()));
        return false;
    }
}

bool MainWindow::maybesave()
{
    if(ui->plainTextEdit->document()->isModified()){
        QMessageBox :: StandardButton ret =
                QMessageBox :: warning(
                    this,
                    "TexEditor",
                    tr("The Document has been Modified"
                       "Do you want to save your changes?"),
                    QMessageBox :: Yes | QMessageBox :: No | QMessageBox :: Cancel );
        if(ret == QMessageBox :: Yes){
            return on_actionGuardar_triggered();
        }else if(ret == QMessageBox :: Cancel)
            return false;
    }
    return true;
}

void MainWindow::on_actionAbrir_Archivo_triggered()
{
    if(maybesave()){
        QString fileName = QFileDialog :: getOpenFileName(
                    this,
                    "TexEditor - Openfile",
                    "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller_parser",
                    "Text Files (*.txt):: All File (*.*) ");
       if(!fileName.isEmpty()){
           QFile file(fileName);
           if(file.open(QFile :: ReadOnly)){
               ui->plainTextEdit->setPlainText(file.readAll());
           }else{
               QMessageBox :: warning(
                           this,
                           "TexEditor",
                           tr("cannot write file %1. \nError: %2")
                           .arg(fileName)
                           .arg(file.errorString()));
           }
       }
    }
}

void MainWindow::on_actionNueva_clae_triggered()
{

   return;
}

void MainWindow::on_actionCorrer_triggered()
{
    Lexer c = Lexer() ;
       char NombreArchivo[50];
       QString name = QFileInfo(curFile).fileName();
      /* string name2 = name.toStdString();
       for(int i=0; i < name2.length(); i++){
           NombreArchivo[i] = name2[i];
       }*/
       qDebug()<<name;

       int resultado = c.lexer(name.toLocal8Bit().constData());

       if(resultado == 1){
           ui->textEdit->setText("No se puede leer el archivo.");
           return;
       }
       if(resultado == 2){
           ui->textEdit->setText("Compilado con exito!");
           return;
       }
       if(resultado == 3){
           ui->textEdit->setText("Error Sintactico.");
           return;
       }
       ui->textEdit->setText("Error Sintactico.");
}
