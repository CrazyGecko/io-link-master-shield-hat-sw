
//!*****************************************************************************
//!  \file      Max14819.h
//!*****************************************************************************
//!
//!  \brief		max14819 driver specific layer
//!
//!  \author    Pascal Frei (freip2)
//!
//!  \date      2019-06-27
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!	
//!*****************************************************************************
#ifndef MAX14819_HPP_INCLUDED
#define MAX14819_HPP_INCLUDED



//!**** Header-Files **********************************************************
#include <memory>
#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLMessage.hpp"
#include "protocol/IOLinkConfig.hpp"
//!**** Macros ****************************************************************


//!**** Data types ************************************************************

//!**** Function prototypes ***************************************************

//!**** Data ******************************************************************

//!**** Implementation ********************************************************
class Max14819 : public std::enable_shared_from_this<Max14819>{
public:
    // Error define
    static constexpr uint8_t ERROR             = 1u;
    static constexpr uint8_t SUCCESS           = 0u;
    // MAX14819 DI Init defines
    static constexpr uint8_t CURRENT_SOURCE    = 0x02u;
    static constexpr uint8_t CURRENT_SINK      = 0x01u;
    static constexpr uint8_t CURRENT_DISABLE   = 0x00u;
    static constexpr uint8_t THRSLD_TYPE1      = 1u;        // Different Threshold Levels, see MAX14819 Datasheet, p. 5
    static constexpr uint8_t THRSLD_TYPE2      = 0u;        // Different Threshold Levels, see MAX14819 Datasheet, p. 5
    static constexpr uint8_t FILTER_EN         = 0x08u;     // Glich filter enable
    static constexpr uint8_t FILTER_DIS        = 0x00u;     // Glich filter disable

    // Timing constexprants for Max14819
    static constexpr uint32_t INIT_POWER_OFF_DELAY	= 1000u;	// Delay in ms for disable duration of sensor power when startup
    static constexpr uint32_t INIT_BOOTUP_DELAY    = 300u;	// Delay after switch-to-operational-command
    static constexpr uint32_t INIT_WURQ_TIMEOUT    = 80u;   // Timeout in ms for abort WURQ request (2x retry after 10ms, 3x tries a 20ms)

    // Max14819 Register defines
    static constexpr uint8_t TxRxDataA     = 0x00u;
    static constexpr uint8_t TxRxDataB     = 0x01u;

    static constexpr uint8_t Interrupt     = 0x02u;
    static constexpr uint8_t StatusInt     = 0x80u;
    static constexpr uint8_t WURQInt       = 0x40u;
    static constexpr uint8_t TxErrorB      = 0x20u;
    static constexpr uint8_t TxErrorA      = 0x10u;
    static constexpr uint8_t RxErrorB      = 0x08u;
    static constexpr uint8_t RxErrorA    	= 0x04u;
    static constexpr uint8_t RxDataRdyB    = 0x02u;
    static constexpr uint8_t RxDataRdyA   	= 0x01u;

    static constexpr uint8_t InterruptEn   = 0x03u;
    static constexpr uint8_t StatusIntEn   = 0x80u;
    static constexpr uint8_t WURQIntEn     = 0x40u;
    static constexpr uint8_t TxErrIntEnB   = 0x20u;
    static constexpr uint8_t TxErrIntEnA   = 0x10u;
    static constexpr uint8_t RxErrIntEnB   = 0x08u;
    static constexpr uint8_t RxErrIntEnA   = 0x04u;
    static constexpr uint8_t RxDaRdyIntEnB = 0x02u;
    static constexpr uint8_t RxDaRdyIntEnA = 0x01u;

    static constexpr uint8_t RxFIFOLvlA 	= 0x04u;
    static constexpr uint8_t RxFIFOLvlB 	= 0x05u;

