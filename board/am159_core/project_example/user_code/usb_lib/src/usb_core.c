/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_core.c
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : Standard protocol processing (USB v2.0)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "../../usb_lib/inc/usb_lib.h"
#include "hw/amhw_zmf159_usb.h"

//extern amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT;
//extern uint8_t rxUsbBufOdd[16] ;
//extern uint8_t txUsbBufOdd[16] ;
//extern uint8_t epInDataNum[16] ;
extern uint8_t setupPacket[8] ;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ValBit(VAR,Place)    (VAR & (1 << Place))
#define SetBit(VAR,Place)    (VAR |= (1 << Place))
#define ClrBit(VAR,Place)    (VAR &= ((1 << Place) ^ 255))

#define Send0LengthData()   UserToPMABufferCopy(setupPacket, ENDP0, 0);



#define USB_StatusIn()  zmf159_handle->epInDataNum[0] = 1; \
                        Send0LengthData()
                        
#define USB_StatusOut() PMAToUserBufferCopy(setupPacket, ENDP0, 0);

#define StatusInfo0 StatusInfo.bw.bb1 /* Reverse bb0 & bb1 */
#define StatusInfo1 StatusInfo.bw.bb0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t_uint8_t StatusInfo;
am_bool_t Data_Mul_MaxPacketSize = AM_FALSE;
/* Private function prototypes -----------------------------------------------*/
static void DataStageOut(void);
static void DataStageIn(void);
static void NoData_Setup0(void);
static void Data_Setup0(void);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Standard_GetConfiguration.
* Description    : Return the current configuration variable address.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 1 , if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
uint8_t *Standard_GetConfiguration(uint16_t Length)
{
  if (Length == 0)
  {
    zmf159_handle->Ctrl_Info.Usb_wLength =
      sizeof(zmf159_handle->Current_Configuration);
    return 0;
  }
  return (uint8_t *)&zmf159_handle->Current_Configuration;
}

/*******************************************************************************
* Function Name  : Standard_SetConfiguration.
* Description    : This routine is called to set the configuration value
*                  Then each class should configure device themself.
* Input          : None.
* Output         : None.
* Return         : Return USB_SUCCESS, if the request is performed.
*                  Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetConfiguration(void)
{

  if ((zmf159_handle->USBwValues.bw.bb0 <=
		  zmf159_handle->Total_Configuration) && (zmf159_handle->USBwValues.bw.bb1 == 0)
      && (zmf159_handle->USBwIndexs.w == 0)) /*call Back usb spec 2.0*/
  {
    zmf159_handle->Current_Configuration = zmf159_handle->USBwValues.bw.bb0;
    return USB_SUCCESS;
  }
  else
  {
    return USB_UNSUPPORT;
  }
}

/*******************************************************************************
* Function Name  : Standard_GetInterface.
* Description    : Return the Alternate Setting of the current interface.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
uint8_t *Standard_GetInterface(uint16_t Length)
{
  if (Length == 0)
  {
    zmf159_handle->Ctrl_Info.Usb_wLength =
      sizeof(zmf159_handle->Current_AlternateSetting);
    return 0;
  }
  return (uint8_t *)&zmf159_handle->Current_AlternateSetting;
}

/*******************************************************************************
* Function Name  : Standard_SetInterface.
* Description    : This routine is called to set the interface.
*                  Then each class should configure the interface them self.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetInterface(void)
{
  RESULT Re;
  /*Test if the specified Interface and Alternate Setting are supported by
    the application Firmware*/
  Re = (*zmf159_handle->pProperty->Class_Get_Interface_Setting)(zmf159_handle->USBwIndexs.bw.bb0, zmf159_handle->USBwValues.bw.bb0);

  if (zmf159_handle->Current_Configuration != 0)
  {
    if ((Re != USB_SUCCESS) || (zmf159_handle->USBwIndexs.bw.bb1 != 0)
        || (zmf159_handle->USBwValues.bw.bb1 != 0))
    {
      return  USB_UNSUPPORT;
    }
    else if (Re == USB_SUCCESS)
    {
      zmf159_handle->Current_Interface = zmf159_handle->USBwIndexs.bw.bb0;
      zmf159_handle->Current_AlternateSetting = zmf159_handle->USBwValues.bw.bb0;
      return USB_SUCCESS;
    }

  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_GetStatus.
* Description    : Copy the device request data to "StatusInfo buffer".
* Input          : - Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is at end of data block,
*                  or is invalid when "Length" is 0.
*******************************************************************************/
uint8_t *Standard_GetStatus(uint16_t Length)
{
  if (Length == 0)
  {
    zmf159_handle->Ctrl_Info.Usb_wLength = 2;
    return 0;
  }

  StatusInfo.w = 0;
  /* Reset Status Information */

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /*Get Device Status */
    uint8_t Feature = zmf159_handle->Current_Feature;

    /* Remote Wakeup enabled */
    if (ValBit(Feature, 5))
    {
      SetBit(StatusInfo0, 1);
    }

    /* Bus-powered */
    if (ValBit(Feature, 6))
    {
      ClrBit(StatusInfo0, 0);
    }
    else /* Self-powered */
    {
      SetBit(StatusInfo0, 0);
    }
  }
  /*Interface Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    return (uint8_t *)&StatusInfo;
  }
  /*Get EndPoint Status*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    uint8_t Related_Endpoint;
    uint8_t wIndex0 = zmf159_handle->USBwIndexs.bw.bb0;

    Related_Endpoint = (wIndex0 & 0x0f);
    if (ValBit(wIndex0, 7))
    {
      /* IN endpoint */

//      if(_GetUSB_EPn_HALT(Related_Endpoint))
      if (amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint))
      {
        SetBit(StatusInfo0, 0); /* IN Endpoint stalled */
      }
    }
    else
    {
      /* OUT endpoint */

      if (amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint))
      {
        SetBit(StatusInfo0, 0); /* OUT Endpoint stalled */
      }
    }

  }
  else
  {
    return NULL;
  }
  return (uint8_t *)&StatusInfo;
}

