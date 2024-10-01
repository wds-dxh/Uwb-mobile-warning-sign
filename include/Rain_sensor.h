#ifndef __RAIN_SENSOR_H__
#define __RAIN_SENSOR_H__

/**
 * @brief 雨滴检测驱动
 * @param none
 * @retval none
*/
class Rain_sensor{
    public:
    void Rain_sensor_init();
    int Rain_sensor_get();
    bool Rain_sensor_is_rain();
    void show_rain_sensor(); //显示雨滴检测模块的值,开关于模拟量同时显示
    
};







#endif