    static constexpr uint8_t CQCtrlA       = 0x06u;
    static constexpr uint8_t CQCtrlB       = 0x07u;
    static constexpr uint8_t ComRt1        = 0x80u;
    static constexpr uint8_t ComRt0        = 0x40u;
    static constexpr uint8_t EstCom        = 0x20u;
    static constexpr uint8_t WuPuls        = 0x10u;
    static constexpr uint8_t TxFifoRst     = 0x08u;
    static constexpr uint8_t RxFifoRst     = 0x04u;
    static constexpr uint8_t CycleTmrEn    = 0x02u;
    static constexpr uint8_t CQSend        = 0x01u;

    static constexpr uint8_t CQErrA        = 0x08u;
    static constexpr uint8_t CQErrB        = 0x09u;
    static constexpr uint8_t TransmErr     = 0x80u;
    static constexpr uint8_t TCyclErr      = 0x40u;
    static constexpr uint8_t TChksmEr      = 0x20u;
    static constexpr uint8_t TSizeErr      = 0x10u;
    static constexpr uint8_t RChksmEr	    = 0x08u;
    static constexpr uint8_t RSizeErr      = 0x04u;
    static constexpr uint8_t FrameErr      = 0x02u;
    static constexpr uint8_t ParityErr     = 0x01u;

    static constexpr uint8_t MsgCtrlA      = 0x0Au;
    static constexpr uint8_t MsgCtrlB      = 0x0Bu;
    static constexpr uint8_t TxErDestroy   = 0x80u;
    static constexpr uint8_t SPIChks       = 0x40u;
    static constexpr uint8_t InsChks       = 0x20u;
    static constexpr uint8_t TSizeEn       = 0x10u;
    static constexpr uint8_t TxKeepMsg     = 0x08u;
    static constexpr uint8_t RChksEn       = 0x04u;
    static constexpr uint8_t RMessgRdyEn   = 0x02u;
    static constexpr uint8_t InvCQ         = 0x01u;

    static constexpr uint8_t ChanStatA     = 0x0Cu;
    static constexpr uint8_t ChanStatB     = 0x0Du;
    static constexpr uint8_t Rst           = 0x80u;
    static constexpr uint8_t FramerEn      = 0x40u;
    static constexpr uint8_t LCLimCOR 	    = 0x20u;
    static constexpr uint8_t CQFaultCOR 	= 0x10u;
    static constexpr uint8_t LCLim         = 0x08u;
    static constexpr uint8_t UVL           = 0x04u;
    static constexpr uint8_t CQFault       = 0x02u;

    static constexpr uint8_t LEDCtrl       = 0x0Eu;
    static constexpr uint8_t LEDEn2B       = 0x80u;
    static constexpr uint8_t RxErrEnB 	    = 0x40u;
    static constexpr uint8_t LEDEn1B       = 0x20u;
    static constexpr uint8_t RxRdyEnB      = 0x10u;
    static constexpr uint8_t LEDEn2A       = 0x08u;
    static constexpr uint8_t RxErrEnA      = 0x04u;
    static constexpr uint8_t LEDEn1A       = 0x02u;
    static constexpr uint8_t RxRdyEnA      = 0x01u;

    static constexpr uint8_t Trigger       = 0x0Fu;
    static constexpr uint8_t TrigInit3     = 0x08u;
    static constexpr uint8_t TrigInit2     = 0x04u;
    static constexpr uint8_t TrigInit1     = 0x02u;
    static constexpr uint8_t TrigInit0     = 0x01u;

    static constexpr uint8_t CQCfgA        = 0x10u;
    static constexpr uint8_t CQCfgB        = 0x11u;
    static constexpr uint8_t IEC3Th        = 0x80u;
    static constexpr uint8_t SourceSink    = 0x40u;
    static constexpr uint8_t SinkSel1      = 0x20u;
    static constexpr uint8_t SinkSel0 	    = 0x10u;
    static constexpr uint8_t NPN           = 0x08u;
    static constexpr uint8_t PushPul       = 0x04u;
    static constexpr uint8_t DrvDis        = 0x02u;
    static constexpr uint8_t CQFilterEn    = 0x01u;

