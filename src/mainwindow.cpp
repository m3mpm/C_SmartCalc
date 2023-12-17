#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QLocale curLocale(QLocale("ru_RU"));
    QLocale::setDefault(curLocale);

    ui->setupUi(this);

    ui->checkBox_popolnit_snyant->setDisabled(1);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(digits_numbers()));

    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(math_operations_div()));
    connect(ui->pushButton_multi,SIGNAL(clicked()),this,SLOT(math_operations_multi()));
    connect(ui->pushButton_exp,SIGNAL(clicked()),this,SLOT(math_operations_exp()));
    connect(ui->pushButton_munis,SIGNAL(clicked()),this,SLOT(math_operations_minus()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_operations_plus()));

    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(functions()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(functions()));

    connect(ui->pushButton_openBracket,SIGNAL(clicked()),this,SLOT(brackets()));
    connect(ui->pushButton_closeBracket,SIGNAL(clicked()),this,SLOT(brackets()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
        ui->pushButton_getResult->click();
    if(event->key() == Qt::Key_Escape)
        ui->pushButton_clear->click();
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    ui->lineEdit->setText(str + button->text());
}

void MainWindow::on_pushButton_erase_clicked()
{
    QString str = ui->lineEdit->text();
      str = str.left(str.count() - 1);
      ui->lineEdit->setText(str);
}

void MainWindow::on_pushButton_dot_clicked()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    ui->lineEdit->setText(str + button->text());
}

void MainWindow::math_operations_div()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    int len = str.length();
    if(len == 0) {
        ui->lineEdit->setText("0" + button->text());
    } else if(str[len-1] == '*'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '/'){
        ui->lineEdit->setText((str));
    } else if(str[len-1] == '-'){
        ui->lineEdit->setText((str));
    } else if(str[len-1] == '+'){
        ui->lineEdit->setText((str));
    } else if(str[len-1] == '^'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else {
        ui->lineEdit->setText(str + button->text());
    }
}

void MainWindow::math_operations_multi()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    int len = str.length();
    if(len == 0) {
        ui->lineEdit->setText("0" + button->text());
    } else if(str[len-1] == '/'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '*'){
        ui->lineEdit->setText(str);
    } else if(str[len-1] == '-'){
        ui->lineEdit->setText(str);
    } else if(str[len-1] == '+'){
        ui->lineEdit->setText(str);
    } else if(str[len-1] == '^'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else {
        ui->lineEdit->setText(str + button->text());
    }
}

void MainWindow::math_operations_exp()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    int len = str.length();
    if(len == 0) {
        ui->lineEdit->setText("0" + button->text());
    } else if(len > 2 && ((str[len-2] == '*' || str[len-2] == '/') && (str[len-1] == '+' || str[len-1] == '-'))){
        ui->lineEdit->setText(str);
    } else if(str[len-1] == '-'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '+'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '/'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '*'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '^'){
        ui->lineEdit->setText(str);
    } else {
        ui->lineEdit->setText(str + button->text());
    }
}

void MainWindow::math_operations_plus()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    int len = str.length();
    if(len == 0) {
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '-'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText(str + button->text());
    } else if(str[len-1] == '+'){
        ui->lineEdit->setText(str);
    } else {
        ui->lineEdit->setText(str + button->text());
    }
}

void MainWindow::math_operations_minus()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    int len = str.length();
    if(len == 0) {
        ui->lineEdit->setText((str + button->text()));
    } else if(str[len-1] == '+'){
        str = str.left(str.count() - 1);
        ui->lineEdit->setText((str + button->text()));
    } else if(str[len-1] == '-'){
        ui->lineEdit->setText((str));
    } else {
        ui->lineEdit->setText((str + button->text()));
    }
}

void MainWindow::functions()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    ui->lineEdit->setText((str + button->text()+"("));
}

void MainWindow::brackets()
{
    QPushButton *button = (QPushButton *) sender();
    QString str = ui->lineEdit->text();
    ui->lineEdit->setText((str + button->text()));
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit->clear();
    ui->doubleSpinBox_x->setValue(0);
}

