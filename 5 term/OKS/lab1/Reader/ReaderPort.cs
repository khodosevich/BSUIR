using Common;
using System.IO.Ports;
using System.Text;

namespace Reader
{
    internal class ReaderPort : PortWrapper
    {
        public ReaderPort(string portName, int speed) : base(portName, speed)
        {
            _serialPort.DataReceived += new SerialDataReceivedEventHandler(Output);
        }

        public void ReadProccess() 
        {
            base.PortInfo();

            while (true) ;
        }

        private void Output(object sender, SerialDataReceivedEventArgs e)
        {
            var buffer = new byte[1024];
            _serialPort.Read(buffer, 0, 1024);

            var valueBuffer = buffer.TakeWhile(b => b != 0).ToArray();

            var data = Encoding.ASCII.GetString(valueBuffer);

            Console.WriteLine(data);
            Console.WriteLine($"{valueBuffer.Length} bytes received");
        }
    }
}
