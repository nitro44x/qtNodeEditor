#pragma once

#include <forms/exports.hpp>

#include <QMainWindow>
#include <memory>

namespace Ui { class MainWindow; }

namespace sackofcheese {

    class QTNODEEDITORFORMS_EXPORT MainWindow : public QMainWindow {
        Q_OBJECT;
        std::unique_ptr<Ui::MainWindow> m_ui = nullptr;

    public:
        MainWindow();
        ~MainWindow();
    };

}