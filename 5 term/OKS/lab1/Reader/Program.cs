using Reader;

var argument = args[0].Split(',');

var portName = argument[0].Trim();

var speed = int.Parse(argument[1].Trim());

var readerPort = new ReaderPort(portName, speed);

readerPort.ReadProccess();