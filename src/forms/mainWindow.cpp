#include <forms/mainWindow.hpp>

#include "ui_mainWindow.h"

namespace sackofcheese {

    MainWindow::MainWindow() : m_ui(new Ui::MainWindow) {
        m_ui->setupUi(this);
    }

    MainWindow::~MainWindow() = default;
}