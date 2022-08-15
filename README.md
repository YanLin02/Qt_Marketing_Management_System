

# Qt_Marketing_Management_System

**2022暑期学校语言课程设计大作业**



> 今日我们相聚于此, 是为了纪念Qt大作业的完成。它的完成对于所有「学生」而言, 值得足足两个星期的自由鼓励。



## 题目

***题目八： 商品销售管理系统***

[要求] 该系统需创建和管理以下信息：
1、商品信息：标号、品名、产地、进价、数量、 到期日期、进货日期、销售数据集；
2、销售信息：销售日期、数量、价格、营业员工号、 业务类型（售出、退货）。 

系统功能要求如下： 
1．创建和管理描述商品基本信息的类； 
2．创建和管理描述特定销售的类； 
3．销售业务，在商品类中添加销售信息（售货、退货），添加时应考虑商品是否有货、 过期等； 
4．基本查询功能：按商品查询、按销售日期查询等； 
5．数据文件读写：文件中包含所有商品信息、每个商品的销售记录等数据；
6．基本信息显示：1）显示所有商品库存信息；2）显示特定商品的销售详情； 
7．可选功能提升：查询指定商品的存货、毛利等。



## 任务分析

- l 创建管理类（存放商品），商品类（存放商品信息及该商品的销售数据），销售数据类（存放一条销售数据中拥有的信息）

- l 管理类应具有添加/删除商品的功能。

- l 商品类应具有添加/删除销售的功能，且要进行相应验证。

- l 管理类应具有根据关键词查找商品的功能。

- l 商品类应具有根据关键词查找销售的功能

- l 管理类应具有在给定路径写入/读取文件的功能，永久保存数据。

- l 商品库存应在添加销售记录后实时变化。

- l 可以查询指定商品/销售信息的毛利。

- l 创建GUI，使操作简明易懂。

- l 但操作不规范使弹出警号和错误。

- l 为按钮添加图标。

- l 添加右键菜单。

- l 实现不同Tab页面的功能协调。

- l 显示当前文件路径

  

## 设计思路与流程

**先从C++功能入手：**

​		创建`Sale`、`Goods`和`MarketingManager`数据类，存储相关数据。  

​		为数据类添加功能函数。  

**创建Qt相关内容：**  

​		创建Qt设计师界面类，设计多个功能对话框。  

​		为功能对话框添加输入限制与功能函数。  

​		创建`NewTableTab`设计师界面类，构建Tab界面模板。  

​		在UI界面添加功能按钮，程序界面初步完成。  

​		在`MainWindow`中添加代码，实现Tab界面的切换和关闭。  

**C++部分与Qt部分耦合：**  

​		向`MainWindow`中添加代码，绑定功能与槽函数。  

​		测试允许并debug。  



## 功能介绍

- l 读取、写入文件，实现数据永久保存。
- l 按关键词查找数据。
- l 添加或删除数据。
- l 有序展示数据。
- l 显示存货。
- l 显示毛利。
- l 使用指针，实现数据一致性。
- l 对输入加以限制。
- l 右键菜单，双击功能



## 文件与对象描述

`sale.h/.cpp`: 包含`Sale`类，具有存储销售信息的数据成员，通过构造函数可以为信息赋值，成员函数`saveData`可以向指定文件流中依次传输数据。

`goods.h/.cpp`: 包含`Goods`类，具有存储商品信息的数据成员，通过构造函数可以为信息赋值，另有`m_Remaining` 成员储存剩余数量，`v_SalesData`成员利用`QVector<Sale>` 保存销售数据，`m_NumberofData`存储销售数据集数据量便于维护。成员函数`findSaleData`传入查找类型和关键词查找指定销售信息，返回`QVector<const Sale*>`类型，存储查找到的销售信息的指针。成员函数`addSalesDate`，`deleteSalesDate`用于在检测后添加或删除销售信息。重载==便于使用算法库。另有`saveSalesFile`，`deleteSalesFile`，`readSalesFile`函数用于处理销售信息文件，成员函数`saveGoods`可以向指定文件流中依次传输数据*

`marketingmanager.h/.cpp`: 包含`MarketingManager`类，具有`QVector<Goods>`类型成员 `v_GoodsList`存储商品清单，`m_NumberofGoods` 成员存储商品数量。成员函数`findGoods`传入查找类型和关键词查找指定商品信息，返回`QVector<const  Goods*>`类型，存储查找到的商品的指针。`findGoods`，`deleteGoods`用于在检测后添加或删除商品，另有`saveGoodsFile`，`deleteGoodsFile`，`readGoodsFile`函数用于处理商品信息文件，成员函数`saveAllFile`，`readAllFile` `deleteAllFile`处理所有文件。

`mainwindow.h/.cpp`: 操作主窗口，包含ui文件，成员包含商品信息存储及管理类`m_MKManager`，表格模型指针`m_tableModel`，当前路径`m_currentPath`，状态栏标签指针`p_pathLabel`，以及用于标签页管理的`v_newTables`，`m_tabNumber`和`v_TabModes`，分别储存各个标签页句柄，标签页数量，各个标签页类型。构造函数初始化成员并进行格式设定，同时设置右键菜单。成员函数有刷新商品列表的`refreshGoodsList`，新建标签页的`addTab`，获得当前选择的行号的`getChoosenLine`，获得当前选择的页面的`getChoosenTab`，修改路径的`changePath`以及各种按钮的槽函数。 

`newtabletab.h/.cpp`: 包含`NewTableTab`类，是新建标签页的模板，具有两种存放方式，显示销售数据时采用`refreshSaleData`刷新，使用p_goods 存放相关信息，而显示商品清单时采用`refreshGoodsList`刷新，使用`v_p_goodsList`存放相关信息。两者均可使用`getChoosenLine`获得当前选定的行数。 

`addgoodsdialog.h/.cpp`: 包含`addGoodsDialog`类，是创建新商品时输入信息的窗口，具有获取各个信息的函数，在构造函数限制输入。

`addsaledatadialog.h/.cpp`: 包含`AddSaleDataDialog`类，是创建新销售时的输入窗口，具有获取各个信息的函数，在构造函数限制输入。 

`caculateprofiledialog.h/.cpp`: 包含`CalculateProfileDialog`类，包含计算利润的算法和ui。

`findgoodsdialog.h/.cpp`: 包含`FindGoodsDialog`类，包含查找类型和信息的输入窗口。

`findsaledatadialog.h/.cpp`: 包含`FindSaleDataDialog`类包含查找类型和信息的输入窗口。  



## 总结

经过一定时间的开发，我完成了商品销售管理系统。

在研发过程中，我学会了图形化界面开发的基本方法，自学了格式限制（正则表达式），右键菜单等功能，初步了解了Qt这一重量级计算机编程。

经过在C++层面的摸索，我感悟到指针在程序方面的重要作用，学会了lambda表达式、算法库和函数指针。

可以说，倘若没有移动设备的兴起，未来的PC便是Qt的天下。