/*******************************************************************************
* Function Name  : Standard_ClearFeature.
* Description    : Clear or disable a specific feature.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_ClearFeature(void)
{
  uint32_t     Type_Rec = Type_Recipient;
  uint32_t     Status;

  if (Type_Rec == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {/*Device Clear Feature*/
    ClrBit(zmf159_handle->Current_Feature, 5);
    return USB_SUCCESS;
  }
  else if (Type_Rec == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {/*EndPoint Clear Feature*/
    uint32_t Related_Endpoint;
    uint32_t wIndex0;
    uint32_t rEP;

    if ((zmf159_handle->USBwValues.w != ENDPOINT_STALL)
        || (zmf159_handle->USBwIndexs.bw.bb1 != 0))
    {
      return USB_UNSUPPORT;
    }

    wIndex0 = zmf159_handle->USBwIndexs.bw.bb0;
    rEP = wIndex0 & ~0x80;
    Related_Endpoint = ENDP0 + rEP;

    if (ValBit(zmf159_handle->USBwIndexs.bw.bb0, 7))
    {
      /*Get Status of endpoint & stall the request if the related_ENdpoint
      is Disabled*/
      //Status = _GetUSB_EPn_HALT(Related_Endpoint);
        Status = amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint);
    }
    else
    {
      //Status = _GetUSB_EPn_HALT(Related_Endpoint);
        Status = amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint);
    }

    if ((rEP >= zmf159_handle->Total_Endpoint) || (Status == 0)
        || (zmf159_handle->Current_Configuration == 0))
    {
      return USB_UNSUPPORT;
    }


    if (wIndex0 & 0x80)
    {
      /* IN endpoint */
      //if( _GetUSB_EPn_HALT(Related_Endpoint))
      if (amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint))
      {
        //_ClrUSB_EPn_HALT(Related_Endpoint);
          amhw_zmf159_ep_stat_set(ZMF159_USB, Related_Endpoint, 0);
      }
    }
    else
    {
      /* OUT endpoint */
      //if( _GetUSB_EPn_HALT(Related_Endpoint))
      if (amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint))
      {
        //_ClrUSB_EPn_HALT(Related_Endpoint);
          amhw_zmf159_ep_stat_set(ZMF159_USB, Related_Endpoint, 0);
      }
    }
    return USB_SUCCESS;
  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_SetEndPointFeature
