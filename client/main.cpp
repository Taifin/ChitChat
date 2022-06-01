#include <QApplication>
#include <thread>
#include "view.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    view current_view;

    std::thread t([&]() {
        while (true) {
            current_view.current_session.processor.wait_next_query();
        }
    });
    t.detach();

    current_view.start();

    return a.exec();
}
