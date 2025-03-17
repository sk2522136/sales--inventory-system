#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inventory.h"  // Inventory Window Include Karo
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_btn_clicked()
{
    QString username = ui->username_edit->text();
    QString password = ui->password_edit->text();

    if (username == "admin" && password == "1234") {
        QMessageBox::information(this, "Login Success", "Welcome!");

        // 🟢 Inventory Window Open Karein
        inventoryWindow = new inventory();
        inventoryWindow->show();

        // 🛑 Login Window Close Karna Hai (Optional)
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid Username or Password");
    }
}

