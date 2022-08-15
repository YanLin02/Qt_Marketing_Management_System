#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	//不可编辑
	ui->GoodsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//整行选中
	ui->GoodsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	//初始化商品界面
	this->m_tableModel = new QStandardItemModel(this);
	ui->GoodsTableView->setModel(m_tableModel);
	
	
	//格式化表格界面向量
	this->v_newTables.clear();
	this->v_TabModes.clear();
	this->m_tabNumber = 0;
	
	//加一个为了同步index
	this->v_newTables.push_back(new NewTableTab());
	this->v_TabModes.push_back(-1);
	this->m_tabNumber++;
	
	//设定商品界面不可删除
	((QTabBar* )ui->tabWidget->tabBar())->setTabButton(0, QTabBar::RightSide, NULL);
	
	//状态栏设置
	this->p_pathLabel = new QLabel("当前未指定路径",this);
	ui->statusbar->addPermanentWidget(p_pathLabel);
	
	//右键菜单
	ui->tabWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
	ui->tabWidget->addAction(ui->a_addGoods);
	ui->tabWidget->addAction(ui->a_addSaleData);
	ui->tabWidget->addAction(ui->a_findGoods);
	ui->tabWidget->addAction(ui->a_showSaleData);
	ui->tabWidget->addAction(ui->a_getProfile);
	
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::refreshGoodsList()
{
	//初始化商品表格
	this->m_tableModel->clear();
	this->m_tableModel->setColumnCount(8);
	this->m_tableModel->setHorizontalHeaderLabels(QStringList()<<"标号"<<"品名"<<"产地"<<"进价"<<"数量"<<"库存"<<"到期日期"<<"进货日期");
	
	//获取并设置行数信息
	unsigned int rowNum = this->m_MKManager.m_NumberofGoods;
	this->m_tableModel->setRowCount(rowNum);
	
	//插入数据
	QStandardItem *aTempItem; //临时的item
	QString tempStr;
	for (unsigned int i = 0; i < rowNum; ++i) {
		Goods tempGoods = this->m_MKManager.v_GoodsList[i];//读取一个商品
		
		tempStr = QString::number(tempGoods.m_ID);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 0, aTempItem);
		
		tempStr = tempGoods.m_Name;
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 1, aTempItem);
		
		tempStr =tempGoods.m_Origin;
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 2, aTempItem);
		
		tempStr = QString::number(tempGoods.m_BuyingPrice);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 3, aTempItem);
		
		tempStr = QString::number(tempGoods.m_Amount);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 4, aTempItem);
		
		tempStr = QString::number(tempGoods.m_Remaining);
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 5, aTempItem);
		
		tempStr = tempGoods.m_DueDate.toString("yy-MM-dd");
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 6, aTempItem);
		
		tempStr = tempGoods.m_PurchaseDate.toString("yy-MM-dd");
		aTempItem = new QStandardItem(tempStr);
		this->m_tableModel->setItem(i, 7, aTempItem);
	}
}

NewTableTab* MainWindow::addTab(const QString &tabName)
{
	NewTableTab* temp = new NewTableTab(this);
	this->v_newTables.push_back(temp);//便于以后刷新
	
	temp->setAttribute(Qt::WA_DeleteOnClose);//关闭时删除
	ui->tabWidget->addTab(temp,tabName);
	
	ui->tabWidget->setCurrentWidget(temp);
	this->m_tabNumber++;				
	
	return temp;
}

int MainWindow::getChoosenLine()//获取当前选定的行
{
	QTableView *m_pTableView = ui->GoodsTableView;
	QModelIndexList selected = m_pTableView->selectionModel()->selectedRows();
	QList<int> rows;
	foreach( const QModelIndex & index, selected)
		rows.append( index.row() );
	if(rows.isEmpty())
		return -1;
	else
		return rows.at(0);
}

int MainWindow::getChoosenTab()//获取当前选定的页面
{
	return ui->tabWidget->currentIndex();
}

void MainWindow::changePath(const QString &path)
{
	this->m_currentPath = path;
	this->p_pathLabel->setText(path);
	
}

void MainWindow::on_a_openFile_triggered()//打开按钮按下后
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = "选择目标文件夹";
	
	//QFileDialog *fileDialog = new QFileDialog(this);
	//fileDialog->setFileMode(QFileDialog::Directory);
	QString path = QFileDialog::getExistingDirectory(this, dlgTitle, curPath);
	
	if(path.isEmpty())
		return;
	
	this->changePath(path);
	
	//打开文件
	this->m_MKManager.readAllFile(path);
	
	
	//刷新每个页面
	this->refreshGoodsList();
	ui->tabWidget->setCurrentWidget(ui->goodsTab);	
	
	//关闭其他界面
	int fin = this->m_tabNumber;
	for (int var = 1; var < fin ; ++var) {
		on_tabWidget_tabCloseRequested(1);
	}
	
	
}

