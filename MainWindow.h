#include <QMainWindow>

#include <memory>


class Ui_MainWindow;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    std::unique_ptr<Ui_MainWindow> m_ui;
};
