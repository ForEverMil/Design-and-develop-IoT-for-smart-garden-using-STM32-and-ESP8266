const mqtt = require('mqtt');
const express = require('express');
const http = require('http');
const fs = require('fs');
const cors = require('cors');
const { Server } = require('socket.io');
const bodyParser = require('body-parser');

const app = express();
app.use(cors());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

const io = new Server(3001, {
  cors: {
    origin: '*',
  },
});

const mqttBroker = 'mqtt://mqtt-dashboard.com';
const mqttClient = mqtt.connect(mqttBroker);

mqttClient.on('connect', function () {
  console.log('Connected to MQTT Broker');
  mqttClient.subscribe('esp8266/sensor');
});

mqttClient.on('message', function (topic, message) {
  if (topic === 'esp8266/sensor') {
    var sensorData = JSON.parse(message.toString());
    console.log('Received message from MQTT broker:', message.toString());
    io.emit('sensorData', sensorData);
  }
});

const PORT = process.env.PORT || 3000;

app.listen(PORT, function () {
  console.log(`Server is running on port ${PORT}`);
});

io.on('connection', function (socket) {
  console.log('A user connected');

  socket.on('disconnect', function () {
    console.log('User disconnected');
  });

  socket.on('relay', function (relayValue) {
    const mqttMessage = relayValue === 1 ? "1" : "0";
    mqttClient.publish('esp8266/control', mqttMessage);
    console.log('Published MQTT message:', mqttMessage);
  });
});
