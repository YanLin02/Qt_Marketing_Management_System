#ifndef FINDSALEDATADIALOG_H
#define FINDSALEDATADIALOG_H

#include <QDialog>

namespace Ui {
class FindSaleDataDialog;
}

class FindSaleDataDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit FindSaleDataDialog(QWidget *parent = nullptr);
	~FindSaleDataDialog();
	
	int getType();//获取查找类型
	
	QString getKey();//获取查找关键词
	
private slots:
	void on_comboBox_currentIndexChanged(int index);
	
private:
	Ui::FindSaleDataDialog *ui;
};

#endif // FINDSALEDATADIALOG_H
