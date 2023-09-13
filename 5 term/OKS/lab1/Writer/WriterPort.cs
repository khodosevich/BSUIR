using Common;
using System.Text;

namespace Writer
{
    public class WriterPort : PortWrapper
    {
        public WriterPort(string portName,int  speed) : base(portName, speed)
        {
        }

        public void WriteProccess()
        {
            base.PortInfo();

            while (true)
            {
                var data = Console.ReadLine();

                var bytes = Encoding.ASCII.GetBytes(data);

                var valueBytes = bytes.Append((byte)0).ToArray();

                _serialPort.Write(valueBytes, 0, valueBytes.Length);
            }
        }
    }
}
