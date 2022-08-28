/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 1.0.2
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.08.09
**
****************************************************************************/
#include "mainwindow.h"
#include "Log/flog.h"
#include "Universal/universal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , center_window_( new CenterWindow)
    , serial_(new serial_port::MasterSerialThread)
{
  el::Loggers::removeFlag(el::LoggingFlag::NewLineForContainer);
  el::Helpers::installLogDispatchCallback<LogHandler>("LogHandler");
  el::Helpers::installLogDispatchCallback<HtmlHandler>("HtmlHandler");
  LOG(INFO) << "Starting log";
  LogHandler* logHandler = el::Helpers::logDispatchCallback<LogHandler>("LogHandler");
  logHandler->setEnabled(false);
  //    InitUI();
  setCentralWidget(center_window_);  // 设置主窗体

  InitBar();  // Initial menu bar tool bar and status ber
  ConnectSignal();
  resize(1080, 720);
}

MainWindow::~MainWindow()
{
}


void MainWindow::InitUI()
{
    center_window_ = new CenterWindow;
}

void MainWindow::InitBar()
{
#if 0
    QMenuBar *menu_bar = new QMenuBar(this);             //创建一个菜单栏
    this->setMenuBar(menu_bar);                                         //设置为MainWindow的菜单栏
    QToolBar *tool_bar = new QToolBar(this);                    //创建一个工具栏
    this->addToolBar(tool_bar);                                            //添加工具栏到MainWindow
    QStatusBar *status_bar = new QStatusBar(this);            //创建一个状态栏
    this->setStatusBar(status_bar);                                        //设置为MainWindow的状态栏

    //创建菜单
    QMenu *file_menu = new QMenu("文件(&F)",menu_bar);
    QMenu *edit_menu = new QMenu("编辑(&E)",menu_bar);
    QMenu *help_menu = new QMenu("帮助(&H)",menu_bar);

    //创建动作
    QAction *new_action = new QAction("新建(&N)");
    QAction *open_action = new QAction("打开(&O)");
    QAction *save_action = new QAction("保存(&S)");

    //添加状态栏提示
    new_action->setStatusTip("新建一个文件或项目");
    open_action->setStatusTip("打开一个文件或项目");
    save_action->setStatusTip("保存");

    //添加动作到新建菜单，QAction就会自动变成子菜单
    file_menu->addAction(new_action);
    file_menu->addAction(open_action);
    file_menu->addSeparator();                      //添加菜单分隔符
    file_menu->addAction(save_action);

    //给编辑菜单添加子菜单
    edit_menu->addAction("剪切(&T)");
    //给帮助菜单添加子菜单
    help_menu->addAction("关于(&A)");

    //把菜单添加到菜单栏
    menu_bar->addMenu(file_menu);
    menu_bar->addMenu(edit_menu);
    menu_bar->addMenu(help_menu);

    //把动作添加到工具栏，QAction就会自动变成工具
    tool_bar->addAction(new_action);
    tool_bar->addAction(open_action);
    tool_bar->addAction(save_action);
#endif
    menubar_ = new QMenuBar(this);
    this->setMenuBar(menubar_);
    QMenu *save_menu = new QMenu("保存(&S)", menubar_);
    QMenu *help_menu = new QMenu("帮助(&H)", menubar_);
    menubar_->addMenu(save_menu);
    menubar_->addMenu(help_menu);

    //创建动作
    QAction *save_edr_data_action = new QAction("EDRData(&SD)");
    save_edr_data_action->setIcon(QIcon(":/image/Image/save_data.jpg"));  // 设置图标
    QAction *save_acu_data_action = new QAction("ACUData(&SD)");
//    save_acu_data_action->setIcon(QIcon(":/image/Image/save_data.jpg"));  // 设置图标
    QAction *save_curve_action = new QAction("SaveCurve(&SC)");
    save_curve_action->setIcon(QIcon(":/image/Image/save_curve.jpg"));
    QAction *clear_data_cation = new QAction("ClearECUInf");  // 设置清除ECU信息
    clear_data_cation->setIcon(QIcon(":/image/Image/clear3.png"));
    //添加动作到新建菜单，QAction就会自动变成子菜单
    save_menu->addAction(save_edr_data_action);
    save_menu->addAction(save_acu_data_action);
    save_menu->addSeparator();                      //添加菜单分隔符
    save_menu->addAction(save_curve_action);

    toolbar_ = new QToolBar(this);
    this->addToolBar(toolbar_);
    QAction *connect_action = new QAction("Connect(&C)");
    connect_action->setIcon(QIcon(":/image/Image/open.png"));
    toolbar_->addAction(connect_action);
    toolbar_->addAction(save_edr_data_action);
    toolbar_->addAction(save_acu_data_action);
    toolbar_->addAction(save_curve_action);
    toolbar_->addAction(clear_data_cation);

//    设置状态栏
    statusbar_ = new QStatusBar(this);
    this->setStatusBar(statusbar_);
    status_label_ = new QLabel;
    status_label_->setMinimumWidth(300);
    status_label_->setFrameShape(QFrame::NoFrame);
    this->statusbar_->addWidget(status_label_);
    status_label_->setText(tr("EDRReader"));
    connect(clear_data_cation, &QAction::triggered, center_window_, &CenterWindow::ClearECUInf);

}

