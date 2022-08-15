#ifndef FINDGOODSDIALOG_H
#define FINDGOODSDIALOG_H

#include <QDialog>

namespace Ui {
class FindGoodsDialog;
}

class FindGoodsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit FindGoodsDialog(QWidget *parent = nullptr);
	~FindGoodsDialog();
	
	int getType();//获取查找类型
	
	QString getKey();//获取查找关键词
	
private slots:
	void on_comboBox_currentIndexChanged(int index);
	
private:
	Ui::FindGoodsDialog *ui;
};

#endif // FINDGOODSDIALOG_H
