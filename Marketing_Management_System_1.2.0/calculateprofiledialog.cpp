#include "calculateprofiledialog.h"
#include "ui_calculateprofiledialog.h"

CalculateProfileDialog::CalculateProfileDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CalculateProfileDialog),
	m_buyingPrice(0),m_salePrice(0)
{
	ui->setupUi(this);
	
	//格式限制
	QRegExp floating("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
	QValidator *validator_f1 = new QRegExpValidator(floating, ui->buyPriceLine);
	this->ui->buyPriceLine->setValidator(validator_f1);
	
	QValidator *validator_f2 = new QRegExpValidator(floating, ui->salePriceLine);
	this->ui->salePriceLine->setValidator(validator_f2);
	
	QValidator *validator_f3 = new QRegExpValidator(floating, ui->sale_Amount);
	this->ui->sale_Amount->setValidator(validator_f3);
	
}

CalculateProfileDialog::~CalculateProfileDialog()
{
	delete ui;
}

void CalculateProfileDialog::setBuyingPrice(double p)
{
	ui->buyPriceLine->setText(QString::number(p));
	this->m_buyingPrice = p;
}

void CalculateProfileDialog::setSalePrice(double p)
{
	ui->salePriceLine->setText(QString::number(p));
	this->m_salePrice = p;
}

void CalculateProfileDialog::setSaleNum(double p)
{
	ui->sale_Amount->setText(QString::number(p));
	this->m_saleNum = p;
}

void CalculateProfileDialog::on_pushButton_clicked()//计算按下后
{
	if(ui->salePriceLine->text().isEmpty()||ui->buyPriceLine->text().isEmpty()||ui->sale_Amount->text().isEmpty()){
		QMessageBox::critical(this,"计算利润","请将数据填写完整");
		return;
	}
	double final = (m_salePrice - m_buyingPrice)/m_buyingPrice * 100;
	QString temp = QString::number(final) + " %";
	ui->finishLine->setText(temp);
	
	double get = (m_salePrice - m_buyingPrice) * m_saleNum;
	ui->getWhat->setText(QString::number(get));
	
}

void CalculateProfileDialog::on_buyPriceLine_editingFinished()
{
	this->m_buyingPrice = ui->buyPriceLine->text().toDouble();
	//qDebug() << m_buyingPrice<<"\n============\n";
}

void CalculateProfileDialog::on_salePriceLine_editingFinished()
{
	this->m_salePrice = ui->salePriceLine->text().toDouble();
	
}

void CalculateProfileDialog::on_sale_Amount_editingFinished()
{
    this->m_saleNum = ui->sale_Amount->text().toDouble();
}
