#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Mpu6050_eleccat.h"
// 包含 Arduino Wire 库
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 mpu;  // 创建一个 MPU6050 对象

#define OUTPUT_READABLE_YAWPITCHROLL

// #define INTERRUPT_PIN 2  // 使用引脚 2 作为中断引脚
// #define LED_PIN 13       // LED 引脚，Arduino Uno 上是 13
// bool blinkState = false; // LED 闪烁状态

// MPU 控制/状态变量
bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

// 方向/运动变量
Quaternion q;
VectorInt16 aa;
VectorInt16 aaReal;
VectorInt16 aaWorld;
VectorFloat gravity;
float euler[3];
float ypr[3];

// 用于 InvenSense teapot 示例的数据包结构
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };


/**
 * @brief 初始化MPU6050
 * @param 无
 * @return 无
*/
void Mpu6050_eleccat :: Mpu6050_eleccat_init(){

    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3V or Arduino
    // Pro Mini running at 3.3V, cannot handle this baud rate reliably due to
    // the baud timing being too misaligned with processor ticks. You must use
    // 38400 or slower in these cases, or use some kind of external separate
    // crystal solution for the UART timer.

    // initialize device
    // Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    // pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    // Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // // wait for ready
    // Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    // while (Serial.available() && Serial.read()); // empty buffer
    // while (!Serial.available());                 // wait for data
    // while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050mpuIntStatusmpu.setDMPEnabled(true);
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        // Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        // Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        // Serial.println(F(")..."));
        // attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } 
    else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    // pinMode(LED_PIN, OUTPUT);
}
/**
 * @brief 获取yaw角度
 * @param angle[10]   俯仰角，横滚角，偏航角
 * @return yaw角度
*/
float Mpu6050_eleccat :: Mpu6050_eleccat_getYaw(uint8_t angle){

    // 从 FIFO 读取数据包
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // 获取最新数据包
   
        #ifdef OUTPUT_READABLE_YAWPITCHROLL
        // 显示偏航、俯仰和横滚角（角度）
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        // Serial.print("ypr\t");
        // Serial.print(ypr[0] * 180/M_PI);
        // Serial.print("\t");
        // Serial.print(ypr[1] * 180/M_PI);
        // Serial.print("\t");
        // Serial.println(ypr[2] * 180/M_PI);
        #endif

        switch (angle)
        {
        case 0:
            return ypr[0] * 180/M_PI;
            break;
        case 1:
            return ypr[1] * 180/M_PI;
            break;
        case 2:
            return ypr[2] * 180/M_PI;
            break;
        
        
        }
}

}

/**
 * @brief 运行
 * @param 无
 * @return 无
*/
void Mpu6050_eleccat :: Mpu6050_run(){



 if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // 获取最新数据包
   
        #ifdef OUTPUT_READABLE_YAWPITCHROLL
        // 显示偏航、俯仰和横滚角（角度）
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        // Serial.print("ypr\t");
        // Serial.print(ypr[0] * 180/M_PI);
        // Serial.print("\t");
        // Serial.print(ypr[1] * 180/M_PI);
        // Serial.print("\t");
        // Serial.println(ypr[2] * 180/M_PI);
        #endif
        }

}