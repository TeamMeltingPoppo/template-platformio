/*
 * Example of a simple MAVLink node that sends a heartbeat message every second and toggles the built-in LED when it receives a heartbeat message.
 */

#include <Arduino.h>
#include <mavlink/swingby/mavlink.h>

namespace
{
    constexpr uint8_t system_id = 1;
    constexpr uint8_t component_id = 1;
}

void send_heartbeat();
void handle_mavlink_message(const mavlink_message_t &message);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
    static uint32_t last_heartbeat_time = 0;
    mavlink_message_t raw_message;
    mavlink_status_t parse_status;
    // read MAVLink messages from Serial
    if (mavlink_parse_char(MAVLINK_COMM_0, Serial.read(), &raw_message, &parse_status))
    {
        handle_mavlink_message(raw_message);
    }
    // send heartbeat every 1 second
    if (millis() - last_heartbeat_time > 1000)
    {
        send_heartbeat();
        last_heartbeat_time = millis();
    }
}

void send_heartbeat()
{
    mavlink_message_t raw_message;
    mavlink_heartbeat_t heartbeat;
    heartbeat.type = MAV_TYPE::MAV_TYPE_GENERIC;
    heartbeat.autopilot = MAV_AUTOPILOT::MAV_AUTOPILOT_GENERIC;
    heartbeat.base_mode = MAV_MODE::MAV_MODE_PREFLIGHT;
    heartbeat.custom_mode = 0;
    heartbeat.system_status = MAV_STATE::MAV_STATE_STANDBY;
    heartbeat.mavlink_version = 3;
    mavlink_msg_heartbeat_encode(system_id, component_id, &raw_message, &heartbeat);
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &raw_message);
    Serial.write(buffer, len);
}

void handle_mavlink_message(const mavlink_message_t &message)
{
    switch (message.msgid)
    {
    case MAVLINK_MSG_ID_HEARTBEAT:
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        mavlink_heartbeat_t heartbeat;
        mavlink_msg_heartbeat_decode(&message, &heartbeat);
        Serial.printf("Received heartbeat: type=%d, autopilot=%d, base_mode=%d, custom_mode=%d, system_status=%d, mavlink_version=%d\n",
                      heartbeat.type,
                      heartbeat.autopilot,
                      heartbeat.base_mode,
                      heartbeat.custom_mode,
                      heartbeat.system_status,
                      heartbeat.mavlink_version);
    }
    break;
    default:
    {
        // do nothing
    }
    break;
    }
}