#include "mainwindow.h"
#include "clocky.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//первое января две тысячи двадцать третьего года три часа пятнадцать минут десять секунд



    return a.exec();
}


//После того, как сходим на экскурсию и в дневнике задачи простейшего уровня и еду фпм в понедельник сбросиит на почту первую часть ознакомительного отчета



/*
 В каждой группе из 3 человек выделяется полный стакан, задний конец и передний конец
Причем полный стакан реализует то что называется сервер, где под сервером понимается не компьютер, а программа, которая исполняется на некотором компьютере
И суть которой заключается в том, чтобы в бесконечном режиме опрашивать так называемую сетевую карту компьютера и в том случае если в процессе опрашивания сетевой
карты вохникает событие связанное с тем, что полученно некоторое сообщение с другого компьютера(по сети) Программа обрабатывает это сообщения и выполняет
определенные действия в соответствии со своим функционалом
При этом одной из функций сервера в каждой группе будет отправка сообщения "клиенту" Данных о том, что сообщение полученно
Под клиентом будем понимать не компьютер, а мпециальную программу, которая функционирует на каком-то удаленнном компьютере, но имеет связь по сети с сервером.
ЭТот клиент может и должен направлять сообщение серверу. Эти сообщения еще называются серверными-запросами. Часто говорят, что "в настоящее время существует
клиент-серверная организация процесса функционирования систем".
Соответственно в каждой из ваших групп кроме полного стакана мы выделяем задний и передний концы

Задний конец занимается вопросами формирования сообщений для сервера, получение сообщений от сервера и разрабатывает всю начинку клиентской части

Фул стек (полный стакан) занимается как начинкой сервера, так и передним концом.

Передний конец занимается вопросами организации диалога с конечным пользователем и увязывает этот диалог с задним концом



Функционал, который нужно реализовать:
У озера - данные о книгах и сами книги (сервер) по запросу либо есть она, либо нету. Если есть она отправляется
--------------------------------------------------------------
ВСЕ НА ЯЗЫКЕ С++
QT ДЛЯ РИСОВАНИЯ
БИБЛИОТЕКИ ОНЛАЙН QT ИСПОЛЬЗОВАТЬ НЕЛЬЗЯ
Подсказка- Сокер

-----------------------------------------------------------------------------------------------------------------
у ББС - досье на студентов первого курса (номер книжки зач, год рожд...адрес почты электронной, ник в соц сетях , инф платник не платник, инфа каким образом сдал экзы
за все четыре года)Запросы отправляют сами студенты


---------------------------------------------------------------------------------------
Группа комеди клаб -
Фул стек занимается организацией и хранением информации о том, какое блюда(напиток) может быть приготовлен из тех или иных ингредиентов с указанием
веса или обьема . Фул стек наполняет базу данных. Заполняет какой продукт, из каких компонент состоит и описанием процесса приготовления

Тот, кто будет заниматься клиентами 2 вопроса
передний конец организует общение с пользователем, задний конец- общение с сервером(т.е правильный запрос на сервер, чтобы сервер выдал по определенной клиентной информации)
Именно клиент может спросить рецепт по названию или несколько рецептов что можно приготовить из того или иного ингредиента
----------------------------------------------------------------------------------------------------
Функционал группы ГАИ - про нарушителей. с ноомерами автомабилем местом и временем и информацией






 */