speed = $prop("SpeedKmh");
rpm = $prop("Rpms");
abs = $prop("ABSLevel");
gear = $prop("Gear");
fuel = $prop("FuelPercent");
engine = $prop("EngineStarted");
tclevel = $prop("TCLevel");

var date = new Date();

hour = date.getHours();
minute = date.getMinutes();

return `${speed}-${rpm}-${abs}-${gear}-${fuel}-${engine}-${tclevel}-${hour}-${minute}-EOF-\n`;
