
let relaysent = false;
let timer1;
document
  .getElementById('temp_slide')
  .addEventListener('input', handleSlideInput);
document
  .getElementById('turn_on_slide')
  .addEventListener('input', handleSlideInput);
document
  .getElementById('turn_off_slide')
  .addEventListener('input', handleSlideInput);
function handleSlideInput() {
  clearTimeout(timer1);

  timer1 = setTimeout(function () {
    const nguongnhietdo = parseFloat(
      document.getElementById('temp_slide').value
    );
    const nguongdoam = parseFloat(
      document.getElementById('turn_on_slide').value
    );
    const nguongdoamdat = parseFloat(
      document.getElementById('turn_off_slide').value
    );

    if (isNaN(nguongnhietdo) || isNaN(nguongdoam) || isNaN(nguongdoamdat)) {
      if (!relaysent) {
        document.getElementById('switch1').checked = false;
        socket.emit('relay', 0);
        relaysent = true;
      }
    } else {
      let hienthinhietdo = parseFloat(
        document.getElementById('temperatureWindow').innerHTML
      );
      let hienthindoam = parseFloat(
        document.getElementById('humidityWindow').innerHTML
      );
      let hienthidoamdat = parseFloat(
        document.getElementById('soilMoistureWindow').innerHTML
      );

      if (
        nguongnhietdo <= hienthinhietdo &&
        nguongdoam <= hienthindoam &&
        nguongdoamdat <= hienthidoamdat
      ) {
        document.getElementById('switch1').checked = true;
        socket.emit('relay', 1);
      } else {
        document.getElementById('switch1').checked = false;
        socket.emit('relay', 0);
      }
      relaysent = false;
    }
  }, 1000);
}

document.getElementById('switch2').addEventListener('change', function () {
  const switchValue1 = this.checked ? 1 : 0;
  socket.emit('relay', switchValue1);
});

let isEventProcessed1 = false;
function checkAndUpdateStatus1() {
  const hour1data = parseInt(document.getElementById('hour1').value);
  const minute1data = parseInt(document.getElementById('minute1').value);
  console.log(hour1data, minute1data);

  const currentTime = moment();
  const currentHour = currentTime.format('HH');
  const currentMinute = currentTime.format('mm');

  if (
    hour1data === parseInt(currentHour) &&
    minute1data === parseInt(currentMinute) &&
    !isEventProcessed1
  ) {
    document.getElementById('switch3').checked = true;
    socket.emit('relay', 1);
    isEventProcessed1 = true;

    setTimeout(() => {
      document.getElementById('switch3').checked = false;
      socket.emit('relay', 0);
      isEventProcessed1 = false;
    }, 30000);
  }
}
const intervalId1 = setInterval(checkAndUpdateStatus1, 1000);

