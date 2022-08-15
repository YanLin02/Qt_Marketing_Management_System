#include "findsaledatadialog.h"
#include "ui_findsaledatadialog.h"

FindSaleDataDialog::FindSaleDataDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FindSaleDataDialog)
{
	ui->setupUi(this);
	on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());	
}

FindSaleDataDialog::~FindSaleDataDialog()
{
	delete ui;
}

int FindSaleDataDialog::getType()
{
	return ui->comboBox->currentIndex();
}

QString FindSaleDataDialog::getKey()
{
	return ui->lineEdit->text();
}

void FindSaleDataDialog::on_comboBox_currentIndexChanged(int index)
{
	if(index == 0){
		//日期要求输入 0000/00/00 格式
		ui->lineEdit->setInputMask("0000/00/00");
		ui->lineEdit->setText("2000/01/01");
	}
	else if (index == 1 || index == 2) {
		//仅输入数字
		ui->lineEdit->setInputMask("");		
		
		QRegExp floating("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
		QValidator *validator_f = new QRegExpValidator(floating, ui->lineEdit);
		this->ui->lineEdit->setValidator(validator_f);
		ui->lineEdit->setText("");				
	}
	else if (index == 3){
		ui->lineEdit->setInputMask("");		
		QRegExp integer("[1-9][0-9]+$");
		QValidator *validator_i = new QRegExpValidator(integer, ui->lineEdit);
		this->ui->lineEdit->setValidator(validator_i);
		ui->lineEdit->setText("");				
	}
	else {
		ui->lineEdit->setInputMask("");	
		
		ui->lineEdit->setText("请输入 售出 或 退货");				
	}
}
