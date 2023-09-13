using System.IO.Ports;

namespace Common
{
    public class PortWrapper : IDisposable
    {
        protected SerialPort _serialPort;

        public PortWrapper(string portName, int speed)
        {
            _serialPort = new SerialPort(portName, speed, Parity.None, 8, StopBits.One);
            _serialPort.Open();

            _serialPort.ReadTimeout = 500;
            _serialPort.WriteTimeout = 500;
        }

        public void PortInfo() 
        {
            Console.WriteLine($"Process started on port {_serialPort.PortName} with speed: {_serialPort.BaudRate}");
        }
        public void Dispose()
        {
            _serialPort.Dispose();
        }
    }
}
