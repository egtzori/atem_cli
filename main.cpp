#include <stdio.h>
#include <QCoreApplication>
#include <App.h>

App::App(int argc, char **argv): QCoreApplication(argc, argv) {
    this->argv = argv;
    this->argc = argc;

    m_atemConnection = new QAtemConnection(this);
    connect(m_atemConnection, SIGNAL(connected()), this, SLOT(onAtemConnected()));
    m_atemConnection->connectToSwitcher(QHostAddress(argv[1]));

    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);
    connect(mTimer, SIGNAL(timeout()), SLOT(on_connection_timeout()));
    mTimer->start(CONN_TIMEOUT_MS);
}

void App::on_connection_timeout() {
    printf("connection timeout!\n");
    QCoreApplication::quit();
}

void App::onAtemConnected() {
    mTimer->stop();

    QAtemMixEffect *me = m_atemConnection->mixEffect(0);
    if (!me) {
        printf("cannot get MixEffect! this is fatal");
        QCoreApplication::quit();
        return;
    }

    if (0 == strcmp("program", this->argv[2])) {
        int num = atoi(this->argv[3]);
        printf("change program %d\n", num);
        me->changeProgramInput(num);
        QCoreApplication::quit();
    } else if (0 == strcmp("preview", this->argv[2])) {
        int num = atoi(this->argv[3]);
        printf("change preview %d\n", num);
        me->changePreviewInput(num);
        QCoreApplication::quit();
    } else if (0 == strcmp("cut", this->argv[2])) {
        printf("cut\n");
        me->cut();
        QCoreApplication::quit();
    } else if (0 == strcmp("auto", this->argv[2])) {
        printf("auto\n");
        me->autoTransition();
        QCoreApplication::quit();
    } else if (0 == strcmp("auto_set", this->argv[2])) {
        int num1 = atoi(this->argv[3]);
        printf("set style %d\n", num1);
        m_atemConnection->mixEffect(0)->setTransitionType(num1);
        QCoreApplication::quit();
    } else if (0 == strcmp("auto_read", this->argv[2])) {
        printf("style %d frames %d\n", me->nextTransitionStyle(), me->transitionFrameCount());
        QCoreApplication::quit();
    } else if (0 == strcmp("read", this->argv[2])) {
        printf("program %d preview %d\n", me->programInput(), me->previewInput());
        QCoreApplication::quit();
    } else {

        printf("nothing to do..\n");
        QCoreApplication::quit();
        return;
    }
}

int print_usage_and_die(int argc, char **argv) {
    argc=argc;
    printf("usage: %s <ip_address> read\n", argv[0]);
    printf("usage: %s <ip_address> program <1-8>\n", argv[0]);
    printf("usage: %s <ip_address> preview <1-8>\n", argv[0]);
    printf("usage: %s <ip_address> cut\n", argv[0]);
    printf("usage: %s <ip_address> auto\n", argv[0]);
    printf("usage: %s <ip_address> auto_read\n", argv[0]);
    printf("usage: %s <ip_address> auto_set <0-4>\n", argv[0]);
    printf("auto_set effects: 0=Mix, 1=Dip, 2=Wipe, 3=Sting, 4=DVE\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (2 >= argc) {
        return print_usage_and_die(argc, argv);
    }

    if (0 == strcmp("program", argv[2])) {
        if (4 != argc) return print_usage_and_die(argc, argv);
    } else if (0 == strcmp("preview", argv[2])) {
        if (4 != argc) return print_usage_and_die(argc, argv);
    } else if (0 == strcmp("cut", argv[2])) {
        if (3 != argc) return print_usage_and_die(argc, argv);
    } else if (0 == strcmp("auto_set", argv[2])) {
        if (4 != argc) return print_usage_and_die(argc, argv);
    } else if (0 == strcmp("auto", argv[2])) {
        if (3 != argc) return print_usage_and_die(argc, argv);
    } else if (0 == strcmp("read", argv[2])) {
        if (3 != argc) return print_usage_and_die(argc, argv);
    } else if (0 == strcmp("auto_read", argv[2])) {
        if (3 != argc) return print_usage_and_die(argc, argv);
    } else {
        return print_usage_and_die(argc, argv);
    }

    App a(argc, argv);
    return a.exec();
}
