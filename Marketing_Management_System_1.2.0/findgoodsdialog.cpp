#include "findgoodsdialog.h"
#include "ui_findgoodsdialog.h"

FindGoodsDialog::FindGoodsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FindGoodsDialog)
{
	ui->setupUi(this);
	on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());
}

FindGoodsDialog::~FindGoodsDialog()
{
	delete ui;
}

int FindGoodsDialog::getType()
{
	return ui->comboBox->currentIndex();
}

QString FindGoodsDialog::getKey()
{
	return ui->lineEdit->text();
}

void FindGoodsDialog::on_comboBox_currentIndexChanged(int index)//格式设置
{
	if(index == 0){
		//仅输入数字
		ui->lineEdit->setInputMask("");		
		
		QRegExp integer("[1-9][0-9]+$");
		QValidator *validator_i = new QRegExpValidator(integer, ui->lineEdit);
		this->ui->lineEdit->setValidator(validator_i);
		ui->lineEdit->setText("");				
	}
	else if (index == 3 || index == 4) {
		//日期要求输入 0000/00/00 格式
		ui->lineEdit->setInputMask("0000/00/00");
		ui->lineEdit->setText("2000/01/01");
	}
	else {
		ui->lineEdit->setInputMask("");		
		ui->lineEdit->setText("");		
	}
}
