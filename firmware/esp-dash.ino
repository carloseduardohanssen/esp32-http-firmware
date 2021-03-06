
#if ESP_DASH && !DEEP_SLEEP

void buttonClicked(const char* id) {
  DEBUG_PRINTLNC("Button Clicked - " + String(id));
  digitalWrite(LED, !digitalRead(LED));
}

void initEspDash() {
  ESPDash.init(server);

  ESPDash.addTemperatureCard("temperature_01", "Sensor 01", 0, 20);
  ESPDash.addLineChart("sensor_01", "Sensor 01 - Temperature", x_axis, x_axis_size, "Cº", y_axis, y_axis_size);
  ESPDash.addButtonCard("btn_let", "Blink Button");
  ESPDash.attachButtonClick(buttonClicked);

  server.begin();
}
#endif

