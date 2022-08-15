#include "marketingmanager.h"

MarketingManager::MarketingManager()
{
	this->v_GoodsList.clear();
	this->m_NumberofGoods = 0;
}

QVector<const Goods*> MarketingManager::findGoods(QString key, int type)
{
	QVector<const Goods*> temp;
	// 0: ID  1: Name  2: Origin  3: DueDate 4: PurchaseDate
	//日期要求输入 0000/00/00 格式
	switch (type) {
	case 0:
		for_each(this->v_GoodsList.begin(),this->v_GoodsList.end(),[=,&temp](const Goods& g){
			if (g.m_ID == key.toUInt())
				temp.push_back(&g);
		});
		break;
	case 1:
		for_each(this->v_GoodsList.begin(),this->v_GoodsList.end(),[=,&temp](const Goods& g){
			if (g.m_Name == key)
				temp.push_back(&g);
		});
		break;
	case 2:
		for_each(this->v_GoodsList.begin(),this->v_GoodsList.end(),[=,&temp](const Goods& g){
			if (g.m_Origin == key)
				temp.push_back(&g);
		});
		break;
	case 3:
		for_each(this->v_GoodsList.begin(),this->v_GoodsList.end(),[=,&temp](const Goods& g){
			if (g.m_DueDate.toString("yyyy/MM/dd") == key)
				temp.push_back(&g);
		});
		break;
	case 4:
		for_each(this->v_GoodsList.begin(),this->v_GoodsList.end(),[=,&temp](const Goods& g){
			if (g.m_PurchaseDate.toString("yyyy/MM/dd") == key)
				temp.push_back(&g);
		});
		break;
	default:
		qDebug() << "输入类型错误\n";
		break;
	}
	return temp;
}

bool MarketingManager::addGoods(const Goods &g)
{
	auto flag = find_if(this->v_GoodsList.begin(),this->v_GoodsList.end(),[=](const Goods& good)->bool{
		return g.m_ID == good.m_ID;
	});//查找ID相同产品
	
	if (flag != this->v_GoodsList.end()) {
		//qDebug() << "Failed! the ID has already exist!";
		return false;//ID相同报错退出
	} 
	else {
		this->v_GoodsList.push_back(g);
		this->m_NumberofGoods++;
		//qDebug("添加成功");
		return true;
	}
}

bool MarketingManager::deleteGoods(unsigned int index)
{
	if (index < this->m_NumberofGoods){
		auto flag = this->v_GoodsList.begin();
		for (unsigned int var = 0; var < index; ++var)
			flag++;
		this->v_GoodsList.erase(flag);
		this->m_NumberofGoods--;
		return true;
		//qDebug() << "Success!\n";
	}
	else {
		return false;
		//qDebug() << "Index out of range!\n";
	}
	
}

void MarketingManager::deleteGoods(const Goods &g)//没有用到
{
	auto flag = find(this->v_GoodsList.begin(),this->v_GoodsList.end(),g);
	if (flag != this->v_GoodsList.end()) {
		this->v_GoodsList.erase(flag);
		this->m_NumberofGoods--;
		
		qDebug() << "Success!\n";
	} 
	else {
		qDebug() << "Input not found!\n";
	}
}

bool MarketingManager::saveGoodsFile(const QString &path)
{
	//根据传入文件夹的路径生成具体文件路径
	const QString FilePath = path + "/Goods.txt";
	
	QFile aFile(FilePath);
	if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text)) //保存为文本
		return false;
	QTextStream aStream(&aFile);//用文本流保存文件
	aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字
	
	aStream << this->m_NumberofGoods <<"\n";//写入数据量
	
	if(this->m_NumberofGoods > 0)
	{
		for (unsigned int i = 0; i < this->m_NumberofGoods; ++i) {
			this->v_GoodsList[i].saveGoods(aStream);
		}
	}
	aFile.close(); //关闭文件
	return true;	
}

bool MarketingManager::deleteGoodsFile(const QString &path)
{
	//根据传入文件夹的路径生成具体文件路径
	const QString FilePath = path + "/Goods.txt";
	
	if(FilePath.isEmpty()||!QDir().exists(FilePath))//是否传入了空的路径||路径是否存在
		return false;
	//清除容器
	this->v_GoodsList.clear();
	this->m_NumberofGoods = 0;
	//删除文件
	QFile::remove(FilePath);
	return true;
	
}

bool MarketingManager::readGoodsFile(const QString &path)
{
	//根据传入文件夹的路径生成具体文件路径
	const QString FilePath = path + "/Goods.txt";
	QFile aFile(FilePath);//打开文件
	if(!aFile.exists())//判断文件是否存在
		return false;
	if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	
	QTextStream aStream(&aFile); //用文本流读取文件
	aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字
	//格式化容器
	this->v_GoodsList.clear();
	this->m_NumberofGoods = 0;
	//先读入数据量
	aStream >> this->m_NumberofGoods;
	//利用循环读取数据
	if(this->m_NumberofGoods>0)
	{
		for(unsigned int i=0; i < this->m_NumberofGoods; i++)
		{
			unsigned int ID;//标号
			QString name;//品名
			QString origin;//产地
			double buyingPrice;//进价
			double amount;//数量
			double remaining;//剩余数量
			int Dyy,Dmm,Ddd,Pyy,Pmm,Pdd;
			
			aStream >> ID >> name;
			aStream >> origin;
			aStream >> buyingPrice;
			aStream >> amount >> remaining;
			aStream >> Dyy >> Dmm >> Ddd >> Pyy >> Pmm >> Pdd;
			
			this->v_GoodsList.push_back(Goods(ID,name,origin,buyingPrice,amount,remaining,QDate(Dyy,Dmm,Ddd),QDate(Pyy,Pmm,Pdd)));
		}
	}
	aFile.close();//关闭文件
	return true;
	
}

bool MarketingManager::saveAllFile(const QString &path)
{
	bool flag = this->saveGoodsFile(path);
	for (unsigned int i = 0; i < this->m_NumberofGoods; ++i) {
		if(!this->v_GoodsList[i].saveSalesFile(path))
			flag = false;
	}
	return flag;
}

bool MarketingManager::readAllFile(const QString &path)
{
	bool flag = this->readGoodsFile(path);
	for (unsigned int i = 0; i < this->m_NumberofGoods; ++i) {
		if(!this->v_GoodsList[i].readSalesFile(path))
			flag = false;
	}
	return flag;
	
}

bool MarketingManager::deleteAllFile(const QString &path)
{
	bool flag = true;
	for (unsigned int i = 0; i < this->m_NumberofGoods; ++i) {
		if(!this->v_GoodsList[i].deleteSalesFile(path))
			flag = false;
	}
	if(!this->deleteGoodsFile(path))
		flag = false;
	return flag;	
}