* Description    : Set or enable a specific feature of EndPoint
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetEndPointFeature(void)
{
  uint32_t    wIndex0;
  uint32_t    Related_Endpoint;
  uint32_t    rEP;
  uint32_t   Status;

  wIndex0 = zmf159_handle->USBwIndexs.bw.bb0;
  rEP = wIndex0 & ~0x80;
  Related_Endpoint = ENDP0 + rEP;

  //Status = _GetUSB_EPn_HALT(Related_Endpoint);
  Status = amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint);
  if (Related_Endpoint >= zmf159_handle->Total_Endpoint
      || zmf159_handle->USBwValues.w != 0 || Status == 0
      || zmf159_handle->Current_Configuration == 0)
  {
    return USB_UNSUPPORT;
  }
  else
  {
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_SetDeviceFeature.
* Description    : Set or enable a specific feature of Device.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
RESULT Standard_SetDeviceFeature(void)
{
  SetBit(zmf159_handle->Current_Feature, 5);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_GetDescriptorData.
* Description    : Standard_GetDescriptorData is used for descriptors transfer.
*                : This routine is used for the descriptors resident in Flash
*                  or RAM
*                  pDesc can be in either Flash or RAM
*                  The purpose of this routine is to have a versatile way to
*                  response descriptors request. It allows user to generate
*                  certain descriptors with software or read descriptors from
*                  external storage part by part.
* Input          : - Length - Length of the data in this transfer.
*                  - pDesc - A pointer points to descriptor struct.
*                  The structure gives the initial address of the descriptor and
*                  its original size.
* Output         : None.
* Return         : Address of a part of the descriptor pointed by the Usb_
*                  wOffset The buffer pointed by this address contains at least
*                  Length bytes.
*******************************************************************************/
uint8_t *Standard_GetDescriptorData(uint16_t Length, ONE_DESCRIPTOR *pDesc)
{
  uint32_t  wOffset;

  wOffset = zmf159_handle->Ctrl_Info.Usb_wOffset;
  if (Length == 0)
  {
    zmf159_handle->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size - wOffset;
    return 0;
  }

  return pDesc->Descriptor + wOffset;
}

/*******************************************************************************
* Function Name  : DataStageOut.
* Description    : Data stage of a Control Write Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

void DataStageOut(void)
{
  am_endpoint_info *pEPinfo = &zmf159_handle->Ctrl_Info;
  uint32_t save_rLength;

  save_rLength = pEPinfo->Usb_wLength;

  if (pEPinfo->CopyData && save_rLength)
  {
    uint8_t *Buffer;
    uint32_t Length;

    Length = pEPinfo->PacketSize;
    if (Length > save_rLength)
    {
      Length = save_rLength;
    }

    Buffer = (*pEPinfo->CopyData)(Length);
    pEPinfo->Usb_wLength -= Length;
    pEPinfo->Usb_wOffset += Length;

    PMAToUserBufferCopy(Buffer, ENDP0, Length);//EP0接收OUT_PACK数据
  }

  if (pEPinfo->Usb_wLength != 0)
  {

  }
  /* Set the next State*/
  if (pEPinfo->Usb_wLength >= pEPinfo->PacketSize)
  {
    zmf159_handle->ControlState = OUT_DATA;
  }
  else
  {
    if (pEPinfo->Usb_wLength > 0)
    {
      zmf159_handle->ControlState = LAST_OUT_DATA;
    }
    else if (pEPinfo->Usb_wLength == 0)
    {
      zmf159_handle->ControlState = WAIT_STATUS_IN;
      USB_StatusIn();
    }
  }
}

/*******************************************************************************
* Function Name  : DataStageIn.
* Description    : Data stage of a Control Read Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DataStageIn(void)
{
  am_endpoint_info *pEPinfo = &zmf159_handle->Ctrl_Info;
  uint32_t save_wLength = pEPinfo->Usb_wLength;
  uint32_t ControlState = zmf159_handle->ControlState;

  uint8_t *DataBuffer;
  uint32_t Length;

  if ((save_wLength == 0) && (ControlState == LAST_IN_DATA))
  {
    if(Data_Mul_MaxPacketSize == AM_TRUE)
    {
      /* No more data to send and empty packet */
      Send0LengthData();
      ControlState = LAST_IN_DATA;
      Data_Mul_MaxPacketSize = AM_FALSE;
    }
    else 
    {
      /* No more data to send so STALL the TX Status*/
      ControlState = WAIT_STATUS_OUT;

    }
    goto Expect_Status_Out;
  }

  Length = pEPinfo->PacketSize;
  ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA;

  if (Length > save_wLength)
  {
    Length = save_wLength;
  }

  DataBuffer = (*pEPinfo->CopyData)(Length);
  
  UserToPMABufferCopy(DataBuffer, ENDP0, Length); 
 
  pEPinfo->Usb_wLength -= Length;
  pEPinfo->Usb_wOffset += Length;
  
