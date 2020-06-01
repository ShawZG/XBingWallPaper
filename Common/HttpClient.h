#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H


class QNetworkAccessManager;
class QNetworkReply;

#include <QObject>

const int HTTP_RESPONSE_OK = 200;

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);
    ~HttpClient();

    static HttpClient *instance();
    static bool validateReplay(QNetworkReply *reply, QJsonDocument &doc);

    QNetworkReply *getBingWallpaperUrlRequest(int distanceDay, int width, int height);
    QNetworkReply *downloadWallpaperRequest(QString url);

private:
    Q_DISABLE_COPY(HttpClient)
    QNetworkAccessManager *manager = nullptr;
};

#endif // HTTPCLIENT_H
