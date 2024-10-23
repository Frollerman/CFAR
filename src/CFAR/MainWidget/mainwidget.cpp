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
    connect(stolbLE_, SIGNAL(editingFinished()), this, SLOT(resetTableSize()));
    connect(strLE_, SIGNAL(editingFinished()), this, SLOT(resetTableSize()));
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
    connect(loadButton_, SIGNAL(pressed()), this, SLOT(loadFile()));

    tableWidget_ = new QTableWidget(this);
    tableWidget_->setRowCount(strLE_->text().toInt());
    tableWidget_->setColumnCount(stolbLE_->text().toInt());
    // tableWidget_->setEnabled(false);

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
    calcBtn_->setEnabled(false);
    connect(calcBtn_, SIGNAL(pressed()), this, SLOT(calculate()));

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
    // loadButton_->setEnabled(false);

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
        loadButton_->setEnabled(false);
    } else {
        btn1_->setIcon(QIcon(QPixmap(":/icons/check.png")));
        loadButton_->setEnabled(true);
        xyFine = true;
    }

    if(xb < x && xb > xs && yb < y && yb > ys && (xb%2) && (yb%2)) {
        btn2_->setIcon(QIcon(QPixmap(":/icons/check.png")));
        bFine = true;
    } else {
        btn2_->setIcon(QIcon(QPixmap(":/icons/cross.png")));
        calcBtn_->setEnabled(false);
    }

    if(xs < x && xb > xs && ys < y && yb > ys && (xs%2) && (ys%2)) {
        btn3_->setIcon(QIcon(QPixmap(":/icons/check.png")));
        sFine = true;
    } else {
        btn3_->setIcon(QIcon(QPixmap(":/icons/cross.png")));
        calcBtn_->setEnabled(false);
    }

    // если все значения в норме, активируем кнопки
    if(xyFine && bFine && sFine) {
        loadButton_->setEnabled(true);
        if(isFileLoaded) {
            calcBtn_->setEnabled(true);
        }
    }

}

void MainWidget::resetTableSize()
{
    tableWidget_->setRowCount(strLE_->text().toInt());
    tableWidget_->setColumnCount(stolbLE_->text().toInt());
}

void MainWidget::loadFile()
{
    QFile file(filePathLE_->text());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream tStream(&file);
    QString line;

    if(file.isOpen()) {
        while (!tStream.atEnd()) {
            line += tStream.readLine();
        }
    } else {
        filePathLE_->setText("Файл не был открыт!");
        return;
    }

    QStringList list = line.split(" ");

    for(int i = 0; i < strLE_->text().toInt(); i++) {
        for(int j = 0; j < stolbLE_->text().toInt(); j++) {
            QTableWidgetItem *newItem = new QTableWidgetItem(list.takeFirst());
            tableWidget_->setItem(i, j, newItem);
        }
    }

    isFileLoaded = true;
    calcBtn_->setEnabled(true);
}

void MainWidget::calculate()
{
    const int x = tableWidget_->rowCount();
    const int y = tableWidget_->columnCount();

    float mat[x][y];
    float aux[x][y];

    // заполняем матрицу значениями из таблицы
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            mat[i][j] = tableWidget_->item(i, j)->text().toFloat();
        }
    }

    // заполняем дополнительную матрицу суммами значений подматриц
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++) {
            aux[i][j] = mat[i][j];
            if (i > 0) aux[i][j] += aux[i-1][j];
            if (j > 0) aux[i][j] += aux[i][j-1];
            if (i > 0 && j > 0) aux[i][j] -= aux[i-1][j-1];
        }
    }

    int Xb = XbLE_->text().toInt();
    int Yb = YbLE_->text().toInt();
    int Xs = XsLE_->text().toInt();
    int Ys = YsLE_->text().toInt();

    QString porogText;

    // вычисляем порог для каждой подходящей ячейки
    for(int i = Yb / 2; i < x - Yb / 2; i++) {
        for(int j = Xb / 2; j < y - Xb / 2; j++) {

            // изначально необходимые суммы - это суммы наибольшей подматрицыы (по нижнему правому краю)
            float Sb = aux[i + Yb / 2][j + Xb / 2];
            float Ss = aux[i + Ys / 2][j + Xs / 2];

            {
                int x1 = i - Yb / 2;
                int x2 = i + Yb / 2;
                int y1 = j - Xb / 2;
                int y2 = j + Xb / 2;

                // если слева есть подматрица, то вычитаем сумму ее значений
                if (y1 > 0) Sb -= aux[x2][y1-1];
                // если сверху есть подматрица, то вычитаем сумму ее значений
                if (x1 > 0) Sb -= aux[x1-1][y2];
                // если и сверху, и слева были подматрицы, то
                // добавляем подматрицу по диагонали слева сверху,
                // так как ее сумма была вычтена дважды
                if (x1 > 0 && y1 > 0) Sb += aux[x1-1][y1-1];
            }

            // по аналогии вычисляем вторую сумму
            {
                int x1 = i - Ys / 2;
                int x2 = i + Ys / 2;
                int y1 = j - Xs / 2;
                int y2 = j + Xs / 2;

                if (y1 > 0) Ss -= aux[x2][y1-1];
                if (x1 > 0) Ss -= aux[x1-1][y2];
                if (x1 > 0 && y1 > 0) Ss += aux[x1-1][y1-1];
            }

            // вычисление и объявление переменных для порога
            float sq = Xb * Yb - Xs * Ys;
            float err = 0.01;
            float Th = std::pow((1/err), (1/sq)) - 1;

            float porog = (Sb - Ss) * Th;

            // проверка условия на превышение порога
            if(mat[i][j] > porog) {
                porogText += "Для ячейки (" + QString::number(i + 1) + "," + QString::number(j + 1) + ") = " + QString::number(mat[i][j]) +
                             " Sb = " + QString::number(Sb) + " Ss = " + QString::number(Ss) + " Порог = " + QString::number(porog) + "\n";
                porogText += "Порог превышен!\n";
            }
        }
    }

    porogTE_->setText(porogText);

}
