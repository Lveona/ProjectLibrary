/*!
 * @file         BaseControl.h
 * @date         2018/05/18
 * @author       Li.hongji
 * @version      0.1
 * @brief        Header file for Base Control
 */
/*********************************************************************************
 * Revision History                                                              *
 * No    Date        Revised by        Description                               *
 * --    ----        ----------        -----------                               *
 * 01    2018/05/18    Li.hongji             New                                 *
 *********************************************************************************/
#ifndef _CAPP_CONTROL_H_
#define _CAPP_CONTROL_H_

#include <QQmlContext>
#include <QQuickView>

class QTimer;
using namespace std;
class CBaseScreen : public QObject
{
	Q_OBJECT
public:
	void registerAppControl(void * context, QString objName)
	{
		QQmlContext * _context	=	(QQmlContext *)context;
		_context->setContextProperty(objName, this);
	}

	void createAppControl(void * context, QString objName)
	{
        startControl();
		registerAppControl(context, objName);
	}

protected:
    CBaseScreen(){}
    virtual ~CBaseScreen(){
//		qDebug()<<"~CBaseScreen is called ";
	}
    virtual void startControl() = 0;

private:
};

#endif



