#include "goods.h"

Goods::Goods()
	:m_ID(0),m_Name("\0"),m_Origin("\0"),m_BuyingPrice(0),m_Amount(0),m_DueDate(QDate(0,0,0)),m_PurchaseDate(QDate(0,0,0))
{
	//清空销售数据	
	this->m_NumberofData = 0;
	this->v_SalesData.clear();
}

Goods::Goods(unsigned int id, QString name, QString org, double pric, double amou, QDate due, QDate purc)
	:m_ID(id),m_Name(name),m_Origin(org),m_BuyingPrice(pric),m_Amount(amou),m_Remaining(amou),m_DueDate(due),m_PurchaseDate(purc)
{
	//清空销售数据
	this->m_NumberofData = 0;
	this->v_SalesData.clear();
}

Goods::Goods(unsigned int id, QString name, QString org, double pric, double amou, double rem, QDate due, QDate purc)
	:m_ID(id),m_Name(name),m_Origin(org),m_BuyingPrice(pric),m_Amount(amou),m_Remaining(rem),m_DueDate(due),m_PurchaseDate(purc)
{
	//清空销售数据
	this->m_NumberofData = 0;
	this->v_SalesData.clear();
}

QVector<const Sale *> Goods::findSaleData(QString key, int type)
{
	// 0: 销售日期  1: 数量  2: 价格  3: 营业员工号 4: 业务类型（售出0、退货1）
	
	QVector<const Sale *> temp;
	switch (type) {
	case 0:
		for_each(this->v_SalesData.begin(),this->v_SalesData.end(),[=,&temp](const Sale& s){
			if (s.m_SaleDate.toString("yyyy/MM/dd") == key)
				temp.push_back(&s);});
		break;
	case 1:
		for_each(this->v_SalesData.begin(),this->v_SalesData.end(),[=,&temp](const Sale& s){
			if (s.m_Volume == key.toDouble())
				temp.push_back(&s);});
		break;
	case 2:
		for_each(this->v_SalesData.begin(),this->v_SalesData.end(),[=,&temp](const Sale& s){
			if (s.m_Price == key.toDouble())
				temp.push_back(&s);});		
		break;
	case 3:
		for_each(this->v_SalesData.begin(),this->v_SalesData.end(),[=,&temp](const Sale& s){
			if (s.m_EmployeeId == key.toUInt())
				temp.push_back(&s);});		
		break;
	case 4:
		for_each(this->v_SalesData.begin(),this->v_SalesData.end(),[=,&temp](const Sale& s){
			if (s.m_Activity == key.toInt())
				temp.push_back(&s);});		
		break;
	default:
		break;
	}
	return temp;
}

bool Goods::addSalesDate(const Sale& sa)
{
	if(sa.m_Activity == 0){//出货
		if (sa.m_SaleDate <= this->m_DueDate && sa.m_Volume <= this->m_Remaining){//判断保质期和数量
			this->v_SalesData.push_back(sa);//增加记录
			this->m_NumberofData++;//增加记录数量
			this->m_Remaining -= sa.m_Volume;//减少商品数量
			return true;
		}
		else {
			return false;			
		}
	}
	else {//退货
		this->v_SalesData.push_back(sa);//增加记录
		this->m_NumberofData++;//增加记录数量
		this->m_Remaining += sa.m_Volume;//增加商品数量
		return true;
	}
	//	if (sa.m_SaleDate <= this->m_DueDate && sa.m_Volume <= this->m_Remaining){//判断保质期和数量
	//		this->v_SalesData.push_back(sa);//增加记录
	//		this->m_NumberofData++;//增加记录数量
	//		if(sa.m_Activity == 1)
	//			this->m_Remaining -= sa.m_Volume;//减少商品数量
	//		else
	//			this->m_Remaining += sa.m_Volume;//减少商品数量
	//		//qDebug() << "Success!" << endl;
	//		return true;
	//	}
	//	else {
	//		//qDebug() << "Add saledata fail!" << endl;
	//		return false;
	//	}
}

