#ifndef AOPENGLWINDOW_H
#define AOPENGLWINDOW_H

#include <QOpenGLFunctions_4_0_Core>
#include <QWindow>

#include <QTime>

class QOpenGLContext;
class AAbstractScene;

class AOpenGLWindow : public QWindow, protected QOpenGLFunctions_4_0_Core
{
    Q_OBJECT

public:
    explicit AOpenGLWindow(QWindow *parent = 0);
    ~AOpenGLWindow();
	
public slots:

	// Called every frame by timer
	void tick();
	// Called when window is resized
	void resizeEngine();

protected:	
    void keyPressEvent( QKeyEvent* e );
    void keyReleaseEvent( QKeyEvent* e );
    void mousePressEvent( QMouseEvent* e );
    void mouseReleaseEvent( QMouseEvent* e );
    void mouseMoveEvent( QMouseEvent* e );
	
private:
	void initializeEngine();
    void renderEngine();	
	void updateEngine();

    QOpenGLContext *m_context;
	bool m_isEngineInitialized;

	bool m_leftButtonPressed;
	bool m_isFullscreen;
    QPoint m_prevPos;
    QPoint m_pos;
	QTime m_time;	
    int m_frame;
	float m_refreshRate;

	AAbstractScene* m_engineScene;
	AAbstractScene* m_loadingScene;
	AAbstractScene* m_currentScene;
};

#endif