Expect_Status_Out:
  zmf159_handle->ControlState = ControlState;
}

/*******************************************************************************
* Function Name  : NoData_Setup0.
* Description    : Proceed the processing of setup request without data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void NoData_Setup0(void)
{
  RESULT Result = USB_UNSUPPORT;
  uint32_t RequestNo = zmf159_handle->USBbRequest;
  uint32_t ControlState;

  if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
  {
    /* Device Request*/
    /* SET_CONFIGURATION*/
    if (RequestNo == SET_CONFIGURATION)
    {
      Result = Standard_SetConfiguration();
    }

    /*SET ADDRESS*/
    else if (RequestNo == SET_ADDRESS)
    {
      if ((zmf159_handle->USBwValues.bw.bb0 > 127) || (zmf159_handle->USBwValues.bw.bb1 != 0)
          || (zmf159_handle->USBwIndexs.w != 0)
          || (zmf159_handle->Current_Configuration != 0))
        /* Device Address should be 127 or less*/
      {
        ControlState = STALLED;

        goto exit_NoData_Setup0;
      }
      else
      {
        
        Result = USB_SUCCESS;
      }
    }
    /*SET FEATURE for Device*/
    else if (RequestNo == SET_FEATURE)
    {
      if ((zmf159_handle->USBwValues.bw.bb0 == DEVICE_REMOTE_WAKEUP)
          && (zmf159_handle->USBwIndexs.w == 0)
          && (ValBit(zmf159_handle->Current_Feature, 5)))
      {
        Result = Standard_SetDeviceFeature();
      }
      else
      {
        Result = USB_UNSUPPORT;
      }
    }
    /*Clear FEATURE for Device */
    else if (RequestNo == CLEAR_FEATURE)
    {
      if (zmf159_handle->USBwValues.bw.bb0 == DEVICE_REMOTE_WAKEUP
          && zmf159_handle->USBwIndexs.w == 0
          && ValBit(zmf159_handle->Current_Feature, 5))
      {
        Result = Standard_ClearFeature();
      }
      else
      {
        Result = USB_UNSUPPORT;
      }
    }

  }

  /* Interface Request*/
  else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    /*SET INTERFACE*/
    if (RequestNo == SET_INTERFACE)
    {
      Result = Standard_SetInterface();
    }
  }

  /* EndPoint Request*/
  else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
  {
    /*CLEAR FEATURE for EndPoint*/
    if (RequestNo == CLEAR_FEATURE)
    {
      Result = Standard_ClearFeature();
    }
    /* SET FEATURE for EndPoint*/
    else if (RequestNo == SET_FEATURE)
    {
      Result = Standard_SetEndPointFeature();
    }
  }
  else
  {
    Result = USB_UNSUPPORT;

  }

  // 类请求
  if (Result != USB_SUCCESS)
  {
    Result = (*zmf159_handle->pProperty->Class_NoData_Setup)(RequestNo);
    if (Result == USB_NOT_READY)
    {
      ControlState = PAUSE;
      goto exit_NoData_Setup0;
    }
  }

  if (Result != USB_SUCCESS)
  {
    goto exit_NoData_Setup0;
  }

  ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */

  // 发送空包
  USB_StatusIn();

exit_NoData_Setup0:
  zmf159_handle->ControlState = ControlState;
  return;
}

