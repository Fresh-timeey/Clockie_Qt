#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaPlayer>  // Включаем только QMediaPlayer
#include <QMainWindow>
#include <QTime>
#include "formatslovestny.h"
#include "formatchislovoy.h"
#include "clocky.h"
#include <QColorDialog> // Добавляем заголовочный файл для QColorDialog
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_6_triggered();
    void on_action_8_triggered();
    void on_action_triggered();
    void on_action_3_triggered();
    void on_action_5_triggered();
    void on_action_11_triggered();
    void on_action1_4_triggered();
    void on_action2_triggered();
    void on_action3_triggered();
    void on_action4_triggered();
    void on_action5_triggered();
    void on_action6_triggered();
    void on_action7_triggered();
    void on_action8_triggered();

    void on_action_10_triggered(); // Новый слот для action_10

    void on_action_14_triggered();
    void on_action_9_triggered();

    void on_action_13_triggered();

    void on_action_7_triggered();

private:
    Ui::MainWindow *ui;
    formatslovestny okno_slovo;
    formatchislovoy okno_chislo;
    ClockWidget *oknoChasov;
    QTime startTime;
    void updateBackgroundSelection(int index);


    QMediaPlayer* m_player;  // Объявление объекта для воспроизведения музыки
    QAudioOutput* audioOutput; // Объявление объекта для вывода аудио

    QMediaPlayer* m_player2;
    QAudioOutput *audiooutput2;

    QMediaPlayer* m_player3;
    QAudioOutput *audiooutput3;
};

#endif // MAINWINDOW_H
