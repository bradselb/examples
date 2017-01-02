#if !defined SERVER_H
#define SERVER_H

#include <QObject>
#include <QDialog>

class QTcpServer;
class QLabel;
class QPushButton;

class Server : public QDialog
{
  Q_OBJECT

  public:
    Server(QWidget* parent=0, quint16 port=7000);
    ~Server();

  private slots:
    void handleConnection();

  private:
    QTcpServer* m_tcpServer;
    QLabel* m_label;
    QPushButton* m_button;

};


#endif //defined SERVER_H

