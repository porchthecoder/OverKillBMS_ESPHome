#include <bms2.h>
#include <bms2_options.h>
#include <esphome.h>

OverkillSolarBms2 bms = OverkillSolarBms2();
#define SOC_POLL_RATE 1000  // Send every n milliseconds
HardwareSerial HWSerial(2); // Define a Serial port instance called 'Receiver' using serial port 2

#define Receiver_Txd_pin 16
#define Receiver_Rxd_pin 17

//#define BMS_OPTION_DEBUG
//#define FAKE_BMS

uint32_t timestamp_1000ms = 0;

class MyCustomSensor : public PollingComponent, public Sensor
{
public:
        Sensor *voltage_sensor = new Sensor();
        Sensor *current_sensor = new Sensor();
        Sensor *soc_sensor = new Sensor();
        Sensor *cfet_sensor = new Sensor();
        Sensor *dfet_sensor = new Sensor();

        Sensor *cellv1_sensor = new Sensor();
        Sensor *cellv2_sensor = new Sensor();
        Sensor *cellv3_sensor = new Sensor();
        Sensor *cellv4_sensor = new Sensor();
        Sensor *cellv5_sensor = new Sensor();
        Sensor *cellv6_sensor = new Sensor();
        Sensor *cellv7_sensor = new Sensor();
        Sensor *cellv8_sensor = new Sensor();
        Sensor *cellv9_sensor = new Sensor();
        Sensor *cellv10_sensor = new Sensor();
        Sensor *cellv11_sensor = new Sensor();
        Sensor *cellv12_sensor = new Sensor();
        Sensor *cellv13_sensor = new Sensor();
        Sensor *cellv14_sensor = new Sensor();
        Sensor *cellv15_sensor = new Sensor();
        Sensor *cellv16_sensor = new Sensor();

        Sensor *ssov_protection_sensor = new Sensor();
        Sensor *ssov_count_sensor = new Sensor();
        Sensor *ssuv_protection_sensor = new Sensor();
        Sensor *ssuv_count_sensor = new Sensor();

        Sensor *wpov_protection_sensor = new Sensor();
        Sensor *wpov_count_sensor = new Sensor();
        Sensor *wpuv_protection_sensor = new Sensor();
        Sensor *wpuv_count_sensor = new Sensor();

        Sensor *cot_protection_sensor = new Sensor();
        Sensor *cot_count_sensor = new Sensor();
        Sensor *clt_protection_sensor = new Sensor();
        Sensor *clt_count_sensor = new Sensor();

        Sensor *dot_protection_sensor = new Sensor();
        Sensor *dot_count_sensor = new Sensor();
        Sensor *dlt_protection_sensor = new Sensor();
        Sensor *dlt_count_sensor = new Sensor();

        Sensor *coc_protection_sensor = new Sensor();
        Sensor *coc_count_sensor = new Sensor();
        Sensor *doc_protection_sensor = new Sensor();
        Sensor *doc_count_sensor = new Sensor();

        Sensor *sc_protection_sensor = new Sensor();
        Sensor *sc_count_sensor = new Sensor();

        Sensor *fed_protection_sensor = new Sensor();
        Sensor *fed_count_sensor = new Sensor();

        Sensor *slmos_protection_sensor = new Sensor();
        Sensor *slmos_count_sensor = new Sensor();

        Sensor *temp1_sensor = new Sensor();
        Sensor *temp2_sensor = new Sensor();
        Sensor *temp3_sensor = new Sensor();

        Sensor *bal_cap_sensor = new Sensor();
        Sensor *rate_cap_sensor = new Sensor();
        Sensor *cycle_count_sensor = new Sensor();

        Sensor *bms_comm_sensor = new Sensor();

        // constructor
        // MyCustomSensor() : PollingComponent(15000) {}
        uint32_t last_update;

        void setup() override
        {
                // This will be called by App.setup()
                HWSerial.begin(9600, SERIAL_8N1, Receiver_Rxd_pin, Receiver_Txd_pin);

                while (!Serial1)
                { // Wait for the BMS serial port to initialize
                }
                bms.begin(&HWSerial);
                bms.set_query_rate(2000); // Set query rate to 2000 milliseconds (2 seconds)
                last_update = millis();
        }

