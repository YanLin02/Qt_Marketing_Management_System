#include "addgoodsdialog.h"
#include "ui_addgoodsdialog.h"

addGoodsDialog::addGoodsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::addGoodsDialog)
{
	ui->setupUi(this);
	
	//设置输入格式限制
	QRegExp integer("[1-9][0-9]+$");
	QValidator *validator_i = new QRegExpValidator(integer, ui->IDEdit);
	this->ui->IDEdit->setValidator(validator_i);
	
	QRegExp floating("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
	QValidator *validator_f1 = new QRegExpValidator(floating, ui->PriceEdit);
	this->ui->PriceEdit->setValidator(validator_f1);
	
	QValidator *validator_f2 = new QRegExpValidator(floating, ui->NumberEdit);
	this->ui->NumberEdit->setValidator(validator_f2);
	
	
}

addGoodsDialog::~addGoodsDialog()
{
	delete ui;
}

QString addGoodsDialog::getID()
{
	return this->ui->IDEdit->text();
}

QString addGoodsDialog::getName()
{
	return this->ui->NameEdit->text();
}

QString addGoodsDialog::getOrigin()
{
	return this->ui->OriginEdit->text();
}

QString addGoodsDialog::getBuyingPrice()
{
	return this->ui->PriceEdit->text();
}

QString addGoodsDialog::getAmount()
{
	return this->ui->NumberEdit->text();
}

QDate addGoodsDialog::getDueDate()
{
	return this->ui->DueEdit->date();
}

QDate addGoodsDialog::getPurchaseDate()
{
	return this->ui->PurchaseEdit->date();
}

