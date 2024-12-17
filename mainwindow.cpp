

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clocky.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QTime>
#include <QColorDialog> // Добавляем заголовочный файл для QColorDialog
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
     oknoChasov(nullptr)
{
    ui->setupUi(this);
    startTime = QTime::currentTime();

    // Инициализация QMediaPlayer и QAudioOutput
    m_player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(m_player);
    m_player->setAudioOutput(audioOutput);


    //2
    m_player2 = new QMediaPlayer(this);
    audiooutput2=new QAudioOutput(m_player2);
    m_player2->setAudioOutput(audiooutput2);


    //3
    m_player3 = new QMediaPlayer(this);
    audiooutput3=new QAudioOutput(m_player3);
    m_player3->setAudioOutput(audiooutput3);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (oknoChasov) {
        delete oknoChasov;
    }
}

// Открытие окна Словесного Формата
void MainWindow::on_action_6_triggered()
{
    okno_slovo.show();
}

// Открытие окна Числового Формата
void MainWindow::on_action_8_triggered()
{
    okno_chislo.show();
}

// Открыть файл exe
void MainWindow::on_action_triggered()
{
    // Открываем диалоговое окно для выбора exe файла
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Executable"),
                                                    "C:/",
                                                    tr("Executable Files (*.exe)"));
    // Проверяем, выбран ли файл
    if (!fileName.isEmpty()) {
        // Создаем объект QProcess
        QProcess *process = new QProcess(this);

        // Запускаем exe файл
        process->start(fileName);

        // Проверяем успешность запуска
        if (!process->waitForStarted()) {
            qDebug() << "Ошибка: не удалось запустить процесс.";
        }
    } else {
        qDebug() << "Выбор файла отменен.";
    }
}



#include <QTime>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "mainwindow.h"
#include <QPushButton>
// Закрытие всех окон и показ результатов тестирования

// Закрытие всех окон и показ результатов тестирования
// Закрытие всех окон и показ результатов тестирования
void MainWindow::on_action_3_triggered()
{
    // Закрытие всех окон
    if (oknoChasov) {
        oknoChasov->close();
    }
    okno_slovo.close();
    okno_chislo.close();

    // Вычисление времени работы программы
    QTime endTime = QTime::currentTime();
    int elapsedSeconds = startTime.secsTo(endTime);
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;

    // Запись текущего результата в файл
    QString resultFilePath = "results.txt";
    QFile resultFile(resultFilePath);
    if (resultFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&resultFile);
        out << startTime.toString("hh:mm:ss") << "," << endTime.toString("hh:mm:ss") << "," << elapsedSeconds << "\n";
        resultFile.close();
    } else {
        qDebug() << "Ошибка: не удалось открыть файл для записи.";
    }

    // Чтение результатов из файла
    int minTime = INT_MAX;
    int maxTime = 0;
    QList<QStringList> allResults;

    if (resultFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&resultFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 3) {
                int time = fields[2].toInt();
                allResults.append(fields);
                if (time < minTime) {
                    minTime = time;
                }
                if (time > maxTime) {
                    maxTime = time;
                }
            }
        }
        resultFile.close();
    } else {
        qDebug() << "Ошибка: не удалось открыть файл для чтения.";
    }

    // Формирование сообщения
    QString resultMessage = QString("Результаты тестирования:\n")
                            + "Время запуска программы: " + startTime.toString("hh:mm:ss") + "\n"
                            + "Время завершения программы: " + endTime.toString("hh:mm:ss") + "\n"
                            + "Продолжительность работы: " + QString::number(minutes) + " минут " + QString::number(seconds) + " секунд\n"
                            + "Максимальное время тестирования: " + QString::number(maxTime / 60) + " минут " + QString::number(maxTime % 60) + " секунд\n"
                            + "Минимальное время тестирования: " + QString::number(minTime / 60) + " минут " + QString::number(minTime % 60) + " секунд\n";

    // Создание MessageBox
    QMessageBox msgBox;
    msgBox.setWindowTitle("Результаты тестирования");
    msgBox.setText(resultMessage);

    // Создание таблицы
    QTableWidget *tableWidget = new QTableWidget(allResults.size(), 3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Время запуска" << "Время завершения" << "Продолжительность (сек)");

    for (int i = 0; i < allResults.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(allResults[i][0]));
        tableWidget->setItem(i, 1, new QTableWidgetItem(allResults[i][1]));
        tableWidget->setItem(i, 2, new QTableWidgetItem(allResults[i][2]));
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(&msgBox);
    layout->addWidget(tableWidget);

    QDialog dialog;
    dialog.setLayout(layout);

    QPushButton *saveButton = msgBox.addButton(tr("Сохранить результат"), QMessageBox::ActionRole);
    QPushButton *exitButton = msgBox.addButton(tr("Выйти"), QMessageBox::RejectRole);

    // Обработка нажатия кнопок
    connect(saveButton, &QPushButton::clicked, [&]() {
        QString saveFileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Text Files (*.txt)"));
        if (!saveFileName.isEmpty()) {
            QFile file(saveFileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << resultMessage;
                file.close();
            } else {
                qDebug() << "Ошибка: не удалось сохранить файл.";
            }
        }
    });
    connect(exitButton, &QPushButton::clicked, [&]() {
        QApplication::quit();
    });

    // Показ диалога
    dialog.exec();
}