    static constexpr uint8_t CyclTmrA 	    = 0x12u;
    static constexpr uint8_t CyclTmrB      = 0x12u;
    static constexpr uint8_t TCyclBs1      = 0x80u;
    static constexpr uint8_t TCyclBs0      = 0x40u;
    static constexpr uint8_t TCyclM5       = 0x20u;
    static constexpr uint8_t TCyclM4       = 0x10u;
    static constexpr uint8_t TCyclM3       = 0x08u;
    static constexpr uint8_t TCyclM2       = 0x04u;
    static constexpr uint8_t TCyclM1       = 0x02u;
    static constexpr uint8_t TCyclM0       = 0x01u;

    static constexpr uint8_t DeviceDlyA    = 0x14u;
    static constexpr uint8_t DeviceDlyB    = 0x15u;
    static constexpr uint8_t DelayErr      = 0x80u;
    static constexpr uint8_t BDelay1       = 0x40u;
    static constexpr uint8_t BDelay0       = 0x20u;
    static constexpr uint8_t DDelay3       = 0x10u;
    static constexpr uint8_t DDelay2       = 0x08u;
    static constexpr uint8_t DDelay1       = 0x04u;
    static constexpr uint8_t DDelay0       = 0x02u;
    static constexpr uint8_t RspnsTmrEn    = 0x01u;

    static constexpr uint8_t TrigAssgnA    = 0x16u;
    static constexpr uint8_t TrigAssgnB    = 0x17u;
    static constexpr uint8_t Trig3         = 0x80u;
    static constexpr uint8_t Trig2         = 0x40u;
    static constexpr uint8_t Trig1         = 0x20u;
    static constexpr uint8_t Trig0         = 0x10u;
    static constexpr uint8_t TrigEn        = 0x01u;

    static constexpr uint8_t LCnfgA        = 0x18u;
    static constexpr uint8_t LCnfgB        = 0x19u;
    static constexpr uint8_t LRT1          = 0x80u;
    static constexpr uint8_t LRT0          = 0x40u;
    static constexpr uint8_t LDynBL        = 0x20u;
    static constexpr uint8_t LBL1          = 0x10u;
    static constexpr uint8_t LBL0          = 0x08u;
    static constexpr uint8_t LCL2x         = 0x04u;
    static constexpr uint8_t LClimDis      = 0x02u;
    static constexpr uint8_t LEn           = 0x01u;

    static constexpr uint8_t IOStCfgA      = 0x1Au;
    static constexpr uint8_t IOStCfgB      = 0x1Bu;
    static constexpr uint8_t DiLevel       = 0x80u;
    static constexpr uint8_t CQLevel       = 0x40u;
    static constexpr uint8_t TxEn          = 0x20u;
    static constexpr uint8_t Tx            = 0x10u;
    static constexpr uint8_t DiFilterEn    = 0x08u;
    static constexpr uint8_t DiEC3Th       = 0x04u;
    static constexpr uint8_t DiCSource     = 0x02u;
    static constexpr uint8_t DiCSink       = 0x01u;

    static constexpr uint8_t DrvrCurrLim   = 0x1Cu;
    static constexpr uint8_t CL1           = 0x80u;
    static constexpr uint8_t CL0           = 0x40u;
    static constexpr uint8_t CLDis         = 0x20u;
    static constexpr uint8_t CLBL1         = 0x10u;
    static constexpr uint8_t CLBL0         = 0x08u;
    static constexpr uint8_t TAr1          = 0x04u;
    static constexpr uint8_t TAr0          = 0x02u;
    static constexpr uint8_t ArEn          = 0x01u;

    static constexpr uint8_t Clock         = 0x1Du;
    static constexpr uint8_t VCCWarnEn     = 0x80u;
    static constexpr uint8_t TXTXENDis     = 0x40u;
    static constexpr uint8_t ExtClkMis     = 0x20u;
    static constexpr uint8_t ClkOEn        = 0x10u;
    static constexpr uint8_t ClkDiv1       = 0x08u;
    static constexpr uint8_t ClkDiv0       = 0x04u;
    static constexpr uint8_t ExtClkEn      = 0x02u;
    static constexpr uint8_t XtalEn        = 0x01u;

