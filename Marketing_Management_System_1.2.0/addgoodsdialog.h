#ifndef ADDGOODSDIALOG_H
#define ADDGOODSDIALOG_H

#include <QDialog>

namespace Ui {
class addGoodsDialog;
}

class addGoodsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit addGoodsDialog(QWidget *parent = nullptr);
	~addGoodsDialog();
	
	///////////////////////////////获取信息区/////////////////////////////////
	
	QString getID();//标号
	QString getName();//品名
	
	QString getOrigin();//产地
	
	QString getBuyingPrice();//进价
	
	QString getAmount();//数量
	
	QDate getDueDate();//到期日期
	QDate getPurchaseDate();//进货日期
	
	
private:
	Ui::addGoodsDialog *ui;
};

#endif // ADDGOODSDIALOG_H