        void update() override
        {
                // This will be called every "update_interval" milliseconds.
                bms.main_task(true);
                // bms.debug();

                if (bms.get_comm_error_state())
                { // returns false if comm is ok, true if it fails.
                        Serial.println("Can not talk to BMS");
                        bms_comm_sensor->publish_state(0); // return 1 if communication with the BMS is unknown
                        return;
                }

                // Do something at 1 millisecond
                if (millis() - last_update >= 2500)
                {

                        bms_comm_sensor->publish_state(1); // Return 1 if we are talking to the BMS.

                        // bms.query_0x03_basic_info();

                        float voltage = bms.get_voltage();
                        voltage_sensor->publish_state(voltage);

                        float current = bms.get_current();
                        current_sensor->publish_state(current);

                        float soc = bms.get_state_of_charge();
                        soc_sensor->publish_state(soc);

                        uint8_t cfet = bms.get_charge_mosfet_status() ? 1 : 0;
                        cfet_sensor->publish_state(cfet);

                        uint8_t dfet = bms.get_discharge_mosfet_status() ? 1 : 0;
                        dfet_sensor->publish_state(dfet);

                        float cellv1 = bms.get_cell_voltage(0);
                        cellv1_sensor->publish_state(cellv1);

                        float cellv2 = bms.get_cell_voltage(1);
                        cellv2_sensor->publish_state(cellv2);

                        float cellv3 = bms.get_cell_voltage(2);
                        cellv3_sensor->publish_state(cellv3);

                        float cellv4 = bms.get_cell_voltage(3);
                        cellv4_sensor->publish_state(cellv4);

                        float cellv5 = bms.get_cell_voltage(4);
                        cellv5_sensor->publish_state(cellv5);

                        float cellv6 = bms.get_cell_voltage(5);
                        cellv6_sensor->publish_state(cellv6);

                        float cellv7 = bms.get_cell_voltage(6);
                        cellv7_sensor->publish_state(cellv7);

                        float cellv8 = bms.get_cell_voltage(7);
                        cellv8_sensor->publish_state(cellv8);

                        float cellv9 = bms.get_cell_voltage(8);
                        cellv9_sensor->publish_state(cellv9);

                        float cellv10 = bms.get_cell_voltage(9);
                        cellv10_sensor->publish_state(cellv10);

                        float cellv11 = bms.get_cell_voltage(10);
                        cellv11_sensor->publish_state(cellv11);

                        float cellv12 = bms.get_cell_voltage(11);
                        cellv12_sensor->publish_state(cellv12);

                        float cellv13 = bms.get_cell_voltage(12);
                        cellv13_sensor->publish_state(cellv13);

                        float cellv14 = bms.get_cell_voltage(13);
                        cellv14_sensor->publish_state(cellv14);

                        float cellv15 = bms.get_cell_voltage(14);
                        cellv15_sensor->publish_state(cellv15);

                        float cellv16 = bms.get_cell_voltage(15);
                        cellv16_sensor->publish_state(cellv16);

                        ProtectionStatus flags = bms.get_protection_status();
                        FaultCount fault = bms.get_fault_counts();

                        bool ssov = flags.single_cell_overvoltage_protection;
                        ssov_protection_sensor->publish_state(ssov);
                        uint8_t ssov_count = fault.single_cell_overvoltage_protection;
                        ssov_count_sensor->publish_state(ssov_count);

                        bool ssuv = flags.single_cell_undervoltage_protection;
                        ssuv_protection_sensor->publish_state(ssuv);
                        uint8_t ssuv_count = fault.single_cell_undervoltage_protection;
                        ssuv_count_sensor->publish_state(ssuv_count);

                        bool wpov = flags.whole_pack_overvoltage_protection;
                        wpov_protection_sensor->publish_state(wpov);
                        uint8_t wpov_count = fault.whole_pack_overvoltage_protection;
                        wpov_count_sensor->publish_state(wpov_count);

                        bool wpuv = flags.whole_pack_undervoltage_protection;
                        wpuv_protection_sensor->publish_state(wpov);
                        uint8_t wpuv_count = fault.whole_pack_undervoltage_protection;
                        wpuv_count_sensor->publish_state(wpuv_count);

                        bool cot = flags.charging_over_temperature_protection;
                        cot_protection_sensor->publish_state(cot);
                        uint8_t cot_count = fault.charging_over_temperature_protection;
                        cot_count_sensor->publish_state(cot_count);

                        bool clt = flags.charging_low_temperature_protection;
                        clt_protection_sensor->publish_state(clt);
                        uint8_t clt_count = fault.charging_low_temperature_protection;
                        clt_count_sensor->publish_state(clt_count);

                        bool dot = flags.discharge_over_temperature_protection;
                        dot_protection_sensor->publish_state(dot);
                        uint8_t dot_count = fault.discharge_over_temperature_protection;
                        dot_count_sensor->publish_state(dot_count);

                        bool dlt = flags.discharge_low_temperature_protection;
                        dlt_protection_sensor->publish_state(dlt);
                        uint8_t dlt_count = fault.discharge_low_temperature_protection;
                        dlt_count_sensor->publish_state(dlt_count);

                        bool coc = flags.charging_overcurrent_protection;
                        coc_protection_sensor->publish_state(coc);
                        uint8_t coc_count = fault.charging_overcurrent_protection;
                        coc_count_sensor->publish_state(coc_count);

                        bool doc = flags.discharge_overcurrent_protection;
                        doc_protection_sensor->publish_state(doc);
                        uint8_t doc_count = fault.discharge_overcurrent_protection;
                        doc_count_sensor->publish_state(doc_count);

                        bool sc = flags.short_circuit_protection;
                        sc_protection_sensor->publish_state(sc);
                        uint8_t sc_count = fault.short_circuit_protection;
                        sc_count_sensor->publish_state(sc_count);

                        bool fed = flags.front_end_detection_ic_error;
                        fed_protection_sensor->publish_state(fed);
                        uint8_t fed_count = fault.front_end_detection_ic_error;
                        fed_count_sensor->publish_state(fed_count);

                        bool slmos = flags.software_lock_mos;
                        slmos_protection_sensor->publish_state(slmos);
                        uint8_t slmos_count = fault.software_lock_mos;
                        slmos_count_sensor->publish_state(slmos_count);

                        float temp1 = bms.get_ntc_temperature(0);
                        temp1_sensor->publish_state(temp1);
                        float temp2 = bms.get_ntc_temperature(1);
                        temp3_sensor->publish_state(temp2);
                        float temp3 = bms.get_ntc_temperature(2);
                        temp3_sensor->publish_state(temp3);

                        float bal_cap = bms.get_balance_capacity();
                        bal_cap_sensor->publish_state(bal_cap);
                        float rate_cap = bms.get_rate_capacity();
                        rate_cap_sensor->publish_state(rate_cap);
                        float cycle_count = bms.get_cycle_count();
                        cycle_count_sensor->publish_state(cycle_count);

                        // bms.debug();
                        last_update = millis();
                }
        }
};