/*******************************************************************************
* Function Name  : Data_Setup0.
* Description    : Proceed the processing of setup request with data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Data_Setup0(void)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  RESULT Result;
  uint32_t Request_No = zmf159_handle->USBbRequest;

  uint32_t Related_Endpoint, Reserved;
  uint32_t wOffset = 0, Status;

  CopyRoutine = NULL;

  if (Request_No == GET_DESCRIPTOR)
  {
    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
      uint8_t wValue1 = zmf159_handle->USBwValues.bw.bb1;
      if (wValue1 == DEVICE_DESCRIPTOR)
      {
        CopyRoutine = zmf159_handle->pProperty->GetDeviceDescriptor;
      }
      else if (wValue1 == CONFIG_DESCRIPTOR)
      {
        CopyRoutine = zmf159_handle->pProperty->GetConfigDescriptor;
      }
      else if (wValue1 == STRING_DESCRIPTOR)
      {
        CopyRoutine = zmf159_handle->pProperty->GetStringDescriptor;
      }  /* End of GET_DESCRIPTOR */
    }
  }

  /*GET STATUS*/
  else if ((Request_No == GET_STATUS) && (zmf159_handle->USBwValues.w == 0)
           && (zmf159_handle->USBwLengths.w == 0x0002)
           && (zmf159_handle->USBwIndexs.bw.bb1 == 0))
  {
    /* GET STATUS for Device*/
    if ((Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        && (zmf159_handle->USBwIndexs.w == 0))
    {
      CopyRoutine = Standard_GetStatus;
    }

    /* GET STATUS for Interface*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
      if (((*zmf159_handle->pProperty->Class_Get_Interface_Setting)(zmf159_handle->USBwIndexs.bw.bb0, 0) == USB_SUCCESS)
          && (zmf159_handle->Current_Configuration != 0))
      {
        CopyRoutine = Standard_GetStatus;
      }
    }

    /* GET STATUS for EndPoint*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
      Related_Endpoint = (zmf159_handle->USBwIndexs.bw.bb0 & 0x0f);
      Reserved = zmf159_handle->USBwIndexs.bw.bb0 & 0x70;

//      Status = (_GetUSB_HALT()>>Related_Endpoint)&0x01;
//      Status = _GetUSB_EPn_HALT(Related_Endpoint);
      Status = amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint);
      if ((Related_Endpoint < zmf159_handle->Total_Endpoint) && (Reserved == 0)
          && (Status != 0))
      {
        CopyRoutine = Standard_GetStatus;
      }
    }

  }

  /*GET CONFIGURATION*/
  else if (Request_No == GET_CONFIGURATION)
  {
    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
      CopyRoutine = Standard_GetConfiguration;
    }
  }
  /*GET INTERFACE*/
  else if (Request_No == GET_INTERFACE)
  {
    if ((Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        && (zmf159_handle->Current_Configuration != 0) && (zmf159_handle->USBwValues.w == 0)
        && (zmf159_handle->USBwIndexs.bw.bb1 == 0) && (zmf159_handle->USBwLengths.w == 0x0001)
        && ((*zmf159_handle->pProperty->Class_Get_Interface_Setting)(zmf159_handle->USBwIndexs.bw.bb0, 0) == USB_SUCCESS))
    {
      CopyRoutine = Standard_GetInterface;
    }

  }
  
  if (CopyRoutine)
  {
    zmf159_handle->Ctrl_Info.Usb_wOffset = wOffset;
    zmf159_handle->Ctrl_Info.CopyData = CopyRoutine;
    /* sb in the original the cast to word was directly */
    /* now the cast is made step by step */
    (*CopyRoutine)(0);
    Result = USB_SUCCESS;
  }
  else
  {
    Result = (*zmf159_handle->pProperty->Class_Data_Setup)(zmf159_handle->USBbRequest);
      
    if (Result == USB_NOT_READY)
    {
      zmf159_handle->ControlState = PAUSE;
      return;
    }
  }

  if (zmf159_handle->Ctrl_Info.Usb_wLength == 0xFFFF)
  {
    /* Data is not ready, wait it */
    zmf159_handle->ControlState = PAUSE;
    return;
  }
  if ((Result == USB_UNSUPPORT) || (zmf159_handle->Ctrl_Info.Usb_wLength == 0))
  {
    /* Unsupported request */
    zmf159_handle->ControlState = STALLED;
    
    return;
  }


  if (ValBit(zmf159_handle->USBbmRequestType, 7)) // in
  {
    /* Device ==> Host */
    __IO uint32_t wLength = zmf159_handle->USBwLengths.w;
     
    /* Restrict the data length to be the one host asks */
    if (zmf159_handle->Ctrl_Info.Usb_wLength > wLength)
    {
      zmf159_handle->Ctrl_Info.Usb_wLength = wLength;
    }
    
    else if (zmf159_handle->Ctrl_Info.Usb_wLength < zmf159_handle->USBwLengths.w)
    {
      if (zmf159_handle->Ctrl_Info.Usb_wLength < zmf159_handle->MaxPacketSize)
      {
        Data_Mul_MaxPacketSize = AM_FALSE;
      }
      else if ((zmf159_handle->Ctrl_Info.Usb_wLength % zmf159_handle->MaxPacketSize) == 0)
      {
        Data_Mul_MaxPacketSize = AM_TRUE;
      }
    }   

    zmf159_handle->Ctrl_Info.PacketSize = zmf159_handle->MaxPacketSize;
    DataStageIn();
  }
  else
  {
    zmf159_handle->Ctrl_Info.Usb_wLength = zmf159_handle->USBwLengths.w;//
    zmf159_handle->ControlState = OUT_DATA;

  }

  return;
}

/*******************************************************************************
* Function Name  : Setup0_Process
* Description    : Get the device request data and dispatch to individual process.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t Setup0_Process(void)
{
    uint8_t *pBuf ;
  if (zmf159_handle->ControlState != PAUSE)
  {  
	  am_kprintf("setup\r\n");
    pBuf = setupPacket;
    PMAToUserBufferCopy(pBuf, ENDP0,  8);
    zmf159_handle->USBbmRequestType = pBuf[0];
    zmf159_handle->USBbRequest   = pBuf[1];
    zmf159_handle->USBwValues.w  = pBuf[3]|(pBuf[2]<<8); // wValue
    zmf159_handle->USBwIndexs.w  = pBuf[5]|(pBuf[4]<<8); // wIndex
    zmf159_handle->USBwLengths.w = pBuf[6]|(pBuf[7]<<8);// wLength

    am_kprintf("set up data: %x %x %x %x %x\r\n", zmf159_handle->USBbmRequestType,
    											  zmf159_handle->USBbRequest,
												  zmf159_handle->USBwValues.w,
												  zmf159_handle->USBwIndexs.w,
												  zmf159_handle->USBwLengths.w);
  }

  am_kprintf("req: %d \r\n", zmf159_handle->USBbRequest);
  zmf159_handle->ControlState = SETTING_UP; 
  
  if (zmf159_handle->USBwLengths.w == 0)
  {
    /* Setup with no data stage */
    NoData_Setup0();
  }
  else
  {
    /* Setup with data stage */
    Data_Setup0();
  }
  return Post0_Process();
}

