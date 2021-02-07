HMI架构说明
一、	预览
本次全液晶仪表平台的HMI效果图如下：
![nod9ffmt6oclq5mi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/nod9ffmt6oclq5mi.png)
仪表平台的HMI开发工具基于Linux的QT5.11.2开发。QT具有优良的跨平台特性，其良好的封装机制使得QT的模块化程度非常高，可重用性较好，并且支持2D/3D图形渲染，支持OpenGL，对于开发者来说是非常方便的。
仪表 HMI的系统框图如下图所示： 
![0ablk6x8d3yjh5mi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/0ablk6x8d3yjh5mi.png)
1.	QML是画面描画层，负责画面/动画显示
2.	Screen是画面管理层，是QML对应的C++层，保持画面的显示数据与状态
3.	Control是业务逻辑层，负责接收底层数据，处理业务逻辑
4.	App是HMI的下层，向HMI提供信号数据。App 指的IVS、IVP、PowerMgr等编译生成的动态链接库。用于与IVS、IVP、PowerMgr等进程进行进程间通信。

二、HMI各层内容详细说明
1. QML：
 ![9j7h90yisv1dzpvi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/9j7h90yisv1dzpvi.png)
main.qml：是主画面画布，负责加载所有其他qml。也包含HMI入场出场转场等动画效果。
![jwalwf3a2izilik9](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/jwalwf3a2izilik9.png)
 
由于HMI采用双进程架构，大部分画面在Gauge进程，指针/油表/水温表在Point进程。
Gauge进程采用30帧，Point进程采用60帧。Gauge进程有动画，Point进程无动画。

1.1 Gauge: 包含车速表，转速表，燃油表，水温表
1.1.1车速表（数字式、指针式、异形式）
    
1.1.2转速表（数字式、指针式、异形式）
   
1.1.3 	燃油表（圆弧式、异形式）
   
1.1.4	水温表（圆弧式、异形式）
  
1.2 CarInfo: 包含小计里程，平均车速，平均油耗，瞬时油耗，保养里程，故障查询，胎压信息
1.2.1 小计里程
1.2.2平均车速
1.2.3平均油耗（曲线式）
 
1.2.4瞬时油耗
1.2.5保养里程
1.2.6故障查询
1.3 Interconnect: 包含电话，音乐（在线/蓝牙/USB），收音机，导航
1.3.1电话
1.3.2音乐
1.3.3收音机
1.3.4导航
1.4 ADAS: 包含车，车道线
1.5 Diag: 包含电检设置画面
1.6 Popup:报警信息，包含普通报警，安全带报警，胎压报警
1.7 Telltale: 包含指示灯
1.8 Setting: 包含设置画面
1.9 Home: 包含时间，温度，总计里程，续航里程
1.10 Update: 包含升级进度/提示信息



2. Screen：
 
类结构说明
![u7zrxbl22fadzpvi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/u7zrxbl22fadzpvi.png)
 
CBaseScreen：是所有Screen的基类。核心实现将自身C++类注册到QML中。
CSingleton：单例类。保证HMI进程生命周期只有一个实例对象。
createAppScreen: 调用registerAppScreen，创建Screen
registerAppScreen：把Screen注册到qml，让qml可以使用Screen的属性
ScreenParses：数组，包含Screen需要解析的信息id和对应函数
static ScreenDataParser screenParses[] {
    {PROPERTYID_LEFT_TURN, setLeftvisible },
    {PROPERTYID_RIGHT_TURN, setRightvisible },
};
	
2.1 Gauge: 负责更新画面的车速，转速，燃油，水温等信息
2.2 CarInfo: 负责更新画面的行车电脑/胎压信息等信息
2.3 Interconnect: 负责更新画面的互联等信息
2.4 ADAS: 负责更新画面的ADAS等信息
2.5 Diag: 负责更新画面的电检等信息
2.6 Popup: 负责更新画面的报警文言等信息
2.7 Telltale: 负责更新画面的指示灯等信息
2.8 Setting: 负责更新画面的设置等信息
2.9 Home: 负责更新画面的上下边缘等信息
2.10 Update: 负责更新升级画面的进度/提示等信息
2.11 Manager: 负责更新画面的按键迁移等信息，注册App回调函数，保证模块间通信/进程间通信

3. Control：
 
类结构说明
 ![kpooop5l3pyi7ldi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/kpooop5l3pyi7ldi.png)
CBaseControl：线程类，是所有Control的基类。CBaseControl继承QThread，主要实现消费者的功能，App传过来的数据做为生产者。CBaseControl负责将数据放入线程处理，并将数据发送给对应的Control模块。
CSingleton：单例类。保证HMI进程生命周期只有一个实例对象。
中间层掉用回调函数，通过pushData将数据输入到链表中，Control循环调用dataChange解析数据
 
Parsers：数组，包含Control需要解析的信息id和对应函数
static DataParser parsers[]
{
    {MSG_User2, func_MSG_User2},
    {MSG_User3, func_MSG_User3},
    {MSG_User4, func_MSG_User4},
};

