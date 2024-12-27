#include <QApplication>
#include <QByteArray>
#include <QFont>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPalette>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStyle>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  QStyle *style = QStyleFactory::create("Fusion");
  QPalette palette = style->standardPalette();
  QApplication::setStyle(style);
  QApplication::setPalette(palette);

  QWidget window;
  window.setWindowTitle("Practical");
  QVBoxLayout *layout = new QVBoxLayout(&window);

  QFont *monoFont = new QFont;
  monoFont->setFamily("monospace [Consolas]");
  monoFont->setFixedPitch(true);
  monoFont->setStyleHint(QFont::TypeWriter);

  QLabel *label = new QLabel("Server");
  QLineEdit *lineEdit = new QLineEdit("https://spacex-production.up.railway.app/");
  lineEdit->setFont(*monoFont);
  QPlainTextEdit *queryTextEdit = new QPlainTextEdit();
  queryTextEdit->setPlainText("query {\n    company {\n        ceo\n    }\n}");
  queryTextEdit->setFont(*monoFont);
  QPlainTextEdit *responseTextEdit = new QPlainTextEdit();
  responseTextEdit->setFont(*monoFont);
  responseTextEdit->setReadOnly(true);
  QPushButton *button = new QPushButton("Execute Query");

  // Setup networking
  QNetworkAccessManager *manager = new QNetworkAccessManager();
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [=](QNetworkReply *reply) {
                     if (reply->error()) {
                       responseTextEdit->setPlainText(reply->errorString());
                       return;
                     }

                     QString answer = reply->readAll();
                     responseTextEdit->setPlainText(answer);
                   });

  QObject::connect(button, &QPushButton::clicked, [=]() {
    QNetworkRequest *request = new QNetworkRequest;
    request->setUrl(QUrl(lineEdit->displayText()));
    QString byteArray = queryTextEdit->toPlainText();
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("query", byteArray);

    QJsonDocument doc(json);
    QByteArray postData = doc.toJson();

    manager->post(*request, postData);
  });

  layout->addWidget(label);
  layout->addWidget(lineEdit);
  layout->addWidget(queryTextEdit);
  layout->addWidget(button);
  layout->addWidget(responseTextEdit);
  window.show();
  return QApplication::exec();
}
