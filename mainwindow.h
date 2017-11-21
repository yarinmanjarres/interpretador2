#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    bool on_actionGuardar_triggered();

    bool on_actionGuardar_Como_triggered();

    void on_actionAbrir_Archivo_triggered();

    void on_actionNueva_clae_triggered();

    void on_actionCorrer_triggered();

private:
    Ui::MainWindow *ui;

    bool saveFile();
    bool maybesave();
    QString curFile;
};

#endif // MAINWINDOW_H