3.1 Gauge: 负责处理车速，转速，燃油，水温的平滑计算
平滑算法是在GaugeControl里单独开辟一个GaugeThread线程，使用stepperCb函数计算平滑步进值，进而得到平滑后的数值。
3.2 CarInfo: 负责处理行车电脑/胎压信息的逻辑策略
3.3 Interconnect: 负责处理互联的逻辑策略
3.4 ADAS: 负责处理ADAS的逻辑策略
3.5 Diag: 负责处理电检的逻辑策略
3.6 Popup: 负责处理报警文言的逻辑策略
通用接口：
定时器接口 triggerTimeout100ms
电源接口 triggerPowerMode
按键接口 triggerHardKey
自检接口 triggerAutoCheckState
3.7 Telltale: 负责处理指示灯的逻辑策略
通用接口：
定时器接口 get_timeout500ms
策略接口 handle
电源接口 triggerPowerMode
自检接口 setautocheckSts
3.8 Setting: 负责处理设置的逻辑策略，包含电源/按键状态
3.9 Home: 负责处理画面的上下边缘信息的逻辑策略
3.10 Update: 负责升级画面的进度/提示的逻辑策略

三、HMI数据通信说明
1. 外部通信:
HMI进程与App的IVP/IVS/PM进程之间主要通过PPS进行通信。IVP/IVS/PM模块提供动态链接库（.so），动态链接库的主要功能是建立与IVP/IVS/PM进程的通信。HMI编译时链接IVP/IVS/PM的动态链接库，最终可以实现HMI与IVS/IVP/PM进程通信。
如下面框图所示：
 ![1vu4p1etbh60qkt9](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/1vu4p1etbh60qkt9.png)
	HMI	：HMI进程，仪表UI画面
	IVS		：IVS进程，传递车速、仪表状态信息模块。
	IVP		：IVP进程，传递IVI主机信息模块。
	PM:     :  PowerManager进程，传递电源信息模块。

1.1 接受数据
由于IVS/IVP通信频繁，尤其是IVS模块，每20ms就会通知HMI，此时如果HMI处理耗时的操作，会导致消息阻塞。所以仪表HMI在外部通信设计中采用了生产者和消费者模型，在Control中开辟一个线程作为消费者收集IVP/IVS数据，防止消息阻塞。
消费者和生产者模型如下：

 ![78ttl9l2vm2njyvi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/78ttl9l2vm2njyvi.png)

Class	概要
App CallBack	IVS、IVP的生产者线程，每20ms生产数据。
List<data>	双向链表，将生产者数据压入栈底。消费者从栈顶取出。
CBaseLib	包含消费者线程，通过while(false == m_messageList.empty())不断的从List<data>栈顶取数据。


具体的步骤如下：
1.	Control创建消费者线程，Manager使用libivs.so组件与IVS进行连接，调用init_connect() 与IVS建立连接，之后统一调用register_callback()函数注册func()。
2.	IVS监测到数据时，Manager的func()函数被调用，在func()函数中通过调用各个Control的pushData ()、push_back()将数据存入双向链表中，在消费者线程中通过pop_front函数将数据取出。
3.	各个Control调用dataChange函数，对数据分包处理，然后把处理结果通过信号发送给对应的Screen
4.	对应的Screen在收到信号之后进行属性设定。
1.2 发送数据
发送数据主要采用直接调用API的方式。HMI规定，与IVS.so通信的方式只能通过Control完成，Screen不可以直接与IVS.so有调用关系，流程如下：

1、	Screen发送信号通知Control。
2、	Control调用IVS.so的通知函数。
2. 内部通信:

1. Control:
1.1 普通信号流程
 
1.2 按键信号流程
 
1.3 电源信号流程
 
1.4 互联流程
 
1.5 Manager流程

 

2. Screen:
2.1 普通信号流程
 
2.2 按键信号流程
 
2.3 电源信号流程
 

2.4 画面迁移流程
 
3. Qml:
在Qt中QML和C++通信有很多种方式，在仪表HMI中主要采用其中Q_PROPERTY的一种方法。
该方法如下：
Q_PROPERTY(Type name READ getFunction WRITE setFunction NOTIFY notifySignal)
	Type			：定义的属性名字，可以在QML中引用。
	READ 		：定义对该属性名读时调用的函数。
	WRITE 		：定义对该属性名写时调用的函数。
	NOTIFY 	：当属性名字有更新时，通过调用notifySignal通知更新画面。
仪表HMI规定，为了保证代码易读性，QML和Control的通信只采用Q_PROPERTY的方法。

4. 进程间通信:
进程间通信使用Qt的QShareMemory模块，每个进程都有一个ShareMemory。ShareMemoryA负责创建共享内存，并往共享内存写数据，ShareMemoryB负责从共享内存读数据。通过设置共同名字的Key，来保证使用同一个共享内存区域。ShareMemoryA放入单独线程，周期20ms。ShareMemoryB放入单独线程，周期10ms。
 ![bguuwbqjkfzb0529](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/bguuwbqjkfzb0529.png)
 
为了防止数据丢失，Gauge进程会定周期给Point进程发送信息。周期为100ms。
5. 定周期通信:
 
四、HMI切换主题
Scenemanager是换肤框架的换肤管理器，负责动态卸载加载画面，qml画面会打包成rcc文件。切换主题时候，卸载加载rcc文件，实现切换主题。
时序图如下：
 ![ltgdtgahnou07ldi](https://github.com/Lveona/ProjectLibrary/blob/main/readmeImg/ltgdtgahnou07ldi.png)

五、HMI画面启动优化
在仪表HMI Framework中，整个HMI使用静态编译的方式，没有动态库so之说。HMI进程启动通过主动调用各个Screen的单例方法实现创建加载。
HMI启动时候先加载Control/Screen，后加载qml。main.qml使用Loader逐步加载，边加载边显示入场动画。字体采用ttf格式，在Main.qml用FontLoader加载。
经过优化，HMI可以在2s内看到第一帧画面。平时切换主题，加载/卸载rcc占用500ms加上出场/入场动画，可以做到1s左右看到新主题画面。主题切换过程支持特效动画。




