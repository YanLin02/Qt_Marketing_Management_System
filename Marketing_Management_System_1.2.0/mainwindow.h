#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QFileDialog>
#include "QStandardItemModel"
#include <QLabel>
#include <QTableWidgetSelectionRange>

#include "goods.h"
#include "marketingmanager.h"
#include "sale.h"

#include "newtabletab.h"
#include "addgoodsdialog.h"
#include "findgoodsdialog.h"
#include "calculateprofiledialog.h"
#include "addsaledatadialog.h"
#include "findsaledatadialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
	void refreshGoodsList();//刷新商品列表
	
	NewTableTab* addTab(const QString& tabName);//新建标签页
	
	int getChoosenLine();//获得当前选择的行号

	int getChoosenTab();//获得当前选择的页面
	
	void changePath(const QString& path);//修改路径
	
private slots:
	void on_a_openFile_triggered();
	
	void on_a_addGoods_triggered();
	
	void on_tabWidget_tabCloseRequested(int index);
	
	void on_a_saveFile_triggered();
	
	void on_a_saveAsAnother_triggered();
	
	void on_a_showSaleData_triggered();
	
	void on_a_deleteGoods_triggered();
	
	void on_a_findGoods_triggered();
	
	void on_a_getProfile_triggered();
	
	void on_a_addSaleData_triggered();
	
	void on_a_deleteSaleData_triggered();
	
	void on_a_deleteAllFile_triggered();
	
	void on_a_About_triggered();
	
	void on_GoodsTableView_doubleClicked(const QModelIndex &index);
	
	void on_a_FindSaleData_triggered();
	
private:
	Ui::MainWindow *ui;
	
	MarketingManager m_MKManager;
	QStandardItemModel* m_tableModel;
	
	QVector<NewTableTab*> v_newTables;
	unsigned int m_tabNumber;
	QVector<int> v_TabModes;
	//-1 系统界面  0 商品信息界面  1 销售信息界面  2 不可编辑界面信息
	
	QString m_currentPath;
	QLabel* p_pathLabel;
};
#endif // MAINWINDOW_H