void MainWindow::on_a_addGoods_triggered()//增加商品按钮按下后
{
	addGoodsDialog addGoodsDia(this);
	
	while (true) {
		int ret = addGoodsDia.exec();//展示窗口
		if(ret == QDialog::Accepted){//点击OK后读取信息
			//qDebug() << "Accepted!";
			QString ID = addGoodsDia.getID();//标号
			QString Name = addGoodsDia.getName();//品名
			
			QString Origin = addGoodsDia.getOrigin();//产地
			
			QString BuyingPrice = addGoodsDia.getBuyingPrice();//进价
			
			QString Amount = addGoodsDia.getAmount();//数量
			
			QDate DueDate = addGoodsDia.getDueDate();//到期日期
			QDate PurchaseDate = addGoodsDia.getPurchaseDate();//进货日期
			
			//判断信息是否完整
			if (ID.isEmpty()||Name.isEmpty()||Origin.isEmpty()||BuyingPrice.isEmpty()||Amount.isEmpty()) {
				QMessageBox::critical(&addGoodsDia,"添加商品","请将商品信息填写完整");
			} 
			else {
				//添加商品并判断是否成功
				bool isSuccess = this->m_MKManager.addGoods(Goods(ID.toUInt(),Name,Origin,BuyingPrice.toDouble(),Amount.toDouble(),DueDate,PurchaseDate));
				if (isSuccess){
					QMessageBox::information(&addGoodsDia,"添加商品","添加商品成功");
					break;
				}
				else{
					QMessageBox::critical(&addGoodsDia,"添加商品","添加失败：商品ID重复");
				}
			}
		}
		else {
			break;
		}
	}
	//刷新并保存
	this->refreshGoodsList();
	if(!this->m_currentPath.isEmpty())	
		this->m_MKManager.saveAllFile(this->m_currentPath);	
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)//tab关闭按钮按下后
{
	this->ui->tabWidget->removeTab(index);//移除Tab页面
	
	auto flag_1 = this->v_newTables.begin();//找到对应的迭代器
	for (int i = 0; i < index; ++i)
		flag_1++;
	delete *flag_1;
	this->v_newTables.erase(flag_1);
	
	auto flag_2 = this->v_TabModes.begin();//找到对应的迭代器
	for (int i = 0; i < index; ++i)
		flag_2++;
	this->v_TabModes.erase(flag_2);
	this->m_tabNumber--;
	
}

void MainWindow::on_a_saveFile_triggered()//保存按钮按下后
{
	if(this->m_currentPath.isEmpty()){
		//QMessageBox::critical(this,"保存文件","保存失败：未打开文件");
		//选择地址
		QString curPath = QDir::currentPath();
		QString dlgTitle = "选择目标文件夹";
		QString path = QFileDialog::getExistingDirectory(this, dlgTitle, curPath);
		if(path.isEmpty())
			return;
		//修改路径
		this->changePath(path);
	}
	if(this->m_MKManager.saveAllFile(this->m_currentPath))
		QMessageBox::information(this,"保存文件","保存成功");
	else
		QMessageBox::critical(this,"保存文件","保存失败");
}

void MainWindow::on_a_saveAsAnother_triggered()//转存按钮按下后
{
	//选择地址
	QString curPath = QDir::currentPath();
	QString dlgTitle = "选择目标文件夹";
	QString path = QFileDialog::getExistingDirectory(this, dlgTitle, curPath);
	if(path.isEmpty())
		return;
	//判断与当前是否一致
	if(path == this->m_currentPath){
		QMessageBox::information(this,"转存文件","选定路径与当前路径相同");
		this->on_a_saveFile_triggered();
		return;
	}
	if(this->m_MKManager.saveAllFile(path))
		QMessageBox::information(this,"转存文件","转存成功");
	else
		QMessageBox::critical(this,"转存文件","转存失败");
	
}