void MainWindow::ConnectSignal()
{
  connect(serial_, &serial_port::MasterSerialThread::ResponseOrRequest, center_window_, &CenterWindow::ReceivedDataHandle);
  connect(serial_, &serial_port::MasterSerialThread::ResponseOrRequest, this, &MainWindow::GetSerialData);
  connect(this, &MainWindow::DataTostatusBar, this, &MainWindow::SetStatusbarText);

  connect(center_window_->ecu_information_btn_[0], &QPushButton::clicked,[this](){
     serial_->TransAction(100, serial_port::MasterSerialThread::ECUSerialNumberDataIdentifier);
    });
  connect(center_window_->ecu_information_btn_[1], &QPushButton::clicked,[this](){
     serial_->TransAction(100, serial_port::MasterSerialThread::ECUHardWareVersionNumberDataIdentifier);
    });
  connect(center_window_->ecu_information_btn_[2], &QPushButton::clicked,[this](){
     serial_->TransAction(100, serial_port::MasterSerialThread::ECUSoftWareVersionNumberDataIdentifier);
    });
  connect(center_window_->ecu_information_btn_[3], &QPushButton::clicked,[this](){
     serial_->TransAction(100, serial_port::MasterSerialThread::ECUManufacturingDateOfProduction);
    });
  connect(center_window_->ecu_information_btn_[4], &QPushButton::clicked,[this](){
     serial_->TransAction(100, serial_port::MasterSerialThread::functionConfigrationDataIdentifier);
    });
  connect(center_window_->clear_dtc_btn, &QPushButton::clicked,[this](){
      serial_->TransAction(100, serial_port::MasterSerialThread::clearDiagnosticInformation);
    });
  connect(center_window_->read_dtc_btn, &QPushButton::clicked,[this](){
      serial_->TransAction(100, serial_port::MasterSerialThread::reportDTCByStatusMask);
    });
  connect(center_window_->event_data_btn_[0], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData13);
    });
  connect(center_window_->event_data_btn_[1], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData14);
    });
  connect(center_window_->event_data_btn_[2], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData15);
    });
  connect(center_window_->event_data_btn_[3], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData16);
    });
  connect(center_window_->event_data_btn_[4], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData17);
    });
  connect(center_window_->event_data_btn_[5], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData18);
    });
  connect(center_window_->event_data_btn_[6], &QPushButton::clicked,[this](){
      serial_->TransAction(300, serial_port::MasterSerialThread::eventData19);
    });

}


void MainWindow::GetSerialData(const QTime &time,const QString &dir,const QByteArray &data)
{
  QString data_str = dataToHex(data.mid(4, 3));
  data_str = dir + " " + data_str;
  emit DataTostatusBar(data_str);
}

void MainWindow::SetStatusbarText(QString &str)
{
  status_label_->setText(str);
}