bool Goods::deleteSalesDate(unsigned int index)
{
	if (index < this->m_NumberofData){
		auto flag = this->v_SalesData.begin();
		for (unsigned int var = 0; var < index; ++var)
			flag++;
		this->v_SalesData.erase(flag);
		this->m_NumberofData--;
		return true;
		//qDebug() << "Success!\n";
	}
	else {
		//qDebug() << "Index out of range!\n";
		return false;
	}
}

double Goods::getProfit(double price)
{
	return (price - this->m_BuyingPrice) / price;
}

double Goods::getProfit(unsigned int index)
{
	if (index < this->m_NumberofData){
		return (this->v_SalesData.at(index).m_Price - this->m_BuyingPrice) / this->v_SalesData.at(index).m_Price;
		qDebug() << "Success!\n";
	}
	else {
		qDebug() << "Index out of range!\n";
		return -1;
	}
}

bool Goods::operator==(const Goods &g)
{
	return this->m_ID == g.m_ID;
}

bool Goods::saveSalesFile(const QString &path)
{
	//根据传入文件夹的路径生成具体文件路径
	const QString FilePath = path + "/" +QString::number(this->m_ID) + ".txt";
	
	QFile aFile(FilePath);
	if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text)) //保存为文本
		return false;
	QTextStream aStream(&aFile);//用文本流保存文件
	aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字
	
	aStream << this->m_NumberofData <<"\n";//写入数据量
	
	if(this->m_NumberofData > 0)
	{
		for (unsigned int i = 0; i < this->m_NumberofData; ++i) {
			this->v_SalesData[i].saveData(aStream);
		}
	}
	aFile.close(); //关闭文件
	return true;	
}

bool Goods::deleteSalesFile(const QString &path)
{
	//根据传入文件夹的路径生成具体文件路径
	const QString FilePath = path + "/" +QString::number(this->m_ID) + ".txt";
	
	if(FilePath.isEmpty()||!QDir().exists(FilePath))//是否传入了空的路径||路径是否存在
		return false;
	//清除容器
	this->v_SalesData.clear();
	this->m_NumberofData = 0;
	//删除文件
	QFile::remove(FilePath);
	return true;
}

bool Goods::readSalesFile(const QString &path)
{
	const QString FilePath = path + "/" +QString::number(this->m_ID) + ".txt";
	
	QFile aFile(FilePath);//打开文件
	if(!aFile.exists())//判断文件是否存在
		return false;
	if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	
	QTextStream aStream(&aFile); //用文本流读取文件
	aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字
	//格式化容器
	this->v_SalesData.clear();
	this->m_NumberofData = 0;
	//先读入数据量
	aStream >> this->m_NumberofData;
	//利用循环读取数据
	if(this->m_NumberofData>0)
	{
		for(unsigned int i=0; i < this->m_NumberofData; i++)
		{
			int yy, mm, dd;
			double volume, price;
			unsigned int employeeId;
			int act;//业务类型（售出0、退货1）
			
			aStream >> yy >> mm >> dd;
			aStream >> volume >> price;
			aStream >> employeeId;
			aStream >> act;
			
			this->v_SalesData.push_back(Sale(QDate(yy,mm,dd),volume,price,employeeId,act));
		}
	}
	aFile.close();//关闭文件
	return true;
}

void Goods::saveGoods(QTextStream &aStream)
{
	aStream << m_ID <<" "<< m_Name << "\n";
	aStream << m_Origin <<"\n";
	aStream << m_BuyingPrice <<"\n";
	aStream << m_Amount <<" "<< m_Remaining <<"\n";
	aStream << m_DueDate.year() <<" "<< m_DueDate.month() <<" "<< m_DueDate.day() <<"\n";
	aStream << m_PurchaseDate.year() <<" "<< m_PurchaseDate.month() <<" "<< m_PurchaseDate.day() <<"\n";
}