void MainWindow::on_a_showSaleData_triggered()//查看某商品的销售记录
{
	int tabIndex = getChoosenTab();
	if (this->v_TabModes[tabIndex] == -1) {//在主菜单选中商品
		//获取当前选定的行
		int rowNumber = this->getChoosenLine();
		if(rowNumber < 0){
			QMessageBox:: critical(this,"查看销售记录","请选择商品");
			return;
		}
		
		//名称拼接
		QString tabName;
		tabName = "["+QString::number(this->m_MKManager.v_GoodsList[rowNumber].m_ID)+"] "+this->m_MKManager.v_GoodsList[rowNumber].m_Name;
		
		//添加Tab界面并刷新
		addTab(tabName)->refreshSaleData(this->m_MKManager.v_GoodsList[rowNumber]);
		this->v_TabModes.push_back(1);
	}
	else if (this->v_TabModes[tabIndex] == 0) {
		int rowNumber = this->v_newTables[tabIndex]->getChoosenLine();
		if(rowNumber < 0){
			QMessageBox:: critical(this,"查看销售记录","请选择商品");
			return;
		}
		//通过this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]访问商品信息
		QString tabName;
		tabName = "["+QString::number(this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]->m_ID)+"] "+this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]->m_Name;
		addTab(tabName)->refreshSaleData(*(this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]));
		this->v_TabModes.push_back(1);
	}
}

void MainWindow::on_a_deleteGoods_triggered()//删除按钮按下后
{
	int rowNumber = this->getChoosenLine();
	if(rowNumber < 0){
		QMessageBox:: critical(this,"删除商品","请选择商品");
		return;
	}
	
	if(!this->m_currentPath.isEmpty())
		this->m_MKManager.v_GoodsList[rowNumber].deleteSalesFile(this->m_currentPath);
	
	if(this->m_MKManager.deleteGoods(rowNumber))
		QMessageBox::information(this,"删除商品","删除成功");
	else
		QMessageBox:: critical(this,"删除商品","删除失败");
	//刷新并保保存
	this->refreshGoodsList();
	if(!this->m_currentPath.isEmpty())	
		this->m_MKManager.saveAllFile(this->m_currentPath);
}

void MainWindow::on_a_findGoods_triggered() //查找按钮按下后
{
	FindGoodsDialog findGoodsDia(this);
	
	while (true) {
		int ret = findGoodsDia.exec();//展示窗口
		if(ret == QDialog::Accepted){//点击OK后读取信息
			int type = findGoodsDia.getType();
			QString key = findGoodsDia.getKey();
			
			if(key.isEmpty())
				QMessageBox::critical(&findGoodsDia,"查找商品","请将商品信息填写完整");
			else{
				auto resultList = this->m_MKManager.findGoods(key,type);
				//名称拼接
				QString tabName;
				tabName = "["+key+"] 的查找结果";
				
				//添加Tab界面并刷新
				addTab(tabName)->refreshGoodsList(resultList,resultList.size());
				this->v_TabModes.push_back(0);
				return;
			}
		}
		else {
			return;
		}
	}
}

void MainWindow::on_a_getProfile_triggered() //计算利率
{
	CalculateProfileDialog CPDia(this);
	
	int tabIndex = getChoosenTab();
	if (this->v_TabModes[tabIndex] == 1){//选中销售记录查看,自动填入信息
		int rowNumber = this->v_newTables[tabIndex]->getChoosenLine();
		if(rowNumber >= 0){
			CPDia.setBuyingPrice(this->v_newTables[tabIndex]->p_goods->m_BuyingPrice);
			CPDia.setSalePrice(this->v_newTables[tabIndex]->p_goods->v_SalesData[rowNumber].m_Price);
			CPDia.setSaleNum(this->v_newTables[tabIndex]->p_goods->v_SalesData[rowNumber].m_Volume);
			CPDia.on_pushButton_clicked();
		}
	}
	else if(this->v_TabModes[tabIndex] == -1){//选中商品查看,自动填入信息
		int rowNumber = this->getChoosenLine();
		if(rowNumber >= 0){
			CPDia.setBuyingPrice(this->m_MKManager.v_GoodsList[rowNumber].m_BuyingPrice);
		}
	}
	else if(this->v_TabModes[tabIndex] == 0){//在查找后选中商品自动填入信息
		int rowNumber = this->v_newTables[tabIndex]->getChoosenLine();
		if(rowNumber >= 0){
			CPDia.setBuyingPrice(this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]->m_BuyingPrice);
		}
	}
	CPDia.exec();
}

