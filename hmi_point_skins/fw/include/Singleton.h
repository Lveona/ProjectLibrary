/*!
 * @file         Singleton.h
 * @date         2018/05/18
 * @author       Li.hongji
 * @version      0.1
 * @brief        Header file for Singleton
 */
/*********************************************************************************
 * Revision History                                                              *
 * No    Date        Revised by        Description                               *
 * --    ----        ----------        -----------                               *
 * 01    2018/05/18    Li.hongji             New                                 *
 *********************************************************************************/
#ifndef _CSINGLETON_H_
#define _CSINGLETON_H_

/**
 * This class (a) defines an Instance operation that lets clients access its
 * unique instance, and (b) may be responsible for creating its own unique
 * instance.
 */
template<class T>
class CSingleton
{
public:
	static T * instance()
	{
        if(m_instance == nullptr)
			m_instance = new T();

		return m_instance;
	}
protected:
	CSingleton()
	{

	}
	virtual ~CSingleton()
	{

	}

private:
	static T * m_instance;

};

template<class T>
T * CSingleton<T>::m_instance = nullptr;
#endif