/*******************************************************************************
* Function Name  : In0_Process
* Description    : Process the IN token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t In0_Process(void)
{
  uint32_t ControlState = zmf159_handle->ControlState;
  
  if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
  {
    DataStageIn();
    /* ControlState may be changed outside the function */
    ControlState = zmf159_handle->ControlState;
  }

  else if (ControlState == WAIT_STATUS_IN)
  {
    if ((zmf159_handle->USBbRequest == SET_ADDRESS) &&
        (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)))
    {
//      pUser_Standard_Requests->User_SetDeviceAddress();
    	(*zmf159_handle->pProperty->User_SetDeviceAddress)();
    }
    
    (*zmf159_handle->pProperty->Process_Status_IN)();
  }

  else
  {
    ControlState = STALLED;

  }

  zmf159_handle->ControlState = ControlState;
  
  return Post0_Process();
}

/*******************************************************************************
* Function Name  : Out0_Process
* Description    : Process the OUT token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
uint8_t Out0_Process(void)
{
  uint32_t ControlState = zmf159_handle->ControlState;

  if ((ControlState == OUT_DATA) || (ControlState == LAST_OUT_DATA))
  {
    DataStageOut();
    ControlState = zmf159_handle->ControlState; /* may be changed outside the function */
  }

  else if (ControlState == WAIT_STATUS_OUT)
  {
    (*zmf159_handle->pProperty->Process_Status_OUT)();
  
    ControlState = STALLED;
  }

  else if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
  {
    /* host aborts the transfer before finish */
    ControlState = STALLED;

  }

  /* Unexpect state, STALL the endpoint */
  else
  {
    ControlState = STALLED;
  }

  zmf159_handle->ControlState = ControlState;

  return Post0_Process();
}

/*******************************************************************************
* Function Name  : Post0_Process
* Description    : Stall the Endpoint 0 in case of error.
* Input          : None.
* Output         : None.
* Return         : - 0 if the control State is in PAUSE
*                  - 1 if not.
*******************************************************************************/
uint8_t Post0_Process(void)
{

  if (zmf159_handle->ControlState == STALLED)
  {
    
  }
  return (zmf159_handle->ControlState == PAUSE);
}

/*******************************************************************************
* Function Name  : SetDeviceAddress.
* Description    : Set the device and all the used Endpoints addresses.
* Input          : - Val: device adress.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SetDeviceAddress(uint8_t Val)
{
    amhw_zmf159_addr_set(ZMF159_USB, Val);
}

/*******************************************************************************
* Function Name  : NOP_Process
* Description    : No operation function.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void NOP_Process(void)
{

}