void MainWindow::on_a_addSaleData_triggered() //增加销售
{
	int tabIndex = getChoosenTab();
	if (this->v_TabModes[tabIndex] == 1){//选中销售记录
		//采用this->v_newTables[tabIndex]->p_goods获取商品信息
		AddSaleDataDialog ASDDia(this->v_newTables[tabIndex]->p_goods->m_Name);
		while (true) {
			int ret = ASDDia.exec();//展示窗口
			if(ret == QDialog::Accepted){//点击OK后读取信息
				
				QDate SaleDate = ASDDia.getSaleDate();//销售日期
				
				QString Volume = ASDDia.getVolume();//数量
				
				QString Price = ASDDia.getPrice();//价格
				
				QString EmployeeId = ASDDia.getEmployeeId();//营业员工号
				
				int Activity = ASDDia.getActivity();//业务类型（售出0、退货1）
				
				//判断信息是否完整
				if (Volume.isEmpty()||Price.isEmpty()||EmployeeId.isEmpty()) {
					QMessageBox::critical(&ASDDia,"新增记录","请将销售信息填写完整");
				} 
				else {
					//添加销售信息并判断是否成功
					double Pri = Price.toDouble();
					if(Activity == 1)//退货收入为负
						Pri *= -1;
					bool isSuccess = this->v_newTables[tabIndex]->p_goods->addSalesDate(Sale(SaleDate,Volume.toDouble(),Pri,EmployeeId.toUInt(),Activity));
					if (isSuccess){
						QMessageBox::information(&ASDDia,"新增记录","添加记录成功");
						break;
					}
					else{
						QMessageBox::critical(&ASDDia,"新增记录","添加失败：商品已到期或库存不足");
					}
				}
			}
			else {
				break;
			}
		}
		//刷新
		this->refreshGoodsList();
		this->v_newTables[tabIndex]->refreshSaleData(*(this->v_newTables[tabIndex]->p_goods));
	}
	else if (this->v_TabModes[tabIndex] == -1) {//在主菜单选中商品
		int rowNumber = this->getChoosenLine();
		if(rowNumber < 0){
			QMessageBox:: critical(this,"新增记录","请选择商品或销售记录");
			return;
		}
		AddSaleDataDialog ASDDia(this->m_MKManager.v_GoodsList[rowNumber].m_Name);
		while (true) {
			int ret = ASDDia.exec();//展示窗口
			if(ret == QDialog::Accepted){//点击OK后读取信息
				
				QDate SaleDate = ASDDia.getSaleDate();//销售日期
				
				QString Volume = ASDDia.getVolume();//数量
				
				QString Price = ASDDia.getPrice();//价格
				
				QString EmployeeId = ASDDia.getEmployeeId();//营业员工号
				
				int Activity = ASDDia.getActivity();//业务类型（售出0、退货1）
				
				
				//判断信息是否完整
				if (Volume.isEmpty()||Price.isEmpty()||EmployeeId.isEmpty()) {
					QMessageBox::critical(&ASDDia,"新增记录","请将销售信息填写完整");
				} 
				else {
					//添加销售信息并判断是否成功
					double Pri = Price.toDouble();
					if(Activity == 1)
						Pri *= -1;
					bool isSuccess = this->m_MKManager.v_GoodsList[rowNumber].addSalesDate(Sale(SaleDate,Volume.toDouble(),Pri,EmployeeId.toUInt(),Activity));
					if (isSuccess){
						QMessageBox::information(&ASDDia,"新增记录","添加记录成功");
						break;
					}
					else{
						QMessageBox::critical(&ASDDia,"新增记录","添加失败：商品已到期或库存不足");
					}
				}
			}
			else {
				break;
			}
		}
		//刷新
		this->refreshGoodsList();
	}
	else if (this->v_TabModes[tabIndex] == 0) {//位于搜索界面选中商品
		int rowNumber = this->v_newTables[tabIndex]->getChoosenLine();
		if(rowNumber < 0){
			QMessageBox:: critical(this,"新增记录","请选择商品或销售记录");
			return;
		}
		//通过this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]访问商品信息
		AddSaleDataDialog ASDDia(this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]->m_Name);
		while (true) {
			int ret = ASDDia.exec();//展示窗口
			if(ret == QDialog::Accepted){//点击OK后读取信息
				
				QDate SaleDate = ASDDia.getSaleDate();//销售日期
				
				QString Volume = ASDDia.getVolume();//数量
				
				QString Price = ASDDia.getPrice();//价格
				
				QString EmployeeId = ASDDia.getEmployeeId();//营业员工号
				
				int Activity = ASDDia.getActivity();//业务类型（售出0、退货1）
				
				
				//判断信息是否完整
				if (Volume.isEmpty()||Price.isEmpty()||EmployeeId.isEmpty()) {
					QMessageBox::critical(&ASDDia,"新增记录","请将销售信息填写完整");
				} 
				else {
					//添加销售信息并判断是否成功
					double Pri = Price.toDouble();
					if(Activity == 1)
						Pri *= -1;
					bool isSuccess = ((Goods*)(this->v_newTables[tabIndex]->v_p_goodsList[rowNumber]))->addSalesDate(Sale(SaleDate,Volume.toDouble(),Pri,EmployeeId.toUInt(),Activity));
					if (isSuccess){
						QMessageBox::information(&ASDDia,"新增记录","添加记录成功");
						break;
					}
					else{
						QMessageBox::critical(&ASDDia,"新增记录","添加失败：商品已到期或库存不足");
					}
				}
			}
			else {
				break;
			}
		}
		//刷新
		this->refreshGoodsList();
		this->v_newTables[tabIndex]->refreshGoodsList(this->v_newTables[tabIndex]->v_p_goodsList,this->v_newTables[tabIndex]->v_p_goodsList.size());
	}
	
	//保存
	if(!this->m_currentPath.isEmpty())	
		this->m_MKManager.saveAllFile(this->m_currentPath);
}

