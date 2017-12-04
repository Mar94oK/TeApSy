#ifndef SIPSAPPHIREREFBOARD_H
#define SIPSAPPHIREREFBOARD_H

#include <QString>

struct VoltagesMeasuredByExternalADC {
    
    //are measured by externtal TI ADCs
    float voltage_12V_SYS; //1
    float voltage_1V2D; //2
    float voltage_AML_VCC_CORE; //3
    float voltage_5V0D_AON; //4
    float voltage_5V0D; //5
    float voltage_5V0D_GS1; //6
    float voltage_3V3D; //7
    float voltage_1V5_DDR3_AML; //8
    float voltage_1V5_DDR3_GS1; //9
    float voltage_VDDIO_AO18; //10
    float voltage_VCC1V8; //11
    float voltage_3V3A_1; //12
    float voltage_3V3A_2; //13
    float voltage_1V2D_DMD; //14
    float voltage_3V3D_GS1; //15
    
};


struct CurrentsMeasuredByExternalADC {
    
    //are measured by externtal TI ADCs
    float voltage_12V_SYS; //1
    float voltage_1V2D; //2
    float voltage_AML_VCC_CORE; //3
    float voltage_5V0D_AON; //4
    float voltage_5V0D; //5
    float voltage_5V0D_GS1; //6
    float voltage_3V3D; //7
    float voltage_1V5_DDR3_AML; //8
    float voltage_1V5_DDR3_GS1; //9
    float voltage_VDDIO_AO18; //10
    float voltage_VCC1V8; //11
    float voltage_3V3A_1; //12
    float voltage_3V3A_2; //13
    float voltage_1V2D_DMD; //14
    float voltage_3V3D_GS1; //15
    
    
};

struct VoltagesMeasuredByInternalADC {
    //are measured by ADC in uC
    float input_voltage;
    float battery_voltage;
    
};

struct TemperatureSensorsData {

    double _mainCpuTemp;
    double _cryptoCpuTemp;
    double _LNBp1Temp;
    double _LNBp2Temp;
    double _demodulator1Temp;
    double _demodulator2Temp;
    double _tuner1Temp;
    double _tuner2Temp;

};

struct I2CDevice {

  QString _I2CdeviceName;
  QString _I2CdeviceAddress;
  bool _foundOnBus;


};



struct VoltageCurrentData {
    QString _name;
    float _valueVoltage;
    float _valueCurrent;

};


struct I2CDeviceFoundOnBus {

    I2CDevice _device;
    unsigned int totalScansPerfromed;

};

class SipSapphireCommand {

    QString _commandTitle;
    QString _command;


public:

    SipSapphireCommand( QString commandTitle, QString command);



    QString command() const;
    QString commandTitle() const;
};


class SiPSapphireRefBoard
{
public:
    SiPSapphireRefBoard();
    
private:
    
    VoltagesMeasuredByExternalADC _voltagesMainDomain;
    CurrentsMeasuredByExternalADC _currentsMainDomain;
    VoltagesMeasuredByInternalADC _voltagesAuxilaryMeasurements; //inputs and uC;

    double _temperature; //onBoardSensor;

    TemperatureSensorsData _extTempMeasICs;
    I2CDeviceFoundOnBus _foundDevices;


    
};

#endif // SIPSAPPHIREREFBOARD_H