void MainWindow::on_action_5_triggered()
{
    QString programDescription =
        "Программа предназначена для создания часов\n\n"
        "Часы: .\n"
        "1. предусмотрен ввод даты и времени в формате словесного описания, например, \"Двадцать шестого июня две тысячи двадцать четвертого года Двенадцать часов шестнадцать минут сорок пять секунд\", с последующим выводом стандартного формата даты и времени (26.06.2024 12:16:45).\n\n"
        "2.  Возможность взятия даты и времени из таймера для автоматического ввода.\n\n"
        "3. Интерфейс для рисования, дополненный возможностью ввода даты и времени для сохранения в файл статистики.\n\n"
        "Программа предусматривает проверку правильности ввода даты и времени. В случае неверного формата данные сохраняются в файле статистики.\n";

    QMessageBox::information(this, "Описание программы", programDescription);
}










void MainWindow::on_action_11_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(-1);  // -1 для действия по умолчанию
    oknoChasov->show();
}

void MainWindow::on_action1_4_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(0);  // 0 для изображения 1f.jpg
    oknoChasov->show();
}

void MainWindow::on_action2_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(1);  // 1 для изображения 2f.jpg
    oknoChasov->show();
}

void MainWindow::on_action3_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(2);  // 2 для изображения 3f.jpg
    oknoChasov->show();
}

void MainWindow::on_action4_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(3);  // 3 для изображения 4f.jpg
    oknoChasov->show();
}

void MainWindow::on_action5_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(4);  // 4 для изображения 5f.jpg
    oknoChasov->show();
}

void MainWindow::on_action6_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(5);  // 5 для изображения 6f.jpg
    oknoChasov->show();
}

void MainWindow::on_action7_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(6);  // 6 для изображения 7f.jpg
    oknoChasov->show();
}

void MainWindow::on_action8_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->setBackgroundImage(7);  // 7 для изображения 8f.jpg
    oknoChasov->show();
}



void MainWindow::on_action_10_triggered() {
    // Открываем диалог выбора цвета
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет для стрелок часов");
    // if (color.isValid()) {
    //     // Устанавливаем выбранный цвет для стрелок часов
    //     oknoChasov->setClockColor(color);
    // }
}


void MainWindow::on_action_9_triggered()
{    m_player2->stop();
    m_player3->stop();
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Выберите аудиофайл"),
                                                    "",
                                                    tr("Аудиофайлы (*.mp3 *.wav *.ogg *.flac)"));
    if (!fileName.isEmpty()) {
        m_player->stop();  // Остановка предыдущего воспроизведения

        // Загрузка медиафайла
        m_player->setSource(QUrl::fromLocalFile(fileName));
        audioOutput->setVolume(1.0);  // Установка громкости
        m_player->play();  // Воспроизведение
    }
}
//гага
void MainWindow::on_action_14_triggered()
{
    m_player->stop();
    m_player3->stop();
    m_player2->setSource(QUrl("qrc:/music/build/Gaga.mp3"));
    audiooutput2->setVolume(1);
    m_player2->play();
}

//прогноз
void MainWindow::on_action_13_triggered()
{
    m_player->stop();
    m_player2->stop();
    m_player3->setSource(QUrl("qrc:/music/build/ont-prognoz-pogody.mp3"));
    audiooutput3->setVolume(1);
    m_player3->play();
}


void MainWindow::on_action_7_triggered()
{
    if (!oknoChasov) {
        oknoChasov = new ClockWidget(this);
    }
    oknoChasov->show();
}