    static constexpr uint8_t Status        = 0x1Eu;
    static constexpr uint8_t ThShdnCOR     = 0x80u;
    static constexpr uint8_t ThWarnCOR     = 0x40u;
    static constexpr uint8_t VCCUVCOR      = 0x20u;
    static constexpr uint8_t VCCWarnCOR    = 0x10u;
    static constexpr uint8_t ThShdn        = 0x08u;
    static constexpr uint8_t TempWarn      = 0x04u;
    static constexpr uint8_t VCCUV         = 0x02u;
    static constexpr uint8_t VCCWarn       = 0x01u;

    static constexpr uint8_t RevID         = 0x1Fu;
    static constexpr uint8_t ID3           = 0x08u;
    static constexpr uint8_t ID2           = 0x04u;
    static constexpr uint8_t ID1           = 0x02u;
    static constexpr uint8_t ID0           = 0x01u;

    static constexpr uint8_t MAX_REG       = RevID;

    // maximal number of bytes to send (according to max14819 FIFO length)
    static constexpr uint8_t MAX_MSG_LENGTH= 64;

    class PIN
    {
    private:
        /* data */
    public:
        PIN(/* args */){};
        virtual ~PIN(){};
        virtual void set(bool){};
    };

    class SPI
    {
    private:
        /* data */
    public:
        SPI(/* args */){};
        virtual ~SPI(){};
        virtual void DataRW(uint8_t* data, uint8_t length) = 0;
    };

    class DebugOut
    {
    private:
        /* data */
    public:
        DebugOut(/* args */){};
        virtual ~DebugOut(){};
        virtual void print(char const * buf){};
    };
    
    class Wait
    {
    private:
        /* data */
    public:
        Wait(){};
        virtual ~Wait(){};
        virtual void ms(uint32_t ms){};
    };

    class Max14819_Port : public openiolinklibrary::IOLMasterPort
    {
    public:
        struct CommunicationInfo
        {
            uint8_t comSpeed;
            uint32_t comSpeedBaud;
        };
        enum class PortNr {PORTA=0, PORTB=1};

    private:
        PortNr portnr;
        std::shared_ptr<Max14819> chip;
        CommunicationInfo communicationInfo;
    
    protected:
        uint8_t sendIOLData(uint8_t* data, uint8_t sizeofdata, uint8_t sizeofanswer);
        
    public:
        Max14819_Port(PortNr portnr_, std::shared_ptr<Max14819> chip_): portnr(portnr_), chip(chip_){};
        ~Max14819_Port(){};
        void setMode(Mode);
        void wakeUpRequest();

        CommunicationInfo getCommunicationInfo(){return communicationInfo;};
    };
    
    
private:
    std::shared_ptr<PIN> ErrLED=nullptr;
    std::shared_ptr<PIN> StatLED=nullptr;
    std::shared_ptr<SPI> spi_interface;
    std::shared_ptr<DebugOut> debug_interface;
    std::shared_ptr<Wait> wait;

    uint8_t spi_address;

    std::shared_ptr<Max14819_Port> PORTA;
    std::shared_ptr<Max14819_Port> PORTB;



public:
    Max14819(std::shared_ptr<DebugOut> debugout_, std::shared_ptr<SPI> spi_interface_, uint8_t spi_address_, std::shared_ptr<Wait> wait_);
    // Max14819(DriverSelect driver, SPI spi_interface);
    // Max14819(DriverSelect driver, SPI spi_interface, PIN ledred_);
    // Max14819(DriverSelect driver, SPI spi_interface, PIN ledred_, PIN ledgreen_);
    // Max14819(DriverSelect driver, SPI spi_interface, PIN ledgreen_);
    ~Max14819();
    void initPorts (void);
    uint8_t reset(void);
    uint8_t writeRegister(uint8_t reg, uint8_t data);
    uint8_t readRegister(uint8_t reg);
    std::shared_ptr<Max14819_Port> getPort(Max14819_Port::PortNr port);
};// class max14819

#endif //MAX14819_HPP_INCLUDED
