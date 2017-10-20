#ifndef SIPSAPPHIREREFBOARD_H
#define SIPSAPPHIREREFBOARD_H


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









class SiPSapphireRefBoard
{
public:
    SiPSapphireRefBoard();
    
private:
    
    
    
    
};

#endif // SIPSAPPHIREREFBOARD_H
