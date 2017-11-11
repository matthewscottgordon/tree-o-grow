#include <MainWindow.h>

#include "ui_MainWindow.h"

MainWindow::MainWindow()
    : m_ui(new Ui_MainWindow)
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow() = default;
