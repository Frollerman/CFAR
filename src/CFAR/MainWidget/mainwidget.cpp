#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    initializeWidget();
}

void MainWidget::initializeWidget()
{
    stolbLE_ = new QLineEdit("45", this);
    strLE_ = new QLineEdit("45", this);
    XbLE_ = new QLineEdit("5", this);
    YbLE_ = new QLineEdit("3", this);
    XsLE_ = new QLineEdit("3", this);
    YsLE_ = new QLineEdit("1", this);

    connect(stolbLE_, SIGNAL(editingFinished()), this, SLOT(checkVariables()));
    connect(strLE_, SIGNAL(editingFinished()), this, SLOT(checkVariables()));
    connect(XbLE_, SIGNAL(editingFinished()), this, SLOT(checkVariables()));
    connect(YbLE_, SIGNAL(editingFinished()), this, SLOT(checkVariables()));
    connect(XsLE_, SIGNAL(editingFinished()), this, SLOT(checkVariables()));
    connect(YsLE_, SIGNAL(editingFinished()), this, SLOT(checkVariables()));

    stolbLE_->setMaximumWidth(50);
    strLE_->setMaximumWidth(50);

    XbLE_->setMaximumWidth(50);
    YbLE_->setMaximumWidth(50);

    XsLE_->setMaximumWidth(50);
    YsLE_->setMaximumWidth(50);

    filePathLE_ = new QLineEdit("~/", this);
    porogTE_ = new QTextEdit(this);

    porogTE_->setReadOnly(true);
    // porogTE_->setFixedWidth(200);

    hBoxMain_ = new QHBoxLayout(this);
    vBox1_ = new QVBoxLayout(this);
    vBox2_ = new QVBoxLayout(this);
    hBox1_ = new QHBoxLayout(this);
    hBox2_ = new QHBoxLayout(this);

    formLayout1_ = new QFormLayout(this);
    formLayout1_->addRow(tr("Кол-во столбцов:"), stolbLE_);
    formLayout1_->addRow(tr("Кол-во строк:"), strLE_);

    formLayout2_ = new QFormLayout(this);
    formLayout2_->addRow(tr("Xb:"), XbLE_);
    formLayout2_->addRow(tr("Yb:"), YbLE_);

    formLayout3_ = new QFormLayout(this);
    formLayout3_->addRow(tr("Xs:"), XsLE_);
    formLayout3_->addRow(tr("Ys:"), YsLE_);

    formLayout4_ = new QFormLayout(this);
    formLayout4_->addRow(tr("Путь к файлу:"), filePathLE_);

    formLayout5_ = new QFormLayout(this);
    formLayout5_->addRow(tr("Превышения порога:"), porogTE_);

    loadButton_ = new QPushButton("Загрузить файл", this);

    tableWidget_ = new QTableWidget(this);
    tableWidget_->setRowCount(strLE_->text().toInt());
    tableWidget_->setColumnCount(stolbLE_->text().toInt());

    for(int i = 0; i < stolbLE_->text().toInt(); i++) {
        tableWidget_->setColumnWidth(i, 75);
    }

    QPixmap pix(":/icons/check.png");

    btn1_ = new QPushButton("", this);
    btn2_ = new QPushButton("", this);
    btn3_ = new QPushButton("", this);

    btn1_->setFlat(true);
    btn2_->setFlat(true);
    btn3_->setFlat(true);

    btn1_->setEnabled(false);
    btn2_->setEnabled(false);
    btn3_->setEnabled(false);

    btn1_->setToolTip("Кол-во столбцов и строк должно быть > 40");
    btn2_->setToolTip("Xb < кол-ва столбцов, Xb > Xs, Xb - нечетное\nYb < кол-ва строк, Yb > Ys, Yb - нечетное");
    btn3_->setToolTip("Xs < кол-ва столбцов, Xb > Xs, Xs - нечетное\nYs < кол-ва строк, Yb > Ys, Ys - нечетное");

    btn1_->setIcon(QIcon(pix));
    btn1_->setIconSize(QSize(50, 50));

    btn2_->setIcon(QIcon(pix));
    btn2_->setIconSize(QSize(50, 50));

    btn3_->setIcon(QIcon(pix));
    btn3_->setIconSize(QSize(50, 50));

    calcBtn_ = new QPushButton("Рассчитать", this);

    hBox1_->addWidget(btn1_);
    hBox1_->addLayout(formLayout1_);
    hBox1_->addWidget(btn2_);
    hBox1_->addLayout(formLayout2_);
    hBox1_->addWidget(btn3_);
    hBox1_->addLayout(formLayout3_);

    hBox2_->addLayout(formLayout4_);
    hBox2_->addWidget(loadButton_);

    vBox1_->addLayout(hBox1_);
    vBox1_->addLayout(hBox2_);
    vBox1_->addWidget(tableWidget_);
    vBox1_->addWidget(calcBtn_);

    vBox2_->addLayout(formLayout5_);

    hBoxMain_->addLayout(vBox1_);
    hBoxMain_->addLayout(vBox2_);

    this->setLayout(hBoxMain_);
}

void MainWidget::checkVariables()
{
    allVarsFine_ = false;

    int x = stolbLE_->text().toInt();
    int y = strLE_->text().toInt();
    int xb = XbLE_->text().toInt();
    int yb = YbLE_->text().toInt();
    int xs = XsLE_->text().toInt();
    int ys = YsLE_->text().toInt();

    bool xyFine = false;
    bool bFine = false;
    bool sFine = false;

    if(x < 41 || y < 41) {
        btn1_->setIcon(QIcon(QPixmap(":/icons/cross.png")));
    } else {
        btn1_->setIcon(QIcon(QPixmap(":/icons/check.png")));
        xyFine = true;
    }

    if(xb < x && xb > xs && yb < y && yb > ys && (xb%2) && (yb%2)) {
        btn2_->setIcon(QIcon(QPixmap(":/icons/check.png")));
        bFine = true;
    } else {
        btn2_->setIcon(QIcon(QPixmap(":/icons/cross.png")));
    }

    if(xs < x && xb > xs && ys < y && yb > ys && (xs%2) && (ys%2)) {
        btn3_->setIcon(QIcon(QPixmap(":/icons/check.png")));
        sFine = true;
    } else {
        btn3_->setIcon(QIcon(QPixmap(":/icons/cross.png")));
    }

    if(xyFine && bFine && sFine) {
        allVarsFine_ = true;
    }

}

void MainWidget::resetTableSize()
{
    tableWidget_->setRowCount(strLE_->text().toInt());
    tableWidget_->setColumnCount(stolbLE_->text().toInt());
}
