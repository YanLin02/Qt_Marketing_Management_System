#include "addsaledatadialog.h"
#include "ui_addsaledatadialog.h"

AddSaleDataDialog::AddSaleDataDialog(const QString& GoodsName, QWidget *parent):
	QDialog(parent),
	ui(new Ui::AddSaleDataDialog)
{
	ui->setupUi(this);
	
	ui->GoodsName->setText(GoodsName);
	
	//格式设置
	QRegExp integer("[1-9][0-9]+$");
	QValidator *validator_i = new QRegExpValidator(integer, ui->OperatorID);
	this->ui->OperatorID->setValidator(validator_i);
	
	QRegExp floating("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
	
	QValidator *validator_f1 = new QRegExpValidator(floating, ui->SaleNumber);
	this->ui->SaleNumber->setValidator(validator_f1);
	
	
	QValidator *validator_f2 = new QRegExpValidator(floating, ui->SalePrice);
	this->ui->SalePrice->setValidator(validator_f2);
	
}

AddSaleDataDialog::~AddSaleDataDialog()
{
	delete ui;
}

QDate AddSaleDataDialog::getSaleDate()
{
	return ui->dateEdit->date();
}

QString AddSaleDataDialog::getVolume()
{
	return ui->SaleNumber->text();
}

QString AddSaleDataDialog::getPrice()
{
	return ui->SalePrice->text();
}

QString AddSaleDataDialog::getEmployeeId()
{
	return ui->OperatorID->text();
}

int AddSaleDataDialog::getActivity()
{
	return ui->OperationType->currentIndex();
}

void AddSaleDataDialog::on_OperationType_currentIndexChanged(int index)
{
	this->actNow = index;
	if(index == 1){
		ui->text_need_edit->setText("退款金额：");
	}
	else {
		ui->text_need_edit->setText("销售价格：");		
	}
}
