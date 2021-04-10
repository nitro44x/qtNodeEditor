#pragma once

#include <QMainWindow>

#include <memory>

namespace Ui { class MainWindow; }

namespace sackofcheese {

    class MainWindow : public QMainWindow {
        Q_OBJECT;

        std::unique_ptr<Ui::MainWindow> m_ui = nullptr;
    public:
        MainWindow();
        ~MainWindow();
    };

}