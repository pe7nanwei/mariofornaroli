#include "zsn60x.h"
#include "ametal.h"
/* ZSN60x  B�࿨������Գ��� */
void demo_zsn60x_piccb_active_test_entry (zsn60x_handle_t handle)
{
    unsigned char  info[12] = {0};
    unsigned char  ret = 0;
    /* ��ʹ��B����صĺ���ǰ��������Э��ΪB�࿨ */
    ret = zsn60x_set_ios_type (handle, ZSN60X_ICC_ISO_TYPE_B);
    if(ret  !=  0 ){
        am_kprintf("ios set fail beacuse %0x2", ret);
        return;
    }
    //B������ӿں���  ����ģʽΪ 0x00  IDLE
    ret = zsn60x_piccb_active(handle, 0x00, info);
    if(ret == 0){
        unsigned char i = 0;
        am_kprintf("CARD INFO  is :");
        for(i = 0; i < 12 ; i ++ ){
            am_kprintf("%02x ",  info[i]);
       }
        am_kprintf("\r\n");
    }else{
        am_kprintf("active fail beacuse error 0x%02x", ret);
    }
}
