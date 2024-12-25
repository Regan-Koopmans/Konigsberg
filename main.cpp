#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStyleFactory>
#include <QStyle>
#include <QPalette>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    // Light theme
    QStyle* style = QStyleFactory::create("Fusion");
    QPalette palette = style->standardPalette();
    QApplication::setStyle(style);
    QApplication::setPalette(palette);

    QWidget window;
    window.setWindowTitle("QtTextExample");

    QVBoxLayout* layout = new QVBoxLayout(&window);

    QLabel* label = new QLabel("Server");
    

    QLineEdit* lineEdit = new QLineEdit("QLineEdit: Sample input text");
    

    QTextEdit* textEdit = new QTextEdit();
    textEdit->setText("query {}");
    QPlainTextEdit* plainTextEdit = new QPlainTextEdit("QPlainTextEdit: Enter multi-line plain text here.\nIt's optimized for text editing without rich formatting.");
    

    QPushButton* button = new QPushButton("Execute Query");
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    layout->addWidget(button);
    layout->addWidget(textEdit);
layout->addWidget(plainTextEdit);
    window.show();

    return QApplication::exec();
}