void MainWindow::on_pushButton_getResult_clicked()
{
    QString str = ui->lineEdit->text();
    if(str.isEmpty()) {
        ui->lineEdit->setText(str);
    } else {
        QByteArray count = str.toLower().toLatin1();
        char *cstr = count.data();

        double result = 0.0;
        double input_x = ui->doubleSpinBox_x->value();

        int error = get_result(cstr,input_x,&result);
        if(isnan(result)){
            ui->lineEdit->setText("Error");
        } else if(error == SUCCESS) {
           ui->lineEdit->setText(QString::number(result,'l',2));
        } else {
           ui->lineEdit->setText("Input error");
        }
    }
}

void MainWindow::on_pushButton_graph_clicked()
{
    QString str = ui->lineEdit->text();
    if(str.isEmpty()) {
        ui->lineEdit->setText(str);
    } else {
        ui->spinBox_startX->setValue(-10);
        ui->spinBox_endX->setValue(10);
        ui->spinBox_startY->setValue(-10);
        ui->spinBox_endY->setValue(10);
        ui->Graph->clearGraphs();
        ui->Graph->replot();
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_pushButton_comeBackToCalc1_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit->clear();
    ui->doubleSpinBox_x->setValue(0);
    ui->Graph->clearGraphs();
    ui->Graph->replot();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clearGraph_clicked()
{
    ui->spinBox_startX->setValue(-10);
    ui->spinBox_endX->setValue(10);
    ui->spinBox_startY->setValue(-10);
    ui->spinBox_endY->setValue(10);
    ui->Graph->clearGraphs();
    ui->Graph->replot();
}

void MainWindow::on_pushButton_buildGraph_clicked()
{
    QString str = ui->lineEdit->text();
    if(str.toLower().contains('x')) {
        QByteArray count = str.toLower().toLatin1();
        char *cstr = count.data();

        int error = check_input_str(cstr);
        if(error == SUCCESS) {
            double result = 0.0;
            double start_x = (double)ui->spinBox_startX->value();
            double end_x = (double)ui->spinBox_endX->value();
            double start_y = (double)ui->spinBox_startY->value();
            double end_y = (double)ui->spinBox_endY->value();

            if (start_x < end_x && start_y < end_y) {
                double step = fabs(start_x - end_x)/10000;

                ui->Graph->xAxis->setRange(start_x-10,end_x+10);
                ui->Graph->yAxis->setRange(start_y-10,end_y+10);

                QVector<double> x, y;
                for(double X = start_x;X <=end_x;X += step) {
                    error = get_result(cstr,X,&result);

                    if(error == SUCCESS) {
                        if(result >= start_y && result <= end_y) {
                            x.push_back(X);
                            y.push_back(result);
                        }
                    }
                }
                ui->Graph->addGraph();

                ui->Graph->graph(0)->setLineStyle(QCPGraph::lsNone);
                ui->Graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

                ui->Graph->graph(0)->addData(x,y);
                ui->Graph->replot();

                ui->Graph->setInteraction(QCP::iRangeDrag,1);
                ui->Graph->setInteraction(QCP::iRangeZoom,1);
                x.clear();
                y.clear();

            } else {
                ui->stackedWidget->setCurrentIndex(0);
                ui->lineEdit->setText("Input error: start x > end x or start y > end y");
            }
        } else {
            ui->stackedWidget->setCurrentIndex(0);
            ui->lineEdit->setText("Input error");
        }
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        ui->lineEdit->setText(str);
    }
}

void MainWindow::on_pushButton_creditCalc_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->radioButton_ann->setChecked(1);
}

void MainWindow::on_pushButton_comeBackToCalc2_clicked()
{

    on_pushButton_creditClear_clicked();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_creditClear_clicked()
{
    ui->doubleSpinBox_sumCredit->setValue(0);
    ui->spinBox_periodCredit->setValue(0);
    ui->doubleSpinBox_procentCredit->setValue(0);

    ui->radioButton_ann->setChecked(1);
    ui->radioButton_diff->setChecked(0);

    ui->label_monthPay1->setText("Ежемесячный платеж, руб");
    ui->label_monthPayValue1->setText("0");
    ui->label_monthPay2->setText("");
    ui->label_monthPayValue2->setText("");

    ui->label_overPayCredit->setText("0");
    ui->label_allPayCredit->setText("0");
    // удаляет таблицу
    ui->tableWidget_credit->setColumnCount(0);
    ui->tableWidget_credit->setRowCount(0);
}


void MainWindow::on_pushButton_creditGetResult_clicked()
{
    double input_sum = ui->doubleSpinBox_sumCredit->value();
    int input_period = ui->spinBox_periodCredit->value();
    double input_procent = ui->doubleSpinBox_procentCredit->value();

    if(input_sum != 0.0 && input_period != 0 && input_procent != 0.0) {

        ui->tableWidget_credit->setColumnCount(4);
        ui->tableWidget_credit->setRowCount(input_period);
        ui->tableWidget_credit->setHorizontalHeaderLabels(QStringList() << "Сумма платежа, руб" << "Платеж по основному долгу, руб" << "Платеж по процентам, руб" << "Остаток долга, руб");

        int pay_method = 0;
        if(ui->radioButton_ann->isChecked()) {
            pay_method = 1;
        } else if(ui->radioButton_diff->isChecked()) {
            pay_method = 2;
        }
        double month_procent = (input_procent/12)/100;

        QTableWidgetItem *itm;

        if(pay_method == 1) {
            double fix_month_pay = input_sum*(month_procent+(month_procent/(pow(1+month_procent, input_period)-1))); //fixed part // print

            double over_pay = 0.0;
            double over_payi = 0.0;
            double left_dolg = input_sum;

            for(int i = 0; i < input_period; i++) {
                over_payi = left_dolg * month_procent;
                double main_dolg_payi = fix_month_pay - over_payi;
                left_dolg -= main_dolg_payi;
                over_pay += over_payi;

                itm = new QTableWidgetItem(QString::number(fix_month_pay,'l',2));
                ui->tableWidget_credit->setItem(i,0,itm);
                itm = new QTableWidgetItem(QString::number(main_dolg_payi,'l',2));
                ui->tableWidget_credit->setItem(i,1,itm);
                itm = new QTableWidgetItem(QString::number(over_payi,'l',2));
                ui->tableWidget_credit->setItem(i,2,itm);
                itm = new QTableWidgetItem(QString::number(left_dolg,'l',2));
                ui->tableWidget_credit->setItem(i,3,itm);

            }
            double all_pay = input_sum + over_pay;

            ui->label_monthPay1->setText("Ежемесячный платеж, руб");
            ui->label_monthPay2->setText("");
            ui->label_monthPayValue2->setText("");

            ui->label_monthPayValue1->setText(QString::number(fix_month_pay,'l',2));
            ui->label_overPayCredit->setText(QString::number(over_pay,'l',2));
            ui->label_allPayCredit->setText(QString::number(all_pay,'l',2));
        } else if (pay_method == 2) {
            double fix_month_pay = input_sum/input_period;

            double over_pay1 = input_sum * month_procent;
            double month_pay1 = fix_month_pay + over_pay1;
            double over_pay = 0.0;
            double left_dolg = input_sum;
            double over_payi = 0.0;

            for(int i= 0; i < input_period; i++) {
                over_payi = left_dolg * month_procent;
                left_dolg -= fix_month_pay;
                over_pay += over_payi;
                double month_payi = fix_month_pay + over_payi;

                itm = new QTableWidgetItem(QString::number(month_payi,'l',2));
                ui->tableWidget_credit->setItem(i,0,itm);
                itm = new QTableWidgetItem(QString::number(fix_month_pay,'l',2));
                ui->tableWidget_credit->setItem(i,1,itm);
                itm = new QTableWidgetItem(QString::number(over_payi,'l',2));
                ui->tableWidget_credit->setItem(i,2,itm);
                itm = new QTableWidgetItem(QString::number(left_dolg,'l',2));
                ui->tableWidget_credit->setItem(i,3,itm);
            }
            double all_pay = input_sum + over_pay;
            double month_payLast = fix_month_pay + over_payi;

            ui->label_monthPay1->setText("Первый платеж, руб");
            ui->label_monthPayValue1->setText(QString::number(month_pay1,'l',2));
            ui->label_monthPay2->setText("Последний платеж, руб");
            ui->label_monthPayValue2->setText(QString::number(month_payLast,'l',2));
            ui->label_overPayCredit->setText(QString::number(over_pay,'l',2));
            ui->label_allPayCredit->setText(QString::number(all_pay,'l',2));
        }

    } else {
        ui->doubleSpinBox_sumCredit->setValue(input_sum);
        ui->spinBox_periodCredit->setValue(input_period);
        ui->doubleSpinBox_procentCredit->setValue(input_procent);
    }

}


void MainWindow::on_pushButton_depositCalc_clicked()
{
    ui->radioButton_getInEnd->setChecked(1);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_clearDeposit_clicked()
{
    ui->doubleSpinBox_sumDeposit->setValue(0);
    ui->spinBox_periodDeposit->setValue(0);
    ui->doubleSpinBox_procentDeposit->setValue(0);
    ui->doubleSpinBox_procentNalog->setValue(0);
    ui->doubleSpinBox_procentNalogCb->setValue(0);

    ui->radioButton_getInEnd->setChecked(1);
    ui->radioButton_getInMonth->setChecked(0);

    ui->checkBox_capitalization->setChecked(0);
    ui->checkBox_popolnit_snyant->setChecked(0);

    ui->label_profitDeposit->setText("0");
    ui->label_nalogPayDeposit->setText("0");
    ui->label_sumAccountInEndDeposit->setText("0");

    ui->tableWidget_popolnitDeposit->setColumnCount(0);
    ui->tableWidget_popolnitDeposit->setRowCount(0);
    ui->tableWidget_snyatDeposit->setColumnCount(0);
    ui->tableWidget_snyatDeposit->setRowCount(0);
}


void MainWindow::on_pushButton_comeBackToCalc3_clicked()
{
    on_pushButton_clearDeposit_clicked();
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_popolnit_snyant_clicked()
{
    int input_period = ui->spinBox_periodDeposit->value();
    if (input_period > 2) {
        ui->tableWidget_popolnitDeposit->setColumnCount(1);
        ui->tableWidget_popolnitDeposit->setRowCount(input_period - 2);
        ui->tableWidget_popolnitDeposit->setHorizontalHeaderLabels(QStringList() << "Сумма пополенения, руб");

        ui->tableWidget_snyatDeposit->setColumnCount(1);
        ui->tableWidget_snyatDeposit->setRowCount(input_period - 2);
        ui->tableWidget_snyatDeposit->setHorizontalHeaderLabels(QStringList() << "Сумма снятия, руб");

        ui->checkBox_popolnit_snyant->setChecked(1);

    }
}


void MainWindow::on_pushButton_getResultDeposit_clicked()
{
    int daysInMonth = 30;
    int daysInYear = 365;
    int howToGetMoney = 0;
    int isCapitalization = 0;
    double finalProfit = 0.0;
    double totalSum = 0.0;
    double yearProfit_i = 0.0;
    double mustPayNalog_i = 0.0;
    double mustPayNalogTotal = 0.0;

    double input_sum = ui->doubleSpinBox_sumDeposit->value();
    int input_period = ui->spinBox_periodDeposit->value();
    double input_procent = ui->doubleSpinBox_procentDeposit->value();
    double input_procentNalog = ui->doubleSpinBox_procentNalog->value();
    double input_procentNalogCb = ui->doubleSpinBox_procentNalogCb->value();


    if(ui->radioButton_getInEnd->isChecked()) {
        howToGetMoney = 1;
    } else if(ui->radioButton_getInMonth->isChecked()) {
        howToGetMoney = 2;
    }

    if (ui->checkBox_capitalization->isChecked()) {
        isCapitalization = 1;
    }


    if(input_sum != 0.0 && input_period != 0 && input_procent != 0.0 && input_procentNalogCb != 0.0) {

        double arrPopolnenie[input_period];
        double arrSnyant[input_period];
        memset(arrPopolnenie, 0, sizeof(arrPopolnenie));
        memset(arrSnyant, 0, sizeof(arrSnyant));

        double yearProfit = 0.0;
        double dayProfit = 0.0;
        double monthProfit_i = 0.0;
        double monthSum_i= input_sum;


        if(ui->checkBox_popolnit_snyant->isChecked()){
            if(input_period > 2) {
                for(int j = 0; j < input_period - 2; j++){
                    QTableWidgetItem *itm_p = ui->tableWidget_popolnitDeposit->item(j,0);
                    QTableWidgetItem *itm_s = ui->tableWidget_snyatDeposit->item(j,0);
                    if(itm_p != 0) {
                        arrPopolnenie[j] = itm_p->text().toDouble();
                    }
                    if(itm_s != 0) {
                        arrSnyant[j] = itm_s->text().toDouble();
                    }
                }
            }
        }

        if((howToGetMoney == 1 && (isCapitalization == 0 || isCapitalization == 1)) || (howToGetMoney == 2 && isCapitalization == 0)) {

            for(int i = 0, j = 0; i < input_period; i++) {

                if(i != 0 && i % 12 == 0 && howToGetMoney == 2) {
                    mustPayNalog_i = calculateNalog(input_procentNalogCb,input_procentNalog,yearProfit_i);
                    mustPayNalogTotal += mustPayNalog_i;
                    yearProfit_i = 0;
                }

                if(i != 0 && i != input_period - 1 && input_period > 2) {
                    monthSum_i += arrPopolnenie[j];
                    monthSum_i -= arrSnyant[j];
                    input_sum += arrPopolnenie[j];
                    input_sum -= arrSnyant[j];
                    j++;
                }
                yearProfit = monthSum_i * (input_procent / 100);
                dayProfit = yearProfit/daysInYear;
                monthProfit_i = dayProfit * daysInMonth;

                yearProfit_i += monthProfit_i;

                finalProfit += monthProfit_i;
            }

            if (howToGetMoney == 2) {
                mustPayNalog_i = calculateNalog(input_procentNalogCb,input_procentNalog,yearProfit_i);
                mustPayNalogTotal += mustPayNalog_i;
            } else {
                mustPayNalogTotal = calculateNalog(input_procentNalogCb,input_procentNalog,finalProfit);
            }


            if (isCapitalization == 0) {
                totalSum += input_sum;
            } else if (isCapitalization == 1) {
                totalSum += input_sum + finalProfit;
            }

            ui->label_profitDeposit->setText(QString::number(finalProfit,'f',2));
            ui->label_sumAccountInEndDeposit->setText(QString::number(totalSum,'f',2));

        } else if (howToGetMoney == 2 && isCapitalization == 1) {
            for(int i = 1, j = 0; i <= input_period; i++) {
                if(i != 1 && i != input_period && input_period > 2) {
                    monthSum_i += arrPopolnenie[j];
                    monthSum_i -= arrSnyant[j];
                    input_sum += arrPopolnenie[j];
                    input_sum -= arrSnyant[j];
                    j++;
                }
                yearProfit = (monthSum_i * input_procent) / 100;
                dayProfit = yearProfit/daysInYear;
                monthProfit_i = dayProfit * daysInMonth;

                yearProfit_i += monthProfit_i;

                monthSum_i += monthProfit_i;
                finalProfit += monthProfit_i;

                if(i % 12 == 0) {
                    mustPayNalog_i = calculateNalog(input_procentNalogCb,input_procentNalog,yearProfit_i);
                    mustPayNalogTotal += mustPayNalog_i;
                    yearProfit_i = 0;
                }
            }

            mustPayNalog_i = calculateNalog(input_procentNalogCb,input_procentNalog,yearProfit_i);
            mustPayNalogTotal += mustPayNalog_i;

            totalSum = input_sum + finalProfit;
            ui->label_profitDeposit->setText(QString::number(finalProfit,'l',2));
            ui->label_sumAccountInEndDeposit->setText(QString::number(totalSum,'l',2));
        }

        ui->label_nalogPayDeposit->setText(QString::number(mustPayNalogTotal,'l',2));
    } else {
        ui->doubleSpinBox_sumDeposit->setValue(input_sum);
        ui->spinBox_periodDeposit->setValue(input_period);
        ui->doubleSpinBox_procentDeposit->setValue(input_procent);
        ui->doubleSpinBox_procentNalog->setValue(input_procentNalog);
        ui->doubleSpinBox_procentNalogCb->setValue(input_procentNalogCb);
    }
}

double MainWindow::calculateNalog(double input_procentNalogCb, double input_procentNalog, double yearProfit_i) {
    double mustPay = 0.0;
    double sumNalogFree = (1000000 * input_procentNalogCb)/100;;
    double sumNalogPay = yearProfit_i - sumNalogFree;

    if(sumNalogPay > 0){
        mustPay = (sumNalogPay*input_procentNalog)/100;
    }

return mustPay;
}

