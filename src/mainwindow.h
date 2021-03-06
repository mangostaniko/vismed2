
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "glwidget.h"
#include "volume.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>
#include <QComboBox>
#include <QMouseEvent>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void openFile(QString filepath);

signals:

	void dataLoaded(Volume *volumeData);

protected slots :

	void openFileAction();
	void closeAction();
	void setCompositing(int mode);
    void setShading();
	void setPerspective(bool enabled);

private:

	// USER INTERFACE ELEMENTS

	Ui_MainWindow *ui;
	GLWidget *glWidget;


	// DATA

	enum DataType
	{
		VOLUME = 0,
	};

	struct FileType
	{
		QString filename;
		DataType type;
	} fileType;

	Volume *volume; // for Volume-Rendering

};

#endif
