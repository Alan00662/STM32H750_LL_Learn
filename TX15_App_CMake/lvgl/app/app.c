#include "app.h"
#include "../lvgl/demos/lv_demos.h"

/* lvgl驱动初始化 */
void app_lvgl_init(void)
{
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
}



void app_entry(void){
	
//	lv_example_label();
//	lv_example_switch1();
	lv_demo_widgets();


}