void MainWindow::on_a_deleteSaleData_triggered()//删除记录
{
	int tabIndex = getChoosenTab();
	if (this->v_TabModes[tabIndex] != 1){//选中销售记录
		QMessageBox:: critical(this,"删除记录","请选择可编辑的销售记录");
		return;
	}
	//采用this->v_newTables[tabIndex]->p_goods获取商品信息
	int rowNumber = this->v_newTables[tabIndex]->getChoosenLine();
	if(rowNumber < 0){
		QMessageBox:: critical(this,"删除记录","请选择销售记录");
		return;
	}
	if(this->v_newTables[tabIndex]->p_goods->deleteSalesDate(rowNumber))
		QMessageBox::information(this,"删除记录","删除成功");
	else
		QMessageBox:: critical(this,"删除记录","删除失败");		
	
	//刷新
	this->refreshGoodsList();
	this->v_newTables[tabIndex]->refreshSaleData(*(this->v_newTables[tabIndex]->p_goods));
	
	//保存
	if(!this->m_currentPath.isEmpty())	
		this->m_MKManager.saveAllFile(this->m_currentPath);
	
}

void MainWindow::on_a_deleteAllFile_triggered()
{
	if(this->m_currentPath.isEmpty())
		return;
	QMessageBox::StandardButton result = QMessageBox::warning(this,"删除文件","你确定要删除吗？",QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel);
	if(result == QMessageBox::Yes){
		if(this->m_MKManager.deleteAllFile(m_currentPath))
			QMessageBox::information(this,"删除文件","删除成功");
		else 
			QMessageBox:: critical(this,"删除文件","删除失败");
	}
	this->refreshGoodsList();
	//关闭其他界面
	int fin = this->m_tabNumber;
	for (int var = 1; var < fin ; ++var) {
		on_tabWidget_tabCloseRequested(1);
	}
	
}

void MainWindow::on_a_About_triggered()
{
	QMessageBox::about(this,"关于商品销售管理系统","       JS121418\n      孙彦林制作\nQQ:1310400098");
}

void MainWindow::on_GoodsTableView_doubleClicked(const QModelIndex &index)
{
    this->on_a_showSaleData_triggered();
}

void MainWindow::on_a_FindSaleData_triggered()
{
	int tabIndex = getChoosenTab();	
	if (this->v_TabModes[tabIndex] != 1){//选中销售记录
		QMessageBox:: critical(this,"查找信息","请选择销售记录");
		return;
	}
	//采用this->v_newTables[tabIndex]->p_goods获取商品信息
	
	FindSaleDataDialog FSDDia(this);
	
	while (true) {
		int ret = FSDDia.exec();//展示窗口
		if(ret == QDialog::Accepted){//点击OK后读取信息
			int type = FSDDia.getType();
			QString key = FSDDia.getKey();
			
			if(key.isEmpty())
				QMessageBox::critical(&FSDDia,"查找信息","请将商品信息填写完整");
			else{
				auto resultList = this->v_newTables[tabIndex]->p_goods->findSaleData(key,type);
				//名称拼接
				QString tabName;
				tabName = "["+key+"] 的查找结果(不可编辑)";
				
				//添加Tab界面并刷新
				addTab(tabName)->refreshSaleData(resultList);
				this->v_TabModes.push_back(2);
				return;
			}
		}
		else {
			return;
		}
	}
	
}
