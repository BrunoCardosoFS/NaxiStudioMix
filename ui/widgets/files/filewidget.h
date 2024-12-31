#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QtWidgets>

class FileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileWidget(QWidget *parent = nullptr);
    QString path;

private:
    QLabel *TimeLabel;
    QLabel *TitleLabel;

signals:
    void clicked(QString path);

public slots:
    void setInfo(QString title, QString path, QString duration);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // FILEWIDGET_H
