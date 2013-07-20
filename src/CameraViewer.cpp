// -*- C++ -*-
/*!
 * @file  CameraViewer.cpp
 * @brief Camera Viewer Component
 * @date $Date$
 *
 * $Id$
 */

#include "CameraViewer.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// Module specification
// <rtc-template block="module_spec">
static const char* cameraviewer_spec[] =
  {
    "implementation_id", "CameraViewer",
    "type_name",         "CameraViewer",
    "description",       "Camera Viewer Component",
    "version",           "1.0.0",
    "vendor",            "Sugar Sweet Robotics",
    "category",          "Experimental",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CameraViewer::CameraViewer(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in)

    // </rtc-template>
{
  m_pImg = NULL;
}

/*!
 * @brief destructor
 */
CameraViewer::~CameraViewer()
{
}



RTC::ReturnCode_t CameraViewer::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  cvNamedWindow("CapturedImage", CV_WINDOW_AUTOSIZE);  
  cvStartWindowThread();
  //  m_pImg = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);

  //  for (int i = 0;i < 240;i++) {
  //n    for(int j = 0;j < 320;j++) {
  //n      m_pImg->imageData[(i*240+j)*3+1] = 255;
  //n    }
  //  }
  
  ///  cvShowImage("CapturedImage", m_pImg);
  //  cv::imwrite("hoge.jpg", cv::Mat(m_pImg));

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraViewer::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraViewer::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraViewer::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CameraViewer::onActivated(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraViewer::onDeactivated(RTC::UniqueId ec_id)
{
  cvReleaseImage(&m_pImg);
  m_pImg = NULL;
  cvDestroyWindow("CapturedImage");
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraViewer::onExecute(RTC::UniqueId ec_id) {
  //std::cout << "onExecute" << std::endl;
  if (m_inIn.isNew()) {

    m_inIn.read();
    if ((m_pImg == NULL) || 
	(m_in.width != m_pImg->width || m_in.height != m_pImg->height)) {

      if(m_pImg != NULL) {
	cvReleaseImage(&m_pImg);
      }
      m_pImg = cvCreateImage(cvSize(m_in.width, m_in.height), IPL_DEPTH_8U, 3);
      std::cout << "Update" << std::endl;
    }
    std::cout << "Received(" << m_in.width << "x" << m_in.height << ")" << std::endl;
    //    cvStartWindowThread();
    // m_pImg->width = m_in.width;
    //m_pImg->height = m_in.height;
    memcpy(m_pImg->imageData, (void*)&(m_in.pixels[0]), m_in.pixels.length());
    
    cv::imwrite("save.jpg", cv::Mat(m_pImg));
    //for (int i = 0;i < 240;i++) {
    //      for(int j = 0;j < 320;j++) {
    //	m_pImg->imageData[(i*240+i)*3] = 255;
    //      }
    //    }
    //    cvShowImage("CapturedImage", m_pImg);
    //    cvWaitKey(1);
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraViewer::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraViewer::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraViewer::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraViewer::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraViewer::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CameraViewerInit(RTC::Manager* manager)
  {
    coil::Properties profile(cameraviewer_spec);
    manager->registerFactory(profile,
                             RTC::Create<CameraViewer>,
                             RTC::Delete<CameraViewer>);
  }
  
};


