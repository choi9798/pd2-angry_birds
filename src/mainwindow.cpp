#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/image/bg.png").scaled(960, 480));
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene

    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    quit_button = new QPushButton(this);
    quit_button->setObjectName("quit");
    quit_button->setGeometry(20,20,70,70);
    quit_button->setStyleSheet("#quit{border-image: url(:/image/quit.png)}");
    quit_button->show();
    restart_button = new QPushButton(this);
    restart_button->setObjectName("restart");
    restart_button->setGeometry(100,20,70,70);
    restart_button->setStyleSheet("#restart{border-image: url(:/image/restart-icon-61175.png)}");
    restart_button->show();
    score_label = new QLabel(this);
    score_label->setGeometry(800,20,110,40);
    score_label->setFont(QFont("Time",25,QFont::Bold));
    score_label->show();
    connect(restart_button,SIGNAL(clicked()),this,SLOT(re()));
    connect(quit_button,SIGNAL(clicked()), this, SLOT(qquit()));

    // Create world

    world = new b2World(b2Vec2(0.0f, -9.8f));

    // Setting Size

    GameItem::setGlobalSize(QSizeF(32,18),size());

    // Create ground (You can edit here)

    itemList.push_back(new Land(16,0.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    block1=new Ob(17.0f,7.5f,1.5,5,&timer,QPixmap(":/image/11.png").scaled(width()/32*1.5,height()/18*5),world,scene);
    block2=new Ob(25.0f,7.5f,1.5,5,&timer,QPixmap(":/image/11.png").scaled(width()/32*1.5,height()/18*5),world,scene);
    block3=new Ob(21.0f,10.8f,9.5,1,&timer,QPixmap(":/image/22.png").scaled(width()/32*9.5,height()/18*1),world,scene);
    up_bound = new Land(16,20.8,32,3,QPixmap(":/image/ground.png").scaled(width(),height()/6.0),world,scene);
    left_bound = new Land(-0.5,10,1,18,QPixmap(":/image/11.png").scaled(width()/32*1,height()/18*18),world,scene);
    right_bound = new Land(33,10,1,18,QPixmap(":/image/11.png").scaled(width()/32*1,height()/18*18),world,scene);

    // Create bird (You can edit here)

    birdie = new Bird(6.0f,2.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32*2,height()/18*2),world,scene);
    pig = new Pig(19.1f,2.0f,1.0f,&timer,QPixmap(":/image/pig.png").scaled(width()/32*2,height()/18*2),world,scene);
    yellowb = new Yellowbird(4.0f,2.0f,1.0f,&timer,QPixmap(":/image/yellow.png").scaled(width()/32*2,height()/18*2),world,scene);
    blackb = new Blackbird(2.0f,2.0f,1.0f,&timer,QPixmap(":/image/black.png").scaled(width()/32*2,height()/18*2),world,scene);
    blueb = new Bluebird(0.0f,2.0f,1.0f,&timer,QPixmap(":/image/blue.png").scaled(width()/32*2,height()/18*2),world,scene);

    // Setting the Velocity

    //birdie->setLinearVelocity(b2Vec2(11,5));
    itemList.push_back(birdie);
    itemList.push_back(pig);
    itemList.push_back(block1);
    itemList.push_back(block2);
    itemList.push_back(yellowb);
    itemList.push_back(blackb);
    itemList.push_back(blueb);
    // Timer

    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        /* TODO : add your code here */
        //std::cout << "Press !" << std::endl ;
        QMouseEvent *mou = static_cast<QMouseEvent *>(event);
        ix = mou->globalX();
        iy = mou->globalY();
        std::cout << ix << " ";
        std::cout << iy << " ";
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;
        presstime++;
        std::cout << presstime << std::endl;
        if(presstime == 6)
        {
            yellowb->ability();
        }
        if(presstime == 10)
        {
            blackb->ability();
        }
        if(presstime == 14)
        {
            blueb->ability();
        }
        if(presstime == 2)
        {
            QMouseEvent *mou = static_cast<QMouseEvent *>(event);
            fx = mou->globalX();
            fy = mou->globalY();
            birdie->setLinearVelocity(b2Vec2((ix-fx)/10, (fy-iy)/10));
            itemList.push_back(birdie);
        }
        if(presstime == 4)
        {
            QMouseEvent *mou = static_cast<QMouseEvent *>(event);
            fx = mou->globalX();
            fy = mou->globalY();
            yellowb->setLinearVelocity(b2Vec2((ix-fx)/10, (fy-iy)/10));
            itemList.push_back(yellowb);
        }
        if(presstime == 8)
        {
            QMouseEvent *mou = static_cast<QMouseEvent *>(event);
            fx = mou->globalX();
            fy = mou->globalY();
            blackb->setLinearVelocity(b2Vec2((ix-fx)/10, (fy-iy)/10));
            itemList.push_back(blackb);
        }
        if(presstime == 12)
        {
            QMouseEvent *mou = static_cast<QMouseEvent *>(event);
            fx = mou->globalX();
            fy = mou->globalY();
            blueb->setLinearVelocity(b2Vec2((ix-fx)/10, (fy-iy)/10));
            itemList.push_back(blueb);
        }

    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
    vel = pig->g_body->GetLinearVelocity();
    if(vel.x!=0 || vel.y != 0)
    {
        score++;
        std::cout << "score : " << score << std::endl;
        score_label->setNum(score);
    }

}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
    exit(0);
}

void MainWindow::re()
{
    std::cout << "restart" << std::endl ;
    delete birdie;
    delete block1;
    delete block2;
    delete block3;
    delete yellowb;
    delete blackb;
    delete pig;
    delete blueb;

    block1=new Ob(17.0f,7.5f,1.5,5,&timer,QPixmap(":/image/11.png").scaled(width()/32*1.5,height()/18*5),world,scene);
    block2=new Ob(25.0f,7.5f,1.5,5,&timer,QPixmap(":/image/11.png").scaled(width()/32*1.5,height()/18*5),world,scene);
    block3=new Ob(21.0f,10.8f,9.5,1,&timer,QPixmap(":/image/22.png").scaled(width()/32*9.5,height()/18*1),world,scene);

   // bot_bound = new Land(16,1,32,3,QPixmap(":/image/ground.png").scaled(width(),height()/6.0),world,scene);
    up_bound = new Land(16,20.8,32,3,QPixmap(":/image/ground.png").scaled(width(),height()/6.0),world,scene);
    left_bound = new Land(-0.5,10,1,18,QPixmap(":/image/11.png").scaled(width()/32*1,height()/18*18),world,scene);
    right_bound = new Land(33,10,1,18,QPixmap(":/image/11.png").scaled(width()/32*1,height()/18*18),world,scene);

    birdie = new Bird(6.0f,2.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32*2,height()/18*2),world,scene);
    pig = new Pig(19.1f,2.0f,1.0f,&timer,QPixmap(":/image/pig.png").scaled(width()/32*2,height()/18*2),world,scene);
    yellowb = new Yellowbird(4.0f,2.0f,1.0f,&timer,QPixmap(":/image/yellow.png").scaled(width()/32*2,height()/18*2),world,scene);
    blackb = new Blackbird(2.0f,2.0f,1.0f,&timer,QPixmap(":/image/black.png").scaled(width()/32*2,height()/18*2),world,scene);
    blueb = new Bluebird(0.0f,2.0f,1.0f,&timer,QPixmap(":/image/blue.png").scaled(width()/32*2,height()/18*2),world,scene);
    presstime = 0;
    score = 0;
    score_label->setNum(score);
}

void MainWindow::qquit()
{
   quitGame();
}
