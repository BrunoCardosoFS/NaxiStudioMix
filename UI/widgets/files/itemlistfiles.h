#ifndef ITEMLISTFILES_H
#define ITEMLISTFILES_H

#include <QtWidgets>

class itemlistfiles : public QGroupBox
{

    Q_OBJECT

public:
    itemlistfiles(QWidget *parent = nullptr);

    QString pathFile;
    QString titleFile;

    void setPathFile(QString path);
    void setTitleFile(QString title);

private:
    QLabel *titleFileLabel;

signals:
    void loadPlayer(const QString &path);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ITEMLISTFILES_H
