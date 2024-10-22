#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QTextEdit>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    QLineEdit *stolbLE_ = nullptr;
    QLineEdit *strLE_ = nullptr;
    QLineEdit *XbLE_ = nullptr;
    QLineEdit *YbLE_ = nullptr;
    QLineEdit *XsLE_ = nullptr;
    QLineEdit *YsLE_ = nullptr;

    QLineEdit *filePathLE_ = nullptr;

    QHBoxLayout *hBoxMain_ = nullptr;
    QVBoxLayout *vBox1_ = nullptr;
    QVBoxLayout *vBox2_ = nullptr;
    QHBoxLayout *hBox1_ = nullptr;
    QHBoxLayout *hBox2_ = nullptr;

    QFormLayout *formLayout1_ = nullptr;
    QFormLayout *formLayout2_ = nullptr;
    QFormLayout *formLayout3_ = nullptr;
    QFormLayout *formLayout4_ = nullptr;
    QFormLayout *formLayout5_ = nullptr;

    QPushButton *loadButton_ = nullptr;

    QTableWidget *tableWidget_ = nullptr;

    QPushButton *btn1_ = nullptr;
    QPushButton *btn2_ = nullptr;
    QPushButton *btn3_ = nullptr;

    QTextEdit *porogTE_ = nullptr;

    QPushButton *calcBtn_ = nullptr;

    bool allVarsFine_ = false;

    void initializeWidget();

signals:

private slots:
    void checkVariables();
    void resetTableSize();
};

#endif // MAINWIDGET_H
